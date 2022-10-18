#include "testping.h"


TestPing::TestPing(QObject *parent)
{
connect(&processPing, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessagePing()));

}

void TestPing::rightMessagePing()
{
    QByteArray strdata = processPing.readAllStandardOutput();
    strdata=strdata.simplified();
    strdata=strdata.trimmed();

    QString cadena_esperada="64 bytes from";
    qDebug() << strdata;
    if(strdata.contains(cadena_esperada.toUtf8())){
        qDebug()<<"Tenemos comunicacion";

            processPing.terminate();
        }

    else {
        qDebug() << "Sin comunicacion";
    }
}

void TestPing::startPing()
{
processPing.start("ping", QStringList() << "192.168.127.30");
qint64 id=processPing.processId();
qDebug() <<QString::number(id);
cicloEsperaMensaje();
}

void TestPing::cicloEsperaMensaje()
{
   //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);
    int i=0;
    forever
    {


        if(i==100000000)
        {

            i=0;
        }
        //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);


        //usleep(1000);
        i++;
    }
    //ccomThread.setStart();
}
