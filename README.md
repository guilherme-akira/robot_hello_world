This project is built using the Arduino IDE's support for ESP boards.

Install all the requirements in order to make the IDE support ESP boards (google it if the IDE doesn't pop-up the steps automatically).

Library dependencies:
- Adafruit_GFX.h
  - Go to [Tools] > [Manage Libraries...] > Search for "Adafruit GFX Library" > Install it @ v1.12.1
  - Install possible dependencies
- Adafruit_ST7789.h
  - Go to [Tools] > [Manage Libraries...] > Search for "Adafruit ST7735 and ST7789 Library" > Install it @ v1.11.0
  - Install possible dependencies
- AudioFileSourcePROGMEM.h AudioGeneratorMOD.h AudioOutputI2S.h
  - Go to the Arduino's library folder:
    - Mac: ```~/Documents/Arduino/libraries```
    - Linux: ```~/Arduino/libraries```
  - Clone the repository:
    - ```git clone https://github.com/earlephilhower/ESP8266Audio```
