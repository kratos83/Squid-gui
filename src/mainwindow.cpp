#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace squid_config;
using namespace dansguardian_config;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Exit to application
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(esci()));
    //Connect info
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(information()));
    //Donate
    connect(ui->actionDonatr,SIGNAL(triggered(bool)),this,SLOT(donate()));
    view_signal_squid();
    view_signal_dans();
    view_vis_dans();
    view_vis_squid();
}

void MainWindow::view_signal_squid()
{
    //Squid parameter
    connect(ui->read_file,SIGNAL(clicked(bool)),this,SLOT(view_parameter_squid()));
    connect(ui->write_file,SIGNAL(clicked(bool)),this,SLOT(write_parameter_squid()));
    //Mime parameter
    connect(ui->read_file_mime,SIGNAL(clicked(bool)),this,SLOT(view_parameter_mime_squid()));
    connect(ui->write_file_mime,SIGNAL(clicked(bool)),this,SLOT(write_parameter_mime_squid()));
    //Cache parameter
    connect(ui->read_file_cache,SIGNAL(clicked(bool)),this,SLOT(view_parameter_cache_squid()));
    connect(ui->write_file_cache,SIGNAL(clicked(bool)),this,SLOT(write_parameter_cache_squid()));
    //Msntauth parameter
    connect(ui->read_file_msnt,SIGNAL(clicked(bool)),this,SLOT(view_parameter_msnt_squid()));
    connect(ui->write_file_msnt,SIGNAL(clicked(bool)),this,SLOT(write_parameter_msnt_squid()));
    //Start, stop and restart server proxy squid
    connect(ui->start_squid,SIGNAL(clicked(bool)),this,SLOT(start_squid()));
    connect(ui->stop_squid,SIGNAL(clicked(bool)),this,SLOT(stop_squid()));
    connect(ui->restart_squid,SIGNAL(clicked(bool)),this,SLOT(restart_squid()));
    connect(ui->status_squid,SIGNAL(clicked(bool)),this,SLOT(status_squid()));
    //View stack squid
    connect(ui->config_squid,SIGNAL(clicked(bool)),this,SLOT(view_stack_squid()));
    //View return main
    connect(ui->return_main,SIGNAL(clicked(bool)),this,SLOT(view_main_stack()));
    //Backup and restore squid
    connect(ui->actionBackup_squid,SIGNAL(triggered(bool)),this,SLOT(backup_squid()));
    connect(ui->actionRestore_backup_squid,SIGNAL(triggered(bool)),this,SLOT(restore_squid()));
    //Add and remove row squid config
    connect(ui->m_row_squid_c,SIGNAL(clicked(bool)),this,SLOT(add_row_squid()));
    connect(ui->m_delete_squid_c,SIGNAL(clicked(bool)),this,SLOT(delete_row_squid()));
    connect(ui->m_row_squid_mime,SIGNAL(clicked(bool)),this,SLOT(add_row_squid_mime()));
    connect(ui->m_delete_squid_mime,SIGNAL(clicked(bool)),this,SLOT(delete_row_squid_mime()));
    connect(ui->m_row_squid_cache,SIGNAL(clicked(bool)),this,SLOT(add_row_squid_cache()));
    connect(ui->m_delete_squid_cache,SIGNAL(clicked(bool)),this,SLOT(delete_row_squid_cache()));
    connect(ui->m_row_squid_msnt,SIGNAL(clicked(bool)),this,SLOT(add_row_squid_msnt()));
    connect(ui->m_delete_squid_msnt,SIGNAL(clicked(bool)),this,SLOT(delete_row_squid_msnt()));
}

void MainWindow::view_vis_squid()
{
    model = new QStandardItemModel(1000,4);
    model1 = new QStandardItemModel(1000,2);
    model2 = new QStandardItemModel(1000,1);
    model3 = new QStandardItemModel(1000,2);
    lista_squid();
}

/*
 * Parameter squid
 */
void MainWindow::view_squid()
{
#ifdef Q_OS_LINUX
    find_file_config("/etc/squid/squid.conf",ui->stackedWidget);
#elif defined Q_OS_FREEBSD
    find_file_config("/usr/local/etc/squid/squid.conf",ui->stackedWidget);
#endif
}

