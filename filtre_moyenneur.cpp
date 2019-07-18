/**
 * Author: Rayanne Souza
 * Last modification: 3 July 2016
 *
 */

#include "filtre_moyenneur.h"
void FILTRE_MOYENNEUR :: matrix_initialize()
{
    for(int j = 0; j < 3; j++)
        for(int i = 0; i < WIDTH; i++)
            img[i][j] = 0;

}

void FILTRE_MOYENNEUR :: compute_pixel( int i, int j )
{
    p = p + img[ i ][ j ];

    if( w_filter > 0 )
            p = p + img[ i - 1 ][ j ];

    if( w_filter < WIDTH - 1 )
            p = p + img[ i + 1 ][ j ];

}

void FILTRE_MOYENNEUR :: moyenneur(){

	if( reset_n == false )
	{
        current_state = WAIT;
		w_count = 0;
		h_count = 0;
		enable = 0;
		w_filter = 0;
		h_filter = 0;
		end_image = 0;
        matrix_initialize();

        href_out = false;
        vref_out = false;
	}
	
	else
	{
		if( v_in )
			enable = 1;

		if( h_in && enable )		
		{
			img[ w_count ][ h_count ] = p_in;
		
			if( h_count >= 1 && w_count >= 1 )					
                current_state = COMPUTE;
	
	        send_pixel();

			if( w_count < WIDTH - 1 )
				w_count ++;
			else
			{
				w_count = 0;
				if( h_count < 2 ){ h_count ++; }
				else { h_count = 0;  }
			}	

		}
        else
            href_out = false;
	}
}

void FILTRE_MOYENNEUR :: send_pixel( )
{

    switch(current_state)
    {
		 case COMPUTE:

            p = img[ w_filter ][ h_filter];

		    if( w_filter > 0 )
			    p = p + img[ w_filter - 1 ][ h_filter ];
		
		    if( w_filter < WIDTH - 1 )
			    p = p + img[ w_filter + 1 ][ h_filter ];

		    if( h_filter < 2 )
                compute_pixel( w_filter, h_filter + 1 );

            else if( end_image < WIDTH*(HEIGHT - 1 ) )
                compute_pixel( w_filter, 0 );
            
        
            if( h_filter == 0 )
                compute_pixel( w_filter, 2 );

            else
		        compute_pixel( w_filter,  h_filter - 1 );
            

            p_out = p/9;
            
            href_out = true;
            vref_out = ( end_image < WIDTH*4 - 1 );


            if ( end_image == WIDTH*HEIGHT - 1 )
            {   
                end_image = 0;
                p = 0;
                next_state = WAIT;
            }
            else{
                end_image++;
                next_state = COMPUTE; 
            }

            // Compteur du buffer de 3 lignes
		    if( w_filter < WIDTH - 1 )
			    w_filter ++;
		    else
		    {
			    w_filter = 0;
			    if( h_filter < 2 )
		    	    h_filter ++;
            
			    else
				    h_filter = 0;
			}    
	
            break;

    case WAIT:
            href_out = false;
            break;
    default:
            href_out = false;
            break;
    }
	
    current_state = next_state;
}
