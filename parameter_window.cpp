#include "parameter_window.h"
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <Qlist.h>
#include <QSpinBox>

Parameter_window::Parameter_window(QWidget *parent, QString windowTitle, QStringList *variable_list) :
    QDialog(parent)
{
    this->setWindowTitle(windowTitle);

    QGridLayout *layout_1 = new QGridLayout();

    for (int i = 0; i < variable_list->length(); i++)
    {
        labels_name << new QLabel(this);
        spinbox_value << new QSpinBox(this);
        labels_unit << new QLabel(this);
    }
    for (int i = 0; i < variable_list->length(); i++)
    {
        labels_name.at(i)->setText("f32CurrPhaseL1");
        //spinbox_value.at(i)->setText("0.0");
        labels_unit.at(i)->setText("[rpm]");

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
    for (int i = 0; i < variable_list->length(); i++)
    {
        layout_1->addWidget(labels_name.at(i),i,0);
        layout_1->addWidget(spinbox_value.at(i),i,1);
        layout_1->addWidget(labels_unit.at(i),i,2);
    }

    setLayout(layout_1);

    //setMinimumSize(500, 50);

    setMinimumHeight(25 * variable_list->length());

    setMinimumWidth(400);

    resize(400,100);

    this->show();
}


Parameter_window::~Parameter_window()
{
}