void MainWindow::view_parameter_squid()
{
#ifdef Q_OS_LINUX
    read_file("/etc/squid/squid.conf",model);
#elif defined Q_OS_FREEBSD
    read_file("/usr/local/etc/squid/squid.conf",model);
#endif
}

void MainWindow::write_parameter_squid()
{
#ifdef Q_OS_LINUX
    write_file("/etc/squid/squid.conf",ui->tableView);
#elif defined Q_OS_FREEBSD
    write_file("/usr/local/etc/squid/squid.conf",ui->tableView);
#endif
}

/*
 * Parameter mime squid
 */
void MainWindow::view_parameter_mime_squid()
{
#ifdef Q_OS_LINUX
    read_file("/etc/squid/mime.conf",model1);
#elif defined Q_OS_FREEBSD
    read_file("/usr/local/etc/squid/mime.conf",model1);
#endif
}

void MainWindow::write_parameter_mime_squid()
{
#ifdef Q_OS_LINUX
    write_file("/etc/squid/mime.conf",ui->tableView_2);
#elif defined Q_OS_FREEBSD
    write_file("/usr/local/etc/squid/mime.conf",ui->tableView_2);
#endif
}

/*
 * Parameter cache squid
 */
void MainWindow::view_parameter_cache_squid()
{
#ifdef Q_OS_LINUX
    read_file("/etc/squid/cachemgr.conf",model2);
#elif defined Q_OS_FREEBSD
    read_file("/usr/local/etc/squid/cachemgr.conf",model2);
#endif
}

void MainWindow::write_parameter_cache_squid()
{
#ifdef Q_OS_LINUX
    write_file("/etc/squid/cachemgr.conf",ui->tableView_3);
#elif defined Q_OS_FREEBSD
    write_file("/usr/local/etc/squid/cachemgr.conf",ui->tableView_3);
#endif
}

/*
 * Parameter msntauth squid
 */
void MainWindow::view_parameter_msnt_squid()
{
#ifdef Q_OS_LINUX
    read_file("/etc/squid/msntauth.conf",model3);
#elif defined Q_OS_FREEBSD
    read_file("/usr/local/etc/squid/msntauth.conf",model3);
#endif
}

void MainWindow::write_parameter_msnt_squid()
{
#ifdef Q_OS_LINUX
    write_file("/etc/squid/msntauth.conf",ui->tableView_4);
#elif defined Q_OS_FREEBSD
    write_file("/usr/local/etc/squid/msntauth.conf",ui->tableView_4);
#endif
}

/*
 * Backup and restore
 * squid config
 */
void MainWindow::backup_squid()
{
#ifdef Q_OS_LINUX
    backup_squid_config("/etc/squid/squid.conf");
#elif defined Q_OS_FREEBSD
    backup_squid_config("/usr/local/etc/squid/squid.conf");
#endif
}

void MainWindow::restore_squid()
{
#ifdef Q_OS_LINUX
    restore_squid_config("/etc/squid/squid.conf");
#elif defined Q_OS_FREEBSD
    restore_squid_config("/usr/local/etc/squid/squid.conf");
#endif
}

/*
 * Remove and add row
 */
void MainWindow::add_row_squid()
{
    insert_row_squid(model);
}

void MainWindow::delete_row_squid()
{
    remove_row_squid(model,ui->tableView);
}

void MainWindow::add_row_squid_mime()
{
    insert_row_squid(model1);
}

void MainWindow::delete_row_squid_mime()
{
    remove_row_squid(model1,ui->tableView_2);
}

void MainWindow::add_row_squid_cache()
{
    insert_row_squid(model2);
}

void MainWindow::delete_row_squid_cache()
{
    remove_row_squid(model2,ui->tableView_3);
}

void MainWindow::add_row_squid_msnt()
{
    insert_row_squid(model3);
}

void MainWindow::delete_row_squid_msnt()
{
    remove_row_squid(model3,ui->tableView_4);
}

/*
 * Start, stop and restart squid
 */
void MainWindow::start_squid()
{
    if(start_service() == true)
    {
        view_log_error(ui->statusBar);
    }
    else
        view_log_error(ui->statusBar);
}

