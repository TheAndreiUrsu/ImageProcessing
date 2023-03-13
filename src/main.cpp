#include <iostream>
#include <fstream>
#include <vector>
#include "string.h"
#include "header.h"
#include <string>

Image* LoadFile(std::string _file); // loads the .tga file and returns the image.
void WriteFile(std::string _file); // writes the .tga file.

void Multiply(std::string _file1, std::string _file2); // Multiplies every pixel in _file2 by _file1. Done by first dividing the pixels in _file2 by 255, doing the multiplication and then multiplying by 255 to get the right pixel.
void Multiply(std::string _file1, int scale, char channel); // Multiplies the channel in _file1 by the scale value.

void Subtract(std::string _file1, std::string _file2); // Subtracts the pixels in _file1 from the pixels in _file2.

void Add(std::string _file1, int num, char channel); // Adds pixels to a certain channel. 

void Rotate(std::string _file1, int degrees); // Rotates the image in _file1 by a certain number of degrees.

std::vector<Image> images;
Image* _image;

int main(int argc, const char** argv) {

	if (argc == 1) {
		Multiply(argv[1], std::stoi(argv[3]), 'b');
		//std::cout << "No commands provided" << std::endl;
	}
	else if (argc == 2) { // Used for help command.
	
		if (std::strcmp(argv[1],"--help")==0) { // strcmp returns 0 if both strings are the same.
			std::cout << "Project 2: Image Processing, Spring 2023\n" << std::endl;
			std::cout << "Usage: \n\t./project2.out [output] [firstImage] [method] [...]" << std::endl;
		}
		else {
			LoadFile(argv[1]);
			_image->DebugHeader();
		}
	}
	else if (argc == 3) { // Debugging WriteFile();
		LoadFile(argv[1]);
		WriteFile(argv[2]);
	}
	else if (argc == 4) // Used for 1 image and another command to modify it.
	{

		// Scaling the singular image's color channels.
		if (std::strcmp(argv[2], "scaleblue") == 0) {
			Multiply(argv[1], std::stoi(argv[3]), 'b');
		}
		else if (std::strcmp(argv[2], "scalegreen") == 0) {
			Multiply(argv[1], std::stoi(argv[3]), 'g');
		}
		else if (std::strcmp(argv[2], "scalered") == 0) {
			Multiply(argv[1], std::stoi(argv[3]), 'r');
		}
	}

	return 0;
}

void Multiply(std::string _file1, int scale, char channel) {
	Image* og = LoadFile(_file1);

	float normal = 0.0f; // calculates and stores the normalized channel value.

	// Debugging the pixels.
	std::cout << "***** IMAGE DATA BEFORE MULTIPLYING *****" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	for (unsigned int i = 2; i < og->GetPixels().size(); i *= 2) {
		std::cout << "PIXEL " << i << ": " << std::endl;
		std::cout << "B: " << static_cast<int>(og->GetPixels().at(i)[0]) << ", G: " << static_cast<int>(og->GetPixels().at(i)[1]) << ", R: " << static_cast<int>(og->GetPixels().at(i)[2]) << std::endl;
	}

	// Multiplying a pixel example.
	if (channel == 'b') {

		for (unsigned char*& i : og->GetPixels()) { // For each uses an iterator to quickly change every pixel in this 512x512 image. Source: https://www.geeksforgeeks.org/g-fact-40-foreach-in-c-and-java/ : cutting down from 4 minutes to 1.56 seconds.
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the b value is accessed through i[0]. 
			normal = (static_cast<float>((i[0])) / 255) * scale * 255 + 0.5f;
			i[0] = static_cast<unsigned char>(normal);
		}
		
	}
	else if (channel == 'g') {

		for (unsigned char*& i : og->GetPixels()) { 
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the g value is accessed through i[1]. 
			normal = (static_cast<float>((i[1])) / 255) * scale * 255 + 0.5f;
			i[1] = static_cast<unsigned char>(normal);
		}
	}
	else if (channel == 'r') {

		for (unsigned char*& i : og->GetPixels()) { // For each uses an iterator to quickly change every pixel in this 512x512 image. Source: https://www.geeksforgeeks.org/g-fact-40-foreach-in-c-and-java/ : cutting down from 4 minutes to 1.56 seconds.
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the r value is accessed through i[2]. 
			normal = (static_cast<float>((i[2])) / 255) * scale * 255 + 0.5f;
			i[2] = static_cast<unsigned char>(normal);
		}
	}

	// Debugging the pixels.
	std::cout << "***** IMAGE DATA AFTER MULTIPLYING *****" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	for (unsigned int i = 2; i < og->GetPixels().size(); i *= 2) {
		std::cout << "PIXEL " << i << ": " << std::endl;
		std::cout << "B: " << static_cast<int>(og->GetPixels().at(i)[0]) << ", G: " << static_cast<int>(og->GetPixels().at(i)[1]) << ", R: " << static_cast<int>(og->GetPixels().at(i)[2]) << std::endl;
	}


}

