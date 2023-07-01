#include <iostream>
#include <fstream>
#include <math.h>

void generateImageFromLSystem(const std::string& lsystem, const std::string& filename) {
    // Implementa qui la generazione dell'immagine basata sul L-system
    // Utilizza le istruzioni per determinare la struttura dell'immagine
    // Puoi utilizzare librerie esterne come OpenCV o SFML per creare l'immagine finale

    // Esempio: scrivi un file SVG per rappresentare il risultato del L-system
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Errore nell'apertura del file." << std::endl;
        return;
    }

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" style=\"background-color: white;\">" << std::endl;


    // Posizione iniziale
    double x = 0.0;
    double y = 0.0;

    // Angolo iniziale
    double angle = 0.0;

    // Lunghezza del passo
    double stepLength = 10.0;

    // Aggiungi qui il codice per interpretare le istruzioni L-system e disegnare le linee corrispondenti
    for (char c : lsystem) {
        if (c == 'A' || c == 'B' || c == 'F') {
            // Avanza nella direzione corrente
            double newX = x + stepLength * cos( angle * M_PI / 180.0 );
            double newY = y + stepLength * sin( angle * M_PI / 180.0 );

            // Disegna una linea dal punto corrente al nuovo punto
            file << "<line x1=\"" << static_cast<int>(x) << "\" y1=\"" << static_cast<int>(y)<< "\" x2=\"" << static_cast<int>(newX) << "\" y2=\"" << static_cast<int>(newY) << "\" stroke=\"black\" stroke-width=\"0.8\"/>" << std::endl;

            // Aggiorna la posizione corrente
            x = newX;
            y = newY;
        }
        else if (c == '+') {
            // Ruota in senso orario di un angolo specifico (ad esempio, 90 gradi)
            angle += 60;
        }
        else if (c == '-') {
            // Ruota in senso antiorario di un angolo specifico (ad esempio, 90 gradi)
            angle -= 60;
        }
    }

    file << "</svg>" << std::endl;
    file.close();

    std::cout << "Immagine generata con successo: " << filename << std::endl;
}

int main() {

    std::string result = "";

    std::ifstream file("../Results/Sierpinski Arrowhead.txt");
    if (file.is_open()) { // Verifica se il file è stato aperto correttamente
        std::getline(file, result); // Leggi la prima riga del file

        std::cout << "Stringa letta con successo" << std::endl;

        file.close(); // Chiudi il file dopo averlo letto
    } else {
        std::cout << "Impossibile aprire il file." << std::endl;
    }

    std::string filename = "lsystem.svg";
    generateImageFromLSystem(result, filename);

    return 0;
}
