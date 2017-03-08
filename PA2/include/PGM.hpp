//
//  PGM.hpp
//  CS485_PA02
//
//  Created by Evan Grill on 2/12/17.
//  Copyright © 2017 Evan Grill. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
using namespace std;

class PGM
{
public:
    PGM();
    PGM( PGM& copyFrom );
    PGM( const string filename );
    ~PGM();
    
    bool readFile( const string filename );
    bool writeFile( const string filename );
    
    bool clear( );
    bool normalize( );
    bool gaussian1D( const double sigma, const int maskSize );
    bool gaussian2D( const double sigma, const int maskSize );
    bool sobel( const int threshold );
    bool downScale( const int factor );
    
    bool apply1DMask( double* mask, const int size );
    bool apply2DMask( double** mask, const int size );
    
    bool threshold( const int level );
    
    int getWidth( );
    int getHeight( );
    int getDepth( );
    string getFilename( );
    
    
    
    
private:
    int width;
    int height;
    int depth;
    uint8_t** image;
    string fname;
    
};