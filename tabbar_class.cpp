#include "tabbar_class.h"
#include "dialog.h"

tabbar_class::tabbar_class(QWidget *parent, QString tabbar_name="noname"):
    QWidget(parent)
{
    tab_widget = new QWidget();
    mdi_area = new QMdiArea();
    tab_widget_layout = new QGridLayout();

    tab_widget_layout->setSpacing(0);
    tab_widget_layout->setSpacing(0);
    tab_widget_layout->setContentsMargins(0,0,0,0);

    tabbar_name_local = tabbar_name;

    tab_widget_layout->addWidget(mdi_area);

    tab_widget->setLayout(tab_widget_layout);

    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}


QString tabbar_class::getTabbarName()
{
    return tabbar_name_local;
}

void tabbar_class::addPlotWindow(QString variable_name)
{
    plot_dialoag_1.append(new add_plot_dialoag(this, "Plot Window", variable_name));

    mdi_area->addSubWindow(plot_dialoag_1.at(0));
}

void tabbar_class::addVariableWindow(QList<data_type_variable> vari_list)
{
    dialog_1.append(new Dialog(this, "Measurement Window", vari_list));

    mdi_area->addSubWindow(dialog_1.at(dialog_1.length()-1));
}

void tabbar_class::addParameterWindow(QStringList *variable_list)
{
    parameter_window_1.append(new Parameter_window(this, "Parameter Window", variable_list));

    mdi_area->addSubWindow(parameter_window_1.at(0));
}

void tabbar_class::setVariableValue(QList<data_type_variable> vari_list_main)
{
    for (quint8 i = 0; i < dialog_1.length(); i++ )
    {
        Dialog *foo = dialog_1.at(i);
        foo->setValue(vari_list_main);
    }
}

tabbar_class::~tabbar_class()
{
}

