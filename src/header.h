#pragma once
#include <iostream>
struct Header {
	char idLen;
	char hasColorMap;
	char imageType;
	short colorMapOrigin;
	short colorMapLen;
	short colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;

	Header(char id, char colorMap, char imageType, short colorOrigin, short colorLen, short colorDepth, short x, short y, short width, short height, char bits, char descriptor) {
		this->idLen = id;
		this->hasColorMap = colorMap;
		this->imageType = imageType;
		this->colorMapOrigin = colorOrigin;
		this->colorMapDepth = colorDepth;
		this->xOrigin = x;
		this->yOrigin = y;
		this->width = width;
		this->height = height;
		this->bitsPerPixel = bits;
		this->imageDescriptor = descriptor;
	}
};
