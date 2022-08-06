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

#include <lite/check.h>
#include <lite/lite.h>
#include <lite/window.h>

static void check1_press( LiteCheck *check1, LiteCheckState state, void *data )
{
     LiteCheck *check2 = data;

     lite_enable_check( check2, state == LITE_CHS_CHECKED ? 1 : 0 );

     lite_set_check_caption( check1, state == LITE_CHS_CHECKED ? "check1 - disable check2" : "check1 - enable check2" );
}

static void check2_press( LiteCheck *check2, LiteCheckState state, void *data )
{
     lite_close_window( data );
}

int main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteCheck    *check1, *check2;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 240; rect.h = 90;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Check Test", &window );

     /* setup the 1st check */
     rect.x = 20; rect.y = 20; rect.w = 170; rect.h = 20;
     lite_new_check( LITE_BOX(window), &rect, "check1 - enable check2", liteDefaultCheckTheme, &check1 );

     /* setup the 2nd check */
     rect.x = 40; rect.y = 50; rect.w = 185; rect.h = 20;
     lite_new_check( LITE_BOX(window), &rect, "check2 - exit application if pressed", liteDefaultCheckTheme, &check2 );
     lite_enable_check( check2, 0 );

     /* install callbacks */
     lite_on_check_press( check1, check1_press, check2 );
     lite_on_check_press( check2, check2_press, window );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
