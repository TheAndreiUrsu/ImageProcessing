#include <iostream>
#include <fstream>
#include <vector>
#include "string.h"
#include "header.h"
#include <string>

Image* LoadFile(std::string _file); // loads the .tga file and returns the image.
void WriteFile(std::string _file); // writes the .tga file.

Image* Multiply(Image* _top, Image* _bottom); // Multiplies every pixel in _file2 by _file1. Done by first dividing the pixels in _file2 by 255, doing the multiplication and then multiplying by 255 to get the right pixel.
Image* Multiply(Image* image, int scale, char channel); // Multiplies the channel in _file1 by the scale value.

std::vector<float*> Normalize(std::vector<unsigned char*>& pixels); // Helper method for normalizing all the pixels.

Image* Screen(Image* _top, Image* _bottom);

Image* Subtract(Image* _top, Image* _bottom); // Subtracts the pixels in top image from the pixels in the bottom image.

Image* Add(Image* image, int num, char channel); // Adds pixels to a certain channel. 
Image* Add(Image* image, char channel);

Image* Overlay(Image* I1, Image* I2);

Image* Rotate(Image* image, int degrees); // Rotates the image in _file1 by a certain number of degrees.

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();
void Task8();
void Task9();
void Task10();

int main(int argc, const char** argv) {
	/*int option;
	std::cout << "Choose a task to test: (1-10)" << std::endl;
	std::cin >> option;*/
	/*Task1();
	Task2();
	Task3();
	Task4();
	Task5();
	Task6();
	Task7();
	Task8();*/
	Task9();
	// Test Cases.
	/*if (option == 1)
		Task1();
	else if (option == 2)
		Task2();
	else if (option == 3)
		Task3();
	else if (option == 4)
		Task4();
	else if (option == 5)
		Task5();
	else if (option == 6)
		Task6();
	else if (option == 7)
		Task7();
	else if (option == 8)
		Task8();
	else if (option == 9)
		Task9();
	else if (option == 10)
		Task10();*/
	

	// CLI
	
	//if (argc == 1) {
	//	Multiply(argv[1], std::stoi(argv[3]), 'b');
	//	//std::cout << "No commands provided" << std::endl;
	//}
	//else if (argc == 2) { // Used for help command.
	//
	//	if (std::strcmp(argv[1],"--help")==0) { // strcmp returns 0 if both strings are the same.
	//		std::cout << "Project 2: Image Processing, Spring 2023\n" << std::endl;
	//		std::cout << "Usage: \n\t./project2.out [output] [firstImage] [method] [...]" << std::endl;
	//	}
	//	else {
	//		LoadFile(argv[1]);
	//		_image->DebugHeader();
	//	}
	//}
	//else if (argc == 3) { // Debugging WriteFile();
	//	LoadFile(argv[1]);
	//	WriteFile(argv[2]);
	//}
	//else if (argc == 4) // Used for 1 image and another command to modify it.
	//{

	//	// Scaling the singular image's color channels.
	//	if (std::strcmp(argv[2], "scaleblue") == 0) {
	//		Multiply(argv[1], std::stoi(argv[3]), 'b');
	//	}
	//	else if (std::strcmp(argv[2], "scalegreen") == 0) {
	//		Multiply(argv[1], std::stoi(argv[3]), 'g');
	//	}
	//	else if (std::strcmp(argv[2], "scalered") == 0) {
	//		Multiply(argv[1], std::stoi(argv[3]), 'r');
	//	}

	//	// Adding to a respective color channel.
	//	if (std::strcmp(argv[2], "addblue") == 0) {
	//		Add(argv[1], std::stoi(argv[3]), 'b');
	//	}
	//	else if (std::strcmp(argv[2], "addgreen") == 0) {
	//		Add(argv[1], std::stoi(argv[3]), 'g');
	//	}
	//	else if (std::strcmp(argv[2], "addblue") == 0) {
	//		Add(argv[1], std::stoi(argv[3]), 'b');
	//	}
	//}

	return 0;
}

