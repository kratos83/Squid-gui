#include "status_service.h"
#include "ui_status_service.h"
#include <QDebug>

status_service::status_service(QString read_service, QString read_name_service, QWidget *parent): 
	QDialog(parent),
	ui(new Ui::status_service)
{
    ui->setupUi(this);
    testo = read_service;
    read_function = read_name_service;
    setWindowTitle(read_function);
    ui->textEdit->setPlainText(testo);
    connect(ui->m_exit,SIGNAL(clicked(bool)),this,SLOT(close()));
}

status_service::~status_service()
{
    delete ui;
}

