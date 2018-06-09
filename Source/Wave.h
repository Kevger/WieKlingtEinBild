#pragma once
#include <fstream>

static constexpr auto DEFAULT_BITS_PER_SAMPLE = 16;
static constexpr auto DEFAULT_BYTES_PER_SAMPLE = DEFAULT_BITS_PER_SAMPLE / 8;

/**
 * \brief Klasse zur Erzeugung von .wav Audiodateien
 */
class Wave
{
private:
	/**
	 * \brief Bereitet Header fur Audiodatei vor
	 */
	void prepareHeader();

	/**
	 * \brief Outputfilestream. Genutzt um Audiodaten in Datei zu schreiben
	 */
	std::ofstream file{"WieKlingtEinBild.wav", std::ios::binary};

	/**
	 * \brief Header der .wav Datei 
	 */
	struct
	{
		//little endian
		///Keine zusaetzlichen Daten
		const uint32_t subChunk1Size{16}; 
		///Keine Kompression
		const uint16_t audioFormat{1}; 
		///Anzahl der Channel (hier: 1)
		const uint16_t numChannels{1}; 
		///Abtastrate 
		uint32_t sampleRate{44100}; 
		///Abtastrate* Frame Groesse
		const uint32_t byteRate{static_cast<uint32_t>(sampleRate * numChannels * DEFAULT_BYTES_PER_SAMPLE)}; 
		///Allignment. numChannels * DEFAULT_BYTES_PER_SAMPLE
		const uint16_t blockAlign{static_cast<uint16_t>(numChannels * DEFAULT_BYTES_PER_SAMPLE)};
		///Bits pro Samplewert pro Kanal
		const uint16_t bitsPerSample{DEFAULT_BITS_PER_SAMPLE}; 
	} waveHeader;

public:

	/**
	 * \brief Konstruktor
	 * \param fileName: Dateiname der zu erzeugenden Audiodatei (.wav)
	 * \param sampleRate: Abtastrate der Audiodatei
	 */
	Wave(std::string fileName, uint32_t sampleRate);

	/**
	 * \brief Standardkonstruktor
	 */
	Wave();

	/**
	 * \brief Schreibt Daten in Audiodatei
	 * \tparam T Typ von Daten z.B. uint16_t
	 * \param data Daten die geschrieben werden sollen
	 */
	template <typename T>
	void writeSamples(T data)
	{
		auto size = sizeof(T);
		while (size--)
		{
			file.put(static_cast<uint8_t>(data & 0xFF));
			data >>= 8;
		}
	}

	/**
	 * \brief Header fertig machen. Erst nutzen wenn Audiodateien fertig beschrieben wurde.
	 */
	void finishHeader();

	/**
	* \brief Audiodatei schliesen
	*/
	void closeFile();

	~Wave();
};