Image* Subtract(Image* _top, Image* _bottom) { // Subtracts pixels in file 2 from file 1.
	
	Image* out = _top;
	
	std::vector<unsigned char*> bottom = _bottom->GetPixels();
	std::vector<unsigned char*> top = out->GetPixels();
	
	int i = 0;
	for (unsigned char*& px : out->GetPixels()) { // Iterating through the _image which is the output image.
		if ((static_cast<int>(bottom[i][0]) - top[i][0] < 0))
			px[0] = 0;
		else
			px[0] = static_cast<char>(bottom[i][0] - top[i][0]); // Blue pixel
		if ((static_cast<int>(bottom[i][1]) - top[i][1] < 0))
			px[1] = 0;
		else
			px[1] = static_cast<char>(bottom[i][1] - top[i][1]); // Green pixel
		if ((static_cast<int>(bottom[i][2]) - top[i][2] < 0))
			px[2] = 0;
		else
			px[2] = static_cast<char>(bottom[i][2] - top[i][2]); // Red Pixel
		
		++i;
	}

	return out;
}

Image* Add(Image* image , int num, char channel) {
	Image* out = image;

	if (channel == 'b') {

		for (unsigned char*& i : out->GetPixels()) {
			if (static_cast<int>(i[0]) + num > 255)
				i[0] = 255;
			else {
				i[0] += static_cast<int>(num);
				i[0] = static_cast<unsigned char>(i[0]);
			}
		}
	}
	else if (channel == 'g') {

		for (unsigned char*& i : out->GetPixels()) {
			if (static_cast<int>(i[1]) + num > 255)
				i[1] = 255;
			else {
				i[1] += static_cast<int>(num);
				i[1] = static_cast<unsigned char>(i[1]);
			}
		}
	}
	else if (channel == 'r') {

		for (unsigned char*& i : out->GetPixels()) {
			if (static_cast<int>(i[2]) + num > 255)
				i[2] = 255;
			else {
				i[2] += static_cast<int>(num);
				i[2] = static_cast<unsigned char>(i[2]);
			}
		}
	}

	return out;
}

Image* Add(Image* I1, Image* I2, char channel) { // The second image is the channel to be copied.
	Image* out = I1;

	std::vector<unsigned char*> I1Px = out->GetPixels();
	std::vector<unsigned char*> I2Px = I2->GetPixels();
	
	if (channel == 'b') {
		int i = 0;
		for (unsigned char*& px : I1Px) {
			px[0] = I2Px[i][0];
			++i;
		}
	}
	else if (channel == 'g') {
		int i = 0;
		for (unsigned char*& px : I1Px) {
			px[1] = I2Px[i][1];
			++i;
		}
	}
	else if (channel == 'r') {
		int i = 0;
		for (unsigned char*& px : I1Px) {
			px[2] = I2Px[i][2];
			++i;
		}
	}


	return out;
}

Image* Overlay(Image* I1, Image* I2) {
	Image* out = I1;

	std::vector<float*> I1_Norm = Normalize(I1->GetPixels());
	std::vector<float*> I2_Norm = Normalize(I2->GetPixels());

	int i = 0;

	for (unsigned char*& px : out->GetPixels()) {

		// Blue channels.
		if(I2_Norm[i][0] <= 0.5){
			px[0] = static_cast<unsigned char>((2 * I2_Norm[i][0] * I1_Norm[i][0]) * 255 + 0.5f);
		}
		else if (I2_Norm[i][0] > 0.5) {
			px[0] = static_cast<unsigned char>((1 - (2 * (1 - I1_Norm[i][0]) * (1 - I2_Norm[i][0]))) * 255 + 0.5f); // 1 - (2 * (1 - NP1)  * (1 - NP2))
		}

		// Green channels.
		if (I2_Norm[i][1] <= 0.5) {
			px[1] = static_cast<unsigned char>((2 * I2_Norm[i][1] * I1_Norm[i][1]) * 255 + 0.5f);
		}
		else if (I2_Norm[i][1] > 0.5) {
			px[1] = static_cast<unsigned char>((1 - (2 * (1 - I1_Norm[i][1]) * (1 - I2_Norm[i][1]))) * 255 + 0.5f);
		}

		// Red channels.
		if (I2_Norm[i][2] <= 0.5) {
			px[2] = static_cast<unsigned char>((2 * I2_Norm[i][2] * I1_Norm[i][2]) * 255 + 0.5f);
		}
		else if (I2_Norm[i][2] > 0.5) {
			px[2] = static_cast<unsigned char>((1 - (2 * (1 - I1_Norm[i][2]) * (1 - I2_Norm[i][2]))) * 255 + 0.5f);
		}

		++i;
	}

	return out;
}

