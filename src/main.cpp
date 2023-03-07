#include <iostream>
#include <fstream>
#include <vector>
#include "string.h"
#include "header.h"

void LoadFile(std::string _file); // loads the .tga file
void WriteFile(std::string _file); // writes the .tga file.

Image* _image;

int main(int argc, const char** argv) {

	if (argc == 1) {
		std::cout << "No commands provided" << std::endl;
	}
	else if (argc == 2) {

		if (std::strcmp(argv[1],"--help")==0) { // strcmp returns 0 if both strings are the same.
			std::cout << "Project 2: Image Processing, Spring 2023\n" << std::endl;
			std::cout << "Usage: \n\t./project2.out [output] [firstImage] [method] [...]" << std::endl;
		}
		else {
			LoadFile(argv[1]);
		}
	}

	return 0;
}

void WriteFile(std::string _file) {
	// Testing writing, by changing the first pixel.
	std::ofstream file("input/" + _file, std::ios_base::out | std::ios_base::binary);
	if (file.is_open()) {
		file.seekp(19); // Used for writing to the image, the image data starts at the 19th byte.
		file.write(reinterpret_cast<char*>(0), sizeof(0));
		file.write(reinterpret_cast<char*>(0), sizeof(0));
		file.write(reinterpret_cast<char*>(0), sizeof(0));
	}
}

void LoadFile(std::string _file) {
	std::vector<unsigned char*> pixels; // Stores all the pixels in the image, each entry has a dynamic array of 3 b g r pixels, representing the color.
	std::ifstream file("input/" + _file, std::ios_base::binary);
	std::cout << "Beginning to open file: " << _file << std::endl << std::endl;

	if (!file.is_open()) { // Handling file can't open.
		std::cout << "No file: " << _file << " exists!" << std::endl;
		return;
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

	// Debugging the pixels.
	std::cout << "***** IMAGE DATA *****" << std::endl;
	std::cout << "-----------------------" << std::endl << std::endl;

	for (unsigned int i = 2; i < pixels.size(); i *= 2) {
		std::cout << "PIXEL " << i << ": " << std::endl;
		std::cout << "B: " << static_cast<int>(pixels.at(i)[0]) << ", G: " << static_cast<int>(pixels.at(i)[1]) << ", R: " << static_cast<int>(pixels.at(i)[2]) << std::endl;
	}
	file.close();
	

	//// Memory deallocation.
	//for (unsigned int i = 0; i < pixels.size(); i++) {
	//	delete[] pixels[i];
	//}
}

