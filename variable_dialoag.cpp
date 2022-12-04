#include "variable_dialoag.h"
#include "ui_variable_dialoag.h"

variable_dialoag::variable_dialoag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::variable_dialoag)
{
    ui->setupUi(this);
}

variable_dialoag::~variable_dialoag()
{
    delete ui;
}
