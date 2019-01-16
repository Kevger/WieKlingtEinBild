![](/Dokumentation/_readme/infographic.png) 

Das Front-End zu diesem Back-End ist hier verfügbar:
[Wie klingt ein Bild? - Front-End](https://github.com/PErlenmaier/WieKlingtEinBild "Hier zum Repository vom Front-End")


Anleitung
---------
Der Aufruf vom Programm, muss mit der Übergabe von 10 Parametern erfolgen.

### Grundeinstellungen für die Parameterübergabe:
1) Bilddateiname (zwingend .bmp)
2) Audiodateiname (zwingend .wav)
3) Abtastfrequenz (normalerweise 44100)
4) Grundlautstaerke (Wertebereich je nach Bild um die 100)
5) Puffergröße (oft 128 - 2048). Größerer Wert -> Größerer Rechenaufwand und Tondauer
6) Algorithmustyp (0 für LR_SCAN bis 6 für UD_LR_SCAN)
7) Algorithmus spezische Einstellung 1
8) Algorithmus spezische Einstellung 2
9) Algorithmus spezische Einstellung 3
10) Alle Pixel invertiert betrachten (falls Argument ungleich 0, dann aktiv)

#### Algorithmus spezische Einstellung 1:
- LR_SCAN: Maximale Frequenz
- LR_SCAN_NO_THRESHOLD: Maximale Frequenz
- UD_SCAN: Maximale Frequenz
- UD_SCAN_NO_THRESHOLD: Maximale Frequenz
- TRIPLET: -
- TRIPLET_JMP: - 
- UD_LR_SCAN: Maximale Frequenz

#### Algorithmus spezische Einstellung 2:
- LR_SCAN: Aktivierungsschwelle für Pixel
- LR_SCAN_NO_THRESHOLD: -
- UD_SCAN: Aktivierungsschwelle für Pixel
- UD_SCAN_NO_THRESHOLD: - 
- TRIPLET: Tondauer abhaengig von dem Blauanteil (0-255)
- TRIPLET_JMP: Tondauer abhaengig von der Pixelintensitaet
- UD_LR_SCAN: Tondauer abhaengig vom Blauanteil

#### Algorithmus spezische Einstellung 3:
- LR_SCAN: - 
- LR_SCAN_NO_THRESHOLD: - 
- UD_SCAN: - 
- UD_SCAN_NO_THRESHOLD: - 
- TRIPLET: Anzahl der Triplets die man pro Frequenz überspringen soll
- TRIPLET_JMP: Anzahl der Zyklen durch die Bilddaten (z.B. 128)
- UD_LR_SCAN: -

Beispiel
--------
Der Aufruf vom Programm z.B. über Eingabeaufforderung.
```
WieKlingtEinBild.exe Beispiel.bmp Beispiel.wav 44100 100 256 0 12000 160 0 0
```


