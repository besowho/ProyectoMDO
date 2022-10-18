#include "maininterface.h"


mainInterface::mainInterface(QObject *parent)
    :QObject(parent)
{
    //cCamThread = new controlCameraThread(this);
    //ccomThread = new CommunicationThread(this);
    //pImageThread.wait();
    //ccomThread.wait();
    pImageThread.start(QThread::NormalPriority);
    ccomThread->start(QThread::NormalPriority);
    connect(this, SIGNAL(sendToThreadPIT(QString)), &pImageThread, SLOT(getConfigureInformation(QString)));
    connect(this, SIGNAL(sendToThreadCcom(QString)), ccomThread, SLOT(mensajeFromInterfazPrincipal(QString)));

    connect(&pImageThread, SIGNAL(sendDetectedInformation(QString)), this, SLOT(receiveMessageFromPIT(QString)));

    connect(ccomThread, SIGNAL(sendMensajeFromZocket(QString)), this, SLOT(receivedMessageFromSocket(QString )));

    //connect(this, SIGNAL(prueba(QString)), this, SLOT(receivedMessageFromSocket(QString)));

  //56565656565656565  ccom.connectWithImageProcessingComputer();
 //ccomThread.start();
    //connect(processPing, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessagePing()));
    startPing();
}
void mainInterface::receivedMessage(QString message)
{

}

/*void mainInterface::reciveMensajeDividido(unsigned short *mensajeui)
{
    unsigned short deteccion=mensajeui[0];
    unsigned short funcionesEspeciales=mensajeui[1];
    unsigned short movimiento=mensajeui[2];
    unsigned short pulsoVida=mensajeui[3];

    qDebug()<<"SLOT(reciveMensajes, valor Deteccion: "<<deteccion<<", Funcion especial: "<< funcionesEspeciales<<", Movimiento: "<<movimiento<<", pulso de vida: "<<pulsoVida;
    emit sendControlCamera(funcionesEspeciales, movimiento);

}*/

void mainInterface::getMessage(QString message)
{
    //qDebug()<<message<<QThread::currentThread();
    //cicloEsperaMensaje();
   // ccomThread.setStart();
    //emit sendToThread(message);
   // ccomThread.setStart();
   // pImageThread.recibeMensaje("Hola 565777");
    sendMensaje(message);
}

void mainInterface::cicloEsperaMensaje()
{
   //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);
    int i=0;
    int contadorPing=0;
    QString cadena_esperada="64 bytes from";
    forever
    {
        //usleep(6000);

        //QCoreApplication::processEvents();
       processPing->waitForReadyRead(100);
        //processPing->waitForFinished(100);
        QByteArray strdata = processPing->readAllStandardOutput();
        strdata=strdata.simplified();
        strdata=strdata.trimmed();


        //qDebug() << strdata;
        if(strdata.contains(cadena_esperada.toUtf8())){
            qDebug()<<"Tenemos comunicacion";
            contadorPing=contadorPing+1;
            if(contadorPing==3)
            {
                contadorPing=0;
                //Env{ia el valor a PIT
                qDebug()<<"Se envia al PIT";
                emit sendToThreadPIT("#%#565");
            }

            //processPing->terminate();
        }

        else {
            if(strdata.length()>0)
                qDebug() << "Sin comunicacion";
        }





        if(i==5)
        {
            //qDebug()<<"Se realizara emit desde MainInterface"<<QThread::currentThread();

            emit sendToThreadCcom("mensaje 565");
            //emit prueba("nopos no sale");
            i=0;
        }



        //usleep(1000);
        i++;
    }
    //ccomThread.setStart();
}

void mainInterface::sendMensaje(QString mensaje)
{
    //ccomThread.sendMensaje(mensaje);
   // qDebug()<<mensaje<<QThread::currentThread();

    //pImageThread.recibeMensaje("%&%");
    emit sendToThreadCcom(mensaje);
    emit sendToThreadPIT(mensaje);
     cicloEsperaMensaje();
}

void mainInterface::receiveMessageFromPIT(QString mensaje)
{
    qDebug()<<"Mensaje recibido del Hilo PIT: "<<mensaje;
    //emit sendToThreadCcom(mensaje);
}

 void mainInterface::receivedMessageFromSocket(QString mensaje)
 {
    qDebug()<<"Mensaje Recibido del Socket: "<<mensaje;
 }

 void mainInterface::rightMessagePing()
 {
     //processPing->waitForReadyRead(100);
     //processPing->waitForFinished(100);
     QByteArray strdata = processPing->readAllStandardOutput();
     strdata=strdata.simplified();
     strdata=strdata.trimmed();

     QString cadena_esperada="64 bytes from";
     qDebug() << strdata;
     if(strdata.contains(cadena_esperada.toUtf8())){
         qDebug()<<"Tenemos comunicacion";

             processPing->terminate();
         }

     else {
         qDebug() << "Sin comunicacion";
     }
 }

 void mainInterface::startPing()
 {
 processPing->start("ping", QStringList() << "192.168.127.4");
 qint64 id=processPing->processId();
 qDebug() <<QString::number(id);
 }
