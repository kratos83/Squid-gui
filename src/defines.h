#ifndef DEFINES_H
#define DEFINES_H


#include <QtGui>
#include <QSysInfo>
#include <QDebug>
#include <QProcess>
#include <QLabel>

#if defined(Q_OS_WIN)
#include <windows.h>
#include <stdio.h>
#endif

#include "settingsmanager.h"

/********************************************
 * Visualizzo o dansguardian o e2guardian
 * ******************************************/
#define DANSGUARDIAN "dansguardian"
#define DANSGUARDIAN_DIR "/etc/dansguardian"
#define E2GUARDIAN "e2guardian"
#define E2GUARDIAN_DIR "/et/e2guardian"
/********************************************/
/********Definizizioni sistemi operativi*****/
#define WINDOWS_XP "Windows Xp"
#define WINDOWS_VISTA "Windows Vista"
#define WINDOWS_SEVEN "Windows 7"
#define WINDOWS_8 "Windows 8"
#define WINDOWS_8_1 "Windows 8.1"
#define WINDOWS_10 "Windows 10"
#define _WINNT "OS basato su NT"


//Visualizzo i sistemi utilizzati
static QString getSystemInfo()
{
  QString os_type = "";
#if defined(Q_OS_LINUX)
    QString com_lsb = "lsb_release -d ";
    QString com_uname = "uname -a";
    QProcess *add_rel = new QProcess;
    add_rel->setReadChannel(QProcess::StandardOutput);
    add_rel->setProcessChannelMode(QProcess::MergedChannels);
    add_rel->start(com_lsb);
    add_rel->closeWriteChannel();
    if(add_rel->state()!=QProcess::NotRunning){
        add_rel->waitForReadyRead();
        QByteArray result = add_rel->readAll();
    QStringList list = QString(result).split(":");
    QString text = list.at(1);
        os_type += text;
    }

    os_type += " -- ";

    QProcess *add_uname = new QProcess;
    add_uname->setReadChannel(QProcess::StandardOutput);
    add_uname->setProcessChannelMode(QProcess::MergedChannels);
    add_uname->start(com_uname);
    add_uname->closeWriteChannel();
    if(add_uname->state()!=QProcess::NotRunning){
        add_uname->waitForReadyRead();
        QByteArray result = add_uname->readAll();
        os_type += QString(result);
    }

#elif defined(Q_OS_WIN)
    switch(QSysInfo::windowsVersion())
    {
      case QSysInfo::WV_XP:
    os_type += WINDOWS_XP;
      break;
      case QSysInfo::WV_VISTA:
    os_type += WINDOWS_VISTA;
      break;
      case QSysInfo::WV_WINDOWS7:
    os_type += WINDOWS_SEVEN;
      break;
      case QSysInfo::WV_WINDOWS8:
    os_type += WINDOWS_8;
      break;
      case QSysInfo::WV_WINDOWS8_1:
    os_type += WINDOWS_8_1;
      break;
      case QSysInfo::WV_NT_based:
    os_type += _WINNT;
      break;
      default:
      break;
    }
#elif defined(Q_OS_MACX)
    QString com_uname = "uname -a";
  QProcess *add_uname = new QProcess;
  add_uname->setReadChannel(QProcess::StandardOutput);
  add_uname->setProcessChannelMode(QProcess::MergedChannels);
  add_uname->start(com_uname);
  add_uname->closeWriteChannel();
  if(add_uname->state()!=QProcess::NotRunning){
      add_uname->waitForReadyRead();
      QByteArray result = add_uname->readAll();
      os_type += QString(result);
  }
#elif defined(Q_OS_FREEBSD)
    QString com_uname = "uname -a";
    QProcess *add_uname = new QProcess;
    add_uname->setReadChannel(QProcess::StandardOutput);
    add_uname->setProcessChannelMode(QProcess::MergedChannels);
    add_uname->start(com_uname);
    add_uname->closeWriteChannel();
    if(add_uname->state()!=QProcess::NotRunning){
        add_uname->waitForReadyRead();
        QByteArray result = add_uname->readAll();
        os_type += QString(result);
    }
#endif

    return os_type;
}

