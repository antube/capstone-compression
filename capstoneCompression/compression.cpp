#include <setjmp.h>
#include "turbojpeg.h"
#include "jpeglib.h"
#include "structs.h"

ImageBuffer* compressImage(ImageBuffer *bitmapImage, int quality, TJSAMP subSampling)
{
	//Create Compression Object
	tjhandle handle = tjInitCompress();

	ImageBuffer* jpegImage;

	jpegImage->init(tjBufSize(bitmapImage->width, bitmapImage->height, subSampling));

	tjCompress2();

}

ImageBuffer* compressImage(ImageBuffer *bitmapImage, IntBuffer *quatizationMatrix, TJSAMP subSampling)
{

}