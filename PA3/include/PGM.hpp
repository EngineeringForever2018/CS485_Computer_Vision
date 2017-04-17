/********************************************
 *	PA2 - Affine Transforms
 *	Evan Grill, March 9, 2017
 *  PGM.hpp: Defines PGM class.
 ********************************************/

#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Matrix.hpp"

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
    bool sobel( double** gradient_angle, double** gradient_magnitude );
    bool downScale( const int factor );
    
    bool apply1DMask( double* mask, const int size );
    bool apply2DMask( double** mask, const int size );
    
    bool threshold( const int level );
    bool affineTransform( const Matrix& A );
    bool affineTransform( const Matrix& A, const Matrix& B );

    bool detectCircle( int size = 30, int threshold = 175 );

    bool drawCircle( const int x, const int y, const int radius, const int thickness, bool filled = false );
    
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