#ifndef MAININTERFACE_H
#define MAININTERFACE_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtTest>
#include <unistd.h>
#include <QProcess>



#include "processimagethread.h"
//#include "controlcamerathread.h"
//#include "controlcommunication.h"
//#include "hiloprocesamensajes.h"
#include "communicationthread.h"

//class controlCameraThread;
//class controlCommunication;
//class CommunicationThread;


class mainInterface : public QObject
{
    Q_OBJECT

public:
    mainInterface(QObject *parent = nullptr);
   //~mainInterface();
    void getMessage(QString message);
    void sendMensaje(QString mensaje);
    void cicloEsperaMensaje();
    void startPing();
    QProcess *processPing = new QProcess(this);


public slots:

    void receivedMessage(QString);
    void receiveMessageFromPIT(QString);
    void receivedMessageFromSocket(QString);
    void rightMessagePing();
    //void reciveMensajeDividido(unsigned short *);

signals:
    void sendControlCamera(unsigned int, unsigned int);
    void sendToThreadPIT(QString);
    void sendToThreadCcom(QString);
    void prueba(QString);
private:
   // controlCameraThread cCamThread;
   // controlCommunication ccom;
    CommunicationThread *ccomThread = new CommunicationThread(this);
    processImageThread pImageThread;
    void commRecovery();

    //HiloProcesaMensajes hiloProcesaMensajes;


};

#endif // MAININTERFACE_H
