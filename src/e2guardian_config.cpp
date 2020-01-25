#include "e2guardian_config.h"
#include "defines.h"
#include "status_service.h"

void e2guardian_config::find_file_config_dans(QString fileName, QStackedWidget *widget)
{
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly))
     {
	 LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Access denied. Unable to read file. Use root."),
	   LOG_ERROR_ALL,QIODevice::Append);
	 widget->setCurrentIndex(0);
         QMessageBox::warning(0,QObject::tr("E2Guardian configuration"),QObject::tr("Access denied.\nUnable to read file.\nUse root."));
     }
     else
     {
	 LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Start your configuration."),
	   LOG_INFO_ALL,QIODevice::Append);
     }
}

void e2guardian_config::read_file_dans(QString nameFile, QStandardItemModel *model)
{
    QFile file(nameFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int count = 0;
        QTextStream stream(&file);
        while(!stream.atEnd()){
            QString line = stream.readLine().trimmed();

            //Empty line
            if(line.isEmpty())
                continue;

            //Comment
            if("#" == line.left(1))
                continue;

            //Add
            QStringList list = line.split(" ");
            for(int y =0; y< list.size(); y++){
                QString value = list.at(y);
                QStandardItem *m_item1 = new QStandardItem(value);
                model->setItem(count,y,m_item1);
            }
            count++;
        }
        file.close();
	LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Load file successfull."),
	   LOG_INFO_ALL,QIODevice::Append);
    }
    else
    {	
	LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Unable to read file."),
	   LOG_ERROR_ALL,QIODevice::Append);
        QMessageBox::warning(0,QObject::tr("E2Guardian configuration"),QObject::tr("Unable to read file."));
    }
}

void e2guardian_config::write_file_dans(QString fileName, QTableView *view)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            QTextStream stream(&file);
            int x = 0;
            QString exportdata;

            int counthidden=0, jint = 0;

            while (jint < view->model()->columnCount()) {
                counthidden+=view->isColumnHidden(jint);
                jint++;
            }

            int z = 0;

            int w = 1;
            while (z < view->model()->rowCount()) {

                x = 0;

                w = 1;
            while (x < view->model()->columnCount()) {
            if (!view->isColumnHidden(x)) {

		 QString indice = view->model()->data(view->model()->index(z,x),Qt::DisplayRole).toString();
                 exportdata.append(indice);
		 
                if (view->model()->columnCount() - w > counthidden)
                exportdata.append(" ");
                else
                exportdata.append("\n");

                w++;
            }
                x++;

            }

                z++;
            }
            stream << exportdata;
            file.close();
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Write file successfull."),
	   LOG_INFO_ALL,QIODevice::Append);
    }
    else {
       LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Cannot write file."),
	   LOG_ERROR_ALL,QIODevice::Append);
       QMessageBox::warning(0,QObject::tr("E2Guardian configuration"),QObject::tr("Cannot write file."));
    }
}

bool e2guardian_config::start_service_dans()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl start e2guardian");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/e2guardian start");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

bool e2guardian_config::stop_service_dans()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl stop e2guardian");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/e2guardian stop");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

bool e2guardian_config::restart_service_dans()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl restart e2guardian");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/e2guardian restart");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

void e2guardian_config::status_service_dans()
{
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    status_service *st;
#ifdef Q_OS_LINUX
    process.start("systemctl status e2guardian");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
	st = new status_service(result,QObject::tr("Status e2guardian"));
	st->exec();
    }
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/e2guardian status");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
	st = new status_service(result,QObject::tr("Status e2guardian"));
	st->exec();
    }
#endif
}

void e2guardian_config::view_log_error_dans(QStatusBar *label)
{
    QProcess process;
#ifdef Q_OS_LINUX
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("systemctl is-active e2guardian");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
        QStringList list = result.split('\n');
        if(list.at(0) == "active")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian started."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("E2Guardian started"));
        }
        else if(list.at(0) == "unknown")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian stopped."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("E2Guardian stopped"));
        }
        else if(list.at(0) == "failed")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian failed to start. Press systemctl status e2guardian."),
		      LOG_ERROR_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("E2Guardian failed to start. Press systemctl status e2guardian"));
        }
    }
#elif defined Q_OS_FREEBSD
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("/usr/local/etc/rc.d/e2guardian status");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
        QStringList list = result.split('as');
        if(list.at(0) == "e2guardian is running")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian started."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("E2Guardian started"));
        }
        else if(list.at(0) == "e2guardian is not running")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian stopped."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("E2Guardian stopped"));
        }
    }
#endif
}

void e2guardian_config::backup_dans_config(QString filename)
{
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.start("cp -rv "+filename+" "+filename+".bkp");
    process.waitForFinished();
    process.close();
    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Backup successfull."),
		      LOG_INFO_ALL,QIODevice::Append);
}

void e2guardian_config::restore_dans_config(QString filename)
{
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("cp -rv "+filename+".bkp "+filename);
    process.waitForFinished();
    process.close();
    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("E2Guardian::Restore backup successfull."),
		      LOG_INFO_ALL,QIODevice::Append);
}

void e2guardian_config::insert_row_dans(QStandardItemModel *model)
{
    QList<QStandardItem*> item;
    QStandardItem *new_row = new QStandardItem;
    item.append(new_row);
    model->appendRow(item);
}

void e2guardian_config::remove_row_dans(QStandardItemModel *model, QTableView *view)
{
    QModelIndex currentIndex = view->selectionModel()->currentIndex();
    model->removeRow(currentIndex.row());
}

