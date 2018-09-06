#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void openStringEditor();
    void openGraphicEditor();
    void openAutomatonEditor();
};

#endif // WIDGET_H
