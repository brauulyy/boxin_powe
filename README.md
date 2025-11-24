Detector de Fuerza de Golpe con Guante de Boxeo 🎯🥊
Este proyecto utiliza OpenCV con C++ para detectar un guante de boxeo de color en tiempo real y simular una máquina de boxeo casera que calcula la fuerza del golpe.

🛠 Características
Detección de guantes en tiempo real a través de la webcam.

La fuerza del golpe se calcula en función del tiempo de contacto con una zona objetivo.

Cuenta regresiva de 5 segundos que se activa con la tecla 'g'.

Alterna la vista previa de la máscara del guante con la tecla 'm'.

Cierra el programa con ESC.

🎨 Detección de Color
El color del guante se detecta mediante filtrado HSV.

Color predeterminado: rosa.

Para cambiar el color del guante, modifica estas líneas en el código:

C++

Scalar lower_pink(140, 50, 100);
Scalar upper_pink(170, 255, 255);
✅ Requisitos
OpenCV instalado (opencv2 o opencv4 según tu configuración).

C++11 o superior.

Webcam.

🚀 Cómo Ejecutar
Compila el código usando g++ o tu compilador preferido:

Bash

g++ -std=c++11 -o boxing boxing.cpp $(pkg-config --cflags --libs opencv4)
Ejecuta el programa:

Bash

./boxing
📸 Controles
g — Iniciar cuenta regresiva

m — Mostrar/ocultar máscara HSV

ESC — Salir del programa
