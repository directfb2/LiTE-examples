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

#include <lite/image.h>
#include <lite/label.h>
#include <lite/lite.h>
#include <lite/slider.h>
#include <lite/window.h>

#ifdef USE_IMAGE_HEADERS
#include "directfb-logo.h"
#endif

/* macro to be used after the lite_main() function */
#ifdef LITE_MAIN_ENTRYPOINT
#define LITE_MAIN()
#else
#define LITE_MAIN() int main( int argc, char *argv[] ) { return lite_main( argc, argv ); }
#endif

static int clip[4] = { 10, 130, 300, 60 };

static void slider_update( LiteSlider *slider, float pos, void *data )
{
     int         width, height;
     int         i      = (long) data;
     LiteImage  *image  = LITE_BOX(slider)->user_data;
     LiteWindow *window = lite_find_my_window( LITE_BOX(image) );

     lite_get_image_size( image, &width, &height );

     clip[i] = (i % 2 ? height : width) * pos;

     if (clip[2] != 0 && clip[3] != 0) {
          DFBRectangle rect = { clip[0], clip[1],
                                clip[0] + clip[2] <= width  ? clip[2] : width  - clip[0],
                                clip[1] + clip[3] <= height ? clip[3] : height - clip[1] };

          lite_set_image_clipping( image, &rect );
     }
     else
          lite_close_window( window );
}

int lite_main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteImage    *image;
     LiteLabel    *label_usage;
     LiteLabel    *labels[4];
     LiteSlider   *sliders[4];
     int           width, height;
     int           i;
     const char   *channels[4] = { "x", "y", "w", "h" };

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 300; rect.h = 200;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Image Test", &window );

     /* setup the image */
     rect.x = 0; rect.y = 0; rect.w = clip[2]; rect.h = clip[3];
     lite_new_image( LITE_BOX(window), &rect, liteNoImageTheme, &image );
#ifdef USE_IMAGE_HEADERS
     lite_load_image( image, directfb_logo_data, sizeof(directfb_logo_data) );
#else
     if (!getenv( "LITE_NO_DFIFF" ))
          lite_load_image( image, DATADIR"/directfb-logo.dfiff", 0 );
     else
          lite_load_image( image, DATADIR"/directfb-logo.png", 0 );
#endif
     lite_get_image_size( image, &width, &height );

     /* set the image clipping area. */
     rect.x = clip[0]; rect.y = clip[1]; rect.w = clip[2]; rect.h = clip[3];
     lite_set_image_clipping( image, &rect );

     /* setup usage label */
     rect.x = 10; rect.y = 70; rect.h = 25;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 16, &label_usage );
     lite_set_label_text( label_usage, "Set clipping area, exit if w=0 or h=0" );

     /* setup labels */
     for (i = 0; i < 4; i++) {
          rect.x = 10; rect.y = 100 + i * 25; rect.w = 15;
          lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 18, &labels[i] );
          lite_set_label_text( labels[i], channels[i] );
     }

     /* setup sliders */
     for (i = 0; i < 4; i++) {
          rect.x = 30; rect.y = 100 + i * 25; rect.w = 260; rect.h = 20;
          lite_new_slider( LITE_BOX(window), &rect, liteDefaultSliderTheme, &sliders[i] );
          lite_set_slider_pos( sliders[i], (float) clip[i] / (i % 2 ? height : width) );
     }

     /* install callback */
     for (i = 0; i < 4; i++) {
          LITE_BOX(sliders[i])->user_data = image;
          lite_on_slider_update( sliders[i], slider_update, (void*)(long) i );
     }

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}

LITE_MAIN()
