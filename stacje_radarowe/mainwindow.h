#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "apiworker.h"

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
 * @brief The main window of the air quality monitoring application.
 *
 * This class handles the GUI, API requests, data processing, and chart display
 * for monitoring air quality data from the GIOŚ API. It supports online and offline
 * modes, displays data on a chart, and performs simple statistical analysis.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow.
     * @param parent The parent widget (default is nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private:
    /**
     * @brief Calculates the trend of the measurement data.
     * @param data Vector of pairs containing timestamp and measurement value.
     * @return QString describing the trend ("Rosnący", "Malejący", or "Stabilny").
     */
    QString calculateTrend(const QVector<QPair<QDateTime, double>> &data);

private:
    Ui::MainWindow *ui;       ///< Pointer to the UI object.
    QChartView *chartView;    ///< Chart view for displaying measurement data.
    ApiWorker *apiWorker;     ///< Worker for handling API requests in a separate thread.
    QThread *apiThread;       ///< Thread for running API requests.
};

#endif // MAINWINDOW_H
