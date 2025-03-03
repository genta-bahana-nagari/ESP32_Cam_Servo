# ESP32_Cam_Servo

## Overview
ESP32_Cam_Servo is a project that integrates an ESP32-CAM module with a servo motor to enable remote-controlled movement. This project is ideal for applications such as home surveillance, object tracking, and automation.

## Features
- Live video streaming using ESP32-CAM
- Servo motor control via web interface
- Wi-Fi connectivity for remote access
- Low-cost and efficient implementation

## Hardware Requirements
- ESP32-CAM module
- SG90 or MG995 servo motor
- External 5V power supply (for servo stability)
- Jumper wires
- Micro USB to serial adapter for flashing firmware

## Software Requirements
- Arduino IDE (or PlatformIO)
- ESP32 board package installed in Arduino IDE
- Required libraries:
  - `ESPAsyncWebServer`
  - `AsyncTCP`
  - `WiFi.h`
  - `ESP32Servo.h`

## Wiring Diagram
| ESP32-CAM | Servo Motor |
|-----------|------------|
| 5V        | VCC        |
| GND       | GND        |
| GPIO13    | Signal     |

> Note: Ensure the servo is powered by an external 5V source to prevent ESP32-CAM from resetting.

## Installation & Usage
1. Clone this repository:
   ```sh
   git clone https://github.com/yourusername/ESP32_Cam_Servo.git
   ```
2. Open the project in Arduino IDE.
3. Configure your Wi-Fi credentials in the `config.h` file:
   ```cpp
   #define WIFI_SSID "your-ssid"
   #define WIFI_PASSWORD "your-password"
   ```
4. Compile and upload the code to the ESP32-CAM.
5. Open the serial monitor to find the assigned IP address.
6. Access the web interface via your browser: `http://<ESP32-IP>`.
7. Use the interface to control the servo motor.

## Future Enhancements
- Add object tracking using OpenCV
- Implement face recognition
- Improve web interface with interactive controls

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- ESP32-CAM community for valuable resources
- Developers of `ESPAsyncWebServer` and `ESP32Servo` libraries

---
Feel free to contribute by submitting pull requests or reporting issues!

