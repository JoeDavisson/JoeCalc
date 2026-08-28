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

#include <string.h>

#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>

#include "Button.H"

Button::Button(int x, int y, int w, int h, const char *label, Fl_Callback *cb)
: Fl_Button(x, y, w, h, label)
{
  if (cb) { callback(cb); }

  bgcolor1 = FL_BACKGROUND2_COLOR;
  bgcolor2 = FL_INACTIVE_COLOR;
}

Button::Button(int x, int y, int w, int h, const char *label,
               int color, Fl_Callback *cb)
: Fl_Button(x, y, w, h, label)
{
  if (cb) { callback(cb); }

  shade(color);
}

Button::~Button()
{
}

void Button::shade(int v)
{
  if (v < 0) { v = 0; }
  if (v > 7) { v = 7; }

  v *= 12;
  v += (256 - (7 * 12)) / 2 + 32;

  bgcolor1 = fl_rgb_color(v, v, v);
  bgcolor2 = fl_rgb_color(v - 8, v - 8, v - 8);
}

void Button::draw()
{
  int lw = 0, lh = 0;

  fl_draw_box(FL_THIN_DOWN_FRAME, x(), y(), w(), h(), bgcolor1);

  if (value())
  {
    fl_draw_box(FL_THIN_DOWN_BOX, x() + 1, y() + 1, w() - 2, h() - 2, bgcolor2);
  }
    else
  {
    fl_draw_box(FL_THIN_UP_BOX, x() + 1, y() + 1, w() - 2, h() - 2, bgcolor1);
  }

  if (strlen(label()) > 0)
  {
    measure_label(lw, lh);

    if (value())
    {
      draw_label(x() + 1 + (w() - lw) / 2, y() + 1 + (h() - lh) / 2, lw, lh);
    }
      else
    {
      draw_label(x() + (w() - lw) / 2, y() + (h() - lh) / 2, lw, lh);
    }
  }
}

