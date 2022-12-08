#ifndef DIALOG_H
#define DIALOG_H


#include "global.h"

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QList>
#include <QLabel>


class Dialog : public QDialog
{
    Q_OBJECT

private:
    QList<QLabel *> labels_name;
    QList<QLabel *> labels_value;
    QList<QLabel *> labels_unit;

public:
    Dialog(QWidget *parent = nullptr, QString windowTitle = "Hallo", QList<data_type_variable> vari_list = {});
    ~Dialog();
    setValue(int16_t value);
};
#endif // DIALOG_H
