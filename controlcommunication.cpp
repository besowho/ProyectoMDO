#include "controlcommunication.h"

controlCommunication::controlCommunication()
{

}

// ====================================================================
// Connect with control computer
// ====================================================================
void controlCommunication::connectWithImageProcessingComputer()
{
    // -----------------------------------------------------------------------
    // Initialise ZMQ context and generate connections with image processing computer
    zmq_context_pt = nzmqt::createDefaultContext(this);
    zmq_context_ptsub = nzmqt::createDefaultContext(this);
    /*zmq_context_pt1 = nzmqt::createDefaultContext(this);
    zmq_context_pt2 = nzmqt::createDefaultContext(this);
    zmq_context_pt3 = nzmqt::createDefaultContext(this);
*/
    //Socket subscriber
    zmq_subscriber_pt = zmq_context_ptsub->createSocket(nzmqt::ZMQSocket::TYP_SUB);

    connect(zmq_subscriber_pt, SIGNAL(messageReceived(const QList<QByteArray>&)), this, SLOT(subscriber_process_received_message(const QList<QByteArray>&)));

    zmq_subscriber_pt->connectTo(SUBSCRIBER_CONNECT_TO);
    zmq_subscriber_pt->subscribeTo("");
    zmq_context_ptsub->start();


    //Socket publisher
    zmq_publisher_pt = zmq_context_pt->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    zmq_publisher_pt->bindTo(PUBLISHER_BIND_TO);
    zmq_context_pt->start();

/*
    //Socket publisher 1
    zmq_publisher_pt1 = zmq_context_pt1->createSocket(nzmqt::ZMQSocket::TYP_PUB);

    zmq_publisher_pt1->bindTo(PUBLISHER_BIND_TO1);
    zmq_context_pt1->start();

    //Socket publisher2
    zmq_publisher_pt2 = zmq_context_pt2->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    zmq_publisher_pt2->bindTo(PUBLISHER_BIND_TO2);
    zmq_context_pt2->start();

    //Socket publisher3
    zmq_publisher_pt3 = zmq_context_pt3->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    zmq_publisher_pt3->bindTo(PUBLISHER_BIND_TO3);
    zmq_context_pt3->start();

*/

}

// ====================================================================
// Process information received in the subscriber socket
// ====================================================================
void controlCommunication::subscriber_process_received_message(const QList<QByteArray> &message_list)
{
    // Get access to the first message in the list
    QByteArray message = message_list.at(0);
        // Transform to QString
        QString message_string = message;
        // Get a list of strings separed by commas from the message string
        /*QStringList message_string_list = message_string.split(",");
        // Get the number of strings found
        const int n_strings = message_string_list.size();
        // Check that we have received at least GCC01_SIZE strings, otherwise
        // do not proceed to the next step
        if (n_strings > GCC01_SIZE)
        {
            // Loop over the strings and store its value in the GCC01 vector
            // We started at 1 because the very first string is GCC01
            for(int i = 1; i < GCC01_SIZE + 1; i++)
            {
                QString string_at_i_position = message_string_list.at(i);
                GCC01[i-1]=string_at_i_position.toInt();
            }
        }*/
        qDebug() << "Mensaje recibido: "+ message_string;
        //emit sharedMessage(message_string);

       // publishMessage("Mensaje enviado por CONTROLCAMOBSDET");
}

/*void controlCommunication::send_Live_Signal()
{
    // Send the message
    qDebug()<<"Entro live Signal";
    zmq_publisher_pt->sendMessage("FCS10;");
}*/

void controlCommunication::publishMessage(QString message)
{
    QList<QByteArray> output_message;
    // Generate the 8 bit representation of the string
    output_message += message.toLocal8Bit();

    qDebug() << "Sent message: " << output_message;

    // Send the message
    zmq_publisher_pt->sendMessage(output_message);
}

/*
void controlCommunication::publishMessage1(QString message)
{
    QList<QByteArray> output_message;
    // Generate the 8 bit representation of the string
    output_message += message.toLocal8Bit();

    qDebug() << "Sent message: " << output_message;

    // Send the message
    zmq_publisher_pt1->sendMessage(output_message);
}

void controlCommunication::publishMessage2(QString message)
{
    QList<QByteArray> output_message;
    // Generate the 8 bit representation of the string
    output_message += message.toLocal8Bit();

    qDebug() << "Sent message: " << output_message;

    // Send the message
    zmq_publisher_pt2->sendMessage(output_message);
}

void controlCommunication::publishMessage3(QString message)
{
    QList<QByteArray> output_message;
    // Generate the 8 bit representation of the string
    output_message += message.toLocal8Bit();

    qDebug() << "Sent message: " << output_message;

    // Send the message
    zmq_publisher_pt3->sendMessage(output_message);
}*/

void controlCommunication::sendMensaje(QString mensaje)
{
    QList<QByteArray> output_message;
    // Generate the 8 bit representation of the string
    output_message += mensaje.toLocal8Bit();

    qDebug() << "Sent message 565: " << output_message;

    // Send the message
    zmq_publisher_pt->sendMessage(output_message);
}
