//
//  main.cpp
//  CS485_PA01
//
//  Created by Evan Grill on 2/12/17.
//  Copyright © 2017 Evan Grill. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "PGM.hpp"

int main(int argc, const char * argv[])
{
    if( argc < 5 || argc > 5 )
    {
        cout << "Usage: main [sigma] [levels] [steps] [filename]" << endl;
        return 1;
    }

    double sigma = atof( argv[1] );
    int levels = atoi ( argv[2] );
    int steps = atoi( argv[3] );
    string filename = argv[4];
    double inter_sig;

    PGM pyramid( filename );

    for( int i=0; i < levels; i++ )
    {
        for( int k = 0; k < steps; k++ )
        {
            if( k == 0 )
            {
                inter_sig = sigma;
            }
            else
            { 
                inter_sig = pow( 2.0, 1.0 / k ) * sigma;
            }

            pyramid.gaussian2D( inter_sig, int( 5 * inter_sig ) );
            pyramid.normalize( );
            pyramid.writeFile( pyramid.getFilename( ) + "_L" + to_string( i ) + 
                                "_S" + to_string( k ) + ".pgm"  );
        }
        pyramid.downScale( 2 );
        pyramid.writeFile( pyramid.getFilename( ) + "_L" + to_string( i + 1 ) + ".pgm"  );
    }

    return 0;
}
