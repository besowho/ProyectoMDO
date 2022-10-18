#include "communicationthread.h"

CommunicationThread::CommunicationThread(QObject *parent)
    :QThread(parent)
{
    if(!isRunning())
    {
        start(NormalPriority);
    }
    else {
        //restart =true;
        condition.wakeOne();
    }
    /*mutex.lock();
    existeInstruccion=false;
    operacion=0;
    velocidad=0;
    mutex.unlock();*/


}

void CommunicationThread::setStart()
{
   // ccom.connectWithImageProcessingComputer();
}

void CommunicationThread::sendMensaje(QString mensaje)
{
    //ccom.sendMensaje(mensaje);
    
    if(!isRunning())
    {
        start(NormalPriority);
    }
    else {
        //restart =true;
        condition.wakeOne();
    }
    mutex.lock();
    mensajeRecibido=mensaje;
    newMensaje=true;
    mensajeRecibidoInt=1;
    mutex.unlock();

   // qDebug() << "Comunication Thread recibio el mensaje de MainInterface"<<QThread::currentThread();

}
void CommunicationThread::mensajeFromDecodificaMensaje(unsigned short *)
{

}

void CommunicationThread::run()
{
    //qDebug() << "Comunication Thread recibio el mensaje de MainInterface y entro al run"<<QThread::currentThread();

    //controlCommunication ccom;
    //ccom.connectWithImageProcessingComputer();
    int contador=0;
    forever
    {

        if (contador==1000000000)
        {
            //qDebug() << "Comunication Thread recibio el mensaje de MainInterface y entro al run"<<QThread::currentThread();
            mutex.lock();
            newMensaje=false;
            mensajeRecibidoInt=0;
            mutex.unlock();
            //ccom.sendMensaje(mensajeRecibido);

            //emit sendMensajeFromZocket("MensajeDelSocket");

            sendSignalMainInterface();
            contador=0;
        }
contador++;


           //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);


    }
}

void CommunicationThread::mensajeFromInterfazPrincipal(QString mensaje)
{
    if(!isRunning())
    {
        start(NormalPriority);
    }
    else {
        //restart =true;
        condition.wakeOne();
    }
    mutex.lock();
    mensajeRecibido=mensaje;
    newMensaje=true;
    mensajeRecibidoInt=1;
    mutex.unlock();

    //qDebug() << "Comunication Thread recibio el mensaje de MainInterface"<<mensaje<<QThread::currentThread();
}

void CommunicationThread::sendSignalMainInterface()
{

    emit sendMensajeFromZocket("MensajeDelSocket");
}
