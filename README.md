👀 Animated OLED Eyes (Arduino)

A smooth animated robot eyes project using a 128×64 OLED display (SSD1306) and Arduino.
The eyes can blink, look around, and show expressions like happy and confused, giving your robot or project a lively personality.

✨ Features

Smooth eye movement using interpolation

Random behaviors:

Idle look-around

Blinking

Happy expression

Confused expression

Rounded eye shapes for a modern look

Non-blocking animations using millis()

🧰 Hardware Required

Arduino Uno / Nano / Mega (any compatible board)

128×64 OLED Display (SSD1306, I2C)

Jumper wires

USB cable

🔌 OLED Wiring (I2C)
OLED Pin	Arduino Pin
VCC	5V / 3.3V
GND	GND
SDA	A4 (Uno/Nano)
SCL	A5 (Uno/Nano)

⚠️ OLED I2C address used: 0x3C

📦 Required Libraries

You must install all libraries below before uploading the code.

1️⃣ Libraries List

Adafruit SSD1306

Adafruit GFX Library

Wire (built-in)

SPI (built-in)

📥 Library Installation Process
Method 1: Arduino Library Manager (Recommended)

Open Arduino IDE

Go to Sketch → Include Library → Manage Libraries

Search and install:

Install in this order:
Adafruit GFX Library
Adafruit SSD1306


Restart Arduino IDE after installation

Method 2: Manual Installation (Optional)

Download libraries from GitHub:

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit_SSD1306

Extract ZIP files

Move folders to:

Documents/Arduino/libraries/


Restart Arduino IDE

⚙️ Configuration Details
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C


If your OLED does not display anything, try changing:

#define SCREEN_ADDRESS 0x3D

▶️ How It Works

Each eye is treated as an object with:

Position (x, y)

Size (width, height)

Target values for smooth animation

Physics-style interpolation creates smooth motion

Random behavior selection controls expressions

No delay() is used → smooth & responsive animation

🧠 Expressions Implemented
Expression	Description
Idle	Eyes randomly look around
Blink	Natural eyelid animation
Happy	Smaller height, wider eyes
Confused	Asymmetrical eye sizes
🚀 Upload Steps

Connect Arduino via USB

Select Board and Port

Click Upload

Watch the eyes come alive 👀✨

🛠️ Customization Ideas

Add sad / angry expressions

Control eyes using:

Ultrasonic sensor

IR sensor

Bluetooth (HC-05)

Sync eyes with robot movement

Add mouth animation on another OLED
