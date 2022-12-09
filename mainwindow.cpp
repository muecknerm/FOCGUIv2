#include "mainwindow.h"
#include "dialog.h"
#include "parameter_window.h"
#include "add_variable_dialog.h"
#include "serial_thread.h"
#include "tabbar_class.h"


#include <qboxlayout.h>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>
#include <QMdiSubWindow>
#include <QComboBox>
#include <QProgressBar>
#include <Qlabel.h>
#include <QRadioButton>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupMainwindow();
    createActions();
    createMenus();

    /* setup content */
    QStringList *new_list = new QStringList();

    port = new serial_thread();

    variable_list = new QStringList();

    QList<data_type_variable> vari_list_1, vari_list_2;

    addVariables();

    vari_list_1.append(vari_list_main.at(0));
    vari_list_1.append(vari_list_main.at(3));

    vari_list_2.append(vari_list_main.at(0));
    vari_list_2.append(vari_list_main.at(1));
    vari_list_2.append(vari_list_main.at(4));
    vari_list_2.append(vari_list_main.at(5));


    tabbar_var.append(new tabbar_class(this, "System"));
    tabbar_var.append(new tabbar_class(this, "Phasecurrent"));
    tabbar_var.append(new tabbar_class(this, "Speed"));

    for (int i = 0; i < tabbar_var.length(); i++)
    {
        tabbar_class *temp = tabbar_var.at(i);
        tabbar1->addTab(temp->tab_widget, temp->getTabbarName());
    }

    tabbar_class *temp;

    /* add to mdi window 1 - System */
    temp = tabbar_var.at(0);
    temp->addVariableWindow(vari_list_1);
    temp->addVariableWindow(vari_list_2);

    tabbar1->setTabPosition(QTabWidget::South);

    ui_connected = false;

    port->open_serial();

    connect(button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
    connect(port, SIGNAL(dataReadyRead()), this, SLOT(readData()) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(this);
    subMenu_file = menuBar()->addMenu("&File");
    subMenu_edit = menuBar()->addMenu("&Edit");
    subMenu_view = menuBar()->addMenu("&View");
    subMenu_variables = menuBar()->addMenu("&Variables");
    subMenu_options = menuBar()->addMenu("&Options");
    subMenu_measurement = menuBar()->addMenu("&Measurement");
    subMenu_dataset = menuBar()->addMenu("&Dataset");
    subMenu_about = menuBar()->addMenu("&About");

    /* Submenu File */
    subMenu_file->addAction(action_load_a2l);
    subMenu_file->addSeparator();
    subMenu_file->addAction(action_save_experiment);
    subMenu_file->addAction(action_load_experiment);
    subMenu_file->addSeparator();
    subMenu_file->addAction(action_close_application);

    subMenu_variables->addAction(action_add_variable);
    subMenu_variables->addAction(action_add_parameter);
}

void MainWindow::createActions()
{
    action_add_variable = new QAction("&Add Variable", this);
    action_add_parameter = new QAction("&Add Parameter", this);
    action_load_a2l =  new QAction("&Load A2L File", this);
    action_save_experiment = new QAction("&Save Experiment", this);
    action_load_experiment = new QAction("&Load Experiement", this);

    action_close_application = new QAction("&Exit", this);

    connect(action_add_variable, &QAction::triggered, this, &MainWindow::addVariable);
    connect(action_load_a2l, &QAction::triggered, this, &MainWindow::load_a2l);
}

void MainWindow::addVariable()
{
    add_variable_dialog *new_dialog = new add_variable_dialog(this, variable_list);
}

void MainWindow::addVariables()
{
    for (quint16 i = 0; i < 25; i++)
    {
        vari_list_main.append({"", 0.0, "", "", 0.0});
    }

    vari_list_main[0] = {"s16AngleRot",         0.0, "[°]", "int16_t", 1000.0};
    vari_list_main[1] = {"s16SpeedMech",        0.0, "[rpm]", "uint16_t", 1.0};
    vari_list_main[2] = {"s16DucyPwmL1Invt",    0.0, "[]", "uint16_t", 1.0};
    vari_list_main[3] = {"s16DucyPwmL2Invt",    0.0, "[]", "uint16_t", 1.0};
    vari_list_main[4] = {"s16DucyPwmL2Invt",    0.0, "[]", "uint16_t", 1.0};
    vari_list_main[5] = {"s16SpeedRef",         0.0, "[rpm]", "uint16_t", 1.0};
}

void MainWindow::load_a2l()
{

    QString file_name = QFileDialog::getOpenFileName(this, "Load A2L", "C://");
    QFile file_data(file_name);

    if(!file_data.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file_data.errorString());
    }

    QTextStream in(&file_data);


    while(!in.atEnd()) {
        variable_list->append( in.readLine());
    }

    file_data.close();
}

void MainWindow::add_subwindow()
{
}


