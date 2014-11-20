#pragma once;
#include <Serial.h>
#include <Arduino.h>
#include <string.h>
#include <stdarg.h>

const float pi = 3.14;

float lerp(float v0, float v1, float t) 
{
  return (1-t)*v0 + t*v1;
}

void error(char arr[]) 
{
  Serial.print("ERROR!!!: ");
  Serial.println(arr);
}

int log(char *str, ...) {
	int i, j, count = 0;
 
	va_list argv;
	va_start(argv, str);
	for(i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] == '%') {
			count++;
 
			Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);
 
			switch (str[++i]) {
				case 'd': Serial.print(va_arg(argv, int));
					break;
				case 'l': Serial.print(va_arg(argv, long));
					break;
				case 'f': Serial.print(va_arg(argv, double));
					break;
				case 'c': Serial.print((char) va_arg(argv, int));
					break;
				case 's': Serial.print(va_arg(argv, char *));
					break;
				case '%': Serial.print("%");
					break;
				default:;
			};
 
			j = i+1;
		}
	};
	va_end(argv);
 
	if(i > j) {
		Serial.write(reinterpret_cast<const uint8_t*>(str+j), i-j);
	}
       Serial.println();
	return count;
}
