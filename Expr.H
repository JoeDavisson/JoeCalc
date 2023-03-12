/*
Copyright (c) 2023 Joe Davisson.

This file is part of JoeCalc.

Rendera is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Rendera is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Rendera; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

class Expr
{
public:
  enum
  {
    TOKEN_NONE,
    TOKEN_OP,
    TOKEN_NUM
  };

  static double eval_exp(const char *);
  static void eval_shift(double &);
  static void eval_bitwise(double &);
  static void eval_add_sub(double &);
  static void eval_mul_div(double &);
  static void eval_unary(double &);
  static void eval_group(double &);
  static void get_token();
  static double parseString(const char *);

private:
  Expr() { }
  ~Expr() { }
};


