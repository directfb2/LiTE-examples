#  This file is part of LiTE-examples.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.

include $(APPDIR)/Make.defs

PRIORITY  = SCHED_PRIORITY_DEFAULT
STACKSIZE = 16384
MODULE    = $(CONFIG_EXAMPLES_LITE)

CFLAGS += -Idata
CFLAGS += -DUSE_IMAGE_HEADERS

ifeq ($(CONFIG_LITE_ANIMATION),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_animation
else
PROGNAME = lite
endif
MAINSRC = src/animationtest.c
endif
ifeq ($(CONFIG_LITE_BUTTON),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_button
else
PROGNAME = lite
endif
MAINSRC = src/buttontest.c
endif
ifeq ($(CONFIG_LITE_CHECK),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_check
else
PROGNAME = lite
endif
MAINSRC = src/checktest.c
endif
ifeq ($(CONFIG_LITE_IMAGE),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_image
else
PROGNAME = lite
endif
MAINSRC = src/imagetest.c
endif
ifeq ($(CONFIG_LITE_LABEL),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_label
else
PROGNAME = lite
endif
MAINSRC = src/labeltest.c
endif
ifeq ($(CONFIG_LITE_LIST),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_list
else
PROGNAME = lite
endif
MAINSRC = src/listtest.c
endif
ifeq ($(CONFIG_LITE_PROGRESSBAR),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_progressbar
else
PROGNAME = lite
endif
MAINSRC = src/progressbartest.c
endif
ifeq ($(CONFIG_LITE_SCROLLBAR),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_scrollbar
else
PROGNAME = lite
endif
MAINSRC = src/scrollbartest.c
endif
ifeq ($(CONFIG_LITE_SLIDER),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_slider
else
PROGNAME = lite
endif
MAINSRC = src/slidertest.c
endif
ifeq ($(CONFIG_LITE_TEXTBUTTON),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_textbutton
else
PROGNAME = lite
endif
MAINSRC = src/textbuttontest.c
endif
ifeq ($(CONFIG_LITE_TEXTLINE),y)
ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
PROGNAME = lite_textline
else
PROGNAME = lite
endif
MAINSRC = src/textlinetest.c
endif

RAWDATA_HDRS  = data/D.h
RAWDATA_HDRS += data/directfb-logo.h
RAWDATA_HDRS += data/tuxsprites.h

DIRECTFB_CSOURCE ?= directfb-csource

data/%.h: data/%.$(shell echo $(CONFIG_LITE_IMAGE_EXTENSION))
	$(DIRECTFB_CSOURCE) --raw $^ --name=$* > $@

src/animationtest.c: data/tuxsprites.h
src/buttontest.c: data/D.h
src/imagetest.c: data/directfb-logo.h

context:: $(RAWDATA_HDRS)

distclean::
	$(call DELFILE, $(RAWDATA_HDRS))

include $(APPDIR)/Application.mk
