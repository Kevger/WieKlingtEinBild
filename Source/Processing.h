#pragma once
#include "Image.h"
#include "Sound.h"
#include "Wave.h"
#include <memory>


/**
 * \brief Beeinhaltet Datenstrukturen zur Umwandlung von Bildinformationen in Toene
 */
namespace Processing
{

	/**
	 * \brief Verfuegbare Algorithmen
	 */
	enum class ProcessingAlgorithm
	{
		LR_SCAN = 0,
		LR_SCAN_NO_THRESHOLD,
		UD_SCAN,
		UD_SCAN_NO_THRESHOLD,
		TRIPLET,
		TRIPLET_JMP,
		UD_LR_SCAN
		//TODO Mehr implementieren
	};

	/**
	 * \brief Grundeinstellungen fuer die Tonerzeugung
	 */
	struct ProcessingSettings
	{
		///Grundlautstaerke
		double audioVolume = 50; 
		///Abtastrate
		double samplingFrequency = 44100;
		///Anzahl der Samples pro Frequenzgenerierung, erhoeht die Tondauer&Rechenaufwand
		size_t samples = 128;	
	};


	/**
	 * \brief Zusaetzliche Einstellungen spezifisch fuer die verschienden Algorithmen
	 */
	struct AdditionalSettings
	{
		/**
		* \brief Zusaetzliche Einstellung spezifisch fuer die verschiedenen Algorithmen\n
		* LR_SCAN: Maximale Frequenz\n
		* LR_SCAN_NO_THRESHOLD: Maximale Frequenz\n
		* UD_SCAN: Maximale Frequenz\n
		* UD_SCAN_NO_THRESHOLD: Maximale Frequenz\n
		* TRIPLET: -\n
		* TRIPLET_JMP: - \n
		* UD_LR_SCAN: Maximale Frequenz
		*/
		uint64_t settings1 = 0;

		/**
		* \brief Zusaetzliche Einstellunge spezifisch fuer die verschiedenen Algorithmen\n
		* LR_SCAN: Aktivierungsschwelle fuer Pixel\n
		* LR_SCAN_NO_THRESHOLD: -\n
		* UD_SCAN: Aktivierungsschwelle fuer Pixel\n
		* UD_SCAN_NO_THRESHOLD: -\n
		* TRIPLET: Tondauer abhaengig von dem Blauanteil (0-255)\n
		* TRIPLET_JMP: Tondauer abhaengig von der Pixelintensitaet\n
		* UD_LR_SCAN: Tondauer abhaengig vom Blauanteil
		*/
		uint64_t settings2 = 0;

		/**
		* \brief Zusaetzliche Einstellunge spezifisch fuer die verschiedenen Algorithmen\n
		* LR_SCAN: -\n
		* LR_SCAN_NO_THRESHOLD: -\n
		* UD_SCAN: -\n
		* UD_SCAN_NO_THRESHOLD: -\n
		* TRIPLET: Anzahl der Triplets die man pro Frequenz ueberspringen soll\n
		* TRIPLET_JMP: Anzahl der Zyklen durch die Bilddaten (z.B. 128)\n
		* UD_LR_SCAN: -
		*/
		uint64_t settings3 = 0;

		/**
		* \brief Zusaetzliche Einstellunge spezifisch fuer die verschiedenen Algorithmen\n
		* LR_SCAN: Pixel invertieren\n
		* LR_SCAN_NO_THRESHOLD: Pixel invertieren\n
		* UD_SCAN: Pixel invertieren\n
		* UD_SCAN_NO_THRESHOLD: Pixel invertieren\n
		* TRIPLET: Pixel invertieren\n
		* TRIPLET_JMP: Pixel invertieren\n
		* UD_LR_SCAN: Pixel invertieren
		*/
		uint64_t settings4 = 0;
	};


	/**
	 * \brief Klasse zur Umwandlung von Bilddaten in Tondaten 
	 */
	class Processing
	{
	private:
		std::unique_ptr<Image> image;
		std::unique_ptr<Sound> sound;
		std::unique_ptr<Wave> wave;


		/**
		 * \brief Bild wird von Links nach Rechts spaltenweise durchgescannt. Jede Zeile steht fuer eine Frequenz. 
		 * Je intensiver RGB vom Pixel desto hoeher die Amplitude der jeweiligen Frequenz. Pixel werden nur betrachtet, 
		 * wenn der Durschnitt von RGB > Aktivierungsschwelle ist
		 * 
		 * \param additionalSettings:\n
		 *  Settings1: Maximale Frequenz\n
		 *  Settings2: Aktivierungsschwelle fuer Pixel\n
		 *  Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		 */
		void lrScan(const AdditionalSettings& additionalSettings); 


