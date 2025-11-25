# 🥊 Detector de Fuerza de Golpe con Guante de Boxeo 🎯

Este proyecto utiliza **OpenCV con C++** para detectar un guante de boxeo por color en tiempo real y simular una **máquina de boxeo casera** que calcula la fuerza del golpe.

## 🛠 Características
- 🔴 **Detección de guantes en tiempo real** mediante la webcam.
- ⚡ **Cálculo de fuerza** basado en el tiempo de contacto con la zona objetivo.
- ⏳ **Cuenta regresiva de 5 segundos** que se activa con la tecla **`g`**.
- 🎭 **Alternar vista de máscara** (HSV) con la tecla **`m`**.
- ❌ **Salir del programa** con **ESC**.

## 🎨 Detección de Color (HSV)
El color del guante se detecta mediante filtrado en el espacio **HSV**.

🎀 **Color predeterminado:** rosa  
Para modificar el color del guante cambia estos valores:

```cpp
Scalar lower_pink(140, 50, 100);
Scalar upper_pink(170, 255, 255);
```

##✅ Requisitos
OpenCV instalado (opencv2 u opencv4).

C++11 o superior.

Webcam.

##🚀 Cómo Ejecutar
Compilar
bash
Copiar código
g++ -std=c++11 -o boxing boxing.cpp $(pkg-config --cflags --libs opencv4)
Ejecutar
bash
Copiar código
./boxing
