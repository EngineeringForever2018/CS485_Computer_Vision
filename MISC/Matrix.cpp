#include <cstdint>

#include "Matrix.hpp"

template <class T>
Matrix<T>::Matrix( uint8_t rows, uint8_t cols )
{
	m = rows;
	n = cols;
	mat = new T*[m];
	for( int i = 0; i < m; i++ )
	{
		mat[i] = new T[n];
	}
}

template <class T>
Matrix<T>::Matrix( const Matrix<T>& copyFrom )
{
	delete this;
	this = new Matrix<T>( copyFrom.rows( ), copyFrom.cols( ) );
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			mat[i][j] = copyFrom.mat[i][j];
		}
	}
}

template <class T>
Matrix<T>::~Matrix( )
{
	for( int i = 0; i < m; i++ )
	{
		delete[] mat[i];
	}

	delete[] mat;
}

template <class T>
const uint8_t Matrix<T>::rows( )
{
	return const_cast<uint8_t>( m );
}

template <class T>
const uint8_t Matrix<T>::cols( )
{
	return const_cast<uint8_t>( n );
}

template <class T>
Matrix<T>& Matrix<T>::operator=( const Matrix<T>& copyFrom )
{
	this = new Matrix<T>( copyFrom );
	return *this;
}