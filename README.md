# 🌡️ IMPLEMENTASI SENSOR LM35 & 4N35
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

### 🔧 Komponen yang Digunakan
- Arduino Uno
- Sensor Suhu LM35
- LCD I2C
- Push button
- Buzzer
- LED
- Optocoupler 4N35

## 🎯 Fitur & Mode Operasi

### Mode 1: Perekaman Suhu 📝
```plaintext
[Tekan Tombol #1]
```
- Menangkap data suhu dari sensor LM35
- Menampilkan hasil pembacaan di layar LCD
- Mengirim data ke serial monitor
- Menyimpan data di EEPROM

### Mode 2: Pemutaran Data 📊
```plaintext
[Tekan Tombol #2]
```
- Mengambil rekaman suhu yang tersimpan
- Menampilkan data historis di LCD
- Mengeluarkan data lengkap melalui serial monitor

### Mode 3: Reset Memori 🗑️
```plaintext
[Tekan Tombol #3]
```
- Menghapus semua data tersimpan dari EEPROM
- Bunyi buzzer sebagai konfirmasi
- Siap untuk perekaman baru

### Mode 4: Efek LED 💡
```plaintext
[Tekan Tombol #4]
```
- Efek LED fading dinamis
- Pola cahaya kustom
- Animasi indikator visual

### Mode 5: Reset Siklus 🔄
```plaintext
[Tekan Tombol #5]
```
- Kembali ke Mode 1
- Siap untuk sesi perekaman suhu baru

## 📊 Konfigurasi Pin

| Komponen  | Nomor Pin |
|-----------|-----------|
| LM35      | A0        |
| LCD (RS)  | 12        |
| LCD (EN)  | 11        |
| Tombol    | 2         |
| Buzzer    | 8         |
| LED       | 9         |
| 4N35      | 7         |

## 🔍 Cara Kerja
1. **Kasus 1:** 
   - Tekan tombol pertama kali untuk merekam data suhu
   - Data ditampilkan di LCD dan serial monitor
   
2. **Kasus 2:**
   - Tekan tombol kedua kali untuk melihat hasil rekaman
   - Ditampilkan di serial monitor dan LCD
   
3. **Kasus 3:**
   - Tekan tombol ketiga kali untuk menghapus rekaman
   - Buzzer akan berbunyi setelah penghapusan selesai
   
4. **Kasus 4:**
   - Tekan tombol keempat kali untuk efek LED
   - LED akan menampilkan efek fading dan berkedip
   
5. **Kasus 5:**
   - Tekan tombol kelima kali untuk kembali ke kasus 1
   - Sistem siap memulai siklus baru
