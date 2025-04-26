#ifndef APIWORKER_H
#define APIWORKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/**
 * @class ApiWorker
 * @brief Handles API requests in a separate thread.
 *
 * This class performs network requests to the GIOŚ API in a separate thread
 * to prevent blocking the main UI thread.
 */
class ApiWorker : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs the ApiWorker.
     * @param parent The parent object (default is nullptr).
     */
    explicit ApiWorker(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
    }

public slots:
    /**
     * @brief Fetches the list of stations from the specified URL.
     * @param url The API endpoint URL.
     */
    void fetchStations(const QString &url) {
        QNetworkRequest request(QUrl(url));
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            emit stationsFetched(reply->readAll(), reply->error(), reply->errorString());
            reply->deleteLater();
        });
    }

    /**
     * @brief Fetches the list of sensors for a station from the specified URL.
     * @param url The API endpoint URL.
     */
    void fetchSensors(const QString &url) {
        QNetworkRequest request(QUrl(url));
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            emit sensorsFetched(reply->readAll(), reply->error(), reply->errorString());
            reply->deleteLater();
        });
    }

    /**
     * @brief Fetches measurement data for a sensor from the specified URL.
     * @param url The API endpoint URL.
     */
    void fetchData(const QString &url) {
        QNetworkRequest request(QUrl(url));
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            emit dataFetched(reply->readAll(), reply->error(), reply->errorString());
            reply->deleteLater();
        });
    }

signals:
    /**
     * @brief Emitted when stations data is fetched.
     * @param data The raw JSON data.
     * @param error The network error code.
     * @param errorString The error description.
     */
    void stationsFetched(const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString);

    /**
     * @brief Emitted when sensors data is fetched.
     * @param data The raw JSON data.
     * @param error The network error code.
     * @param errorString The error description.
     */
    void sensorsFetched(const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString);

    /**
     * @brief Emitted when measurement data is fetched.
     * @param data The raw JSON data.
     * @param error The network error code.
     * @param errorString The error description.
     */
    void dataFetched(const QByteArray &data, QNetworkReply::NetworkError error, const QString &errorString);

private:
    QNetworkAccessManager *manager;  ///< Manager for handling network requests.
};

#endif // APIWORKER_H