#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui/QtGui>
#include <QtDebug>
#include <QtNetwork/QtNetwork>
#include <QMessageBox>
#include <qqrencode.h>
#include <QFileDialog>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onIPChange(QString &newIP);

    void on_pushButtonLoadServerPath_clicked();



    void on_pushButtonStartServer_clicked();

    void on_checkBoxServerAutostart_toggled(bool checked);

signals:
    void ipChanged(QString &newIP);

protected:
    void timerEvent(QTimerEvent *event);

private:
    void generateIPQRCode();
    void startServerProcess();
    QProcess *process;
    bool connected;
    QHash<int, QString> ips;
    int counter;
    void loadIP();
    int ipTimerID;
    void init();
    Ui::Widget *ui;
    QString ip;
};

#endif // WIDGET_H
