#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QFile>
#include <QDir>
#include <QMessageBox>

/**
 * @brief Constructs the MainWindow and initializes the UI and components.
 * @param parent The parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize thread and worker for API requests
    apiWorker = new ApiWorker();
    apiThread = new QThread(this);
    apiWorker->moveToThread(apiThread);
    apiThread->start();

    // Usuń istniejący QFrame
    QFrame* oldChartFrame = ui->chartView;
    QRect frameGeometry = oldChartFrame->geometry();

    // Stwórz nowy QChartView
    chartView = new QChartView(this);
    chartView->setObjectName("chartView");
    chartView->setGeometry(frameGeometry);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameShape(QFrame::StyledPanel);
    chartView->setFrameShadow(QFrame::Raised);

    // Zastąp stary widget nowym w układzie rodzica
    if (oldChartFrame->parentWidget() && oldChartFrame->parentWidget()->layout()) {
        QLayout* parentLayout = oldChartFrame->parentWidget()->layout();
        parentLayout->replaceWidget(oldChartFrame, chartView);
    } else {
        chartView->setParent(oldChartFrame->parentWidget());
    }

    // Usuń stary frame
    oldChartFrame->setParent(nullptr);
    delete oldChartFrame;

    // Inicjalizacja kombo z zakresami dat
    ui->comboZakres->addItems({
        "Ostatnia doba",
        "Ostatni tydzień",
        "Ostatni miesiąc",
        "Ostatni rok",
        "Własny zakres"
    });

    // Ustaw początkową wartość dla pól daty
    ui->dateOd->setDate(QDate::currentDate().addDays(-7));
    ui->dateDo->setDate(QDate::currentDate());

    // Domyślnie ukryj elementy wyboru daty
    ui->dateOd->setVisible(false);
    ui->dateDo->setVisible(false);
    ui->LabelDo->setVisible(false);
    ui->LabelOd->setVisible(false);

    // Pobieranie stacji dla miasta
    connect(ui->buttonPobierzStacje, &QPushButton::clicked, this, [=]() {
        QString miasto = ui->inputMiasto->text().trimmed();
        if (miasto.isEmpty()) return;

        miasto[0] = miasto[0].toUpper(); // pierwsza litera wielka
        ui->buttonPobierzStacje->setEnabled(false); // Disable button during fetch

        apiWorker->fetchStations("https://api.gios.gov.pl/pjp-api/rest/station/findAll");
    });

    connect(apiWorker, &ApiWorker::stationsFetched, this, [=](const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString) {
        ui->buttonPobierzStacje->setEnabled(true); // Re-enable button

        if (error != QNetworkReply::NoError) {
            ui->textWyniki->setPlainText("Błąd sieci: " + errorString);
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(data);

        if (!doc.isArray()) {
            ui->comboStacje->clear();
            ui->comboStacje->addItem("Brak wyników");
            return;
        }

        QJsonArray stacje = doc.array();

        // Zapisz wszystkie stacje do pliku lokalnego
        QJsonDocument allStationsDoc(stacje);
        QDir().mkpath("offline");  // folder offline
        QFile file("offline/stacje.json");
        if (file.open(QIODevice::WriteOnly)) {
            file.write(allStationsDoc.toJson());
            file.close();
            qDebug() << "Zapisano stacje.json";
        }

        ui->comboStacje->clear();

        QString miasto = ui->inputMiasto->text().trimmed();
        miasto[0] = miasto[0].toUpper();
        for (const QJsonValue &val : stacje) {
            QJsonObject ob = val.toObject();
            if (ob.contains("city") && ob["city"].isObject()) {
                QString cityName = ob["city"].toObject()["name"].toString();
                if (cityName == miasto) {
                    QString nazwa = ob["stationName"].toString();
                    int id = ob["id"].toInt();
                    ui->comboStacje->addItem(nazwa, id);
                }
            }
        }

        if (ui->comboStacje->count() == 0)
            ui->comboStacje->addItem("Brak wyników");
    });

    // Obsługa zmiany stacji - pobieranie sensorów
    connect(ui->comboStacje, &QComboBox::currentIndexChanged, this, [=](int index) {
        if (index < 0 || ui->comboStacje->currentData().isNull()) return;

        int stationId = ui->comboStacje->currentData().toInt();
        QString endpoint = "https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + QString::number(stationId);
        apiWorker->fetchSensors(endpoint);
    });

    connect(apiWorker, &ApiWorker::sensorsFetched, this, [=](const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString) {
        if (error != QNetworkReply::NoError) {
            ui->textWyniki->setPlainText("Błąd sieci: " + errorString);

            // Próba wczytania danych offline
            int stationId = ui->comboStacje->currentData().toInt();
            QString fileName = "offline/sensory_" + QString::number(stationId) + ".json";

            if (QFile::exists(fileName)) {
                QFile file(fileName);
                if (file.open(QIODevice::ReadOnly)) {
                    QByteArray data = file.readAll();
                    QJsonDocument doc = QJsonDocument::fromJson(data);
                    QJsonArray sensory = doc.array();

                    ui->comboSensory->clear();
                    for (const QJsonValue &val : sensory) {
                        QJsonObject ob = val.toObject();
                        QString paramName = ob["param"].toObject()["paramName"].toString();
                        int sensorId = ob["id"].toInt();
                        ui->comboSensory->addItem(paramName, sensorId);
                    }

                    if (ui->comboSensory->count() == 0)
                        ui->comboSensory->addItem("Brak czujników (offline)");

                    file.close();
                }
            }
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(data);

        if (!doc.isArray()) {
            ui->comboSensory->clear();
            ui->comboSensory->addItem("Brak czujników");
            return;
        }

        QJsonArray sensory = doc.array();

        // Zapisz sensory do pliku offline
        int stationId = ui->comboStacje->currentData().toInt();
        QJsonDocument docToSave(sensory);
        QString filename = "offline/sensory_" + QString::number(stationId) + ".json";
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(docToSave.toJson());
            file.close();
        }

        ui->comboSensory->clear();
        for (const QJsonValue &val : sensory) {
            QJsonObject ob = val.toObject();
            QString paramName = ob["param"].toObject()["paramName"].toString();
            int sensorId = ob["id"].toInt();
            ui->comboSensory->addItem(paramName, sensorId);
        }

        if (ui->comboSensory->count() == 0)
            ui->comboSensory->addItem("Brak czujników");
    });

    // Obsługa zmian wyboru zakresu dat
    connect(ui->comboZakres, &QComboBox::currentTextChanged, this, [=](const QString &text) {
        bool show = (text == "Własny zakres");
        ui->dateOd->setVisible(show);
        ui->dateDo->setVisible(show);
        ui->LabelDo->setVisible(show);
        ui->LabelOd->setVisible(show);
    });

    // Obsługa trybu offline
    connect(ui->buttonOffline, &QPushButton::clicked, this, [=]() {
        QString miasto = ui->inputMiasto->text().trimmed();
        if (miasto.isEmpty()) return;
        miasto[0] = miasto[0].toUpper();

        // Wczytaj stacje.json
        QFile stacjeFile("offline/stacje.json");
        if (!stacjeFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Błąd", "Brak pliku offline/stacje.json");
            return;
        }

        QByteArray stacjeData = stacjeFile.readAll();
        stacjeFile.close();
        QJsonDocument stacjeDoc = QJsonDocument::fromJson(stacjeData);
        QJsonArray stacjeArray = stacjeDoc.array();

        ui->comboStacje->clear();
        bool found = false;

        // Szukamy stacji z podanego miasta
        for (const QJsonValue &val : stacjeArray) {
            QJsonObject ob = val.toObject();
            if (ob.contains("city") && ob["city"].isObject()) {
                QString cityName = ob["city"].toObject()["name"].toString();
                if (cityName == miasto) {
                    QString stationName = ob["stationName"].toString();
                    int stationId = ob["id"].toInt();
                    ui->comboStacje->addItem(stationName, stationId);
                    found = true;
                }
            }
        }

        if (!found) {
            QMessageBox::information(this, "Brak wyników", "Nie znaleziono stacji dla miasta.");
            return;
        }

        // Automatycznie wybierz pierwszą stację
        if (ui->comboStacje->count() > 0) {
            int stationId = ui->comboStacje->itemData(0).toInt();

            // Wczytaj sensory z sensory_{stationId}.json
            QString sensoryFileName = "offline/sensory_" + QString::number(stationId) + ".json";
            QFile sensoryFile(sensoryFileName);
            if (!sensoryFile.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, "Błąd", "Brak pliku " + sensoryFileName);
                return;
            }

            QByteArray sensoryData = sensoryFile.readAll();
            sensoryFile.close();
            QJsonDocument sensoryDoc = QJsonDocument::fromJson(sensoryData);
            QJsonArray sensoryArray = sensoryDoc.array();

            ui->comboSensory->clear();

            for (const QJsonValue &val : sensoryArray) {
                QJsonObject ob = val.toObject();
                QString paramName = ob["param"].toObject()["paramName"].toString();
                int sensorId = ob["id"].toInt();
                ui->comboSensory->addItem(paramName, sensorId);
            }

            QMessageBox::information(this, "Tryb offline", "Dane wczytane z plików lokalnych.");
        }
    });

    // Pobieranie danych pomiarowych
    connect(ui->buttonPobierzDane, &QPushButton::clicked, this, [=]() {
        if (ui->comboSensory->currentIndex() < 0 || ui->comboSensory->currentData().isNull()) {
            QMessageBox::warning(this, "Uwaga", "Wybierz sensor do pobrania danych");
            return;
        }

        int sensorId = ui->comboSensory->currentData().toInt();
        if (sensorId == 0) return;

        QString endpoint = "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + QString::number(sensorId);
        apiWorker->fetchData(endpoint);
    });

    connect(apiWorker, &ApiWorker::dataFetched, this, [=](const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString) {
        if (error != QNetworkReply::NoError) {
            ui->textWyniki->setPlainText("Błąd sieci: " + errorString + "\nPróba wczytania danych offline...");

            // Próba wczytania danych offline
            int sensorId = ui->comboSensory->currentData().toInt();
            QString fileName = "offline/dane_" + QString::number(sensorId) + ".json";

            if (QFile::exists(fileName)) {
                QFile file(fileName);
                if (file.open(QIODevice::ReadOnly)) {
                    QByteArray data = file.readAll();
                    QJsonDocument doc = QJsonDocument::fromJson(data);
                    QJsonObject root = doc.object();
                    QJsonArray values = root["values"].toArray();

                    // Implementacja tej samej logiki co dla online
                    QString zakres = ui->comboZakres->currentText();
                    QDateTime cutoff;
                    QDate fromDate, toDate;
                    bool customRange = (zakres == "Własny zakres");

                    if (customRange) {
                        fromDate = ui->dateOd->date();
                        toDate = ui->dateDo->date();
                    } else if (zakres == "Ostatnia doba") {
                        cutoff = QDateTime::currentDateTime().addDays(-1);
                    } else if (zakres == "Ostatni tydzień") {
                        cutoff = QDateTime::currentDateTime().addDays(-7);
                    } else if (zakres == "Ostatni miesiąc") {
                        cutoff = QDateTime::currentDateTime().addMonths(-1);
                    } else if (zakres == "Ostatni rok") {
                        cutoff = QDateTime::currentDateTime().addYears(-1);
                    }

                    QLineSeries *series = new QLineSeries();
                    series->setName(ui->comboSensory->currentText());

                    QString output = "DANE OFFLINE:\n";

                    // Zmienne do statystyk
                    double minValue = std::numeric_limits<double>::max();
                    double maxValue = std::numeric_limits<double>::min();
                    double sum = 0.0;
                    int count = 0;
                    QDateTime minTime, maxTime;
                    QVector<QPair<QDateTime, double>> trendData;

                    for (const QJsonValue &val : values) {
                        QJsonObject ob = val.toObject();
                        QDateTime dateTime = QDateTime::fromString(ob["date"].toString(), Qt::ISODate);
                        if (!dateTime.isValid()) continue;

                        if (customRange) {
                            if (dateTime.date() < fromDate || dateTime.date() > toDate) continue;
                        } else {
                            if (dateTime < cutoff) continue;
                        }

                        QString valueStr = ob["value"].isNull() ? "brak danych" : QString::number(ob["value"].toDouble());
                        output += dateTime.toString("dd.MM.yyyy hh:mm") + " → " + valueStr + "\n";

                        if (!ob["value"].isNull()) {
                            double value = ob["value"].toDouble();
                            series->append(dateTime.toMSecsSinceEpoch(), value);
                            trendData.append({dateTime, value});

                            // Statystyki
                            if (value < minValue) {
                                minValue = value;
                                minTime = dateTime;
                            }
                            if (value > maxValue) {
                                maxValue = value;
                                maxTime = dateTime;
                            }
                            sum += value;
                            count++;
                        }
                    }

                    // Dodaj statystyki do wyniku
                    if (count > 0) {
                        double average = sum / count;
                        QString trend = calculateTrend(trendData);
                        output += "\n📊 Statystyki:\n";
                        output += "🔺 Maksimum: " + QString::number(maxValue) + " (" + maxTime.toString("dd.MM.yyyy hh:mm") + ")\n";
                        output += "🔻 Minimum: " + QString::number(minValue) + " (" + minTime.toString("dd.MM.yyyy hh:mm") + ")\n";
                        output += "📈 Średnia: " + QString::number(average, 'f', 2) + "\n";
                        output += "📉 Trend: " + trend + "\n";
                    }

                    ui->textWyniki->setPlainText(output);

                    // Tworzenie wykresu
                    QChart *chart = new QChart();
                    chart->addSeries(series);
                    chart->setTitle("Pomiary OFFLINE " + ui->comboSensory->currentText() + " - " + ui->comboStacje->currentText());

                    QDateTimeAxis *axisX = new QDateTimeAxis();
                    if (zakres == "Ostatni rok") {
                        axisX->setFormat("MM.yyyy");
                    } else {
                        axisX->setFormat("dd.MM.yyyy");
                    }
                    axisX->setTitleText("Data pomiaru");

                    QValueAxis *axisY = new QValueAxis();
                    axisY->setLabelFormat("%.1f");
                    axisY->setTitleText(ui->comboSensory->currentText());

                    chart->addAxis(axisX, Qt::AlignBottom);
                    chart->addAxis(axisY, Qt::AlignLeft);
                    series->attachAxis(axisX);
                    series->attachAxis(axisY);

                    chartView->setChart(chart);
                    file.close();
                } else {
                    ui->textWyniki->setPlainText("Błąd odczytu pliku offline: " + fileName);
                }
            } else {
                ui->textWyniki->setPlainText("Brak danych offline dla wybranego sensora.");
            }
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();

        // Zapisz dane do pliku offline
        int sensorId = ui->comboSensory->currentData().toInt();
        QString filename = "offline/dane_" + QString::number(sensorId) + ".json";
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        }

        QJsonArray values = root["values"].toArray();

        // Ustalanie zakresu dat
        QString zakres = ui->comboZakres->currentText();
        QDateTime cutoff;
        QDate fromDate, toDate;
        bool customRange = (zakres == "Własny zakres");

        if (customRange) {
            fromDate = ui->dateOd->date();
            toDate = ui->dateDo->date();
        } else if (zakres == "Ostatnia doba") {
            cutoff = QDateTime::currentDateTime().addDays(-1);
        } else if (zakres == "Ostatni tydzień") {
            cutoff = QDateTime::currentDateTime().addDays(-7);
        } else if (zakres == "Ostatni miesiąc") {
            cutoff = QDateTime::currentDateTime().addMonths(-1);
        } else if (zakres == "Ostatni rok") {
            cutoff = QDateTime::currentDateTime().addYears(-1);
        }

        QLineSeries *series = new QLineSeries();
        series->setName(ui->comboSensory->currentText());

        QString output;

        // Zmienne do statystyk
        double minValue = std::numeric_limits<double>::max();
        double maxValue = std::numeric_limits<double>::min();
        double sum = 0.0;
        int count = 0;
        QDateTime minTime, maxTime;
        QVector<QPair<QDateTime, double>> trendData;

        for (const QJsonValue &val : values) {
            QJsonObject ob = val.toObject();
            QDateTime dateTime = QDateTime::fromString(ob["date"].toString(), Qt::ISODate);
            if (!dateTime.isValid()) continue;

            if (customRange) {
                if (dateTime.date() < fromDate || dateTime.date() > toDate) continue;
            } else {
                if (dateTime < cutoff) continue;
            }

            // Dodaj do wyniku tekstowego
            QString valueStr = ob["value"].isNull() ? "brak danych" : QString::number(ob["value"].toDouble());
            output += dateTime.toString("dd.MM.yyyy hh:mm") + " → " + valueStr + "\n";

            // Dodaj do wykresu i statystyk
            if (!ob["value"].isNull()) {
                double value = ob["value"].toDouble();
                series->append(dateTime.toMSecsSinceEpoch(), value);
                trendData.append({dateTime, value});

                // Statystyki
                if (value < minValue) {
                    minValue = value;
                    minTime = dateTime;
                }
                if (value > maxValue) {
                    maxValue = value;
                    maxTime = dateTime;
                }
                sum += value;
                count++;
            }
        }

        // Dodaj statystyki do wyniku
        if (count > 0) {
            double average = sum / count;
            QString trend = calculateTrend(trendData);
            output += "\n📊 Statystyki:\n";
            output += "🔺 Maksimum: " + QString::number(maxValue) + " (" + maxTime.toString("dd.MM.yyyy hh:mm") + ")\n";
            output += "🔻 Minimum: " + QString::number(minValue) + " (" + minTime.toString("dd.MM.yyyy hh:mm") + ")\n";
            output += "📈 Średnia: " + QString::number(average, 'f', 2) + "\n";
            output += "📉 Trend: " + trend + "\n";
        }

        ui->textWyniki->setPlainText(output);

        // Tworzenie wykresu
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Pomiary " + ui->comboSensory->currentText() + " - " + ui->comboStacje->currentText());

        QDateTimeAxis *axisX = new QDateTimeAxis();
        if (zakres == "Ostatni rok") {
            axisX->setFormat("MM.yyyy");
        } else {
            axisX->setFormat("dd.MM.yyyy");
        }
        axisX->setTitleText("Data pomiaru");

        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelFormat("%.1f");
        axisY->setTitleText(ui->comboSensory->currentText());

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        chartView->setChart(chart);
    });
}

/**
 * @brief Destroys the MainWindow and cleans up resources.
 */
MainWindow::~MainWindow()
{
    apiThread->quit();
    apiThread->wait();
    delete apiWorker;
    delete ui;
}

/**
 * @brief Calculates the trend of the measurement data using linear regression.
 * @param data Vector of pairs containing timestamp and measurement value.
 * @return QString describing the trend ("Rosnący", "Malejący", or "Stabilny").
 */
QString MainWindow::calculateTrend(const QVector<QPair<QDateTime, double>> &data) {
    if (data.size() < 2) return "Brak danych do analizy trendu";

    // Simple linear regression: y = mx + b
    double n = data.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;

    // Use timestamps as X values (in seconds since epoch)
    for (int i = 0; i < n; ++i) {
        double x = data[i].first.toMSecsSinceEpoch() / 1000.0; // Convert to seconds
        double y = data[i].second;
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumXX += x * x;
    }

    // Calculate slope (m)
    double slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);

    // Determine trend based on slope
    if (slope > 0.01) return "Rosnący";
    else if (slope < -0.01) return "Malejący";
    else return "Stabilny";
}
