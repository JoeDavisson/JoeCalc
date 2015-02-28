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

#include <FL/Fl_Input.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  bool op_started = false;
  int op = Calc::OP_NONE;
  double value1 = 0;
  double value2 = 0;

  void clear()
  {
    Gui::getInput()->value("");
  }

  void append(const char *s)
  {
    if(op_started)
    {
      clear();
      op_started = false;
    }

    Gui::getInput()->insert(s);
  }

  void setOp(int type)
  {
    op = type;
    op_started = true;
  }
}

void Calc::key_clear()
{
  clear();
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
  static char buf[256];

  if(!op_started)
    value2 = atof(Gui::getInput()->value());
  else
    value2 = 0;

  switch(op)
  {
    case OP_ADD:
      sprintf(buf, "%f", value1 + value2);
      break;
    case OP_SUB:
      sprintf(buf, "%f", value1 - value2);
      break;
    case OP_MUL:
      sprintf(buf, "%f", value1 * value2);
      break;
    case OP_DIV:
      if(value2 > 0)
        sprintf(buf, "%f", value1 / value2);
      else
        sprintf(buf, "Divide By Zero Error");
      break;
  }

  Gui::getInput()->value(buf);
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
  value1 = atof(Gui::getInput()->value());
}

void Calc::key_sub()
{
  setOp(OP_SUB);
  value1 = atof(Gui::getInput()->value());
}

void Calc::key_mul()
{
  setOp(OP_MUL);
  value1 = atof(Gui::getInput()->value());
}

void Calc::key_div()
{
  setOp(OP_DIV);
  value1 = atof(Gui::getInput()->value());
}

void Calc::key_sign()
{
}

void Calc::key_invert()
{
}

void Calc::key_and()
{
}

void Calc::key_or()
{
}

void Calc::key_xor()
{
}

void Calc::key_mod()
{
}

void Calc::key_shl()
{
}

void Calc::key_shr()
{
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
}

void Calc::key_recip()
{
}

void Calc::key_int()
{
}

void Calc::key_ceil()
{
}

void Calc::key_pow()
{
}

void Calc::key_twos()
{
}

void Calc::key_frac()
{
}

void Calc::key_floor()
{
}

