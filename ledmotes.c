#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"
#include "distance-sensor.h" // Include the hypothetical distance sensor library

// Blink the LEDs based on distance sensor value
static struct etimer blinktimer;
static uint8_t distance_value;

PROCESS(distance_led_process, "Distance LED Process");
AUTOSTART_PROCESSES(&distance_led_process);

PROCESS_THREAD(distance_led_process, ev, data)
{
  PROCESS_BEGIN();
  
  // Activate the distance sensor
  SENSORS_ACTIVATE(distance_sensor);

  while (1)
  {
    // Set the timer to 1 second
    etimer_set(&blinktimer, CLOCK_SECOND);
    
    // Wait for the timer event
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
    
    // Read the distance sensor value
    distance_value = distance_sensor.value(DISTANCE_SENSOR_VALUE);
    
    // Light up LEDs based on distance value
    // Assuming distance value ranges from 0 to 255
    leds_off(LEDS_ALL);
    if (distance_value < 64)
    {
      leds_on(LEDS_BLUE);  // Very close
    }
    else if (distance_value < 128)
    {
      leds_on(LEDS_GREEN); // Moderately close
    }
    else if (distance_value < 192)
    {
      leds_on(LEDS_YELLOW); // Not too close
    }
    else
    {
      leds_on(LEDS_RED);    // Far away
    }
    
    // Print the state of the LEDs
    printf("Distance Value: %d, LED State: %0.2X\n", distance_value, leds_get());
  }
  
  PROCESS_END();
}
