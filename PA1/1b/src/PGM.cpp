//
//  PGM.cpp
//  CS485_PA01
//
//  Created by Evan Grill on 2/12/17.
//  Copyright © 2017 Evan Grill. All rights reserved.
//

#include "PGM.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

PGM::PGM( )
{
    
}

PGM::PGM( PGM& copyFrom )
{
    this->width = copyFrom.width;
    this->height = copyFrom.height;
    this->depth = copyFrom.depth;
    
    image = new uint8_t*[width];
    for( int i = 0; i < width; i++ )
    {
        image[i] = new uint8_t[height];
    }
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            image[i][j] = copyFrom.image[i][j];
        }
    }
    
}

PGM::PGM( const string filename )
{
    this->readFile( filename );
}

PGM::~PGM( )
{
    clear( );
}

bool PGM::readFile( const string filename )
{
    string tempString;
    char tempChar;
    
    ifstream input;
    input.open( filename );
    
    if( !input )
    {
        cout << "File open failure." << endl;
        input.close( );
        return false;
    }
    
    input >> tempString;
    if( tempString.compare( "P2" ) != 0 && tempString.compare( "P5" ) != 0 )
    {
        cout << "File format wrong." << endl;
        input.close( );
        return false;
    }
    
    getline( input, tempString );
    while( tempString[0] == '#' || tempString.compare( "" ) == 0 )
    {
        getline(input, tempString);
    }
    
    istringstream stringStream( tempString );
    stringStream >> width;
    stringStream >> height;
    input >> depth;
    
    image = new uint8_t*[width];
    for( int i = 0; i < width; i++ )
    {
        image[i] = new uint8_t[height];
    }
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            input.get( tempChar );
            image[i][j] = (uint8_t) tempChar;
        }
    }
    
    input.close( );
    return true;
}

bool PGM::writeFile( const string filename )
{
    ofstream output( filename );
    
    if( !output.good( ) )
    {
        output.close( );
        return false;
    }
    
    output << "P5" << endl;
    output << "# Created by code written by Evan Grill." << endl;
    output << width << " " << height << endl;
    output << depth << endl;
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            output << (char) image[i][j];
        }
    }

    output.close( );
    return true;
}

bool PGM::clear( )
{
    width = height = depth = 0;
    for( int i = 0; i < width; i ++ )
    {
        delete image[i];
    }
    
    delete image;
    
    return true;
}

bool PGM::normalize( )
{
    int max = -1;
    int min = INT_MAX;
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            if( image[i][j] < min )
            {
                min = image[i][j];
            }
            if( image[i][j] > max )
            {
                max = image[i][j];
            }
        }
    }
    
    double mult = double(depth - 0) / double( max - min );
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            image[i][j] = (int) ( ( image[i][j] - min ) * mult );
        }
    }
    
    return true;
}

bool PGM::gaussian1D( const double sigma, const int maskSize )
{
    double coef = 1.0 / sqrt( 2 * 3.14159265359 * sigma * sigma );
    double e_coef = -1.0 / ( 2 * sigma * sigma );
    double* mask = new double[maskSize];
    double sum;
    
    for( int i = -1 * (maskSize - 1) / 2; i <= (maskSize - 1) / 2; i++ )
    {
        mask[i + (maskSize - 1)/2] = coef * exp( e_coef * ( i*i ) );
    }
    
    sum = 0.0;
    for( int i = 0; i < maskSize; i++ )
    {
        sum += mask[i];
    }
    
    for( int i = 0; i < maskSize; i++ )
    {
        mask[i] = mask[i] / sum;
    }
    
    apply1DMask( mask, maskSize );
    
    return true;
}

bool PGM::gaussian2D( const double sigma, const int maskSize )
{
    // make mask
    double coef = 1.0 / ( 2 * 3.14159265359 * sigma * sigma ) ;
    double e_coef = -1.0 / ( 2 * sigma * sigma );
    double** mask;
    double sum;
    
    mask = new double*[maskSize];
    
    for( int i = 0; i < maskSize; i++ )
    {
        mask[i] = new double[maskSize];
    }
    
    for( int i = -1 * (maskSize - 1) / 2; i <= (maskSize - 1) / 2; i++ )
    {
        for( int j = -1 * (maskSize - 1) / 2; j <= (maskSize - 1) / 2; j++ )
        {
            mask[i + (maskSize-1)/2][j + (maskSize-1)/2] = coef * exp( e_coef * ( i*i + j*j ) );
        }
    }
    
    sum = 0.0;
    
    for( int i = 0; i < maskSize; i++ )
    {
        for( int j = 0; j < maskSize; j++ )
        {
            sum += mask[i][j];
        }
    }
        
    for( int i = 0; i < maskSize; i++ )
    {
        for( int j = 0; j < maskSize; j++ )
        {
            mask[i][j] = mask[i][j] / sum;
        }
    }

    apply2DMask( mask, maskSize );
    
    return true;
}

