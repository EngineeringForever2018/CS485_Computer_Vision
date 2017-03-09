/********************************************
 *	PA2 - Affine Transforms
 *	Evan Grill, March 9, 2017
 *  Matrix.cpp: Implements Matrix class.
 ********************************************/

#include <cstdint>
#include <iostream>
#include <cmath>
using namespace std;

#include "Matrix.hpp"

Matrix::Matrix( uint8_t rows, uint8_t cols )
{
	m = rows;
	n = cols;
	mat = new double*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new double[n];
	}
}

Matrix::Matrix( const Matrix& copyFrom )
{
	m = copyFrom.rows( );
	n = copyFrom.cols( );
	mat = new double*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new double[n];
	}
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			mat[i][j] = copyFrom.mat[i][j];
		}
	}
}

Matrix::Matrix( const float** copyFrom, const int& rows, const int& cols )
{
	m = rows;
	n = cols;
	mat = new double*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new double[n];
	}
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			mat[i][j] = copyFrom[i][j];
		}
	}
	
}

Matrix::Matrix( const float* copyFrom, const int& rows )
{
	m = rows;
	n = 1;
	mat = new double*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new double[n];
	}
	
	for( int i = 0; i < m; i++ )
	{
			mat[i][0] = copyFrom[i];
	}
	
}

Matrix::~Matrix( )
{
	for( int i = 0; i < m; i++ )
	{
		delete[] mat[i];
	}

	delete[] mat;
}

const uint8_t Matrix::rows( ) const
{
	return (const uint8_t) m;
}

const uint8_t Matrix::cols( ) const
{
	return (const uint8_t) n;
}

const bool Matrix::isSquare( ) const
{
	return (const bool) ( m == n );
}

bool Matrix::setValue( uint8_t row, uint8_t col, double value )
{
	if ( row >= m || col >= n )
	{
		return false;
	}
	mat[row][col] = value;
	return true;
}

double Matrix::getValue( uint8_t row, uint8_t col ) const
{
	if( row >= m || col >= n )
	{
		return nan( "" ); 
	}

	return mat[row][col];
}

void Matrix::print( ) const
{
	for( int i = 0; i < m; i++ )
	{
		printf( "[ " );
		for( int j = 0; j < n; j++ )
		{
			printf( "%.2f ", mat[i][j] );
		}
		printf( "]\n" );
	}
}

Matrix addMatrix( const Matrix& A, const Matrix& B )
{
	if( A.rows( ) != B.rows( ) || A.cols( ) != B.cols( ) )
	{
		return NULL;
	}

	Matrix C( A.rows( ), A.cols( ) );

	for( int i = 0; i < C.rows( ); i++ )
	{
		for( int j = 0; j < C.cols( ); j++ )
		{
			C.mat[i][j] = A.mat[i][j]+B.mat[i][j];
		}
	}

	return C;
}

Matrix multiplyMatrix( const Matrix& A, const Matrix& B )
{
	if( A.cols( ) != B.rows( ) )
	{
		return NULL;
	}

	Matrix C( A.rows( ), B.cols( ) );
	double sum;
	for( int i = 0; i < C.rows( ); i++ )
	{
		for( int j = 0; j < C.cols( ); j++ )
		{
			sum = 0;
			for( int k = 0; k < A.cols( ); k++ )
			{
				sum = sum + ( A.mat[i][k] * B.mat[k][j] );
			}
			C.mat[i][j] = sum;
		}
	}

	return C;
}

Matrix multiplyMatrix( const double& k, const Matrix& A )
{
	Matrix C( A.rows( ), A.cols( ) );
	for( int i = 0; i < C.rows( ); i++ )
	{
		for( int j = 0; j < C.cols( ); j++ )
		{
			C.mat[i][j] = k * A.mat[i][j];
		}
	}

	return C;
}

Matrix transposeMatrix( const Matrix& A )
{
	Matrix C( A.cols( ), A.rows( ) );
	for( int i = 0; i < C.rows( ); i++ )
	{
		for( int j = 0; j < C.cols( ); j++ )
		{
			C.mat[i][j] = A.mat[j][i];
		}
	}

	return C;
}

