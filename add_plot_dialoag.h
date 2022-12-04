#ifndef ADD_PLOT_DIALOAG_H
#define ADD_PLOT_DIALOAG_H

#include <QDialog>
#include "add_plot_dialoag.h"
#include "qcustomplot.h"

class add_plot_dialoag: public QDialog
{
    Q_OBJECT
public:
    add_plot_dialoag(QWidget *parent = nullptr, QString windowTitle = "Add Variable", QString vairable_name = "fault");
    ~add_plot_dialoag();
};

#endif // ADD_PLOT_DIALOAG_H
