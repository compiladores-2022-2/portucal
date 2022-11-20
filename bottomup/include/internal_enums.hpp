#ifndef OPERANDS_H
#define OPERANDS_H

enum OP{
  UNION,
  PLUS,
  MINUS,
  TIMES,
  MODOP,
  DIV,
  EXP,
  EQ,
  DIF,
  LEQ,
  GEQ,
  LESS,
  GREATER,
  AND,
  OR,
  UNARY_PLUS,
  UNARY_MINUS,
  NOT
};

enum PRIMITIVE_TYPE{
  PINT,
  PLOGICO,
  PCARAC,
  PFLUT,
};

enum COMMAND{
  ECONTINUE,
  EPARE,
};

#endif