/*
Copyright (c) 2023 Joe Davisson.

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

#include <FL/Fl.H>
#include <FL/fl_ask.H>

#include "Calc.H"
#include "Gui.H"

enum
{
  OPTION_THEME,
  OPTION_HELP
};

int verbose_flag;

struct option long_options[] =
{
  { "theme",   required_argument, &verbose_flag, OPTION_THEME },
  { "help",    no_argument,       &verbose_flag, OPTION_HELP  },
  { 0, 0, 0, 0 }
};

void setDarkTheme()
{
  // 32 - 55
  for(int i = 0; i < 24; i++)
  { 
    int v = i * 4;
    Fl::set_color(8 + i, fl_rgb_color(v, v, v));
  }
  
  Fl::set_color(FL_BACKGROUND_COLOR, 56, 56, 56);
  Fl::set_color(FL_BACKGROUND2_COLOR, 48, 48, 48);
  Fl::set_color(FL_FOREGROUND_COLOR, 192, 192, 192);
  Fl::set_color(FL_INACTIVE_COLOR, 64, 64, 64);
  Fl::set_color(FL_SELECTION_COLOR, 192, 192, 192);
}

void setLightTheme()
{
  Fl::set_color(FL_BACKGROUND_COLOR, 192, 192, 192);
  Fl::set_color(FL_BACKGROUND2_COLOR, 172, 172, 172);
  Fl::set_color(FL_FOREGROUND_COLOR, 8, 8, 8);
  Fl::set_color(FL_INACTIVE_COLOR, 160, 160, 160);
  Fl::set_color(FL_SELECTION_COLOR, 64, 64, 64);
}

void printHelp()
{
  printf("Usage: joecalc [OPTIONS] filename\n\n");
  printf("--theme=dark\t\t use dark theme\n");
  printf("--theme=light\t\t use light theme\n\n");
}

int main(int argc, char *argv[])
{
  setLightTheme();

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
          case OPTION_THEME:
            if(strcmp(optarg, "dark") == 0)
              {
                setDarkTheme();
                break;
              }
              if(strcmp(optarg, "light") == 0)
              {
                setLightTheme();
                break;
              }
              printf("Unknown theme: \"%s\"\n\n", optarg);
              return 0;

          case OPTION_HELP:
            printHelp();
            return 0;

          default:
            printHelp();
            return 0;
        }
      }
    }
  }

  Fl::visual(FL_DOUBLE | FL_RGB);
  Fl::scheme("gtk+");
  fl_message_hotspot(0);
  Fl::visible_focus(0);

  Gui::init();

  int ret = Fl::run();
  return ret;
}

