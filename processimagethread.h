#ifndef PROCESSIMAGETHREAD_H
#define PROCESSIMAGETHREAD_H

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
#include <QProcess>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <mavlinkprocess.h>


extern "C" {
    #include <ssmDetect/ssmDetect.h>
}

using namespace std;
using namespace cv;

class processImageThread : public QThread
{
    Q_OBJECT

public:
    processImageThread(QObject *parent = nullptr);
    void textBox(Mat inputImage, string text, unsigned int textLine, unsigned short textColor);
    void iniciaProcesoPing();
    string dateAndTime();
    void recibeMensaje(QString);
    QProcess process, processPing, alarma;
    bool alwaysOnTop;
    QStringList args;



signals:
    void sendDetectedInformation(QString );

public slots:
    void getConfigureInformation(QString);
    void rightMessagePing();



protected:
    void run() override;

private:


    QMutex mutex;
    QWaitCondition condition;
    int mensajeRecibidoInt=0;
    QString mensajeRecibido, mensajeAux;
    bool newMensaje=false;
    Mat imageIn, imageGrayScale;
    struct ssmDetection{
        unsigned int pointsSeaEdge[2][200];
        unsigned int numPointsSeaEdge;
        unsigned int detectedObjects[4][20];
        unsigned int numDetectedObjects;
        double collisionAlertThreshold;
        bool collisionAlert = false;
    };

    //variables de control para comunicacion
    bool enviaMensaje = false;
    int contador = 0; // cada 6o ciclos enviar un mensaje
    bool cameraComStatus=true;
    int contadorCameraCom=0;
    int contadorPing=0;
    VideoCapture camera;
     string ipCameraName = "rtsp://192.168.127.4/1/stream2";


};

#endif // PROCESSIMAGE_H
