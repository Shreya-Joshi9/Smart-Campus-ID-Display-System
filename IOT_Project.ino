#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

SoftwareSerial scannerSerial(10, 11);  // Define RX and TX pins for the scanner
Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define SSD1306 0x3C

void setup() {
  Serial.begin(115200);
  scannerSerial.begin(9600);
  display.begin(SSD1306, 0x3C, 4, 5);

  pinMode(13, OUTPUT);  // Buzzer pin
  digitalWrite(13, LOW);

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  String myString;
  String scannedCode = scannerRead();
  if (myString.length() == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Scanned ID: ");
    display.println(scannedCode);

    

    String userInfo = fetchUserInfo(scannedCode);
    display.setCursor(0, 20);
    display.print("Information: ");
    display.println(userInfo);

    display.display();
    beep();  // Activate the buzzer
    delay(5000);  // Display information for 5 seconds
    display.clearDisplay();
    digitalWrite(13, LOW);  // Turn off the buzzer
  }
}

String myString;
String scannerRead() {
  String result = "";
  while (scannerSerial.available()) {
    char c = scannerSerial.read();
    if (c != '\n' && c != '\r') {
      result += c;
    } else if (myString.length() == 0) {
      return result;
    }
  }
  return "";
}

String fetchUserInfo(String id) {
  // Replace these sample IDs and information with your actual data
  if (id == "2JR22CS414") {
    return "SHREYA S. JOSHI";
  } else if (id == "2JR22CS405") {
    return "MEGHA S. POOJARI,";
  } else {
    return "User not found";
  }
}

void beep() {
  digitalWrite(13, HIGH);  // Turn on the buzzer
  delay(100);
  digitalWrite(13, LOW);  // Turn off the buzzer
}