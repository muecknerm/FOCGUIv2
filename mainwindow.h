#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "add_plot_dialoag.h"
#include "tabbar_class.h"
#include "global.h"

#include <QMainWindow>
#include <QMenu>
#include <qmdiarea.h>
#include <QPushButton>
#include <QAction>
#include "serial_thread.h"
#include <QStringList>
#include <QList>
#include <QFrame>


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void createMenus();
    void createActions();
    void addVariable();
    void addVariables();
    void addParameters();
    void load_a2l();
    void setupMainwindow();

    /* Menu entries */
    QMenu *fileMenu;
    QMenu *subMenu_file;
    QMenu *subMenu_edit;
    QMenu *subMenu_view;
    QMenu *subMenu_variables;
    QMenu *subMenu_options;
    QMenu *subMenu_measurement;
    QMenu *subMenu_dataset;
    QMenu *subMenu_about;

    /* Menu actions */
    QAction *action_add_variable;
    QAction *action_add_parameter;
    QAction *action_load_a2l;
    QAction *action_load_experiment;
    QAction *action_save_experiment ;
    QAction *action_close_application;
    QPushButton *button2;
    QProgressBar *progressbar;
    QComboBox *comboBox;
    QRadioButton *radioButton_wp;
    QRadioButton *radioButton_rp;
    QWidget *widget_mainwindow;
    QWidget *widget_mainwindow_bottom;
    QWidget *widget_mainwindow_top;
    QWidget *widget_mainwindow_left;
    QLabel *label_2;
    QLabel *label_wp;
    QLabel *label_rp;
    QTabWidget *tabbar1;


    QFrame *line_1;
    QFrame *line_2;


    /* Layout */
    QGridLayout *layout_mainwindow;
    QGridLayout *layout_mainwindow_bottom_widget;
    QGridLayout *layout_mainwindow_top_widget;
    QGridLayout *layout_mainwindow_left_widget;

    QStringList *variable_list;

    QList <tabbar_class *> tabbar_var;

    /* configure application */
    bool ui_connected;
    serial_thread *port;
    QVector<int16_t> result_readData;

    QList<data_type_variable> vari_list_main;
    QList<data_type_variable> parameter_list_main;

private slots:
    void on_button1_clicked();

public slots:
    void readData();
    void writeData():

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_subwindow();
    void setReadData(quint16 readDataID, quint16 readDataValue);

    QPushButton *button1;
};
#endif // MAINWINDOW_H
