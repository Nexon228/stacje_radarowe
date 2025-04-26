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

class ApiWorker : public QObject {
    Q_OBJECT
public:
    explicit ApiWorker(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
    }

    void fetchStations(const QString &city) {
        QNetworkRequest request(QUrl("https://api.gios.gov.pl/pjp-api/rest/station/findAll"));
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &ApiWorker::onStationsFetched);
    }

signals:
    void stationsFetched(const QJsonArray &stations);

private slots:
    void onStationsFetched() {
        QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            if (doc.isArray()) {
                emit stationsFetched(doc.array());
            }
        }
        reply->deleteLater();
    }

private:
    QNetworkAccessManager *manager;
};

#endif // APIWORKER_H
