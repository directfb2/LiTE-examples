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
#include <lite/scrollbar.h>
#include <lite/window.h>

#define SCROLLBAR_THICKNESS 16

typedef struct {
     LiteLabel     *label_info;
     LiteLabel     *label_hori_title;
     LiteLabel     *label_hori_info;
     LiteScrollbar *scrollbar_hori;
     LiteLabel     *label_verti_title;
     LiteLabel     *label_verti_info;
     LiteScrollbar *scrollbar_verti;
} UserData;

static int on_window_resize( LiteWindow *window, int width, int height )
{
     DFBRectangle   rect;
     UserData      *user_data = LITE_BOX(window)->user_data;

     rect.w = 240;                                     rect.x = (width - SCROLLBAR_THICKNESS - rect.w) / 2;
     rect.y = (80 + height - SCROLLBAR_THICKNESS) / 2; rect.h = 20;
     LITE_BOX(user_data->label_info)->rect = rect;

     rect.x = 10; rect.h = 13; rect.y = height - rect.h - SCROLLBAR_THICKNESS - 3; rect.w = 125;
     LITE_BOX(user_data->label_hori_title)->rect = rect;

     rect.x += rect.w + 5;
     LITE_BOX(user_data->label_hori_info)->rect = rect;

     rect.x = 0;                           rect.y = height - SCROLLBAR_THICKNESS - 1;
     rect.w = width - SCROLLBAR_THICKNESS; rect.h = SCROLLBAR_THICKNESS;
     LITE_BOX(user_data->scrollbar_hori)->rect = rect;

     rect.w = 125; rect.x = width - rect.w - SCROLLBAR_THICKNESS - 3; rect.y = 10; rect.h = 13;
     LITE_BOX(user_data->label_verti_title)->rect = rect;

     rect.y += rect.h + 5;
     LITE_BOX(user_data->label_verti_info)->rect = rect;

     rect.x = width - SCROLLBAR_THICKNESS - 1; rect.y = 0;
     rect.w = SCROLLBAR_THICKNESS;             rect.h = height - SCROLLBAR_THICKNESS;
     LITE_BOX(user_data->scrollbar_verti)->rect = rect;

     lite_enable_scrollbar( user_data->scrollbar_hori,  width < 600 );
     lite_enable_scrollbar( user_data->scrollbar_verti, height < 400 );

     if (width >= 600 && height >= 400)
          lite_close_window( window );

     return 1;
}

static void scrollbar_update( LiteScrollbar *scrollbar, LiteScrollInfo *info, void *data )
{
     char       text[64];
     LiteLabel *label = data;

     sprintf( text, "(%u,%u,%u),(%d,%d)", info->min, info->page_size, info->max, info->pos, info->track_pos );
     lite_set_label_text( label, text );
}

