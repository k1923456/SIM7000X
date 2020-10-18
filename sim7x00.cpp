/**
*  @filename   :   sim7x00.cpp
*  @brief      :   Implements for sim7x00 Serial library
*  @author     :   Kaloha from Waveshare
*
*  Copyright (C) Waveshare     May 24 2018
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


#include "sim7x00.h"
#include "arduPi.h"

int sim7x00::POWERKEY=4;

sim7x00::sim7x00(){
}

sim7x00::~sim7x00(){
}


/**************************Power on Module**************************/
bool sim7x00::Power_On(int power_key){
    char answer  = 0, count = 0;

	Serial.begin(115200);

	// checks if the module is started
	answer = Send_AT_Command("AT", 1000, "OK");
	if (answer == 0)
	{
		printf("Starting up...\n");

		pinMode(power_key, OUTPUT);
		// power on pulse
		digitalWrite(power_key, HIGH);
		delay(200);
		digitalWrite(power_key, LOW);

		// waits for an answer from the module
		while ((answer == 0)&&(count++<10)) {
            delay(2000);     
			answer = Send_AT_Command("AT", 1000, "OK");   // Send AT every two seconds and wait for the answer
		}
	}

     if(answer == 1)
    {
        printf("Module is ready.\n");
        return true;
    }

    printf("Module communiction failed,\n");
    printf("Please check if the module is not powered or not set to the default baud rate:115200\n");
    return false;

}

bool sim7x00::Power_On()
{
    return Power_On(POWERKEY);
}


/**************************Send AT command and check for the answers**************************/
char sim7x00::Send_AT_Command(const char* at_command, unsigned int timeout, const char* expected_answer1, const char* expected_answer2){
	uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial.available() > 0) Serial.read();    // Clean the input buffer

    Serial.println(at_command);    // Send the AT command 

    previous = millis();   

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial.available() != 0){    
            response[x] = Serial.read();

            if(expected_answer1 != "")
            {
                // check if the desired answer 1  is in the response of the module
                if (strstr(response, expected_answer1) != NULL)   
                {
                    answer = 1;
                }
                // check if the desired answer 2 is in the response of the module
                else if (expected_answer2 != "") 
                {
                    if(strstr(response, expected_answer2) != NULL)
                    {
                        answer = 2;
                    }
                    
                }
            }
            else
            {
                printf("%c",response[x]);
            }

            #if DEBUG_SIM7X00>0
                printf("%c",response[x]);
            #endif
            
            x++;
        }
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;

}

char sim7x00::Send_AT_Command(const char* at_command, unsigned int timeout, const char* expected_answer) {

	return Send_AT_Command(at_command, timeout, expected_answer, "");
}

char sim7x00::Send_AT_Command(const char* at_command, unsigned int timeout){

    return Send_AT_Command(at_command, timeout, "", "");
}

char sim7x00::Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1, const char* expected_end2, bool print_response){
    uint8_t x=0,  answer=0;
    unsigned long previous;

    previous = millis();   

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial.available() != 0){    
            response[x] = Serial.read();

            if(expected_end1 != "")
            {
                // check if the desired answer 1  is in the response of the module
                if (strstr(response, expected_end1) != NULL)   
                {
                    answer = 1;
                }
                // check if the desired answer 2 is in the response of the module
                else if (expected_end2 != "") 
                {
                    if(strstr(response, expected_end2) != NULL)
                    {
                        answer = 2;
                    }
                    
                }
            }
            #if DEBUG_SIM7X00>0
                printf("%c",response[x]);
            #endif
            x++;
        }
    }while((answer == 0) && ((millis() - previous) < timeout));  

    return answer;
}

char sim7x00::Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1, const char* expected_end2){

    return(Get_Serial_Response(response, timeout, expected_end1, expected_end2, false));
}

char sim7x00::Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1){

    return(Get_Serial_Response(response, timeout, expected_end1, "", false));
}

char sim7x00::Get_Serial_Response(char* response, unsigned int timeout){
    return(Get_Serial_Response(response, timeout, "", "", false));
}

