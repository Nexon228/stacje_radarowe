#include <gtest/gtest.h>
#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QApplication>

/**
 * @brief Test case for parsing stations JSON data.
 */
TEST(MainWindowTest, ParseStationsJson) {
    // Mock JSON data for stations
    QString jsonData = R"([
        {"id": 1, "stationName": "Test Station", "city": {"name": "Poznań"}},
        {"id": 2, "stationName": "Other Station", "city": {"name": "Warszawa"}}
    ])";
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonArray stacje = doc.array();

    // Simulate filtering for Poznań
    QString miasto = "Poznań";
    QVector<QPair<int, QString>> result;
    for (const QJsonValue &val : stacje) {
        QJsonObject ob = val.toObject();
        if (ob.contains("city") && ob["city"].isObject()) {
            QString cityName = ob["city"].toObject()["name"].toString();
            if (cityName == miasto) {
                result.append({ob["id"].toInt(), ob["stationName"].toString()});
            }
        }
    }

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].first, 1);
    EXPECT_EQ(result[0].second, "Test Station");
}

/**
 * @brief Test case for calculating statistics from measurement data.
 */
TEST(MainWindowTest, CalculateStatistics) {
    QVector<QPair<QDateTime, double>> data = {
        {QDateTime::fromString("2025-04-26T10:00:00", Qt::ISODate), 10.0},
        {QDateTime::fromString("2025-04-26T11:00:00", Qt::ISODate), 15.0},
        {QDateTime::fromString("2025-04-26T12:00:00", Qt::ISODate), 5.0}
    };

    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    double sum = 0.0;
    int count = 0;

    for (const auto &entry : data) {
        double value = entry.second;
        if (value < minValue) minValue = value;
        if (value > maxValue) maxValue = value;
        sum += value;
        count++;
    }

    double average = sum / count;
    EXPECT_EQ(minValue, 5.0);
    EXPECT_EQ(maxValue, 15.0);
    EXPECT_DOUBLE_EQ(average, 10.0);
}

/**
 * @brief Test case for trend calculation.
 */
TEST(MainWindowTest, CalculateTrend) {
    MainWindow window;
    QVector<QPair<QDateTime, double>> data = {
        {QDateTime::fromString("2025-04-26T10:00:00", Qt::ISODate), 5.0},
        {QDateTime::fromString("2025-04-26T11:00:00", Qt::ISODate), 10.0},
        {QDateTime::fromString("2025-04-26T12:00:00", Qt::ISODate), 15.0}
    };

    QString trend = window.calculateTrend(data);
    EXPECT_EQ(trend, "Rosnący");

    data = {
        {QDateTime::fromString("2025-04-26T10:00:00", Qt::ISODate), 15.0},
        {QDateTime::fromString("2025-04-26T11:00:00", Qt::ISODate), 10.0},
        {QDateTime::fromString("2025-04-26T12:00:00", Qt::ISODate), 5.0}
    };
    trend = window.calculateTrend(data);
    EXPECT_EQ(trend, "Malejący");

    data = {
        {QDateTime::fromString("2025-04-26T10:00:00", Qt::ISODate), 10.0},
        {QDateTime::fromString("2025-04-26T11:00:00", Qt::ISODate), 10.1},
        {QDateTime::fromString("2025-04-26T12:00:00", Qt::ISODate), 10.0}
    };
    trend = window.calculateTrend(data);
    EXPECT_EQ(trend, "Stabilny");
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);  // Required for Qt-based tests
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}