#include "structs.h"
#include <fstream>


/////////////////////////
// writeBufferToFile
// Inputs:
//        filePath : char*
//        Image    : ImageBuffer*
//
// Returns:
//         void
/////////////////////////
void writeBufferToFile(char *filePath, ImageBuffer *Image)
{
	//Create instance of outfile object
	std::ofstream outfile;

	//Open file specified in filePath in outfile
	outfile.open(filePath, std::ios::binary);

	//Write all provied data to file
	outfile.write((char*)Image->buffer, (unsigned long)*Image->size);

	//close file
	outfile.close();
}