bool LUDecomposition( const Matrix& A, Matrix& L, Matrix& U )
{
	if( !A.isSquare( ) )
	{
		return false;
	}

	if( A.rows( ) != 2 && A.rows( ) != 3 )
	{
		cout << "LU Decomposition not implemented for greater thant 3x3 matrix" << endl;
		return false;
	}
	for( int i = 0; i < A.rows( ); i++ )
	{
		if( determinant( leadingSubMatrix( A, i ) ) == 0 )
		{
			return false;
		}
	}

	Matrix Lr( A.rows( ), A.cols( ) );
	Matrix Ur( A.rows( ), A.cols( ) );
	
	if( A.rows( ) == 2 )
	{
		for( int i = 0; i < Lr.rows( ); i++ )
		{
			Lr.setValue( i, i, 1 );;
		}
		for( int j = 0; j < Ur.cols( ); j++ )
		{
			Ur.setValue( 0, j, A.getValue( 0, j ) );
		}
		Lr.setValue( 1, 0, A.getValue( 1, 0 ) / Ur.getValue( 0, 0 ) );
		Ur.setValue( 1, 1, A.getValue( 1, 1 ) - Lr.getValue( 1, 0 ) * Ur.getValue( 0, 1 ) );
	}
	if( A.rows( ) == 3 )
	{
		for( int i = 0; i < Lr.rows( ); i++ )
		{
			Lr.setValue( i, i, 1 );;
		}

		for( int j = 0; j < Ur.cols( ); j++ )
		{
			Ur.setValue( 0, j, A.getValue( 0, j ) );
		}

		for( int i = 0; i < Lr.rows( ); i++ )
		{
			Lr.setValue( i, 0, A.getValue( i, 0 ) / Ur.getValue( 0, 0 ) );
		}
	
		for( int j = 1; j < Ur.cols( ); j++ )
		{
			Ur.setValue( 1, j, A.getValue( 1, j ) - Lr.getValue( 1, 0 ) * Ur.getValue( 0, j ) );
		}
		
		Lr.setValue( 2, 1, ( A.getValue( 2, 1 ) - Lr.getValue( 2, 0 ) * Ur.getValue( 0, 1 ) ) / Ur.getValue( 1, 1 ) );
		Ur.setValue( 2, 2, A.getValue( 2, 2 ) - Lr.getValue( 2, 0 ) * Ur.getValue( 0, 2 ) - Lr.getValue( 2, 1 ) * Ur.getValue( 1, 2 ) );
	}

	L = Lr;
	U = Ur;

	return true;
}

double determinant( const Matrix& A )
{
	
	if( !A.isSquare( ) )
	{
		
	}
	
	if( A.rows( ) == 1 )
	{
		return A.getValue( 0, 0 );
	}

	if( A.rows( ) == 2 )
	{
		return A.getValue( 0, 0 ) * A.getValue( 1, 1 ) - A.getValue( 0, 1 ) * A.getValue( 1, 0 );
	}

	return A.getValue( 0, 0 ) * cofactor( A, 0, 0 );
}

Matrix leadingSubMatrix( const Matrix& A, const uint8_t& k )
{
	if( k > A.rows( ) || A.rows( ) != A.cols ( ) )
	{
		return NULL;
	}
	return subMatrix( A, A.rows( ) - 1, A.cols( ) - 1 );
}

Matrix adjointMatrix( const Matrix& A )
{
	if( !A.isSquare( ) )
	{
		return NULL;
	}

	if( A.rows( ) == 1 )
	{
		return identityMatrix( 1 );
	}
	if( A.rows( ) == 2 )
	{
		Matrix B( 2, 2 );
		B.setValue( 0, 0, A.getValue( 1, 1 ) );
		B.setValue( 1, 1, A.getValue( 0, 0 ) );
		B.setValue( 0, 1, A.getValue( 0, 1 ) * -1 );
		B.setValue( 1, 0, A.getValue( 1, 0 ) * -1 );
		return B;
	}
	return transposeMatrix( cofactorMatrix( A ) );
}

