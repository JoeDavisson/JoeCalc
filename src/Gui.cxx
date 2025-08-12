/*
Copyright (c) 2025 Joe Davisson.

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
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tooltip.H>

#include "Button.H"
#include "Calc.H"
#include "Gui.H"
#include "ToggleButton.H"
#include "../icons/joecalc64x64.xpm"

class MainWin;
class Button;
class ToggleButton;

namespace
{
  // window
  MainWin *window;
  Fl_Pixmap *icon;

  // main menu
  Fl_Menu_Bar *menubar;

  // widgets
  Fl_Box *display;
  Fl_Box *binary;
  Fl_Box *hex;
  Button *key_clear;

  Fl_Group *group_num;
  Button *key_0;
  Button *key_1;
  Button *key_2;
  Button *key_3;
  Button *key_4;
  Button *key_5;
  Button *key_6;
  Button *key_7;
  Button *key_8;
  Button *key_9;
  Button *key_equals;
  Button *key_dot;

  Fl_Group *group_hex;
  Button *key_a;
  Button *key_b;
  Button *key_c;
  Button *key_d;
  Button *key_e;
  Button *key_f;

  Fl_Group *group_arith;
  Button *key_add;
  Button *key_sub;
  Button *key_mul;
  Button *key_div;

  Fl_Group *group_logic;
  Button *key_sign;
  Button *key_invert;
  Button *key_and;
  Button *key_or;
  Button *key_xor;
  Button *key_mod;
  Button *key_shl;
  Button *key_shr;

  Fl_Group *group_mode;
  ToggleButton *key_dec;
  ToggleButton *key_hex;
  ToggleButton *key_oct;
  ToggleButton *key_bin;

  Fl_Group *group_misc;
  Button *key_sqrt;
  Button *key_recip;
  Button *key_int;
  Button *key_incr;
  Button *key_pow;
  Button *key_pi;
  Button *key_frac;
  Button *key_decr;

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
}

class MainWin : public Fl_Double_Window
{
public:
  MainWin(int w, int h, const char *label)
  : Fl_Double_Window(w, h, label)
  {
  }

  ~MainWin()
  {
  }
  
  int handle(int event)
  {
    int ret = 0;

    switch(event)
    {
      case FL_FOCUS:
        return 1;
      case FL_UNFOCUS:
        return 1;
      case FL_KEYBOARD:
        // give focus to the main menu
        if(Fl::event_alt() > 0)
        {
          Gui::getMenuBar()->take_focus();
          return 0;
        }

        ret = Calc::keypress(Fl::event_key(),
                             Fl::event_shift() ? true : false,
                             Fl::event_ctrl() ? true : false);

        // pass ctrl +/-/0 to allow DPI scaling
        if (ret == -1)
          return Fl_Double_Window::handle(event);
        else
          return 1;
      default:
        return Fl_Double_Window::handle(event);
    }
  }
};

namespace About
{
  namespace Items
  {
    Fl_Double_Window *dialog;
    Button *close;
    Fl_Box *title;
    Fl_Box *copyright;
    Fl_Box *info;
    Fl_Box *icon_box;
  }

  void show()
  {
    Items::dialog->show();
  }

  void hide()
  {
    Items::dialog->hide();
  }

  void init()
  {
    const char *credits = "JoeCalc is based in part on the work\nof the FLTK project (http://www.fltk.org).";

    Items::dialog = new Fl_Double_Window(344, 160, "About");
    Items::dialog->set_modal();
    Items::close = new Button(124, 112, 96, 32, "Ok", (Fl_Callback *)hide);
    Items::title = new Fl_Box(FL_NO_BOX, 80, 8, 256, 32, PACKAGE_STRING);
    Items::title->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    Items::title->labelsize(24);
    Items::title->labelfont(FL_HELVETICA_BOLD);
    Items::copyright = new Fl_Box(FL_NO_BOX, 80, 40, 256, 32, "Copyright (c) 2025 Joe Davisson");
    Items::copyright->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    Items::info = new Fl_Box(FL_NO_BOX, 80, 64, 256, 32, credits);
    Items::info->align(FL_ALIGN_LEFT | FL_ALIGN_BOTTOM | FL_ALIGN_INSIDE);
    Items::info->labelsize(12);
    Items::icon_box = new Fl_Box(FL_NO_BOX, 8, 8, 64, 64, "");
    Items::icon_box->labeltype(FL_NO_LABEL);
    Items::icon_box->image(icon);
    Items::icon_box->align(FL_ALIGN_CENTER | FL_ALIGN_IMAGE_BACKDROP);
    Items::dialog->end();
  }
}

void Gui::init()
{
  fl_register_images();

  // main window
//  window = new MainWin(496, 424, "JoeCalc");
  window = new MainWin(496, 376, "JoeCalc");
  window->callback(closeCallback);
  window->xclass("JoeCalc");
  icon = new Fl_Pixmap((char * const *)joecalc64x64_xpm);

  // menu
  menubar = new Fl_Menu_Bar(0, 0, window->w(), 24);
  menubar->box(FL_THIN_UP_BOX);
  menubar->color(FL_INACTIVE_COLOR);

  menubar->add("&File/E&xit", 0,
    (Fl_Callback *)quit, 0, 0);
  menubar->add("&Edit/C&opy", 0,
    (Fl_Callback *)Calc::copyToClipboard, 0, 0);
//  menubar->add("&Edit/P&aste", 0,
//    (Fl_Callback *)Calc::pasteFromClipboard, 0, 0);
  menubar->add("&Help/&About...", 0,
    (Fl_Callback *)About::show, 0, 0);

  display = new Fl_Box(8, 32, 376, 32, "");
  display->box(FL_DOWN_BOX);
  display->labelsize(18);
  display->labelfont(FL_COURIER);
  display->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
  display->color(FL_BACKGROUND2_COLOR);
  display->set_visible_focus();
  binary = new Fl_Box(8, 72, 480, 12, "");
  binary->box(FL_FLAT_BOX);
  binary->labelsize(10);
  binary->labelfont(FL_COURIER);
  binary->align(FL_ALIGN_CENTER/* | FL_ALIGN_INSIDE*/);
  binary->color(FL_BACKGROUND_COLOR);
  hex = new Fl_Box(8, 84, 480, 12, "");
  hex->box(FL_FLAT_BOX);
  hex->labelsize(10);
  hex->labelfont(FL_COURIER);
  hex->align(FL_ALIGN_CENTER/* | FL_ALIGN_INSIDE*/);
  binary->color(FL_BACKGROUND_COLOR);
  key_clear = new Button(392, 32, 88, 32, "Clear", (Fl_Callback *)Calc::key_clear);

  group_num = new Fl_Group(8, 102, 176, 172, "");
  group_num->box(FL_DOWN_BOX);
  key_0 = new Button(72, 232, 48, 32, "0", (Fl_Callback *)Calc::key_0);
  key_1 = new Button(16, 192, 48, 32, "1", (Fl_Callback *)Calc::key_1);
  key_2 = new Button(72, 192, 48, 32, "2", (Fl_Callback *)Calc::key_2);
  key_3 = new Button(128, 192, 48, 32, "3", (Fl_Callback *)Calc::key_3);
  key_4 = new Button(16, 152, 48, 32, "4", (Fl_Callback *)Calc::key_4);
  key_5 = new Button(72, 152, 48, 32, "5", (Fl_Callback *)Calc::key_5);
  key_6 = new Button(128, 152, 48, 32, "6", (Fl_Callback *)Calc::key_6);
  key_7 = new Button(16, 112, 48, 32, "7", (Fl_Callback *)Calc::key_7);
  key_8 = new Button(72, 112, 48, 32, "8", (Fl_Callback *)Calc::key_8);
  key_9 = new Button(128, 112, 48, 32, "9", (Fl_Callback *)Calc::key_9);
  key_equals = new Button(128, 232, 48, 32, "=", (Fl_Callback *)Calc::key_equals);
  key_dot = new Button(16, 232, 48, 32, ".", (Fl_Callback *)Calc::key_dot);
  group_num->end();

  group_hex = new Fl_Group(8, 280, 176, 88, "");
  group_hex->box(FL_DOWN_FRAME);
  key_a = new Button(16, 288, 48, 32, "A", (Fl_Callback *)Calc::key_a);
  key_b = new Button(72, 288, 48, 32, "B", (Fl_Callback *)Calc::key_b);
  key_c = new Button(128, 288, 48, 32, "C", (Fl_Callback *)Calc::key_c);
  key_d = new Button(16, 328, 48, 32, "D", (Fl_Callback *)Calc::key_d);
  key_e = new Button(72, 328, 48, 32, "E", (Fl_Callback *)Calc::key_e);
  key_f = new Button(128, 328, 48, 32, "F", (Fl_Callback *)Calc::key_f);
  group_hex->end();
  
  group_arith = new Fl_Group(192, 102, 64, 172, "");
  group_arith->box(FL_DOWN_FRAME);
  key_add = new Button(200, 112, 48, 32, "+", (Fl_Callback *)Calc::key_add);
  key_add->tooltip("Add");
  key_sub = new Button(200, 152, 48, 32, "-", (Fl_Callback *)Calc::key_sub);
  key_sub->tooltip("Subtract");
  key_mul = new Button(200, 192, 48, 32, "*", (Fl_Callback *)Calc::key_mul);
  key_mul->tooltip("Multiply");
  key_div = new Button(200, 232, 48, 32, "/", (Fl_Callback *)Calc::key_div);
  key_div->tooltip("Divide");
  group_arith->end();

  group_logic = new Fl_Group(264, 102, 120, 172, "");
  group_logic->box(FL_DOWN_FRAME);
  key_sign = new Button(272, 112, 48, 32, "+/-", (Fl_Callback *)Calc::key_sign);
  key_sign->tooltip("Toggle Sign\n");
  key_invert = new Button(328, 112, 48, 32, "~", (Fl_Callback *)Calc::key_invert);
  key_invert->tooltip("One's Complement");
  key_and = new Button(272, 152, 48, 32, "&", (Fl_Callback *)Calc::key_and);
  key_and->tooltip("And");
  key_or = new Button(328, 152, 48, 32, "|", (Fl_Callback *)Calc::key_or);
  key_or->tooltip("Or");
  key_xor = new Button(272, 192, 48, 32, "^", (Fl_Callback *)Calc::key_xor);
  key_xor->tooltip("Exclusive-Or");
  key_mod = new Button(328, 192, 48, 32, "%", (Fl_Callback *)Calc::key_mod);
  key_mod->tooltip("Modulo");
  key_shl = new Button(272, 232, 48, 32, "<<", (Fl_Callback *)Calc::key_shl);
  key_shl->tooltip("Shift Left");
  key_shr = new Button(328, 232, 48, 32, ">>", (Fl_Callback *)Calc::key_shr);
  key_shr->tooltip("Shift Right"); group_logic->end();

  group_mode = new Fl_Group(392, 102, 96, 172, "");
  group_mode->box(FL_DOWN_FRAME);
  key_dec = new ToggleButton(400, 112, 80, 32, "Dec");
  key_dec->callback((Fl_Callback *)Calc::key_dec);
  key_dec->tooltip("Decimal Mode");
  key_hex = new ToggleButton(400, 152, 80, 32, "Hex");
  key_hex->callback((Fl_Callback *)Calc::key_hex);
  key_hex->tooltip("Hexadecimal Mode");
  key_oct = new ToggleButton(400, 192, 80, 32, "Oct");
  key_oct->callback((Fl_Callback *)Calc::key_oct);
  key_oct->tooltip("Octal Mode");
  key_bin = new ToggleButton(400, 232, 80, 32, "Bin");
  key_bin->callback((Fl_Callback *)Calc::key_bin);
  key_bin->tooltip("Binary Mode");
  group_mode->end();

  group_misc = new Fl_Group(192, 280, 296, 88, "");
  group_misc->box(FL_DOWN_FRAME);
  key_sqrt = new Button(200, 288, 64, 32, "√", (Fl_Callback *)Calc::key_sqrt);
  key_sqrt->tooltip("Square Root");
  key_recip = new Button(272, 288, 64, 32, "1/x", (Fl_Callback *)Calc::key_recip);
  key_recip->tooltip("Reciprocal");
  key_int = new Button(344, 288, 64, 32, "Int", (Fl_Callback *)Calc::key_int);
  key_int->tooltip("Integer Part");
  key_incr = new Button(416, 288, 64, 32, "++", (Fl_Callback *)Calc::key_incr);
  key_incr->tooltip("Increment");
  key_pow = new Button(200, 328, 64, 32, "xⁿ", (Fl_Callback *)Calc::key_pow);
  key_pow->tooltip("Power");
  key_pi = new Button(272, 328, 64, 32, "π", (Fl_Callback *)Calc::key_pi);
  key_pi->tooltip("Pi");
  key_frac = new Button(344, 328, 64, 32, "Frac", (Fl_Callback *)Calc::key_frac);
  key_frac->tooltip("Fractional Part");
  key_decr = new Button(416, 328, 64, 32, "--", (Fl_Callback *)Calc::key_decr);
  key_decr->tooltip("Decrement");
  group_misc->end();

  window->end();

  Fl_Tooltip::enable(1);
  Fl_Tooltip::color(FL_WHITE);
  Fl_Tooltip::textcolor(FL_BLACK);

  // init dialogs
  About::init();
  
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

  switch(mode)
  {
    case Calc::MODE_DEC:
      key_dec->value(1);
      break;
    case Calc::MODE_HEX:
      key_hex->value(1);
      break;
    case Calc::MODE_OCT:
      key_oct->value(1);
      break;
    case Calc::MODE_BIN:
      key_bin->value(1);
      break;
  }

  key_dec->redraw();
  key_hex->redraw();
  key_oct->redraw();
  key_bin->redraw();
}

