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

#include <unistd.h>

#include <Fl/Fl.H>
#include <Fl/fl_ask.H>

#include "Calc.H"
#include "Gui.H"

int main(int argc, char *argv[])
{
  Fl::visual(FL_DOUBLE | FL_RGB);
  Fl::scheme("gtk+");
  fl_message_hotspot(0);
  Fl::visible_focus(0);

  Gui::init();

  int ret = Fl::run();
  return ret;
}

