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

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
//#include <tgmath.h>
#include <cmath>

#include "Expr.H"

/*

( )

! ~ ++ -- - (unary)

* / %

+ -
<< >>
&
^
|

*/

// | ^ & > < - + % / * ~ ( )
 
namespace
{
  char *exp_ptr;
  char token[4096];
  char tok_type;
}

double Expr::eval_exp(const char *exp)
{
  double result;

  exp_ptr = (char *)exp;
  get_token();

  if (!*token) 
    return 0;

  eval_shift(result);

  return result;
}

void Expr::eval_shift(double &result)
{
  char op;
  double temp;

  eval_bitwise(result);

  while((op = *token) == '<' || op == '>')
  {
    get_token();

    if(*token != '<' && *token != '>')
    {
      printf("Syntax Error #2\n");
    }

    get_token();
    eval_bitwise(temp);

    switch (op) 
    {
      case '<':
        result = (int64_t)result << (int64_t)temp;
        break;
      case '>':
        result = (int64_t)result >> (int64_t)temp;
        break;
    }
  }
}

void Expr::eval_bitwise(double &result)
{
  char op;
  double temp;

  eval_add_sub(result);

  while((op = *token) == '&' || op == '|' || op == '^')
  {
    get_token();
    eval_add_sub(temp);

    switch (op) 
    {
      case '&':
        result = (int64_t)result & (int64_t)temp;
        break;
      case '|':
        result = (int64_t)result | (int64_t)temp;
        break;
      case '^':
        result = (int64_t)result ^ (int64_t)temp;
        break;
    }
  }
}

void Expr::eval_add_sub(double &result)
{
  char op;
  double temp;

  eval_mul_div(result);

  while((op = *token) == '+' || op == '-')
  {
    get_token();
    eval_mul_div(temp);

    switch (op) 
    {
      case '+':
        result += temp;
        break;
      case '-':
        result -= temp;
        break;
    }
  }
}

void Expr::eval_mul_div(double &result)
{
  char op;
  double temp;

  eval_unary(result);

  while ((op = *token) == '*' || op == '/' || op == '%') 
  {
    get_token();
    eval_unary(temp);
    switch (op) 
    {
      case '*':
        result = result * temp;
        break;
      case '/':
        // FIXME check for divide by zero!
        result = result / temp;
        break;
      case '%':
        // FIXME check for divide by zero!
        result = std::fmod(result, temp);
        break;
    }
  }
}

void Expr::eval_unary(double &result)
{
  char op = 0;

  if((tok_type == TOKEN_OP) && (*token == '+' || *token == '-'))
  {
    op = *token;
    get_token();
  }

  eval_group(result);

  if(op == '-')
    result = -result;
}

void Expr::eval_group(double &result)
{
  if((*token == '(')) 
  {
    get_token();
//    eval_add_sub(result);
    eval_shift(result);

    if (*token != ')')
      printf("Unbalanced Parentheses\n");

    get_token();
  }
  else switch (tok_type)
  {
      case TOKEN_NUM:
        result = atof(token);
        get_token();
        return;
      default:
        printf("Syntax Error\n");
  }
}

void Expr::get_token()
{
  const char *ch = " |^&><-+%/*~()"; 
  char *temp = token;

  tok_type = 0;
  *temp = '\0';

  if(!*exp_ptr)  // at end of expression
    return;

  while(isspace(*exp_ptr))  // skip over white space
    exp_ptr++; 

  if(strchr(ch, *exp_ptr)) 
  {
    tok_type = TOKEN_OP;
    *temp++ = *exp_ptr++;  // advance to next char
  }
  else if(isdigit(*exp_ptr) || *exp_ptr == '.')
  {
    while(!strchr(ch + 1, *exp_ptr) && (*exp_ptr))
      *temp++ = toupper(*exp_ptr++);
    tok_type = TOKEN_NUM;
  }

  *temp = '\0';
}

double Expr::parseString(const char *expstr)
{
  return eval_exp(expstr);
}
 