void Matrix::operator= (const Matrix& A )
{ 
	for( int i = 0; i < m; i++ )
	{
		delete[] mat[i];
	}
	delete[] mat;

	m = A.rows( );
	n = A.cols( );
	mat = new double*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new double[n];
	}
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			mat[i][j] = A.mat[i][j];
		}
	}

}

Matrix identityMatrix( const uint8_t& size )
{
	Matrix I( size, size );
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size; j++ )
		{
			if( i == j )
			{
				I.setValue( i, j, 1 );
			}
			else
			{
				I.setValue( i, j, 0 );
			}
		}
	}

	return I;
}

double minor( const Matrix& A, const uint8_t& i, const uint8_t& j )
{
	if( !A.isSquare( ) )
	{
		return nan( "" );
	}
	return determinant( subMatrix( A, i, j ) );
}

double cofactor( const Matrix& A, const uint8_t& i, const uint8_t& j )
{
	return pow( -1, i+j+2 ) * minor( A, i, j );
}

Matrix subMatrix (const Matrix& A, const uint8_t& i, const uint8_t& j )
{
	if( !A.isSquare( ) || i > A.rows( ) || j > A.cols( ) ) {
		return NULL;
	}

	Matrix C( A.rows( ) - 1, A.cols( ) - 1);
	for( int k = 0; k < A.rows( ); k++ )
	{
		for( int l = 0; l < A.cols( ); l++ )
		{
			if( k < i && l < j )
			{
				C.setValue( k, l, A.getValue( k, l ) );
			}
			else if( k > i && l < j )
			{
				C.setValue( k - 1, l, A.getValue( k, l ) );
			}
			else if( k < i && l > j )
			{
				C.setValue( k, l - 1, A.getValue( k, l ) );
			}
			else if( k > i && l > j )
			{
				C.setValue( k - 1, l - 1, A.getValue( k, l ) );
			}
		}
	}

	return C;
}

Matrix cofactorMatrix( const Matrix& A )
{
	if( !A.isSquare( ) )
	{
		return NULL;
	}

	Matrix C( A.rows( ), A.cols( ) );
	for( int i = 0; i < C.rows( ); i++ )
	{
		for( int j = 0; j < C.cols( ); j++ )
		{
			C.setValue( i, j, cofactor( A, i, j ) );
		}
	}

	return C;
}

bool Matrix::operator== ( const Matrix& A ) const
{
	if( m != A.rows( ) || n != A.cols( ) )
	{
		return false;
	}
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			if( mat[i][j] != A.getValue( i, j ) )
			{
				return false;
			}
		}
	}

	return true;
}

const bool Matrix::isOrthogonal( ) const
{
	Matrix A = *this;
	if( !A.isSquare( ) )
	{
		return false;
	}
	if( A.rows( ) == 1 )
	{
		return A.getValue( 0, 0 ) == 1 || A.getValue( 0, 0 ) == -1;
	}
	if( A.rows( ) == 2 )
	{
		return ( 1 == pow( A.getValue( 0, 0 ), 2 ) + pow( A.getValue( 0, 1 ), 2 ) ) &&
			   ( 1 == pow( A.getValue( 1, 0 ), 2 ) + pow( A.getValue( 1, 1 ), 2 )) &&
			   ( 0 == A.getValue( 0, 0 ) * A.getValue( 0, 1 ) + A.getValue( 1, 0 ) * A.getValue( 1, 1 ) );
	}
	
	return multiplyMatrix( A, transposeMatrix( A ) ) == identityMatrix( A.rows( ) );
}

float** Matrix::solvableMatrix( )
{
	float** C = new float*[m+1];
	for( int i = 0; i < m+1; i++ )
	{
		C[i] = new float[n+1];
	}

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C[i+1][j+1] = mat[i][j];
		}
	}
	return C;
}

float* Matrix::solvableVector( )
{
	float* C;

	if( m > 1 && n > 1 )
	{
		return NULL;
	}

	if( m > 1 )
	{
		C = new float[m+1];
		for( int i = 0; i < m; i++ )
		{
			C[i+1] = mat[i][0];
		}
		return C;
	}

	if( n > 1 )
	{
		C = new float[n+1];
		for( int i = 0; i < m; i++ )
		{
			C[i+1] = mat[0][i];
		}
		return C;
	}

	return NULL;
}