void WriteFile(std::string _file) {
	// Testing writing, by changing the first pixel.
	std::ofstream file("output/" + _file, std::ios_base::out | std::ios_base::binary);
	
	if (!file.is_open()) { // Handling file can't open.
		std::cout << "Can't create: " << _file << " !" << std::endl;
	}
	
	// Header
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->idLen), 1); // Writing the ID_LEN
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->hasColorMap), 1); // Writing the COLOR_MAP_TYPE
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->imageType), 1); // Writing the IMAGE_TYPE
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->colorMapOrigin), 2); // Writing the COLOR_MAP_ORIGIN
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->colorMapLen), 2); // Writing the COLOR_MAP_LEN
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->colorMapDepth), 1); // Writing the COLOR_MAP_DEPTH
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->xOrigin), 2); // Writing the X_ORIGIN
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->yOrigin), 2); // Writing the Y_ORIGIN
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->width), 2); // Writing the Image WIDTH
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->height), 2); // Writing the Image HEIGHT
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->bitsPerPixel), 1); // Writing the PIXEL_DEPTH
	file.write(reinterpret_cast<char*>(&_image->GetHeader()->imageDescriptor), 1); // Writing the IMAGE_DESCRIPTOR

	// Pixels
	std::vector<unsigned char*> temp = _image->GetPixels();

	for (unsigned char*& i : temp) {
		file.write(reinterpret_cast<char*>(&i[0]), 1); // Writing the blue pixel
		file.write(reinterpret_cast<char*>(&i[1]), 1); // Writing the red pixel
		file.write(reinterpret_cast<char*>(&i[2]), 1); // Writing the green pixel
	}

	_image->DebugHeader();

	
	file.close();
}

Image* LoadFile(std::string _file) {
	std::vector<unsigned char*> pixels; // Stores all the pixels in the image, each entry has a dynamic array of 3 b g r pixels, representing the color.
	std::ifstream file("input/" + _file, std::ios_base::binary);
	std::cout << "Beginning to open file: " << _file << std::endl << std::endl;

	if (!file.is_open()) { // Handling file can't open.
		std::cout << "No file: " << _file << " exists!" << std::endl;
		return nullptr;
	}
	
	// Reading the header file of the tga file.
	char id_len;
	file.read(reinterpret_cast<char*>(&id_len), 1); // 1st byte contains the id length.

	char color_map_type;
	file.read(reinterpret_cast<char*>(&color_map_type), 1); // 2nd byte contains the color map type.

	char image_type;
	file.read(reinterpret_cast<char*>(&image_type), 1); // 3rd byte contains the image type.

	short color_map_origin;
	file.read(reinterpret_cast<char*>(&color_map_origin), 2); // 4th & 5th bytes contain the color map origin. Always 0.

	short color_map_length;
	file.read(reinterpret_cast<char*>(&color_map_length), 2); // 6th & 7th bytes contain the color map length. Always 0.

	char color_map_depth;
	file.read(reinterpret_cast<char*>(&color_map_depth), 1); // 8th byte contains the color map depth. Always 0.

	short x_origin;
	file.read(reinterpret_cast<char*>(&x_origin), 2); // 9th & 10th bytes contain the image's x origin. Always 0.

	short y_origin;
	file.read(reinterpret_cast<char*>(&y_origin), 2); // 11th & 12th bytes contain the image's y origin. Always 0.

	short width;
	file.read(reinterpret_cast<char*>(&width), 2); // 13th & 14th bytes contain the image's width in px.

	short height;
	file.read(reinterpret_cast<char*>(&height), 2); // 15th & 16th bytes contain the image's height in px.

	char pixel_depth;
	file.read(reinterpret_cast<char*>(&pixel_depth), 1); // 17th byte contains the image's pixel depth. Always 24 (for RGB, each 8 bits).

	char image_descriptor;
	file.read(reinterpret_cast<char*>(&image_descriptor), 1); // 18th byte contains the image's descriptor.

	unsigned char* bgr_pixel;
	unsigned char b_pixel, g_pixel, r_pixel; // Values between 0 and 255.

	/* Note:
		~ The pixels in the image is equal to width*height, the size of the pixels vector too.
	*/
	for (int i = 0; i < height * width; i++) {
		bgr_pixel = new unsigned char[3]; // Allocates an array of size 3 each time the loop is called. It gets deallocated when the program is finished.
		file.read(reinterpret_cast<char*>(&b_pixel), 1);
		file.read(reinterpret_cast<char*>(&g_pixel), 1);
		file.read(reinterpret_cast<char*>(&r_pixel), 1);
		bgr_pixel[0] = b_pixel; // Blue value
		bgr_pixel[1] = g_pixel; // Green value
		bgr_pixel[2] = r_pixel; // Red value
		pixels.push_back(bgr_pixel); // 1 Pixel
	}

	_image = new Image(pixels, id_len, color_map_type, image_type, color_map_origin, color_map_length, color_map_depth, x_origin, y_origin, width, height, pixel_depth, image_descriptor);

	file.close();
	return _image;

	//// Memory deallocation.
	//for (unsigned int i = 0; i < pixels.size(); i++) {
	//	delete[] pixels[i];
	//}
}

