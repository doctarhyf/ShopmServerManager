#include "widget.h"
#include "ui_widget.h"
#define IP_TIMER_INTERVAL 1000
#define LAST_IP 0
#define NEW_IP 1
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}


void Widget::init()
{

    process = new QProcess(this);
    QSettings settings;
    QString serverPath = settings.value("serverPath", QVariant("")).toString();

    ui->lineEditServerPath->setText(serverPath);

    connected = false;
    counter = 0;
    ip = "";
    ipTimerID = startTimer(IP_TIMER_INTERVAL);

    connect(this, SIGNAL(ipChanged(QString&)), this, SLOT(onIPChange(QString&)));

    bool serverAutoStart = settings.value("serverAutoStart", QVariant(false)).toBool();
    ui->checkBoxServerAutostart->setChecked(serverAutoStart);
    if(ui->checkBoxServerAutostart->isChecked()) startServerProcess();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadIP()
{
    if(counter > 1) counter = 0;
    ip = "";


    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);


    for(int i = 0; i < activeConfigs.size(); i++){
        QNetworkSession session(activeConfigs.at(i), this);

        if( session.interface().flags() & QNetworkInterface::IsUp){

            QNetworkInterface intf = session.interface();

            if(intf.humanReadableName() == "Wi-Fi"){
                //qDebug() << intf.index();

                QList<QNetworkAddressEntry> entrz = intf.addressEntries();

                for(QNetworkAddressEntry adde : entrz){

                   if( adde.ip().protocol() == QAbstractSocket::IPv4Protocol){
                       ip = adde.ip().toString();


                   }


                }

            }


        }

    }


    ips.insert(counter, ip);

    QString ip1 = ips.value(LAST_IP);
    QString ip2 = ips.value(NEW_IP);


    //qDebug() << "ip1 : " << ip1;
    //qDebug() << "ip2 : " << ip2;

    //qDebug() << "Checking";

    if(ip1 != ip2){


        connected = ip == "" ? false : true;

        QString connState = connected ? "online" : "offline";
        qDebug() << "Conn State Changed : " << connState;
        emit ipChanged(ip);


    }



    counter ++;

}

void Widget::onIPChange(QString &newIP)
{
    //qDebug() << "On new IP : " << newIP;
    ip = newIP;
    connected = ip == "" ? false : true;

    if(connected){
        ui->labelIP->setText("IP : <strong>" + ip + "</strong>");
    }else{
        ui->labelIP->setText("<strong>Wi-Fi Disconnected</strong>");
    }


}

void Widget::timerEvent(QTimerEvent *event)
{
    loadIP();
    //qDebug() << "timer event";
}

void Widget::startServerProcess()
{
    QString serverPath = ui->lineEditServerPath->text();

    if(serverPath == ""){
        QMessageBox::critical(this, tr("Chemin serveur vide"), tr("Veuillez choisir un chemin du serveur valide."), QMessageBox::Ok);
        return;
    }

    QFile file(serverPath);

    if(file.open(QIODevice::ReadOnly)){
        if(!file.exists()){

            QMessageBox::critical(this, tr("Fichier inexistant"), tr("Le fichier pointe par le chemin est inexistant."), QMessageBox::Ok);

            file.close();
            return;
        }
        file.close();
    }


    process->start(serverPath);

}


void Widget::on_pushButtonLoadServerPath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choisir fichier serveur"), "C:/xampp", "*.exe");


    if(path != "") {
        QSettings settings;
        settings.setValue("serverPath", path);

        ui->lineEditServerPath->setText(path);
    }
}



void Widget::on_pushButtonStartServer_clicked()
{
    startServerProcess();
}

void Widget::on_checkBoxServerAutostart_toggled(bool checked)
{
    QSettings settings;

    settings.setValue("serverAutoStart", QVariant(checked));
}
