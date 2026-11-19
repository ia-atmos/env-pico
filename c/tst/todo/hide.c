#include "pico.h"

int main (void) {
    pico_open(NULL);
    pico_set_app_title("Show - Hide");
    pico_input_event(NULL, PICO_EVENT_KEY_DN);

    pico_set_app_show(0);
    puts("hidden");
    pico_input_delay(1000);

    pico_set_app_show(1);
    puts("shown");
    pico_input_event(NULL, PICO_EVENT_KEY_DN);

    pico_set_app_show(0);
    puts("hidden");
    pico_input_delay(1000);

    pico_close();
    return 0;
}
