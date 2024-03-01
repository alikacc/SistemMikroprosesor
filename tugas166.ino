#include <TimerOne.h>

// Mendefinisikan nomor pin untuk segmen-segmen dan digit-digit
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DIGIT1 9
#define DIGIT2 10
#define DIGIT3 11

// Deklarasi variabel integer volatile untuk penghitungan
volatile int count = 0;

// Menentukan pola untuk setiap segmen pada tiap digit
const byte digitPatterns[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}  // 9
};

void setup() {
  // Mengatur mode pin untuk segmen-segmen dan digit-digit
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(DIGIT3, OUTPUT);
  
  // Menonaktifkan interupsi selama pengaturan
  noInterrupts();
  // Menginisialisasi Timer1 untuk menginterupsi setiap satu detik
  Timer1.initialize(1000000);
  // Menempelkan penangan interupsi
  Timer1.attachInterrupt(hitung);
  // Mengaktifkan interupsi setelah pengaturan
  interrupts();
}

void loop() {
  // Membaca nilai count
  int value = count;
  // Menampilkan setiap digit pada pin digit yang sesuai
  displayDigit(value / 100, DIGIT1);
  displayDigit((value / 10) % 10, DIGIT2);
  displayDigit(value % 10, DIGIT3);
}

void displayDigit(int digit, int digitPin) {
  // Mematikan semua pin digit terlebih dahulu
  digitalWrite(DIGIT1, LOW);
  digitalWrite(DIGIT2, LOW);
  digitalWrite(DIGIT3, LOW);
  
  // Mendapatkan pola untuk digit saat ini
  byte *pattern = digitPatterns[digit];
  // Iterasi melalui segmen-segmen dan menetapkan pin yang sesuai
  for (int i = A; i <= G; i++) {
    digitalWrite(i, pattern[i - A] ? HIGH : LOW);
  }
  
  // Menyalakan pin digit yang dipilih
  digitalWrite(digitPin, HIGH);
}

void hitung() {
  // Menambahkan nilai count setiap satu detik
  count++;
  // Mengatur ulang count menjadi 0 setelah mencapai 1000
  if (count == 1000) {
    count = 0;
  }
}
