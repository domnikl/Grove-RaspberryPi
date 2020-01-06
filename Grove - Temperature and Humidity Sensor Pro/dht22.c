#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_TIMINGS 85
int data[5] = {0, 0, 0, 0, 0};

int dht22_setup()
{
    return wiringPiSetup();
}

int dht22_read(int pin, float *humidity, float *temperature)
{
    delay(2000);

    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    /* pull pin down for 18 milliseconds */
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);

    /* prepare to read the pin */
    pinMode(pin, INPUT);

    /* detect change and read data */
    for (i = 0; i < MAX_TIMINGS; i++)
    {
        counter = 0;
        while (digitalRead(pin) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
            {
                break;
            }
        }

        laststate = digitalRead(pin);

        if (counter == 255)
        {
            printf("breaking ...\n");
            break;
        }

        /* ignore first 3 transitions */
        if ((i >= 4) && (i % 2 == 0))
        {
            /* shove each bit into the storage bytes */
            data[j / 8] <<= 1;
            if (counter > 16)
                data[j / 8] |= 1;
            j++;
        }
    }

    printf("j = %d\n", j);

    /*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
    if ((j >= 40) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        float h = (float)((data[0] << 8) + data[1]) / 10;

        if (h > 100)
        {
            h = data[0]; // for DHT11
        }

        float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;

        if (c > 125)
        {
            c = data[2]; // for DHT11
        }

        if (data[2] & 0x80)
        {
            c = -c;
        }

        *humidity = h;
        *temperature = c;

        printf("Humidity = %.1f %% Temperature = %.1f *C\n", h, c);
        return 1;
    }
    else
    {
        printf("Data not good, skip\n");
        return 0;
    }
}
