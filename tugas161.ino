const int jumlahOutput = 4; // Deklarasi jumlah output
const int pinOutput[jumlahOutput] = {2, 3, 4, 5}; // Array pin output

void setup() {
  // Konfigurasi pin output
  for (int i = 0; i < jumlahOutput; i++) {
    pinMode(pinOutput[i], OUTPUT);
  }
  Serial.begin(9600); // Inisialisasi komunikasi serial
}

void loop() {
    for(int i=0;i < jumlahOutput;i++){
      digitalWrite(pinOutput[i], HIGH); // Nyalakan LED
      delay(1000); // Delay untuk 1 detik
      digitalWrite(pinOutput[i], LOW); // Matikan LED
  }
}
