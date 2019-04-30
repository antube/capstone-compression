#pragma once
#include "turbojpeg.h"
#include "structs.h"

ImageBuffer* compressImage(ImageBuffer*, int, TJSAMP);

void compressImage(ImageBuffer*, Int16Buffer*, TJSAMP, char*);