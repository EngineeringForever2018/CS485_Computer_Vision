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
	if( argc < 3 )
	{
		cout << "Usage: main [input filename] [output filename]" << endl;
		return 1;
	}
	string input = argv[1];
	string output = argv[2];
	PGM test( input );
//	PGM test2( test );
//	test2.sobel( 200 );
//	test2.writeFile( output );
	test.detectCircle( 200, 125, 30);
	test.writeFile( output );
	return 0;
}