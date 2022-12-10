#ifndef PARAMETER_WINDOW_H
#define PARAMETER_WINDOW_H

#include "global.h"
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
    QList<qint16>   labels_id;

public:
    Parameter_window(QWidget *parent = nullptr, QString windowTitle = "Parameter Window", QList<data_type_variable> parameter_list = {});
    ~Parameter_window();
};
#endif // PARAMETER_WINDOW_H
