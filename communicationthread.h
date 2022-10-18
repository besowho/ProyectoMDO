#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QString>
#include <QEventLoop>
#include <iostream>
#include <QCoreApplication>
#include <QtTest>



#include "controlcommunication.h"


//class controlCommunication;


class CommunicationThread : public QThread
{
    Q_OBJECT
public:
    CommunicationThread(QObject *parent = nullptr);
    void setStart();
    void sendMensaje(QString mensaje);
    void sendSignalMainInterface();

public slots:
    void mensajeFromInterfazPrincipal(QString);

signals:
    void controlDetccion(bool tipoDeteccion, bool shutDown, double collisionAlertThreshold);
    void sendMensajeFromZocket(QString);

private slots:

    void mensajeFromDecodificaMensaje(unsigned short *);



protected:
    void run() ;

private:
    QMutex mutex;
    QWaitCondition condition;
    int mensajeRecibidoInt=0;
    QString mensajeRecibido, mensajeAux;
    bool newMensaje=false;
    controlCommunication ccom;

};

#endif // COMMUNICATIONTHREAD_H
