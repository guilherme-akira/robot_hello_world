#include <Arduino.h>
#include <WiFi.h>

// Audio
#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// SD card
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// SPI connection
#define SPI_PIN_SCK       (18)
#define SPI_PIN_MISO      (19)
#define SPI_PIN_MOSI      (23)

// SD card connection
#define SD_PIN_SCK        SPI_PIN_SCK
#define SD_PIN_MISO       SPI_PIN_MISO
#define SD_PIN_MOSI       SPI_PIN_MOSI
#define SD_PIN_CS         (4)
#define SD_AUDIO_DIR      "/audios/"
#define SD_IMAGE_DIR      "/images/"

// Audio
#define AUDIO_PIN_VOLUME  (15)
#define AUDIO_VOLUME_MIN  (0.0)
#define AUDIO_VOLUME_MAX  (4.0)

// Audio declarations
File audio_dir;
AudioFileSourceSD *audio_source = NULL;
AudioGeneratorMP3 *mp3  = NULL;
AudioOutputI2S    *audio_output  = NULL;

// SD card declarations

bool setup_sd(char *error) {
  bool ret = true;

  do {
    SPI.begin(SD_PIN_SCK, SD_PIN_MISO, SD_PIN_MOSI, SD_PIN_CS);

    if (!SD.begin(SD_PIN_CS)) {
      ret = false;
      strcpy(error, "[SD] Card mount failed!");
      break;
    }

    if (SD.cardType() == CARD_NONE) {
      ret = false;
      strcpy(error, "[SD] No SD card attached!");
      break;
    }
  } while(false);

  return ret;
}

bool setup_audio(char *error) {
  bool ret = true;

  do {
    audioLogger = &Serial;
    if (!(audio_source = new AudioFileSourceSD())) {
      ret = false;
      strcpy(error, "[AUDIO] Failed on audio_source allocation!");
      break;
    }

    if (!(audio_output = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC))) {
      ret = false;
      strcpy(error, "[AUDIO] Failed on audio_output allocation!");
      delete audio_source;
      break;
    }

    if (!(mp3 = new AudioGeneratorMP3())) {
      ret = false;
      strcpy(error, "[AUDIO] Failed on MP3 generator allocation!");
      delete audio_source;
      delete audio_output;
      break;
    }

    //mp3->SetBufferSize(3*1024);
    //mp3->SetSampleRate(44100);
    //mp3->SetStereoSeparation(32);
    //mp3->begin(audio_source, audio_output);
    audio_dir = SD.open(SD_AUDIO_DIR);
  } while(false);

  return ret;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  // General
  char error[80];
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  delay(1000);

  if (!setup_sd(error) ||
      !setup_audio(error)) {
    Serial.printf("ERROR: %s\n\r", error);
    return;
  }
}

void loop()
{
  // Set volume
  //int analog_read = analogRead(AUDIO_PIN_VOLUME);
  //audio_output->SetGain(mapFloat(analog_read, 0, 4095, AUDIO_VOLUME_MIN, AUDIO_VOLUME_MAX));
  audio_output->SetGain(0.4);

  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    File audio_file = audio_dir.openNextFile();
    if (audio_file) {
      Serial.printf("File name: %s\n", audio_file.name());
      if (String(audio_file.name()).endsWith(".mp3")) {
        audio_source->close();
        if (audio_source->open(SD_AUDIO_DIR "hello_world.mp3")) {
          mp3->begin(audio_source, audio_output);
        } else {
          Serial.printf("Error opening file\n");
          //Serial.printf_P(PSTR("Error opening '%s'\n"), file.name());
        }
      }
    } else {
      Serial.printf("MP3 done\n");
      delay(1000);
    }
  }
}
