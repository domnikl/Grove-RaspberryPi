#ifndef dht22_h__
#define dht22_h__
 
extern int dht22_setup();
extern int dht22_read(int pin, int* humidity, int* temperature);
 
#endif  // dht22_h__
