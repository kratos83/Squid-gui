#include "squid_config.h"
#include "defines.h"
#include "status_service.h"

using namespace squid_config;

SquidConfig::SquidConfig(QObject *parent)
  :  QObject(parent)
{
}

void SquidConfig::find_file_config(QString fileName, QStackedWidget *widget)
{
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly))
     {
         LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Access denied. Unable to read file. Use root."),
	   LOG_ERROR_ALL,QIODevice::Append);
	 widget->setCurrentIndex(0);
         QMessageBox::warning(0,QObject::tr("Squid configuration"),QObject::tr("Access denied.\nUnable to read file.\nUse root."));
     }
     else
     {
	 LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Start your configuration."),
	   LOG_INFO_ALL,QIODevice::Append);
     }
}

void SquidConfig::read_file(QString nameFile, QStandardItemModel *model)
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
	LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Load file successfull."),
	   LOG_INFO_ALL,QIODevice::Append);
    }
    else
    {
	LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Unable to read file."),
	   LOG_ERROR_ALL,QIODevice::Append);
    }
}

void SquidConfig::write_file(QString fileName, QTableView *view)
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
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Write file successfull."),
	   LOG_INFO_ALL,QIODevice::Append);
    }
    else {
       QMessageBox::warning(0,QObject::tr("Squid configuration"),QObject::tr("Cannot write file."));
       LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Cannot write file."),
	   LOG_ERROR_ALL,QIODevice::Append);
    }
}

bool SquidConfig::start_service()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl start squid");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/squid start");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

bool SquidConfig::stop_service()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl stop squid");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/squid stop");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

bool SquidConfig::restart_service()
{
    bool ok = false;
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
#ifdef Q_OS_LINUX
    process.start("systemctl restart squid");
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/squid restart");
#endif
    process.waitForFinished();
    process.close();
    return ok ? true : false;
}

void SquidConfig::service_status()
{
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    status_service *st;
#ifdef Q_OS_LINUX
    process.start("systemctl status squid");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
	st = new status_service(result,QObject::tr("Status squid"));
	st->exec();
    }
#elif defined Q_OS_FREEBSD
    process.start("/usr/local/etc/rc.d/squid status");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
	st = new status_service(result,QObject::tr("Status squid"));
	st->exec();
    }
#endif
}

void SquidConfig::view_log_error(QStatusBar *label)
{
    QProcess process;
#ifdef Q_OS_LINUX
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("systemctl is-active squid");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
        QStringList list = result.split('\n');
        if(list.at(0) == "active")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid started."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("Squid started"));
        }
        else if(list.at(0) == "unknown")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid stopped."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("Squid stopped"));
        }
        else if(list.at(0) == "failed")
        {
	    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid failed to start. Press systemctl status squid."),
		      LOG_ERROR_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("Squid failed to start. Press systemctl status squid"));
        }
    }
#elif defined Q_OS_FREEBSD
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("/usr/local/etc/rc.d/squid status");
    process.closeWriteChannel();
    while(process.state() != QProcess::NotRunning)
    {
        process.waitForReadyRead();
        QString result = process.readAll();
        QStringList list = result.split('as');
        if(list.at(0) == "squid is running")
        {
	     LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid started."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("Squid started"));
        }
        else if(list.at(0) == "squid is not running")
        {
	     LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid stopped."),
		      LOG_INFO_ALL,QIODevice::Append);
            label->showMessage(QObject::tr("Squid stopped"));
        }
    }
#endif
}

void SquidConfig::backup_squid_config(QString filename)
{
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.start("cp -rv "+filename+" "+filename+".bkp");
    process.waitForFinished();
    process.close();
     LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Backup successfull."),
		      LOG_INFO_ALL,QIODevice::Append);
}

void SquidConfig::restore_squid_config(QString filename)
{
    QProcess process;
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("cp -rv "+filename+".bkp "+filename);
    process.waitForFinished();
    process.close();
    LOG_FILE("["+QTime::currentTime().toString("hh:mm:ss")+"] "+QObject::tr("Squid::Restore backup successfull."),
		      LOG_INFO_ALL,QIODevice::Append);
}

void SquidConfig::insert_row_squid(QStandardItemModel *model)
{
    QList<QStandardItem*> item;
    QStandardItem *new_row = new QStandardItem;
    item.append(new_row);
    model->appendRow(item);
}

void SquidConfig::remove_row_squid(QStandardItemModel *model, QTableView *view)
{
    QModelIndex currentIndex = view->selectionModel()->currentIndex();
    model->removeRow(currentIndex.row());
}
