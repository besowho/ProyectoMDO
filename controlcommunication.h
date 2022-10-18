#ifndef CONTROLCOMMUNICATION_H
#define CONTROLCOMMUNICATION_H

#include <QObject>
#include "nzmqt.hpp" // This file contains the class ZMQSocket which facilitates the
                     // implementation of zmq_sockets by using slots and signals from Qt

#include <QStringList>


#define SUBSCRIBER_CONNECT_TO "tcp://192.168.127.10:9005"
#define PUBLISHER_BIND_TO "tcp://*:9004"
#define PUBLISHER_BIND_TO1 "tcp://*:9001"
#define PUBLISHER_BIND_TO2 "tcp://*:9002"
#define PUBLISHER_BIND_TO3 "tcp://*:9003"



class controlCommunication: public QObject // Inherints from QObject to
        // use slots and signals mechanisms
{
    Q_OBJECT
public:
    controlCommunication();
    void connectWithImageProcessingComputer();
    void publishMessage(QString);
    void publishMessage1(QString);
    void publishMessage2(QString);
    void publishMessage3(QString);

    void sendMensaje(QString mensaje);



protected:

    // -----------------------------------------------------------
    // ZMQ objects to connect with control computer
    nzmqt::ZMQContext *zmq_context_pt;
    nzmqt::ZMQSocket *zmq_subscriber_pt;
    nzmqt::ZMQSocket *zmq_publisher_pt;
    /*nzmqt::ZMQSocket *zmq_publisher_pt;
    nzmqt::ZMQContext *zmq_context_pt1;
    nzmqt::ZMQSocket *zmq_publisher_pt1;
    nzmqt::ZMQContext *zmq_context_pt2;
    nzmqt::ZMQSocket *zmq_publisher_pt2;
    nzmqt::ZMQContext *zmq_context_pt3;
    nzmqt::ZMQSocket *zmq_publisher_pt3;*/
    nzmqt::ZMQContext *zmq_context_ptsub;

private slots:

    // Process information received in the subscriber socket
    void subscriber_process_received_message(const QList<QByteArray>& message_list);

    //void send_Live_Signal();

signals:
void sharedMessage(QString);


};

#endif // CONTROLCOMMUNICATION_H
