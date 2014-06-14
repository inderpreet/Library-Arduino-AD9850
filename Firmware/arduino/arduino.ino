/* 
* Description: This file is part of 
* --
* Copyright (C) 2014 Inderpreet Singh(er.inderpreet@gmail.com), 
			  Thought Process Designs
* Web      :  http://google.com/+InderpreetSingh
*		 	  http://embeddedcode.wordpress.com
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL2) as published by the Free Software
* Foundation and appearing in the file LICENSE.TXT included in the packaging of
* this file. Please note that GPL2 Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL2 ("Copyleft").
*
* We put a lot of time and effort into our project and hence this copyright 
* notice ensures that people contribute as well as each contribution is 
* acknowledged. Please retain this original notice and if you make changes
* please document them below along with your details.
* The latest copy of this project/library can be found at: 
* https://github.com/inderpreet/
*
*/
// ----------------------------------------------------------------------------

#include <IP_AD9850.h>

IP_AD9850 AD9850(A0, A1, A2, A3);

// Frequency sweep settings
#define MAX_FREQ 15000000
#define FREQ_STEP 5000

void setup()
{
    //reset device
    AD9850.reset();                   //reset module
    delay(1000);
    AD9850.powerDown();               //set signal output to LOW
    // initialize serial communication
    AD9850.set_freq(0,0,1000);
    delay(2000);
}

void loop(){
    freqSweep();
}

void freqSweep(){
	// Sweep from 1kHz to 10MHz
    double freq = 0;
    while(freq<=MAX_FREQ){
        freq = freq + FREQ_STEP;
        AD9850.set_freq(0, 0, freq);
        delay(1000);
	}
}