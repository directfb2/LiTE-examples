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
#include <lite/slider.h>
#include <lite/window.h>

static u8 color[4] = { 0xf0, 0xc0, 0xc0, 0xc0 };

static int on_window_resize( LiteWindow *window, int width, int height )
{
     if (width > 80) {
          int          i;
          LiteSlider **sliders = LITE_BOX(window)->user_data;

          for (i = 0; i < 4; i++)
               LITE_BOX(sliders[i])->rect.w = width - 80;
     }

     return 0;
}

static void slider_update( LiteSlider *slider, float pos, void *data )
{
     int i = (long) data;

     color[i] = 255 * pos;

     if (color[0]) {
          DFBColor bg_color = { color[0], color[1], color[2], color[3] };

          lite_set_window_background( lite_find_my_window( LITE_BOX(slider) ), &bg_color );
     }
     else
          lite_close_window( lite_find_my_window( LITE_BOX(slider) ) );
}

int main( int argc, char *argv[] )
{
     DFBRectangle  rect;
     LiteWindow   *window;
     LiteLabel    *labels[4];
     LiteSlider   *sliders[4];
     int           i;
     DFBColor      bg_color;
     const char   *channels[4] = { "Alpha", "Red", "Green", "Blue" };

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 280; rect.h = 115;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Slider Test", &window );

     /* fill background */
     bg_color.a = color[0]; bg_color.r = color[1]; bg_color.g = color[2]; bg_color.b = color[3];
     lite_set_window_background( window, &bg_color );

     /* setup labels */
     for (i = 0; i < 4; i++) {
          rect.x = 10; rect.y = 10 + i * 25; rect.w = 55;
          lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 18, &labels[i] );
          lite_set_label_text( labels[i], channels[i] );
     }

     /* setup sliders */
     for (i = 0; i < 4; i++) {
          rect.x = 70; rect.y = 10 + i * 25; rect.w = 200; rect.h = 20;
          lite_new_slider( LITE_BOX(window), &rect, liteDefaultSliderTheme, &sliders[i] );
          lite_set_slider_pos( sliders[i], color[i] / 255.0f );
     }

     /* install callbacks */
     LITE_BOX(window)->user_data = sliders;
     window->OnResize = on_window_resize;
     for (i = 0; i < 4; i++)
          lite_on_slider_update( sliders[i], slider_update, (void*)(long) i );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
