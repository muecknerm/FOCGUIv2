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

    addVariables();
    addParameters();

    /* setup content */
    port = new serial_thread();

    QList<data_type_variable> variable_list_1, variable_list_2;
    QList<data_type_variable> plot_list_1, plot_list_2, plot_list_3, plot_list_4;
    QList<data_type_variable> paramter_list_1, parameter_list_2;

    variable_list_1.append(variable_list.at(17));
    variable_list_1.append(variable_list.at(18));
    variable_list_1.append(variable_list.at(19));

    for (quint8 i = 1; i < 20; i++)
    {
        variable_list_2.append(variable_list.at(i));
    }

    plot_list_1.append(variable_list.at(1));
    plot_list_2.append(variable_list.at(17));
    plot_list_3.append(variable_list.at(13));
    plot_list_4.append(variable_list.at(10));

    for (quint8 i = 0; i < 10; i++)
    {
        paramter_list_1.append(parameter_list.at(i));
    }

    tabbar_var.append(new tabbar_class(this, "System"));
    tabbar_var.append(new tabbar_class(this, "Phasecurrent"));
    tabbar_var.append(new tabbar_class(this, "Speed"));

    for (int i = 0; i < tabbar_var.length(); i++)
    {
        tabbar_class *temp = tabbar_var.at(i);
        tabbar1->addTab(temp->tab_widget, temp->getTabbarName());
    }

    /* add to mdi window 1 - System */
    tabbar_class *temp;
    temp = tabbar_var.at(0);
    temp->addVariableWindow(variable_list_1);
    temp->addVariableWindow(variable_list_2);

    temp->addParameterWindow(paramter_list_1, port);

    temp->addPlotWindow(plot_list_1);
    temp->addPlotWindow(plot_list_2);
    temp->addPlotWindow(plot_list_3);
    temp->addPlotWindow(plot_list_4);


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
    //add_variable_dialog *new_dialog = new add_variable_dialog(this, variable_list);
}

void MainWindow::addVariables()
{
    for (quint16 i = 0; i < 25; i++)
    {
        variable_list.append({i,"", 0.0, "", "", 0.0, 'f', 0,0,0}); //, "", 0
    }

    variable_list[0]  = {1,"Counter",             0.0, "[]",       "uint8_t",  1.0,       'f', 0,   0,      255};
    variable_list[1]  = {1,"s16AngleRot",         0.0, "[°]",      "int16_t",  1000.0,    'f', 2,   0,      7};
    variable_list[2]  = {2,"s16SpeedMech",        0.0, "[rpm]",    "uint16_t", 1.0,       'f', 2,   -8000,  8000};
    variable_list[3]  = {3,"s16DucyPwmL1Invt",    0.0, "[%]",      "uint16_t", 1.0,       'f', 2,   0,      100};
    variable_list[4]  = {4,"s16DucyPwmL2Invt",    0.0, "[%]",      "uint16_t", 1.0,       'f', 2,   0,      100};
    variable_list[5]  = {5,"s16SpeedRef",         0.0, "[rpm]",    "uint16_t", 1.0,       'f', 2,   0,      100};
    variable_list[6]  = {6,"u16VoltDCLinkRaw",    0.0, "[]",       "uint16_t", 1.0,       'f', 0,   0 ,     65000};
    variable_list[7]  = {7,"s16CurPhaseU",        0.0, "[A]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[8]  = {8,"s16CurPhaseV",        0.0, "[A]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[9]  = {9,"s16CurPhaseW",        0.0, "[A]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[10] = {10,"s16VoltPhaseU",      0.0, "[V]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[11] = {11,"s16VoltPhaseV",      0.0, "[V]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[12] = {12,"s16VoltPhaseW",      0.0, "[V]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[13] = {13,"s16CurDx",           0.0, "[A]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[14] = {14,"s16CurQx",           0.0, "[A]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[15] = {15,"s16VoltDx",          0.0, "[V]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[16] = {16,"s16VoltQx",          0.0, "[V]",      "uint16_t", 1000.0,    'f', 2,   -20,    20};
    variable_list[17] = {17,"u16CurPhaseURaw",    0.0, "[]",       "uint16_t", 1.0,       'f', 0,   0,      65000};
    variable_list[18] = {18,"u16CurPhaseVRaw",    0.0, "[]",       "uint16_t", 1.0,       'f', 0,   0,      65000};
    variable_list[19] = {19,"u16CurPhaseWRaw",    0.0, "[]",       "uint16_t", 1.0,       'f', 0,   0,      65000};
}

void MainWindow::addParameters()
{
    for (quint16 i = 0; i < 11; i++)
    {
        parameter_list.append({i,"", 0.0, "", "", 0.0, 'f', 0, 0,0}); //, "", 0
    }

    parameter_list[0]  = {0, "cs16SpeedRef_C",         0.0, "[]",       "uint8_t",  1.0, 'f', 2, -8000, 8000};
    parameter_list[1]  = {1, "cu16SpeedCtrlKp_C",      0.0, "[°]",      "int16_t",  1000.0, 'f', 0, 5};
    parameter_list[2]  = {2, "cu16SpeedGradient_C",    0.0, "[rpm]",    "uint16_t", 1.0, 'f', 2, 0, 5};
    parameter_list[3]  = {3, "cu16OfsCurPhaseL1_C",    0.0, "[%]",      "uint16_t", 1.0, 'f', 2, 0, 65000};
    parameter_list[4]  = {4, "cu16OfsCurPhaseL2_C",    0.0, "[%]",      "uint16_t", 1.0, 'f', 2, 0, 65000};
    parameter_list[5]  = {5, "cu16OfsCurPhaseL3_C",    0.0, "[rpm]",    "uint16_t", 1.0, 'f', 2, 0, 65000};
    parameter_list[6]  = {6, "cbStateEnaManVoltCtl_C", 0.0, "[]",       "uint16_t", 1.0, 'f', 2, 0, 1};
    parameter_list[7]  = {7, "cf32VoltDxRefMan_C",     0.0, "[V]",      "uint16_t", 1000.0, 'f', 2, -20, 20};
    parameter_list[8]  = {8, "cf32VoltQxRefMan_C",     0.0, "[V]",      "uint16_t", 1000.0, 'f', 2, -20, 20 };
    parameter_list[9]  = {9, "cf32AngleOffset_C",      0.0, "[°]",      "uint16_t", 100.0, 'f', 2, 0, 360};
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
        //variable_list->append( in.readLine());
    }

    file_data.close();
}

void MainWindow::readData()
{
    result_readData = port->getReadData();

    for (qint16 i = 0; i < result_readData.length(); i++)
    {
        variable_list[i].variable_value =  result_readData[i] / variable_list[i].variable_scaling_factor;
    }

    for (quint8 i = 0; i < tabbar_var.length(); i++)
    {
        tabbar_class *temp = tabbar_var.at(i);
        temp->setVariableValue(variable_list);
    }

    /* set progress bar */
    progressbar->setValue(result_readData.at(0));
}

void MainWindow::writeData(quint16 id, quint16 value)
{
    port->setWriteData(id, value);
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

    setWindowTitle(tr("FOC Interface"));

    setCentralWidget(widget_mainwindow);

    setMinimumSize(160, 160);
    resize(1400, 800);
}
