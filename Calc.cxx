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

#include <FL/Fl_Input.H>

#include "Calc.H"
#include "Gui.H"

namespace
{
  void append(const char *s)
  {
    Gui::getInput()->insert(s);
  }

  void clear()
  {
    Gui::getInput()->value("0");
  }
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
}

void Calc::key_sub()
{
}

void Calc::key_mul()
{
}

void Calc::key_div()
{
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
}

void Calc::key_hex()
{
}

void Calc::key_oct()
{
}

void Calc::key_bin()
{
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

