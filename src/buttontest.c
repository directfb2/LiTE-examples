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

#include <lite/button.h>
#include <lite/lite.h>
#include <lite/window.h>

static void button1_press( LiteButton *button1, void *data )
{
     LiteButtonState  state;
     LiteButton      *button2 = data;

     lite_get_button_state( button2, &state );

     lite_enable_button( button2, (state == LITE_BS_DISABLED || state == LITE_BS_DISABLED_ON) ? 1 : 0 );
}

static void button2_press( LiteButton *button2, void *data )
{
     LiteButtonState  state;
     LiteButton      *button3 = data;

     lite_get_button_state( button2, &state );

     lite_enable_button( button3, state == LITE_BS_HILITE_ON ? 1 : 0 );

     lite_set_button_image( button3, LITE_BS_NORMAL, state == LITE_BS_HILITE_ON ? DATADIR"/D.dfiff" : NULL );
}

static void button3_press( LiteButton *button3, void *data )
{
     lite_close_window( data );
}

int main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteButton   *button1, *button2, *button3;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 180; rect.h = 70;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Button Test", &window );

     /* setup the 1st button */
     rect.x = 10; rect.y = 10; rect.w = 50; rect.h = 50;
     lite_new_button( LITE_BOX(window), &rect, liteDefaultButtonTheme, &button1 );

     /* setup the 2nd button */
     rect.x = 60; rect.y = 10; rect.w = 50; rect.h = 50;
     lite_new_button( LITE_BOX(window), &rect, liteDefaultButtonTheme, &button2 );
     lite_enable_button( button2, 0 );
     lite_set_button_type( button2, LITE_BT_TOGGLE );

     /* setup the 3rd button */
     rect.x = 120; rect.y = 20; rect.w = 52; rect.h = 30;
     lite_new_button( LITE_BOX(window), &rect, liteNoButtonTheme, &button3 );
     lite_enable_button( button3, 0 );

     /* install callbacks */
     lite_on_button_press( button1, button1_press, button2 );
     lite_on_button_press( button2, button2_press, button3 );
     lite_on_button_press( button3, button3_press, window );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
