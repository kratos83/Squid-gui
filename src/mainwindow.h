#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "about.h"
#include "squid_config.h"
#include "dansguardian_config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //View exit message
    void closeEvent(QCloseEvent *e);

private slots:
    //Squid
    void view_vis_squid();
    void lista_squid();
    void view_signal_squid();
    //Parameter squid
    void view_squid();
    void view_parameter_squid();
    void write_parameter_squid();
    //Parameter mime squid
    void view_parameter_mime_squid();
    void write_parameter_mime_squid();
    //Parameter cache squid
    void view_parameter_cache_squid();
    void write_parameter_cache_squid();
    //Parameter msntauth
    void view_parameter_msnt_squid();
    void write_parameter_msnt_squid();
    //Backup and restore squid
    void backup_squid();
    void restore_squid();
    //Start, stop and restart squid
    void start_squid();
    void stop_squid();
    void restart_squid();
    void status_squid();
    //View stack squid
    void view_stack_squid();
    //View main
    void view_main_stack();
    //Add row and remove row
    void add_row_squid();
    void delete_row_squid();
    void add_row_squid_mime();
    void delete_row_squid_mime();
    void add_row_squid_cache();
    void delete_row_squid_cache();
    void add_row_squid_msnt();
    void delete_row_squid_msnt();
    //DansGuardian
    void view_vis_dans();
    void view_list_dans();
    void view_signal_dans();
    //Parameter dansguardian
    void view_dans();
    void view_parameter_dans();
    void write_parameter_dans();
    //Backup and restore squid
    void backup_dans();
    void restore_dans();
    //Start, stop and restart squid
    void start_dans();
    void stop_dans();
    void restart_dans();
    void status_dans();
    //Add row and remove row
    void add_row_dans();
    void delete_row_dans();
    //View stack dansguardian
    void view_stack_dans();
    //Info application
    void information();
    //Donate
    void donate();
    //View exit
    void esci();
private:
    Ui::MainWindow *ui;
    QStandardItemModel *model,*model1,*model2,*model3;//Model squid
    QStandardItemModel *m_dans_c;
};

#endif // MAINWINDOW_H
