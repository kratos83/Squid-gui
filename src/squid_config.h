#ifndef SQUID_CONFIG_H
#define SQUID_CONFIG_H

#include <QtGui>
#include <QStatusBar>
#include <QMessageBox>
#include <QtCore>
#include <QTableView>
#include <QStackedWidget>
#include <QDebug>


namespace squid_config
{
    void find_file_config(QString fileName, QStackedWidget *widget);
    void read_file(QString nameFile, QStandardItemModel *model );
    void write_file(QString fileName, QTableView *view);
    bool start_service();
    bool stop_service();
    bool restart_service();
    void service_status();
    void view_log_error(QStatusBar *label);
    void backup_squid_config(QString filename);
    void restore_squid_config(QString filename);
    void insert_row_squid(QStandardItemModel *model);
    void remove_row_squid(QStandardItemModel *model, QTableView *view);
}

#endif // SQUID_CONFIG_H
