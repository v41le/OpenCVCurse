#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////// License Plate Detector //////////////////////

void main() {

    // Declara una matriz para almacenar la imagen.
    Mat img;

    // Crea una instancia de VideoCapture para capturar video desde la cámara (ID 0).
    VideoCapture cap(0);

    // Carga el clasificador en cascada entrenado para detectar placas de matrícula.
    CascadeClassifier plateCascade;
    plateCascade.load("carpetafotos/haarcascade_russian_plate_number.xml");

    // Verifica si el clasificador en cascada se ha cargado correctamente.
    if (plateCascade.empty()) {
        cout << "XML file not loaded" << endl;
    }

    // Declara un vector para almacenar las regiones detectadas de las placas.
    vector<Rect> plates;

    // Inicia un ciclo infinito para capturar y procesar video continuamente.
    while (true) {
        // Lee un cuadro de video de la cámara y lo almacena en 'img'.
        cap.read(img);

        // Detecta las placas de matrícula en la imagen utilizando el clasificador en cascada.
        // Los resultados se almacenan en el vector 'plates'.
        plateCascade.detectMultiScale(img, plates, 1.1, 10);

        // Itera sobre las regiones detectadas de las placas.
        for (int i = 0; i < plates.size(); i++) {
            // Extrae la región de la imagen original que contiene la placa.
            Mat imgCrop = img(plates[i]);

            // Guarda la imagen recortada de la placa en una ubicación específica.
            imwrite("carpetafotos/Plates/" + to_string(i) + ".png", imgCrop);

            // Dibuja un rectángulo alrededor de la placa en la imagen original.
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
        }

        // Muestra la imagen original con las placas detectadas y los rectángulos dibujados.
        imshow("Image", img);

        // Espera a que el usuario presione una tecla durante 1 milisegundo.
        waitKey(1);
    }
}

