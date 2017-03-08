#pragma once

#include <cstdint>
using namespace std;

class Matrix
{
public:
	Matrix( uint8_t rows = 2, uint8_t cols = 2 );
	Matrix( const Matrix &copyFrom );
	~Matrix( );

	const uint8_t rows( ) const;
	const uint8_t cols( ) const;
	const bool isSquare( ) const;
	const bool isOrthogonal( ) const;

	bool setValue( uint8_t row, uint8_t col, double value );
	double getValue( uint8_t row, uint8_t col ) const;
	void print( );

	friend Matrix addMatrix( const Matrix& A, const Matrix& B );
	friend Matrix multiplyMatrix( const Matrix& A, const Matrix& B );
	friend Matrix multiplyMatrix( const double& k, const Matrix& A );
	friend Matrix transposeMatrix( const Matrix& A );
	friend bool LUDecomposition( const Matrix& A, Matrix& L, Matrix& U );
	friend double determinant( const Matrix& A );
	friend Matrix leadingSubMatrix( const Matrix& A, const uint8_t& k );
	friend Matrix adjointMatrix( const Matrix& A );
	friend double minor( const Matrix& A, const uint8_t& i, const uint8_t& j );
	friend Matrix subMatrix (const Matrix& A, const uint8_t& i, const uint8_t& j );
	friend double cofactor( const Matrix& A, const uint8_t& i, const uint8_t& j );
	friend Matrix cofactorMatrix( const Matrix& A );
	void operator= ( const Matrix& A );
	bool operator== (const Matrix& A ) const;

private:
	double** mat;
	uint8_t m;
	uint8_t n;
};

Matrix identityMatrix( const uint8_t& size );
