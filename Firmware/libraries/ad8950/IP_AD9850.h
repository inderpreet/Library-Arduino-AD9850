/* 
* Description: This file is part of the AD9850 library
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

#ifndef __IP_AD9850_H__
#define __IP_AD9850_H__

#include "Arduino.h"

#define AD_CLKToggle digitalWrite(_CLK, HIGH); delay(2); digitalWrite(_CLK, LOW); delay(2);
#define AD_FQUPToggle digitalWrite(_FQUP, HIGH); delay(2); digitalWrite(_FQUP, LOW); delay(2);

class IP_AD9850{
 public:
     	IP_AD9850(int CLK, int FQUP, int BitData, int RESET);
     	void reset();
     	void set_freq(boolean PowerDown, byte Phase, double Freq);
     	void set_freq(double Freq);
        void operator<<(double Freq);
        void powerDown();

 private:
     	int _CLK;
     	int _FQUP;
     	int _RST;
     	int _BitData;
     
     	void write(byte word);	
};

#endif
