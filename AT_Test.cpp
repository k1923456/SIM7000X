/**
*  @filename   :   AT_Test.cpp
*  @brief      :   AT Command Testing
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

sim7x00 sim7000 = sim7x00();

void setup() {
	sim7000.Power_On();
}

void loop() {
	char at_command[100];
	memset(at_command, '\0', 100);    // Initialize the string
    delay(100);
	while( Serial.available() > 0) Serial.read();    // Clean the input buffer
	
	printf("Please input the AT command\n:");
	scanf("%s",at_command);

	Serial.println(at_command);
	sim7000.Send_AT_Command(at_command,2000);
}

int main() {
	setup();
	while (1) {
		loop();
	}
	return (0);
}