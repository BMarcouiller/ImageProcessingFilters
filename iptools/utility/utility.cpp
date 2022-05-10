#include "utility.h"
#include <cmath>

#define MAXRGB 255
#define MINRGB 0

using namespace cv;

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int x, int y, int sX, int sY, int value)
{
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{
		for (int row = y; row < (y + sY); row++){
			for (int col = x; col < (x + sX); col++)
			{
				tgt.setPixel(row,col,checkValue(src.getPixel(row,col)+value)); 
			}
		}
	}
	
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int x, int y, int sX, int sY, int threshold)
{
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{
		for (int row = y; row < (y + sY); row++){
			for (int col = x; col < (x + sX); col++){
				if (src.getPixel(row, col) < threshold)
					tgt.setPixel(row, col, MINRGB);
				else
					tgt.setPixel(row, col, MAXRGB);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::reg2dsmooth(image &src, image &tgt, int x, int y, int sX, int sY, int ws)
{
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{

		for(int row = (y + ws/2); row < (y + sY - ws/2); row++){
			for(int col = (x + ws/2); col < (x + sX - ws/2); col++){
				int sum = 0;
				for(int y = 0; y < ws; y++){
					for(int x = 0; x < ws; x++){
						sum += src.getPixel(row - ws/2 + y, col - ws/2 + x);
					}
				}
				tgt.setPixel(row, col , checkValue(sum/(ws * ws)));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::sep2dsmooth(image &src, image &tgt, int x, int y, int sX, int sY, int ws){
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{
		//vertical filter
		for(int row = (y + ws/2); row < (y + sY - ws/2); row++){
			for(int col = (x + ws/2); col < (x + sX - ws/2); col++){
				int sum = 0;
				for(int off = 0; off < ws; off++){
					sum += src.getPixel(row - ws/2 + off, col);
				}
				tgt.setPixel(row, col, checkValue(sum/ws));
			}
		}
		//horizontal filter
		for(int row = (y + ws/2); row < (y + sY - ws/2); row++){
			for(int col = (x + ws/2); col < (x + sX - ws/2); col++){
				int sum = 0;
				for(int off = 0; off < ws; off++){
					sum += src.getPixel(row, col - ws/2 + off);
				}
				tgt.setPixel(row, col, sum/ws);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::colorbright(image &src, image &tgt, int x, int y, int sX, int sY, int DR, int DG, int DB){
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{
		for(int row = y; row < (y + sY); row++){
			for (int col = x; col < (x + sX); col++){
				int R1 = src.getPixel(row, col, RED) + DR;
				tgt.setPixel(row, col, RED, checkValue(R1));
				int G1 = src.getPixel(row, col, GREEN) + DG;
				tgt.setPixel(row, col, GREEN, checkValue(G1));
				int B1 = src.getPixel(row, col, BLUE) + DB;
				tgt.setPixel(row, col, BLUE, checkValue(B1));
				
			}
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::colorvisual(image &src, image &tgt, int x, int y, int sX, int sY, int threshold, int v1){
	if((x + sX) > src.getNumberOfColumns()){
		printf("ROI out of bounds, rejected!\n");
	}
	else if ((y + sY) > src.getNumberOfRows()){
		printf("ROI out of bounds, rejected!");
	}
	else{
		for(int row = y; row < (y + sY); row++){
			for (int col = x; col < (x + sX); col++){
				int intensity = (src.getPixel(row, col, RED) + src.getPixel(row, col, GREEN) + src.getPixel(row, col, BLUE))/3;
				if(abs(v1 - intensity) < threshold){
					tgt.setPixel(row, col, RED, MAXRGB);
					tgt.setPixel(row, col, GREEN, MINRGB);
					tgt.setPixel(row, col, BLUE, MINRGB);
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::dualthres(image &src, image &tgt, int threshold, int V1, int V2)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(src.getPixel(i,j) > threshold)
				tgt.setPixel(i,j, checkValue(src.getPixel(i,j) + V1));
			else if(src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j, checkValue(src.getPixel(i,j) - V2));
			else
				tgt.setPixel(i,j, src.getPixel(i,j));
		}
	}
}
/*-----------------------------------------------------------------------**/
//Assignment 2
/*-----------------------------------------------------------------------**/
void utility::histogram(image &src, int x, int y, int sX, int sY, float (&vals)[2], char* outfile){
	float histogram[256] = {};
	int max = 0;
	int low = 0;
	int high = 0;

	//populate histogram
	for(int row = y; row < (y + sY); row++){
			for (int col = x; col < (x + sX); col++){
				int i = src.getPixel(row, col);
				histogram[i]++;
			}
	}
	
	//find min
	for(int i = 0; i <256; i++){
		if(histogram[i] > 1){
			low = i;
			break;
		}
	}
	//find high
	for(int i = 255; i > 0; i--){
		if(histogram[i] > 1){
			high = i;
			break;
		}
	}

	vals[0] = low;
	vals[1] = high;
	/*
	//find  max
	for(int i = 0; i < 256; i++){
		if(histogram[i] > max) max = histogram[i];
	}

	//normalize histogram
	for(int i = 0; i < 256; i++){
		histogram[i] /= max;
	}

	
	
	image hist;
	hist.read("blank.pgm");
	
	for(int col = 0; col < 256; col++){
		for(int row = 0; row < histogram[col]*512; row++){
			hist.setPixel(512-row, col * 2, 0);
			hist.setPixel(512-row, col * 2 + 1, 0);
		}
	}

	hist.save(outfile);
	*/

	
}

/*-----------------------------------------------------------------------**/
void utility::histostretch(image &src, image &tgt, int x, int y, int sX, int sY, int a, int b){

	float vals[2];
	histogram(src, x, y, sX, sY, vals, "hist.pgm");
	float c = vals[0];
	float d = vals[1];

	float t = (b-a)/(d-c);
	//cout <<"t  " << t << "\n";
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float p = src.getPixel(row, col);
				
				
			int new_p = checkValue((p - c) * t + a);
			tgt.setPixel(row, col, new_p);
		}
	}
	//histogram(tgt, x, y, sX, sY, vals, "newhist.pgm");
}
/*-----------------------------------------------------------------------**/
void utility::althistostretch(image &src, image &tgt, int x, int y, int sX, int sY, int a, int b){

	float vals[2];
	histogram(src, x, y, sX, sY, vals, "alt_hist.pgm");
	float c = vals[0];
	float d = vals[1];

	float t = (b-a)/(d*0.95-c*1.05);
	//cout <<"t  " << t << "\n";
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float p = src.getPixel(row, col);
			
			if(p < 1.05*c) tgt.setPixel(row, col, a);
			else if(p > 0.95*d) tgt.setPixel(row, col, b);
			else{
				int new_p = checkValue((p - c) * t + a);
				tgt.setPixel(row, col, new_p);
			}	
			
		}
	}
	histogram(tgt, x, y, sX, sY, vals, "alt_newhist.pgm");
}

/*-----------------------------------------------------------------------**/
void utility::histothres(image &src, image &tgt, int x, int y, int sX, int sY, int threshold, char ground, int a, int b){

	float histogram[256] = {};
	float c = 0;
	float d = 0;

	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = src.getPixel(row, col);
			if(ground == 'B' && p <= threshold ){
				histogram[p]++;
			}
			else if(ground == 'F' && p >= threshold){
				histogram[p]++;
			}
		}
	}

	//find low
	for(int i = 0; i <256; i++){
		if(histogram[i] > 1){
			c = i;
			break;
		}
	}
	//find high
	for(int i = 255; i > 0; i--){
		if(histogram[i] > 1){
			d = i;
			break;
		}
	}

	float t = (b-a)/(d-c);
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float p = src.getPixel(row, col);
			int new_p = checkValue((p - c) * t + a);

			if(ground == 'B' && p <= threshold){

				tgt.setPixel(row, col, new_p);
			}
			else if(ground == 'F' && p >= threshold){
				tgt.setPixel(row, col, new_p);
			}
		}
	}

}
/*-----------------------------------------------------------------------**/
void utility::colorstretch(image &src, image &tgt, int x, int y, int sX, int sY, char color, int a, int b){
	float histogram[256] = {};
	float c = 0;
	float d = 0;

	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p;
			if(color == 'R'){
				p = src.getPixel(row, col, RED);
				histogram[p]++;
			} 
			else if(color == 'G'){
				p = src.getPixel(row, col, GREEN);
				histogram[p]++;
			} 
			else if(color == 'B'){
				p = src.getPixel(row, col, BLUE);
				histogram[p]++;
			}
		}
	}
	//find low
	for(int i = 0; i <256; i++){
		if(histogram[i] > 10){
			c = i;
			break;
		}
	}
	//find high
	for(int i = 255; i > 0; i--){
		if(histogram[i] > 10){
			d = i;
			break;
		}
	}

	float t = (b-a)/(d-c);
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float p;
			if(color == 'R'){
				p = src.getPixel(row, col, RED);
				int new_p = checkValue((p - c) * t + a);
				tgt.setPixel(row, col, RED, new_p);
			} 
			else if(color == 'G'){
				p = src.getPixel(row, col, GREEN);
				int new_p = checkValue((p - c) * t + a);
				tgt.setPixel(row, col, GREEN, new_p);
			} 
			else if(color == 'B') {
				p = src.getPixel(row, col, BLUE);
				int new_p = checkValue((p - c) * t + a);
				tgt.setPixel(row, col, BLUE, new_p);
			}
		}
	}
}

void utility::rgbtohsi(image &src, image &tgt, int x, int y, int sX, int sY){
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float total = src.getPixel(row, col, RED) + src.getPixel(row, col, GREEN) + src.getPixel(row, col, BLUE);
			float r = src.getPixel(row, col, RED)/ total;
			float b = src.getPixel(row, col, BLUE)/total;
			float g = src.getPixel(row, col, GREEN)/total;

			float numerator = 0.5 *((r-g) + (r-b));
			float denomenator = pow(pow(r-g, 2) + (r-b) * (g-b), 1/2);
			float h;
			if(b <= g){
				
				h = acos(numerator/denomenator);
			}
			else if(b > g){
				h = 2 * M_PI - acos(numerator/denomenator);
			}

			float s = 1 - 3 * min(min(r, g), b);
			float i = total/(3 * 255);

			tgt.setPixel(row, col, RED, h);
			tgt.setPixel(row, col, GREEN, s);
			tgt.setPixel(row, col, BLUE, i);
		}
	}

}

void utility::hsitorgb(image &src, image &tgt, int x, int y, int sX, int sY){
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			float h = tgt.getPixel(row, col, RED);
			float s = tgt.getPixel(row, col, GREEN);
			float i = tgt.getPixel(row, col, BLUE);

			float r, g, b;
			if(h >= 0 && h < 2 * M_PI /3){
				b = i * (1 - s);
				r = i * (1 + ((s * cos(h))/cos(M_PI/3 - h)));
				g = 3 * i - (b + r);
			}
			else if(h >= 2 * M_PI / 3 && h < 4 * M_PI/3){
				h = h - (2 * M_PI / 3);

				r = i * (1 - s);
				g = i * (1 + ((s * cos(h))/cos(M_PI/3 - h)));
				b =  3 * i - (b + r);
			}
			else if( h >= 4 * M_PI/3 && h < 2 * M_PI){
				h = h - 4 * M_PI/3;

				g = i * (1 - s);
				b = i * (1 + ((s * cos(h))/cos(M_PI/3 - h)));
				r = 3 * i - (b + r);
			}
		
			tgt.setPixel(row, col, RED, r * 255);
			tgt.setPixel(row, col, GREEN, r * 255);
			tgt.setPixel(row, col, BLUE, b * 255);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::hsistretch(image &src, image &tgt, int x, int y, int sX, int sY, char channel, int a, int b){

	rgbtohsi(src, tgt, x, y, sX, sY);
	hsitorgb(src, tgt, x, y, sX, sY);

}

/*-----------------------------------------------------------------------**/
//Assignment 3
/*-----------------------------------------------------------------------**/

void utility::sobel3(image &src, image &tgt, int x, int y, int sX, int sY, int TH, int TL, string filename){
	//this code is taken from https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/image-processing/edge_detection.html#Sobel and slightly modified
	for(int row = y + 1; row < (y + sY - 1); row++){
		for (int col = x + 1; col < (x + sX - 1); col++){
			int gx = 0;
			int gy = 0;

			//left col 
			int p = src.getPixel(row - 1, col - 1);
			gx += p * -1;
			gy += p * 1; 

			p = src.getPixel(row, col -1);
			gx += p * -2;
			//gy = 0

			p = src.getPixel(row +1, col -1);
			gx += p * -1;
			gy += p * -1;

			//middle column
			p = src.getPixel(row -1, col);
			//gx == 0
			gy += p * 2;

			//middle = 0

			p = src.getPixel(row+1, col);
			//gx = 0
			gy += p * -2;

			//right column
			p = src.getPixel(row -1, col +1);
			gx += p * 1;
			gy += p * 1;

			p = src.getPixel(row, col +1);
			gx += p * 2;
			//gy = 0

			p = src.getPixel(row +1, col +1);
			gx += p * 1;
			gy += p * -1;
			
			int length = int(sqrt(float(gx * gx) + float (gy * gy)));

			length /= 17;
			tgt.setPixel(row, col, checkValue(length));

		}
	}

	float histogram[256] = {};
	float c = 0;
	float d = 0;

	for(int row = y +1; row < (y + sY -1); row++){
		for (int col = x + 1; col < (x + sX - 1); col++){
			int p = tgt.getPixel(row, col);
			histogram[p]++;
		}
	}

	//find low
	for(int i = 0; i <256; i++){
		if(histogram[i] > 1){
			c = i;
			break;
		}
	}
	//find high
	for(int i = 255; i > 0; i--){
		if(histogram[i] > 1){
			d = i;
			break;
		}
	}

	float t = (255)/(d-c);
	for(int row = y + 1 ; row < (y + sY -1); row++){
		for (int col = x + 1; col < (x + sX -1); col++){
			float p = tgt.getPixel(row, col);
			int new_p = checkValue((p - c) * t + 0);
			tgt.setPixel(row, col, new_p);
		}
	}
	
	//thresholding
	for(int row = y + 1 ; row < (y + sY -1); row++){
		for (int col = x + 1; col < (x + sX -1); col++){
			int p = tgt.getPixel(row, col);
			if(p <= TL || p >= TH){
				tgt.setPixel(row, col, 0);
			} 
			else{
				tgt.setPixel(row, col, 255);
			} 
		}
	}

	//horizontal

	//vertical
}

void utility::binaryedge(image &src, image &tgt, int x, int y, int sX, int sY, int TH, int TL, string filename){
	sobel3(src, tgt, x, y, sX, sY, TH, TL, filename);
}

void utility::histostretchcv(image &src, image &tgt, int x, int y, int sX, int sY){
	histoequalcv(src, tgt, x, y, sX, sY);
}

void utility::histoequalcv(image &src, image &tgt, int x, int y, int sX, int sY){
	//extract roi
	image roi;
	roi.resize(sY, sX);
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = src.getPixel(row, col);
			roi.setPixel(row-y, col-x, p);
		}
	}
	roi.save("roi.pgm");
	Mat image = imread("roi.pgm");
	Mat equal;

	cvtColor( image, image, COLOR_BGR2GRAY );
	equalizeHist(image, equal);
	
	imwrite("roi.pgm", equal);
	roi.read("roi.pgm");
	//insert modified roi
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = roi.getPixel(row-y, col-x);
			tgt.setPixel(row, col, p);
		}
	}
}