std::vector<float*> Normalize(std::vector<unsigned char*> &pixels) {
	std::vector<float*> normal_pixels;
	
	for (unsigned char*& i : pixels) {
		float* pixel = new float[3];
		pixel[0] = (static_cast<float>(i[0]) / 255);
		pixel[1] = (static_cast<float>(i[1]) / 255);
		pixel[2] = (static_cast<float>(i[2]) / 255);
		normal_pixels.push_back(pixel);
	}

	return normal_pixels;
}

Image* Multiply(Image* _top, Image* _bottom){

	Image* out = _top;

	// First normalizing the pixels in both images.
	std::vector<float*> top_px = Normalize(_top->GetPixels());
	std::vector<float*> bot_px = Normalize(_bottom->GetPixels());

	int i = 0;
	for (unsigned char*& px : out->GetPixels()) { // Iterating through the _image which is the output image.
		px[0] = static_cast<char>((top_px[i][0] * bot_px[i][0]) * 255 + 0.5f); // Blue pixel
		px[1] = static_cast<char>((top_px[i][1] * bot_px[i][1]) * 255 + 0.5f); // Green pixel
		px[2] = static_cast<char>((top_px[i][2] * bot_px[i][2]) * 255 + 0.5f); // Red Pixel
		++i;
	}

	return out;
}

Image* Multiply(Image* image, int scale, char channel) {
	Image* out = image;

	float normal = 0.0f; // calculates and stores the normalized channel value.

	// Multiplying a pixel example.
	if (channel == 'b') {

		for (unsigned char*& i : out->GetPixels()) { // For each uses an iterator to quickly change every pixel in this 512x512 image. Source: https://www.geeksforgeeks.org/g-fact-40-foreach-in-c-and-java/ : cutting down from 4 minutes to 1.56 seconds.
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the b value is accessed through i[0]. 
			normal = (static_cast<float>((i[0])) / 255) * scale * 255 + 0.5f;
			
			if (normal > 255) // Checking for overflow.
				i[0] = 255;
			else
				i[0] = static_cast<unsigned char>(normal);
		}
		
	}
	else if (channel == 'g') {

		for (unsigned char*& i : out->GetPixels()) { 
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the g value is accessed through i[1]. 
			normal = (static_cast<float>((i[1])) / 255) * scale * 255 + 0.5f;
			
			if (normal > 255) // Checking for overflow.
				i[1] = 255;
			else
				i[1] = static_cast<unsigned char>(normal);
		}
	}
	else if (channel == 'r') {

		for (unsigned char*& i : out->GetPixels()) { // For each uses an iterator to quickly change every pixel in this 512x512 image. Source: https://www.geeksforgeeks.org/g-fact-40-foreach-in-c-and-java/ : cutting down from 4 minutes to 1.56 seconds.
			// i is the dynamic array containing the b,g,r values of the pixel.
			// the r value is accessed through i[2]. 
			normal = (static_cast<float>((i[2])) / 255) * scale * 255 + 0.5f;
			
			if (normal > 255) // Checking for overflow.
				i[2] = 255;
			else
				i[2] = static_cast<unsigned char>(normal);
		}
	}


	return out;
}

