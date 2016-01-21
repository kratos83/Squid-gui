#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    connect(ui->esci,SIGNAL(clicked(bool)),this,SLOT(close()));
    setWindowTitle("About");
    view_info();
}

void about::view_info()
{
    ui->info->setAlignment(Qt::AlignCenter);
    ui->info->setText(QString::fromUtf8(tr("Squid-Gui proxy server for Linux and BSD.\n"
                                                      "(C)2015 Codelinsoft. All right reserved.\n"
                                                      "Squid-Gui version 0.2\n"
                                                      "\nCompiled version Qt: ").toStdString().c_str())+QString(QT_VERSION_STR));
}

about::~about()
{
    delete ui;
}
