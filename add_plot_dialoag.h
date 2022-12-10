#ifndef ADD_PLOT_DIALOAG_H
#define ADD_PLOT_DIALOAG_H

#include "global.h"
#include <QDialog>
#include "add_plot_dialoag.h"
#include "qcustomplot.h"

class add_plot_dialoag: public QDialog
{
    Q_OBJECT

private:
    QCustomPlot *customPlot;
public:
    void setValue(QList<data_type_variable> variable_list);
    add_plot_dialoag(QWidget *parent = nullptr, QString windowTitle = "Plot Window", QList<data_type_variable> variable_list = {});
    ~add_plot_dialoag();
};

#endif // ADD_PLOT_DIALOAG_H
