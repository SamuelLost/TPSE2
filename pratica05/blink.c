#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define TO_SEC(t) ((t) * 1000000)

const char high[] = "1";
const char low[] = "0";

int setLed(int power) {
	FILE *led = NULL; //declare pointers
	led = fopen("/sys/class/leds/beaglebone:green:usr0/brightness", "w");
	if (power)
		fwrite(high, 1, sizeof(high), led);
	else
		fwrite(low, 1, sizeof(low), led);
	fclose(led);
	
	led = fopen("/sys/class/leds/beaglebone:green:usr1/brightness", "w");
	if (power)
		fwrite(high, 1, sizeof(high), led);
	else
		fwrite(low, 1, sizeof(low), led);
	fclose(led);
	
	led = fopen("/sys/class/leds/beaglebone:green:usr2/brightness", "w");
	if (power)
		fwrite(high, 1, sizeof(high), led);
	else
		fwrite(low, 1, sizeof(low), led);
	fclose(led);
	
	led = fopen("/sys/class/leds/beaglebone:green:usr3/brightness", "w");
	if (power)
		fwrite(high, 1, sizeof(high), led);
	else
		fwrite(low, 1, sizeof(low), led);
	fclose(led);
	
	return 1;
}

int main(int argc, char* args[]) {
	int ledStatus = 0;
	
	// if (argc < 3) {
	// 	printf("Bad execution call\nExample of run: ./program <quantity> <time in sec>\n\n");
	// 	return 0;
	// }
	
	// int time = atoi(args[2]);
	// int times = atoi(args[1]);
	
	for (int i = 0; i < 5; i++) {
		setLed(ledStatus);
		usleep(TO_SEC(1));
		ledStatus ^= 1;
	}
	
	return 0;
}