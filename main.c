#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(light_sensor_process, "Light sensor process");
AUTOSTART_PROCESSES(&light_sensor_process);

PROCESS_THREAD(light_sensor_process, ev, data)
{
    static struct etimer timer;

    PROCESS_BEGIN();

    // Initialize the event timer
    etimer_set(&timer, CLOCK_SECOND);

    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        // Simulate cursor detection
        int cursor_detected = rand() % 2;

        if(cursor_detected) {
            leds_on(LEDS_RED);
            printf("Cursor detected, light on\n");
        } else {
            leds_off(LEDS_RED);
            printf("No cursor, light off\n");
        }

        // Reset the timer
        etimer_reset(&timer);
    }

    PROCESS_END();
}
