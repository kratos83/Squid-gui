/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

