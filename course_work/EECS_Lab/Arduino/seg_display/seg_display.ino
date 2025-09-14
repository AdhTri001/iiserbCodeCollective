#define A 3
#define B 2
#define C 6
#define D 8
#define E 7
#define F_SEG 4
#define G 5
// Pins driving common anodes
#define CA1 12
#define CA2 13

// Pins for A B C D E F G, in sequence
const int segs[7] = { A, B, C, D, E, F_SEG, G };
// Segments that make each number
const byte numbers[10] = {
  0b1000000, 0b1111001, 0b0100100, 0b0110000,
  0b0011001, 0b0010010, 0b0000010, 0b1111000,
  0b0000000, 0b0010000 };

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
}

void loop() {
  for (int digit1=0; digit1 < 10; digit1++) {
    for (int digit2=0; digit2 < 10; digit2++) {
      unsigned long startTime = millis();
      for (unsigned long elapsed=0; elapsed < 600;
          elapsed = millis() - startTime) {
        lightDigit2(numbers[digit2]);
        delay(500);
      }
    }
  }
}

void lightDigit2(byte number) {
  lightSegments(number);
}

void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}