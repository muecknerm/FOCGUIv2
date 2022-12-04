#ifndef VARIABLE_DIALOAG_H
#define VARIABLE_DIALOAG_H

#include <QDialog>

namespace Ui {
class variable_dialoag;
}

class variable_dialoag : public QDialog
{
    Q_OBJECT

public:
    explicit variable_dialoag(QWidget *parent = nullptr);
    ~variable_dialoag();

private:
    Ui::variable_dialoag *ui;
};

#endif // VARIABLE_DIALOAG_H
