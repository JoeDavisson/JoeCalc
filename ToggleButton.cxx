/*
Copyright (c) 2023 Joe Davisson.

This file is part of JoeCalc.

Rendera is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Rendera is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Rendera; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include <string.h>

#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Toggle_Button.H>

#include "ToggleButton.H"

ToggleButton::ToggleButton(int x, int y, int w, int h, const char *label)
: Fl_Toggle_Button(x, y, w, h, label)
{
}

ToggleButton::~ToggleButton()
{
}

void ToggleButton::draw()
{
  int lw, lh;

  if(value())
    fl_draw_box(FL_DOWN_BOX, x(), y(), w(), h(), FL_INACTIVE_COLOR);
  else
    fl_draw_box(FL_UP_BOX, x(), y(), w(), h(), FL_BACKGROUND2_COLOR);

  if(strlen(label()) > 0)
  {
    measure_label(lw, lh);
    if(value())
      draw_label(x() + 1 + (w() - lw) / 2, y() + 1 + (h() - lh) / 2, lw, lh);
    else
      draw_label(x() + (w() - lw) / 2, y() + (h() - lh) / 2, lw, lh);

  }
}