//Visualizzo la ram installata e utilizzata
static QString getSystemRam(){
  QString os_ram = "";
#if defined(Q_OS_LINUX)
    QString com_ram = "head -3 /proc/meminfo";
    QProcess *add_mem = new QProcess;
    add_mem->setReadChannel(QProcess::StandardOutput);
    add_mem->setProcessChannelMode(QProcess::MergedChannels);
    add_mem->start(com_ram);
    add_mem->closeWriteChannel();
    if(add_mem->state()!=QProcess::NotRunning){
        add_mem->waitForReadyRead();
        QByteArray result = add_mem->readAll();
    QStringList list = QString(result).split(":");
    //Visualizzo la memoria totale
    QStringList ram_tot = list.at(1).split("MemFree");
    QStringList ram_tot_t = ram_tot.at(0).split("kB");
    double ram_totale = ram_tot_t.at(0).toDouble()/1024/1024;
    //Visualizzo la memoria libera
    QStringList ram_av = list.at(3).split("kB");
    double ram_libera = ram_av.at(0).toDouble()/1024/1024;
    //Visualizzo la memoria utilizzata
    double ram_utilizzata = ram_totale-ram_libera;
    os_ram += "Memoria totale: "+QString::number(ram_totale,'f',2)+" GB\n"+
          "Memoria utilizzata: "+QString::number(ram_utilizzata,'f',2)+" GB\n"+
          "Memoria libera: "+QString::number(ram_libera,'f',2)+" GB";
    }
#elif defined(Q_OS_WIN)
  MEMORYSTATUSEX memory_status;
  ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
  memory_status.dwLength = sizeof(MEMORYSTATUSEX);
  if (GlobalMemoryStatusEx(&memory_status)) {
    os_ram += QString("\nMemoria totale: %1 GB").arg(memory_status.ullTotalPhys / (1024 * 1024 *1024))+
              QString("\nMemoria utilizzata: %1 GB").arg(memory_status.ullAvailVirtual / (1024 * 1024 *1024))+
             QString("\nMemoria libera: %1 GB").arg(memory_status.ullAvailPhys / (1024 * 1024 *1024));
  } else {
    os_ram += "Unknown RAM";
  }
#elif defined(Q_OS_MACX)
  QString com_ram_freebsd = "sysctl hw.physmem hw.usermem";
  QProcess *add_mem = new QProcess;
  add_mem->setReadChannel(QProcess::StandardOutput);
  add_mem->setProcessChannelMode(QProcess::MergedChannels);
  add_mem->start(com_ram_freebsd);
  add_mem->closeWriteChannel();
  if(add_mem->state()!=QProcess::NotRunning){
      add_mem->waitForReadyRead();
      QByteArray result = add_mem->readAll();
  QStringList list = QString(result).split(":");
  //Visualizzo memoria totale
  QStringList ram_tot = list.at(1).split("hw.usermem");
  double ram_totale = (ram_tot.at(0).toDouble()/1024)/1024/1024;
  //Visualizzo la memoria libera
  double ram_libera = (list.at(2).toDouble()/1024)/1024/1024;
  //Visualizzo la ram utilizzata
  double ram_utilizzata = ram_totale-ram_libera;
  os_ram += "Memoria totale: "+QString::number(ram_totale,'f',2)+" GB\n"+
        "Memoria utilizzata: "+QString::number(ram_utilizzata,'f',2)+" GB\n"+
        "Memoria libera: "+QString::number(ram_libera,'f',2)+" GB";
  }
#elif defined(__FreeBSD__)
  QString com_ram_freebsd = "sysctl hw.physmem hw.usermem";
  QProcess *add_mem = new QProcess;
  add_mem->setReadChannel(QProcess::StandardOutput);
  add_mem->setProcessChannelMode(QProcess::MergedChannels);
  add_mem->start(com_ram_freebsd);
  add_mem->closeWriteChannel();
  if(add_mem->state()!=QProcess::NotRunning){
      add_mem->waitForReadyRead();
      QByteArray result = add_mem->readAll();
  QStringList list = QString(result).split(":");
  //Visualizzo memoria totale
  QStringList ram_tot = list.at(1).split("hw.usermem");
  double ram_totale = (ram_tot.at(0).toDouble()/1024)/1024/1024;
  //Visualizzo la memoria libera
  double ram_libera = (list.at(2).toDouble()/1024)/1024/1024;
  //Visualizzo la ram utilizzata
  double ram_utilizzata = ram_totale-ram_libera;
  os_ram += "Memoria totale: "+QString::number(ram_totale,'f',2)+" GB\n"+
        "Memoria utilizzata: "+QString::number(ram_utilizzata,'f',2)+" GB\n"+
        "Memoria libera: "+QString::number(ram_libera,'f',2)+" GB";
  }

#endif

  return os_ram;
}


/*
 * Istanzio gli errori
 */
enum SOFT_LOG{
    LOG_ERROR_ALL,
    LOG_WARNING_ALL,
    LOG_INFO_ALL,
    LOG_DEFAULT_ALL
};

/*
 * Scrivo il log del file
 */
static void LOG_FILE(QString linea ,const SOFT_LOG soft, QIODevice::OpenModeFlag flags)
{
    QFile soft_file(settingsManager->generalValue("CartellaLog/LOG",QVariant()).toString());
    soft_file.open(flags);
    
    QTextStream stream(&soft_file);
    switch(soft)
    {
      case LOG_ERROR_ALL:
    stream << "[ERRORE]: " << linea+"\n";
      break;
      case LOG_WARNING_ALL:
    stream << "[ATTENZIONE]: " << linea+"\n";
      break;
      case LOG_INFO_ALL:
    stream << "[INFO]: " << linea+"\n";
      break;
      default:
    stream << "" << linea+"\n";
      break;
    }
    QByteArray array;
    array.append(linea);
    soft_file.close();
}

#endif // DEFINES_H
