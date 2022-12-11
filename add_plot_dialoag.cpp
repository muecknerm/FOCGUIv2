#include "add_plot_dialoag.h"
#include <QVector>
#include <QDebug>

add_plot_dialoag::add_plot_dialoag(QWidget *parent, QString windowTitle, QList<data_type_variable> variable_list) :
    QDialog(parent)
{
    this->setWindowTitle("XY-Plot Window");

    QGridLayout *main_layout = new QGridLayout();
    customPlot = new QCustomPlot();

    QVector<double> x(10), y(10); // initialize with entries 0..100

    for (int i = 0; i< 10; i++)
    {
        x[i]=i;
        y[i]=1;
    }

    for (int i = 0; i < variable_list.length(); ++i)
    {
        labels_name << new QLabel(this);
        labels_value << new QLabel(this);
        labels_unit << new QLabel(this);
        labels_id.append(0);
    }

    for (int i = 0; i < variable_list.length(); ++i)
    {
        data_type_variable foo = variable_list.at(i);

        labels_name.at(i)->setText(foo.variable_name);
        labels_value.at(i)->setText("0.0");
        labels_unit.at(i)->setText(foo.variable_unit);
        labels_id[i] = foo.id;

        // create graph and assign data to it:
        customPlot->addGraph();
        customPlot->graph(i)->setData(x, y);
        customPlot->xAxis->setLabel("Time [s]");
        customPlot->yAxis->setLabel(foo.variable_name + " " + foo.variable_unit);
        customPlot->yAxis->setRange(foo.min_value, foo.max_value);
    }

    /* set layout */
    main_layout->setSpacing(0);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(customPlot, 0, 0);

    setMinimumHeight(200);
    setMinimumWidth(400);

    setLayout(main_layout);

    this->show();
}

void add_plot_dialoag::setValue(QList<data_type_variable> variable_list)
{
    static double key = 0;

    customPlot->graph(0)->addData(key, variable_list[labels_id[0]].variable_value);
    customPlot->xAxis->setRange(key, 1, Qt::AlignRight);
    customPlot->replot();

    key = key + 0.01;
}

add_plot_dialoag::~add_plot_dialoag()
{
}
