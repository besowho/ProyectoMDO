#include "processimagethread.h"

processImageThread::processImageThread(QObject * parent)
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
    alwaysOnTop=false;
    args << "/home/osboxes/Documents/Proyecto-MDO/scripts/alwaysOnTop.sh";
   // connect(&processPing, SIGNAL(readyReadStandardOutput()), this, SLOT(rightMessagePing()));
   // iniciaProcesoPing();
}



//void processImageThread::initSocketMavlink()
//{
//socketMavlink = new QUdpSocket(this);
//socketMavlink->bind(QHostAddress::LocalHost, 14551);
//connect(socketMavlink, &QUdpSocket::readyRead, this, &processImageThread::readMsgMavlink);
//}

//void processImageThread::readMsgMavlink()
//{
//    mavlink_status_t statusMavlink;
//    mavlink_message_t msgMavlink;
//    int channel = MAVLINK_COMM_0;

//    while(socketMavlink->hasPendingDatagrams())
//    {
//        QByteArray datagram;
//        datagram.resize(socketMavlink->pendingDatagramSize());
//        socketMavlink->readDatagram(datagram.data(),datagram.size());
//        QString str = QString(datagram.data());

//       if (mavlink_parse_char(channel, str, &msgMavlink, &statusMavlink))
//       {
//           printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msgMavlink.msgid, msgMavlink.seq, msgMavlink.compid, msgMavlink.sysid);
//       }

//        qDebug()<< "Data: " << str;

//    }
//}

