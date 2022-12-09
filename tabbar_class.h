#ifndef TABBAR_CLASS_H
#define TABBAR_CLASS_H

#include "dialog.h"
#include "add_plot_dialoag.h"
#include "parameter_window.h"
#include "global.h"

#include <QList>
#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QString>
#include <QWidget>
#include <QList>


class tabbar_class : public QWidget
{
        Q_OBJECT
private:
    QString tabbar_name_local;
    QList<QMdiSubWindow *> mdi_subwindow_1;
    QList<Dialog *> dialog_1;
    QList<Parameter_window *> parameter_window_1;
    QList<add_plot_dialoag *> plot_dialoag_1;


public:
    tabbar_class(QWidget *parent, QString tabbar_name);
    ~tabbar_class();

    QWidget *tab_widget;
    QMdiArea *mdi_area;
    QGridLayout *tab_widget_layout;

    void addPlotWindow(QString variable_name);
    void addVariableWindow(QList<data_type_variable> vari_list);
    void addParameterWindow(QStringList *variable_list);
    void setVariableValue(QList<data_type_variable> vari_list_main);
    QString getTabbarName();
};

#endif // TABBAR_CLASS_H


