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
#include "Matrix.hpp"

extern void solve_system( int, int, float**, float*, float* );

void ReadLine( string input,
			   string& filename,
			   float& LEx, 
			   float& LEy,
			   float& REx,
			   float& REy,
			   float& NTx,
			   float& NTy,
			   float& MCx,
			   float& MCy )
{
	istringstream in( input );
	in >> filename;
	in >> LEx; 
	in >> LEy;
	in >> REx;
	in >> REy;
	in >> NTx;
	in >> NTy;
	in >> MCx;
	in >> MCy;
}

void ReadLine( string input,
			   float& LEx, 
			   float& LEy,
			   float& REx,
			   float& REy,
			   float& NTx,
			   float& NTy,
			   float& MCx,
			   float& MCy )
{
	istringstream in( input );
	in >> LEx; 
	in >> LEy;
	in >> REx;
	in >> REy;
	in >> NTx;
	in >> NTy;
	in >> MCx;
	in >> MCy;
}

int main( int argc, const char** argv )
{
	float LEx, LEy, REx, REy, NTx, NTy, MCx, MCy;
	ifstream images( argv[1] );
	ifstream fixed( argv[2] );
	string readLine, readFilename;

	Matrix A( 4, 3 );
	Matrix Bx( 4, 1 );
	Matrix By( 4, 1 );
	
	float** A0;
	float* Bx0;
	float* By0;
	float* X0 = new float[4];
	float* Y0 = new float[4];

	getline( fixed, readLine );
	ReadLine( readLine, LEx, LEy, REx, REy, NTx, NTy, MCx, MCy );
		Bx.setValue( 0, 0, LEx ); By.setValue( 0, 0, LEy );
		Bx.setValue( 1, 0, REx ); By.setValue( 1, 0, REy );
		Bx.setValue( 2, 0, NTx ); By.setValue( 2, 0, NTy );
		Bx.setValue( 3, 0, MCx ); By.setValue( 3, 0, MCy );

	while( getline( images, readLine ) )
	{
		ReadLine( readLine, readFilename, LEx, LEy, REx, REy, NTx, NTy, MCx, MCy );
		A.setValue( 0, 0, LEx ); A.setValue( 0, 1, LEy ); A.setValue( 0, 2, 1 );
		A.setValue( 1, 0, REx ); A.setValue( 1, 1, REy ); A.setValue( 1, 2, 1 );
		A.setValue( 2, 0, NTx ); A.setValue( 2, 1, NTy ); A.setValue( 2, 2, 1 );
		A.setValue( 3, 0, MCx ); A.setValue( 3, 1, MCy ); A.setValue( 3, 2, 1 );

		A0 = A.solvableMatrix( );
		Bx0 = Bx.solvableVector( );
		By0 = By.solvableVector( );

		solve_system( 4, 3, A0, X0, Bx0 );
		solve_system( 4, 3, A0, Y0, By0 );

		Matrix Affine( 3, 3 );
		Affine.setValue( 0, 0, X0[1] ); 
		Affine.setValue( 0, 1, X0[2] );
		Affine.setValue( 0, 2, X0[3] );
		Affine.setValue( 1, 0, Y0[1] ); 
		Affine.setValue( 1, 1, Y0[2] );
		Affine.setValue( 1, 2, Y0[3] );
		Affine.setValue( 2, 0, 0 ); 
		Affine.setValue( 2, 1, 0 );
		Affine.setValue( 2, 2, 1 );

		PGM image( readFilename );
		image.affineTransform( Affine );
		image.normalize( );
		image.writeFile( readFilename.substr( 0, readFilename.size( ) - 4 ) + "_t.pgm" );
	}
}