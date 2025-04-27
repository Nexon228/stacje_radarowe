#ifndef APIWORKER_H
#define APIWORKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QThread>

/**
 * @class ApiWorker
 * @brief Klasa do asynchronicznego pobierania danych z API GIOŚ w osobnym wątku.
 *
 * ApiWorker zarządza żądaniami sieciowymi do API GIOŚ, zapisuje dane do plików offline
 * i emituje sygnały z pobranymi danymi w formacie JSON. Działa w osobnym wątku QThread,
 * aby nie blokować GUI.
 */
class ApiWorker : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy ApiWorker.
     * @param parent Wskaźnik na rodzica (domyślnie nullptr).
     */
    explicit ApiWorker(QObject *parent = nullptr);

    /**
     * Upublicznij manager dla testów
     */
    QNetworkAccessManager *manager;

    /**
     * @brief Pobiera listę stacji pomiarowych.
     * @param city Nazwa miasta, dla którego pobierane są stacje.
     */
    void fetchStations(const QString &city);

    /**
     * @brief Pobiera listę sensorów dla danej stacji.
     * @param stationId Identyfikator stacji pomiarowej.
     */
    void fetchSensors(int stationId);

    /**
     * @brief Pobiera dane pomiarowe dla danego sensora.
     * @param sensorId Identyfikator sensora.
     */
    void fetchData(int sensorId);

signals:
    /**
     * @brief Sygnał emitowany po pobraniu stacji.
     * @param stations Tablica JSON z danymi stacji.
     * @param city Miasto, dla którego pobrano stacje.
     */
    void stationsFetched(const QJsonArray &stations, const QString &city);

    /**
     * @brief Sygnał emitowany po pobraniu sensorów.
     * @param sensors Tablica JSON z danymi sensorów.
     * @param stationId Identyfikator stacji.
     */
    void sensorsFetched(const QJsonArray &sensors, int stationId);

    /**
     * @brief Sygnał emitowany po pobraniu danych pomiarowych.
     * @param data Obiekt JSON z danymi pomiarowymi.
     * @param sensorId Identyfikator sensora.
     */
    void dataFetched(const QJsonObject &data, int sensorId);

    /**
     * @brief Sygnał emitowany w przypadku błędu sieciowego.
     * @param errorString Opis błędu.
     */
    void networkError(const QString &errorString);

private slots:
    /**
     * @brief Slot obsługujący zakończenie pobierania stacji.
     */
    void onStationsFetched();

    /**
     * @brief Slot obsługujący zakończenie pobierania sensorów.
     */
    void onSensorsFetched();

    /**
     * @brief Slot obsługujący zakończenie pobierania danych pomiarowych.
     */
    void onDataFetched();

private:
    QString currentCity; /**< Przechowuje miasto dla bieżącego żądania. */
    int currentStationId; /**< Przechowuje ID stacji dla bieżącego żądania. */
    int currentSensorId; /**< Przechowuje ID sensora dla bieżącego żądania. */
};

#endif // APIWORKER_H
