#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

struct data_type_variable
{
    qint8 id;
    QString variable_name;
    float variable_value;
    QString variable_unit;
    QString variable_type;
    float variable_scaling_factor;
    char format_typ;
    quint8 format_length;
    float min_value;
    float max_value;
};


#endif // DIALOG_H
