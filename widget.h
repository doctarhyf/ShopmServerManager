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
#include <QSystemTrayIcon>

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
    void onTrayIconMenuTriggered(QAction* action);
    void messageClicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void onIPChange(QString &newIP);

    void on_pushButtonLoadServerPath_clicked();



    void on_pushButtonStartServer_clicked();

    void on_checkBoxServerAutostart_toggled(bool checked);

    void on_pushButtonStopServer_clicked();

    void on_pushButtonClearLog_clicked();

    void on_pushButtonSaveLog_clicked();

signals:
    void ipChanged(QString &newIP);

protected:
    void timerEvent(QTimerEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void checkForNewRepport();
    int repportCountOld, repportCountNew;
    void initTrayIcon();
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void log(QString log);
    QString connState;
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
