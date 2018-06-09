#include "Wave.h"


void Wave::prepareHeader()
{
	//big endian
	file << "RIFF____WAVEfmt ";
	//little endian
	writeSamples(waveHeader.subChunk1Size);
	writeSamples(waveHeader.audioFormat);
	writeSamples(waveHeader.numChannels);
	writeSamples(waveHeader.sampleRate);
	writeSamples(waveHeader.byteRate);
	writeSamples(waveHeader.blockAlign);
	writeSamples(waveHeader.bitsPerSample);
	//big endian
	file << "data____";
	//Datei ist bereit, beschrieben zu werden
}

Wave::Wave(std::string fileName, uint32_t sampleRate): file{fileName, std::ios::binary}
{
	waveHeader.sampleRate = sampleRate;
	prepareHeader();
}

Wave::Wave()
{
	prepareHeader();
}

void Wave::finishHeader()
{
	//Groesse der Datei erhalten
	const auto sizeOfFile = static_cast<const uint32_t>(file.tellp());
	//ChunkSize befuellen
	file.seekp(4);
	writeSamples(sizeOfFile - 8);
	//SubChunk2Size befuellen
	file.seekp(40);
	writeSamples(sizeOfFile - 28);
}

void Wave::closeFile()
{
	file.close();
}

Wave::~Wave()
{
	if (file.is_open())
		file.close();
}
