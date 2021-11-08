/*
Copyright (c) 2021 Joe Davisson.

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
#include <iostream>
//#include <unistd.h>

#include <FL/Fl.H>
#include <FL/fl_ask.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
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
    Fl::set_color(FL_BACKGROUND_COLOR, 64, 64, 64);
    Fl::set_color(FL_BACKGROUND2_COLOR, 48, 48, 48);
    Fl::set_color(FL_FOREGROUND_COLOR, 208, 208, 208);
    Fl::set_color(FL_INACTIVE_COLOR, 56, 56, 56);
    Fl::set_color(FL_SELECTION_COLOR, 208, 208, 208);
  }

  void setLightTheme()
  {
    Fl::set_color(FL_BACKGROUND_COLOR, 192, 192, 192);
    Fl::set_color(FL_BACKGROUND2_COLOR, 172, 172, 172);
    Fl::set_color(FL_FOREGROUND_COLOR, 8, 8, 8);
    Fl::set_color(FL_INACTIVE_COLOR, 172, 172, 172);
    Fl::set_color(FL_SELECTION_COLOR, 64, 64, 64);
  }

  struct _help_type {};

  std::ostream &
  operator << (std::ostream &os, _help_type const &)
  {
    return
      os
      << std::endl << "Usage: joecalc [OPTIONS]"
      << std::endl
      << std::endl << "Options:"
      << std::endl << "  --theme=dark\t\t use dark theme"
      << std::endl << "  --theme=light\t\t use light theme"
      << std::endl << std::endl;
  }
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
              std::cerr
                << "Unknown theme: \"" << optarg << "\"" << std::endl
                << _help_type();
              return EXIT_FAILURE;

          case OPTION_HELP:
            printf("Usage: joecalc [OPTIONS]\n");
            printf("\n");
            printf("Options:\n");
            printf("  --theme=dark\t\t use dark theme\n");
            printf("  --theme=light\t\t use light theme\n");
            break;

          default:
            std::cout << _help_type();
            return EXIT_SUCCESS;
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

