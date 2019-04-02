#include "Color.h"
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include "ppm/ppm.h"
#include "Image.h"


/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
*/
using namespace imaging;
using namespace std;


	//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	*
	* It holds the actual buffer of the pixel values and provides methods for accessing them,
	* either as individual pixels or as a memory block. The Image class alone does not provide
	* any functionality for loading and storing an image, as it is the result or input to such a procedure.
	*
	* The internal buffer of an image object stores the actual bytes (data) of the color image as
	* a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
	* width X height X sizeof(Color) bytes.
	*
	* All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	* intensity ranges, each color component is within the range [0.0, 1.0].
	*/

		Color * buffer;                              //! Holds the image data.

		

		// data accessors

		/*! Obtains a pointer to the internal data.
		*
		*  This is NOT a copy of the internal image data, but rather a pointer
		*  to the internally allocated space, so DO NOT attempt to delete the pointer.
		*/
		Color *Image::getRawDataPtr() {
			return buffer;
		}

		/*! Obtains the color of the image at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to get.
		*  \param y is the (zero-based) vertical index of the pixel to get.
		*
		*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		*/
		Color Image::getPixel(unsigned int x, unsigned int y) const {
			Color color;
			if (x<0 || x>getWidth() || y<0 || y>getHeight()) {
				color.r = 0;
				color.g = 0;
				color.b = 0;
			}
			else {
				color.r = buffer[x*y].r;
				color.g = buffer[x*y].g;
				color.b = buffer[x*y].b;
			}
			return color;
		}

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to set.
		*  \param y is the (zero-based) vertical index of the pixel to set.
		*  \param value is the new color for the (x,y) pixel.
		*/
		void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
			
			if (x<0 || x>getWidth() || y<0 || y>getHeight()) {
				cout << "x, y Out of bounds!"<<endl;
			}
			else {
				 buffer[x*y].r=value.r;
				 buffer[x*y].g=value.g;
				 buffer[x*y].b=value.b;
			}
			
		}

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void Image::setData(const Color * & data_ptr) {
			buffer = new Color[width*  height];
			if (getWidth() != 0 && getWidth() != 0) {
				for (int i = 0; i < getWidth()*getHeight(); i++) {
					buffer[i] = data_ptr[i];
				}
			}

		}

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		*/
		Image::Image():width(0),height(0),buffer(nullptr) {}

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		*/
		Image::Image(unsigned int width, unsigned int height):width(width), height(height), buffer(nullptr) {}

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		* \param data_ptr is the source of the data to copy to the internal image buffer.
		*
		* \see setData
		*/
		Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) :width(width), height(height) {
			setData(data_ptr);
		}

		/*! Copy constructor.
		*
		* \param src is the source image to replicate in this object.
		*/
		Image::Image(const Image &src):width(src.getWidth()),height(src.getHeight()){
			const Color * srcbuffer = src.buffer;
			setData(srcbuffer);
		}

		/*! The Image destructor.
		*/
		Image::~Image() {
			cout << "Delete image constructor" << endl;
			delete[] buffer;
		}

		/*! Copy assignment operator.
		*
		* \param right is the source image.
		*/
		Image & Image::operator = (const Image & right) {
			width = right.getWidth();
			height = right.getHeight();
			const Color * srcbuffer = right.buffer;
			setData(srcbuffer);
			return *this;
		}

		/*!
		* Loads the image data from the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is initialized, its contents are wiped out before initializing it to the width, height and data
		* read from the file.
		*
		* \param filename is the string of the file to read the image data from.
		* \param format specifies the file format according to which the image data should be decoded from the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the loading completes successfully, false otherwise.
		*/
		bool Image::load(const std::string & filename, const std::string & format) {
		
			const char * charFilename = filename.c_str(); //pairnoume to onoma toy arxeioy poy anoigoyme gia na diavasoume
			if(format.compare("ppm")!=0){ //elegxoume an to arxeio exei katalhksh ppm
				cout << "This is a not ppm format!" << endl;
				return false;
			}
			ifstream iFile(filename); //arxikopoiume to ifstream
			if (!iFile.is_open())
			{
				cout << "The " << filename << " can not be opened \n";
				return false;//termatizei to programma
			}

			string fileHeaderFormat;
			int fileWidth, fileHeight, fileLenght;

			iFile >> fileHeaderFormat >> fileWidth >> fileHeight >> fileLenght; //pairnei ta P6,width,height,length

			if (fileHeaderFormat.compare("P6")!=0) { //elegxei an h epikefalia einai P6
				cout << "The header format is not P6!" << endl;
				iFile.close();
				return false;
			}
			if (fileWidth ==0) {//elegxei an uparxei to width
				cout << "The width does not exist!" << endl;
				iFile.close();
				return false;
			}

			if (fileHeight == 0) {//elegxei an uparxei to height
				cout << "The height does not exist!" << endl;
				iFile.close();
				return false;
			}

			if (fileLenght == 0 || fileLenght>255) {//elegxei an to length einai mesa sta oria
				cout << "The lenght does not exist or is bigger than 255!" << endl;
				iFile.close();
				return false;
			}

			width = fileWidth; // arxikopoioume to width pou exoyme me o fileWidth pou dexomaste
			height = fileHeight;// arxikopoioume to height pou exoyme me o fileheight pou dexomaste
			
			
			cout << "Image dimensions are: " << fileWidth << " * " << fileHeight << endl; //emfaanizoyme diastaseis

		  // Now go back to start of file and close the file
			iFile.clear();
			iFile.seekg(0, ios_base::beg);
			iFile.close();

			
			float * result=ReadPPM(charFilename, &fileWidth, &fileHeight);  //ftiaxnei ena float * gia afta pou tha diavasei
			buffer = new Color[fileWidth*fileHeight];                       //arxikopoioume to color buffer pou exoyme
			int j = 0;
		   for (int i = 0; i < 3*fileWidth*fileHeight; i=i+3) {          //antigrafoume ta dedomena apo to float * sto color Buffer
				buffer[j].r = result[i];
				buffer[j].g = result[i+1];
				buffer[j].b = result[i+2];
				j++;
			}
			

			Image * img = new Image(fileWidth, fileHeight, buffer);       //dhmiourgoume to Image antikeimeno me vash fileWidth, fileHeight,c olor buffer
		
		
			
		
		
			delete[] result;  //diagrafoyme to pinaka float*
            return true;



		}

		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is not initialized, the method should return immediately with a false return value.
		*
		* \param filename is the string of the file to write the image data to.
		* \param format specifies the file format according to which the image data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool Image:: save(const std::string & filename, const std::string & format) {

			if (format.compare("ppm") != 0) { //elegxoume an to arxeio exei katalhksh ppm
				cout << "This is a not ppm format!" << endl;
				return false;
			}

			const char * charFilename = filename.c_str(); //pairnoyme to onoma to arxeioy poy anoigoyme gia na grapsoume
			float *  result=new float[3* getWidth()*getHeight()]; //arxikopoume to pinaka float* result pou exoyme na grapsoume
			int count = 0;
			for (int i = 0; i < getWidth()*getHeight(); i = i+1) {  //pairnw to buffer pou exw kai gia kathe r,g,b afairw to 255 pou einai
				result[count] = 255.0f-buffer[i].r;                 //h megisth timh gia na ftiaksw to arnhtiko kai ta bazw sto pinaka result
				result[count + 1] = 255.0f-buffer[i].g;
				result[count + 2] = 255.0f- buffer[i].b;
				count = count + 3;
			}
			
			if (!WritePPM(result, getWidth(), getHeight(), charFilename)) {   // edw fwnazw th WritePPM gia na m grapsei to pinaka float* result sto arxeio
				return false;

			}

			
			
			delete[] buffer;//diagrafw to color buffer 
			delete[] result;// diagrafw to float * result
			return true;


			
			
			
			
		}

	   





