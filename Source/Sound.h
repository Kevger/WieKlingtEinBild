#pragma once
#include <vector>

static constexpr double DEFAULT_SAMPLINGRATE = 44100;
static constexpr double DEFAULT_AUDIOVOLUME = 100;
static constexpr size_t DEFAULT_BUFFERSIZE = 128;


/**
 * \brief Klasse zur Erzeugung von Toenen
 */
class Sound
{
private:
	/**
	 * \brief Puffer fuer die Audiodaten
	 */
	std::vector<double> buffer;

	/**
	 * \brief Abtastfrequenz welche zur Tonerzeugung genutzt wird
	 */
	const double samplingFrequency	{ DEFAULT_SAMPLINGRATE };

	/**
	 * \brief Grundlautstaerke
	 */
	const double audioVolume		{ DEFAULT_AUDIOVOLUME };

	/**
	 * \brief Letzte Position der Sinuswelle bei verlassen der Funktion addFrequency
	 */
	double lastPos{ 0 };

	/**
	 * \brief Groesse des Puffers
	 */
	const size_t bufferSize{ DEFAULT_BUFFERSIZE };
public:

	/**
	 * \brief Standardkonstruktor
	 */
	Sound();

	/**
	 * \brief Konstruktor
	 * \param samplingFrequency: Abtastrate fuer Tonerzeugung
	 * \param audioVolume: Grundlautstaerke
	 * \param bufferSize: Puffergroesse. Je groesser desto groesser/laenger ein Sample und Rechenaufwand
	 */
	Sound(double samplingFrequency, double audioVolume, size_t bufferSize);


	/**
	 * \brief Einen Ton mit einer bestimmter Frequenz&Amplitude aufaddieren
	 * \param volume Amplitude (Lautstarke) der Frequenz
	 * \param frequency Frequenz in Hz
	 */
	void addFrequency(double volume, double frequency);


	/**
	 * \brief Den zuvor beschriebenen Puffer auslesen.
	 * \return Konstante Referenz auf den Puffer
	 */
	const std::vector<double>& getBuffer() const;


	/**
	 * \brief Puffer loeschen/zuruecksetzen
	 */
	void resetBuffer();

	~Sound() = default;
};

