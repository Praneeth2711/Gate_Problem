// ============================================================
//  Half-Subtractor: Arduino C++ Implementation
//  Inputs : A -> Digital Pin 2 | B -> Digital Pin 3
//  Outputs: D (Difference) -> Pin 12 | X (Borrow) -> Pin 13
//  Logic  : D = A XOR B  | X = (!A) AND B
// ============================================================

const int PIN_A   = 2;   // Minuend input
const int PIN_B   = 3;   // Subtrahend input
const int PIN_D   = 12;  // Difference output LED (Green)
const int PIN_X   = 13;  // Borrow output LED (Red)

void setup() {
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_X, OUTPUT);

  Serial.begin(9600);
  Serial.println("Half-Subtractor Initialised");
  Serial.println("A  B  |  D  X");
}

void loop() {
  bool A = (bool)digitalRead(PIN_A);
  bool B = (bool)digitalRead(PIN_B);

  bool D = A ^ B;         // Difference : D = A XOR B
  bool X = (!A) && B;     // Borrow     : X = A'B

  digitalWrite(PIN_D, D ? HIGH : LOW);
  digitalWrite(PIN_X, X ? HIGH : LOW);

  Serial.print(A); Serial.print("  ");
  Serial.print(B);
  Serial.print("  |  ");
  Serial.print(D); Serial.print("  ");
  Serial.println(X);

  delay(100);
}
