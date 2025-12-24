#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
// AFL++ Persistent Mode
__AFL_FUZZ_INIT();

int main() {

    SetTraceLogLevel(LOG_NONE);
    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;

    while (__AFL_LOOP(10000)) {
        int len = __AFL_FUZZ_TESTCASE_LEN;
        
        if (len < 40) continue;

        int fontSize = 32;
        int glyphCount = 0;

        GlyphInfo *glyphs = LoadFontData(buf, len, fontSize, NULL, 0, FONT_DEFAULT, &glyphCount);

        if (glyphs != NULL && glyphCount > 0) {

            Rectangle *glyphRecs = NULL;
            Image atlas = GenImageFontAtlas(glyphs, &glyphRecs, glyphCount, fontSize, 4, 0);

            UnloadImage(atlas);
            if (glyphRecs != NULL) {
                RL_FREE(glyphRecs);
            }
            UnloadFontData(glyphs, glyphCount);
        }
    }

    return 0;
}
