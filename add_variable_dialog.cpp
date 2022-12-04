#include "add_variable_dialog.h"
#include <QDebug>

add_variable_dialog::add_variable_dialog(QWidget *parent, QStringList *variable_list) :
    QDialog(parent)
{
    this->setWindowTitle("Add Variable");
    resize(400,400);

    QGridLayout *main_layout = new QGridLayout();
    QPushButton *button_ok = new QPushButton();
    QPushButton *button_cancel = new QPushButton();

    list_variables = new QListWidget();

    button_ok->setText("Ok");
    button_cancel->setText("Cancel");

    main_layout->addWidget(list_variables, 0, 0);
    main_layout->addWidget(button_ok, 1, 0);
    main_layout->addWidget(button_cancel, 2, 0);

    connect(button_ok, &QPushButton::clicked, this, &add_variable_dialog::button_ok_fct);
    connect(button_cancel, &QPushButton::clicked, this, &add_variable_dialog::button_cancel_fct);

    setLayout(main_layout);

    for (int i = 0; i < variable_list->length() ; i++)
    {
        list_variables->addItem(variable_list->at(i));
    }

    this->show();
}

void add_variable_dialog::button_ok_fct()
{


    qDebug() << list_variables->currentItem();
    this->close();
}

void add_variable_dialog::button_cancel_fct()
{
    this->close();
}

add_variable_dialog::~add_variable_dialog()
{
}