void processImageThread::run()
{
    string s;
    stringstream ss;
    Mat channels[3];

    int contadorPrueba=0;

    //Image variables
    //Mat imageIn, imageGrayScale;
    Mat preprocessedImage;
    Mat preprocessedImage1D;
    unsigned int r = 480;
    unsigned int c = 640;
    double currentFrame;
    double totalFrames = 0;

    //Extra object detected
    bool extraObjectDetected = false;
    int extraObjectIndex = 0;

    //Colors
    //Scalar yellow = Scalar(0, 255, 255);
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    Scalar blue = Scalar(255, 255, 0);

    //Counting time
    double FPS = 0.0;
    char textFPS[12];
    long double sampleTime = 0;
    long double prevCount;
    long double time = 0.0;

    //Detector state struct
    struct0_T detectorState;
    struct0_T* detectorStatePtr;
    detectorState.use_prior_on_mixture = true;
    detectorState.use_uniform_component = true;
    detectorState.colorspace = ycrcb;
    detectorState.em_min_likelihood_delta = 0.01;
    detectorState.em_max_steps = 10;
    detectorState.is_initialized = false;
    detectorStatePtr = &detectorState;

    //Communication struct
    ssmDetection ssmDetectionStruct;

    //mavlink
    mavlinkProcess mp;
    mp.initSocketMavlink();
   // mp.readMsgMavlink();


    //Log file
    ofstream logFileText;
    char fileName[100];
    string temp1 = dateAndTime();
    const char *tempChar = temp1.c_str();
    sprintf(fileName,"/home/osboxes/Documents/Proyecto-MDO/Compiled-MDO/LOG_FILES/LOG_FILE_MDO_%s.txt", tempChar);
    logFileText.open(fileName);
    logFileText << "Alertas de colision registradas por el modulo de deteccion de objetos (MDO), proyecto ANGUILA:" << endl << endl;




// void Infusion::setPatientIdentifier(const QString& nric)
// {
//     ui->Patientidentifier->setText(nric);


    //**********************************************************************************************
    // APLICATION CONFIGURATION
    //**********************************************************************************************

    //Select 0 for video file, 1 for usb camera or 2 for IP camera
    unsigned int videoSource = 0;

    //Write video
    bool writeVideo = false; //Set true to record window

    //Show image
    bool showImage = true;

    //Full screen application
    bool fullScreen = false;

    //Input/output video
    string videoFileName = "/home/osboxes/Documents/Proyecto-MDO/SSM_TEST_VIDEO/VIDEO_TEST_SSM_03.avi";
    string outputVideoName = "//home/osboxes/Documents/Proyecto-MDO/SSM_OUTPUT_VIDEO/SSM_TEST_VIDEO_01.avi";
    //string ipCameraName = "rtsp://192.168.127.4/1/stream2";//"rtsp://169.254.118.117/1/stream2";

    //Collision alert threshold
    double collisionAlertThreshold = 0.3; //Can be changed externally

    //Operation mode, 0 for manual and 1 for automatic.
    bool operationMode = true; //Can be changed externally

    //Do image processing
    bool doImageProcessing = true;

    //Shut down computer flag
    bool shutDown = false; //Can be changed externally

    //**********************************************************************************************
    // END OF APLICATION CONFIGURATION
    //**********************************************************************************************

    //Collision alert variables
    unsigned int collisionAlertLineHeight;
    bool collisionAlert = false;
    bool collisionAlertPrev = false;

    //Video variables
    VideoWriter outputVideo(outputVideoName, VideoWriter::fourcc('M', 'P', 'E', 'G'), 20, Size(640,480));
    VideoCapture videoSequence;
    //VideoCapture camera;

    //Configuracion pin
    QByteArray strdata;
    QString cadena_esperada="64 bytes from";


    if (fullScreen && showImage)
    {
        namedWindow("MDO Anguila", WINDOW_FREERATIO);
        namedWindow("SSM TEST", WINDOW_NORMAL);
        //setWindowProperty("SSM TEST", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);


    }


    if(videoSource == 0)
    {
        //Open videosequence
        videoSequence.open(videoFileName);
        if (videoSequence.isOpened())
        {
            cout << "[OK] Video file was found." << endl;



        }
        else
        {
            cout <<  "[ERR] Video file was not found." << endl ;
            //565return 0;

        }

        //Get total number of frames
        totalFrames = videoSequence.get(CAP_PROP_FRAME_COUNT);

    }

    if(videoSource == 1)
    {
        unsigned int height = 480;
        unsigned int width = 640;
        if(camera.open(0))
        {
            camera.set(CAP_PROP_FRAME_HEIGHT, height);
            camera.set(CAP_PROP_FRAME_WIDTH, width);
            camera.set(CAP_PROP_FPS, 60);
            cout << "[OK] Web camera was found" << endl;
        }
        else
        {
            cout <<  "[ERR] Web camera was not found." << endl ;
            //565return 0;
        }
    }

    if(videoSource == 2)
    {
        if(camera.open(ipCameraName))
        {
            cout << "[OK] IP camera was found." << endl;
        }
        else
        {
            cout <<  "[ERR] IP camera was not found." << endl ;
            //565return 0;
        }
    }

    cout << "[OK] Ready to start Semantic Segmentation Model." << endl;

    forever//(;;)
    {
        contadorPrueba=contadorPrueba+1;

       //receive data mavlink
        mp.readMsgMavlink();


        //Time delay
        //usleep(5000);
        //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);

        //Counting time
        prevCount = getTickCount() * 1.0000;

        if(videoSource == 0)
        {
            //End loop if image reading fails
            if (!videoSequence.read(imageIn)) { break; };

            //Repeat video sequence continuously
            if (!writeVideo)
            {
                currentFrame = videoSequence.get(CAP_PROP_POS_FRAMES);
                if (currentFrame >= totalFrames) videoSequence.set(CAP_PROP_POS_FRAMES, 1);
            }

            resize(imageIn, imageIn, Size(640,480), INTER_LINEAR);
            if(contadorPrueba==100)
            {
               // cameraComStatus=false;
               // processPing.start("ping", QStringList() << "192.168.127.30");
                //QCoreApplication::processEvents();
               // qDebug()<<"inicia ping";
                //iniciaProcesoPing();
            }
        }

        if(videoSource == 1)
        {
            camera >> imageIn;
            //cout << "ImageIn.cols: " << imageIn.cols << ", imageIn.rows: " << imageIn.rows << endl;
            //resize(imageIn, imageIn, Size(640,480), INTER_LINEAR);
        }

        if(videoSource == 2 && cameraComStatus)
        {
            try{
                camera >> imageIn;
                //cout << "ImageIn.cols: " << imageIn.cols << ", imageIn.rows: " << imageIn.rows << endl;
                resize(imageIn, imageIn, Size(640,480), INTER_LINEAR);
            }
            catch(std::exception &e){
                qDebug()<<"entro al catch"<<&e;
                /*imageIn = cv::imread("/home/pi/Documents/imagenes/LOGO_UNINDETEC.png");
                resize(imageIn, imageIn, Size(640,480), INTER_LINEAR);
                textBox(imageIn, "UNINDETEC", 1, 0);
                textBox(imageIn, "SEMANTIC SEGMENTATION MODEL", 2, 0);
                textBox(imageIn, "VIDEO TEST", 3, 0);
                if (operationMode) textBox(imageIn, "OPERATION MODE: AUTOMATIC", 4, 0);
                else textBox(imageIn, "OPERATION MODE: MANUAL", 4, 0);
                textBox(imageIn, textFPS, 5, 0);
                if (collisionAlert) textBox(imageIn, "COLLISION ALERT", 6, 3);;
                textBox(imageIn, "COMMUNICATION ERROR", 7, 3);
                imshow("SSM TEST", imageIn);
                moveWindow("SSM TEST", 10,10 );*/
                cameraComStatus=false;
                camera.release();
                //iniciaProcesoPing();
                //processPing.start("ping", QStringList() << "192.168.127.4");
                //qint64 id=processPing.pid();
                //qDebug() <<QString::number(id);

            }

        }
        else
        {
            //qDebug()<<"Entro al else";
            if(cameraComStatus==false)
            {
               // qDebug()<<"Entro al bool";
                //Entra si la camara no se encuentra accesible
               /* processPing.waitForReadyRead(100);
                processPing.waitForFinished(100);
                strdata = processPing.readAllStandardOutput();
                strdata=strdata.simplified();
                strdata=strdata.trimmed();
                qDebug()<<"Obtenido del buffer" << strdata;
                if(strdata.contains(cadena_esperada.toUtf8())){
                    qDebug()<<"Tenemos comunicacion";

                    contadorPing=contadorPing+1;

                }

                else {
                    if(strdata.length()>0)
                        qDebug() << "Sin comunicacion";
                }*/



            }

        }

        //*****************************
        // IMAGE PROCESSING STARTS
        //*****************************

        if (doImageProcessing && cameraComStatus)
        {
            resize(imageIn, preprocessedImage, Size(50,50), INTER_LINEAR);
            cvtColor(preprocessedImage, preprocessedImage, COLOR_BGR2YCrCb);
            split(preprocessedImage, channels);

            //Debug
            /*imshow("preprocessedImage", preprocessedImage);
            cout << "Size of preprocessedImage: " << preprocessedImage.size() << endl;
            cout << "Number of channels of preprocessedImage: " << preprocessedImage.channels() << endl;
            cout << "Type of preprocessedImage: " << preprocessedImage.type() << endl;
            cout << "Number of channels of channels[0]: " << channels[0].channels() << endl;
            cout << "method 1: " << preprocessedImage.at<cv::Vec2b>(25,25)[0] << endl;
            cout << "method 2: " << preprocessedImage.at<uint8_T>(25,25,0) << endl;
            printf(" method 3: %d\n", channels[0].at<uint8_T>(25,25));
            cout << "method 4: " << channels[0].at<uint8_T>(25,25,0) << endl;*/

            int iy = -1;
            for (int c = 0; c<preprocessedImage.cols; c++)
            {
                for (int r = 0; r<preprocessedImage.rows; r++)
                {
                    iy++;
                    detectorState.Im_in[iy] = (double) channels[0].at<uint8_T>(r,c);
                }
            }
            for (int c = 0; c<preprocessedImage.cols; c++)
            {
                for (int r = 0; r<preprocessedImage.rows; r++)
                {
                    iy++;
                    detectorState.Im_in[iy] = (double) channels[2].at<uint8_T>(r,c);
                }
            }
            for (int c = 0; c<preprocessedImage.cols; c++)
            {
                for (int r = 0; r<preprocessedImage.rows; r++)
                {
                    iy++;
                    detectorState.Im_in[iy] = (double) channels[1].at<uint8_T>(r,c);
                }
            }

            ssmDetect(detectorStatePtr);

            //Adjust points of edge of the sea and saturation functions
            for(int i=0; i<detectorState.num_points; i=i+2)
            {
                detectorState.sel_xy[i] = detectorState.sel_xy[i] + 20;
                detectorState.sel_xy[i+1] = detectorState.sel_xy[i+1] - 10;

                if (detectorState.sel_xy[i]>c) detectorState.sel_xy[i] = c;
                if (detectorState.sel_xy[i]<=0) detectorState.sel_xy[i] = 1;

                if (detectorState.sel_xy[i+1]>r) detectorState.sel_xy[i+1] = r;
                if (detectorState.sel_xy[i+1]<=0) detectorState.sel_xy[i+1] = 1;
            }

            //Adjust (x,y) of objects and saturation functions
            for(int i = 0; i<detectorState.num_objects; i++)
            {
                detectorState.objects[i].bounding_box[0] = detectorState.objects[i].bounding_box[0] + 2;
                detectorState.objects[i].bounding_box[1] = detectorState.objects[i].bounding_box[1] - 5;

                if (detectorState.objects[i].bounding_box[0]>c) detectorState.objects[i].bounding_box[0] = c;
                if (detectorState.objects[i].bounding_box[0]<=0) detectorState.objects[i].bounding_box[0] = 1;

                if (detectorState.objects[i].bounding_box[1]>r) detectorState.objects[i].bounding_box[1] = r;
                if (detectorState.objects[i].bounding_box[1]<=0) detectorState.objects[i].bounding_box[1] = 1;
            }

            //If an extra object is detected, correct
            extraObjectDetected = false;
            for (int i = 0; i<detectorState.num_objects; i++)
            {
                if (floor(detectorState.objects[i].bounding_box[1]) == floor(detectorState.sel_xy[1]) || floor(detectorState.objects[i].bounding_box[1]) == floor(detectorState.sel_xy[1] + 1))
                {
                    extraObjectDetected = true;
                    extraObjectIndex = i;
                }
            }
            if (extraObjectDetected)
            {
                for (int i = extraObjectIndex; i<detectorState.num_objects; i++)
                {
                    detectorState.objects[i].bounding_box[0] = detectorState.objects[i+1].bounding_box[0];
                    detectorState.objects[i].bounding_box[1] = detectorState.objects[i+1].bounding_box[1];
                    detectorState.objects[i].bounding_box[2] = detectorState.objects[i+1].bounding_box[2];
                    detectorState.objects[i].bounding_box[3] = detectorState.objects[i+1].bounding_box[3];
                }
                detectorState.num_objects = detectorState.num_objects - 1;
            }

            //Collision alert
            if (collisionAlertThreshold > 0.9) collisionAlertThreshold = 0.9;
            if (collisionAlertThreshold < 0.1) collisionAlertThreshold = 0.1;
            collisionAlertLineHeight = floor(r - r * collisionAlertThreshold);
            collisionAlert = false;
            for(int i=0; i<detectorState.num_points*2; i=i+2)
            {
                if (detectorState.sel_xy[i+1] >= collisionAlertLineHeight) collisionAlert = true;
            }
            for(int i = 0; i<detectorState.num_objects; i++)
            {
                if (detectorState.objects[i].bounding_box[1] + detectorState.objects[i].bounding_box[3] >= collisionAlertLineHeight) collisionAlert = true;
            }

            //Write to communications structure
            ssmDetectionStruct.collisionAlert = collisionAlert;
            ssmDetectionStruct.collisionAlertThreshold = collisionAlertThreshold;
            ssmDetectionStruct.numPointsSeaEdge = detectorState.num_points;
            ssmDetectionStruct.numDetectedObjects = detectorState.num_objects;

            for(unsigned int i=0; i<200; i++)
            {
                ssmDetectionStruct.pointsSeaEdge[0][i] = 0;
                ssmDetectionStruct.pointsSeaEdge[1][i] = 0;
            }

            for(unsigned int i=0; i<ssmDetectionStruct.numPointsSeaEdge; i++)
            {
                ssmDetectionStruct.pointsSeaEdge[0][i] = detectorState.sel_xy[2*i];
                ssmDetectionStruct.pointsSeaEdge[1][i] = detectorState.sel_xy[2*i+1];
            }

            for(int i = 0; i<20; i++)
            {
                ssmDetectionStruct.detectedObjects[0][i] = 0;
                ssmDetectionStruct.detectedObjects[1][i] = 0;
                ssmDetectionStruct.detectedObjects[2][i] = 0;
                ssmDetectionStruct.detectedObjects[3][i] = 0;
            }

            for(int i = 0; i<detectorState.num_objects; i++)
            {
                ssmDetectionStruct.detectedObjects[0][i] = detectorState.objects[i].bounding_box[0];
                ssmDetectionStruct.detectedObjects[1][i] = detectorState.objects[i].bounding_box[1];
                ssmDetectionStruct.detectedObjects[2][i] = detectorState.objects[i].bounding_box[2];
                ssmDetectionStruct.detectedObjects[3][i] = detectorState.objects[i].bounding_box[3];
            }

            //Debug
            /*cout << "num_points: " << ssmDetectionStruct.numPointsSeaEdge << endl;
            cout << "num_objects: " << ssmDetectionStruct.numDetectedObjects << endl;
            //ss << detectorState.is_initialized;
            //ss >> s;
            //temp1 = detectorState.is_initialized;
            //cout << "is_initialized: " << temp1 << endl;
            for(unsigned int i=0; i<ssmDetectionStruct.numPointsSeaEdge; i++)
            {
                cout << "(" << ssmDetectionStruct.pointsSeaEdge[0][i] << ", " << ssmDetectionStruct.pointsSeaEdge[1][i] << "), ";
            }
            cout << endl << "***" << endl;
            for(unsigned int i = 0; i<ssmDetectionStruct.numDetectedObjects; i++)
            {
                cout << "("<< ssmDetectionStruct.detectedObjects[0][i] << ", " << ssmDetectionStruct.detectedObjects[1][i] << ", " << ssmDetectionStruct.detectedObjects[2][i] << ", " << ssmDetectionStruct.detectedObjects[3][i] << "), " << endl;
            }
            cout << "***" << endl;
            cout << "Extra object detected: " << extraObjectDetected << endl;*/

            /*cout << "num_points: " << detectorState.num_points << endl;
            cout << "num_objects: " << detectorState.num_objects << endl;
            //ss << detectorState.is_initialized;
            //ss >> s;
            //temp1 = detectorState.is_initialized;
            //cout << "is_initialized: " << temp1 << endl;
            for(int i=0; i<detectorState.num_points*2; i++)
            {
                cout << "(" << detectorState.sel_xy[i] << ", " << detectorState.sel_xy[i+1] << "), ";
            }
            cout << endl << "***" << endl;
            for(int i = 0; i<detectorState.num_objects; i++)
            {
                cout << "("<< detectorState.objects[i].bounding_box[0] << ", " << detectorState.objects[i].bounding_box[1] << ", " << ssmDetectionStruct.detectedObjects[i][2] << ", " << ssmDetectionStruct.detectedObjects[i][3] << "), " << endl;
            }
            cout << "***" << endl;
            cout << "Extra object detected: " << extraObjectDetected << endl;*/

            //Paint
            //cout << "Debug12" << endl;
            if (showImage && cameraComStatus)
            {
                //Paint edge of the sea
                for(int i=0; i<detectorState.num_points*2-2; i=i+2)
                {
                    line(imageIn, Point(detectorState.sel_xy[i], detectorState.sel_xy[i+1]), Point(detectorState.sel_xy[i+2], detectorState.sel_xy[i+3]), blue, 2);
                    //cout << "i: " << i << endl;
                }

                //Paint objects
                if (detectorState.num_objects > 0)
                {
                    for(int i = 0; i<detectorState.num_objects; i++)
                    {
                        rectangle(imageIn, Point(detectorState.objects[i].bounding_box[0], detectorState.objects[i].bounding_box[1]), Point(detectorState.objects[i].bounding_box[0]+detectorState.objects[i].bounding_box[2], detectorState.objects[i].bounding_box[1]+detectorState.objects[i].bounding_box[3]), green, 2);
                    }
                }

                //Paint collision alert threshold
                line(imageIn, Point(1, collisionAlertLineHeight), Point(c, collisionAlertLineHeight), red, 2);


                //Paint line position camera
                line(imageIn, Point(0,455), Point(640,455), green, 1);
                int position = 32;
                for (int n = 0; n<=20; n++)
                {
                    if (position <=640)
                    {
                    line(imageIn, Point(position,450), Point(position,460), green, 1);
                    position = position + 32;
                    }
                }
                int camPosition = QRandomGenerator::global()->bounded(0, 640);
                //center line
                //line(imageIn, Point(320,440), Point(320,470), blue, 1);
                //putText(imageIn, "0", Point(318,430), FONT_HERSHEY_DUPLEX, 0.3, blue, 1);

                line(imageIn, Point(camPosition,440), Point(camPosition,470), blue, 1);
                putText(imageIn, mp.getSurfaceBoatHeading().toStdString(), Point(camPosition-2,430), FONT_HERSHEY_DUPLEX, 0.3, blue, 1);


                //putText(imageIn, QString::number(camPosition).toStdString(), Point(camPosition-2,430), FONT_HERSHEY_DUPLEX, 0.3, blue, 1);





            }

            if (collisionAlert && !collisionAlertPrev)
            {
                logFileText << dateAndTime() << endl;
                alarma.startDetached("play", QStringList()<<"/home/osboxes/Music/02.wav");

            }
            collisionAlertPrev = collisionAlert;

        }
        //*****************************
        // IMAGE PROCESSING ENDS
        //*****************************

        //**********************************************************
        // Code for data transmission must be here:
        // - Transmision of structure: ssmDetectionStruct
        // - Reception of: double collisionAlertThreshold, bool operationMode, bool shutDown
        //**********************************************************
        if (contador == 60)
        {
            contador=0;
            //qDebug()<<"hilo PIT: "<<QThread::currentThread();
            //interfazPrincipal.sendMensaje("Hola desde SMS-TEST");
            QCoreApplication::processEvents();

            emit sendDetectedInformation("Mensaje enviado desde hilo dectec information");

            //QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);

        }
        else
            contador++;




        //**********************************************************
        // End code for data transmission must be here:
        // - Transmision of structure: ssmDetectionStruct
        // - Reception of: double collisionAlertThreshold, bool operationMode, bool shutDown
        //**********************************************************

        //Calculate FPS
        sprintf(textFPS, "FPS: %.2f", FPS);
        if (!showImage)
        {
            cout << "Running SSM! FPS: " << FPS << "\r";
        }

        //Labels
        if (showImage && cameraComStatus)
        {

            textBox(imageIn, "UNINDETEC", 1, 0);
            textBox(imageIn, "SEMANTIC SEGMENTATION MODEL", 2, 0);
            textBox(imageIn, "VIDEO TEST", 3, 0);

            if (operationMode) textBox(imageIn, "OPERATION MODE: AUTOMATIC", 4, 0);
            else textBox(imageIn, "OPERATION MODE: MANUAL", 4, 0);
            textBox(imageIn, textFPS, 5, 0);
            if (collisionAlert) {
                textBox(imageIn, "COLLISION ALERT", 6, 3);
                //alarma.startDetached("play", QStringList()<<"/home/osboxes/Music/01.wav");
            }



        }

        //Write video
        if (writeVideo && cameraComStatus)
        {
            outputVideo.write(imageIn);
        }

        //Show results
        if (showImage && cameraComStatus)
        {
            imshow("SSM TEST", imageIn);
            moveWindow("SSM TEST", 10,10 );
            if(!alwaysOnTop)
            {
                process.start("sh", args);
                alwaysOnTop=true;

            }
            //setWindowProperty("SSM TEST", WND_PROP_TOPMOST, 5);

            if (waitKey(1) > 0) break;
        }

        if (shutDown)
        {
            break;
        }

        //Counting time
        time += sampleTime;
        if (sampleTime > 0) FPS = 1/sampleTime;
        sampleTime = (getTickCount()*1.0000 - prevCount) / (getTickFrequency() * 1.0000);

        /*if (contadorPing == 10)
        {
            cameraComStatus=true;
            contadorPing=0;
            processPing.terminate();
        }*/

    }

    waitKey(0);
    camera.release();
    outputVideo.release();
    logFileText.close();
    destroyAllWindows();
    if (shutDown) system("shutdown -h now"); //Shut down computer
    //565return 0;
}

