/*
Copyright (c) 2023 Joe Davisson.

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

class Calc
{
public:
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

  static void copyToClipboard();
//  void pasteFromClipboard();

  static void keypress(const int, const bool);
  static void changed();

  static void key_clear();

  static void key_0();
  static void key_1();
  static void key_2();
  static void key_3();
  static void key_4();
  static void key_5();
  static void key_6();
  static void key_7();
  static void key_8();
  static void key_9();
  static void key_equals();
  static void key_dot();

  static void key_a();
  static void key_b();
  static void key_c();
  static void key_d();
  static void key_e();
  static void key_f();

  static void key_add();
  static void key_sub();
  static void key_mul();
  static void key_div();

  static void key_sign();
  static void key_invert();
  static void key_and();
  static void key_or();
  static void key_xor();
  static void key_mod();
  static void key_shl();
  static void key_shr();

  static void key_dec();
  static void key_hex();
  static void key_oct();
  static void key_bin();

  static void key_sqrt();
  static void key_recip();
  static void key_int();
  static void key_incr();
  static void key_pow();
  static void key_pi();
  static void key_frac();
  static void key_decr();

  static void expressionCalc();

private:
  Calc() { }
  ~Calc() { }
};

#endif

