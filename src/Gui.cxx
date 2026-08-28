/*
Copyright (c) 2026 Joe Davisson.

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
#include <quadmath.h>

#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Menu_Bar.H>

#include "Button.H"
#include "Gui.H"
#include "InputText.H"
#include "Parse.H"
#include "RepeatButton.H"
#include "StyledText.H"
#include "../icons/joecalc64x64.xpm"

class MainWin;
class Button;

namespace
{
  // window
  MainWin *window;
  Fl_Pixmap *icon;

  // main menu
  Fl_Menu_Bar *menubar;

  // widgets
  StyledText *display;
  InputText *input;
  Fl_Box *bin_display;
  Fl_Box *hex_display;

  RepeatButton *key_undo;
  RepeatButton *key_redo;

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
  Button *key_a;
  Button *key_b;
  Button *key_c;
  Button *key_d;
  Button *key_e;
  Button *key_f;
  Button *key_period;

  Button *key_add;
  Button *key_subtract;
  Button *key_multiply;
  Button *key_divide;
  Button *key_modulo;
  Button *key_power;

  Button *key_and;
  Button *key_or;
  Button *key_xor;
  Button *key_not;
  Button *key_shift_left;
  Button *key_shift_right;

  Button *key_open_paren;
  Button *key_close_paren;

  RepeatButton *key_increment;
  RepeatButton *key_decrement;
  RepeatButton *key_shift_left_1;
  RepeatButton *key_shift_right_1;
  Button *key_shift_left_8;
  Button *key_shift_right_8;
  Button *key_square;
  Button *key_square_root;
  Button *key_reciprocal;
  Button *key_sign_change;
  Button *key_int;
  Button *key_frac;

  Button *key_equals;
  Button *key_clear;
  Button *key_cls;
  Button *key_insert;

  Button *key_hex;
  Button *key_oct;
  Button *key_bin;

  enum
  {
    MODE_DEC,
    MODE_HEX,
    MODE_OCT,
    MODE_BIN
  };

  // vars
  const int64_t min_val = std::numeric_limits<int64_t>::min();
  const uint64_t max_val = std::numeric_limits<uint64_t>::max();
  int mode = MODE_DEC;
  __float128 old_result = 0;

  // prevent escape from closing main window
  void closeCallback(Fl_Widget *widget, void *)
  {
    if ((Fl::event() == FL_KEYDOWN || Fl::event() == FL_SHORTCUT)
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

  void cb_input()
  {
    const __float128 result = Parse::evalExpr(input->value());
    Gui::printResult(result, true);
  }

  void cb_insert(Fl_Widget *w, void *)
  {
    if (w->label()[0] == 'A') { input->insert("a"); }
    else if (w->label()[0] == 'B') { input->insert("b"); }
    else if (w->label()[0] == 'C') { input->insert("c"); }
    else if (w->label()[0] == 'D') { input->insert("d"); }
    else if (w->label()[0] == 'E') { input->insert("e"); }
    else if (w->label()[0] == 'F') { input->insert("f"); }
    else { input->insert(w->label()); }

    input->take_focus();
  }

  void cb_insert_func(Fl_Widget *w, void *)
  {
    Fl_Menu_ *menu = (Fl_Menu_*)w;
    const Fl_Menu_Item *item = menu->mvalue();
    input->insert(item->label());
    input->take_focus();
  }

  void cb_undo()
  {
    input->undo();
  }

  void cb_redo()
  {
    input->redo();
  }

  void cb_clear()
  {
    input->replace(0, input->size(), "");
  }

  void cb_cls()
  {
    display->clear();
  }

  void cb_insert_selected()
  {
    char *selected = display->copySelected();

    if (selected == nullptr) { return; }

    input->insert(selected);
    free(selected);
  }

  void cb_show_dec()
  {
    mode = MODE_DEC;
    Gui::printResult(old_result, false);
  }

  void cb_show_hex()
  {
    mode = MODE_HEX;
    Gui::printResult(old_result, false);
  }

  void cb_show_oct()
  {
    mode = MODE_OCT;
    Gui::printResult(old_result, false);
  }

  void cb_show_bin()
  {
    mode = MODE_BIN;
    Gui::printResult(old_result, false);
  }

  void cb_increment()
  {
    __int128 temp = (__int128)truncq(old_result) + 1;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_decrement()
  {
    __int128 temp = (__int128)truncq(old_result) - 1;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_shift_left_1()
  {
    __int128 temp = (__int128)old_result << 1;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_shift_right_1()
  {
    __int128 temp = (__int128)old_result >> 1;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_shift_left_8()
  {
    __int128 temp = (__int128)old_result << 8;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_shift_right_8()
  {
    __int128 temp = (__int128)old_result >> 8;

    temp &= max_val;
    Gui::printResult(temp, false);
  }

  void cb_square()
  {
    __float128 temp = old_result * old_result;

    if (temp > max_val) { temp = max_val; }

    Gui::printResult(temp, false);
  }

  void cb_square_root()
  {
    __float128 temp = old_result;

    if (temp >= 0) { temp = sqrtq(temp); }
    else { temp = -sqrtq(-temp); }

    if (temp > max_val) { temp = max_val; }

    Gui::printResult(temp, false);
  }

  void cb_reciprocal()
  {
    __float128 temp = (__float128)1 / old_result;

    if (temp > max_val) { temp = max_val; }

    Gui::printResult(temp, false);
  }

  void cb_sign_change()
  {
    __float128 temp = -old_result;

    if (temp > max_val) { temp = max_val; }

    Gui::printResult(temp, false);
  }

  void cb_int()
  {
    Gui::printResult(truncq(old_result), false);
  }

  void cb_frac()
  {
    Gui::printResult(old_result - truncq(old_result), false);
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
    switch(event)
    {
      case FL_FOCUS:
        break;
      case FL_UNFOCUS:
        break;
      case FL_KEYBOARD:
        // give focus to the main menu
        if(Fl::event_alt() > 0)
        {
          Gui::getMenuBar()->take_focus();
          return 0;
        }
    }

    return Fl_Double_Window::handle(event);
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
    char title_text[256];
    const char *credits = "JoeCalc is based in part on the work\nof the FLTK project (http://www.fltk.org).";

    snprintf(title_text, sizeof(title_text), "JoeCalc %s", PACKAGE_STRING);

    Items::dialog = new Fl_Double_Window(408, 224, "About");
    Items::dialog->set_modal();
    Items::close = new Button(156, 172, 96, 32, "Ok", (Fl_Callback *)hide);
    Items::close->labelsize(16);
    Items::title = new Fl_Box(FL_NO_BOX, 80, 8, 256, 32, "");
    Items::title->copy_label(title_text);
    Items::title->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    Items::title->labelsize(24);
    Items::title->labelfont(FL_HELVETICA_BOLD);
    Items::copyright = new Fl_Box(FL_NO_BOX, 80, 56, 256, 32, "Copyright (c) 2026 Joe Davisson");
    Items::copyright->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    Items::copyright->labelsize(16);
    Items::info = new Fl_Box(FL_NO_BOX, 80, 104, 256, 32, credits);
    Items::info->align(FL_ALIGN_LEFT | FL_ALIGN_BOTTOM | FL_ALIGN_INSIDE);
    Items::info->labelsize(16);
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
  window = new MainWin(568, 480, "JoeCalc");
  window->callback(closeCallback);
  window->xclass("JoeCalc");
  icon = new Fl_Pixmap((char * const *)joecalc64x64_xpm);

  // menu
  menubar = new Fl_Menu_Bar(0, 0, window->w(), 24);
  menubar->box(FL_THIN_UP_BOX);

  menubar->add("&File/E&xit", 0,
    (Fl_Callback *)quit, 0, 0);
  menubar->add("&Mode/Decimal", 0,
    (Fl_Callback *)cb_show_dec, 0, FL_MENU_RADIO);
  menubar->add("&Mode/Hexadecimal", 0,
    (Fl_Callback *)cb_show_hex, 0, FL_MENU_RADIO);
  menubar->add("&Mode/Octal", 0,
    (Fl_Callback *)cb_show_oct, 0, FL_MENU_RADIO);
  menubar->add("&Mode/Binary", 0,
    (Fl_Callback *)cb_show_bin, 0, FL_MENU_RADIO);
  menubar->add("&Functions/int", 0,
    (Fl_Callback *)cb_insert_func, 0, 0);
  menubar->add("&Functions/frac", 0,
    (Fl_Callback *)cb_insert_func, 0, 0);
  menubar->add("&Functions/sqrt", 0,
    (Fl_Callback *)cb_insert_func, 0, 0);
  menubar->add("&Functions/abs", 0,
    (Fl_Callback *)cb_insert_func, 0, 0);
  menubar->add("&Functions/rnd", 0,
    (Fl_Callback *)cb_insert_func, 0, 0);
  menubar->add("&Help/&About...", 0,
    (Fl_Callback *)About::show, 0, 0);

  setMenuItem("&Mode/Decimal");

  display = new StyledText(8, 32, 440, 192, 1000);

  input = new InputText(8, 232, 376, 32, "");
  input->callback((Fl_Callback *)cb_input);
  input->textfont(FL_COURIER);
  input->textsize(16);
  input->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);
  input->box(FL_THIN_DOWN_BOX);
  input->color(FL_BACKGROUND2_COLOR);

  key_undo = new RepeatButton(384, 232, 32, 32, "↶", 3, (Fl_Callback *)cb_undo);
  key_undo->labelsize(18);
  key_redo = new RepeatButton(416, 232, 32, 32, "↷", 3, (Fl_Callback *)cb_redo);
  key_redo->labelsize(18);


  key_increment = new RepeatButton(456, 32, 48, 32, "++", 2, (Fl_Callback *)cb_increment);
  key_decrement = new RepeatButton(512, 32, 48, 32, "--", 2, (Fl_Callback *)cb_decrement);
  key_shift_left_1 = new RepeatButton(456, 72, 48, 32, "<< 1", 3, (Fl_Callback *)cb_shift_left_1);
  key_shift_right_1 = new RepeatButton(512, 72, 48, 32, ">> 1", 3, (Fl_Callback *)cb_shift_right_1);
  key_shift_left_8 = new Button(456, 112, 48, 32, "<< 8", 4, (Fl_Callback *)cb_shift_left_8);
  key_shift_right_8 = new Button(512, 112, 48, 32, ">> 8", 4, (Fl_Callback *)cb_shift_right_8);
  key_square = new Button(456, 152, 48, 32, "x²", 5, (Fl_Callback *)cb_square);
  key_square_root = new Button(512, 152, 48, 32, "√", 5, (Fl_Callback *)cb_square_root);
  key_reciprocal = new Button(456, 192, 48, 32, "1/x", 6, (Fl_Callback *)cb_reciprocal);
  key_sign_change = new Button(512, 192, 48, 32, "+/-", 6, (Fl_Callback *)cb_sign_change);
  key_int = new Button(456, 232, 48, 32, "int", 7, (Fl_Callback *)cb_int);
  key_frac = new Button(512, 232, 48, 32, "frac", 7, (Fl_Callback *)cb_frac);

  bin_display = new Fl_Box(8, 280, 560, 12, "");
  bin_display->box(FL_NO_BOX);
  bin_display->labelsize(12);
  bin_display->labelfont(FL_COURIER);
  bin_display->align(FL_ALIGN_CENTER);
  bin_display->color(FL_BACKGROUND_COLOR);

  hex_display = new Fl_Box(8, 296, 560, 12, "");
  hex_display->box(FL_NO_BOX);
  hex_display->labelsize(12);
  hex_display->labelfont(FL_COURIER);
  hex_display->align(FL_ALIGN_CENTER);
  hex_display->color(FL_BACKGROUND_COLOR);

  key_7 = new Button(8, 320, 48, 32, "7", 7, (Fl_Callback *)cb_insert);
  key_8 = new Button(64, 320, 48, 32, "8", 7, (Fl_Callback *)cb_insert);
  key_9 = new Button(120, 320, 48, 32, "9", 7, (Fl_Callback *)cb_insert);
  key_4 = new Button(8, 360, 48, 32, "4", 7, (Fl_Callback *)cb_insert);
  key_5 = new Button(64, 360, 48, 32, "5", 7, (Fl_Callback *)cb_insert);
  key_6 = new Button(120, 360, 48, 32, "6", 7, (Fl_Callback *)cb_insert);
  key_1 = new Button(8, 400, 48, 32, "1", 7, (Fl_Callback *)cb_insert);
  key_2 = new Button(64, 400, 48, 32, "2", 7, (Fl_Callback *)cb_insert);
  key_3 = new Button(120, 400, 48, 32, "3", 7, (Fl_Callback *)cb_insert);
  key_0 = new Button(8, 440, 104, 32, "0", 7, (Fl_Callback *)cb_insert);
  key_period = new Button(120, 440, 48, 32, ".", 7, (Fl_Callback *)cb_insert);

  key_open_paren = new Button(176, 320, 48, 32, "(", 6, (Fl_Callback *)cb_insert);
  key_close_paren = new Button(232, 320, 48, 32, ")", 6, (Fl_Callback *)cb_insert);
  key_e = new Button(176, 360, 48, 32, "E", 5, (Fl_Callback *)cb_insert);
  key_f = new Button(232, 360, 48, 32, "F", 5, (Fl_Callback *)cb_insert);
  key_c = new Button(176, 400, 48, 32, "C", 5, (Fl_Callback *)cb_insert);
  key_d = new Button(232, 400, 48, 32, "D", 5, (Fl_Callback *)cb_insert);
  key_a = new Button(176, 440, 48, 32, "A", 5, (Fl_Callback *)cb_insert);
  key_b = new Button(232, 440, 48, 32, "B", 5, (Fl_Callback *)cb_insert);

  key_add = new Button(288, 320, 48, 32, "+", 4, (Fl_Callback *)cb_insert);
  key_subtract = new Button(344, 320, 48, 32, "-", 4, (Fl_Callback *)cb_insert);
  key_multiply = new Button(400, 320, 48, 32, "*", 4, (Fl_Callback *)cb_insert);
  key_divide = new Button(288, 360, 48, 32, "/", 4, (Fl_Callback *)cb_insert);
  key_modulo = new Button(344, 360, 48, 32, "%", 4, (Fl_Callback *)cb_insert);
  key_power = new Button(400, 360, 48, 32, "**", 4, (Fl_Callback *)cb_insert);

  key_and = new Button(288, 400, 48, 32, "&", 2, (Fl_Callback *)cb_insert);
  key_or = new Button(344, 400, 48, 32, "|", 2, (Fl_Callback *)cb_insert);
  key_xor = new Button(400, 400, 48, 32, "^", 2, (Fl_Callback *)cb_insert);
  key_not = new Button(288, 440, 48, 32, "~", 2, (Fl_Callback *)cb_insert);
  key_shift_left = new Button(344, 440, 48, 32, "<<", 2, (Fl_Callback *)cb_insert);
  key_shift_right = new Button(400, 440, 48, 32, ">>", 2, (Fl_Callback *)cb_insert);

  key_equals = new Button(456, 320, 48, 72, "=", 7, (Fl_Callback *)cb_input);
  key_equals->labelsize(18);
  key_clear = new Button(512, 320, 48, 72, "C", 6, (Fl_Callback *)cb_clear);

  key_cls = new Button(456, 400, 48, 32, "cls", 5, (Fl_Callback *)cb_cls);
  key_insert = new Button(512, 400, 48, 32, "ins", 5, (Fl_Callback *)cb_insert_selected);

  key_hex = new Button(456, 440, 30, 32, "0x", 4, (Fl_Callback *)cb_insert);
  key_oct = new Button(492, 440, 30, 32, "0o", 4, (Fl_Callback *)cb_insert);
  key_bin = new Button(528, 440, 30, 32, "0b", 4, (Fl_Callback *)cb_insert);

  window->end();

  Fl_Tooltip::enable(1);
  Fl_Tooltip::color(FL_WHITE);
  Fl_Tooltip::textcolor(FL_BLACK);

  About::init();
  window->show();
  setDigits(0);
}

void Gui::appendDec(const __float128 result)
{
  if (mode != MODE_DEC) { return; };

  char buf[1024];
  const int len = sizeof(buf);
  int bytes = 0;

  // decimal
  bytes = quadmath_snprintf(buf, len, "%.20Qf", result);

  // trim trailing zeros
  for (int i = bytes - 1; i >= 0; i--)
  {
    if (buf[i] == '0')
    {
      buf[i] = '\0';
    }
    else if (buf[i] == '.')
    {
      buf[i] = '\0';
      break;
    }
      else
    {
      break;
    }
  }

  display->append(buf, 'A');
  display->append("\n");
  input->replace(0, input->size(), buf);

  Gui::setDigits(result);
  old_result = result;
}

void Gui::appendHex(const __float128 result)
{
  if (mode != MODE_HEX) { return; };

  char buf[1024];
  const int len = sizeof(buf);

  if (result >= 0)
  {
    const uint64_t temp = (uint64_t)result;
    snprintf(buf, len, "0x%lx", temp & max_val);
  }
    else
  {
    const int64_t temp = (int64_t)result;
    snprintf(buf, len, "0x%lx", temp & max_val);
  }

  display->append(buf, "", "0x", 'B', 'A');
  display->append("\n");
  input->replace(0, input->size(), buf);

  Gui::setDigits(result);
  old_result = result;
}

void Gui::appendOct(const __float128 result)
{
  if (mode != MODE_OCT) { return; };

  char buf[1024];
  const int len = sizeof(buf);

  if (result >= 0)
  {
    const uint64_t temp = (uint64_t)result;
    snprintf(buf, len, "0o%lo", temp & max_val);
  }
    else
  {
    const int64_t temp = (int64_t)result;
    snprintf(buf, len, "0o%lo", temp & max_val);
  }

  display->append(buf, "", "0o", 'B', 'A');
  display->append("\n");
  input->replace(0, input->size(), buf);

  Gui::setDigits(result);
  old_result = result;
}

void Gui::appendBin(const __float128 result)
{
  if (mode != MODE_BIN) { return; };

  char buf[1024];
  const int len = sizeof(buf);

  if (result >= 0)
  {
    const uint64_t temp = (uint64_t)result;
    snprintf(buf, len, "0b%lb", temp & max_val);
  }
    else
  {
    const int64_t temp = (int64_t)result;
    snprintf(buf, len, "0b%lb", temp & max_val);
  }

  display->append(buf, "", "0b", 'B', 'A');
  display->append("\n");
  input->replace(0, input->size(), buf);

  Gui::setDigits(result);
  old_result = result;
}

void Gui::printResult(__float128 result, const bool show_input)
{
  if (isnanq(result))
  {
    display->append("(syntax error)\n", 'E');
    return;
  }    

  if (result < min_val || result > max_val)
  {
    display->append("(out of range)\n", 'E');
    return;
  }

  if (mode != MODE_DEC) { result = truncq(result); }

  if (show_input == true)
  {
    display->append(input->value(), 'E');
    display->append("\n", 'E');
  }

  appendDec(result);
  appendHex(result);
  appendOct(result);
  appendBin(result);
}

void Gui::updateDisplay(const char *s)
{
  display->copy_label(s);
}

void Gui::setDigits(const __float128 value)
{
  char bin_buf[256];
  char hex_buf[256];
  char temp_buf[256];
  int count = 0;
  int index = 0;
  __int128 temp = (__int128)value;

  // binary
  for(int i = 63; i >= 0; i--)
  {
    if(((temp >> i) & 1) == 1)
    {
      bin_buf[index++] = '1';
    }
      else
    {
      bin_buf[index++] = '0';
    }

    count++;

    if(count > 7)
    {
      count = 0;
      bin_buf[index++] = ' ';
    }
  }

  bin_buf[index] = '\0';
  bin_display->copy_label(bin_buf);

  // hexadecimal
  for(int i = index - 1; i > 0; i -= 9)
  {
    int shift = 0;
    int num = 0;

    for(int j = 0; j < 8; j++)
    {
      if(bin_buf[i - j - 1] == '1')
        num |= (1 << shift);

      shift++;
    }

    snprintf(temp_buf, 3, "%02X", num);

    hex_buf[i - 1] = temp_buf[1];
    hex_buf[i - 2] = temp_buf[0];
    hex_buf[i - 3] = ' ';
    hex_buf[i - 4] = ' ';
    hex_buf[i - 5] = ' ';
    hex_buf[i - 6] = ' ';
    hex_buf[i - 7] = ' ';
    hex_buf[i - 8] = ' ';
    hex_buf[i - 9] = ' ';
  }

  hex_buf[index - 1] = ' ';
  hex_buf[index] = '\0';
  hex_display->copy_label(hex_buf);
}

Fl_Menu_Bar *Gui::getMenuBar()
{
  return menubar;
}

void Gui::setMenuItem(const char *str)
{
  Fl_Menu_Item *item;
  item = (Fl_Menu_Item *)menubar->find_item(str);

  if (item) { item->set(); }
}

void Gui::clearMenuItem(const char *str)
{
  Fl_Menu_Item *item;
  item = (Fl_Menu_Item *)menubar->find_item(str);

  if (item) { item->clear(); }
}

