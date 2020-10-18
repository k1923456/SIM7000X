/**
*  @filename   :   sim7000.h
*  @brief      :   Implements for waveshare SIM7000X NB-IoT HAT
*  @author     :   Kaloha from Waveshare
*
*  Copyright (C) Waveshare     May 25 2018
*  http://www.waveshare.com / http://www.waveshare.net
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

#ifndef sim7000_h
#define sim7000_h

#include "sim7x00.h"
#include "arduPi.h"
//#include "sim7000_at_cmd.h"

#define DEBUG_SIM7000 0

/* sim7x00 Class */
class sim7000 : public sim7x00 {

public:
	// GPS positoning
	bool GPS_Positioning(void);
	char* Get_Latitude(const char* gps_buffer);
	char* Get_Longitude(const char* gps_buffer);
	char* Get_UTC_Time(const char* gps_buffer);

	//TCP IP communication
	int  Get_Signal_Value(void);
	char* Get_Supported_APN(void); 
	bool Get_Current_APN(const char* current_apn);
	bool Set_Network_APN(const char* apn);
	bool Bring_Up_Connection(void);
	bool Get_Local_IP(void);
	bool Open_Socket_Client(const char* protocol, const char* remote_ip, unsigned int remote_port);
	bool Send_Data(char* data, unsigned int len);
	bool Send_Data(char* data);
	void Receiving_Data(unsigned int timeout);
	bool Close_Connect(void);
	//bool 
	
	//MQTT communication using TCP
	//MQTT

private:
	char _utc_time[15];
	char _latitude[10];
	char _longitude[11];
	char _apn[10];
	char _local_ip[30];
};

#endif
