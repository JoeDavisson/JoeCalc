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
#include <stdint.h>

#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tooltip.H>

#include "Calc.H"
#include "Gui.H"

class Win : public Fl_Double_Window
{
public:
  Win(int w, int h, const char *label)
  : Fl_Double_Window(w, h, label)
  {
  }

  ~Win()
  {
  }
  
  int handle(int event)
  {
    switch(event)
    {
      case FL_FOCUS:
        return 1;
      case FL_KEYDOWN:
        Calc::keypress(Fl::event_key());
        return 1;
      default:
        return Fl_Double_Window::handle(event);
    }
  }
};

namespace
{
  // window
  Win *window;

  // main menu
  Fl_Menu_Bar *menubar;

  // stuff
  Fl_Box *display;
  Fl_Output *binary;
  Fl_Button *key_clear;

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
  Fl_Toggle_Button *key_dec;
  Fl_Toggle_Button *key_hex;
  Fl_Toggle_Button *key_oct;
  Fl_Toggle_Button *key_bin;

  Fl_Group *group_misc;
  Fl_Button *key_sqrt;
  Fl_Button *key_recip;
  Fl_Button *key_int;
  Fl_Button *key_sin;
  Fl_Button *key_pow;
  Fl_Button *key_pi;
  Fl_Button *key_frac;
  Fl_Button *key_cos;

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
      exit(0);
  }

  void about()
  {
    fl_message_title("About");
    fl_message("JoeCalc\nCopyright (c) 2015 Joe Davisson");
  }
}

void Gui::init()
{
  // main window
  window = new Win(496, 376, "JoeCalc");
  window->callback(closeCallback);

  // menu
  menubar = new Fl_Menu_Bar(0, 0, window->w(), 24);
  menubar->box(FL_THIN_UP_BOX);

  menubar->add("&File/&Quit", 0,
    (Fl_Callback *)quit, 0, 0);
  menubar->add("&Help/&About...", 0,
    (Fl_Callback *)about, 0, 0);

  display = new Fl_Box(8, 32, 376, 32, "");
  display->box(FL_DOWN_BOX);
  display->labelsize(18);
  display->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  binary = new Fl_Output(8, 68, 480, 24, "");
  binary->textsize(10);
  binary->box(FL_FLAT_BOX);
  binary->value("");
  binary->color(FL_BACKGROUND_COLOR);
  key_clear = new Fl_Button(400, 32, 80, 32, "Clear");
  key_clear->callback((Fl_Callback *)Calc::key_clear);
  key_clear->tooltip("Clear Output");

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
  key_equals = new Fl_Button(128, 232, 48, 32, "=");
  key_equals->callback((Fl_Callback *)Calc::key_equals);
  key_dot = new Fl_Button(16, 232, 48, 32, ".");
  key_dot->callback((Fl_Callback *)Calc::key_dot);
  group_num->end();

  group_hex = new Fl_Group(8, 280, 176, 88, "");
  group_hex->box(FL_ENGRAVED_FRAME);
  key_a = new Fl_Button(16, 288, 48, 32, "A");
  key_a->callback((Fl_Callback *)Calc::key_a);
  key_b = new Fl_Button(72, 288, 48, 32, "B");
  key_b->callback((Fl_Callback *)Calc::key_b);
  key_c = new Fl_Button(128, 288, 48, 32, "C");
  key_c->callback((Fl_Callback *)Calc::key_c);
  key_d = new Fl_Button(16, 328, 48, 32, "D");
  key_d->callback((Fl_Callback *)Calc::key_d);
  key_e = new Fl_Button(72, 328, 48, 32, "E");
  key_e->callback((Fl_Callback *)Calc::key_e);
  key_f = new Fl_Button(128, 328, 48, 32, "F");
  key_f->callback((Fl_Callback *)Calc::key_f);
  group_hex->end();
  
  group_arith = new Fl_Group(192, 102, 64, 172, "");
  group_arith->box(FL_ENGRAVED_FRAME);
  key_add = new Fl_Button(200, 112, 48, 32, "+");
  key_add->callback((Fl_Callback *)Calc::key_add);
  key_add->tooltip("Add");
  key_sub = new Fl_Button(200, 152, 48, 32, "-");
  key_sub->callback((Fl_Callback *)Calc::key_sub);
  key_sub->tooltip("Subtract");
  key_mul = new Fl_Button(200, 192, 48, 32, "*");
  key_mul->callback((Fl_Callback *)Calc::key_mul);
  key_mul->tooltip("Multiply");
  key_div = new Fl_Button(200, 232, 48, 32, "/");
  key_div->callback((Fl_Callback *)Calc::key_div);
  key_div->tooltip("Divide");
  group_arith->end();

  group_logic = new Fl_Group(264, 102, 120, 172, "");
  group_logic->box(FL_ENGRAVED_FRAME);
  key_sign = new Fl_Button(272, 112, 48, 32, "+/-");
  key_sign->callback((Fl_Callback *)Calc::key_sign);
  key_sign->tooltip("Toggle Sign\n");
  key_invert = new Fl_Button(328, 112, 48, 32, "~");
  key_invert->callback((Fl_Callback *)Calc::key_invert);
  key_invert->tooltip("One's Complement");
  key_and = new Fl_Button(272, 152, 48, 32, "&");
  key_and->callback((Fl_Callback *)Calc::key_and);
  key_and->tooltip("And");
  key_or = new Fl_Button(328, 152, 48, 32, "|");
  key_or->callback((Fl_Callback *)Calc::key_or);
  key_or->tooltip("Or");
  key_xor = new Fl_Button(272, 192, 48, 32, "^");
  key_xor->callback((Fl_Callback *)Calc::key_xor);
  key_xor->tooltip("Exclusive-Or");
  key_mod = new Fl_Button(328, 192, 48, 32, "%");
  key_mod->callback((Fl_Callback *)Calc::key_mod);
  key_mod->tooltip("Modulo");
  key_shl = new Fl_Button(272, 232, 48, 32, "<<");
  key_shl->callback((Fl_Callback *)Calc::key_shl);
  key_shl->tooltip("Shift Left");
  key_shr = new Fl_Button(328, 232, 48, 32, ">>");
  key_shr->callback((Fl_Callback *)Calc::key_shr);
  key_shr->tooltip("Shift Right");
  group_logic->end();

  group_mode = new Fl_Group(392, 102, 96, 172, "");
  group_mode->box(FL_ENGRAVED_FRAME);
  key_dec = new Fl_Toggle_Button(400, 112, 80, 32, "Dec");
  key_dec->callback((Fl_Callback *)Calc::key_dec);
  key_dec->tooltip("Decimal Mode");
  key_dec->down_box(FL_UP_BOX);
  key_hex = new Fl_Toggle_Button(400, 152, 80, 32, "Hex");
  key_hex->callback((Fl_Callback *)Calc::key_hex);
  key_hex->tooltip("Hexadecimal Mode");
  key_hex->down_box(FL_UP_BOX);
  key_oct = new Fl_Toggle_Button(400, 192, 80, 32, "Oct");
  key_oct->callback((Fl_Callback *)Calc::key_oct);
  key_oct->tooltip("Octal Mode");
  key_oct->down_box(FL_UP_BOX);
  key_bin = new Fl_Toggle_Button(400, 232, 80, 32, "Bin");
  key_bin->callback((Fl_Callback *)Calc::key_bin);
  key_bin->tooltip("Binary Mode");
  key_bin->down_box(FL_UP_BOX);
  group_mode->end();

  group_misc = new Fl_Group(192, 280, 296, 88, "");
  group_misc->box(FL_ENGRAVED_FRAME);
  key_sqrt = new Fl_Button(200, 288, 64, 32, "√");
  key_sqrt->callback((Fl_Callback *)Calc::key_sqrt);
  key_sqrt->tooltip("Square Root");
  key_recip = new Fl_Button(272, 288, 64, 32, "1/x");
  key_recip->callback((Fl_Callback *)Calc::key_recip);
  key_recip->tooltip("Reciprocal");
  key_int = new Fl_Button(344, 288, 64, 32, "Int");
  key_int->callback((Fl_Callback *)Calc::key_int);
  key_int->tooltip("Integer Part");
  key_sin = new Fl_Button(416, 288, 64, 32, "Sin");
  key_sin->callback((Fl_Callback *)Calc::key_sin);
  key_sin->tooltip("Sine");
  key_pow = new Fl_Button(200, 328, 64, 32, "xⁿ");
  key_pow->callback((Fl_Callback *)Calc::key_pow);
  key_pow->tooltip("Power");
  key_pi = new Fl_Button(272, 328, 64, 32, "π");
  key_pi->callback((Fl_Callback *)Calc::key_pi);
  key_pi->tooltip("Pi");
  key_frac = new Fl_Button(344, 328, 64, 32, "Frac");
  key_frac->callback((Fl_Callback *)Calc::key_frac);
  key_frac->tooltip("Fractional Part");
  key_cos = new Fl_Button(416, 328, 64, 32, "Cos");
  key_cos->callback((Fl_Callback *)Calc::key_cos);
  key_cos->tooltip("Cosine");
  group_misc->end();

  window->end();
  Fl_Tooltip::enable(1);
  Fl_Tooltip::color(fl_rgb_color(248, 224, 192));
  Fl_Tooltip::textcolor(FL_BLACK);
  
  window->show();

  setMode(Calc::MODE_DEC);
  setBinary(0);
  Calc::key_clear();
}

