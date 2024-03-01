#include <avr/interrupt.h> // Menggunakan library AVR untuk mengatur interrupt

const int LED_COUNT = 8; // Jumlah LED
const int LED_PINS[LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7}; // Array pin LED

volatile bool flipFlop = false; // Variabel volatile untuk mengontrol perubahan LED
volatile bool   = false; // Flag untuk menandakan interrupt

void setup() {
  // Set pin LED sebagai output
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  // Setup Timer 1 untuk interrupt pada interval 100ms
  cli(); // Matikan interrupt secara global
  TCCR1A = 0; // Set seluruh register TCCR1A menjadi 0
  TCCR1B = 0; // Sama untuk TCCR1B
  TCNT1 = 0;  // Inisialisasi nilai counter menjadi 0
  OCR1A = 31249; // Set nilai register pembanding untuk 100ms
  TCCR1B |= (1 << WGM12); // Aktifkan mode CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set bit CS12 dan CS10 untuk prescaler 1024
  TIMSK1 |= (1 << OCIE1A); // Aktifkan interrupt pembanding timer
  sei(); // Aktifkan interrupt secara global
  
  // Setup Timer 2 untuk interrupt setiap 1 detik
  cli(); // Matikan interrupt secara global
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 15624; // Set nilai register pembanding untuk 1 detik (prescaler 1024)
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Set bit CS22, CS21, dan CS20 untuk prescaler 1024
  TIMSK2 |= (1 << OCIE2A); // Aktifkan interrupt pembanding timer
  sei(); // Aktifkan interrupt secara global
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  // Ubah status LED
  if (flipFlop) {
    for (int i = 0; i < LED_COUNT; i += 2) {
      digitalWrite(LED_PINS[i], HIGH); // Nyalakan LED dengan indeks genap
      digitalWrite(LED_PINS[i + 1], LOW); // Matikan LED dengan indeks ganjil
    }
  } else {
    for (int i = 0; i < LED_COUNT; i += 2) {
      digitalWrite(LED_PINS[i], LOW); // Matikan LED dengan indeks genap
      digitalWrite(LED_PINS[i + 1], HIGH); // Nyalakan LED dengan indeks ganjil
    }
  }
  flipFlop = !flipFlop; // Toggle flipFlop untuk mengubah keadaan LED
}

ISR(TIMER2_COMPA_vect) {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], HIGH); // Nyalakan semua LED
  }
}
