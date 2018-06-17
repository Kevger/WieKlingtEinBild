#include <iostream>
#include "Processing.h"

int main(int argc, char* argv[])
{

	/*********Grundeinstellungen*********
	*  1: Bilddateiname (.bmp)
	*  2. Audiodateiname (.wav)
	*  3. Abtastfrequenz (normalerweise 44100)
	*  4. Grundlautstaerke (Wertebereich je nach Bild um die 100)
	*  5. Puffergroesse (oft 128 - 2048). Hoeherer Wert -> groesserer Rechenaufwand und Audiolaenge
	*  6. Algorithmustyp
	*******Algorithmuseinstellungen******
	*  7. Settings1
	*  8. Settings2
	*  9. Settings3
	*  A. Ínvertiert Pixel betrachten (Settings4). Wenn != 0 dann invertiert. 
	*************************************/

	//Anzahl der Parameter ueberpruefen
	if (argc != 11)
	{
		std::cerr
			<< "Falsche Anzahl von Argumenten (erwartet 10): " << argc
			<< "\n*********Eingabeformat*********\n"
			<< "* 1: Bilddateiname(.bmp)\n"
			<< "* 2. Audiodateiname(.wav)\n"
			<< "* 3. Abtastfrequenz(normalerweise 44100)\n"
			<< "* 4. Grundlautstaerke(Wertebereich je nach Bild um die 100)\n"
			<< "* 5. Puffergroesse(oft 128 - 2048).Hoeherer Wert->groesserer Rechenaufwand und Audiolaenge\n"
			<< "* 6. Algorithmustyp\n"
			<< "* 7. Settings1 (Maximale Frequenz)\n"
			<< "* 8. Settings2 (Aktivierungsschwelle oder Tondauer)\n"
			<< "* 9. Settings3\n"
			<< "* A. Invertiert Pixel betrachten aktivieren(Settings4)\n" 
			<< "*******************************\n"
			<< std::endl;
		return -1;
	}

	//Bilddatei Name
	std::string imageName = argv[1];
	std::cout << "Bild Dateiname: " << imageName << std::endl;
	//sounddatei Name
	std::string soundName = argv[2];
	std::cout << "Audio Dateiname: " << soundName << std::endl;

	//Grundeinstellungen fuer Tonerzeugung
	Processing::ProcessingSettings processingSettings;
	processingSettings.samplingFrequency = std::stod(argv[3]);
	processingSettings.audioVolume = std::stod(argv[4]);
	processingSettings.samples = std::stoi(argv[5]);

	std::cout << "Abtastfrequenz: " << processingSettings.samplingFrequency << std::endl;
	std::cout << "Lautstaerke: " << processingSettings.audioVolume << std::endl;
	std::cout << "Buffergroesse: " << processingSettings.samples << std::endl;

	//Zusaetzliche Einstellungen fuer den Algorithmus
	Processing::ProcessingAlgorithm processingAlgorithm;
	*(reinterpret_cast<int*>(&processingAlgorithm)) = std::stoi(argv[6]);
	Processing::AdditionalSettings additionalSettings;
	additionalSettings.settings1 = std::stod(argv[7]);
	additionalSettings.settings2 = std::stod(argv[8]);
	additionalSettings.settings3 = std::stod(argv[9]);
	additionalSettings.settings4 = std::stod(argv[10]);

	std::cout << "\nStarte Umwandlung..." << std::endl;

	//Umwandlung von Bild in Ton durchfueren
	Processing::Processing processing;
	processing.start(imageName, soundName, processingAlgorithm, processingSettings,
	                 additionalSettings);
	std::cout << "\nUmwandlung beendet\n" << std::endl;
	return 0;
}
