/*
Copyright (c) 2015 Joe Davisson.

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

#ifndef CALC_H
#define CALC_H

namespace Calc
{
  enum
  {
    MODE_DEC,
    MODE_HEX,
    MODE_OCT,
    MODE_BIN
  };

  enum
  {
    OP_NONE,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_MOD,
    OP_POW
  };

  void changed();

  void key_clear();

  void key_0();
  void key_1();
  void key_2();
  void key_3();
  void key_4();
  void key_5();
  void key_6();
  void key_7();
  void key_8();
  void key_9();
  void key_equals();
  void key_dot();

  void key_a();
  void key_b();
  void key_c();
  void key_d();
  void key_e();
  void key_f();

  void key_add();
  void key_sub();
  void key_mul();
  void key_div();

  void key_sign();
  void key_invert();
  void key_and();
  void key_or();
  void key_xor();
  void key_mod();
  void key_shl();
  void key_shr();

  void key_dec();
  void key_hex();
  void key_oct();
  void key_bin();

  void key_sqrt();
  void key_recip();
  void key_int();
  void key_ceil();
  void key_pow();
  void key_twos();
  void key_frac();
  void key_floor();
}

#endif

