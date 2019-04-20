#include "structs.h"
#include "turbojpeg.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>


///////////////////////
// readFileBMP
// Inputs:
//        filename : char*
//
// Return:
//        CharBuffer*
///////////////////////
ImageBuffer* readFileBMP(char *filename)
{
	//Initialize file stream object
	std::ifstream infile;
	infile.open(filename, std::ios::binary);

	//If Infile has not opened return nullptr
	if (!infile)
		return nullptr;

	tagBITMAPFILEHEADER *header1 = new tagBITMAPFILEHEADER;
	tagBITMAPINFOHEADER *header2 = new tagBITMAPINFOHEADER;

	infile.read((char*)header1, sizeof(tagBITMAPFILEHEADER));
	infile.read((char*)header2, sizeof(tagBITMAPINFOHEADER));

	infile.close();

	ImageBuffer *buffer = new ImageBuffer;

	buffer->width = header2->biWidth;
	buffer->height = header2->biHeight;
	buffer->pitch = buffer->width * 3;

	int *pixelFormat = new int;
	*pixelFormat = TJPF_RGB;

	buffer->size = buffer->height * buffer->width * 3;

	buffer->init(tjLoadImage(filename, &buffer->width, 1, &buffer->height, pixelFormat, TJFLAG_STOPONWARNING));

	//std::cout << tjGetErrorStr();

	if (buffer->buffer == NULL)
		return nullptr;

	delete header1;
	delete header2;
	delete pixelFormat;

	return buffer;
}


/////////////////////
// readFileCSV
// Inputs:
//        filePath : *char
//
// Returns:
//         IntBuffer* 
//////////////////////
IntBuffer* readFileCSVQuantativeMatrix(char *filePath)
{
	//Create instance of ifstream object
	std::ifstream infile;
	
	//Attempt to open csv file
	infile.open(filePath);

	//If infile did not open correctly
	if (!infile)
		//Return a nullptr
		return nullptr;

	//Move to end of file
	infile.seekg(std::ios::end);
	
	//Retrive position in file to give length of file
	int length = infile.tellg();

	//Move to beggining of file
	infile.seekg(std::ios::beg);

	//Create string to store indivuadle numbers before conversion to int and storage in matrix
	std::string num;

	IntBuffer *CSVBuffer;

	CSVBuffer->init(64);

	int index = 0;

	do
	{
		char *character;

		//Read in a single character
		infile.read(character, 1);

		//If character equals deliminator, comma
		if (*character == ',')
		{
			//convert string to int and assign to location in quatization matrix
			//If conversion failed set value to zero
			if( !(std::istringstream(num) >> CSVBuffer->buffer[index]))
				CSVBuffer->buffer[index] = 0;

			//Reset num to blank string
			num = "";

			//Add one to the index
			index++;
		}
		//Else character is an integer
		else
			//Add character
			num += *character;

	} while (infile.tellg() < length);

	infile.close();

	return CSVBuffer;
}