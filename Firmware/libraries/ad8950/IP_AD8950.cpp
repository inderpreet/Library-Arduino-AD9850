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

#include "IP_AD9850.h"

#include "Arduino.h"

IP_AD9850::IP_AD9850(int CLK, int FQUP, int BitData, int RESET)
{
	  	
   	_CLK = CLK;
   	_FQUP= FQUP;
   	_RST= RESET;
   	_BitData = BitData;

	pinMode(_RST, OUTPUT);
   	pinMode(_FQUP, OUTPUT);
   	pinMode(_CLK , OUTPUT);
   	pinMode(_BitData, OUTPUT);

	digitalWrite(_RST, LOW);
   	digitalWrite(_FQUP, LOW);
   	digitalWrite(_CLK, LOW);
   	digitalWrite(_BitData, LOW);
}

//***************************************************************************

void IP_AD9850::reset(){
		char temp;
		digitalWrite(_CLK, LOW);
		digitalWrite(_FQUP, LOW);
		//Reset signal
		digitalWrite(_RST, HIGH);
		temp = 5;
		while(temp>0){
			AD_CLKToggle
			temp--;
		}		
		digitalWrite(_RST, LOW);
		temp = 2;
		while(temp>0){
			AD_CLKToggle
			temp--;
		}		
        AD_FQUPToggle		
	}

//***************************************************************************
	
void IP_AD9850::set_freq(boolean PowerDown, byte Phase, double Freq){
	byte w,w0;
	long int y;
	double x;
	byte ConrolBits = 0x00;  //Bxxxxxx00 only allowed bits!!
	w0= (Phase & B00011111)<<3 | (PowerDown & 0x01)<<2 | ConrolBits;

	//Calculate the frequency of the HEX value
	x=4294967295/125;		//Suitable for 125M Crystal 
	Freq=Freq/1000000;
	Freq=Freq*x;
	y=Freq;
  
	AD_FQUPToggle

	//write w4
	w=(y>>=0);
	write(w);

	//write w3
	w=(y>>8);
	write(w);

	//write w2
	w=(y>>16);
	write(w);

	//write w1
	w=(y>>24);
	write(w);

	//write w0
	//  w=w0;
	write(w0);

	AD_FQUPToggle
}


//***************************************************************************
	
void IP_AD9850::set_freq(double Freq){
	byte w,w0;
	long int y;
	double x;

	w0= 0x00;    //Phase=0, PowerDown=LOW, ControlBits=00
	      
	x=4294967295/125;	//Calculate the frequency of the HEX value, Suitable for 125M Crystal 			
	Freq=Freq/1000000;
	Freq=Freq*x;
	y=Freq;

	AD_FQUPToggle
    
	w=(y>>=0);
	write(w);  	//write w4

	w=(y>>8);
	write(w);	//write w3

	w=(y>>16);
	write(w);	//write w2

	w=(y>>24);
	write(w);	//write w1

	//   w=w0;
	write(w0);	//write w0

	AD_FQUPToggle
}


//***************************************************************************
	
void IP_AD9850::powerDown(){
	byte w,w0;
	w = 0x0;
	w0 = B00000100;
	  
	AD_FQUPToggle

	//write w4
	write(w);

	//write w3
	write(w);

	//write w2
	write(w);

	//write w1
	write(w);

	//write w0
	write(w0);

	AD_FQUPToggle
}

//****************************************************************************
void IP_AD9850::write(byte word)
{ 
  byte i;
  for(i=0; i<8; i++)
  {
    digitalWrite(_BitData, (word>>i)&0x01);
    AD_CLKToggle
  }
}

//***************************************************************************
void IP_AD9850::operator<<(double frequency){
	set_freq(frequency);
}	
	













