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

#ifndef STATUS_SERVICE_H
#define STATUS_SERVICE_H

#include <QtWidgets>

namespace Ui
{
class status_service;
}

class status_service : public QDialog
{
    Q_OBJECT
public:
    explicit status_service(QString read_service, QString read_name_service, QWidget *parent = 0);
    ~status_service();

private:
    Ui::status_service* ui;
    QString testo,read_function;
};

#endif // STATUS_SERVICE_H
