#ifndef DANSGUARDIAN_CONFIG_H
#define DANSGUARDIAN_CONFIG_H

#include <QtGui>
#include <QStatusBar>
#include <QMessageBox>
#include <QtCore>
#include <QTableView>
#include <QStackedWidget>
#include <QDebug>

namespace dansguardian_config
{
    void find_file_config_dans(QString fileName, QStackedWidget *widget);
    void read_file_dans(QString nameFile, QStandardItemModel *model );
    void write_file_dans(QString fileName, QTableView *view);
    bool start_service_dans();
    bool stop_service_dans();
    bool restart_service_dans();
    void status_service_dans();
    void view_log_error_dans(QStatusBar *label);
    void backup_dans_config(QString filename);
    void restore_dans_config(QString filename);
    void insert_row_dans(QStandardItemModel *model);
    void remove_row_dans(QStandardItemModel *model, QTableView *view);
}

#endif // DANSGUARDIAN_CONFIG_H
