/**
 * Author: Rayanne Souza
 * Last modification: 3 July 2016
 *
 */

#include"zoom_2.h"

void ZOOM_2 :: apply_zoom_2()
{
    if( reset_n == false )
    {
        enable = false;
        w_count = 0;
        h_count = 0;
        w_zoom = 0;
        h_zoom = 0;
        change_line = false;
     
        current_state = WAIT;
        next_state = WAIT;   
                
        vref_out = false;
        href_out = false;
    }    

    else
    {
        if( v_in )
            enable = 1;

        // Stocke juste 1/4 de l'image
        if( h_in && enable )        
        {
            if( h_count > ((height/4) - 1) && h_count <= ((3*height)/4 - 1) )
            {
                if( w_count > ((width/4) - 1) && w_count <= ((3*width)/4 - 1) )
                {   
                    img[ w_count - width/4 ][ h_count - (height/4 - 1) ] = pixel_in;
                
                     if( current_state == WAIT )
                        current_state = STEP_ONE; 
                }
            }

            if( w_count < width - 1 )
                w_count ++;
            
            else
            {
                w_count = 0;
                if( h_count < height - 1 )
                    h_count ++;
                else
                {   h_count = 0;
                    enable = 0;
                }
            }        
        }
        compute_pixel();

    }
}
 
void ZOOM_2 :: compute_pixel()
{

    switch( current_state )
    {
        case STEP_ONE:
            pixel_out = img[ w_zoom ][ h_zoom ]; 
            
            href_out = true; 
            vref_out = (h_zoom < 2);                              
    
            next_state = REPEAT;
           
            break;
                
        case REPEAT:
            pixel_out = img[ w_zoom ][ h_zoom ];

            href_out = true;
            vref_out = (h_zoom < 2);

            if( w_zoom < width/2 - 1 )
            {     
                w_zoom ++;
                next_state = STEP_ONE;
            }
            else
            {   
                w_zoom = 0;
                if( change_line )
                {
                    if( h_zoom < height/2 - 1 )
                    {   h_zoom++;
                        change_line = false;
                        next_state = STEP_ONE;
                    }
                    else
                    {   
                        h_zoom = 0;
                        change_line = false;
                        next_state = WAIT;
                    }
                }
                else
                {    
                    change_line = true;
                    next_state = STEP_ONE;
                }
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