void MainWindow::stop_squid()
{
    if(stop_service() == true)
    {
        view_log_error(ui->statusBar);
    }
    else
        view_log_error(ui->statusBar);
}

void MainWindow::restart_squid()
{
    if(restart_service() == true)
    {
        view_log_error(ui->statusBar);
    }
    else
        view_log_error(ui->statusBar);
}

void MainWindow::status_squid()
{
    service_status();
}

void MainWindow::lista_squid()
{
    //List parameter squid.conf
    model->setRowCount(0);
    model->setHeaderData(0,Qt::Horizontal,tr("Parameter"));
    model->setHeaderData(1,Qt::Horizontal,tr("Connection"));
    model->setHeaderData(2,Qt::Horizontal,tr("Port"));
    model->setHeaderData(3,Qt::Horizontal,tr("Value"));
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //List parameter mime.conf
    model1->setRowCount(0);
    model1->setHeaderData(0,Qt::Horizontal,tr("Parameter"));
    model1->setHeaderData(1,Qt::Horizontal,tr("Value"));
    ui->tableView_2->setModel(model1);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);

    //List parameter cache.conf
    model2->setRowCount(0);
    model2->setHeaderData(0,Qt::Horizontal,tr("Parameter"));
    ui->tableView_3->setModel(model2);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);

    //List parameter msntauth.conf
    model3->setRowCount(0);
    model3->setHeaderData(0,Qt::Horizontal,tr("Parameter"));
    model3->setHeaderData(1,Qt::Horizontal,tr("Value"));
    ui->tableView_4->setModel(model3);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_4->setSelectionMode(QAbstractItemView::SingleSelection);
}

/*
 * Info application
 */
void MainWindow::information()
{
    about *info = new about(this);
    info->exec();
}

/*
 * View stack squid
 */
void MainWindow::view_stack_squid()
{
    view_squid();
    ui->stackedWidget->setCurrentIndex(1);
    view_vis_squid();
    ui->tabWidget->setCurrentIndex(0);
}

/*
 * View main stack
 */
void MainWindow::view_main_stack()
{
    //Squid config
    ui->stackedWidget->setCurrentIndex(0);
    model->clear();
    model1->clear();
    model2->clear();
    model3->clear();
    //DansGuardian config
    m_dans_c->clear();
    ui->tabWidget_2->setCurrentIndex(0);
}

/*
 * Donate
 */
void MainWindow::donate()
{
    QString apri_link = "http://www.codelinsoft.it/sito/2015-02-18-23-59-25/donate.html";
    QDesktopServices::openUrl(QUrl(apri_link));
}

/*****************************************************
 * DansGuardian config
 ****************************************************/

void MainWindow::view_signal_dans()
{
    //DansGuardian parameter
    connect(ui->read_file_dans_c,SIGNAL(clicked(bool)),this,SLOT(view_parameter_dans()));
    connect(ui->write_file_dans_c,SIGNAL(clicked(bool)),this,SLOT(write_parameter_dans()));
    //Start, stop and restart server dansguardian
    connect(ui->start_dans,SIGNAL(clicked(bool)),this,SLOT(start_dans()));
    connect(ui->stop_dans,SIGNAL(clicked(bool)),this,SLOT(stop_dans()));
    connect(ui->restart_dans,SIGNAL(clicked(bool)),this,SLOT(restart_dans()));
    connect(ui->status_dans,SIGNAL(clicked(bool)),this,SLOT(status_dans()));
    //View return main
    connect(ui->main_ret,SIGNAL(clicked(bool)),this,SLOT(view_main_stack()));
    //View stack dans
    connect(ui->config_dans,SIGNAL(clicked(bool)),this,SLOT(view_stack_dans()));
    //Backup and restore dansguardian
    connect(ui->actionBackup_dansguardian,SIGNAL(triggered(bool)),this,SLOT(backup_dans()));
    connect(ui->actionRestore_backup_dansguardian,SIGNAL(triggered(bool)),this,SLOT(restore_dans()));
    //Add and remove row squid config
    connect(ui->m_row_dans_c,SIGNAL(clicked(bool)),this,SLOT(add_row_dans()));
    connect(ui->m_delete_dans_c,SIGNAL(clicked(bool)),this,SLOT(delete_row_dans()));
}

