#define _USE_MATH_DEFINES
#include "Sound.h"
#include <cmath>

Sound::Sound()
{
	buffer.resize(bufferSize, 0);
}

Sound::Sound(const double samplingFrequency, const double audioVolume, size_t bufferSize)
	: samplingFrequency(samplingFrequency), audioVolume(audioVolume), bufferSize(bufferSize)
{
	buffer.resize(bufferSize, 0);
}

void Sound::addFrequency(const double volume, const double frequency)
{
	const auto dt = 2.0 * M_PI * frequency / samplingFrequency;
	const auto  currentVolume = volume * audioVolume;

	for (auto i = 0; i != bufferSize; ++i)
		buffer[i] += currentVolume * std::sin(dt * i + lastPos);
	lastPos += dt * bufferSize;

	while (lastPos > 2 * M_PI)
		lastPos -= 2 * M_PI;
}

const std::vector<double>& Sound::getBuffer() const
{
	return buffer;
}

void Sound::resetBuffer()
{
	std::fill(buffer.begin(), buffer.end(), 0.0);
}
