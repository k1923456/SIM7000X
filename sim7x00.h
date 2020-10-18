/**
*  @filename   :   sim7x00.h
*  @brief      :   Implements for sim7x00 Serial library
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

#ifndef sim7x00_h
#define sim7x00_h

#define DEBUG_SIM7X00 0

/* sim7x00 Class */
class sim7x00 {

public:
	// Pin definition
	static int POWERKEY;

	sim7x00();
	~sim7x00();

	// Power on the module, and init the serial port
	bool Power_On(int power_key);
	bool Power_On();

	// Send at command ,then check for the answers
	char Send_AT_Command(const char* at_command, unsigned int timeout, const char* expected_answer1, const char* expected_answer2);
	char Send_AT_Command(const char* at_command, unsigned int timeout, const char* expected_answer);
	char Send_AT_Command(const char* at_command, unsigned int timeout);
	char Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1, const char* expected_end2, bool print_response);
	char Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1, const char* expected_end2);
	char Get_Serial_Response(char* response, unsigned int timeout, const char* expected_end1);
	char Get_Serial_Response(char* response, unsigned int timeout);
};

#endif
