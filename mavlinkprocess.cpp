#include "mavlinkprocess.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_LENGTH 2041
uint64_t microsSinceEpoch();

mavlinkProcess::mavlinkProcess(QObject *parent)
    :QObject(parent)
{
//    if(!isRunning())
//    {
//        start(NormalPriority);
//    }
}
QString SurfaceBoatHeading;

uint64_t microsSinceEpoch()
{

    struct timeval tv;

    uint64_t micros = 0;

    gettimeofday(&tv, NULL);
    micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

    return micros;
}

void mavlinkProcess::initSocketMavlink()
    {
    socketMavlink = new QUdpSocket(this);
    socketMavlink->bind(QHostAddress::LocalHost, 14551);
    connect(socketMavlink, &QUdpSocket::readyRead, this, &mavlinkProcess::readMsgMavlink);

    }



void mavlinkProcess::readMsgMavlink()
    {

        mavlink_status_t statusMavlink;
        mavlink_message_t msgMavlink;
        uint8_t channel = MAVLINK_COMM_0;
        QByteArray datagram;

        while(socketMavlink->hasPendingDatagrams())
        {

            datagram.resize(socketMavlink->pendingDatagramSize());
            socketMavlink->readDatagram(datagram.data(),datagram.size());
            //datagram.resize(socketMavlink->pendingDatagramSize());

           // QString::number(camPosition).toStdString()


          mavlink_msg_heartbeat_pack(255,190, &msgMavlink, MAV_TYPE_SURFACE_BOAT, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_DISARMED, 0, MAV_STATE_ACTIVE);
           //mavlink_msg_heartbeat_pack_chan(255, 190, channel, &msgMavlink, MAV_TYPE_SURFACE_BOAT, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_DISARMED, 0, MAV_STATE_ACTIVE);
           //mavlink_msg_to_send_buffer(, &msgMavlink);
           //mavlink_msg_sys_status_pack(ac_id, 1, &msgMavlink, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);

//              uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
//              int lenght = mavlink_msg_to_send_buffer(buffer, &msgMavlink);

             // if (!lenght) return;
              //socketMavlink->sendData(QByteArray((const char*)buffer, lenght));
             //  socketMavlink->writeDatagram(QByteArray((const char*)buffer, lenght), QHostAddress::LocalHost, 14551);


            printf("Received HEARTBEAT from %d compid %d mode %d\n",msgMavlink.sysid, msgMavlink.compid, mavlink_msg_heartbeat_get_autopilot(&msgMavlink));
            printf("Received MSG %d\n",msgMavlink.msgid);

           for (int pos=0; pos<datagram.length(); ++pos)
           {
                if (!mavlink_parse_char(channel, (uint8_t)datagram[pos], &msgMavlink, &statusMavlink))
                {
                    switch(msgMavlink.msgid)
                     {
                    case MAVLINK_MSG_ID_HEARTBEAT:
                               printf("Sats: %d\n", mavlink_msg_gps_status_get_satellites_visible(&msgMavlink));
                               printf("Received Heading: %d\n", mavlink_msg_vfr_hud_get_heading(&msgMavlink));
                               printf("\nReceived Speed: %f\n", mavlink_msg_vfr_hud_get_groundspeed(&msgMavlink));
                        break;
                    }
                }
           }
        }

          /*
            for (int pos=0; pos<datagram.length(); pos++)
           {

               if (!mavlink_parse_char(channel, (uint8_t)datagram[pos], &msgMavlink, &statusMavlink))
               {

                  switch(msgMavlink.msgid)
                   {
                  case MAVLINK_MSG_ID_HEARTBEAT:
                         //qDebug()<< "msid: " << msgMavlink.msgid;
                          printf("\n Sats: %d\n", mavlink_msg_gps_status_get_satellites_visible(&msgMavlink));
                       //printf("\nReceived HEARTBEAT from %d compid %d mode %d\n",msgMavlink.sysid, msgMavlink.compid, mavlink_msg_heartbeat_get_autopilot(&msgMavlink));
                       //printf("\nReceived GPS Lat: %d\n", mavlink_msg_global_position_int_get_lat(&msgMavlink));
                       //printf("\nReceived GPS Long: %d\n", mavlink_msg_global_position_int_get_lon(&msgMavlink));
                     //  printf("\nReceived Heading: %d\n", mavlink_msg_vfr_hud_get_heading(&msgMavlink));
                      // printf("\nbattery: %f\n", mavlink_msg_power_status_get_Vcc( &msgMavlink));

                      printf("Heading: %f\n", mavlink_msg_global_vision_position_estimate_get_yaw(&msgMavlink));
                       SurfaceBoatHeading = QString::number(mavlink_msg_global_vision_position_estimate_get_yaw(&msgMavlink));


                       //mode = mavlink_msg_set_mode_get_base_mode(&msgMavlink);
//                       switch (mavlink_msg_set_mode_get_base_mode(&msgMavlink))
//                       {
//                         case 0: printf("\nMODO: PREFLIGHT\n"); break;
//                         case 64: printf("\nMODO: MANUAL DISARMED\n"); break;
//                         case 192: printf("\nMODO: MANUAL ARMED\n"); break;
//                         case 92: printf("\nMODO: AUTO DISARMED\n"); break;
//                         case 220: printf("\nMODO: AUTO ARMED\n"); break;
//                       }

                      continue;
                  case MAVLINK_MSG_ID_ATTITUDE:
                      printf("\n Heading: %f\n", mavlink_msg_attitude_get_yaw(&msgMavlink));
//                   default:
//                      printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msgMavlink.msgid, msgMavlink.seq, msgMavlink.compid, msgMavlink.sysid);
//                       printf("\nReceived Heading: %d\n", mavlink_msg_vfr_hud_get_heading(&msgMavlink));
//                       printf("\nReceived Speed: %f\n", mavlink_msg_vfr_hud_get_groundspeed(&msgMavlink));
//                      SurfaceBoatHeading = QString::number(mavlink_msg_vfr_hud_get_heading(&msgMavlink));
//                       //printf("\nbattery: %f\n", mavlink_msg_power_status_get_Vcc( &msgMavlink));

                      continue;
                 case MAVLINK_MSG_ID_GPS_STATUS:
                       printf("\n Sats: %d\n", mavlink_msg_gps_status_get_satellites_visible(&msgMavlink));

                      continue;

                   }

               }
           }
        */

           //qDebug()<< "Data: " << datagram.data();

       // }

/*

    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        struct sockaddr_in gcAddr;
        struct sockaddr_in locAddr;
        //struct sockaddr_in fromAddr;
        uint8_t buf[BUFFER_LENGTH];
        ssize_t recsize;
        socklen_t fromlen = sizeof(gcAddr);
        int bytes_sent;
        mavlink_message_t msg;
        uint16_t len;
        int i = 0;
        unsigned int temp = 0;

//        memset(&locAddr, 0, sizeof(locAddr));
//            locAddr.sin_family = AF_INET;
//            locAddr.sin_addr.s_addr = INADDR_ANY;
//            locAddr.sin_port = htons(14551);


//            //* Bind the socket to port 14551 - necessary to receive packets from qgroundcontrol
//            if (-1 == bind(sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
//            {
//                perror("error bind failed");
//                close(sock);
//                exit(EXIT_FAILURE);
//            }

            memset(&gcAddr, 0, sizeof(gcAddr));
                gcAddr.sin_family = AF_INET;
                gcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
                gcAddr.sin_port = htons(14550);

//                        //Send Heartbeat
                        mavlink_msg_heartbeat_pack(1, 1, &msg, MAV_TYPE_SURFACE_BOAT, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_DISARMED, 0, MAV_STATE_ACTIVE);
                        len = mavlink_msg_to_send_buffer(buf, &msg);
                        sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));

                        // Send Status
                        mavlink_msg_sys_status_pack(1, 1, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                        len = mavlink_msg_to_send_buffer(buf, &msg);
                        sendto(sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof (struct sockaddr_in));

                        memset(buf, 0, BUFFER_LENGTH);
                                recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);
                                if (recsize > 0)
                                {
                                    // Something received - print out all bytes and parse packet
                                    mavlink_message_t msg;
                                    mavlink_status_t status;

                                    printf("Bytes Received: %d\nDatagram: ", (int)recsize);
                                    for (i = 0; i < recsize; ++i)
                                    {
                                        temp = buf[i];
                                        printf("%02x ", (unsigned char)temp);
                                        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
                                        {
                                            // Packet received
                                            printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
                                            switch(msg.msgid)
                                             {
                                            case MAVLINK_MSG_ID_HEARTBEAT:
                                                   //qDebug()<< "msid: " << msgMavlink.msgid;
                                                    printf("\n Sats: %d\n", mavlink_msg_gps_status_get_satellites_visible(&msg));
                                            break;
                                            }
                                        }
                                    }
                                    printf("\n");
                                }
                                memset(buf, 0, BUFFER_LENGTH);
                                //sleep(1); // Sleep one second

*/
}

void mavlinkProcess::sendHeartBeat()
    {
//        mavlink_msg_heartbeat_pack(1,200, &msgMavlink, MAV_TYPE_SURFACE_BOAT, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_DISARMED, 0, MAV_STATE_ACTIVE);

    }

QString mavlinkProcess::getSurfaceBoatHeading()
{

    return SurfaceBoatHeading;

}

