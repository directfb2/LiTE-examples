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
#include <lite/list.h>
#include <lite/lite.h>
#include <lite/textbutton.h>
#include <lite/window.h>

static int item_data_max = 0;

static const char *fonts[] = {
     "Serif",
     "Serif Bold",
     "Sansserif",
     "Sansserif Bold",
     "Sansserif Oblique",
     "Sansserif Bold Oblique",
     "Monospaced",
     "Monospaced Bold",
     "Monospaced Oblique",
     "Monospaced Bold Oblique"
};

static int on_window_resize( LiteWindow *window, int width, int height )
{
     DFBRectangle  rect;
     LiteList     *list = LITE_BOX(window)->user_data;

     rect.x = 0; rect.y = 40; rect.w = width; rect.h = height - 40;
     LITE_BOX(list)->rect = rect;

     lite_list_recalc_layout( list );

     return 1;
}

static void button_exit_press( LiteTextButton *buttonExit, void *data )
{
     lite_close_window( data );
}

static void button_add_press( LiteTextButton *buttonAdd, void *data )
{
     int       count;
     LiteList *list = data;

     lite_list_get_item_count( list, &count );

     lite_list_insert_item( list, count, item_data_max++ % (sizeof(fonts) / sizeof(fonts[0])) );

     lite_list_set_selected_item_index( list, count );
}

static void button_del_press( LiteTextButton *buttonDel, void *data )
{
     int       count, index;
     LiteList *list = data;

     lite_list_get_item_count( list, &count );

     lite_list_get_selected_item_index( list, &index );

     lite_list_del_item( list, index );
}

static void button_scrollto_press( LiteTextButton *buttonScrollTo, void *data )
{
     int       index;
     LiteList *list = data;

     lite_list_get_selected_item_index( list, &index );

     lite_list_ensure_visible( list, index );
}

static int compare( const LiteListItemData *item_data1, const LiteListItemData *item_data2 )
{
     return *item_data2 - *item_data1;
}

static void button_sort_press( LiteTextButton *buttonSort, void *data )
{
     int       count;
     LiteList *list = data;

     lite_list_get_item_count( list, &count );

     lite_list_sort_items( list, compare );

     lite_list_set_selected_item_index( list, 0 );

     lite_list_ensure_visible( list, count - 1 );
}

static void check_press( LiteCheck *check, LiteCheckState state, void *data )
{
     LiteList *list = data;

     lite_enable_list( list, state );
}

void list_draw_item( LiteList *list, LiteListDrawItem *draw_item, void *data )
{
     char           text[32];
     char          *spec, *p;
     LiteFont      *item_font;
     IDirectFBFont *font;
     LiteFontStyle  style      = LITE_FONT_PLAIN;
     const u8       colors[12] = {
       0xff,    0,    0, 0xff, /* red */
          0, 0xff,    0, 0xff, /* green */
          0,    0, 0xff, 0xff  /* blue */
     };

     sprintf( text, "%lu - %s", draw_item->item_data, fonts[draw_item->item_data] );

     spec = p = D_STRDUP( strstr( text, " - " ) + 3 );

     spec[0] = spec[0] + 'a' - 'A';

     while (*p) {
          p++;
          if (*p == ' ') {
               *p = 0;
               break;
          }
     }

     if (strstr( text, "Bold" ))
          style |= LITE_FONT_BOLD;

     if (strstr( text, "Oblique" ))
          style |= LITE_FONT_ITALIC;

     lite_get_font( spec, style, 15, DEFAULT_FONT_ATTRIBUTE, &item_font );

     D_FREE( spec );

     lite_font( item_font, &font );

     draw_item->surface->SetFont( draw_item->surface, font );

     draw_item->surface->SetColor( draw_item->surface,
                                   colors[(draw_item->item_data%3)*4],
                                   colors[(draw_item->item_data%3)*4+1],
                                   colors[(draw_item->item_data%3)*4+2],
                                   colors[(draw_item->item_data%3)*4+3] );

     draw_item->surface->FillRectangle( draw_item->surface,
                                        draw_item->rc_item.x, draw_item->rc_item.y,
                                        draw_item->rc_item.w, draw_item->rc_item.h );

     if (draw_item->disabled)
          draw_item->surface->SetColor( draw_item->surface, 0x64, 0x64, 0x64, 0xff );
     else
          draw_item->surface->SetColor( draw_item->surface, 0, 0, 0, 0xff );

     draw_item->surface->DrawString( draw_item->surface, text, strlen( text ),
                                     draw_item->rc_item.x + 2, draw_item->rc_item.y + 2, DSTF_LEFT|DSTF_TOP );

     if (draw_item->selected) {
          draw_item->surface->SetColor( draw_item->surface, 0, 0, 0, 0xff);

          draw_item->surface->DrawRectangle( draw_item->surface,
                                             draw_item->rc_item.x + 1, draw_item->rc_item.y + 1,
                                             draw_item->rc_item.w - 2, draw_item->rc_item.h - 2 );
     }
}

