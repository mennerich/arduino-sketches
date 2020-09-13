int ledArray[] = {8,9,10,11,12};
int count = 0;
int r = 0;
int t = 75;
int counter = 0;
int upPlayer = 8;
int downPlayer = 12;
int upScore = 0;
int downScore = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for(count=0; count < 5; ++count) {
    pinMode(ledArray[count], OUTPUT);
  }
  
  opening();
  Serial.println("BEGIN!");
}

void opening() {
  for(count=0; count < 5; ++count) {
    digitalWrite(downPlayer, HIGH);
    digitalWrite(upPlayer, HIGH);
    delay(t);
    digitalWrite(downPlayer, LOW);
    digitalWrite(upPlayer, LOW);
    delay(t);
  }
}

void loop() {
  if(counter == 5) {
    t = random(10, 25);  
    counter = 0;
  }
  
  r = random(0,2);
  if(r ==1) {
    up(t);
  } else {
    down(t);
  }

  ++counter;
}

void up(int timer) {
  for(count=0; count < 5; ++count) {
    digitalWrite(ledArray[count], HIGH);
    delay(timer);
    digitalWrite(ledArray[count], LOW);
    delay(timer);
    score(upPlayer);
  }

}

void down(int timer) {
  for(count=4; count > -1; --count) {
    digitalWrite(ledArray[count], HIGH);
    delay(timer);
    digitalWrite(ledArray[count], LOW);
    delay(timer);
    score(downPlayer);
  }

}

void score(int i) {
  int shot = random(0, 200);
  
  if(shot > 195) {
    Serial.print("SCORE!");
    
    if(i == upPlayer) {
      ++upScore;
    } else if(i == downPlayer){
      ++downScore;
    }

    if(upScore == 11) {
      Serial.print("Up Wins!!");
      win(upPlayer); 
    } else if (downScore == 11) {
      Serial.print("Down Wins!!");
      win(downPlayer);
    }

    Serial.print("Up: ");
    Serial.print(upScore);
    Serial.print("\tDown: ");
    Serial.print(downScore);
    Serial.print("\n");
    
    for(int j = 0; j < 3; ++j) {
      digitalWrite(i, HIGH);
      delay(500);
      digitalWrite(i, LOW);
      delay(500); 
    }
  }
}

void win(int winner) {
    for(int j = 0; j < 10; ++j) {
      digitalWrite(winner, HIGH);
      delay(500);
      digitalWrite(winner, LOW);
      delay(500); 
    }
     while(1);
}
