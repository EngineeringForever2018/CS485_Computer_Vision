#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double> gaussianMask( const double sigma, const int size )
{
	double coef = 1.0 / sqrt( 2 * 3.14159265359 * sigma*sigma );
	double e_coef = -1.0 / ( 2 * sigma*sigma );
	vector<double> mask;
	double sum;

	for( int i = 0; i < size; i++ )
	{
		mask.push_back( 0 );
	}

	for( int i = -1 * (size - 1) / 2; i < size / 2; i++ )
	{
		mask[i + (size - 1)/2] = coef * exp( e_coef * i*i );
	}

	sum = 0.0;
	for( int i = 0; i < size; i++ )
	{
		sum += mask[i];
	}

	for( int i = 0; i < size; i++ )
	{
		mask[i] = mask[i] / sum;
	}

	return mask;
}

vector<double> applyMask( vector<double> input, vector<double> mask )
{
	int ind;
	double sum;
	vector<double> result;
	
	for( int i = 0; i < input.size(); i++ )
	{
		sum = 0.0;

		for( int k = 0; k < mask.size(); k++ )
		{
			ind = i + ( k - mask.size()/2 );
			if( ind < 0 ) ind = 0;
			if( ind > input.size( ) - 1) ind = input.size( ) - 1;

			sum += input[ind] * mask[k];
		}

		result.push_back( sum );
	}

	return result;
}

int main( int argc, char** argv )
{
	vector<double> input;
	vector<double> mask;
	vector<double> result_1;
	vector<double> result_5;
	vector<double> result_11;

	double temp;

	for( int i = 0; i < 128; i++ )
	{
		cin >> temp;
		input.push_back( temp );
	}

	mask = gaussianMask( 1, 5 );
	result_1 = applyMask( input, mask );

	mask = gaussianMask( 5, 25 );
	result_5 = applyMask( input, mask );
	
	mask = gaussianMask( 11, 55 );
	result_11 = applyMask( input, mask );

	cout << "input,sigma=1,sigma=5,sigma=11\r\n";
	for( int i = 0; i < input.size( ); i++ )
	{
		cout << input[i] << ",";
		cout << result_1[i] << ",";
		cout << result_5[i] << ","; 
		cout << result_11[i] << ","; 
		cout << "\r\n";
	}

	return 0;
}