This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.

2. Binarization: binarize
Binarize the pixels with the threshold.

3. Scaling: scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.

4. Binarization(Dual Thresholding): dualthres(src, tgt, T, V1, V2) 
Binarize the pixels with the threshold. 
If the pixel intensity is above the threshold value T increase intensity by V1.
If the pixel intensity is below the threshold value T decrease intensity by V2.
Else don't change pixel intensity.

5. Regular 2d Smoothing: reg2dsmooth (ws)
Use mean smoothing over an roi with windows size ws * ws

6. Seperate 2d Smoothing: sep2dsmooth(ws)
Use mean smoothing with seperate 1d windows of size ws.

7. Add intensity Colors: colorbright (DR, DG, DB)
Rnew = Rold + DR
Gnew = Gold + DG
Bnew = Bold + DB

8. Red Visualization thresholding: colorvisual(t, V1)
if  (|v1 - I(row, col)| < t)
		pixel set to Red

9. Grey Histogram Stretching: histostretch(a, b), althistostretch(a,b)

10. Binary Threshold Histogram Stretching: histothres(threshold, B/F, a, b)

11. Color Histogram Stretching: colorstretch(color, a, b)

12. Sobel3 no parameters

13. sobel 5 no parameters

14. binaryedge binaryedge(TH, TL)

*** PARAMETERS FILE ***

These are for parameters:
1. the input file name;
2. the output file name;
3. #rois
4. x
5. y
6. sX
7. sY
8. func
9. parameters

*** Run the program: ./iptool parameters.txt
