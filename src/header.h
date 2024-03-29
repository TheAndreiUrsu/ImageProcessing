#pragma once
#include <iostream>
#include <vector>

class Image {
public:
	// Header.
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

		Header(char idLen, char hasColorMap, char imageType, short colorMapOrigin, short colorMapLen, short colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor) {
			this->idLen = idLen;
			this->hasColorMap = hasColorMap;
			this->imageType = imageType;
			this->colorMapOrigin = colorMapOrigin;
			this->colorMapLen = colorMapLen;
			this->colorMapDepth = colorMapDepth;
			this->xOrigin = xOrigin;
			this->yOrigin = yOrigin;
			this->width = width;
			this->height = height;
			this->bitsPerPixel = bitsPerPixel;
			this->imageDescriptor = imageDescriptor;
		};

		void print() {
			std::cout << "***** FILE HEADER *****" << std::endl;
			std::cout << "-----------------------" << std::endl << std::endl;
			std::cout << "ID_LENGTH: " << static_cast<int>(this->idLen) << std::endl;
			std::cout << "COLOR_MAP_TYPE: " << static_cast<int>(this->hasColorMap) << std::endl;
			std::cout << "IMAGE_TYPE: " << static_cast<int>(this->imageType) << std::endl;
			std::cout << "COLOR_MAP_ORIGIN: " << this->colorMapOrigin << std::endl;
			std::cout << "COLOR_MAP_LENGTH: " << this->colorMapLen << std::endl;
			std::cout << "COLOR_MAP_DEPTH: " << static_cast<int>(this->colorMapDepth) << std::endl;
			std::cout << "X_ORIGIN: " << this->xOrigin << std::endl;
			std::cout << "Y_ORIGIN: " << this->yOrigin << std::endl;
			std::cout << "WIDTH: " << this->width << std::endl;
			std::cout << "HEIGHT: " << this->height << std::endl;
			std::cout << "PIXEL_DEPTH: " << static_cast<int>(this->bitsPerPixel) << std::endl;
			std::cout << "IMAGE_DESCRIPTOR: " << static_cast<int>(this->imageDescriptor) << std::endl << std::endl;
		};
	};

	Image(std::vector<unsigned char*> pixels, char idLen, char hasColorMap, char imageType, short colorMapOrigin, short colorMapLen, short colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor) {
		this->pixels = pixels;
		this->header = new Header(idLen, hasColorMap, imageType, colorMapOrigin, colorMapLen, colorMapDepth, xOrigin, yOrigin, width, height, bitsPerPixel, imageDescriptor);
	}

	Image() { // Default constructor
		this->pixels[0][0] = 0;
		this->pixels[0][1] = 0;
		this->pixels[0][2] = 0;

		this->header = new Header(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	~Image() { // Destructor.
		for (unsigned int i = 0; i < this->pixels.size(); i++) 
			delete[] this->pixels.at(i);

		delete this->header;
	}

	Image& operator=(const Image& that) { // Coppy assignment.
		if (this != &that) {

			for (unsigned int i = 0; i < this->pixels.size(); i++) 
				delete[] this->pixels.at(i);

			for (unsigned int i = 0; i < that.header->height * that.header->width; i++)
				this->pixels.at(i) = that.pixels.at(i);

			delete this->header;
			this->header = that.header;
		}

		return *this;
	}

	Image(const Image& that) { // Copy constructor.

		for (unsigned int i = 0; i < this->pixels.size(); i++)
			delete[] this->pixels.at(i);

		for (unsigned int i = 0; i < that.header->height * that.header->width; i++)
			this->pixels.at(i) = that.pixels.at(i);

		delete this->header;
		this->header = that.header;
	}

	void DebugHeader() {
		this->header->print();
	}

	Header* GetHeader() const {
		return this->header;
	}

	std::vector<unsigned char*> GetPixels() {
		return this->pixels;
	}

private:
	std::vector<unsigned char*> pixels;
	Header* header;
};

