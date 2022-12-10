#include "parameter_window.h"
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <Qlist.h>
#include <QSpinBox>

Parameter_window::Parameter_window(QWidget *parent, QString windowTitle, QList<data_type_variable> parameter_list) :
    QDialog(parent)
{
    this->setWindowTitle(windowTitle);

    QGridLayout *layout_1 = new QGridLayout();

    for (int i = 0; i < parameter_list.length(); i++)
    {
        labels_name << new QLabel(this);
        spinbox_value << new QSpinBox(this);
        labels_unit << new QLabel(this);
        labels_id.append(0);
    }
    for (int i = 0; i < parameter_list.length(); i++)
    {
        data_type_variable foo = parameter_list.at(i);

        labels_name.at(i)->setText(foo.variable_name);
        //spinbox_value.at(i)->setText("0.0");
        labels_unit.at(i)->setText(foo.variable_unit);
        labels_id[i] = foo.id;

        labels_name.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        //spinbox_value.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        labels_unit.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        labels_name.at(i)->setAlignment(Qt::AlignLeft);
        spinbox_value.at(i)->setAlignment(Qt::AlignRight);
        labels_unit.at(i)->setAlignment(Qt::AlignLeft);

        layout_1->setSpacing(0);
        layout_1->setSpacing(0);
        layout_1->setContentsMargins(0,0,0,0);
    }
    for (int i = 0; i < parameter_list.length(); i++)
    {
        layout_1->addWidget(labels_name.at(i),i,0);
        layout_1->addWidget(spinbox_value.at(i),i,1);
        layout_1->addWidget(labels_unit.at(i),i,2);
    }

    setLayout(layout_1);

    //setMinimumSize(500, 50);

    setMinimumHeight(25 * parameter_list.length());

    setMinimumWidth(400);

    resize(400,100);

    this->show();
}


Parameter_window::~Parameter_window()
{
}
