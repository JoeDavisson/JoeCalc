/*
Copyright (c) 2026 Joe Davisson.

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

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <array>
#include <quadmath.h>

#include "Parse.H"

namespace
{
  enum
  {
    OP_FUNC_INT,
    OP_FUNC_FRAC,
    OP_FUNC_ABS,
    OP_FUNC_RND,
    OP_FUNC_SQRT,
    OP_UNARY,
    OP_SHIFT_LEFT,
    OP_SHIFT_RIGHT,
    OP_POWER,
    OP_LEFT_PAREN,
    OP_RIGHT_PAREN,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MODULO,
    OP_NOT,
    OP_AND,
    OP_OR,
    OP_XOR
  };

  struct table_entry
  {
    const int op;
    const char *token;
    const int size;
    const bool is_func;
  };

  const struct table_entry table[] =
  {
    { OP_FUNC_INT, "int", 3 , true },
    { OP_FUNC_FRAC, "frac", 4 , true },
    { OP_FUNC_ABS, "abs", 3 , true },
    { OP_FUNC_RND, "rnd", 3 , true },
    { OP_FUNC_SQRT, "sqrt", 4 , true },
    { OP_UNARY, "", 1, false },
    { OP_SHIFT_LEFT, "<<", 2, false },
    { OP_SHIFT_RIGHT, ">>", 2, false },
    { OP_POWER, "**", 2, false },
    { OP_LEFT_PAREN, "(", 1, false},
    { OP_RIGHT_PAREN, ")", 1, false },
    { OP_ADD, "+", 1, false },
    { OP_SUBTRACT, "-", 1, false },
    { OP_MULTIPLY, "*", 1, false },
    { OP_DIVIDE, "/", 1, false },
    { OP_MODULO, "%", 1, false },
    { OP_NOT, "~", 1, false},
    { OP_AND, "&", 1, false },
    { OP_OR, "|", 1, false },
    { OP_XOR, "^", 1, false }
  };

  const int max = 1000;
  const int top = max - 1;

  std::array<int, max + 1> stack_op;
  std::array<__float128, max + 1> stack_val;
  int sp_op = top;
  int sp_val = top;

  const __float128 not_a_number = std::numeric_limits<__float128>::quiet_NaN();

  int getOp(const char *p)
  {
    int length = sizeof(table) / sizeof(table[0]);

    for (int i = 0; i < length; i++)
    {
       if (strncasecmp(p, table[i].token, table[i].size) == 0)
       {
         return table[i].op;
       }
    }

    return -1;
  }

  void pushOp(const int op)
  {
    stack_op[sp_op] = op;
    sp_op--;

    if (sp_op < 0) { sp_op = 0; }
  }

  void pushVal(const __float128 val)
  {
    stack_val[sp_val] = val;
    sp_val--;

    if (sp_val < 0) { sp_val = 0; }
  }

  int popOp()
  {
    sp_op++;

    if (sp_op >= top) { sp_op = top; }
    return stack_op[sp_op];
  }

  __float128 popVal()
  {
    sp_val++;
    if (sp_val >= top) { sp_val = top; }
    return stack_val[sp_val];
  }

  int topOp()
  {
    if (sp_op < top) { return stack_op[sp_op + 1]; }
    else { return not_a_number; }
  }

  __float128 topVal()
  {
    if (sp_val < top) { return stack_val[sp_val + 1]; }
    else { return not_a_number; }
  }

  bool emptyOp()
  {
    if (sp_op >= top) { return true; }
    else { return false; }
  }

  bool emptyVal()
  {
    if (sp_val >= top) { return true; }
    else { return false; }
  }

  bool isFunc(const int op)
  {
    int length = sizeof(table) / sizeof(table[0]);

    for (int i = 0; i < length; i++)
    {
       if (table[i].op == op)
       {
         return table[i].is_func;
       }
    }

    return false;
  }

  int orderOfOps(const int op) 
  {
    switch (op)
    {
      case OP_OR:
        return 1;
      case OP_XOR:
        return 2;
      case OP_AND:
        return 3;
      case OP_SHIFT_LEFT:
      case OP_SHIFT_RIGHT:
        return 4;
      case OP_ADD:
      case OP_SUBTRACT:
        return 5;
      case OP_MULTIPLY:
      case OP_DIVIDE:
      case OP_MODULO:
        return 6;
      case OP_UNARY:
      case OP_NOT:
        return 7;
      case OP_POWER:
        return 8;
      case OP_FUNC_INT:
      case OP_FUNC_FRAC:
      case OP_FUNC_ABS:
      case OP_FUNC_RND:
      case OP_FUNC_SQRT:
        return 9;
    }

    return 0;
  }

  bool exec()
  {
    if (emptyOp() == true || emptyVal() == true) { return false; }

    int op = popOp();
    __float128 b = popVal();
    __float128 a = 0;

    if (op != OP_UNARY && op != OP_NOT && isFunc(op) == false)
    {
      if (emptyVal() == true) { return false; }

      a = popVal();
    }

    switch (op)
    {
      case OP_OR:
      {
        pushVal((__float128)((__int128)a | (__int128)b));
        break;
      }
      case OP_XOR:
      {
        pushVal((__float128)((__int128)a ^ (__int128)b));
        break;
      }
      case OP_AND:
      {
        pushVal((__float128)((__int128)a & (__int128)b));
        break;
      }
      case OP_SHIFT_LEFT:
      {
        if ((__int128)b < 64)
        {
          pushVal((__float128)((__int128)a << (__int128)b));
        }
          else
        {
          return false;
        }

        break;
      }
      case OP_SHIFT_RIGHT:
      {
        if ((__int128)b < 64)
        {
          pushVal((__float128)((__int128)a >> (__int128)b));
        }
          else
        {
          return false;
        }

        break;
      }
      case OP_ADD:
      {
        pushVal(a + b);
        break;
      }
      case OP_SUBTRACT:
      {
        pushVal(a - b);
        break;
      }
      case OP_MULTIPLY:
      {
        pushVal(a * b);
        break;
      }
      case OP_DIVIDE:
      {
        if (b == 0) { pushVal(not_a_number); }
        else { pushVal(a / b); }
        break;
      }
      case OP_MODULO:
      {
        if (b == 0) { pushVal(not_a_number); }
        else { pushVal(fmodq(a, b)); }
        break;
      }
      case OP_POWER:
      {
        pushVal(powq(a, b));
        break;
      }
      case OP_NOT:
      {
        pushVal((__float128)(~((__int128)b)));
        break;
      }
      case OP_UNARY:
      {
        pushVal(-b);
        break;
      }
      case OP_FUNC_INT:
      {
        pushVal(truncq(b));
        break;
      }
      case OP_FUNC_FRAC:
      {
        pushVal(b - truncq(b));
        break;
      }
      case OP_FUNC_ABS:
      {
        pushVal(fabsq(b));
        break;
      }
      case OP_FUNC_RND:
      {
        pushVal(((__float128)std::rand() / RAND_MAX) * b);
        break;
      }
      case OP_FUNC_SQRT:
      {
        if (b >= 0) { pushVal(sqrtq(b)); }
        else { pushVal(-sqrtq(-b)); }
        break;
      }
    }

    return true;
  }

  __float128 convert(char **p)
  {
    __float128 val = 0;
    char *index;

    if (strncasecmp(*p, "0b", 2) == 0)
    {
      *p += 2;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 2);
      if (index - *p > 64) { val = not_a_number; }
      if (*p == index) { val = not_a_number; }
      *p = index;
      return val;
    }
    if (strncasecmp(*p, "-0b", 3) == 0)
    {
      *p += 3;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 2);
      if (index - *p > 64) { val = not_a_number; }
      if (*p == index) { val = not_a_number; }
      *p = index;
      return -val;
    }
    else if (strncasecmp(*p, "0o", 2) == 0)
    {
      *p += 2;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 8);
      if (index - *p > 22) { val = not_a_number; }
      if (*p == index) { val = not_a_number; }
      *p = index;
      return val;
    }
    else if (strncasecmp(*p, "-0o", 3) == 0)
    {
      *p += 3;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 8);
      if (index - *p > 22) { val = not_a_number; }
      if (*p == index) { ; val = not_a_number; }
      *p = index;
      return -val;
    }
    else if (strncasecmp(*p, "0x", 2) == 0)
    {
      *p += 2;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 16);
      if (index - *p > 16) { val = not_a_number; }
      if (*p == index) { val = not_a_number; }
      *p = index;
      return val;
    }
    else if (strncasecmp(*p, "-0x", 3) == 0)
    {
      *p += 3;
      if (**p == ' ') { return not_a_number; }
      val = strtoull(*p, &index, 16);
      if (index - *p > 16) { val = not_a_number; }
      if (*p == index) { val = not_a_number; }
      *p = index;
      return -val;
    }
      else
    {
      val = strtoflt128(*p, &index);
      if (*p == index) { val = not_a_number; }
      *p = index;
      return val;
    }
  }
}

__float128 Parse::evalExpr(const char *expr)
{
  sp_op = top;
  sp_val = top;

  bool expect_op = false;
  bool prev_was_val = false;
  bool check_first = true;
  char *p = (char *)expr;
  int op = 0;

  while (true)
  {
    const char c = *p;

    if (c == '\0') { break; }

    if (c == ' ')
    {
      p++;
      continue;
    }

    if (prev_was_val == false &&
        expect_op == false &&
        (topOp() == OP_LEFT_PAREN || check_first == true) &&
        c == '-')
    {
      pushOp(OP_UNARY);
      check_first = false;
      expect_op = false;
      p += 1;
    }
    else if (expect_op == false &&
       ((c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-'))
    {
      const __float128 val = convert(&p);

      pushVal(val);
      expect_op = true;
      prev_was_val = true;
    }
      else
    {
      op = getOp(p);

      if (op == -1) { return not_a_number; }

      if (prev_was_val == true)
      {
        if ((isFunc(op) == true) || op == OP_LEFT_PAREN)
        {
          return not_a_number;
        }
      }

      prev_was_val = false;

      if (op == OP_LEFT_PAREN)
      {
        if (expect_op == true) { return not_a_number; }

        pushOp(op);
        expect_op = false;
        p += table[op].size;
      }
      else if (op == OP_RIGHT_PAREN)
      {
        if (expect_op == false) { return not_a_number; }

        while (emptyOp() == false && topOp() != OP_LEFT_PAREN)
        {
          if(exec() == false)
          {
            p += table[op].size;
            break;
          }
        }

        if (emptyOp() == true || topOp() != OP_LEFT_PAREN)
        {
          return not_a_number;
        }

        if (isFunc(topOp()) == true) { popOp(); }

        if (emptyOp() == false) { popOp(); }

        expect_op = true;
        p += table[op].size;
      }
        else
      {

        if (orderOfOps(op) == 0 && op != OP_LEFT_PAREN && op != OP_RIGHT_PAREN)
        {
          return not_a_number;
        }

        while (emptyOp() == false && topOp() != OP_LEFT_PAREN &&
               orderOfOps(topOp()) >= orderOfOps(op) &&
               op != OP_POWER && op != OP_UNARY)
        {
          if (exec() == false) { break; }
        }

        pushOp(op);
        expect_op = false;
        p += table[op].size;
      }
    }
  }

  while (emptyOp() == false)
  {
    if (exec() == false) { break; }
  }

  if (emptyVal() == true || sp_val != top - 1 || expect_op == false)
  {
    return not_a_number;
  }
    else
  {
    return topVal();
  }
}

