#include "structs.h"
#include <fstream>


void writeBufferToFile(char *filePath, ImageBuffer *Image)
{
	std::ofstream outfile;

	outfile.open(filePath);

	outfile.write((char*)Image->buffer, Image->size);

	outfile.close();
}