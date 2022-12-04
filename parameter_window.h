#ifndef PARAMETER_WINDOW_H
#define PARAMETER_WINDOW_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QSpinBox>

class Parameter_window : public QDialog
{
    Q_OBJECT

private:
    QList<QLabel *> labels_name;
    QList<QSpinBox *> spinbox_value;
    QList<QLabel *> labels_unit;

public:
    Parameter_window(QWidget *parent = nullptr, QString windowTitle = "Parameter Window", QStringList *variable_list = nullptr);
    ~Parameter_window();
};
#endif // PARAMETER_WINDOW_H
