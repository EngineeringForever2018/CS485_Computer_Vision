/********************************************
 *	PA2 - Affine Transforms
 *	Evan Grill, March 9, 2017
 *  Main.cpp: Drives program.
 ********************************************/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

#include "PGM.hpp"


int main( int argc, const char** argv )
{
	if( argc < 6 )
	{
		cout << "Usage: main [max radius] [sobel threshold] [max # circles] [input filename] [output filename]" << endl;
		return 1;
	}
	string input = argv[4];
	string output = argv[5];
	int max_radius = atoi( argv[1] );
	int threshold = atoi( argv[2] );
	int max_circles = atoi( argv[3] );
	PGM test( input );
	test.detectCircle( max_radius, threshold, max_circles );
	test.writeFile( output );
	return 0;
}