void Gui::setBinary(long double value)
{
  char binary_buf[256];
  char hex_buf[256];
  int count = 0;
  int index = 0;
  int64_t temp = value;

  for(int i = 63; i >= 0; i--)
  {
    if(((temp >> i) & 1) == 1)
    {
      binary_buf[index++] = '1';
    }
    else
    {
      binary_buf[index++] = '0';
    }

    count++;

    if(count > 7)
    {
      count = 0;
      binary_buf[index++] = ' ';
    }
  }

  for(int i = index - 1; i > 0; i -= 9)
  {
    int shift = 0;
    int num = 0;
    char temp[8];

    for(int j = 0; j < 8; j++)
    {
      if(binary_buf[i - j - 1] == '1')
        num |= (1 << shift);

      shift++;
    }

    snprintf(temp, 3, "%02X", num);

    hex_buf[i - 1] = temp[1];
    hex_buf[i - 2] = temp[0];
    hex_buf[i - 3] = ' ';
    hex_buf[i - 4] = ' ';
    hex_buf[i - 5] = ' ';
    hex_buf[i - 6] = ' ';
    hex_buf[i - 7] = ' ';
    hex_buf[i - 8] = ' ';
    hex_buf[i - 9] = ' ';
  }

  binary_buf[index] = '\0';
  hex_buf[index - 1] = ' ';
  hex_buf[index] = '\0';
  binary->copy_label(binary_buf);
  hex->copy_label(hex_buf);
}

Fl_Menu_Bar *Gui::getMenuBar()
{
  return menubar;
}

