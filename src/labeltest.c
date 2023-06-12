/*
   This file is part of LiTE-examples.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <lite/label.h>
#include <lite/lite.h>
#include <lite/window.h>

/* macro to be used after the lite_main() function */
#ifdef LITE_MAIN_ENTRYPOINT
#define LITE_MAIN()
#else
#define LITE_MAIN() int main( int argc, char *argv[] ) { return lite_main( argc, argv ); }
#endif

static int on_window_resize( LiteWindow *window, int width, int height )
{
     lite_close_window( window );

     return 1;
}

int lite_main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteLabel    *label1, *label2;
     DFBColor      color  = { 0xff, 0xae, 0x11, 0x16 };

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 160; rect.h = 70;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Label Test", &window );

     /* setup the 1st label */
     rect.x = 10; rect.y = 10;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 17, &label1 );
     lite_set_label_font( label1, "default", LITE_FONT_BOLD, 17, DEFAULT_FONT_ATTRIBUTE );
     lite_set_label_text( label1, "Hello World" );

     /* setup the 2nd label */
     rect.x = 0; rect.y = 40;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 14, &label2 );
     lite_set_label_alignment( label2, LITE_LABEL_CENTER );
     lite_set_label_color( label2, &color );
     lite_set_label_font( label2, "default", LITE_FONT_BOLD | LITE_FONT_ITALIC, 14, DEFAULT_FONT_ATTRIBUTE );
     lite_set_label_text( label2, "Exit if resizing" );

     /* install callback */
     window->OnResize = on_window_resize;

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}

LITE_MAIN()
