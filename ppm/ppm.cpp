#include <iostream>
#include <fstream>
#include "ppm.h"
#include <string>




using namespace std;

/*! Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data.
*
* Values in the returned array are in the range [0,1] and for each pixel, three values are stored.
*
*  \param filename is the null-terminated string of the name of the file to open.
*  \param w is the address of an integer parameter to return the width of the image into.
*  \param h is the address of an integer parameter to return the height of the image into.
*
*  \return a pointer to a new float array of 3 X w X h floats, that contains the image data.
*  If the reading operation failed the function returns nullptr.
*/
float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	int width = *w;  //arxikoipw width
	int height = *h; //arxikopoiw height

	ifstream ifs(filename, ios::in | ios::binary);  //anoigw arxei se binary morfh
	if (!ifs.is_open()) { //elegxw an mporei na anoiksei
		cout << "Could not open file" << endl;
		return 0;
	}
	string fileHeaderFormat;
	int fileWidth, fileHeight, fileLenght;

	ifs >> fileHeaderFormat >> fileWidth >> fileHeight >> fileLenght;//diavazw to  P6,width,height,length

	float *buffer = new float[3 * width*height];// dhmiourgia float*buffer.ekei grafw ta dedomena pou diavazw
	for (int i = 0; i < 3 * width*height; i++) // diavazw ola ta dedomena kai ta grafw sto buffer
	{
		char Byte;
		ifs.get(Byte);
		float timh = Byte / 255.0f;
		buffer[i] = Byte;
	}
	// Now go back to start of file and close the file
	ifs.clear();
	ifs.seekg(0, ios_base::beg);
	ifs.close();
	return buffer;

}

/*! Writes an image buffer as a PPM file.
*
*  \param data contains the image buffer. The data are RGB float tripplets with values in the range [0,1].
*  \param w is the width of the image in pixels.
*  \param h is the height of the image in pixels.
*  \param filename is the null-terminated string of the name of the file to create.
*
*  \return true if the image save operation was successful, false otherwise. If the data parameter is nulltr, the
*  function returns immediately with a false return value.
*/
bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	cout << "Opening  Image_neg.ppm for writing... \n";
	ofstream oFile(filename, ios::out | ios::binary); //anoigw to file poy dexomai gia na  grapsw
	if (!oFile.is_open()) {//checks if fille is open or not
		cout << "Could not open Image_neg!" << endl;
		return false;
	}


	//ftiaxnw thn epikefalida kai th grafw sto arxeio
	string headerformat = "P6";
	string lenght = "255";
	string text = headerformat + "\n" + std::to_string(w) + "\n" + std::to_string(h) + "\n255\n\n "; // afto mporei na thelei mono ena xarakthra allagh grammhs kai na mhn thelei keno "\n255\n"
	oFile << text;



	//gia olo to float*buffer mas pou dexomaste grafw ta dedomena sto arxeio
	for (int i = 0; i <3 * w*h; i++)
	{
		oFile.put(data[i]);


	}

	// Make sure everything passed into the file
	oFile.flush();
	// Now go back to start of file and close the file
	oFile.clear();
	oFile.seekp(0, ios_base::beg);
	oFile.close();

	cout << "The Image_neg has been written correctly!! " << endl;
	return true;

}

