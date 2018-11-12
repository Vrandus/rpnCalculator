#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);

static int op_subtract(struct tokenStack *stack);
static int op_multiply(struct tokenStack *stack);
static int op_divide(struct tokenStack *stack);
static int op_greaterThan(struct tokenStack *stack);
static int op_lessThan(struct tokenStack *stack);
static int op_greaterEqual(struct tokenStack *stack);
static int op_lessEqual(struct tokenStack *stack);
static int op_equal(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_subtract},
  {"*", op_multiply},
  {"/", op_divide},
  {"GT", op_greaterThan},
  {"LT", op_lessThan},
  {"GE", op_greaterEqual},
  {"LE", op_lessEqual},
  {"EQ", op_equal},
  {"HELP", op_help},
  {"SWAP", op_swap},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s) {
	struct lexToken *popped = popTokenStack(s);	
	return atoi(popped->symbol);
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v) {
	struct lexToken *newToken = allocToken();
	newToken->kind = LEX_TOKEN_NUMBER;
	sprintf(newToken->symbol, "%d", v);
	pushTokenStack(s, newToken);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_subtract(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}


static int op_multiply(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0);
}

static int op_divide(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2/v1);
  return(0);
}

static int op_greaterThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 > v2)
  	pushInt(stack, 1);
  else
	pushInt(stack, 0);
  return(0);
}

static int op_lessThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1	< v2) 
        pushInt(stack, 1);
  else
        pushInt(stack, 0);
  return(0);
}

static int op_greaterEqual(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1	>= v2) 
        pushInt(stack, 1);
  else
        pushInt(stack, 0);
  return(0);
}

static int op_lessEqual(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1	<= v2) 
        pushInt(stack, 1);
  else
        pushInt(stack, 0);
  return(0);
}

static int op_equal(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1	== v2) 
        pushInt(stack, 1);
  else
        pushInt(stack, 0);
  return(0);
}

static int op_help(struct tokenStack *stack)
{
  printf("documentation\n\n");
  printf("Operations:\n");
  printf("- : push n1 - n2\n");
  printf("+ : push n1 + n2\n");
  printf("* : push n1 * n2\n");  
  printf("/ : push n1 / n2\n");
  printf("GT : push 1 if n1 > n2, else 0 \n");
  printf("LT : push 1 if n1 < n2, else 0\n");
  printf("GE : push 1 if n1 >= n2, else 0\n");
  printf("LE : push 1 if n1 <= n2, else 0\n");
  printf("EQ : push 1 if n1 == n2, else 0\n");
  printf("HELP : Print help of all operations\n");
  printf("swap : Swap n1 and n2\n");
  return(0);
}

static int op_swap(struct tokenStack *stack) {
	int v1;
	int v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v1);
	pushInt(stack, v2);
	return 0;
}

