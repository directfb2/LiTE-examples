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

#include <lite/lite.h>
#include <lite/textbutton.h>
#include <lite/window.h>

static void textbutton1_press( LiteTextButton *textbutton1, void *data )
{
     LiteWindow *window = data;

     lite_close_window( window );
}

static void textbutton2_press( LiteTextButton *textbutton2, void *data )
{
     LiteTextButtonState  state;
     LiteTextButton      *textbutton1 = data;

     lite_get_text_button_state( textbutton1, &state );

     lite_enable_text_button( textbutton1, state == LITE_TBS_DISABLED ? 1 : 0 );

     lite_set_text_button_caption( textbutton2,
                                   state == LITE_TBS_DISABLED ? "Disable Exit TextButton" : "Enable Exit TextButton" );
}

int main( int argc, char *argv[] )
{
     DFBRectangle    rect;
     LiteWindow     *window;
     LiteTextButton *textbutton1, *textbutton2, *textbutton3;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 200; rect.h = 180;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "TextButton Test", &window );

     /* setup the 1st text button */
     rect.x = 20; rect.y = 20; rect.w = 86; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Exit", liteDefaultTextButtonTheme, &textbutton1 );
     lite_enable_text_button( textbutton1, 0 );

     /* setup the 2nd text button */
     rect.x = 20; rect.y = 60; rect.w = 160; rect.h = 60;
     lite_new_text_button( LITE_BOX(window), &rect, "Enable Exit TextButton", liteDefaultTextButtonTheme, &textbutton2 );

     /* setup the 3rd text button */
     rect.x = 20; rect.y = 140; rect.w = 160; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Loooooooooooooong text", liteDefaultTextButtonTheme, &textbutton3 );

     /* install callbacks */
     lite_on_text_button_press( textbutton1, textbutton1_press, window );
     lite_on_text_button_press( textbutton2, textbutton2_press, textbutton1 );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
