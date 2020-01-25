#include "mainwindow.h"
#include <QApplication>
#include <QLoggingCategory>
#include <QDesktopWidget>
#include "defines.h"
#include "settingsmanager.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

Q_DECLARE_LOGGING_CATEGORY(Squid)
Q_LOGGING_CATEGORY(Squid, "Squid-gui");

static void impostazioni(SettingsManager *settings)
{    
    if(settings->generalValue("CartellaLog/LOG",QVariant()).toString().length() == 0)
    {
#ifdef Q_WS_WIN
	settings->setGeneralValue("CartellaLog/LOG",settings->logDir->path()+"/SQUIDGUI.txt");
	qCDebug(Squid) <<  "Inizzalizzazione cartella";
	qCDebug(Squid) <<  settings->logDir->path()+"/SQUIDGUI.txt";
#else
	settings->setGeneralValue("CartellaLog/LOG",settings->logDir->path()+"/SQUIDGUI.txt");
	qCDebug(Squid) <<  "Inizzalizzazione cartella";
	qCDebug(Squid) <<  settings->logDir->path()+"/SQUIDGUI.txt";
#endif
    }
    else
    {
      settings->generalValue("CartellaLog/LOG",QVariant()).toString();
      qCDebug(Squid) <<  "Cartella di destinazione dei file log";
      qCDebug(Squid) <<  settings->generalValue("CartellaLog/LOG",QVariant()).toString();
    }
}

static bool enableRoot()
{
    if(getuid() != 0)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    SettingsManager *settings = new SettingsManager();
    //Visualizzo le impostazioni
    impostazioni(settings);
    
    //Creo il backup del log
    QString file_name = settings->generalValue("CartellaLog/LOG",QVariant()).toString();
    QFile fileName(file_name);
    if(fileName.exists())
    {
        QString destinazione = settings->logDir->path()+"/backup/SQUIDGUI_bkp.txt";
        qCDebug(Squid) <<  "Cartella di destinazione dei log backup ";
        qCDebug(Squid) <<  settings->logDir->path()+"/backup/SQUIDGUI_bkp.txt";
        fileName.copy(destinazione);
    }
    
    //Imposto il log
    LOG_FILE("SQUID-GUI 0.3",LOG_DEFAULT_ALL,QIODevice::WriteOnly);
    qCDebug(Squid) <<  "SQUID-GUI 0.3";
    LOG_FILE("LOG CREATO IL: "+QDate::currentDate().toString("dd/MM/yyyy"),LOG_DEFAULT_ALL,QIODevice::Append);
    qCDebug(Squid) <<  "LOG CREATO IL: "+QDate::currentDate().toString("dd/MM/yyyy");
    LOG_FILE("OS UTILIZZATO: "+getSystemInfo(),LOG_DEFAULT_ALL,QIODevice::Append);
    qCDebug(Squid) <<  "OS UTILIZZATO: ";
    qCDebug(Squid) <<  getSystemInfo().toStdString().c_str();
    LOG_FILE("READ MEMORY:\n"+getSystemRam()+"\n\n\n",LOG_DEFAULT_ALL,QIODevice::Append);
    qCDebug(Squid) <<  "READ MEMORY:";
    qCDebug(Squid) << getSystemRam().toStdString().c_str();
    
    /*
     * Translate QDialog
     */
    QTranslator translator;
    translator.load(":/lang/"+QLocale::system().name()+".qm");
    a.installTranslator(&translator);
    MainWindow w;
    QDesktopWidget wid;

    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();

    w.setGeometry((screenWidth/2)-(w.width()/2),(screenHeight/2)-(w.height()/2),w.width(),w.height());
    if(enableRoot() == 0){
        w.show();
        LOG_FILE("Avvio Squid-gui",LOG_INFO_ALL,QIODevice::Append);
        qCDebug(Squid) <<  "Avvio Squid-gui";
    }
    else{
        LOG_FILE("Access denied. Use root",LOG_INFO_ALL,QIODevice::Append);
        qCDebug(Squid) <<  "Access denied. Use root";
        QMessageBox::warning(0,QObject::tr("Squid-gui"),QObject::tr("Access denied.\n\nUse root."));
        exit(1);
    }
    
    
    return a.exec();
}
