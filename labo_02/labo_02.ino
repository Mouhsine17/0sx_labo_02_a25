const int ledPins[] = { 8, 9, 10, 11 };
int potentiometerPin = A1;
int btnPoussoir = 2;
unsigned long currentTime = 0;
int potentiometerValue = 0;
int mappedIndex = 0;
int valeurMax = 1023;
int valeurMin = 0 ;
int convMax = 20;
int progressionMax=100;
void setup() {

  // Ton code ici
  Serial.begin(9600);
  // Configuration de la broche en mode INPUT_PULLUP
  pinMode(btnPoussoir, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    // Initialisation des DEL en sortie
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.println("Setup completed");
}

int estClic(unsigned long ct) {
  static unsigned long lastTime = 0;
  static int lastState = HIGH;
  const int rate = 50;
  int clic = 0;

  if (ct - lastTime < rate) {
    return clic;  // Trop rapide
  }

  lastTime = ct;

  int state = digitalRead(btnPoussoir);

  if (state == LOW) {
    if (lastState == HIGH) {
      clic = 1;
    }
  }

  lastState = state;

  return clic;
}


void afficherBarre(int value) {
  int pourcentage =( (value * progressionMax) / convMax)*5;

  Serial.print("[");
  for (int i = 0; i < value; i++) {
    Serial.print("#");
  }
  for (int i = value; i < convMax; i++) {
    Serial.print(".");
  }
  Serial.print("] ");
  Serial.print(pourcentage);
  Serial.println("%");
}

void eclairage() {
  potentiometerValue = analogRead(potentiometerPin);
  mappedIndex = map(potentiometerValue, valeurMin, valeurMax, 0, 3);
  for (int i = 0; i < 4; i++) {
    if (i == mappedIndex) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}


void loop() {
  currentTime = millis();
  int valeurBouton = digitalRead(btnPoussoir);
  potentiometerValue = analogRead(potentiometerPin);
  mappedIndex = map(potentiometerValue, valeurMin, valeurMax, valeurMin, convMax);
  eclairage();
  if (estClic(millis())) {
    afficherBarre(mappedIndex);
  }
}
