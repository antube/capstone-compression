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
	if (!infile.is_open())
		return nullptr;

	tagBITMAPFILEHEADER *header1 = new tagBITMAPFILEHEADER;
	tagBITMAPINFOHEADER *header2 = new tagBITMAPINFOHEADER;

	infile.read((char*)header1, sizeof(tagBITMAPFILEHEADER));
	infile.read((char*)header2, sizeof(tagBITMAPINFOHEADER));

	infile.close();

	ImageBuffer *buffer = new ImageBuffer;

	if (header2->biBitCount == 1)
		buffer->colorSpace = TJPF_GRAY;
	else
		buffer->colorSpace = TJPF_RGB;

	buffer->width = header2->biWidth;
	buffer->height = header2->biHeight;
	buffer->pitch = buffer->width * ((buffer->colorSpace == TJPF_GRAY)?1:3);

	int *pixelFormat = new int;
	*pixelFormat = TJPF_RGB;

	*buffer->size = buffer->height * buffer->pitch;

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
Int16Buffer* readFileCSVQuantativeMatrix(char *filePath)
{
	//Create instance of ifstream object
	std::ifstream infile;
	
	//Attempt to open csv file
	infile.open(filePath, 0);

	//If infile did not open correctly
	if (!infile)
		//Return a nullptr
		return nullptr;

	//Create string to store indivuadle numbers before conversion to int and storage in matrix
	std::string num;

	//
	Int16Buffer *CSVBuffer = new Int16Buffer;

	//
	CSVBuffer->init(64);

	//
	int index = 0;

	while (!infile.eof())
	{
		//
		char *character = new char;

		//Read in a single character
		infile.read(character, 1);

		//If character equals deliminator, comma
		if (*character == ',')
		{
			int number = 0;
			//convert string to int and assign to location in quatization matrix
			//If conversion failed set value to zero
			if (!(std::istringstream(num) >> number))
			{
				switch (index / 64)
				{
					case 0:
						CSVBuffer->buffer1[index % 64] = 1;
						break;

					case 1:
						CSVBuffer->buffer2[index % 64] = 1;
						break;
				}
			}
			else
			{
				switch (index / 64)
				{
					case 0:
						CSVBuffer->buffer1[index % 64] = number;
						break;

					case 1:
						CSVBuffer->buffer2[index % 64] = number;
						break;
				}
			}
			//Reset num to blank string
			num = "";

			//Add one to the index
			index++;
		}
		//Else character is an integer
		else
			//Add character
			num += *character;

	//
	}

	//
	infile.close();

	//
	return CSVBuffer;
}