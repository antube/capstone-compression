#pragma once
#include "turbojpeg.h"
#include "structs.h"

ImageBuffer* compressImage(ImageBuffer*, int, TJSAMP);

ImageBuffer* compressImage(ImageBuffer*, IntBuffer*, TJSAMP);