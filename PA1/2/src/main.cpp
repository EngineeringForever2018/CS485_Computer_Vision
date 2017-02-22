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
    int threshold;
    string filename;

    if( argc < 3 || argc > 3 )
    {
        cout << "Usage: main [threshold:0-255] [filename]" << endl;
        return 1;
    }

    threshold = atoi( argv[1] );
    filename = argv[2];

    PGM thresh( filename );
    
    thresh.sobel( threshold );

    return 0;
}
