#include <iostream>
#include <string>
#include "Image.h"
#include <string.h>


using namespace std;
using namespace imaging;


int main(int argc, char *argv[])
{

     string NegName = "Image_neg.ppm";
	 string fName;
	 string ppm;
	 string *pointer;
	 Image * test = new Image();    //ftiaxnoyme antikeimeno tupoy image
	if (argc == 1) {
	
		cout << "File name of the image to load: \n";
		cin >> fName;
		if (fName.length() < 3) { // to arxeio prepei na einai onoma.ppm ara toulaxiston 3 xarakthres prepei na yparxoun
			cout << "This is not an image." << endl; // prepei na yparxoun. an den uparxoun tote termatizei
			system("pause");
			return 0;
		}
		ppm = fName.substr(fName.length() - 3); //pairnoyme th katalhksh toy arxeiou
		pointer = &fName;
		if (test->load(fName.c_str(), ppm)) {  //kaloyme load kai save gia thn image pou theloyme kai gia th katalhksh pou exoyme. 
			test->save(NegName.c_str(), ppm);  // H save kaleite efoson h load etrekse epitixos
		}
        system("pause");
		return 0;
	}
	else {

	//gia na valw arguments paw sto onomaProject/properties/debugging/Command arguments 
	//kai grafw to argument pou thelw

        fName=argv[1];
		cout << "The image of the argument is: "<<fName<< "\n";
		if (fName.length() < 3) { // to arxeio prepei na einai onoma.ppm ara toulaxiston 3 xarakthres prepei na yparxoun
			cout << "This is not an image." << endl; // prepei na yparxoun. an den uparxoun tote termatizei
			system("pause");
			return 0;
		}
		ppm = fName.substr(fName.length() - 3);//pairnoyme th katalhksh toy arxeiou
		pointer = &fName;
		if (test->load(fName.c_str(), ppm)) { //kaloyme load kai save gia thn image pou theloyme kai gia th katalhksh pou exoyme.
			test->save(NegName.c_str(), ppm); // H save  kaleite efoson h load etrekse epitixos
		}
        system("pause");
		return 0;
	}



}