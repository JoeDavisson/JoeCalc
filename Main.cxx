/*
Copyright (c) 2015 Joe Davisson.

This file is part of JoeCalc.

JoeCalc is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

JoeCalc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with JoeCalc; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include <getopt.h>
#include <unistd.h>

#include <Fl/Fl.H>
#include <Fl/fl_ask.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  enum
  {
    OPTION_COLOR,
    OPTION_HELP
  };

  int verbose_flag;

  struct option long_options[] =
  {
    { "color",   required_argument, &verbose_flag, OPTION_COLOR },
    { "help",    no_argument,       &verbose_flag, OPTION_HELP  },
    { 0, 0, 0, 0 }
  };
}

int main(int argc, char *argv[])
{
  int color = 0xD0D0D0;

  // parse command line
  int option_index = 0;

  while(true)
  {
    const int c = getopt_long(argc, argv, "", long_options, &option_index);
    if(c < 0)
      break;

    switch(c)
    {
      case 0:
      {
        switch(option_index)
        {
          case OPTION_COLOR:
            color = (double)strtol(optarg, 0, 16);
            break;
          case OPTION_HELP:
            printf("Usage: joecalc [OPTIONS]\n");
            printf("\n");
            printf("Options:\n");
            printf("  --color=FFFFFF (rgb hex format):\n");
            break;
        }
      }
    }
  }

  int r = color & 0xFF;
  int g = (color >> 8) & 0xFF;
  int b = (color >> 16) & 0xFF;

  int sr = r - 144;
  int sg = g - 144;
  int sb = b - 144;
  sr = sr < 0 ? 0 : sr;
  sg = sg < 0 ? 0 : sg;
  sb = sb < 0 ? 0 : sb;

  int b2r = r + 16;
  int b2g = g + 16;
  int b2b = b + 16;
  b2r = b2r > 255 ? 255 : b2r;
  b2g = b2g > 255 ? 255 : b2g;
  b2b = b2b > 255 ? 255 : b2b;

  int ir = r - 80;
  int ig = g - 80;
  int ib = b - 80;
  ir = ir < 0 ? 0 : ir;
  ig = ig < 0 ? 0 : ig;
  ib = ib < 0 ? 0 : ib;

  int fg = 0;
  if((r + g + b) / 3 < 128)
    fg = 255; 

  Fl::set_color(FL_BACKGROUND_COLOR, r, g, b);
  Fl::set_color(FL_BACKGROUND2_COLOR, b2r, b2g, b2b);
  Fl::set_color(FL_FOREGROUND_COLOR, fg, fg, fg);
  Fl::set_color(FL_INACTIVE_COLOR, ir, ig, ib);
  Fl::set_color(FL_SELECTION_COLOR, sr, sg, sb);

  Fl::visual(FL_DOUBLE | FL_RGB);
  Fl::scheme("gtk+");
  fl_message_hotspot(0);
  Fl::visible_focus(0);

  Gui::init();

  int ret = Fl::run();
  return ret;
}

