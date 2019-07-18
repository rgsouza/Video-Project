/**
 * Author: Rayanne Souza
 * Last modification: 3 July 2016
 *
 */

#ifndef FILTRE_MOYENNEUR_H
#define FILTRE_MOYENNEUR_H
#include<systemc.h>
#include"image.h"

#define WIDTH 720
#define HEIGHT 576


SC_MODULE(FILTRE_MOYENNEUR)
{	
	sc_in< bool > clk;
	sc_in< bool > reset_n;
	sc_in< unsigned char > p_in;
	sc_in< bool > h_in;
	sc_in< bool > v_in;

    sc_out< unsigned char > p_out;
	sc_out< bool > href_out;
	sc_out< bool > vref_out;
    typedef enum {WAIT,  COMPUTE} state;

    state current_state;
    state next_state;

	SC_CTOR(FILTRE_MOYENNEUR){
		SC_METHOD(moyenneur);	
		sensitive << clk.pos();
		async_reset_signal_is( reset_n, false );
		dont_initialize();

        current_state = WAIT;
        next_state = WAIT;

        matrix_initialize();
	}

	 private:
        unsigned int p;
        unsigned char img [ WIDTH ][ 3 ];
        void moyenneur();
        void send_pixel();
        void compute_pixel( int i, int j );
        void matrix_initialize();
        int w_count, h_count, enable, end_image;
        int w_filter, h_filter;

};


#endif
