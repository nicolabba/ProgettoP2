#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H
#include <QWidget>
#include <QPushButton>


class myCheckBox : public QWidget
{
    Q_OBJECT
private:
    bool active;
    QPushButton* button;
public:
    explicit myCheckBox(QWidget *parent = nullptr);
    bool isChecked() const;
signals:
    void stateChanged(bool act);
private slots:
    void pressed();
public slots:
    void setChecked(bool act);
};

#endif // MYCHECKBOX_H
