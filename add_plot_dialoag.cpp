#include "add_plot_dialoag.h"


#include <QVector>

add_plot_dialoag::add_plot_dialoag(QWidget *parent, QString windowTitle, QString vairable_name) :
    QDialog(parent)
{
    this->setWindowTitle("XY-Plot Window");

    QGridLayout *main_layout = new QGridLayout();
    QCustomPlot *customPlot = new QCustomPlot();

    QVector<double> x(10), y(10); // initialize with entries 0..100

    for (int i = 0; i< 10; i++)
    {
        x[i]=i;
        y[i]=1;
    }

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("Time [s]");
    customPlot->yAxis->setLabel("Speed [rpm]");

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

add_plot_dialoag::~add_plot_dialoag()
{
}
