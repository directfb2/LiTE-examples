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

#include <lite/animation.h>
#include <lite/lite.h>
#include <lite/textbutton.h>
#include <lite/window.h>

#ifdef USE_IMAGE_HEADERS
#include "tuxsprites.h"
#endif

#define TIMEOUT 200

static int timeout_id;

static DFBResult timeout_cb( void *data )
{
     LiteAnimation *animation = data;

     lite_update_animation( animation );

     lite_remove_timeout_callback( timeout_id );
     lite_enqueue_timeout_callback( TIMEOUT, timeout_cb, animation, &timeout_id );

     return DFB_OK;
}

static void button_stop_start_press( LiteTextButton *buttonStopStart, void *data )
{
     LiteAnimation *animation = data;

     if (lite_animation_running( animation )) {
          lite_stop_animation( animation );
          lite_set_text_button_caption( buttonStopStart, "Start" );
     }
     else {
          lite_start_animation( animation, TIMEOUT );
          lite_set_text_button_caption( buttonStopStart, "Stop" );
     }
}

static void button_exit_press( LiteTextButton *buttonExit, void *data )
{
     LiteWindow *window = data;

     lite_remove_timeout_callback( timeout_id );
     lite_close_window( window );
}

int main( int argc, char *argv[] )
{
     DFBRectangle    rect;
     LiteWindow     *window;
     LiteAnimation  *animation;
     LiteTextButton *buttonStopStart, *buttonExit;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 140; rect.h = 80;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Animation Test", &window );

     /* setup the animation */
     rect.x = 10; rect.y = 10; rect.w = 40; rect.h = 60;
     lite_new_animation( LITE_BOX(window), &rect, liteNoAnimationTheme, &animation );
#ifdef USE_IMAGE_HEADERS
     lite_load_animation_data( animation, tuxsprites_data, sizeof(tuxsprites_data), 0, 40, 60 );
#else
     if (!getenv( "LITE_NO_DFIFF" ))
          lite_load_animation( animation, DATADIR"/tuxsprites.dfiff", 0, 40, 60 );
     else
          lite_load_animation( animation, DATADIR"/tuxsprites.png", 0, 40, 60 );
#endif
     lite_start_animation( animation, TIMEOUT );

     /* setup the button to stop / start the animation sequence */
     rect.x = 80; rect.y = 10; rect.w = 43; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Stop", liteDefaultTextButtonTheme, &buttonStopStart );

     /* setup the button to exit */
     rect.x = 80; rect.y = 48; rect.w = 43; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Exit", liteDefaultTextButtonTheme, &buttonExit );

     /* install callbacks */
     lite_enqueue_timeout_callback( TIMEOUT, timeout_cb, animation, &timeout_id );
     lite_on_text_button_press( buttonStopStart, button_stop_start_press, animation );
     lite_on_text_button_press( buttonExit, button_exit_press, window );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
