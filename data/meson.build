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

examplesdata = []

rawdata_names = [
  'D',
  'directfb-logo',
  'tuxsprites'
]

rawdata_hdrs = []

if image_headers == 'disabled'
  foreach name : rawdata_names
    examplesdata += name + '.dfiff'
    examplesdata += name + '.png'
  endforeach
else
  foreach rawdata_name : rawdata_names
    rawdata_hdrs += custom_target(rawdata_name,
                                  input: rawdata_name + '.' + image_headers,
                                  output: rawdata_name + '.h',
                                  capture: true,
                                  command: [directfb_csource, '--raw', '--name=@0@'.format(rawdata_name), '@INPUT@'])
  endforeach
endif

install_data(examplesdata, install_dir: examplesdatadir)