void MainWindow::readData()
{
    result_readData = port->getReadData();

    for (qint16 i = 0; i < result_readData.length(); i++)
    {
        vari_list_main[i].variable_value =  result_readData[i];
    }

    for (quint8 i = 0; i < tabbar_var.length(); i++)
    {
        tabbar_class *temp = tabbar_var.at(i);
        temp->setVariableValue(vari_list_main);
    }

    /* set progress bar */
    progressbar->setValue(result_readData.at(0));
}

void MainWindow::on_button1_clicked()
{
    if (ui_connected == false)
    {
        port->open_serial();
        qDebug() << "COM Port successfully open";
        ui_connected = true;
        MainWindow::button1->setText("Disconnect");
    }
    else
    {
        port->close_serial();
        MainWindow::button1->setText("Connect");
        ui_connected = false;
    }
}

void MainWindow::setReadData(quint16 readDataID, quint16 readDataValue)
{

    //vari_list_main

}

void MainWindow::setupMainwindow()
{
    /* setup main ui */
    progressbar = new QProgressBar();
    comboBox = new QComboBox();
    radioButton_wp = new QRadioButton();
    radioButton_rp = new QRadioButton();
    button2 = new QPushButton();
    button1 = new QPushButton();

    /* setup main window layout */
    widget_mainwindow = new QWidget;
    widget_mainwindow_bottom = new QWidget;
    widget_mainwindow_top = new QWidget;
    widget_mainwindow_left = new QWidget;

    layout_mainwindow = new QGridLayout;
    layout_mainwindow_bottom_widget  = new QGridLayout;
    layout_mainwindow_top_widget = new QGridLayout ;
    layout_mainwindow_left_widget = new QGridLayout ;

    label_2 = new QLabel;
    label_wp = new QLabel;
    label_rp = new QLabel;

    line_1 = new QFrame();
    line_1->setFrameShape(QFrame::VLine);
    line_1->setFrameShadow(QFrame::Sunken);

    line_2 = new QFrame();
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);

    tabbar1 = new QTabWidget();

    setWindowTitle(tr("FOC Interface"));

    comboBox->addItem("COM9");
    comboBox->addItem("COM8");

    button1->setMaximumWidth(130);
    button1->setMinimumWidth(130);

    button2->setMaximumWidth(70);
    button2->setMinimumWidth(70);

    label_2->setText("Diff: 221");
    button1->setText("Connect");
    button2->setText("Reset");
    label_rp->setText("RP");
    label_wp->setText("WP");

    label_2->setMaximumWidth(100);
    label_2->setMinimumWidth(100);

    label_2->setFrameStyle(QFrame::Panel);
    label_2->setAlignment(Qt::AlignCenter);

    button1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    comboBox->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    comboBox->setMaximumWidth(150);
    comboBox->setMinimumWidth(150);

    progressbar->setMaximumWidth(70);
    progressbar->setTextVisible(false);
    progressbar->setMaximumHeight(20);

    /* Setup main window layout */
    layout_mainwindow->setSpacing(0);
    layout_mainwindow->setSpacing(0);
    layout_mainwindow->setContentsMargins(0,0,0,0);

    layout_mainwindow_bottom_widget->setSpacing(0);
    layout_mainwindow_bottom_widget->setSpacing(0);
    layout_mainwindow_bottom_widget->setContentsMargins(0,0,3,3);

    layout_mainwindow_top_widget->addWidget(button1, 0, 0, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(comboBox, 0, 1, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(button2, 0, 2, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(line_1, 0,3, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(radioButton_rp, 0, 4, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(label_rp, 0, 5, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(radioButton_wp, 0, 6, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(label_wp, 0, 7, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(line_2, 0,8, Qt::AlignLeft);
    layout_mainwindow_top_widget->addWidget(label_2, 0, 9, Qt::AlignLeft);
    layout_mainwindow_top_widget->setColumnStretch(9,9);

    layout_mainwindow_bottom_widget->addWidget(progressbar, 0, 0, Qt::AlignRight);

    /* add all widgets to main layout */
    layout_mainwindow->addWidget(widget_mainwindow_top, 0, 0, 1, 2);
    layout_mainwindow->addWidget(widget_mainwindow_left, 1, 0, 2, 1);
    layout_mainwindow->addWidget(widget_mainwindow_bottom, 2, 1 ,1 ,2);
    layout_mainwindow->addWidget(tabbar1, 1, 1, 1, 1);

    /* add layout to widgets */
    widget_mainwindow->setLayout(layout_mainwindow);
    widget_mainwindow_bottom->setLayout(layout_mainwindow_bottom_widget);
    widget_mainwindow_top->setLayout(layout_mainwindow_top_widget);
    widget_mainwindow_left->setLayout(layout_mainwindow_left_widget);

    widget_mainwindow_left->setMinimumWidth(40);

    setCentralWidget(widget_mainwindow);

    setMinimumSize(160, 160);
    resize(1400, 800);
}
