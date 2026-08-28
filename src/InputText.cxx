/*
Copyright (c) 2026 Joe Davisson.

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

#include <cstdio>
#include <cstdlib>

#include <FL/Fl_Input.H>

#include "InputText.H"

InputText::InputText(int x, int y, int w, int h, const char *text)
: Fl_Input(x, y, w, h, 0)
{
  maximum_size(256);
  textsize(16);
  copy_label(text);
}

InputText::~InputText()
{
}

int InputText::handle(int event)
{
  int key;

  if (event == FL_KEYBOARD)
  {
    key = Fl::event_key();

    if (key == FL_Up) { undo(); return 1; }
    else if (key == FL_Down) { redo(); return 1; }
  }

  return Fl_Input::handle(event);
}

