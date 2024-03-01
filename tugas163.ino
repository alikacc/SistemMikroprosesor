#include <avr/interrupt.h>; // Mengimpor pustaka untuk menggunakan fitur interrupt pada mikrokontroler AVR.

volatile boolean flipFlop = false; // Variabel yang akan berganti nilai secara bergantian di dalam interrupt.

void setup() { // Fungsi setup, dijalankan sekali saat mikrokontroler pertama kali dinyalakan.
  setupInterrupt(); // Memanggil fungsi untuk melakukan setup interrupt.
  for (int i = 0; i < 8; i++) { // Melakukan inisialisasi pin-pin sebagai output.
    pinMode(i, OUTPUT);
  }
}

void setupInterrupt(void) { // Fungsi untuk melakukan setup interrupt.
  noInterrupts(); // Menonaktifkan interrupt.
  TCCR1A = 0; // Mengatur mode normal untuk Timer 1.
  TCCR1B = 0; // Reset register kontrol Timer 1.
  TCNT1 = 3036; // Mengatur nilai awal timer.
  TCCR1B |= (1 << CS12); // Mengatur prescaler menjadi 256 untuk Timer 1.
  TIMSK1 |= (1 << TOIE1); // Mengaktifkan interrupt overflow untuk Timer 1.
  interrupts(); // Mengaktifkan kembali interrupt.
}

ISR(TIMER1_OVF_vect) { // Fungsi ISR (Interrupt Service Routine) untuk overflow interrupt dari Timer 1.
  TCNT1 = 3036; // Mengatur ulang nilai timer.
  flipFlop = !flipFlop; // Mengubah nilai variabel flipFlop.
}

void loop() { // Fungsi loop, dijalankan secara berulang setelah fungsi setup selesai.
  for (int i = 0; i < 4; i++) { // Loop untuk mengatur keadaan output pin secara bergantian.
    digitalWrite(i, flipFlop ? LOW : HIGH); // Mengatur keadaan output pin 0-3.
    digitalWrite(i + 4, flipFlop ? HIGH : LOW); // Mengatur keadaan output pin 4-7.
  }
}