int main( int argc, char *argv[] )
{
     DFBRectangle    rect;
     LiteWindow     *window;
     LiteLabel      *label_usage;
     LiteLabel      *label_info, *label_hori_title, *label_hori_info, *label_verti_title, *label_verti_info;
     LiteScrollbar  *scrollbar_hori, *scrollbar_verti;
     LiteScrollInfo  info_hori, info_verti;
     UserData        user_data;
     DFBColor        usage_color = { 0xff, 0x55, 0x86, 0xa4 };
     DFBColor        info_color  = { 0xff, 0xab, 0x1b, 0x93 };
     int             width       = 300;
     int             height      = 200;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = width; rect.h = height;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "Scrollbar Test", &window );

     /* setup usage label */
     rect.x = 10; rect.y = 20;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 12, &label_usage );
     lite_set_label_color( label_usage, &usage_color );
     lite_set_label_text( label_usage, "Usage:" );

     /* setup label to disable horizontal scrollbar */
     rect.x = 10; rect.y = 80;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 12, &label_usage );
     lite_set_label_color( label_usage, &usage_color );
     lite_set_label_text( label_usage, "if width > 600, disable horizontal scrollbar" );

     /* setup label to disable vertical scrollbar */
     rect.x = 10; rect.y = 60;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 12, &label_usage );
     lite_set_label_color( label_usage, &usage_color );
     lite_set_label_text( label_usage, "if height > 400, disable vertical scrollbar" );

     /* setup label to exit the application */
     rect.x = 10; rect.y = 100;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 12, &label_usage );
     lite_set_label_color( label_usage, &usage_color );
     lite_set_label_text( label_usage, "if width > 600 and height > 400, exit app" );

     /* setup scroll info label */
     rect.w = 240;                                     rect.x = (width - SCROLLBAR_THICKNESS - rect.w) / 2;
     rect.y = (80 + height - SCROLLBAR_THICKNESS) / 2; rect.h = 20;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 13, &label_info );
     lite_set_label_color( label_info, &info_color );
     lite_set_label_text( label_info, "(min,page_size,max),(pos,track_pos)" );

     /* setup horizontal scrollbar title label */
     rect.x = 10; rect.h = 13; rect.y = height - rect.h - SCROLLBAR_THICKNESS - 3; rect.w = 125;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 13, &label_hori_title );
     lite_set_label_text( label_hori_title, "Horizontal scrollbar" );

     /* setup horizontal scroll info label */
     rect.x += rect.w + 5;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 13, &label_hori_info );
     lite_set_label_color( label_hori_info, &info_color );

     /* setup vertical scrollbar title label */
     rect.w = 125; rect.x = width - rect.w - SCROLLBAR_THICKNESS - 3; rect.y = 10; rect.h = 13;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 13, &label_verti_title );
     lite_set_label_alignment( label_verti_title, LITE_LABEL_RIGHT );
     lite_set_label_text( label_verti_title, "Vertical scrollbar" );

     /* setup vertical scroll info label */
     rect.y += rect.h + 5;
     lite_new_label( LITE_BOX(window), &rect, liteNoLabelTheme, 13, &label_verti_info );
     lite_set_label_alignment( label_verti_info, LITE_LABEL_RIGHT );
     lite_set_label_color( label_verti_info, &info_color );

     /* setup the horizontal scrollbar */
     rect.x = 0;                           rect.y = height - SCROLLBAR_THICKNESS - 1;
     rect.w = width - SCROLLBAR_THICKNESS; rect.h = SCROLLBAR_THICKNESS;
     lite_new_scrollbar( LITE_BOX(window), &rect, false, liteDefaultScrollbarTheme, &scrollbar_hori );
     lite_get_scroll_info( scrollbar_hori, &info_hori );

     /* setup the vertical scrollbar */
     rect.x = width - SCROLLBAR_THICKNESS - 1; rect.y = 0;
     rect.w = SCROLLBAR_THICKNESS;             rect.h = height - SCROLLBAR_THICKNESS;
     lite_new_scrollbar( LITE_BOX(window), &rect, true, liteDefaultScrollbarTheme, &scrollbar_verti );
     info_verti.min       = 30;
     info_verti.max       = 100;
     info_verti.page_size = 10;
     info_verti.line_size = 1;
     info_verti.pos       = 50;
     info_verti.track_pos = -1;
     lite_set_scroll_info( scrollbar_verti, &info_verti );

     /* install callbacks */
     user_data.label_info        = label_info;
     user_data.label_hori_title  = label_hori_title;
     user_data.label_hori_info   = label_hori_info;
     user_data.scrollbar_hori    = scrollbar_hori;
     user_data.label_verti_title = label_verti_title;
     user_data.label_verti_info  = label_verti_info;
     user_data.scrollbar_verti   = scrollbar_verti;
     LITE_BOX(window)->user_data = &user_data;
     window->OnResize = on_window_resize;
     lite_on_scrollbar_update( scrollbar_hori,  scrollbar_update, label_hori_info );
     lite_on_scrollbar_update( scrollbar_verti, scrollbar_update, label_verti_info );

     /* set labels with initial scroll information */
     scrollbar_update( scrollbar_hori,  &info_hori,  label_hori_info );
     scrollbar_update( scrollbar_verti, &info_verti, label_verti_info );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* destroy the window */
     lite_destroy_window( window );

     /* deinitialize */
     lite_close();

     return 0;
}
