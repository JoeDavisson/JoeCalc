/*
Copyright (c) 2023 Joe Davisson.

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
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdint.h>

#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  bool just_cleared = false;
  bool op_started = false;
  int op = Calc::OP_NONE;
  int mode = Calc::MODE_DEC;
  double value1 = 0;
  double value2 = 0;
  char display_buf[256];

  void btoa(int64_t value, char *buf)
  {
    uint64_t temp = value;
    int max_digits = 0;

    if(value == 0)
    {
      buf[0] = '0';
      buf[1] = '\0';
      return;
    }

    while(temp > 0)
    {
      temp >>= 1;
      max_digits++;
    }

    buf[max_digits] = '\0';
    temp = value;

    for(int i = max_digits - 1; i >= 0; i--)
    {
      buf[i] = '0' + (temp & 1);
      temp >>= 1;
    }
  }

  void getValue(double *value)
  {
    switch(mode)
    {
      case Calc::MODE_DEC:
        *value = (double)atof(display_buf);
        break;
      case Calc::MODE_HEX:
        *value = (double)strtoull(display_buf, 0, 16);
        break;
      case Calc::MODE_OCT:
        *value = (double)strtoull(display_buf, 0, 8);
        break;
      case Calc::MODE_BIN:
        *value = (double)strtoull(display_buf, 0, 2);
        break;
    }
  }

  void setOp(int type)
  {
    op = type;
    getValue(&value1);

    if(type == Calc::OP_NONE)
      op_started = false;
    else
      op_started = true;
  }

  bool checkKey(char key)
  {
    switch(mode)
    {
      case Calc::MODE_DEC:
        if((key >= '0' && key <= '9') ||
           (key == '.')/* || (key == '-')*/)
          return true;
        else
          return false;
      case Calc::MODE_HEX:
        if((key >= '0' && key <= '9') ||
           (key >= 'a' && key <= 'f') ||
           (key >= 'A' && key <= 'F'))
          return true;
        else
          return false;
      case Calc::MODE_OCT:
        if(key >= '0' && key <= '7')
          return true;
        else
          return false;
      case Calc::MODE_BIN:
        if(key == '0' || key == '1')
          return true;
        else
          return false;
    }

    return false;
  }

  void update()
  {
    double temp_value = 0;
    getValue(&temp_value);

    if(temp_value > 9007199254740992 || temp_value < -9007199254740992)
    {
      Gui::setBinary(0);
      Gui::updateDisplay("Out of Range");
      op_started = false;
      setOp(Calc::OP_NONE);
      value1 = 0;
      value2 = 0;
      return;
    }
    else
    {
      Gui::setBinary(temp_value);
      Gui::updateDisplay(display_buf);
    }
  }

  void replace(const char *s)
  {
    op_started = false;
    strcpy(display_buf, s);
    Gui::updateDisplay(display_buf);
    setOp(Calc::OP_NONE);
    value1 = 0;
    value2 = 0;
  }

  void replace(double value)
  {
    if(value == 0)
      just_cleared = true;

    if(value > 9007199254740992 || value < -9007199254740992)
    {
      replace("Out of Range");
      value = 0;
    }
    else switch(mode)
    {
      case Calc::MODE_DEC:
        sprintf(display_buf, "%.16g", value);
        break;
      case Calc::MODE_HEX:
        sprintf(display_buf, "%llX", (long long int)value);
        break;
      case Calc::MODE_OCT:
        sprintf(display_buf, "%llo", (long long int)value);
        break;
      case Calc::MODE_BIN:
        btoa((int64_t)value, display_buf);
        break;
    }

    op_started = false;
    Gui::updateDisplay(display_buf);
    Gui::setBinary(value);
    setOp(Calc::OP_NONE);
    value1 = 0;
    value2 = 0;
  }

  void append(const int c)
  {
    if(op_started)
    {
      strcpy(display_buf, "");
      op_started = false;
    }

    if(strcmp(display_buf, "0") == 0)
      if(c != '.')
        strcpy(display_buf, "");

    int pos = strlen(display_buf);

    if(c == FL_BackSpace)
    {
      if(pos > 0)
      {
        display_buf[pos - 1] = '\0';
        display_buf[pos] = '\0';
        update();
      }
      return;
    }

    if(!checkKey(c))
      return;

    if(pos < 32)
    {
      display_buf[pos] = (char)c;
      display_buf[pos + 1] = '\0';
      update();
    } 
  }
}

void Calc::copyToClipboard()
{
  Fl::copy(display_buf, strlen(display_buf), 1, Fl::clipboard_plain_text);
}

/* only works within program
void Calc::pasteFromClipboard()
{
  Fl_Input *in = new Fl_Input(0, 0, 8, 8, Fl::clipboard_plain_text);

  if(Fl::clipboard_contains(Fl::clipboard_plain_text))
     Fl::paste(*in, 1, Fl::clipboard_plain_text);

printf("%s\n", in->value());

  strncpy(display_buf, in->value(), sizeof(display_buf));
  update();

  delete in;
}
*/

