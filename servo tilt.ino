#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "GENTA";
const char* password = "HURUFCILIK";

// Buat objek untuk kedua servo
Servo servoHorizontal;
Servo servoVertical;

// Inisialisasi pin servo
const int servoPin1 = D5; // Pin untuk servo horizontal
const int servoPin2 = D6; // Pin untuk servo vertikal

// Inisialisasi server pada port 80
ESP8266WebServer server(80);

void handleRoot() {
  // HTML untuk antarmuka web kontrol servo
  String html = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP8266 Servo Control</title>
  </head>
  <body>
    <h2>Servo Control</h2>
    <label for="horizontal">Horizontal (0-360):</label>
    <input type="range" id="horizontal" name="horizontal" min="0" max="360" oninput="updateServo(this.value, 'horizontal')">
    <p>Value: <span id="hValue">90</span></p>
    
    <label for="vertical">Vertical (0-360):</label>
    <input type="range" id="vertical" name="vertical" min="0" max="360" oninput="updateServo(this.value, 'vertical')">
    <p>Value: <span id="vValue">90</span></p>

    <script>
      function updateServo(value, axis) {
        var xhttp = new XMLHttpRequest();
        if(axis === 'horizontal') {
          document.getElementById("hValue").innerHTML = value;
        } else {
          document.getElementById("vValue").innerHTML = value;
        }
        xhttp.open("GET", "/setServo?axis=" + axis + "&value=" + value, true);
        xhttp.send();
      }
    </script>
  </body>
  </html>)rawliteral";

  // Mengirim halaman HTML ke browser
  server.send(200, "text/html", html);
}

void handleSetServo() {
  // Mendapatkan parameter dari request URL
  String axis = server.arg("axis");
  int value = server.arg("value").toInt();

  // Mengatur posisi servo sesuai dengan parameter 'axis'
  if (axis == "horizontal") {
    servoHorizontal.write(value);  // Atur servo horizontal
    Serial.print("Horizontal Servo set to: ");  // Cetak nilai servo horizontal
    Serial.println(value);
  } else if (axis == "vertical") {
    servoVertical.write(value);    // Atur servo vertikal
    Serial.print("Vertical Servo set to: ");  // Cetak nilai servo vertikal
    Serial.println(value);
  }

  // Mengirimkan respon 'OK'
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  
  // Sambungkan ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Ketika terhubung ke WiFi, tampilkan alamat IP
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Menampilkan IP Address ke Serial Monitor

  // Attach servo ke pin masing-masing
  servoHorizontal.attach(servoPin1);
  servoVertical.attach(servoPin2);

  // Atur URL root untuk menampilkan halaman web
  server.on("/", handleRoot);

  // Atur URL untuk mengubah posisi servo
  server.on("/setServo", handleSetServo);

  // Mulai server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Menangani permintaan dari client
  server.handleClient();
}
