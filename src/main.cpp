#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"

void LoadFile(std::string _file); // loads the .tga file

std::vector<Header>;

int main(int argc, const char** argv) {
	LoadFile("car.tga");
	return 0;
}

void LoadFile(std::string _file) {
	std::ifstream file("input/" + _file, std::ios_base::binary);
	std::cout << "Beginning to open file: " << _file << std::endl << std::endl;
	if (file.is_open()) {

		// Reading the header file of the tga file.

		unsigned char id_len;
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

		/* Note:
			~ The pixels in the image is equal to width*height.
		*/
		char pixel;
		file.read(reinterpret_cast<char*>(&pixel), 1); 

		std::cout << "***** FILE HEADER *****" << std::endl;
		std::cout << "-----------------------" << std::endl << std::endl;
		std::cout << "ID_LENGTH: " << static_cast<int>(id_len) << std::endl;
		std::cout << "COLOR_MAP_TYPE: " << static_cast<int>(color_map_type) << std::endl;
		std::cout << "IMAGE_TYPE: " << static_cast<int>(image_type) << std::endl;
		std::cout << "COLOR_MAP_ORIGIN: " << color_map_origin << std::endl;
		std::cout << "COLOR_MAP_LENGTH: " << color_map_length << std::endl;
		std::cout << "COLOR_MAP_DEPTH: " << static_cast<int>(color_map_depth) << std::endl;
		std::cout << "X_ORIGIN: " << x_origin << std::endl;
		std::cout << "Y_ORIGIN: " << y_origin << std::endl;
		std::cout << "WIDTH: " << width << std::endl;
		std::cout << "HEIGHT: " << height << std::endl;
		std::cout << "PIXEL_DEPTH: " << static_cast<int>(pixel_depth) << std::endl;
		std::cout << "IMAGE_DESCRIPTOR: " << static_cast<int>(image_descriptor) << std::endl << std::endl;
		std::cout << "***** IMAGE DATA *****" << std::endl;
		std::cout << "-----------------------" << std::endl << std::endl;
		std::cout << "PIXEL 1: " << pixel << std::endl;

	}
}