//Textbox function
void processImageThread::textBox(Mat inputImage, string text, unsigned int textLine, unsigned short textColor)
{
    int fontFace = FONT_HERSHEY_DUPLEX;
    double fontScale = 0.4;
    int thickness = 1;
    int baseline=0;
    Scalar color;

    if (textColor==0 || textColor > 3) {color = Scalar(255, 255, 255);}; //LABEL_COLOR
    if (textColor==1) {color = Scalar(0, 255, 0);};                      //NORMAL COLOR
    if (textColor==2) {color = Scalar(0, 255, 255);};                    //WARNING_COLOR
    if (textColor==3) {color = Scalar(0, 139, 255);};                    //ERROR COLOR

    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;

    // Center the text if desired
    // Point textOrg((inputImage.cols - textSize.width)/2, (inputImage.rows + textSize.height)/2);

    Point textOrg(5, textLine*15);

    // draw the box
    rectangle(inputImage, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height) - Point(0,3), Scalar(225,105,65), FILLED, 8, 0);

    // Add baseline if desired
    //line(inputImage, textOrg + Point(0, thickness), textOrg + Point(textSize.width, thickness), Scalar(0, 0, 255));

    // then put the text itself
    putText(inputImage, text, textOrg, fontFace, fontScale, color, thickness);
}

