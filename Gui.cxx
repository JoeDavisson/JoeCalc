/*
Copyright (c) 2015 Joe Davisson.

This file is part of JoeCalc.

JoeCalc is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

JoeCalc is distributed in the hope that it will be useful,
state WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with JoeCalc; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include <cmath>

#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tooltip.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  // window
  Fl_Double_Window *window;

  // main menu
  Fl_Menu_Bar *menubar;

  // stuff
  Fl_Float_Input *input;
  Fl_Output *binary;

  Fl_Group *group_num;
  Fl_Button *key_0;
  Fl_Button *key_1;
  Fl_Button *key_2;
  Fl_Button *key_3;
  Fl_Button *key_4;
  Fl_Button *key_5;
  Fl_Button *key_6;
  Fl_Button *key_7;
  Fl_Button *key_8;
  Fl_Button *key_9;
  Fl_Button *key_equals;
  Fl_Button *key_dot;

  Fl_Group *group_hex;
  Fl_Button *key_a;
  Fl_Button *key_b;
  Fl_Button *key_c;
  Fl_Button *key_d;
  Fl_Button *key_e;
  Fl_Button *key_f;

  Fl_Group *group_arith;
  Fl_Button *key_add;
  Fl_Button *key_sub;
  Fl_Button *key_mul;
  Fl_Button *key_div;

  Fl_Group *group_logic;
  Fl_Button *key_sign;
  Fl_Button *key_invert;
  Fl_Button *key_and;
  Fl_Button *key_or;
  Fl_Button *key_xor;
  Fl_Button *key_mod;
  Fl_Button *key_shl;
  Fl_Button *key_shr;

  Fl_Group *group_mode;
  Fl_Button *key_dec;
  Fl_Button *key_hex;
  Fl_Button *key_oct;
  Fl_Button *key_bin;

  Fl_Group *group_misc;
  Fl_Button *key_sqrt;
  Fl_Button *key_recip;
  Fl_Button *key_int;
  Fl_Button *key_ceil;
  Fl_Button *key_pow;
  Fl_Button *key_twos;
  Fl_Button *key_frac;
  Fl_Button *key_floor;

  // prevent escape from closing main window
  void closeCallback(Fl_Widget *widget, void *)
  {
    if((Fl::event() == FL_KEYDOWN || Fl::event() == FL_SHORTCUT)
       && Fl::event_key() == FL_Escape)
    {
        return;
    }
    else
    {
      widget->hide();
    }
  }

  // quit program
  void quit()
  {
//    fl_message_title("Quit");
//    if(fl_choice("Are You Sure?", "No", "Yes", NULL) == 1)
      exit(0);
  }
}

void Gui::init()
{
  // main window
  window = new Fl_Double_Window(496, 376, "JoeCalc");
  window->callback(closeCallback);

  // menu
  menubar = new Fl_Menu_Bar(0, 0, window->w(), 24);
  menubar->box(FL_THIN_UP_BOX);

  menubar->add("&File/&Quit", 0,
    (Fl_Callback *)quit, 0, 0);
  menubar->add("&Help/&About...", 0,
    (Fl_Callback *)0, 0, 0);

  input = new Fl_Float_Input(8, 32, 480, 32, "");
  input->textsize(18);
  input->value("0");
  binary = new Fl_Output(8, 68, 480, 24, "");
  binary->textsize(11);
  binary->box(FL_NO_BOX);
  binary->value("00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000");

  group_num = new Fl_Group(8, 102, 176, 172, "");
  group_num->box(FL_ENGRAVED_FRAME);
  key_0 = new Fl_Button(72, 232, 48, 32, "0");
  key_0->callback((Fl_Callback *)Calc::key_0);
  key_1 = new Fl_Button(16, 192, 48, 32, "1");
  key_1->callback((Fl_Callback *)Calc::key_1);
  key_2 = new Fl_Button(72, 192, 48, 32, "2");
  key_2->callback((Fl_Callback *)Calc::key_2);
  key_3 = new Fl_Button(128, 192, 48, 32, "3");
  key_3->callback((Fl_Callback *)Calc::key_3);
  key_4 = new Fl_Button(16, 152, 48, 32, "4");
  key_4->callback((Fl_Callback *)Calc::key_4);
  key_5 = new Fl_Button(72, 152, 48, 32, "5");
  key_5->callback((Fl_Callback *)Calc::key_5);
  key_6 = new Fl_Button(128, 152, 48, 32, "6");
  key_6->callback((Fl_Callback *)Calc::key_6);
  key_7 = new Fl_Button(16, 112, 48, 32, "7");
  key_7->callback((Fl_Callback *)Calc::key_7);
  key_8 = new Fl_Button(72, 112, 48, 32, "8");
  key_8->callback((Fl_Callback *)Calc::key_8);
  key_9 = new Fl_Button(128, 112, 48, 32, "9");
  key_9->callback((Fl_Callback *)Calc::key_9);
  key_equals = new Fl_Button(16, 232, 48, 32, "=");
  key_equals->callback((Fl_Callback *)Calc::key_equals);
  key_dot = new Fl_Button(128, 232, 48, 32, ".");
  key_dot->callback((Fl_Callback *)Calc::key_dot);
  group_num->end();

  group_hex = new Fl_Group(8, 280, 176, 88, "");
  group_hex->box(FL_ENGRAVED_FRAME);
  key_a = new Fl_Button(16, 288, 48, 32, "A");
  key_b = new Fl_Button(72, 288, 48, 32, "B");
  key_c = new Fl_Button(128, 288, 48, 32, "C");
  key_d = new Fl_Button(16, 328, 48, 32, "D");
  key_e = new Fl_Button(72, 328, 48, 32, "E");
  key_f = new Fl_Button(128, 328, 48, 32, "F");
  group_hex->end();
  
  group_arith = new Fl_Group(192, 102, 64, 172, "");
  group_arith->box(FL_ENGRAVED_FRAME);
  key_add = new Fl_Button(200, 112, 48, 32, "+");
  key_sub = new Fl_Button(200, 152, 48, 32, "-");
  key_mul = new Fl_Button(200, 192, 48, 32, "*");
  key_div = new Fl_Button(200, 232, 48, 32, "/");
  group_arith->end();

  group_logic = new Fl_Group(264, 102, 120, 172, "");
  group_logic->box(FL_ENGRAVED_FRAME);
  key_sign = new Fl_Button(272, 112, 48, 32, "+/-");
  key_invert = new Fl_Button(328, 112, 48, 32, "~");
  key_and = new Fl_Button(272, 152, 48, 32, "&");
  key_or = new Fl_Button(328, 152, 48, 32, "|");
  key_xor = new Fl_Button(272, 192, 48, 32, "^");
  key_mod = new Fl_Button(328, 192, 48, 32, "%");
  key_shl = new Fl_Button(272, 232, 48, 32, "<<");
  key_shr = new Fl_Button(328, 232, 48, 32, ">>");
  group_logic->end();

  group_mode = new Fl_Group(392, 102, 96, 172, "");
  group_mode->box(FL_ENGRAVED_FRAME);
  key_dec = new Fl_Button(400, 112, 80, 32, "Dec");
  key_hex = new Fl_Button(400, 152, 80, 32, "Hex");
  key_oct = new Fl_Button(400, 192, 80, 32, "Oct");
  key_bin = new Fl_Button(400, 232, 80, 32, "Bin");
  group_mode->end();

  group_misc = new Fl_Group(192, 280, 296, 88, "");
  group_misc->box(FL_ENGRAVED_FRAME);
  key_sqrt = new Fl_Button(200, 288, 64, 32, "√");
  key_recip = new Fl_Button(272, 288, 64, 32, "1/x");
  key_int = new Fl_Button(344, 288, 64, 32, "Int");
  key_ceil = new Fl_Button(416, 288, 64, 32, "Ceil");
  key_pow = new Fl_Button(200, 328, 64, 32, "xⁿ");
  key_twos = new Fl_Button(272, 328, 64, 32, "2's");
  key_frac = new Fl_Button(344, 328, 64, 32, "Frac");
  key_floor = new Fl_Button(416, 328, 64, 32, "Floor");
  group_misc->end();

//  window->size_range(496, 376, 0, 0, 0, 0, 0);
//  window->resizable(view);
  window->end();
  window->show();
}

Fl_Float_Input *Gui::getInput()
{
  return input;
}

