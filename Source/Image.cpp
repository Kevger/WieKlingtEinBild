#include "Image.h"
#include <iostream>

void Image::readHeader()
{
	//BitmapFileHeader
	file.read(reinterpret_cast<char*>(&(bitmapFileHeader.bfType)), 2);
	file.read(reinterpret_cast<char*>(&(bitmapFileHeader.bfFileSize)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapFileHeader.bfRes1)), 2);
	file.read(reinterpret_cast<char*>(&(bitmapFileHeader.bfRes2)), 2);
	file.read(reinterpret_cast<char*>(&(bitmapFileHeader.bfStartAdress)), 4);
	//BitmapInfoHeader
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biSize)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biWidth)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biHeight)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biColorPlanes)), 2);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biBitsPerPixel)), 2);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biCompression)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biImageSize)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biHorizontalResolution)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biVerticalResolution)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biColorsPerColorPalette)), 4);
	file.read(reinterpret_cast<char*>(&(bitmapInfoHeader.biImportantColorsUsed)), 4);

	if (bitmapFileHeader.bfRes1 || bitmapFileHeader.bfRes2 || bitmapInfoHeader.biColorPlanes != 1)
		std::cout << "Error. FileFormat is wrong." << std::endl;
}

void Image::readImageData()
{
	//Genug freien speicher erhalten
	bitmapData.resize(bitmapInfoHeader.biHeight);
	for (auto& y : bitmapData)
		y.resize(bitmapInfoHeader.biWidth);

	//Bilddaten einlesen
	for (auto& y : bitmapData)
		for (auto& x : y)
			file.read(reinterpret_cast<char*>(&(x)), 3);
}

Image::Image(std::string fileName):
	bitmapFileHeader{0}, bitmapInfoHeader{0}, file(fileName, std::ios::binary)
{
	readHeader();
	readImageData();
}


Image::~Image()
{
	if (file.is_open())
		file.close();
}
