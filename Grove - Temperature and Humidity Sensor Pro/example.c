#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dht22.h>

int main()
{
    printf("starting up ...\n");

    if (dht22_setup() == -1)
    {
        printf("error!!\n");
        return 1;
    }

    int pin = 3;
    float humidity = -1.0;
    float temperature = -1.0;
    int status = 0;

    while (1)
    {
        status = dht22_read(pin, &humidity, &temperature);

        printf("status: %d\n", status);
        printf("humidity: %.2f\n", humidity);
        printf("temperature: %.2f\n", temperature);

        sleep(2);
    }

    return 0;
}
