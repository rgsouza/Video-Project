/**
 * Author: Rayanne Souza
 * Last modification: 25 July 2016
 *
 */

#include"video_out.h"

void VIDEO_OUT :: write_image()
{

    if( reset_n == false )
    {
        count = 0;
        enable = 0;
        num_image = 0;
    }

    else
    {
        if( vref )
            enable = 1;

        if( href && enable )
        {
//            cout << "pixel" << pixel_in << endl;
            img.pixel[ count ] = pixel_in.read();

            if( count == img.width*img.height - 1 )
            {
                enable = 0;
                count = 0;
                num_image ++;
                cout << "create image" << endl;
                std :: ostringstream name;
                name << "wallace_copy" << num_image << ".png";
                image_write( &img, name.str().c_str() );

            }
            else
                count ++;
        }

    }
}

