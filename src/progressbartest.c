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
#include <lite/progressbar.h>
#include <lite/window.h>

static int timeout_id;

DFBResult timeout( void *data )
{
     float            value;
     LiteProgressBar *progressbar = data;

     lite_get_progressbar_value( progressbar, &value );

     if (value == 1.0f) {
          lite_remove_timeout_callback( timeout_id );
          lite_close_window( lite_find_my_window( LITE_BOX(progressbar) ) );
     }
     else {
          value += 0.01f;
          lite_set_progressbar_value( progressbar, value );

          lite_remove_timeout_callback( timeout_id );
          lite_enqueue_timeout_callback( 50, timeout, progressbar, &timeout_id );
     }

     return DFB_OK;
}

int main( int argc, char *argv[] )
{
     DFBRectangle     rect;
     LiteWindow      *window;
     LiteProgressBar *progressbar;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 240; rect.h = 60;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "ProgressBar Test", &window );

     /* setup the progress bar */
     rect.x = 20; rect.y = 20; rect.w = 200; rect.h = 20;
     lite_new_progressbar( LITE_BOX(window), &rect, liteDefaultProgressBarTheme, &progressbar );

     /* install callback */
     lite_enqueue_timeout_callback( 50, timeout, progressbar, &timeout_id );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
