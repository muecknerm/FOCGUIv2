#include "dialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <Qlist.h>


Dialog::Dialog(QWidget *parent, QString windowTitle, QList<data_type_variable> vari_list) :
    QDialog(parent)
{
    this->setWindowTitle(windowTitle);

    QGridLayout *layout_1 = new QGridLayout();

    for (int i = 0; i < vari_list.length(); ++i)
    {
        labels_name << new QLabel(this);
        labels_value << new QLabel(this);
        labels_unit << new QLabel(this);
    }

    for (int i = 0; i < vari_list.length(); ++i)
    {

        data_type_variable foo = vari_list.at(i);

        labels_name.at(i)->setText(foo.variable_name);
        labels_value.at(i)->setText("0.0");
        labels_unit.at(i)->setText(foo.variable_unit);

        labels_name.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        labels_value.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        labels_unit.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        labels_name.at(i)->setAlignment(Qt::AlignLeft);
        labels_value.at(i)->setAlignment(Qt::AlignRight);
        labels_unit.at(i)->setAlignment(Qt::AlignLeft);

        layout_1->setSpacing(0);
        layout_1->setSpacing(0);
        layout_1->setContentsMargins(0,0,0,0);
    }

    for (int i = 0; i < vari_list.length(); ++i)
    {
        layout_1->addWidget(labels_name.at(i),i,0);
        layout_1->addWidget(labels_value.at(i),i,1);
        layout_1->addWidget(labels_unit.at(i),i,2);
    }

    setLayout(layout_1);

    setMinimumHeight(25 * vari_list.length());

    setMinimumWidth(400);

    resize(400,100);
}

Dialog::setValue(QList<data_type_variable> vari_list_main)
{
    labels_value.at(0)->setText(QString::number(vari_list_main[1].variable_value));
}

Dialog::~Dialog()
{
}
