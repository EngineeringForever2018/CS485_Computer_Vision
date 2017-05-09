/********************************************************************
 *
 * CS485 PA4: Camera Calibration
 * Evan Grill
 * May 9, 2017
 * 
 * This project uses OpenCV's built in camera calibration to
 * determine the intrinsic/extrinsic properties of a camera and
 * series of images taken with that camera.  It then reprojects the
 * images based on these properties and determines the reprojection
 * error. 
 *
 ********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

string padText( int input, int length );
vector<Point3f> readWorldPoints( string filename );
vector<Point2f> readPixelPoints( string filename );

int main( int argc, char** argv )
{
	// Verify correct number of arguments.
	// Should be 2, executable name and number of
	// images.
	if( argc < 2 || argc > 2 )
	{
		cout << "Usage: main [# images]" << endl;
		return 0;
	}

	// Declare variables.
	int numImages = atoi( argv[1] );
	vector<vector<Point3f>> worldPoints;
	vector<vector<Point2f>> pixelPoints;
	vector<Mat> images;
	Mat cameraMatrix = Mat::eye(3, 3, CV_32FC1);
	Mat distanceCoefficients = Mat::zeros(8, 1, CV_32FC1);
	vector<Mat> rVectors, tVectors;
	Mat intrinsicStdDevs = Mat(3, 3, CV_32FC1);
	Mat extrinsicStdDevs = Mat(3, 3, CV_32FC1);

	// For each image, open the image, the world points,
	// and the pixel points and store them in their vectors.
	for( int i = 1; i <= numImages; i++ )
	{
		vector<Point3f> temp3f;
		vector<Point2f> temp2f;
		string worldPointsFilename = "test/world/world" + padText( i, 2 ) + ".txt";
		string pixelPointsFilename = "test/pixels/pixel" + padText( i, 2 ) + ".txt";
		string imageFilename = "test/images/cap" + padText( i, 2 ) + ".bmp";
		temp3f = readWorldPoints( worldPointsFilename );
		worldPoints.push_back( temp3f );
		temp2f = readPixelPoints( pixelPointsFilename );
		pixelPoints.push_back( temp2f );
		images.push_back( imread( imageFilename, IMREAD_UNCHANGED ) );
	}
	// Perform camera calibration based on world points and corresponding
	// pixel points.  Determine cameraMatrix (intrinsic) and distance
	// coefficients, rotation vectors and translation vectors (extrinsic).
	calibrateCamera( worldPoints, pixelPoints, images[0].size( ), cameraMatrix,
					 distanceCoefficients, rVectors, tVectors );

	// For each image, reproject points using calculated parameters.
	// Then draw projected points onto image. Then lastly, calculate
	// the average error for all points in the image and output to the console.
	cout << "image,orig_x,orig_y,proj_x,proj_y,err\r\n";
	for( int i = 1; i <= numImages; i++ )
	{
		string outputFilename = "test/output" + padText( i, 2 ) + ".bmp";
		vector<Point2f> calcPoints;
		double err = 0;
		double tempErr;
		projectPoints( worldPoints[i-1], rVectors[i-1], tVectors[i-1], cameraMatrix, distanceCoefficients, calcPoints );
		for( int j = 0; j < calcPoints.size( ); j++ )
		{
			circle( images[i-1], calcPoints[j], 1, Scalar( 255, 255, 0 ), 2 );
			tempErr = sqrt( pow( calcPoints[j].x - pixelPoints[i-1][j].x, 2 ) + pow( calcPoints[j].y - pixelPoints[i-1][j].y, 2 ) );
			err += tempErr;
	//		cout << "cap" << padText( i, 2 ) << ".bmp,";
	//		cout << pixelPoints[i-1][j].x << "," << pixelPoints[i-1][j].y << ",";
	//		cout << calcPoints[j].x << "," << calcPoints[j].y << ",";
	//		cout << tempErr << "\r\n";
		}
		cout << "Image " << i << " Avg Error: " << err / calcPoints.size( ) << endl;
		imwrite( outputFilename, images[i-1] );
	}

	return 0;
}

// Returns a string version of an integer padded to length.
// This is probably implemented somewhere in STL, but I didn't
// bother to check.
string padText( int input, int length )
{
	string output = to_string( input );
	while( output.length( ) < length )
	{
		output = "0" + output;
	}
	
	return output;
}

// Read in the file of world points.
vector<Point3f> readWorldPoints( string filename )
{
	vector<Point3f> worldPoints;
	ifstream input( filename );
	if( !input )
	{
		cout << "Bad File" << endl;
		return worldPoints;
	}

	while( input )
	{
		double x, y;
		input >> x;
		input >> y;
		worldPoints.push_back( Point3f( x, y, 0.0 ) );
	}

	return worldPoints;
}

// Read in the file of image points.
vector<Point2f> readPixelPoints( string filename )
{
	vector<Point2f> pixelPoints;
	ifstream input( filename );
	if( !input )
	{
		cout << "Bad File" << endl;
		return pixelPoints;
	}

	while( input )
	{
		double x, y;
		input >> x;
		input >> y;
		pixelPoints.push_back( Point2f( x, y ) );
	}

	return pixelPoints;
}