//Get date and time
string processImageThread::dateAndTime()
{
    time_t now;
    tm *ltm;

    char dateAndTimeText[200];
    char hourChar[20];
    char minChar[20];
    char secChar[20];
    char dayChar[20];
    char monthChar[20];

    now = time(0);
    ltm = localtime(&now);
    int hour = ltm->tm_hour; if (hour<10){ sprintf(hourChar,"0%d", ltm->tm_hour); } else {sprintf(hourChar,"%d", ltm->tm_hour);};
    int min = ltm->tm_min; if (min<10){ sprintf(minChar,"0%d", ltm->tm_min); } else {sprintf(minChar,"%d", ltm->tm_min);};
    int sec = ltm->tm_sec; if (sec<10){ sprintf(secChar,"0%d", ltm->tm_sec); } else {sprintf(secChar,"%d", ltm->tm_sec);};
    int day = ltm->tm_mday; if (day<10){ sprintf(dayChar,"0%d", ltm->tm_mday); } else {sprintf(dayChar,"%d", ltm->tm_mday);};
    int month = 1 + ltm->tm_mon; if (month<10){ sprintf(monthChar,"0%d", 1 + ltm->tm_mon); } else {sprintf(monthChar,"%d", 1 + ltm->tm_mon);};

    sprintf(dateAndTimeText,"Fecha_D-M-A_%s-%s-%d_Hora_H-M-S_%s-%s-%s", dayChar, monthChar, 1900 + ltm->tm_year, hourChar, minChar, secChar);
    return string(dateAndTimeText);
}

