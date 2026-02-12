#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QApplication>
#include <QtTest/QSignalSpy>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "mainwindow.h"
#include "apiworker.h"

// Globalna zmienna dla QApplication
int global_argc = 1;
char *global_argv[] = {(char*)"test", nullptr};

// Klasa mockująca QNetworkReply do testowania ApiWorker
class MockNetworkReply : public QNetworkReply {
public:
    MockNetworkReply(QObject *parent = nullptr) : QNetworkReply(parent) {}
    void setError(NetworkError error, const QString &errorString) {
        QNetworkReply::setError(error, errorString);
    }
    void setRawData(const QByteArray &data) {
        rawData = data;
    }
    QByteArray readAll() { return rawData; } // Usunięto 'override', jeśli nie jest wymagane
    void abort() override {}
    qint64 bytesAvailable() const override { return rawData.size(); }
protected:
    qint64 readData(char *data, qint64 maxSize) override {
        Q_UNUSED(data);
        Q_UNUSED(maxSize);
        return -1;
    }
private:
    QByteArray rawData;
};

// Klasa mockująca QNetworkAccessManager
class MockNetworkAccessManager : public QNetworkAccessManager {
public:
    MockNetworkAccessManager(QObject *parent = nullptr) : QNetworkAccessManager(parent) {}
    // Ręcznie zdefiniowana metoda get zamiast MOCK_METHOD
    MOCK_METHOD1(get, QNetworkReply*(const QNetworkRequest &request));
};

// Fixture testowy dla MainWindow i ApiWorker
class MainWindowTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = new QApplication(global_argc, global_argv);
        window = new MainWindow();
        worker = new ApiWorker();
        mockManager = new MockNetworkAccessManager(worker);

        // Zastąp domyślny QNetworkAccessManager w ApiWorker naszym mockiem
        worker->manager->deleteLater();
        worker->manager = mockManager;
    }

    void TearDown() override {
        delete worker;
        delete window;
        delete app;
        app = nullptr;
    }

    QApplication* app = nullptr;
    MainWindow* window = nullptr;
    ApiWorker* worker = nullptr;
    MockNetworkAccessManager* mockManager = nullptr;
};

// Test inicjalizacji MainWindow
TEST_F(MainWindowTest, Initialization) {
    ASSERT_NE(window, nullptr);
    ASSERT_NE(window->findChild<QComboBox*>("comboStacje"), nullptr);
    ASSERT_NE(window->findChild<QComboBox*>("comboSensory"), nullptr);
    ASSERT_NE(window->findChild<QPushButton*>("buttonPobierzStacje"), nullptr);
    ASSERT_TRUE(window->findChild<QComboBox*>("comboZakres")->count() > 0);
}

// Test pobierania stacji przez ApiWorker
TEST_F(MainWindowTest, ApiWorker_FetchStations_Success) {
    // Przygotuj dane odpowiedzi
    QJsonArray stationsArray;
    QJsonObject station;
    station["id"] = QJsonValue(1);
    station["stationName"] = QJsonValue("Station 1");
    QJsonObject city;
    city["name"] = QJsonValue("Krakow");
    station["city"] = city;
    stationsArray.append(station);

    QByteArray responseData = QJsonDocument(stationsArray).toJson();

    // Skonfiguruj mock
    MockNetworkReply *reply = new MockNetworkReply();
    reply->setRawData(responseData);
    reply->setError(QNetworkReply::NoError, "");

    EXPECT_CALL(*mockManager, get(testing::_))
        .WillOnce(testing::Return(reply));

    // Użyj QSignalSpy do monitorowania sygnału
    QSignalSpy spy(worker, &ApiWorker::stationsFetched);

    // Wywołaj metodę fetchStations
    worker->fetchStations("Krakow");

    // Poczekaj na sygnał
    spy.wait(1000);

    // Sprawdź, czy sygnał został wyemitowany
    ASSERT_EQ(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QJsonArray resultStations = arguments.at(0).value<QJsonArray>();
    QString resultCity = arguments.at(1).toString();

    ASSERT_EQ(resultStations.size(), 1);
    ASSERT_EQ(resultStations[0].toObject()["stationName"].toString(), "Station 1");
    ASSERT_EQ(resultCity, "Krakow");
}

// Test obsługi błędów sieciowych w ApiWorker
TEST_F(MainWindowTest, ApiWorker_FetchStations_NetworkError) {
    // Skonfiguruj mock z błędem sieciowym
    MockNetworkReply *reply = new MockNetworkReply();
    reply->setError(QNetworkReply::ConnectionRefusedError, "Connection refused");

    EXPECT_CALL(*mockManager, get(testing::_))
        .WillOnce(testing::Return(reply));

    // Użyj QSignalSpy do monitorowania sygnału networkError
    QSignalSpy spy(worker, &ApiWorker::networkError);

    // Wywołaj metodę fetchStations
    worker->fetchStations("Krakow");

    // Poczekaj na sygnał
    spy.wait(1000);

    // Sprawdź, czy sygnał networkError został wyemitowany
    ASSERT_EQ(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QString errorString = arguments.at(0).toString();
    ASSERT_EQ(errorString, "Connection refused");
}

// Test parsowania błędnego JSON-a w ApiWorker
TEST_F(MainWindowTest, ApiWorker_FetchStations_InvalidJson) {
    // Przygotuj niepoprawny JSON
    QByteArray responseData = "invalid json data";

    // Skonfiguruj mock
    MockNetworkReply *reply = new MockNetworkReply();
    reply->setRawData(responseData);
    reply->setError(QNetworkReply::NoError, "");

    EXPECT_CALL(*mockManager, get(testing::_))
        .WillOnce(testing::Return(reply));

    // Użyj QSignalSpy do monitorowania sygnału networkError
    QSignalSpy spy(worker, &ApiWorker::networkError);

    // Wywołaj metodę fetchStations
    worker->fetchStations("Krakow");

    // Poczekaj na sygnał
    spy.wait(1000);

    // Sprawdź, czy sygnał networkError został wyemitowany
    ASSERT_EQ(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QString errorString = arguments.at(0).toString();
    ASSERT_TRUE(errorString.contains("JSON parsing error"));
}

// Test wielowątkowości ApiWorker w MainWindow
TEST_F(MainWindowTest, ApiWorker_Threading) {
    // Sprawdź, czy ApiWorker działa w osobnym wątku
    QThread *workerThread = window->findChild<QThread*>("workerThread");
    ASSERT_NE(workerThread, nullptr);
    ASSERT_NE(window->thread(), worker->thread());
    ASSERT_EQ(worker->thread(), workerThread);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
