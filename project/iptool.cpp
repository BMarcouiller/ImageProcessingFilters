/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 * 														    *
 ************************************************************/

#include "../iptools/core.h"
#include <strings.h>
#include <string>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		//ipf
		pch = strtok(str, " ");
		src.read(pch);

		//opf
		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		//roi
		int roi = atoi(strtok(NULL, " "));
		char* roiStack[roi][9];

		for(int i = 0; i < roi; i++){
			roiStack[i][1] = strtok(NULL, " "); //x
			roiStack[i][2] = strtok(NULL, " "); //y
			roiStack[i][3] = strtok(NULL, " "); //sX
			roiStack[i][4] = strtok(NULL, " "); //sY
			
			
			roiStack[i][0] = strtok(NULL, " "); //func
			
			string func(roiStack[i][0]);

			if(func == "add" || func == "binarize" || func == "reg2dsmooth" || func == "sep2dsmooth" || func == "sobelcv"){
				roiStack[i][5] = strtok(NULL, " "); //p1
				//roiStack[i][6] = "  ";
				//roiStack[i][7] = "  ";
			}
			else if(func == "colorvisual" || func == "histostretch" || func == "althistostretch" || func == "binaryedge"){
				roiStack[i][5] = strtok(NULL, " "); //p1
				roiStack[i][6] = strtok(NULL, " "); //p2
			}
			else if(func == "colorbright" || func == "colorstretch" || func =="hsistretch"){
				roiStack[i][5] = strtok(NULL, " "); //p1
				roiStack[i][6] = strtok(NULL, " "); //p2
				roiStack[i][7] = strtok(NULL, " "); //p3
			}
			else if(func == "histothres"){
				roiStack[i][5] = strtok(NULL, " "); //p1
				roiStack[i][6] = strtok(NULL, " "); //p2
				roiStack[i][7] = strtok(NULL, " "); //p3
				roiStack[i][8] = strtok(NULL, " "); //p4
			}
		}
		tgt = src;
		for(int i = roi - 1; i >= 0; i--){
			int x = atoi(roiStack[i][1]);
			int y = atoi(roiStack[i][2]);
			int sX = atoi(roiStack[i][3]);
			int sY = atoi(roiStack[i][4]);

			string func(roiStack[i][0]);
			func.erase(remove(func.begin(), func.end(), '\n'), func.end());
			if(func == "add"){
				cout << "Adding\n";
				int p1 = atoi(roiStack[i][5]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << "\n";
				utility::addGrey(src, tgt, x, y, sX, sY, p1);
			}
			else if(func == "binarize"){
				cout << "Binarizing\n";
				int p1 = atoi(roiStack[i][5]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << "\n";
				utility::binarize(src, tgt, x, y, sX, sY, p1);
			}
			else if(func == "reg2dsmooth"){
				cout << "Regular smoothing\n";
				int p1 = atoi(roiStack[i][5]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << "\n";
				utility::reg2dsmooth(src, tgt, x, y, sX, sY, p1);
			}
			else if(func == "sep2dsmooth"){
				cout << "Sep smoothing\n";
				int p1 = atoi(roiStack[i][5]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << "\n";
				utility::sep2dsmooth(src, tgt, x, y, sX, sY, p1);
			}
			else if(func == "colorbright"){
				cout << "Color Bright\n";
				int p1 = atoi(roiStack[i][5]);
				int p2 = atoi(roiStack[i][6]);
				int p3 = atoi(roiStack[i][7]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << " " << p2 << " " << p3 << "\n";
				utility::colorbright(src, tgt, x, y, sX, sY, p1, p2, p3);
			}
			else if(func == "colorvisual"){
				cout << "Color Visual\n";
				int p1 = atoi(roiStack[i][5]);
				int p2 = atoi(roiStack[i][6]);
				//cout << x << " " << y << " " << sX << " " << sY << " " << p1 << " " << p2 << "\n";
				utility::colorvisual(src, tgt, x, y, sX, sY, p1, p2);
			}
			else if(func == "histostretch"){
				cout << "Histogram Stretch\n";
				int p1 = atoi(roiStack[i][5]);
				int p2 = atoi(roiStack[i][6]);
				utility::histostretch(src, tgt, x, y, sX, sY, p1, p2);
			}
			else if(func == "althistostretch"){
				cout << "Alternative Histogram Stretch\n";
				int p1 = atoi(roiStack[i][5]);
				int p2 = atoi(roiStack[i][6]);
				utility::histostretch(src, tgt, x, y, sX, sY, p1, p2);
			}
			else if(func == "histothres"){
				cout << "Histogram Stretch Thresholding\n";
				int p1 = atoi(roiStack[i][5]);
				char p2 = roiStack[i][6][0];
				int p3 = atoi(roiStack[i][7]);
				int p4 = atoi(roiStack[i][8]);
				utility::histothres(src, tgt, x, y, sX, sY, p1, p2, p3, p4);
			}
			else if(func == "colorstretch"){
				char p1 = roiStack[i][5][0];
				int p2 = atoi(roiStack[i][6]);
				int p3 = atoi(roiStack[i][7]);
				utility::colorstretch(src, tgt, x, y, sX, sY, p1, p2, p3);
			}
			else if(func == "hsistretch"){
				char p1 = roiStack[i][5][0];
				int p2 = atoi(roiStack[i][6]);
				int p3 = atoi(roiStack[i][7]);
				utility::hsistretch(src, tgt, x, y, sX, sY, p1, p2, p3);
			}
			else if(func == "binaryedge"){
				int p1 = atoi(roiStack[i][5]);
				int p2 = atoi(roiStack[i][6]);
				cout << "binaryedge\n";
				utility::binaryedge(src, tgt, x, y, sX, sY, p1, p2, outfile);
			}

			else if(func == "histostretchcv"){
				utility::histostretchcv(src, tgt, x, y, sX, sY);
			}

			else if(func == "histoequalcv"){
				utility::histoequalcv(src, tgt, x, y, sX, sY);
			}

			else if(func == "houghtrans"){
				utility::houghtrans(src, tgt, x, y, sX, sY);
			}
			else if(func == "hesobel"){
				utility::hesobel(src, tgt, x, y, sX, sY);
			}
			else if(func == "hecanny"){
				utility::hecanny(src, tgt, x, y, sX, sY);
			}
			else{
				cout << func << " is undefined.\n";
			}
		}
		tgt.save(outfile);
	}
	fclose(fp);
	return 0;
}	
