#define LED_RED 26
#define LED_YELLOW 27
#define LED_GREEN 14
#define LED_BLUE 12

#define BUTTON_RED 16
#define BUTTON_YELLOW 17
#define BUTTON_GREEN 5
#define BUTTON_BLUE 18
#define BUTTON_RESET 25

int LEDs[4] = { LED_RED, LED_YELLOW, LED_GREEN, LED_BLUE };
int buttons[4] = { BUTTON_RED, BUTTON_YELLOW, BUTTON_GREEN, BUTTON_BLUE };
int level = 0;
int step = 0;
bool gameOver = false;
int combination[20] = {};


void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
}

void begin() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDs[i], HIGH);
    delay(100);
  }

  delay(500);

  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDs[i], HIGH);
  }

  delay(100);

  for (int i = 3; i >= 0; i--) {
    digitalWrite(LEDs[i], LOW);
  }

  delay(100);

  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDs[i], HIGH);
  }

  delay(500);

  for (int i = 3; i >= 0; i--) {
    digitalWrite(LEDs[i], LOW);
    delay(100);
  }
}

void nextLevel() {
  int randomLED = random(4);
  combination[level] = randomLED;
  level++;
  // Serial.print(randomLED);
}

void playCombination() {
  for (int i = 0; i < level; i++) {
    digitalWrite(LEDs[combination[i]], HIGH);
    delay(500);
    digitalWrite(LEDs[combination[i]], LOW);
    delay(100);
  }
}

void overAnimation() {
  for (int i = 0; i <= 3; i++) {
    digitalWrite(LEDs[i], HIGH);
  }

  delay(100);

  for (int i = 0; i <= 3; i++) {
    digitalWrite(LEDs[i], LOW);
  }

  delay(100);

  for (int i = 0; i <= 3; i++) {
    digitalWrite(LEDs[i], HIGH);
  }
  delay(100);

  for (int i = 0; i <= 3; i++) {
    digitalWrite(LEDs[i], LOW);
  }

  delay(100);
  digitalWrite(LEDs[0], HIGH);
  delay(50);
  digitalWrite(LEDs[0], LOW);
  delay(50);
  digitalWrite(LEDs[0], HIGH);
  delay(50);
  digitalWrite(LEDs[0], LOW);
  delay(50);
  digitalWrite(LEDs[0], HIGH);
  delay(50);
  digitalWrite(LEDs[0], LOW);
  delay(50);
  digitalWrite(LEDs[0], HIGH);
  delay(50);
  digitalWrite(LEDs[0], LOW);
  delay(50);
}

void awaitPlayer() {
  int pressedButton = 0;
  for (int i = 0; i < level; i++) {
    bool played = false;
    while (!played) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(buttons[i]) == LOW) {
          pressedButton = i;
          digitalWrite(LEDs[i], HIGH);
          delay(500);
          digitalWrite(LEDs[i], LOW);
          played = true;
        }
      }
    }

    if (combination[step] != pressedButton) {
      overAnimation();
      gameOver = true;
      break;
    }
    step = step + 1;
  }
  step = 0;
}

void loop() {
  static bool ifElseReset = false;

  int buttonResetState = digitalRead(BUTTON_RESET);
  if (!ifElseReset) {
    if (buttonResetState == LOW) {
      Serial.println("Botão RESET detectado.");
      begin();

      delay(1000);

      ifElseReset = true;
    }
  } else {
    Serial.println("Botão RESET NÃO detectado.");

    nextLevel();
    playCombination();
    awaitPlayer();

    if (gameOver == true) {
      combination[32] = {};
      level = 0;
      step = 0;
      gameOver = false;
      ifElseReset = false;
    }
    delay(1000);
  }
}
