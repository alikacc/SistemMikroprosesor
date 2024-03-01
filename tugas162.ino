// Mendefinisikan pin input dan jumlah pin output
const int inputPin = 9;
const int numOutputPins = 4;

// Array untuk menyimpan nomor pin output
const int outputPins[numOutputPins] = {2, 3, 4, 5};

// Variabel untuk menunjukkan tombol ditekan dan arah gerakan yang dibalikkan
int buttonClicked = 0;
bool reverseDirection = false;

void setup() {
  // Mengatur mode pin output dan mematikannya
  for (int i = 0; i < numOutputPins; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }
  
  // Mengatur mode pin input
  pinMode(inputPin, INPUT);
  
  // Memulai komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
}

void loop() {
  // Membaca status input pin
  int inputState = digitalRead(inputPin);
  
  // Jika tombol ditekan
  if (inputState == HIGH) {
    // Jika arah gerakan tidak dibalikkan dan tombol belum mencapai pin output terakhir
    if (!reverseDirection && buttonClicked < numOutputPins) {
      // Nyalakan LED pada pin output yang sesuai dan tambahkan tombol yang ditekan
      digitalWrite(outputPins[buttonClicked++], HIGH);
    } 
    // Jika arah gerakan dibalikkan dan tombol belum mencapai pin output pertama
    else if (reverseDirection && buttonClicked > 0) {
      // Nyalakan LED pada pin output yang sesuai dan kurangi tombol yang ditekan
      digitalWrite(outputPins[--buttonClicked], HIGH);
    } 
    // Jika sudah mencapai batas akhir
    else {
      // Matikan semua LED dan balikkan arah gerakan
      for (int i = 0; i < numOutputPins; i++)
        digitalWrite(outputPins[i], LOW);
      
      reverseDirection = !reverseDirection;
      
      // Sesuaikan inisialisasi untuk tombol yang ditekan berdasarkan arah gerakan
      buttonClicked = reverseDirection ? numOutputPins - 1 : 0;
      
      // Nyalakan LED pada pin output yang sesuai
      digitalWrite(outputPins[buttonClicked], HIGH);
    }
    
    // Tunda selama 250 ms
    delay(250);
  }
}
