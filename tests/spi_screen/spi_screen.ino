#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_HEIGHT  240
#define TFT_WIDTH   320
#define TFT_DC      21
#define TFT_RST     22
#define TFT_CS      2

#define ROBOT_EYE_HEIGHT    20
#define ROBOT_EYE_WIDTH     10
#define ROBOT_MOUTH_HEIGHT  10
#define ROBOT_MOUTH_WIDTH   20

#define ROBOT_EYE_LEFT_POSITION_X   (1*(TFT_WIDTH/3) - (ROBOT_EYE_WIDTH/2))
#define ROBOT_EYE_LEFT_POSITION_Y   (1*(TFT_HEIGHT/3))
#define ROBOT_EYE_RIGHT_POSITION_X  (2*(TFT_WIDTH/3) - (ROBOT_EYE_WIDTH/2))
#define ROBOT_EYE_RIGHT_POSITION_Y  (1*(TFT_HEIGHT/3))
#define ROBOT_MOUTH_POSITION_X      (1*(TFT_WIDTH/2) - (ROBOT_MOUTH_WIDTH/2))
#define ROBOT_MOUTH_POSITION_Y      (2*(TFT_HEIGHT/3) - ROBOT_MOUTH_WIDTH)

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void test_basic_colors(void);
void test_custom_colors(void);
void test_draw_face(void);
void test_custom_text(String str);

void setup() {
  // put your setup code here, to run once:
  tft.init(TFT_HEIGHT, TFT_WIDTH, SPI_MODE2);
  tft.invertDisplay(0);
  tft.setRotation(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  test_custom_text("basic colors");
  test_basic_colors();
  test_custom_text("custom colors");
  test_custom_colors();
  test_custom_text("draw face");
  test_draw_face();
}

void test_basic_colors(void) {
  tft.fillScreen(ST77XX_WHITE);
  delay(1000);
  tft.fillScreen(ST77XX_RED);
  delay(1000);
  tft.fillScreen(ST77XX_GREEN);
  delay(1000);
  tft.fillScreen(ST77XX_BLUE);
  delay(1000);
  tft.fillScreen(ST77XX_CYAN);
  delay(1000);
  tft.fillScreen(ST77XX_MAGENTA);
  delay(1000);
  tft.fillScreen(ST77XX_YELLOW);
  delay(1000);
  tft.fillScreen(ST77XX_ORANGE);
  delay(1000);
}

void test_custom_colors(void) {
  tft.fillScreen(tft.color565(209, 106, 255));
  delay(1000);
  tft.fillScreen(tft.color565(187, 68, 240));
  delay(1000);
  tft.fillScreen(tft.color565(150, 20, 208));
  delay(1000);
  tft.fillScreen(tft.color565(102, 0, 148));
  delay(1000);
  tft.fillScreen(tft.color565(49, 0, 71));
  delay(1000);
}

void test_draw_face(void) {
  tft.fillRect(0, 0*(TFT_HEIGHT/3), TFT_WIDTH, TFT_HEIGHT/3, tft.color565(63, 145, 219));
  tft.fillRect(0, 1*(TFT_HEIGHT/3), TFT_WIDTH, TFT_HEIGHT/3, tft.color565(54, 157, 218));
  tft.fillRect(0, 2*(TFT_HEIGHT/3), TFT_WIDTH, TFT_HEIGHT/3, tft.color565(99, 150, 193));

  tft.fillRect(ROBOT_EYE_LEFT_POSITION_X, ROBOT_EYE_LEFT_POSITION_Y, ROBOT_EYE_WIDTH, ROBOT_EYE_HEIGHT, ST77XX_WHITE);
  tft.fillRect(ROBOT_EYE_RIGHT_POSITION_X, ROBOT_EYE_RIGHT_POSITION_Y, ROBOT_EYE_WIDTH, ROBOT_EYE_HEIGHT, ST77XX_WHITE);
  tft.fillRect(ROBOT_MOUTH_POSITION_X, ROBOT_MOUTH_POSITION_Y, ROBOT_MOUTH_WIDTH, ROBOT_MOUTH_HEIGHT, ST77XX_WHITE);

  delay(5000);
}

void test_custom_text(String str) {
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.print(str);
  delay(1000);

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(0, 30);
  tft.print(str);
  delay(1000);

  tft.setTextSize(3);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(0, 70);
  tft.print(str);
  delay(1000);

  tft.setTextSize(4);
  tft.setTextColor(ST77XX_BLUE);
  tft.setCursor(0, 120);
  tft.print(str);
  delay(1000);

  tft.setTextSize(5);
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(0, 180);
  tft.print(str);
  delay(1000);
}
