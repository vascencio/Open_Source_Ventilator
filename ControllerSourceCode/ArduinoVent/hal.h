#ifndef HAL_H
#define HAL_H

/*************************************************************
 * Open Ventilator
 * Copyright (C) 2020 - Marcelo Varanda
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************
*/
#include "log.h"
#include <stdint.h>

#ifdef VENTSIM
  #include <QPlainTextEdit>
  #define PROGMEM /**/
  #define F /**/
#else
  #include <Arduino.h>
    #include <avr/pgmspace.h>
  #include "LiquidCrystal_I2C_mv.h"
#endif

#define LCD_NUM_ROWS 4
#define LCD_NUM_COLS 20

typedef enum {
  MONITOR_LED_NORMAL,
  MONITOR_LED_FAST,
  MONITOR_LED_SLOW,
} MONITOR_LET_T;

#ifdef VENTSIM
  void halInit(QPlainTextEdit * ed);
#else
  void halInit(uint8_t reset_val);
  //void LOG(const char * c);
//  #ifdef DEBUG_SERIAL_LOGS
//    #define LOG(x) Serial.print(F(x))
//  #else
//    #define LOG(x) /* dummy */
//  #endif
#endif

void halSetMonitorLED (MONITOR_LET_T speed);
MONITOR_LET_T halGetMonitorLED ();

uint64_t halStartTimerRef();
bool halCheckTimerExpired(uint64_t timerRef, uint64_t lapseTime);

void halWriteSerial(char * s);

void halLoop();
void halBlinkLED();
void halLcdClear();
void halLcdSetCursor(int col, int row);
void halLcdWrite(const char * txt);
void halLcdWrite(int col, int row, const char * txt);

void halValveInOn();
void halValveInOff();
void halValveOutOn();
void halValveOutOff();

uint8_t EEPROM_read(int addr);
void EEPROM_write(uint8_t val, int addr);



#endif // HAL_H
