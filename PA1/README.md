# PA1 Smoothing, Edge Detection, and Gaussian Pyramids
## Due February 23, 2017

## 1a) 1D Gaussian Smoothing

To build the solution to this problem, type `make`.
To run the solution, use the following command:

```
$ ./main < [Input Filename] > [Output Filename]
```

*Note: The output of this solution is a csv file suitable
for viewing in Microsoft Excel.*

## 1b) 2D Gaussian Convolution

To build the solution to this problem, type `make`.
To run the solution, use the following command:

```
$ ./main [sigma] [Input Filename]
``` 

This will output to a file named `<input>_2D_<sigma>.pgm`.

## 1c) 1D Gaussian Convolution

To build the solution to this problem, type `make`.
To run the solution, use the following command:

```
$ ./main [sigma] [Input Filename]
``` 

This will output to a file named `<input>_1D_<sigma>.pgm`.

## 2) Sobel Edge Detection

To build the solution to this problem, type `make`.
To run the solution, use the following command:

```
$ ./main [threshold] [Input Filename]
```

The threshold value should be between 0-255.  This will
output files with "_sobel_x", "_sobel_y", etc. for each step.