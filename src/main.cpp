#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "defines.h"
#include "settingsmanager.h"

static void impostazioni(SettingsManager *settings)
{    
    if(settings->generalValue("CartellaLog/LOG",QVariant()).toString().length() == 0)
    {
#ifdef Q_WS_WIN
	settings->setGeneralValue("CartellaLog/LOG",settings->logDir->path()+"/SQUIDGUI.txt");
#else
	settings->setGeneralValue("CartellaLog/LOG",settings->logDir->path()+"/SQUIDGUI.txt");
#endif
    }
    else
    {
      settings->generalValue("CartellaLog/LOG",QVariant()).toString();
    }
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
	fileName.copy(destinazione);
    }
    
    //Imposto il log
    LOG_FILE("SQUID-GUI 0.2",LOG_DEFAULT_ALL,QIODevice::WriteOnly);
    LOG_FILE("LOG CREATO IL: "+QDate::currentDate().toString("dd/MM/yyyy"),LOG_DEFAULT_ALL,QIODevice::Append);
    LOG_FILE("OS UTILIZZATO: "+getSystemInfo(),LOG_DEFAULT_ALL,QIODevice::Append);
    LOG_FILE("READ MEMORY:\n"+getSystemRam()+"\n\n\n",LOG_DEFAULT_ALL,QIODevice::Append);
    
    /*
     * Translate QDialog
     */
    QTranslator translator;
    translator.load(":/lang/"+QLocale::system().name()+".qm");
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    LOG_FILE("Avvio Squid-gui",LOG_INFO_ALL,QIODevice::Append);

    return a.exec();
}
