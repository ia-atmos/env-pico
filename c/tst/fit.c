#include "pico.h"
#include "../check.h"
#include <math.h>

int main (void) {
    pico_open(NULL);
    pico_set_app_title("Fit");

    // a wide window (400x200) with a square world (100x100)
    pico_set_layer(pico_layer_window());
    pico_set_scene_dim((Pico_Rel_Dim){ '!', {400, 200} });
    pico_set_effect_color(PICO_COLOR_BLUE);     // the color of the bars
    pico_set_layer(pico_layer_world());
    pico_set_effect_color(PICO_COLOR_WHITE);
    pico_set_pencil_color(PICO_COLOR_RED);
    Pico_Rel_Rect r = { '%', {0.5, 0.5, 0.5, 0.5}, PICO_ANCHOR_C };

    // default: stretched (deformed)
    assert(pico_get_scene_fit() == PICO_FIT_STRETCH);
    pico_output_clear();
    pico_output_draw_oval(r);
    _pico_check("fit-01");

    // bars: a 200x200 world in the middle, blue bars on the sides
    pico_set_scene_fit(PICO_FIT_BARS);
    assert(pico_get_scene_fit() == PICO_FIT_BARS);
    pico_output_clear();
    pico_output_draw_oval(r);
    _pico_check("fit-02");

    // positions discount the bars: window pixel -> world
    {
        Pico_Rel_Pos w = { '!', {200, 100}, PICO_ANCHOR_NW };
        Pico_Rel_Pos p = { '%', {0, 0}, PICO_ANCHOR_NW };
        pico_cv_pos(pico_layer_world(), &p, pico_layer_window(), &w);
        assert(fabs(p.x-0.5)<0.01 && fabs(p.y-0.5)<0.01);
        w.x = 100; w.y = 0;                 // where the world starts
        pico_cv_pos(pico_layer_world(), &p, pico_layer_window(), &w);
        assert(fabs(p.x)<0.01 && fabs(p.y)<0.01);
        w.x = 50; w.y = 100;                // on the left bar: outside
        pico_cv_pos(pico_layer_world(), &p, pico_layer_window(), &w);
        assert(p.x < 0);
    }

    // zoom composes: half of the world (50x100 crop) keeps 1:2
    pico_set_scene_src((Pico_Rel_Rect){ '%', {0.5, 0.5, 0.5, 1}, PICO_ANCHOR_C });
    pico_output_clear();
    pico_output_draw_oval(r);
    _pico_check("fit-03");

    // a tall window: bars above and below
    pico_set_scene_src((Pico_Rel_Rect){ '%', {0.5, 0.5, 1, 1}, PICO_ANCHOR_C });
    pico_set_layer(pico_layer_window());
    pico_set_scene_dim((Pico_Rel_Dim){ '!', {200, 400} });
    pico_set_layer(pico_layer_world());
    pico_output_clear();
    pico_output_draw_oval(r);
    _pico_check("fit-04");

    // and back to stretch
    pico_set_scene_fit(PICO_FIT_STRETCH);
    pico_output_clear();
    pico_output_draw_oval(r);
    _pico_check("fit-05");

    pico_close();
    return 0;
}
