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
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdint.h>

#include <FL/Fl_Input.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  bool op_started = false;
  int op = Calc::OP_NONE;
  double value1 = 0;
  double value2 = 0;

  void getValue(double *value)
  {
    *value = atof(Gui::getInput()->value());
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

  void clear()
  {
    Gui::getInput()->value("");
    Gui::setBinary(0);
  }

  void append(const char *s)
  {
    if(op_started)
    {
      clear();
      op_started = false;
    }

    Gui::getInput()->insert(s);
    Gui::setBinary(atof(Gui::getInput()->value()));
  }

  void replace(double val)
  {
    static char buf[256];

    sprintf(buf, "%.16g", val);

    op_started = false;
    Gui::getInput()->value(buf);
    Gui::setBinary(atof(Gui::getInput()->value()));
    setOp(Calc::OP_NONE);
    value1 = 0;
    value2 = 0;
  }

  void replace(const char *s)
  {
    op_started = false;
    Gui::getInput()->value(s);
    setOp(Calc::OP_NONE);
    value1 = 0;
    value2 = 0;
  }
}

void Calc::changed()
{
  const char *old = Gui::getInput()->value();
  char last[2];

  last[0] = old[strlen(old) - 1];
  last[1] = '\0';

  if(op_started)
  {
    op_started = false;
    clear();
    Gui::getInput()->insert(last);
  }
}

void Calc::key_clear()
{
  clear();
  setOp(Calc::OP_NONE);
}

void Calc::key_0()
{
  append("0");
}

void Calc::key_1()
{
  append("1");
}

void Calc::key_2()
{
  append("2");
}

void Calc::key_3()
{
  append("3");
}

void Calc::key_4()
{
  append("4");
}

void Calc::key_5()
{
  append("5");
}

void Calc::key_6()
{
  append("6");
}

void Calc::key_7()
{
  append("7");
}

void Calc::key_8()
{
  append("8");
}

void Calc::key_9()
{
  append("9");
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
      if(value2 != 0.0)
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
      if(value2 != 0.0)
        replace(fmod(value1, value2));
      else
        replace("Divide By Zero Error");
      break;
  }

  setOp(OP_NONE);
  value1 = 0;
  value2 = 0;
}

void Calc::key_dot()
{
  append(".");
}

void Calc::key_a()
{
  append("A");
}

void Calc::key_b()
{
  append("B");
}

void Calc::key_c()
{
  append("C");
}

void Calc::key_d()
{
  append("D");
}

void Calc::key_e()
{
  append("E");
}

void Calc::key_f()
{
  append("F");
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
  value1 = -atof(Gui::getInput()->value());
  replace(value1);
}

void Calc::key_invert()
{
  int64_t temp = (int64_t)atof(Gui::getInput()->value());
  temp = ~temp;
  value1 = temp;
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
  int64_t temp = (int64_t)atof(Gui::getInput()->value());
  temp <<= 1;
  value1 = temp;
  replace(value1);
}

void Calc::key_shr()
{
  int64_t temp = (int64_t)atof(Gui::getInput()->value());
  temp >>= 1;
  value1 = temp;
  replace(value1);
}

void Calc::key_dec()
{
  Gui::setMode(Calc::MODE_DEC);
}

void Calc::key_hex()
{
  Gui::setMode(Calc::MODE_HEX);
}

void Calc::key_oct()
{
  Gui::setMode(Calc::MODE_OCT);
}

void Calc::key_bin()
{
  Gui::setMode(Calc::MODE_BIN);
}

void Calc::key_sqrt()
{
  value1 = sqrt(atof(Gui::getInput()->value()));
  replace(value1);
}

void Calc::key_recip()
{
  double temp = atof(Gui::getInput()->value());

  if(temp != 0.0)
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
  value1 = (int64_t)atof(Gui::getInput()->value());
  replace(value1);
}

void Calc::key_ceil()
{
  value1 = ceil(atof(Gui::getInput()->value()));
  replace(value1);
}

void Calc::key_pow()
{
  setOp(OP_POW);
}

void Calc::key_twos()
{
  value1 = atof(Gui::getInput()->value());
  int64_t temp = (int64_t)value1;
  temp = ~temp;
  temp++;
  value1 = temp;
  replace(value1);
}

void Calc::key_frac()
{
  value1 = atof(Gui::getInput()->value());
  value1 = value1 - (int64_t)value1;
  replace(value1);
}

void Calc::key_floor()
{
  value1 = floor(atof(Gui::getInput()->value()));
  replace(value1);
}

