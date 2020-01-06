#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dht22.h>

int main() {
    printf("starting up ...\n");

    if (dht22_setup() == -1) {
        printf("error!!");
        return 1;
    }

    int pin = 4;
    int humidity = -1;
    int temperature = -1;
    int status = 0;

    while (1) {
        sleep(2);
        status = dht22_read(pin, &humidity, &temperature);

        printf("status: %d\n", status);
        printf("humidity: %d\n", humidity); // durch float 10 teilen!
        printf("temperature: %d\n", temperature);
    }

    return 0;
}
