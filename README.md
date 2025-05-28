# Boxing Glove Punch Force Detector 🎯🥊

This project uses **OpenCV** with C++ to detect a colored boxing glove in real-time and simulate a home-made boxing machine that calculates punch force.

## 🛠 Features
- Real-time glove detection via webcam.
- Punch force is calculated based on contact time with a target zone.
- 5-second countdown activated with key `'g'`.
- Toggle the glove mask preview with key `'m'`.
- Exit the program with **ESC**.

## 🎨 Color Detection
- Glove color is detected using HSV filtering.
- Default color: **pink**.
- To change the glove color, modify these lines in the code:
  ```cpp
  Scalar lower_pink(140, 50, 100);
  Scalar upper_pink(170, 255, 255);

✅ Requirements
1.OpenCV installed (opencv2)

2.C++11 or higher

3.Webcam


🚀 How to Run
Compile the code using g++ or your preferred compiler:

Bash:
g++ -std=c++11 -o boxing boxing.cpp `pkg-config --cflags --libs opencv4`

bash:
./boxing


📸 Controls
g — Start countdown

m — Show/hide HSV mask

ESC — Exit the program
