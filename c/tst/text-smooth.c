#include "pico.h"
#include "../check.h"

int main (void) {
    pico_open(NULL);
    pico_set_app_title("Text Smooth");
    Pico_Rel_Rect r = { '%', {0.5, 0.5, 0, 0.15}, PICO_ANCHOR_C };

    // default: hard edges
    assert(pico_get_pencil_smooth() == 0);
    pico_output_clear();
    pico_output_draw_text("Smooth", r);
    _pico_check("text-smooth-01");

    // smooth edges (same string: another raster)
    pico_set_pencil_smooth(1);
    assert(pico_get_pencil_smooth() == 1);
    pico_output_clear();
    pico_output_draw_text("Smooth", r);
    _pico_check("text-smooth-02");

    // and back
    pico_set_pencil_smooth(0);
    pico_output_clear();
    pico_output_draw_text("Smooth", r);
    _pico_check("text-smooth-01");

    pico_close();
    return 0;
}
