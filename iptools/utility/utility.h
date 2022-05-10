#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int x, int y, int sX, int sY, int value);
		static void binarize(image &src, image &tgt, int x, int y, int sX, int sY, int threshold);
		static void reg2dsmooth(image &src, image &tgt, int x, int y, int sX, int sY, int ws);
		static void sep2dsmooth(image &src, image &tgt, int x, int y, int sX, int sY, int ws);
		static void colorbright(image &src, image &tgt, int x, int y, int sX, int sY, int DR, int DG, int DB);
		static void colorvisual(image &src, image &tgt, int x, int y, int sX, int sY, int threshold, int v1);
		static void scale(image &src, image &tgt, float ratio);
		static void dualthres(image &src, image &tgt, int threshold, int V1, int V2);
		//Assignment 2
		//helper functions
		static void histogram(image &src, int x, int y, int sX, int sY, float (&vals)[2], char* outfile);
		static void rgbtohsi(image &src, image &tgt, int x, int y, int sX, int sY);
		static void hsitorgb(image &src, image &tgt, int x, int y, int sx, int sY);
		//required functions
		static void histostretch(image &src, image &tgt, int x, int y, int sX, int sY, int a, int b);
		static void althistostretch(image &src, image &tgt, int x, int y, int sX, int sY, int a, int b);
		static void histothres(image &src, image &tgt, int x, int y, int sX, int sY, int threshold, char ground, int a, int b);
		static void colorstretch(image &src, image &tgt, int x, int y, int sX, int sY, char color, int a, int b);
		static void hsistretch(image &src, image &tgt, int x, int y, int sX, int sY, char channel, int a, int b);
		//Assignment 3
		static void sobel3(image &src, image &tgt, int x, int y, int sX, int sY, int TH, int TL, string filename);
		static void sobel5(image &src, image &tgt, int x, int y, int sX, int sY);
		static void binaryedge(image &src, image &tgt, int x, int y, int sX, int sY, int TH, int TL, string filename);
		static void sobelcv(image &src, image &tgt, int x, int y, int sX, int sY, int ws);
		static void cannycv(image &src, image &tgt, int x, int y, int sX, int sY);
		static void hsvcanny(image &src, image &tgt, int x, int y, int sX, int sY);
		//Assignment 4
		static void histostretchcv(image &src, image &tgt, int x, int y, int sX, int sY);
		static void histoequalcv(image &src, image &tgt, int x, int y, int sX, int sY);
		static void houghtrans(image &src, image &tgt, int x, int y, int sX, int sY);
		static void hesobel(image &src, image &tgt, int x, int y, int sX, int sY);
		static void hecanny(image &src, image &tgt, int x, int y, int sX, int sY);

};

#endif

