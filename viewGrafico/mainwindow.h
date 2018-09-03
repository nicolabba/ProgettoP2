#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <grafico.h>
#include <qcustomplot.h>
#include <QtCharts/QChartView>
namespace Ui{
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* = 0);
    ~MainWindow();

private slots:
   void qtbaddClick();
   void qpointClick(QPointF);
   void customMenuRequested(QPoint);

private:
    Ui::MainWindow *ui;
    Grafico *g;
    QtCharts::QChartView *chart;
    QLineEdit *lineX;
    QLineEdit *lineY;
    QTableView *viewData;
    QTableView *viewPoints;

    void refresh();
    void refreshTable();
    void resizeEvent(QResizeEvent* = 0);
};

#endif // MAINWINDOW_H
