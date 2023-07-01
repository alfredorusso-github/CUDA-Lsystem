#include <opencv2/opencv.hpp>
#include <math.h>
#include <string>
#include <fstream>
#include <limits>

int main() {
    
    int width = 800;
    int height = 600;

    cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    int x_min = std::numeric_limits<int>::infinity();  // Inizializza i valori minimi con infinito
    int y_min = std::numeric_limits<int>::infinity();
    int x_max = -std::numeric_limits<int>::infinity();  // Inizializza i valori massimi con -infinito
    int y_max = -std::numeric_limits<int>::infinity();

    int lineLength = 20;
    int angle = 0;
    int turn_angle = 60;
    cv::Point start(200, 100);

    std::string result = "";

    std::ifstream file("Results/Sierpinski Arrowhead.txt");
    if (file.is_open()) { // Verifica se il file è stato aperto correttamente
        std::getline(file, result); // Leggi la prima riga del file

        std::cout << "Stringa letta con successo" << std::endl;

        file.close(); // Chiudi il file dopo averlo letto
    } else {
        std::cout << "Impossibile aprire il file." << std::endl;
    }

    cv::Point currentPosition(start);
    int current_angle = angle;

    for(char c: result)
    {
        if(c == 'A' || c == 'B')
        {
            // Draw line
            cv::Point end(
                currentPosition.x + static_cast<int>(lineLength * cos( current_angle * CV_PI / 180.0 )), 
                currentPosition.y - static_cast<int>(lineLength * sin( current_angle * CV_PI / 180.0 ))
            );
            cv::line(image, currentPosition, end, cv::Scalar(0, 0, 0), 1);

            x_min = std::min(x_min, end.x);
            x_max = std::max(x_max, end.x);
            y_min = std::min(y_min, end.y);
            y_max = std::max(y_max, end.y);

            if(end.x > width || end.y > height)
            {
                std::cout << "end.x: " << end.x << "  end.y: " << end.y << std::endl;
            }
            else if(currentPosition.x > width || currentPosition.y > height)
            {
                std::cout << "currentPosition.x: " << currentPosition.x << "  currentPosition.y: " << currentPosition.y << std::endl;
            }
            
            currentPosition = end;
        }
        else if(c == '+')
        {
            // Rotate right
            current_angle += turn_angle; 
        }
        else if(c == '-')
        {
            // Rotate left
            current_angle -= turn_angle; 
        }
    }

    int padding = 100; // Padding aggiuntivo per allargare leggermente l'immagine

    int newWidth = x_max - x_min + 2 * padding; // Calcolo della nuova larghezza
    int newHeight = y_max - y_min + 2 * padding; // Calcolo della nuova altezza

    std::cout << "x_max: " << x_max << "  x_min: " << x_min << std::endl;
    std::cout << "y_max: " << y_max << "  y_min: " << y_min << std::endl;
    std::cout << "width: " << newWidth << "  height: " << newHeight << std::endl;

    cv::Mat newCanvas(newHeight, newWidth, image.type());
    
    double scaleX = static_cast<double>(newWidth) / image.cols;
    double scaleY = static_cast<double>(newHeight) / image.rows;
    double scale = std::min(scaleX, scaleY);

    cv::Mat resizedCanvas;
    cv::resize(image, resizedCanvas, cv::Size(), scale, scale);

    int offsetX = (newWidth - resizedCanvas.cols) / 2;
    int offsetY = (newHeight - resizedCanvas.rows) / 2;

    resizedCanvas.copyTo(newCanvas(cv::Rect(offsetX, offsetY, resizedCanvas.cols, resizedCanvas.rows)));

    cv::imshow("Linee", resizedCanvas);
    cv::waitKey(0);
    
    return 0;
}