bool PGM::sobel( const int threshold )
{
    double** x_mask = new double*[3];
    double** y_mask = new double*[3];
    
    for( int i = 0; i < 3; i++ )
    {
        x_mask[i] = new double[3];
        y_mask[i] = new double[3];
    }
    
    x_mask[0][0] = -1; x_mask[0][1] = 0; x_mask[0][2] = 1;
    x_mask[1][0] = -2; x_mask[1][1] = 0; x_mask[1][2] = 2;
    x_mask[2][0] = -1; x_mask[2][1] = 0; x_mask[2][2] = 1;
    
    y_mask[0][0] = 1; y_mask[0][1] = 2; y_mask[0][2] = 1;
    y_mask[1][0] = 0; y_mask[1][1] = 0; y_mask[1][2] = 0;
    y_mask[2][0] = -1; y_mask[2][1] = -2; y_mask[2][2] = -1;
    
    PGM x_sobel( *this );
    PGM y_sobel( *this );
    
    x_sobel.apply2DMask( x_mask, 3 );
    y_sobel.apply2DMask( y_mask, 3 );
    
    x_sobel.writeFile( "sf_x.pgm" );
    y_sobel.writeFile( "sf_y.pgm" );
    
    PGM mag( *this );
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            mag.image[i][j] = (int) sqrt( x_sobel.image[i][j] *
                                    x_sobel.image[i][j] +
                                    y_sobel.image[i][j] *
                                    y_sobel.image[i][j] );
        }
    }
    
    mag.writeFile( "sf_mag.pgm" );
    
    mag.threshold( threshold );
    
    mag.writeFile( "sf_thresh.pgm" );
    
    return true;
}

bool PGM::threshold( const int level )
{
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            if( image[i][j] < level )
            {
                image[i][j] = 0;
            }
            else
            {
                image[i][j] = 255;
            }
        }
    }
    
    return true;
}

bool PGM::downScale( const int factor )
{
    int sum;
    
    uint8_t** newImage = new uint8_t*[width / factor];
    for( int i = 0; i < width / factor; i++ )
    {
        newImage[i] = new uint8_t[height / factor];
    }
    
    for( int i = 0; i < width / factor; i++ )
    {
        for ( int j = 0; j < height / factor; j++ )
        {
            sum = 0;
            for( int k = 0; k < factor; k++ )
            {
                for( int l = 0; l < factor; l++ )
                {
                    sum += image[i*factor + k][j*factor + l];
                }
            }
            newImage[i][j] = sum / ( factor * factor );
        }
    }
    
    for( int i = 0; i < width; i++ )
    {
        delete image[i];
    }
    
    delete image;
    
    image = newImage;
    width = width / factor;
    height = height / factor;
    
    return true;
}

int PGM::getWidth()
{
    return width;
}

int PGM::getHeight()
{
    return height;
}

int PGM::getDepth()
{
    return depth;
}

bool PGM::apply1DMask( double* mask, const int size )
{
    int x_ind, y_ind;
    double sum;
    
    uint8_t** newImage = new uint8_t*[width];
    for( int i = 0; i < width; i++ )
    {
        newImage[i] = new uint8_t[height];
    }
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            sum = 0.0;
            
            for( int k = 0; k < size; k++ )
            {
                x_ind = i + (k - size/2);
                
                if( x_ind < 0 ) x_ind = 0;
                if( x_ind >= width ) x_ind = width - 1;
                
                sum += image[x_ind][j] * mask[k];
            }
            
            newImage[i][j] = (int) sum;
        }
    }
    
    for( int i = 0; i < width; i++ )
    {
        delete image[i];
    }
    
    delete image;
    
    image = newImage;
    
    newImage = new uint8_t*[width];
    for( int i = 0; i < width; i++ )
    {
        newImage[i] = new uint8_t[height];
    }

    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            sum = 0.0;
            
            for( int k = 0; k < size; k++ )
            {
                y_ind = j + (k - size/2);
                
                if( y_ind < 0 ) y_ind = 0;
                if( y_ind >= height ) y_ind = height - 1;
                
                sum += image[i][y_ind] * mask[k];
            }
            
            newImage[i][j] = (int) sum;
        }
    }
    
    for( int i = 0; i < width; i++ )
    {
        delete image[i];
    }
    
    delete image;
    
    image = newImage;
    
    return true;
}

bool PGM::apply2DMask( double** mask, const int size )
{
    int x_ind, y_ind;
    double sum;
    
    uint8_t** newImage = new uint8_t*[width];
    for( int i = 0; i < width; i++ )
    {
        newImage[i] = new uint8_t[height];
    }
    
    
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            sum = 0.0;
            
            for( int k = 0; k < size; k++ )
            {
                for( int l = 0; l < size; l++ )
                {
                    x_ind = i + (k - size/2);
                    y_ind = j + (l - size/2);
                    
                    if( x_ind < 0 ) x_ind = 0;
                    if( x_ind >= width ) x_ind = width - 1;
                    if( y_ind < 0 ) y_ind = 0;
                    if( y_ind >= height ) y_ind = height - 1;
                    
                    sum += image[x_ind][y_ind] * mask[k][l];
                }
            }
            
            sum = abs( sum );
            
            newImage[i][j] = (int) sum;
        }
    }
    
    for( int i = 0; i < width; i++ )
    {
        delete image[i];
    }
    
    delete image;
    
    image = newImage;
    
    return true;
}
