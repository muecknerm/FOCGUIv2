#include "parameter_window.h"
#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <Qlist.h>
#include <QSpinBox>
#include <QDebug>

Parameter_window::Parameter_window(QWidget *parent, QString windowTitle, QList<data_type_variable> parameter_list, serial_thread *port) :
    QDialog(parent)
{
    this->setWindowTitle(windowTitle);

    port_parameter = port;

    QGridLayout *layout_1 = new QGridLayout();

    for (int i = 0; i < parameter_list.length(); i++)
    {
        labels_name << new QLabel(this);
        spinbox_value << new QSpinBox(this);
        labels_unit << new QLabel(this);
        labels_id.append(0);

        data_type_variable foo = parameter_list.at(i);

        labels_name.at(i)->setText(foo.variable_name);
        //spinbox_value.at(i)->setText("0.0");
        spinbox_value.at(i)->setObjectName(QString::number(foo.id));
        labels_unit.at(i)->setText(foo.variable_unit);
        labels_id[i] = foo.id;
        scaling_factor[i] = foo.variable_scaling_factor;

        labels_name.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        //spinbox_value.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        labels_unit.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        spinbox_value.at(i)->setMinimum(foo.min_value);
        spinbox_value.at(i)->setMaximum(foo.max_value);

        labels_name.at(i)->setAlignment(Qt::AlignLeft);
        spinbox_value.at(i)->setAlignment(Qt::AlignRight);
        labels_unit.at(i)->setAlignment(Qt::AlignLeft);

        connect(spinbox_value[i], &QSpinBox::editingFinished, this, &Parameter_window::on_button1_clicked);

        layout_1->addWidget(labels_name.at(i),i,0);
        layout_1->addWidget(spinbox_value.at(i),i,1);
        layout_1->addWidget(labels_unit.at(i),i,2);

        layout_1->setSpacing(0);
        layout_1->setSpacing(0);
        layout_1->setContentsMargins(0,0,0,0);
    }

    setLayout(layout_1);

    setMinimumHeight(25 * parameter_list.length());

    setMinimumWidth(400);

    resize(400,100);

    this->show();
}

void Parameter_window::on_button1_clicked()
{
    QSpinBox *changedSpinbox = qobject_cast<QSpinBox *>(sender());

    port_parameter->setWriteData(changedSpinbox->objectName().toInt(), changedSpinbox->value());
}

Parameter_window::~Parameter_window()
{
}