int main( int argc, char *argv[] )
{
     DFBRectangle    rect;
     LiteWindow     *window;
     LiteTextButton *buttonExit, *buttonAdd, *buttonDel, *buttonScrollTo, *buttonSort;
     LiteCheck      *check;
     LiteList       *list;

     /* initialize */
     if (lite_open( &argc, &argv ))
          return 1;

     /* create a window */
     rect.x = LITE_CENTER_HORIZONTALLY; rect.y = LITE_CENTER_VERTICALLY; rect.w = 350; rect.h = 400;
     lite_new_window( NULL, &rect, DWCAPS_ALPHACHANNEL, liteDefaultWindowTheme, "List Test", &window );

     /* setup the button to exit */
     rect.x = 10; rect.y = 10; rect.w = 45; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Exit", liteDefaultTextButtonTheme, &buttonExit );

     /* setup the button to add an item */
     rect.x = 60; rect.y = 10; rect.w = 45; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Add", liteDefaultTextButtonTheme, &buttonAdd );

     /* setup the button to delete an item */
     rect.x = 110; rect.y = 10; rect.w = 45; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Del", liteDefaultTextButtonTheme, &buttonDel );

     /* setup the button to scroll to the currently selected item */
     rect.x = 160; rect.y = 10; rect.w = 60; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "ScrollTo", liteDefaultTextButtonTheme, &buttonScrollTo );

     /* setup the button to sort items */
     rect.x = 225; rect.y = 10; rect.w = 45; rect.h = 22;
     lite_new_text_button( LITE_BOX(window), &rect, "Sort", liteDefaultTextButtonTheme, &buttonSort );

     /* setup the check box to enable or disable the list */
     rect.x = 275; rect.y = 10; rect.w = 70; rect.h = 22;
     lite_new_check( LITE_BOX(window), &rect, "Enabled", liteDefaultCheckTheme, &check );
     lite_check_check( check, LITE_CHS_CHECKED );

     /* setup the list */
     rect.x = 0; rect.y = 40; rect.w = 350; rect.h = 360;
     lite_new_list( LITE_BOX(window), &rect, liteDefaultListTheme, &list );
     lite_list_set_row_height( list, 50 );

     /* install callbacks */
     LITE_BOX(window)->user_data = list;
     window->OnResize = on_window_resize;
     lite_on_text_button_press( buttonExit, button_exit_press, window );
     lite_on_text_button_press( buttonAdd, button_add_press, list );
     lite_on_text_button_press( buttonDel, button_del_press, list );
     lite_on_text_button_press( buttonScrollTo, button_scrollto_press, list );
     lite_on_text_button_press( buttonSort, button_sort_press, list );
     lite_on_check_press( check, check_press, list );
     lite_list_on_draw_item( list, list_draw_item, NULL );

     /* initialize the list with a first item */
     button_add_press( buttonAdd, list );

     /* show the window */
     lite_set_window_opacity( window, liteFullWindowOpacity );

     /* run the window event loop */
     lite_window_event_loop( window, 0 );

     /* deinitialize */
     lite_close();

     return 0;
}
