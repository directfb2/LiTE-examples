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

project('LiTE-examples', 'c',
        version: '0.9.1')

examplesdatadir = join_paths(get_option('prefix'), get_option('datadir'), 'lite-examples')

image_headers = get_option('image-headers')

add_global_arguments('-DDATADIR="@0@"'.format(examplesdatadir), language: 'c')

lite_dep = dependency('lite')

if image_headers != 'disabled'
  directfb_csource = find_program('directfb-csource')
  add_global_arguments('-DUSE_IMAGE_HEADERS', language: 'c')
endif

subdir('data')
subdir('src')
