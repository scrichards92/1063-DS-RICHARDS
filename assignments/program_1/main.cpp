/**
* @ProgramName: Program-1
* @Author: Sierra Richards
* @Description:
*     This program reads in images stored as rgb values in a space delimited file format.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 06 02 2017
*/


#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;


/**
Structure to hold an rgb value
*/
struct rgb {
	int r;
	int g;
	int b;
};

/**
* @FunctionName: grayScale
* @Description:
*     Loops through a 2D array and turns every RGB value into its grayscale equivalent.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/

void grayScale(rgb** image, int width, int height) {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <width ; j++) 
		{
			//formula to gray scale an image
			int gray = (image[i][j].r + image[i][j].g + image[i][j].b) / 3;
			image[i][j].r = gray;
			image[i][j].g = gray;
			image[i][j].b = gray;
		}
	}
}

/**
* @FunctionName: flipVert
* @Description: 
*     Loops through a 2D array and copies each row from top to bottom or bottom to top, swapping row[i] with row[height-1 -i],
	to create a vertical flip.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/

void flipVert(rgb** image, int width, int height) {
	for (int i = 0; i < height/2; i++)
	{
		int k = height - i - 1;
		for (int j = 0; j < width; j++)
		{
			rgb temp = image[i][j];
			image[i][j] = image[k][j];
			image[k][j] = temp;
		}
	}
}


/**
* @FunctionName: flipHorz
* @Description: 
*     Loops through a 2D array and copies each column from left to right or right to left, swapping column[i] with column[width-1 -i],
	to create a horizontal flip.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/

void flipHorz(rgb** image, int width, int height) {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width/2; j++)
		{
			int k = width - 1 - j;
			rgb temp = image[i][j];
			image[i][j] = image[i][k];
			image[i][k] = temp;
		}
	}
}


int main() {
	ifstream ifile;          //Input / output files
	ofstream ofile;
	ifile.open("Nemo.txt");
	ofile.open("NemoO.txt");

	int width;               //width of image
	int height;              //height of image

	rgb **imgArray;         //Pointer var for our 2D array because we         
							//don't know how big the image will be!

	ifile >> width >> height;   //Read in width and height from top of input file
								//We need this so we can make the array the right 
								//size. After we get these two values, we can
								//now allocate memory for our 2D array.

	imgArray = new rgb*[height];    //This array points to every row

	for (int i = 0;i<height;i++) {
		imgArray[i] = new rgb[width]; //Now allocate each row of rgb's
	}

	//Read the color data in from our txt file
	for (int i = 0;i<height;i++) {
		for (int j = 0;j<width;j++) {
			ifile >> imgArray[i][j].r >> imgArray[i][j].g >> imgArray[i][j].b;
		}
	}

	//We could make any changes we want to the color image here
	flipVert(imgArray, width, height);
	
	
	//Write out our color data to a new file
	ofile << width << " " << height << endl;
	for (int i = 0;i<height;i++) {
		for (int j = 0;j<width;j++) {
			ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " " << imgArray[i][j].b << " ";
		}
		ofile << endl;
	}

	return 0;
}