void processImageThread::getConfigureInformation(QString mensaje)
{
    if(!isRunning())
    {
        start(NormalPriority);
    }
    else {
        //restart =true;
       // condition.wakeOne();
    }
    //qDebug()<<"Hilo recibio mensaje en SLOT: "<<mensaje<<QThread::currentThread();
    //cameraComStatus=true;
    if(cameraComStatus==false)
    {
        if(camera.open(ipCameraName) )
        {
            cout << "[OK] IP camera was found." << endl;
            /*for(int i=0;i<1000000;i++)
            {

            }*/
            camera >> imageIn;
            //cout << "ImageIn.cols: " << imageIn.cols << ", imageIn.rows: " << imageIn.rows << endl;
            resize(imageIn, imageIn, Size(640,480), INTER_LINEAR);
            cameraComStatus=true;
        }
        else
        {
            cout <<  "[ERR] IP camera was not found." << endl ;
            //565return 0;
        }
    }
}


void processImageThread::recibeMensaje(QString mensaje)
{
    //qDebug()<<"Hilo recibio mensaje: "<<mensaje;
}


void processImageThread::rightMessagePing()
{
    QByteArray strdata = processPing.readAllStandardOutput();
    strdata=strdata.simplified();
    strdata=strdata.trimmed();

    QString cadena_esperada="64 bytes from";
    qDebug() << strdata;
    if(strdata.contains(cadena_esperada.toUtf8())){
        qDebug()<<"Tenemos comunicacion";
        contadorCameraCom=contadorCameraCom + 1;
        if(contadorCameraCom==5)
        {
            contadorCameraCom=0;
            cameraComStatus=true;
            processPing.terminate();
        }
    }
    else {
        qDebug() << "Sin comunicacion";
    }
}

void processImageThread::iniciaProcesoPing()
{
    processPing.start("ping", QStringList() << "192.168.127.4");
    qint64 id=processPing.processId();
    qDebug() <<QString::number(id);

}
