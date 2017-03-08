#include <cstdint>
#include <iostream>
using namespace std;

#include "PGM.hpp"
#include "Matrix.hpp"

int main( int argc, const char** argv )
{
	Matrix A(3, 3);
	A.setValue( 0, 0, 0 );
	A.setValue( 0, 1, -0.80 );
	A.setValue( 0, 2, -0.60 );
	A.setValue( 1, 0, 0.80 );
	A.setValue( 1, 1, -0.36 );
	A.setValue( 1, 2, 0.48 );
	A.setValue( 2, 0, 0.60 );
	A.setValue( 2, 1, 0.48 );
	A.setValue( 2, 2, -0.64 );
	
	Matrix B = identityMatrix( 3 );

	cout << A.isOrthogonal( ) << endl;
	cout << B.isOrthogonal( ) << endl;
	B.print( );
	cout << endl;

	return 0;
}