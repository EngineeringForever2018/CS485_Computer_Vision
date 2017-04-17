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
	test.detectCircle( 100, 175 );
	test.writeFile( output );
	return 0;
}