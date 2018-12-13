#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui/QtGui>
#include <QtDebug>
#include <QtNetwork/QtNetwork>

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

signals:
    void ipChanged(QString &newIP);

protected:
    void timerEvent(QTimerEvent *event);

private:
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
