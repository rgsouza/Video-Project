/**
 * Author: Rayanne Souza
 * Last modification: 17 June 2016
 * 
 */

#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include<systemc.h>
#include"image.h"

SC_MODULE(VIDEO_OUT){

	sc_in< bool > clk;
	sc_in< bool > reset_n;
	sc_in< unsigned char > pixel_in;
	sc_in< bool > href;
	sc_in< bool > vref;

	SC_CTOR(VIDEO_OUT){
		SC_METHOD(write_image);
      		sensitive << clk.pos();
      		async_reset_signal_is(reset_n,false);
      		dont_initialize();


		img.width = 720;
		img.height = 576;
		img.pixel = new unsigned char[ img.width*img.height ];

		enable = 0;
		count= 0;
		num_image = 0;
	}	

	private:
		bool enable;
		int count, num_image;
		Image img;
		void write_image();
};

#endif