void Calc::keypress(const int c, const bool shifted)
{
  switch(c)
  {
    case '=':
      if(shifted)
        key_add();
      else
        key_equals();
      return;
    case '-':
      key_sub();
      return;
    case '8':
      if(shifted)
      {
        key_mul();
        return;
      }
      break;
    case '/':
      key_div();
      return;
    case FL_Enter:
      key_equals();
      return;
    case FL_Escape:
      key_clear();
      return;
    case '7':
      if(shifted)
      {
        key_and();
        return;
      }
      break;
    case '\\':
      if(shifted)
      {
        key_or();
        return;
      }
      break;
    case '6':
      if(shifted)
      {
        key_xor();
        return;
      }
      break;
    case '5':
      if(shifted)
      {
        key_mod();
        return;
      }
      break;
  }

  if(shifted)
    return;

  if(just_cleared)
  {
    just_cleared = false;
    strcpy(display_buf, "");
    Gui::updateDisplay(display_buf);
    append(c);
  }
  else if(op_started)
  {
    op_started = false;
    strcpy(display_buf, "");
    Gui::updateDisplay(display_buf);
    append(c);
  }
  else
  {
    append(c);
  }
}

void Calc::key_clear()
{
  replace("0");
  value1 = 0;
  Gui::setBinary(value1);
  just_cleared = true;
}

void Calc::key_0()
{
  append('0');
}

void Calc::key_1()
{
  append('1');
}

void Calc::key_2()
{
  append('2');
}

void Calc::key_3()
{
  append('3');
}

void Calc::key_4()
{
  append('4');
}

void Calc::key_5()
{
  append('5');
}

void Calc::key_6()
{
  append('6');
}

void Calc::key_7()
{
  append('7');
}

void Calc::key_8()
{
  append('8');
}

void Calc::key_9()
{
  append('9');
}

void Calc::key_equals()
{
  if(op == OP_NONE)
    value2 = 0;
  else
    getValue(&value2);

  switch(op)
  {
    case OP_ADD:
      replace(value1 + value2);
      break;
    case OP_SUB:
      replace(value1 - value2);
      break;
    case OP_MUL:
      replace(value1 * value2);
      break;
    case OP_DIV:
      if(value2 != 0)
        replace(value1 / value2);
      else
        replace("Divide By Zero Error");
      break;
    case OP_POW:
      replace(pow(value1, value2));
      break;
    case OP_AND:
      replace((double)((int64_t)value1 & (int64_t)value2));
      break;
    case OP_OR:
      replace((double)((int64_t)value1 | (int64_t)value2));
      break;
    case OP_XOR:
      replace((double)((int64_t)value1 ^ (int64_t)value2));
      break;
    case OP_MOD:
      if(value2 != 0)
        replace(fmod(value1, value2));
      else
        replace("Divide By Zero Error");
      break;
  }

  setOp(OP_NONE);
}

void Calc::key_dot()
{
  append('.');
}

void Calc::key_a()
{
  append('A');
}

void Calc::key_b()
{
  append('B');
}

void Calc::key_c()
{
  append('C');
}

void Calc::key_d()
{
  append('D');
}

void Calc::key_e()
{
  append('E');
}

void Calc::key_f()
{
  append('F');
}

void Calc::key_add()
{
  setOp(OP_ADD);
}

void Calc::key_sub()
{
  setOp(OP_SUB);
}

void Calc::key_mul()
{
  setOp(OP_MUL);
}

void Calc::key_div()
{
  setOp(OP_DIV);
}

void Calc::key_sign()
{
  getValue(&value1);
  value1 = -value1;
  replace(value1);
}

void Calc::key_invert()
{
  double temp = 0;
  getValue(&temp);
  value1 = (double)(~((int64_t)temp));
  replace(value1);
}

void Calc::key_and()
{
  setOp(OP_AND);
}

void Calc::key_or()
{
  setOp(OP_OR);
}

void Calc::key_xor()
{
  setOp(OP_XOR);
}

void Calc::key_mod()
{
  setOp(OP_MOD);
}

void Calc::key_shl()
{
  double temp = 0;
  getValue(&temp);
  value1 = (double)((int64_t)temp << 1);
  replace(value1);
}

void Calc::key_shr()
{
  double temp = 0;
  getValue(&temp);
  value1 = (double)((int64_t)temp >> 1);
  replace(value1);
}

void Calc::key_dec()
{
  getValue(&value1);
  mode = MODE_DEC;
  replace(value1);
  Gui::setMode(mode);
}

void Calc::key_hex()
{
  getValue(&value1);
  mode = MODE_HEX;
  replace(value1);
  Gui::setMode(mode);
}

void Calc::key_oct()
{
  getValue(&value1);
  mode = MODE_OCT;
  replace(value1);
  Gui::setMode(mode);
}

void Calc::key_bin()
{
  getValue(&value1);
  mode = MODE_BIN;
  replace(value1);
  Gui::setMode(mode);
}

void Calc::key_sqrt()
{
  double temp = 0;
  getValue(&temp);
  value1 = sqrt(temp);
  replace(value1);
}

void Calc::key_recip()
{
  double temp = 0;
  getValue(&temp);

  if(temp != 0)
  {
    value1 = 1.0 / temp;
    replace(value1);
  }
  else
  {
    value1 = 0;
    replace("Divide By Zero Error");
  }
}

void Calc::key_int()
{
  double temp = 0;
  getValue(&temp);
  value1 = (int64_t)temp;
  replace(value1);
}

void Calc::key_incr()
{
  double temp = 0;
  getValue(&temp);
  temp = (int64_t)temp;
  temp++;
  value1 = temp;
  replace(value1);
}

void Calc::key_pow()
{
  setOp(OP_POW);
}

void Calc::key_pi()
{
  value1 = M_PI;
  replace(value1);
}

void Calc::key_frac()
{
  double temp = 0;
  getValue(&temp);
  value1 = temp - (int64_t)temp;
  replace(value1);
}

void Calc::key_decr()
{
  double temp = 0;
  getValue(&temp);
  temp = (int64_t)temp;
  temp--;
  value1 = temp;
  replace(value1);
}

