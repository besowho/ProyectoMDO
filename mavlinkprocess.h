#ifndef MAVLINKPROCESS_H
#define MAVLINKPROCESS_H

#include <QObject>
#include <common/mavlink.h>
#include <QtNetwork/QUdpSocket>



class mavlinkProcess : public QObject
{
    Q_OBJECT
public:
    mavlinkProcess(QObject *parent = nullptr);
    QUdpSocket *socketMavlink;

    void readMsgMavlink();
    void initSocketMavlink();
    void sendHeartBeat();
    QString getSurfaceBoatHeading();



signals:



};

#endif // MAVLINKPROCESS_H
