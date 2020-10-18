/**
*  @filename   :   TCP_IP.cpp
*  @brief      :   TCP_IP Testing
*  @author     :   Kaloha from Waveshare
*
*  Copyright (C) Waveshare     May 24 2018
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

#include "arduPi.h"
#include "sim7x00.h"
#include "sim7000.h"

//#define DEBUG_SIM7X00    1
//#define DEBUG_SIM7000    1

sim7000 SIM7000X = sim7000();

void setup() {
	char* apn;
	SIM7000X.Power_On();

	SIM7000X.Get_Signal_Value();
	apn = SIM7000X.Get_Supported_APN();
	if(SIM7000X.Set_Network_APN(apn))
	{
		printf("Setting network apn to %s successfully.\n",apn);
	}else if(SIM7000X.Get_Current_APN(apn)){
		printf("Current network apn is %s.\n",apn);
	}else{
		printf("Setting network apn to %s failed.\n",apn);
	}

	SIM7000X.Bring_Up_Connection();
	SIM7000X.Get_Local_IP();
	SIM7000X.Open_Socket_Client("TCP","113.81.232.178",1822);
	SIM7000X.Send_Data("Waveshare",9);
	SIM7000X.Receiving_Data(10000);
	SIM7000X.Close_Connect();
}

void loop() {
}

int main() {
	setup();
	while (1) {
		loop();
	}
	return (0);
}