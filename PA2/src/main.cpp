#include <cstdint>
#include <iostream>
using namespace std;

#include "Matrix.hpp"

int main( int argc, const char** argv )
{
	Matrix<int> temp( 3, 3 );
	Matrix<int> temp_2 = temp;

	cout << temp_2.rows( ) << " " << temp_2.cols( ) << endl;

	return 0;
}