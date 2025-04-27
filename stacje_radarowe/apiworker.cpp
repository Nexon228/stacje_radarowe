#include "apiworker.h"
#include <QDir>
#include <QFile>
#include <QThread>
#include <QDebug>

ApiWorker::ApiWorker(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void ApiWorker::fetchStations(const QString &city) {
    currentCity = city;
    qDebug() << "Fetching stations in thread:" << QThread::currentThread();
    const QNetworkRequest request(QUrl("https://api.gios.gov.pl/pjp-api/rest/station/findAll"));
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::onStationsFetched);
}

void ApiWorker::fetchSensors(int stationId) {
    currentStationId = stationId;
    qDebug() << "Fetching sensors in thread:" << QThread::currentThread();
    const QNetworkRequest request(QUrl("https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + QString::number(stationId)));
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::onSensorsFetched);
}

void ApiWorker::fetchData(int sensorId) {
    currentSensorId = sensorId;
    qDebug() << "Fetching data in thread:" << QThread::currentThread();
    const QNetworkRequest request(QUrl("https://api.gios.gov.pl/pjp-api/rest/data/getData/" + QString::number(sensorId)));
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiWorker::onDataFetched);
}

void ApiWorker::onStationsFetched() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() != QNetworkReply::NoError) {
        emit networkError(reply->errorString());
        reply->deleteLater();
        return;
    }

    try {
        QByteArray response = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            emit networkError("JSON parsing error: " + parseError.errorString());
            reply->deleteLater();
            return;
        }

        if (doc.isArray()) {
            QJsonArray stations = doc.array();
            QDir().mkpath("offline");
            QFile file("offline/stacje.json");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(QJsonDocument(stations).toJson());
                file.close();
            } else {
                emit networkError("Failed to write to file: offline/stacje.json");
            }
            emit stationsFetched(stations, currentCity);
        } else {
            emit networkError("Expected JSON array for stations");
        }
    } catch (const std::exception &e) {
        emit networkError("Exception occurred: " + QString(e.what()));
    }

    reply->deleteLater();
}

void ApiWorker::onSensorsFetched() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() != QNetworkReply::NoError) {
        emit networkError(reply->errorString());
        reply->deleteLater();
        return;
    }

    try {
        QByteArray response = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            emit networkError("JSON parsing error: " + parseError.errorString());
            reply->deleteLater();
            return;
        }

        if (doc.isArray()) {
            QJsonArray sensors = doc.array();
            QString filename = "offline/sensory_" + QString::number(currentStationId) + ".json";
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(QJsonDocument(sensors).toJson());
                file.close();
            } else {
                emit networkError("Failed to write to file: " + filename);
            }
            emit sensorsFetched(sensors, currentStationId);
        } else {
            emit networkError("Expected JSON array for sensors");
        }
    } catch (const std::exception &e) {
        emit networkError("Exception occurred: " + QString(e.what()));
    }

    reply->deleteLater();
}

void ApiWorker::onDataFetched() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() != QNetworkReply::NoError) {
        emit networkError(reply->errorString());
        reply->deleteLater();
        return;
    }

    try {
        QByteArray response = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            emit networkError("JSON parsing error: " + parseError.errorString());
            reply->deleteLater();
            return;
        }

        QJsonObject data = doc.object();
        QString filename = "offline/dane_" + QString::number(currentSensorId) + ".json";
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        } else {
            emit networkError("Failed to write to file: " + filename);
        }
        emit dataFetched(data, currentSensorId);
    } catch (const std::exception &e) {
        emit networkError("Exception occurred: " + QString(e.what()));
    }

    reply->deleteLater();
}
