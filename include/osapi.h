/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _OSAPI_H_
#define _OSAPI_H_

#include <string.h>
#include "ets_sys.h"
#include "config.h"

void ets_bzero(void *s, size_t n);
void ets_delay_us(uint32_t us);
void ets_install_putc1(void (*p)(char c));

int ets_memcmp(const void *str1, const void *str2, unsigned int nbyte);
void *ets_memcpy(void *dest, const void *src, unsigned int nbyte);
void *ets_memmove(void *dest, const void *src, unsigned int nbyte);
void *ets_memset(void *dest, int val, unsigned int nbyte);

int ets_strcmp(const char *s1, const char *s2);
char *ets_strcpy(char *s1, const char *s2);
int ets_strlen(const char *s);
int ets_strncmp(const char *s1, const char *s2, unsigned int n);
char *ets_strncpy(char *s1, const char *s2, unsigned int n);
char *ets_strstr(const char *s1, const char *s2);

void ets_timer_arm_new(ETSTimer *ptimer, uint32_t time, bool repeat_flag, bool ms_flag);
void ets_timer_disarm(ETSTimer *ptimer);
void ets_timer_setfn(ETSTimer *ptimer, ETSTimerFunc *pfunction, void *parg);
int ets_sprintf(char *str, const char *format, ...)  __attribute__ ((format (printf, 2, 3)));
int ets_printf(const char *format, ...)  __attribute__ ((format (printf, 1, 2)));
int ets_snprintf(char *str, unsigned int size, const char *format, ...)  __attribute__ ((format (printf, 3, 4)));

#define ets_uart_printf  ets_printf

#endif

