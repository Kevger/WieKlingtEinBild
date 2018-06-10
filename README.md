# Wie klingt ein Bild? Anwendungen der 2D Signalverarbeitung 

Vorwort
-------
Im Rahmen vom interdisziplinären Wahlfach "Anwendungen der 2D Signalverarbeitung (HOTSPOT Wie klingt ein Bild?)" an der HS Pforzheim, habe ich mich mit der Umwandlung von Bild (.bmp) in Audiodaten (.wav) beschäfigt.
Meine Aufgabe im Team war es, das Back-End in C++ zu implementieren. 

Auf externe Bibliotheken wurde verzichtet, weswegen sich das Einlesen und Ausgeben von Daten auf .bmp und .wav Dateien beschränkt.
Eine Doxygen Dokumentation liegt dem Repo bei.

Das Front-End zu diesem Back-End ist hier verfügbar:
[Wie klingt ein Bild? - Front-End](https://github.com/PErlenmaier/WieKlingtEinBild "Hier zum Repository vom Front-End")

Implementierte Algorithmen
--------------------------
0) Links-Rechts-Scan (LR_SCAN)
Bild wird von links nach rechts spaltenweise durchgescannt.
Jede Zeile steht für eine Frequenz. Je intensiver RGB vom Pixel, desto höher die Amplitude der jeweiligen Frequenz.
Nur Pixel mit einer Mindestintensität erhalten eine Amplitude größer 0 erhalten. 
![](/Dokumentation/_readme/LR_SCAN.png) 

1) Links-Rechts-Scan ohne Aktivierungsschwelle (LR_SCAN_NO_THRESHOLD)
Identisch mit (0), nur das alle Pixel egal wie schwach auch diese sind beachtet werden. 
Ist eher verrauscht als (0).
![](/Dokumentation/_readme/LR_SCAN2.png)

2) Oben-Unten-Scan (UD_SCAN)
Identisch mit (0) aber anstatt von links nach rechts, diesmal von oben nach unten.

3) Oben-Unten-Scan ohne Aktivierungsschwelle(UD_SCAN_NO_THRESHOLD)
Identisch mit (2) nur ohne Aktivierungsschwelle wie in (1).

4) TRIPLET
Springt immer um drei Byte (oder Vielfache) durch das Bild und erzeugt anhand von Rot eine Frequenz, mit Grün die Amplitude dieser und optional mit Blau die Dauer der Frequenz.

5) TRIPLET_JMP
Identisch mit (5) nur das Blau jetzt den Offset zum nächsten Triplet bestimmt. Die Dauer vom Ton wird durch Farbintensitaet RGB bestimmt.
![](/Dokumentation/_readme/TRIPLET.png)


6) UD_LR_SCAN
Das Bild wird von oben nach unten und von links nach rechts gleichzeitig gescannt.
Die Senkrechte zur X-Achse und die Parallele erzeugen beide jeweils einen Ton. Jeder Ton wird abhängig vom jeweiligen Farbanteil erzeugt. Rot bestimmt die Frequenz, Grün bestimmt die Lautstärke und der gemeinsame Blauanteil die Dauer der beiden Töne.

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
Aufruf vom Programm z.B. über Eingabeaufforderung.
WieKlingtEinBild.exe Beispiel.bmp Beispiel.wav 44100 100 256 0 12000 160 0 0



