#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "apiworker.h"

#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
namespace QtCharts {
class QChartView;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Główne okno aplikacji monitorującej jakość powietrza.
 *
 * Klasa MainWindow odpowiada za interfejs użytkownika, pobieranie danych z API GIOŚ,
 * wyświetlanie wykresów oraz analizę danych pomiarowych. Wykorzystuje wielowątkowość
 * poprzez ApiWorker działający w osobnym wątku QThread, co zapewnia responsywność GUI.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     * @param parent Wskaźnik na rodzica widgetu (domyślnie nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Obsługuje dane stacji pobrane przez ApiWorker.
     * @param stations Tablica JSON z danymi stacji.
     * @param city Miasto, dla którego pobrano stacje.
     */
    void handleStationsFetched(const QJsonArray &stations, const QString &city);

    /**
     * @brief Obsługuje dane sensorów pobrane przez ApiWorker.
     * @param sensors Tablica JSON z danymi sensorów.
     * @param stationId Identyfikator stacji.
     */
    void handleSensorsFetched(const QJsonArray &sensors, int stationId);

    /**
     * @brief Obsługuje dane pomiarowe pobrane przez ApiWorker.
     * @param data Obiekt JSON z danymi pomiarowymi.
     * @param sensorId Identyfikator sensora.
     */
    void handleDataFetched(const QJsonObject &data, int sensorId);

    /**
     * @brief Obsługuje błędy sieciowe.
     * @param errorString Opis błędu.
     */
    void handleNetworkError(const QString &errorString);

private:
    Ui::MainWindow *ui; /**< Wskaźnik na interfejs użytkownika. */
    QChartView *chartView; /**< Wskaźnik na widok wykresu. */
    QThread *workerThread; /**< Wątek dla ApiWorker. */
    ApiWorker *apiWorker; /**< Instancja ApiWorker do pobierania danych. */
};

#endif // MAINWINDOW_H
