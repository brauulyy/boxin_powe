#include <opencv2/opencv.hpp>  
#include <iostream>            
#include <chrono>              

using namespace cv;
using namespace std;
using namespace std::chrono;

int main() {
    VideoCapture cam(0);  
    if (!cam.isOpened()) {
        cout << "Error al abrir la cámara." << endl;
        return -1;
    }

    Scalar lower_pink(140, 50, 100);
    Scalar upper_pink(170, 255, 255);

    Rect blancoArea(250, 150, 120, 120);

    bool midiendo = false;
    bool golpeContado = false;
    steady_clock::time_point tiempoInicio, tiempoFin;

    Mat frame, hsv, mascara;

    bool cuentaActiva = false;
    steady_clock::time_point cuentaInicio;

    bool mostrarMascara = false;

    // ================================
    // IMPLEMENTACION FISICA 2
    // Parámetros del circuito
    double Vin = 5.0;          // Voltaje de entrada (simulado)
    double R1 = 1000.0;        // Resistencia fija 1k ohm
    // ================================

    while (true) {
        cam >> frame;
        if (frame.empty()) break;

        flip(frame, frame, 1);

        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, lower_pink, upper_pink, mascara);

        vector<vector<Point>> contornos;
        findContours(mascara, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        rectangle(frame, blancoArea, Scalar(0, 0, 255), 2);

        if (cuentaActiva) {
            int segundosTranscurridos = duration_cast<seconds>(steady_clock::now() - cuentaInicio).count();
            int restante = 5 - segundosTranscurridos;

            if (restante > 0) {
                putText(frame, "Golpea en: " + to_string(restante), Point(200, 100),
                    FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 2);
            }
            else if (!midiendo) {
                midiendo = true;
                golpeContado = false;
            }
        }

        if (midiendo && !golpeContado) {
            for (auto& contorno : contornos) {
                double area = contourArea(contorno);
                if (area > 1000 && area < 20000) {

                    Rect bbox = boundingRect(contorno);
                    rectangle(frame, bbox, Scalar(255, 0, 255), 2);

                    if ((bbox & blancoArea).area() > 0) {
                        tiempoInicio = steady_clock::now();
                    }
                    else {
                        if (tiempoInicio.time_since_epoch().count() > 0) {

                            tiempoFin = steady_clock::now();
                            auto duracion = duration_cast<milliseconds>(tiempoFin - tiempoInicio).count();

                            int fuerza = max(0, 999 - static_cast<int>(duracion * 10));

                            putText(frame, "Fuerza: " + to_string(fuerza),
                                Point(180, 450), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

                            cout << "¡Golpe detectado! Fuerza: " << fuerza << endl;

                            // ============================================
                            //  SENSOR RESISTIVO
                            // Simulación de resistencia del sensor
                            double R_sensor = 200.0 + (duracion * 0.5);  // Resistencia cambia con tiempo

                            // Divisor de voltaje
                            double Vout = Vin * (R_sensor / (R1 + R_sensor));

                            // Corriente total
                            double I = Vin / (R1 + R_sensor);

                            // Potencia
                            double P = Vout * I;

                            cout << "---- Datos Electricos (Fisica II) ----" << endl;
                            cout << "R_sensor: " << R_sensor << " ohms" << endl;
                            cout << "Vout: " << Vout << " V" << endl;
                            cout << "Corriente: " << I << " A" << endl;
                            cout << "Potencia: " << P << " W" << endl;

                            // Mostrar en pantalla
                            putText(frame, "Vout: " + to_string(Vout).substr(0,4) + "V",
                                Point(180, 480), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255,255,0), 2);

                            putText(frame, "R: " + to_string((int)R_sensor) + " ohm",
                                Point(180, 510), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255,255,0), 2);

                            // ============================================

                            golpeContado = true;
                            midiendo = false;
                            cuentaActiva = false;
                        }
                    }
                }
            }
        }

        imshow("Boxeo - Guante Rosa", frame);

        if (mostrarMascara) imshow("Mascara Guante", mascara);
        else destroyWindow("Mascara Guante");

        int key = waitKey(10);
        if (key == 'g') {
            cout << "¡Cuenta regresiva activada!" << endl;
            cuentaInicio = steady_clock::now();
            cuentaActiva = true;
            tiempoInicio = steady_clock::time_point();
        }
        if (key == 'm') mostrarMascara = !mostrarMascara;
        if (key == 27) break;
    }

    cam.release();
    destroyAllWindows();
    return 0;
}
