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

#ifndef GUI_H
#define GUI_H

class Fl_Box;
class Fl_Menu_Bar;

class Gui
{
public:
  static void init();
  static void updateDisplay(const char *);
  static void setMode(int);
  static void setBinary(double);
  static Fl_Menu_Bar *getMenuBar();

private:
  Gui() { }
  ~Gui() { }
};

#endif