Image* Screen(Image* top, Image* bottom) {
	std::vector<float*> P1 = Normalize(top->GetPixels());
	std::vector<float*> P2 = Normalize(bottom->GetPixels());

	int i = 0;
	for (unsigned char*& px : bottom->GetPixels()) {
		float* pixel = new float[3];
		
		pixel[0] = (1 - P1[i][0]) * (1 - P2[i][0]); // Blue channel.
		pixel[0] = 1 - pixel[0];
		pixel[0] = pixel[0] * 255 + 0.5f;
		px[0] = static_cast<unsigned char>(pixel[0]);

		pixel[1] = (1 - P1[i][1]) * (1 - P2[i][1]); // Green channel.
		pixel[1] = 1 - pixel[1];
		pixel[1] = pixel[1] * 255 + 0.5f;
		px[1] = static_cast<unsigned char>(pixel[1]);

		pixel[2] = (1 - P1[i][2]) * (1 - P2[i][2]); // Red channel.
		pixel[2] = 1 - pixel[2];
		pixel[2] = pixel[2] * 255 + 0.5f;
		px[2] = static_cast<unsigned char>(pixel[2]);

		++i;
	}

	return bottom;
}

void WriteFile(std::string _file, Image* _image) {
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
	Image* out;
	
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

	out = new Image(pixels, id_len, color_map_type, image_type, color_map_origin, color_map_length, color_map_depth, x_origin, y_origin, width, height, pixel_depth, image_descriptor);

	file.close();
	return out;

	//// Memory deallocation.
	//for (unsigned int i = 0; i < pixels.size(); i++) {
	//	delete[] pixels[i];
	//}
}

void Task1() {
	Image* L1 = LoadFile("layer1.tga");
	Image* L2 = LoadFile("pattern1.tga");
	WriteFile("part1.tga", Multiply(L1, L2));
}
void Task2() {
	Image* Top = LoadFile("layer2.tga");
	Image* Bot = LoadFile("car.tga");
	WriteFile("part2.tga", Subtract(Top, Bot));
}
void Task3() {
	Image* I1 = LoadFile("layer1.tga");
	Image* I2 = LoadFile("pattern2.tga");
	Image* out = Multiply(I1, I2);
	Image* TEXT = LoadFile("text.tga");

	WriteFile("part3.tga", Screen(TEXT, out));
}
void Task4() {
	Image* I1 = LoadFile("layer2.tga");
	Image* I2 = LoadFile("circles.tga");
	Image* out = Multiply(I1, I2);
	Image* I3 = LoadFile("pattern2.tga");

	WriteFile("part4.tga", Subtract(I3,out));
}
void Task5() {
	Image* I1 = LoadFile("layer1.tga");
	Image* I2 = LoadFile("pattern1.tga");

	WriteFile("part5.tga", Overlay(I1, I2));
}
void Task6() {
	Image* image = LoadFile("car.tga");
	WriteFile("part6.tga", Add(image, 200, 'g'));
}
void Task7() {
	Image* image = LoadFile("car.tga");

	image = Multiply(image, 4, 'r');
	image = Multiply(image, 0, 'b');

	WriteFile("part7.tga", image);
}
void Task8() {
	// Load separate times.
	Image* red = LoadFile("car.tga");
	Image* green = LoadFile("car.tga");
	Image* blue = LoadFile("car.tga");

	// Iterate through the pixels, to create a grayscale image based on red.
	for (unsigned char*& px : red->GetPixels()) {
		px[0] = px[2];
		px[1] = px[2];
	}
	// Iterate through the pixels, to create a grayscale image based on green.
	for (unsigned char*& px : green->GetPixels()) {
		px[0] = px[1];
		px[2] = px[1];
	}
	// Iterate through the pixels, to create a grayscale image based on blue.
	for (unsigned char*& px : blue->GetPixels()) {
		px[1] = px[0];
		px[2] = px[0];
	}

	// Write the files.
	WriteFile("part8_r.tga", red);
	WriteFile("part8_g.tga", green);
	WriteFile("part8_b.tga", blue);
}
void Task9() {
	Image* red = LoadFile("layer_red.tga");
	Image* green = LoadFile("layer_green.tga");
	Image* blue = LoadFile("layer_blue.tga");

	Image* res = LoadFile("layer_red.tga"); // Used as baseline.

	res = Add(res, red, 'r');
	res = Add(res, green, 'g');
	res = Add(res, blue, 'b');

	WriteFile("part9.tga", res);
}
void Task10() {}
