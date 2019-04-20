#include "readFile.h"
#include "compression.h"
#include "writeFile.h"
#include <sstream>
#include <turbojpeg.h>


///////////////////
// subSampling
// Inputs:
//        arg : char*
// 
// Returns:
//         TJSAMP
///////////////////
TJSAMP subSampling(char *arg)
{
	if (arg == "444")
		return TJSAMP_444;

	else if (arg == "440")
		return TJSAMP_440;

	else if (arg == "422")
		return TJSAMP_422;

	else if (arg == "420")
		return TJSAMP_420;

	else if (arg == "411")
		return TJSAMP_411;

	else if (arg == "gra")
		return TJSAMP_GRAY;
	
	else
		return 6;
}


////////////////////
// convertStringToInt
// Inputs:
//        string : char*
//
// Returns:
//         int
////////////////////
int convertStringToInt(char *string)
{
	int result = 0;

	if (!(std::istringstream(string) >> result))
		return 0;

	return result;
}


///////////////////////
// main
// Inputs:
//        argc : int
//        argv : *char[]
//                      Original Command                        [0]
//                      Input  Bitmap Path                      [1]
//                      SubSampling Index                       [2]
//                      Option CSV or Quality Index             [3]
//                             -c     -i
//                      Input  CSV    Path or Quality specifier [4] 
//                      Output Jpeg   Path                      [5]
//
// Returns:
//         int : 0 ? 1
//               0 : exits cleanly
//               1 : invalid number of arguments
///////////////////////
int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		TJSAMP sampling = subSampling(argv[2]);

		if (argv[3] == "-c")
		{
			ImageBuffer *bmp = readFileBMP(argv[1]);
			
			IntBuffer *quantitativeMatrix = readFileCSVQuantativeMatrix(argv[4]);
		
			ImageBuffer *jpegImage = compressImage(bmp, quantitativeMatrix, sampling);

			writeBufferToFile(argv[5], jpegImage);
		}
		else if (argv[3] == "-i")
		{
			ImageBuffer *bmp = readFileBMP(argv[1]);

			ImageBuffer *jpegImage = compressImage(bmp, convertStringToInt(argv[4]), sampling);

			writeBufferToFile(argv[5], jpegImage);
		}
	}
	else
		return 1;

	return 0;
}