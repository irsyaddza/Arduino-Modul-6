#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const int buttonPin = 7;         // Pin push button
const int lm35Pin = A0;          // Pin sensor suhu LM35
const int optoPin = 8;           // Pin untuk kontrol 4N35
const int buzzerPin = 11;         // Pin buzzer
const int ledPin = 10;           // Pin LED

int buttonState = 0;             // Status tombol
int lastButtonState = 0;         // Status tombol sebelumnya
int mode = 0;                    // 0 = Off, 1 = Monitoring, 2 = Rekaman, 3 = Clear EEPROM, 4 = LED Fading
float suhuBatas = 30.0;          // Batas suhu untuk alarm
int index = 0;                   // Indeks untuk data di EEPROM

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD I2C

void setup() {
  Serial.begin(9600);              // Memulai komunikasi serial
  pinMode(buttonPin, INPUT);       // Set pin tombol sebagai input
  pinMode(optoPin, OUTPUT);        // Set pin optocoupler sebagai output
  pinMode(buzzerPin, OUTPUT);      // Set pin buzzer sebagai output
  pinMode(ledPin, OUTPUT);         // Set pin LED sebagai output

  lcd.init();
  lcd.backlight();
  lcd.print("Monitoring Off");
}

// Fungsi untuk membaca suhu dari sensor LM35
float bacaSuhu() {
  int analogValue = analogRead(lm35Pin);       // Membaca nilai analog
  float voltage = analogValue * (5.0 / 1023.0); // Konversi ke tegangan
  return voltage * 100;                        // LM35 mengeluarkan 10mV per derajat Celsius
}

// Fungsi untuk menyimpan suhu ke EEPROM
void simpanSuhuKeEEPROM(float suhu) {
  if (index < EEPROM.length() / sizeof(float)) {
    EEPROM.put(index * sizeof(float), suhu);
    index++;
  }
}

// Fungsi untuk membaca suhu dari EEPROM
void tampilkanRekamanSuhu() {
  Serial.println("Rekaman Suhu:");
  lcd.clear();
  lcd.print("Rekaman Suhu:");
  delay(500);

  for (int i = 0; i < index; i++) {
    float suhu;
    EEPROM.get(i * sizeof(float), suhu);
    Serial.print("Suhu ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(suhu);
    Serial.println(" C");

    lcd.setCursor(0, 1);
    lcd.print(suhu);
    lcd.print(" C   ");
    delay(1000);
  }
}

// Fungsi untuk menghapus semua rekaman di EEPROM
void hapusEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  index = 0; // Reset indeks ke 0
  lcd.clear();
  lcd.print("EEPROM Cleared");
  Serial.println("EEPROM Cleared");
  // Bunyi buzzer sebagai tanda selesai
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

// Fungsi untuk menjalankan efek LED Fading
void ledFadingEffect() {
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(ledPin, brightness);
    delay(30);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(ledPin, brightness);
    delay(30);
  }
}

// Fungsi untuk menjalankan efek LED Kelap-Kelip
void ledBlinkEffect() {
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
}

void loop() {
  // Membaca status tombol
  buttonState = digitalRead(buttonPin);

  // Cek perubahan status tombol untuk toggle mode
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      mode = (mode + 1) % 5; // Berpindah mode: 0 -> 1 -> 2 -> 3 -> 4 -> 1 (Kembali ke Monitoring)
      lcd.clear();

      // Mode Off
      if (mode == 0) {
        lcd.print("Monitoring Off");
        Serial.println("Not Connected");
        digitalWrite(buzzerPin, LOW); // Matikan buzzer
        digitalWrite(ledPin, LOW);    // Matikan LED
        digitalWrite(optoPin, LOW);   // Matikan optocoupler
      }
      // Mode Monitoring
      else if (mode == 1) {
        lcd.print("Monitoring On");
        Serial.println("Connected");
        index = 0; // Reset indeks untuk rekaman suhu baru
      }
      // Mode Rekaman
      else if (mode == 2) {
        tampilkanRekamanSuhu(); // Tampilkan semua rekaman dari EEPROM
      }
      // Mode Clear EEPROM
      else if (mode == 3) {
        hapusEEPROM(); // Hapus semua rekaman di EEPROM
      }
      // Mode LED Fading
      else if (mode == 4) {
        lcd.print("LED Fading Mode");
        Serial.println("LED Fading Mode");
      }
    }
    delay(200); // Debounce tombol
  }
  lastButtonState = buttonState;

  // Jika mode Monitoring aktif, baca suhu dan tampilkan di LCD
  if (mode == 1) {
    float suhu = bacaSuhu();
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(suhu);
    lcd.print(" C  ");

    // Simpan suhu di EEPROM jika masih ada ruang
    simpanSuhuKeEEPROM(suhu);

    // Jika suhu di atas batas, aktifkan buzzer dan LED
    if (suhu > suhuBatas) {
      digitalWrite(buzzerPin, HIGH);  // Nyalakan buzzer
      digitalWrite(ledPin, HIGH);     // Nyalakan LED
      digitalWrite(optoPin, HIGH);    // Aktifkan optocoupler
    } else {
      digitalWrite(buzzerPin, LOW);   // Matikan buzzer
      digitalWrite(ledPin, LOW);      // Matikan LED
      digitalWrite(optoPin, LOW);     // Matikan optocoupler
    }

    delay(1000); // Pembaruan suhu setiap 1 detik
  }

  // Jika mode LED Fading aktif, jalankan efek fading dan kelap-kelip LED
  if (mode == 4) {
    ledFadingEffect(); // Jalankan efek fading
    ledBlinkEffect();  // Jalankan efek kelap-kelip setelah fading
  }
}