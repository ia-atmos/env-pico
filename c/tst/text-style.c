#include "pico.h"
#include "../check.h"

// bold and italic synthesized from one font file
int main (void) {
    pico_open(NULL);
    pico_set_app_title("Text Style");
    pico_set_pencil_font_path("../res/DejaVuSans.ttf");
    pico_set_pencil_smooth(1);
    Pico_Rel_Rect r1 = { '%', {0.5, 0.2, 0, 0.12}, PICO_ANCHOR_C };
    Pico_Rel_Rect r2 = { '%', {0.5, 0.4, 0, 0.12}, PICO_ANCHOR_C };
    Pico_Rel_Rect r3 = { '%', {0.5, 0.6, 0, 0.12}, PICO_ANCHOR_C };
    Pico_Rel_Rect r4 = { '%', {0.5, 0.8, 0, 0.12}, PICO_ANCHOR_C };

    assert(pico_get_pencil_bold()==0 && pico_get_pencil_italic()==0);
    pico_output_clear();
    pico_output_draw_text("Plain", r1);

    pico_set_pencil_bold(1);
    assert(pico_get_pencil_bold() == 1);
    pico_output_draw_text("Bold", r2);

    pico_set_pencil_bold(0);
    pico_set_pencil_italic(1);
    assert(pico_get_pencil_italic() == 1);
    pico_output_draw_text("Italic", r3);

    pico_set_pencil_bold(1);
    pico_output_draw_text("Both", r4);
    _pico_check("text-style-01");

    // bold is wider; the same string is another entry of the cache
    {
        Pico_Rel_Dim d = { '!', {0, 20} };
        pico_set_pencil_bold(0);
        pico_set_pencil_italic(0);
        Pico_Abs_Dim a = pico_get_text(&d, "Width");
        pico_set_pencil_bold(1);
        Pico_Rel_Dim e = { '!', {0, 20} };
        Pico_Abs_Dim b = pico_get_text(&e, "Width");
        assert(b.w > a.w && b.h == a.h);

        // and back: the plain one again, unchanged
        pico_set_pencil_bold(0);
        Pico_Rel_Dim f = { '!', {0, 20} };
        Pico_Abs_Dim c = pico_get_text(&f, "Width");
        assert(c.w==a.w && c.h==a.h);
    }

    pico_close();
    return 0;
}