		/**
		* \brief Bild wird von Links nach Rechts spaltenweise durchgescannt. Jede Zeile steht fuer eine Frequenz.
		* Je intensiver RGB vom Pixel desto hoeher die Amplitude der jeweiligen Frequenz. Keine Aktivierungsgrenze
		*
		* \param additionalSettings:\n
		*  Settings1: Maximale Frequenz\n
		*  Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		*/
		void lrScan_no_threshold(const AdditionalSettings& additionalSettings); 


		/**
		* \brief Bild wird von Oben nach Unten zweilenweise durchgescannt. Jede Spalte steht fuer eine Frequenz.
		* Je intensiver RGB vom Pixel desto hoeher die Amplitude der jeweiligen Frequenz. Pixel werden nur betrachtet, 
		* wenn der Durschnitt von RGB > Aktivierungsschwelle ist
		*
		* \param additionalSettings:\n
		*  Settings1: Maximale Frequenz\n
		*  Settings2: Aktivierungsschwelle fuer Pixel\n
		*  Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		*/
		void udScan(const AdditionalSettings& additionalSettings); 


		/**
		* \brief Bild wird von Oben nach Unten zweilenweise durchgescannt. Jede Spalte steht fuer eine Frequenz.
		* Je intensiver RGB vom Pixel desto hoeher die Amplitude der jeweiligen Frequenz. Keine Aktivierungsschwelle
		*
		* \param additionalSettings:\n
		*  Settings1: Maximale Frequenz\n
		*  Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		*/
		void udScan_no_threshold(const AdditionalSettings& additionalSettings); 


		/**
		 * \brief Bild wird immer um 3 Byte (Triplet) oder Vielfache durchgesprungen. Jede Farbe hat eine Eigenschaft bei der Tonerzeugung 
		 * Rot: Lautstaerke ; Gruen: Tonhoehe; Blau: Tondauer
		 * 
		 * \param additionalSettings:\n
		 * Settings2: Tondauer abhaengig von dem Blauanteil\n
		 * Settings3: Anzahl der Triplets die man pro Frequenz ueberspringen soll\n
		 * Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		 */
		void triplet(const AdditionalSettings& additionalSettings); 


		/**
		 * \brief Bild wird mit einem Offset abhaengig von der Farbe durchgesprungen
		 * Rot: Lautstarke, Gruen: Tonhoehe; Blau: keine Funktion
		 * 
		 * \param additionalSettings:\n
		 * Settings2: Tondauer abhaengig von der Pixelintensitaet\n
		 * Settings3: Anzahl der Zyklen durch die Bilddaten (z.B. 128)\n
		 * Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		 */
		void triplet_jmp(const AdditionalSettings& additionalSettings); 


		/**
		 * \brief Das Bild wird von oben nach unten und von links nach rechts gleichzeitig gescannt. 
		 * Die Senkrechte zur X-Achse und die Parallele erzeugen beide jeweils einen Ton. \n
		 * Jeder Ton wird abhaengig von jeweiligen Farbanteil erzeugt.\n
		 * Rot bestimmt die Frequenz, Gruen bestimmt die Lautstaerke und der gemeinsame Blauanteil die Dauer der beiden Frequenzen.
		 * 
		 * \param additionalSettings:\n
		 * Settings1: Max Frequenz\n
		 * Settings2: Tondauer abhaengig von dem Blauanteil\n
		 * Settings4: Wenn != 0, dann werden die Pixel invertiert betrachtet
		 */
		void ud_lr_scan(const AdditionalSettings& additionalSettings);	

	public:
		/**
		 * \brief Starte die Umwandlung eines Bildes in eine Audiodatei, anhand eines vorgegebenen Algorithmus.
		 * \param imageFile: Dateiname vom Bild
		 * \param outputFile: Dateiname der zu erstellenden Audiodatei
		 * \param algorithm: Algorithmus der fuer die Umwandlung genutzt wird
		 * \param settings: Allgemeine Einstellungen fuer die Tonerzeugung
		 * \param additionalSettings: Spezifische Einstellungen fuer den jeweiligen Algorithmus
		 */
		void start(const std::string& imageFile, const std::string& outputFile, ProcessingAlgorithm algorithm,
		           const ProcessingSettings& settings, const AdditionalSettings& additionalSettings);

		/**
		 * \brief Standardkonstruktor
		 */
		Processing() = default;

		/**
		 * \brief Kopieren nicht moeglich
		 */
		Processing(const Processing & other) = delete;

		/**
		 * \brief Zuweisung nicht moeglich
		 */
		Processing& operator=(const Processing & other) = delete;

		/**
		 * \brief Movezuweisung nicht moeglich
		 */
		Processing& operator=(Processing&& other) = delete;
	};
}
