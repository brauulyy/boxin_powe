#include <opencv2/opencv.hpp>  // Librería principal de OpenCV
#include <iostream>            // Para imprimir en consola
#include <chrono>              // Para medir tiempo

using namespace cv;
using namespace std;
using namespace std::chrono;

int main() {
    VideoCapture cam(0);  // Abre la cámara por defecto (índice 0)
    if (!cam.isOpened()) {
        cout << "Error al abrir la cámara." << endl;
        return -1;
    }

    // Definir el rango de color en HSV para detectar el guante rosa
    Scalar lower_pink(140, 50, 100);
    Scalar upper_pink(170, 255, 255);

    // Área del objetivo (el "blanco" donde se debe golpear)
    Rect blancoArea(250, 150, 120, 120);

    // Variables de estado para medir el golpe
    bool midiendo = false;
    bool golpeContado = false;
    steady_clock::time_point tiempoInicio, tiempoFin;

    // Imágenes y máscara
    Mat frame, hsv, mascara;

    // Variables para cuenta regresiva
    bool cuentaActiva = false;
    steady_clock::time_point cuentaInicio;

    // Mostrar o no la máscara (ventana en blanco y negro)
    bool mostrarMascara = false;

    while (true) {
        cam >> frame;  // Captura el frame
        if (frame.empty()) break;

        flip(frame, frame, 1);  // Voltea la imagen horizontalmente (efecto espejo)

        cvtColor(frame, hsv, COLOR_BGR2HSV);              // Convierte a HSV
        inRange(hsv, lower_pink, upper_pink, mascara);    // Aplica el filtro por color (crea la máscara)

        // Encuentra contornos del guante en la máscara
        vector<vector<Point>> contornos;
        findContours(mascara, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Dibuja el área del blanco en el frame
        rectangle(frame, blancoArea, Scalar(0, 0, 255), 2);

        // Si la cuenta regresiva está activa
        if (cuentaActiva) {
            int segundosTranscurridos = duration_cast<seconds>(steady_clock::now() - cuentaInicio).count();
            int restante = 5 - segundosTranscurridos;

            if (restante > 0) {
                // Muestra cuántos segundos faltan para golpear
                putText(frame, "Golpea en: " + to_string(restante), Point(200, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 2);
            }
            else if (!midiendo) {
                // Comienza a medir después de la cuenta regresiva
                midiendo = true;
                golpeContado = false;
            }
        }

        // Si está midiendo y aún no ha contado el golpe
        if (midiendo && !golpeContado) {
            for (auto& contorno : contornos) {
                double area = contourArea(contorno);
                if (area > 1000 && area < 20000) {  // Filtra objetos muy pequeños o grandes
                    Rect bbox = boundingRect(contorno);  // Encuentra la caja del contorno
                    rectangle(frame, bbox, Scalar(255, 0, 255), 2);  // Dibuja caja rosa sobre el guante

                    // Si el guante toca el área objetivo
                    if ((bbox & blancoArea).area() > 0) {
                        tiempoInicio = steady_clock::now();  // Inicia cronómetro
                    }
                    else {
                        if (tiempoInicio.time_since_epoch().count() > 0) {
                            // Termina la medición
                            tiempoFin = steady_clock::now();
                            auto duracion = duration_cast<milliseconds>(tiempoFin - tiempoInicio).count();
                            int fuerza = max(0, 999 - static_cast<int>(duracion * 10));  // Calcula "fuerza"
                            putText(frame, "Fuerza: " + to_string(fuerza), Point(180, 450), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
                            cout << "¡Golpe detectado! Fuerza: " << fuerza << endl;

                            golpeContado = true;
                            midiendo = false;
                            cuentaActiva = false;
                        }
                    }
                }
            }
        }

        // Muestra la imagen principal con todo dibujado
        imshow("Boxeo - Guante Rosa", frame);

        // Solo muestra la máscara si el modo está activo
        if (mostrarMascara) {
            imshow("Mascara Guante", mascara);
        }
        else {
            destroyWindow("Mascara Guante");
        }

        int key = waitKey(10);
        if (key == 'g') {
            // Activa la cuenta regresiva con tecla 'g'
            cout << "¡Cuenta regresiva activada!" << endl;
            cuentaInicio = steady_clock::now();
            cuentaActiva = true;
            tiempoInicio = steady_clock::time_point();  // Reinicia el tiempo inicial
        }
        if (key == 'm') {
            // Alterna la ventana de la máscara con tecla 'm'
            mostrarMascara = !mostrarMascara;
        }
        if (key == 27) break;  // Tecla ESC para salir
    }

    // Libera la cámara y cierra ventanas
    cam.release();
    destroyAllWindows();
    return 0;
}
