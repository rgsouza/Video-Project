/**
 * Author: Rayanne Souza
 * Last modification: 3 July 2016
 *
 */

#ifndef ZOOM_2_H
#define ZOOM_2_H

#include<systemc.h>
#include"image.h"

SC_MODULE(ZOOM_2){

	sc_in< bool > clk;
	sc_in< bool > reset_n;
	sc_in< unsigned char > pixel_in;
	sc_in< bool > h_in;
	sc_in< bool > v_in;

	sc_out< unsigned char > pixel_out;
	sc_out< bool > href_out;
	sc_out< bool > vref_out;

	private:
		bool enable;
        bool change_line;
        unsigned int h_count;
        unsigned int w_count;
        unsigned int w_zoom;
        unsigned int h_zoom;

		const static int  height = 576;
		const static int width = 720;

		unsigned char img[ width/2 ][ height/2 ];
		void apply_zoom_2();
        void compute_pixel();
        typedef enum {STEP_ONE, REPEAT, WAIT} state;
    
        state current_state;
        state next_state;

    public: 

    	SC_CTOR(ZOOM_2){
	    	SC_METHOD(apply_zoom_2);
	    	sensitive << clk.pos();
		    async_reset_signal_is(reset_n, false);
		    dont_initialize(); 
   
            current_state = WAIT;
            next_state = WAIT;
            h_count = 0;
            w_count = 0;
            w_zoom = 0;
            h_zoom = 0;
        }

    
};
#endif 
