#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int DEFAULT_W = 36;
const int DEFAULT_H = 44;
const int DEFAULT_X_L = 38; 
const int DEFAULT_X_R = 90; 
const int DEFAULT_Y = 32;
const int CORNER_RADIUS = 10;

const float MOVE_SPEED = 0.25; 
const float BLINK_SPEED = 0.45;

struct Eye {
  float x, y;      
  float w, h;      
  float targetX, targetY; 
  float targetW, targetH; 
};

Eye leftEye;
Eye rightEye;

enum State {
  IDLE,
  BLINKING,
  HAPPY,
  CONFUSED,
  SAD
};

State currentState = IDLE;
State lastState = IDLE;

unsigned long lastStateChange = 0;
unsigned long nextEventTime = 0;
unsigned long blinkStartTime = 0;
bool isBlinkClosing = true;

void setup() {
  Serial.begin(115200);

  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }


  resetEyeTargets();
  leftEye.x = leftEye.targetX; leftEye.y = leftEye.targetY;
  leftEye.w = leftEye.targetW; leftEye.h = leftEye.targetH;
  rightEye.x = rightEye.targetX; rightEye.y = rightEye.targetY;
  rightEye.w = rightEye.targetW; rightEye.h = rightEye.targetH;

  display.clearDisplay();
  display.display();
  
  pickNextBehavior();
}

void loop() {
  unsigned long currentMillis = millis();

  handleBehavior(currentMillis);

  updatePhysics();


  drawEyes();
}


void updatePhysics() {
  
  leftEye.x += (leftEye.targetX - leftEye.x) * MOVE_SPEED;
  leftEye.y += (leftEye.targetY - leftEye.y) * MOVE_SPEED;
  leftEye.w += (leftEye.targetW - leftEye.w) * MOVE_SPEED;
  leftEye.h += (leftEye.targetH - leftEye.h) * BLINK_SPEED; 

  rightEye.x += (rightEye.targetX - rightEye.x) * MOVE_SPEED;
  rightEye.y += (rightEye.targetY - rightEye.y) * MOVE_SPEED;
  rightEye.w += (rightEye.targetW - rightEye.w) * MOVE_SPEED;
  rightEye.h += (rightEye.targetH - rightEye.h) * BLINK_SPEED;
}

void drawEyes() {
  display.clearDisplay();


  display.fillRoundRect(
    (int)(leftEye.x - leftEye.w/2), 
    (int)(leftEye.y - leftEye.h/2), 
    (int)leftEye.w, 
    (int)leftEye.h, 
    CORNER_RADIUS, SSD1306_WHITE
  );

  display.fillRoundRect(
    (int)(rightEye.x - rightEye.w/2), 
    (int)(rightEye.y - rightEye.h/2), 
    (int)rightEye.w, 
    (int)rightEye.h, 
    CORNER_RADIUS, SSD1306_WHITE
  );

  display.display();
}


void resetEyeTargets() {
  leftEye.targetW = DEFAULT_W;
  leftEye.targetH = DEFAULT_H;
  rightEye.targetW = DEFAULT_W;
  rightEye.targetH = DEFAULT_H;
  

  leftEye.targetY = DEFAULT_Y;
  rightEye.targetY = DEFAULT_Y;
  
  
  leftEye.targetX = DEFAULT_X_L;
  rightEye.targetX = DEFAULT_X_R;
}

void pickNextBehavior() {
 
  int choice = random(0, 100);

  if (choice < 40) {
    
    currentState = IDLE;
    lookAround();
    nextEventTime = millis() + random(500, 2000); 
  } 
  else if (choice < 80) {
    
    currentState = BLINKING;
    isBlinkClosing = true;
    blinkStartTime = millis();

  }
  else if (choice < 90) {
    
    currentState = CONFUSED;
    setExpressionConfused();
    nextEventTime = millis() + 2500; 
  }
  else {
    
    currentState = HAPPY;
    setExpressionHappy();
    nextEventTime = millis() + 2000;
  }
}

void handleBehavior(unsigned long now) {
  
  
  if (currentState == BLINKING) {
    if (isBlinkClosing) {
      leftEye.targetH = 2; 
      rightEye.targetH = 2;
      if (abs(leftEye.h - 2) < 1) { 
        isBlinkClosing = false; 
      }
    } else {
      leftEye.targetH = DEFAULT_H; 
      rightEye.targetH = DEFAULT_H;
      if (abs(leftEye.h - DEFAULT_H) < 2) { 
        currentState = IDLE; 
        nextEventTime = now + random(200, 1000); 
      }
    }
    return; 
  }

  
  if (now > nextEventTime) {
    pickNextBehavior();
  }
}



void lookAround() {
  
  resetEyeTargets();


  int lookX = random(-15, 15);
  int lookY = random(-10, 10);

  leftEye.targetX = DEFAULT_X_L + lookX;
  rightEye.targetX = DEFAULT_X_R + lookX;
  
  leftEye.targetY = DEFAULT_Y + lookY;
  rightEye.targetY = DEFAULT_Y + lookY;
}

void setExpressionHappy() {

  leftEye.targetH = 15;
  leftEye.targetW = 42;
  leftEye.targetY = DEFAULT_Y - 5; // Move up

  rightEye.targetH = 15;
  rightEye.targetW = 42;
  rightEye.targetY = DEFAULT_Y - 5;
}

void setExpressionConfused() {

  resetEyeTargets();
  

  leftEye.targetH = 10;
  leftEye.targetY = DEFAULT_Y - 5;
  rightEye.targetW = 40;
  rightEye.targetH = 48;
}