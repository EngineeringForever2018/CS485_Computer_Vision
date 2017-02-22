//
//  main.cpp
//  CS485_PA01
//
//  Created by Evan Grill on 2/12/17.
//  Copyright © 2017 Evan Grill. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#include "PGM.hpp"

int main(int argc, const char * argv[])
{    
    double sigma;
    string filename;

    if( argc < 3 or argc > 3 )
    {
        cout << "Usage: main [sigma value] [filename]" << endl;
        return 1;
    }

    sigma = atof( argv[1] );
    filename = argv[2];

    filename = filename.substr(0, filename.size() - 4);

    PGM gauss( filename + ".pgm" );
    gauss.gaussian1D( sigma, 5 * sigma );
    gauss.writeFile( filename + "_1D_" + to_string( int(sigma) ) + ".pgm" );

    return 0;
}
