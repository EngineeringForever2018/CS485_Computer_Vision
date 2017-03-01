#pragma once

#include <cstdint>
using namespace std;

template <class T>
class Matrix
{
public:
	Matrix( uint8_t rows = 2, uint8_t cols = 2 );
	Matrix( const Matrix<T> &copyFrom );
	~Matrix( );

	const uint8_t rows( );
	const uint8_t cols( );

	Matrix<T>& operator=( const Matrix<T>& copyFrom );

private:
	T** mat;
	uint8_t m;
	uint8_t n;
};