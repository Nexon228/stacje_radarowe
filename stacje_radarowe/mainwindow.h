#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Najpierw właściwe includowanie QtCharts
#include <QtCharts>

// Następnie używamy namespace
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
// Używamy namespace QtCharts po zdefiniowaniu Ui namespace
namespace QtCharts {
class QChartView;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QChartView *chartView;
};

#endif // MAINWINDOW_H
