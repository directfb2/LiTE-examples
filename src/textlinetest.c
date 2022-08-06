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
#include <lite/textline.h>
#include <lite/window.h>

static void on_enter( const char *text, void *data )
{
     LiteTextLine *textline2 = data;
     int           i         = 0;
     int           len       = strlen( text );
     char         *argv[len+1];
     char         *delay;

     if (len < 1)
          return;

     while (*text) {
          if (*text == ' ') {
               *(char*) text++ = 0;
               continue;
          }

          argv[i++] = (char*) text++;

          while (*text && *text != ' ')
               text++;
     }

     if (i < 1)
          return;

     lite_get_textline_text( textline2, &delay );
     usleep( 1000 * strtol( delay, NULL, 10 ) );
     D_FREE( delay );

     argv[i] = NULL;
     execvp( argv[0], argv );

     lite_close_window( lite_find_my_window( LITE_BOX(textline2) ) );
}

int main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteTextLine *textline1, *textline2;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 240; rect.h = 70;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "TextLine Test", &window );

     /* setup the 1st text line */
     rect.x = 10; rect.y = 10; rect.w = 220; rect.h = 20;
     lite_new_textline( LITE_BOX(window), &rect, liteDefaultTextLineTheme, &textline1 );
     lite_set_textline_text( textline1, "Run program..." );

     /* setup the 2nd text line */
     rect.x = 10; rect.y = 40; rect.w = 100; rect.h = 20;
     lite_new_textline( LITE_BOX(window), &rect, liteDefaultTextLineTheme, &textline2 );
     lite_set_textline_text( textline2, "1000" );

     /* install callback */
     lite_on_textline_enter( textline1, on_enter, textline2 );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     window->window->RequestFocus( window->window );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