void Gui::updateDisplay(const char *s)
{
  display->copy_label(s);
}

void Gui::setMode(int mode)
{
  key_dec->value(0);
  key_hex->value(0);
  key_oct->value(0);
  key_bin->value(0);

  key_dec->color(FL_BACKGROUND_COLOR);
  key_hex->color(FL_BACKGROUND_COLOR);
  key_oct->color(FL_BACKGROUND_COLOR);
  key_bin->color(FL_BACKGROUND_COLOR);

  switch(mode)
  {
    case Calc::MODE_DEC:
      key_dec->value(1);
      key_dec->color(FL_BACKGROUND2_COLOR, FL_BACKGROUND2_COLOR);
      break;
    case Calc::MODE_HEX:
      key_hex->value(1);
      key_hex->color(FL_BACKGROUND2_COLOR, FL_BACKGROUND2_COLOR);
      break;
    case Calc::MODE_OCT:
      key_oct->value(1);
      key_oct->color(FL_BACKGROUND2_COLOR, FL_BACKGROUND2_COLOR);
      break;
    case Calc::MODE_BIN:
      key_bin->value(1);
      key_bin->color(FL_BACKGROUND2_COLOR, FL_BACKGROUND2_COLOR);
      break;
  }

  key_dec->redraw();
  key_hex->redraw();
  key_oct->redraw();
  key_bin->redraw();
}

void Gui::setBinary(double value)
{
  uint64_t temp = value;

  binary->value("");

  int count = 0;

  for(int i = 63; i >= 0; i--)
  {
    if(((temp >> i) & 1) == 1)
      binary->insert("1");
    else
      binary->insert("0");

    count++;
    if(count > 7)
    {
      count = 0;
      binary->insert(" ");
    }
  }
}


