# PA4: Camera Calibration
## Due May 09, 2017

## Build

To build the program, type the following:

```
$ make
```

*Note:* You may need to update the `-L` in the `LIB` line 
and the `-I` in the `INC` line of the makefile to reflect
where you have OpenCV installed.

## Run

To run this program, type the following:

```
$ ./main [# Images]
```

*Note:* This program expects the `test` folder to contain the
following folder combinations:

```
images: cap##.bmp
pixels: pixel##.txt
world: world##.txt
```

Reprojected image output will be to `output##.bmp` in the
`test` folder.