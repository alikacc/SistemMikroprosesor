#include <avr/interrupt.h> // Library untuk menggunakan fitur interrupt pada mikrokontroler AVR

volatile boolean flipFlop = false; // Variabel yang dapat berubah nilainya secara tiba-tiba, akan digunakan dalam fungsi interrupt

void setup() { // Fungsi untuk melakukan konfigurasi awal saat mikrokontroler dihidupkan
  setupInterrupt(); // Memanggil fungsi untuk melakukan konfigurasi fitur interrupt
  for (int i = 0; i < 8; i++) { // Melakukan pengulangan untuk mengatur mode pin
    pinMode(i, OUTPUT); // Mengatur pin-pin sebagai output
  }
}

void setupInterrupt(void) { // Fungsi untuk mengatur fitur interrupt
  noInterrupts(); // Menonaktifkan interrupt sementara
  TCCR1A = 0; // Mengatur mode operasi timer
  TCCR1B = 0; // Mengatur prescaler timer
  TCNT1 = 3036; // Mengatur nilai awal timer
  TCCR1B |= (1 << CS12); // Mengatur prescaler untuk timer
  TIMSK1 |= (1 << TOIE1); // Mengaktifkan interrupt overflow pada timer
  interrupts(); // Mengaktifkan kembali interrupt
}

ISR(TIMER1_OVF_vect) { // Fungsi yang akan dieksekusi ketika interrupt terjadi
  TCNT1 = 3036; // Mengatur kembali nilai awal timer
  flipFlop = !flipFlop; // Mengubah nilai variabel flipFlop secara bergantian antara true dan false
}

void loop() { // Fungsi utama yang akan dieksekusi secara berulang
  for (int i = 0; i < 4; i++) { // Melakukan pengulangan untuk mengatur output pada pin
    digitalWrite(i, flipFlop ? LOW : HIGH); // Mengatur output pada pin ke-i sesuai dengan nilai flipFlop
    digitalWrite(i + 4, flipFlop ? HIGH : LOW); // Mengatur output pada pin ke-(i+4) sesuai dengan nilai flipFlop
  }
}
