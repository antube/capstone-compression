#pragma once

#define PAD 2

struct IntBuffer
{
	unsigned int* buffer; //Data Buffer
	int size;              //Size of Buffer

	void init(long length)
	{
		//Create buffer of specified size
		buffer = new unsigned int[length];

		for (int i = 0; i < length; i++)
		{
			buffer[i] = 0;
		}

		//Store Size of Buffer
		size = length;
	}

	void destroy()
	{
		//Delete Buffer
		delete buffer;

		//Set Size to 0
		size = 0;
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
	int size;              //Size of Buffer

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