void MainWindow::view_vis_dans()
{
    m_dans_c = new QStandardItemModel(1000,3);
    view_list_dans();
}

void MainWindow::view_list_dans()
{
    //List parameter dansguardian.conf
    m_dans_c->setRowCount(0);
    m_dans_c->setHeaderData(0,Qt::Horizontal,tr("Parameter"));
    m_dans_c->setHeaderData(1,Qt::Horizontal,tr("Equal"));
    m_dans_c->setHeaderData(2,Qt::Horizontal,tr("Value"));
    ui->tableView_dans_conf->setModel(m_dans_c);
    ui->tableView_dans_conf->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_dans_conf->setSelectionMode(QAbstractItemView::SingleSelection);
}

//View stack dansguardian
void MainWindow::view_stack_dans()
{
    view_dans();
    ui->stackedWidget->setCurrentIndex(2);
    view_vis_dans();
    ui->tabWidget_2->setCurrentIndex(0);
}

void MainWindow::view_dans()
{
#ifdef Q_OS_LINUX
    find_file_config_dans("/etc/dansguardian/dansguardian.conf",ui->stackedWidget);
#elif defined Q_OS_FREEBSD
    find_file_config_dans("/usr/local/etc/dansguardian/dansguardian.conf",ui->stackedWidget);
#endif
}

void MainWindow::view_parameter_dans()
{
#ifdef Q_OS_LINUX
    read_file_dans("/etc/dansguardian/dansguardian.conf",m_dans_c);
#elif defined Q_OS_FREEBSD
    read_file_dans("/usr/local/etc/dansguardian/dansguardian.conf",m_dans_c);
#endif
}

void MainWindow::write_parameter_dans()
{
#ifdef Q_OS_LINUX
    write_file_dans("/etc/dansguardian/dansguardian.conf",ui->tableView_dans_conf);
#elif defined Q_OS_FREEBSD
    write_file_dans("/usr/local/etc/dansguardian/dansguardian.conf",ui->tableView_dans_conf);
#endif
}

void MainWindow::backup_dans()
{
#ifdef Q_OS_LINUX
    backup_dans_config("/etc/dansguardian/dansguardian.conf");
#elif defined Q_OS_FREEBSD
    backup_dans_config("/usr/local/etc/dansguardian/dansguardian.conf");
#endif
}

void MainWindow::restore_dans()
{
#ifdef Q_OS_LINUX
    restore_dans_config("/etc/dansguardian/dansguardian.conf");
#elif defined Q_OS_FREEBSD
    restore_dans_config("/usr/local/etc/dansguardian/dansguardian.conf");
#endif
}

void MainWindow::start_dans()
{
    if(start_service_dans() == true)
    {
        view_log_error_dans(ui->statusBar);
    }
    else
        view_log_error_dans(ui->statusBar);
}

void MainWindow::stop_dans()
{
    if(stop_service_dans() == true)
    {
        view_log_error_dans(ui->statusBar);
    }
    else
        view_log_error_dans(ui->statusBar);
}

void MainWindow::restart_dans()
{
    if(restart_service_dans() == true)
    {
        view_log_error_dans(ui->statusBar);
    }
    else
        view_log_error_dans(ui->statusBar);
}

void MainWindow::status_dans()
{
    status_service_dans();
}

void MainWindow::add_row_dans()
{
    insert_row_dans(m_dans_c);
}

void MainWindow::delete_row_dans()
{
    remove_row_dans(m_dans_c,ui->tableView_dans_conf);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->ignore();
    esci();
}

void MainWindow::esci()
{
    QMessageBox *box= new QMessageBox(this);
    box->setWindowTitle("Squid-gui");
    box->setText(tr("Exit"));
    box->setInformativeText(tr("Are you sure want to quit?"));
    box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box->setDefaultButton(QMessageBox::Ok);
    int ret = box->exec();
    switch(ret){
      case QMessageBox::Ok:
	//Open backup
	exit(0);
	box->close();
	break;
    case QMessageBox::Cancel:
        //Close
        box->close();
        break;
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}
