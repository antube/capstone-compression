#pragma once
#include <setjmp.h>
#include <fstream>
#include "turbojpeg.h"

#define PAD 2

struct IntBuffer
{
	unsigned int* buffer; //Data Buffer
	unsigned long *size;              //Size of Buffer

	void init(long length)
	{
		//Create buffer of specified size
		buffer = new unsigned int[length];

		for (int i = 0; i < length; i++)
		{
			buffer[i] = 0;
		}

		//Store Size of Buffer
		*size = length;
	}

	void destroy()
	{
		//Delete Buffer
		delete buffer;

		//Set Size to 0
		size = 0;
	}
};

struct Int16Buffer
{
	unsigned int* buffer1; //Data Buffer
	unsigned int* buffer2;
	unsigned long *size = new unsigned long;              //Size of Buffer

	void init(long length)
	{
		//Create buffer of specified size
		buffer1 = new unsigned int[length];
		buffer2 = new unsigned int[length];

		for (int i = 0; i < length; i++)
		{
			buffer1[i] = 0;
			buffer2[i] = 0;
		}

		//Store Size of Buffer
		*size = length;
	}

	void destroy()
	{
		//Delete Buffer
		delete buffer1;
		delete buffer2;

		//Set Size to 0
		delete size;
	}
};

struct CharBuffer
{
	unsigned char* buffer; //Data Buffer
	int size;              //Size of Buffer

	void init(long length)
	{
		//Create buffer of specified size
		buffer = new unsigned char[length];

		//Store Size of Buffer
		size = length;
	}

	void init(unsigned char *buf)
	{
		buffer = buf;
	}

	void destroy()
	{
		//Delete Buffer
		delete buffer;

		//Set Size to 0
		size = 0;
	}
};

struct ImageBuffer
{
	unsigned char* buffer; //Data Buffer
	unsigned long *size = new unsigned long;              //Size of Buffer

	int width;
	int height;
	int subSampling;
	int colorSpace;
	int pitch;

	void init(long length)
	{
		//Create buffer of specified size
		buffer = new unsigned char[length];

		//Store Size of Buffer
		*size = length;
	}

	void init(unsigned char *buf)
	{
		buffer = buf;
	}

	void destroy()
	{
		//Delete Buffer
		delete buffer;

		//Set Size to 0
		delete size;
	}
};