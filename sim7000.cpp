/**
*  @filename   :   sim7000.cpp
*  @brief      :   Implements for waveshare SIM7000X NB-IoT HAT
*  @author     :   Kaloha from Waveshare
*
*  Copyright (C) Waveshare     May 27 2018
*  http://www.waveshare.com  http://www.waveshare.net
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documnetation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to  whom the Software is
* furished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/


#include "sim7000.h"


bool sim7000::GPS_Positioning(void){

    printf("Ready for GPS positioning,\n");
    printf("please connect the GPS antenna and place it outdoors\n");

    if(Send_AT_Command("AT+CGNSPWR=1",2000,"OK") == 1)    //Turn on the GNSS power.
    {
        //Prepare to get gps position messages.
        char answer = 0, x = 0;
        char gps_buffer[200];
        memset(gps_buffer,'\0',200);

        delay(2000);

        while(answer == 0)
        {

            if(Send_AT_Command("AT+CGNSINF",2000,"+CGNSINF: ")==1)
            {
                while(Serial.available()==0);

                do
                {
                    if(Serial.available()>0)
                        gps_buffer[x++] = Serial.read();

                    if(strstr(gps_buffer,"OK") != NULL)
                    {
                        if(strstr(gps_buffer,",,,,,") == NULL)
                        {
                            gps_buffer[x]='\0';
                            printf("The GPS position message is:\n");
                            printf("%s\n",gps_buffer);
                            answer = 1;
                        }else{
                            printf("%s\n",gps_buffer);
                            printf("The GPS position message is not correct,please waiting...\n");
                            memset(gps_buffer,'\0',x);
                            x = 0;
                            delay(2000);
                        }  
                    }
                }while((answer == 0)&&(x > 0));
            }
        }

        

        if(answer == 1)
        {
            Get_UTC_Time(gps_buffer);
            Get_Latitude(gps_buffer);
            Get_Longitude(gps_buffer);
        }
        
        if(Send_AT_Command("AT+CGNSPWR=0",2000,"OK") == 1)
            printf("Turn off the GNSS power.\n");
        return true;
    }
    return false;
}


char* sim7000::Get_UTC_Time(const char* gps_buffer){

    memset(_utc_time,'\0',15);
    strncpy(_utc_time, gps_buffer+4, 14);
    _utc_time[14] = '\0';
    printf("UTC time is :%s\n",_utc_time);
    return _utc_time;
}

char* sim7000::Get_Latitude(const char* gps_buffer){

    memset(_latitude,'\0',10);
    strncpy(_latitude, gps_buffer+23, 9);
    _latitude[9] = '\0';
    printf("Latitude is :%s\n",_latitude);
    return _latitude;
}

char* sim7000::Get_Longitude(const char* gps_buffer){

    memset(_longitude,'\0',11);
    strncpy(_longitude, gps_buffer+33, 10);
    _longitude[10] = '\0';
    printf("Longitude is :%s\n",_longitude);
    return _longitude;
}

//
int  sim7000::Get_Signal_Value(void)
{
    char signal_value1[30], signal_value2[3];
    char x = 0, answer = 0;
    int signal_value = 0;
    unsigned long int timeout = 5000,pre_time = 0;
    memset(signal_value1,'\0',30);
    memset(signal_value2,'\0',3);

    pre_time = millis();

    if(Send_AT_Command("AT+CSQ",1000,"+CSQ: ") == 1)
    {

        while(Serial.available()==0);

        do
        {
            if(Serial.available()>0)
            {
                signal_value1[x++] = Serial.read();
            }

            if(strstr(signal_value1,"OK") != NULL)
            {
                signal_value1[x]='\0';
                for(char j=0; (j<=2) && (signal_value1[j] != ','); j++ )
                    signal_value2[j] = signal_value1[j];
                signal_value = atoi(signal_value2);
//                printf("%s\n",signal_value1);
                printf("The signal value is:%d\n",signal_value);
                answer = 1;
            }
        }while((answer == 0)&&((millis()-pre_time)<timeout));
    }
    
    if(answer == 0){
        printf("Get the signal quality value failed.\n");
        return 0;
    }

    return signal_value;
}

char* sim7000::Get_Supported_APN(void){
    char network_apn[30];
    char x = 0, answer = 0;
    char* y;
    unsigned long int timeout = 5000,pre_time = 0;
    memset(network_apn,'\0',30);
    memset(_apn,'\0',10);

    pre_time = millis();

    if(Send_AT_Command("AT+CGNAPN",2000,"+CGNAPN: ") == 1)
    {
        while(Serial.available()==0);

        do
        {
            if(Serial.available()>0)
            {
                network_apn[x++] = Serial.read();
            }

            if(strstr(network_apn,"OK") != NULL)
            {
                network_apn[x]='\0';
                y = strstr(network_apn,"\"");

                for(char j=0; (*(y+j+1) != '"'); j++)
                    _apn[j] = *(y+j+1);

 //               printf("%s\n",network_apn);
                printf("The valid apn is:%s\n",_apn);
                answer = 1;
            }
        }while((answer == 0)&&((millis()-pre_time)<timeout));
    }
    if(answer == 0){
        printf("Get the network apn failed.\n");
        return "error";
    }
    return _apn;
}

bool sim7000::Get_Current_APN(const char* current_apn){
    char response[30];
    char answer = 0, x = 0;
    unsigned long int pre_time = 0;

    memset(response,'\0',30);

    if(Send_AT_Command("AT+CSTT?",2000,"+CSTT: ") == 1)
    {
        while(Serial.available()==0);

        do
        {
            if(Serial.available()>0)
            {
                response[x++] = Serial.read();
            }

            if(strstr(response,current_apn) != NULL)
            {
                return true;
            }
        }while((answer == 0)&&((millis()-pre_time)<3000));
    }

    return false;
}

bool sim7000::Set_Network_APN(const char* apn)
{
    char apn_cmd[30];
    sprintf(apn_cmd,"AT+CSTT=\"%s\"", apn);
//    printf("%s\n",apn_cmd);
    if(Send_AT_Command(apn_cmd,2000,"OK","ERROR") == 1)
    {
        return true;
    }else{
        return false;
    }
}

bool sim7000::Bring_Up_Connection(void)
{
    if(Send_AT_Command("AT+CIICR",2000,"OK","ERROR") == 1)
    {
        printf("Bring up wireless connect successfully!\n");
        return true;
    }else{
        printf("Bring up wireless connect failed!\n");
        return false;
    }
}

bool sim7000::Get_Local_IP(void){
    char response[30];
    char* ip;
    memset(response, '\0', 30);
    memset(_local_ip, '\0', 30);

    delay(100);

    Serial.println("AT+CIFSR");

    if(Get_Serial_Response(response,1000,"ERROR")!=1)
    {
        if(strstr(response,"1") != NULL)
        {
            ip = strstr(response,"1");
        }
        else if(strstr(response,"2") != NULL)
        {
            ip = strstr(response,"1");
        }
        else{
            return false;
        }

        strncpy(_local_ip,ip,30);
        printf("Local IP is %s\n",_local_ip);
    }
        
    return true;
}


bool sim7000::Open_Socket_Client(const char* protocol, const char* remote_ip, unsigned int remote_port){
    char aux_str[50];
    char* ip;
    memset(aux_str, '\0', 50);

    sprintf(aux_str,"AT+CIPSTART=\"%s\",\"%s\",%d", protocol, remote_ip, remote_port);

    if(Send_AT_Command(aux_str, 5000, "CONNECT OK") == 1){
        printf("Start up %s connection, remote server is:%s:%d\n",protocol, remote_ip, remote_port);
        return true;
    }else{
        return false;
    }
}

bool sim7000::Send_Data(char* data, unsigned int len){

    char aux_str[20];
    memset(aux_str, '\0', 20);
    sprintf(aux_str,"AT+CIPSEND=%d",len);   


    
    if(Send_AT_Command(aux_str,3000,">") == 1){

        if(Send_AT_Command(data,5000,"SEND OK","FAIL")==1){
            printf("Send data:\"%s\" successfully.\n",data);
            return true;
        }
    }

    #if DEBUG_SIM7X00>0
        printf("Send data failed.\n");
    #endif
    
    return false;
    
}

bool sim7000::Send_Data(char* data){
    
    return(Send_Data(data, sizeof(data)));
}

bool sim7000::Close_Connect(void){

    Send_AT_Command("AT+CIPCLOSE=1",5000,"OK","ERROR");
    if(Send_AT_Command("AT+CIPSHUT",5000,"OK")==1){
        printf("Close connect successfully.\n");
        return true;
    }else{
        printf("Close connect failed.\n");
        return false;
    }
}

void sim7000::Receiving_Data(unsigned int timeout){

    uint8_t x=0;
    unsigned long previous;
    char response;

    printf("Start receiving data for %d seconds\n",timeout/1000);
    previous = millis();   

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial.available() != 0){    
            response = Serial.read();
            printf("%c",response);
        }
    }while((millis() - previous) < timeout);  
    printf("\n");

}