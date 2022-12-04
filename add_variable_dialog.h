#ifndef ADD_VARIABLE_DIALOG_H
#define ADD_VARIABLE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QStringList>
#include "mainwindow.h"

class add_variable_dialog: public QDialog
{
        Q_OBJECT

private:
     QListWidget *list_variables;
     QStringList *variable_liste;


    void button_ok_fct();
    void button_cancel_fct();
public:
    add_variable_dialog(QWidget *parent = nullptr, QStringList *variable_list = nullptr);
    ~add_variable_dialog();
};

#endif // ADD_VARIABLE_DIALOG_H