void utility::houghtrans(image &src, image &tgt, int x, int y, int sX, int sY){
	image roi;
	roi.resize(sY, sX);
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = src.getPixel(row, col);
			roi.setPixel(row-y, col-x, p);
			
		}
	}
	
	roi.save("roi.pgm");
	Mat img = imread("roi.pgm");
	//canny
	cvtColor(img, img, COLOR_BGR2GRAY );
	Canny(img, img, 150, 250);
	//gauss smooth
	
	GaussianBlur(img, img, Size(5,5), BORDER_DEFAULT);
	//hoough transform
	
	
	imwrite("roi.pgm", img);
	
	
	roi.read("roi.pgm");
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = roi.getPixel(row-y, col-x);
			tgt.setPixel(row, col, p);
		}
	}
}
void utility::hesobel(image &src, image &tgt, int x, int y, int sX, int sY){
	histoequalcv(src, tgt, x, y, sX, sY);

	Mat img = imread("roi.pgm");
	Mat gradx, grady;

	cvtColor( img, img, COLOR_BGR2GRAY );
	Sobel(img, gradx, CV_16S, 1, 0, 3);
	Sobel(img, grady, CV_16S, 0, 1, 3);

	convertScaleAbs(gradx, gradx);
    convertScaleAbs(grady, grady);
    addWeighted(gradx, 0.5, grady, 0.5, 0, img);

	imwrite("roi.pgm", img);
	
	image roi;
	roi.read("roi.pgm");
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = roi.getPixel(row-y, col-x);
			tgt.setPixel(row, col, p);
		}
	}
}

void utility::hecanny(image &src, image&tgt, int x, int y, int sX, int sY){
	histoequalcv(src, tgt, x, y, sX, sY);

	Mat img = imread("roi.pgm");

	cvtColor( img, img, COLOR_BGR2GRAY );
	Canny(img, img, 100, 200);

	imwrite("roi.pgm", img);
	image roi;
	roi.read("roi.pgm");
	for(int row = y; row < (y + sY); row++){
		for (int col = x; col < (x + sX); col++){
			int p = roi.getPixel(row-y, col-x);
			tgt.setPixel(row, col, p);
		}
	}
}