const int ledArray[] = {8,9,10,11,12};
const int upPlayer = 8;
int upScore, downScore = 0;
const int downPlayer = 12;
const int defaultTimer = 75;
int currentServe;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for(int i= 0; i < 5; ++i) {
    pinMode(ledArray[i], OUTPUT);
  }

  Serial.println("Tennis, v0.1.0");
  opening();
  Serial.println("The Match Bengins!");
  currentServe = coinToss();
}

void loop() {
  volley(); 
}

void opening() {
  for(int i = 0; i < 5; ++i) {
    digitalWrite(downPlayer, HIGH);
    digitalWrite(upPlayer, HIGH);
    delay(defaultTimer);
    digitalWrite(downPlayer, LOW);
    digitalWrite(upPlayer, LOW);
    delay(defaultTimer);
  }
}

int coinToss() {
  int coin = random(0,2);
  if(coin == 0) {
    pulse(upPlayer, 5, defaultTimer);
    return upPlayer;
  } else if(coin == 1) {
    pulse(downPlayer, 5, defaultTimer); 
    return downPlayer;
  }
}

void pulse(int player, int count, int timer) {
  for(int i = 0; i < count; i++) {
    digitalWrite(player, HIGH);
    delay(defaultTimer);
    digitalWrite(player, LOW);
    delay(defaultTimer);
  }
}

void checkForWin() {
  if(upScore == 11) {
    pulse(upPlayer, 10, defaultTimer);
    endGame();
  } else if (downScore == 1) {
    pulse(downPlayer, 10, defaultTimer);
    endGame();
  }
}

void endGame() {
  while(1);
}

void volley() {
  checkForWin();
  if(currentServe == upPlayer) {
    upHit();
  } else {
    downHit();
  }

}


bool winner() {
  int r = random(0, 200);
  if(r > 194) {
    return true;
  } else {
    return false;
  }
}

void upHit() {
  int timer = random(0,75);
  for(int i = 0; i < 4; ++i) {
    digitalWrite(ledArray[i], HIGH);
    delay(timer);
    digitalWrite(ledArray[i], LOW);
    delay(timer);   
  }
  if(winner){
    upScore++;
    pulse(upPlayer, 4, defaultTimer);
    currentServe = upPlayer;
    volley();
  } else {
    downHit();
  }
}

void downHit() {
  int timer = random(0,75);
  for(int i = 4; i > 0; --i) {
    digitalWrite(ledArray[i], HIGH);
    delay(timer);
    digitalWrite(ledArray[i], LOW);
    delay(timer); 
  }
  if(winner){
    downScore++;
    pulse(downPlayer, 4, defaultTimer);
    currentServe = downPlayer;
    volley();
  } else {
    upHit();
  }
}
