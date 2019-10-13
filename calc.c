// include parts of the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>


// type declaration for stack of doubles
struct double_stack {
  double * items;
  int max_size;
  int top;
};

// prototypes of functions that operate on the double stack

  // create a new empty stack
struct double_stack * double_stack_new(int max_size) {
  struct double_stack * result;
  // allocate space for the stack header
  result = malloc(sizeof(struct double_stack));
  result->max_size = max_size;
  result->top = 0;
  // allocate space for the data stored in the stack
  result->items = malloc(sizeof(double)*max_size);
  // return a pointer to the newly-allocated stack
  return result;
}
// end of code


// push a value onto the stack
void double_stack_push(struct double_stack * this, double value){
  this->top = this->top + sizeof(double);
  *(this->items + this->top) = value;}

// pop a value from the stack
double double_stack_pop(struct double_stack * this){
  double poppedValue = *(this->items + this->top);
  this->top = this->top - sizeof(double);
  return poppedValue;
}
//Apply Operator
void apply_operator(struct double_stack * stack, char operator){
  double a = double_stack_pop(stack);
  double b = double_stack_pop(stack);
  switch(operator){
	  case '+': double_stack_push(stack, a+b); break;
	  case 'x': double_stack_push(stack, a*b); break;
	  case '/': double_stack_push(stack, b/a); break;
	  case '-': double_stack_push(stack, b-a); break;
	  case '^': double_stack_push(stack, pow(b, a)); break;
	  default: break;}//switch end
}
//Postfix Calc
double evaluate_postfix_expression(char ** argv, int argc){
  for(int i = argc-1; i>=0; i--){printf("%i: %s\n",i , argv[i]);}
  struct double_stack * stack;
  stack = double_stack_new(argc);
  double value;
    for (int i=0; i<argc; i++){
	if (strlen(argv[i])==1){//Could be a Operator if it's only one character long
	  switch(argv[i][0]){
	  case '+':
	  case 'x':
	  case '/':
	  case '-':
	  case '^':
	    apply_operator(stack, argv[i][0]);
	    break;
	  default:
		value = atof(argv[i]);
		double_stack_push(stack, value);
		break;
	  }//switch end 'apply_operator':

    	} else {
	    value =atof(argv[i]);
	    double_stack_push(stack, value);
	}//if end
  }//for end
value = double_stack_pop(stack);
return(value);
}



//isNumber function
int isNumber(char* characterArray){
  for(int i = 0; i<strlen(characterArray); i++){
    if (!(characterArray[i] <= '9' && characterArray[i] >= '0')) return 0;
    else return 1;
  } 
}

//operatorPrecendence
int operatorPrecendence(int operator){
   switch(operator){
	case '+':
	case '-':
	  return 1;
	case 'x':
	case '/':
	  return 2;
	default: return 3;
   }
}


//Infix Calc
float evaluate_infix_expression(char ** argv, int argc){
 struct double_stack * operator_stack  = double_stack_new(argc);
 char ** postfix_String = malloc(sizeof(double)*argc);
 int postfix_String_Index = 0;
  for (int i=0; i<argc; i++) {
      printf("Hit for loop for %s\n", argv[i]);
  if (isNumber(argv[i])){
    postfix_String[postfix_String_Index] = argv[i];
    postfix_String_Index++;
  }//if end
  else if (argv[i][0] == '(') {												// if '('
    double_stack_push(operator_stack, argv[i][0]);
  }
  else if ((argv[i][0] == '+') || (argv[i][0] == 'x')||(argv[i][0] == '/')||(argv[i][0] == '-')||(argv[i][0] == '^')) {	//if 'operator'
	int operatorTag = operatorPrecendence(argv[i][0]);
	printf("Hit operator if statement. Operator Tag is %i\n", operatorTag);
    for(int j = ((operator_stack->top)/sizeof(double)); j>0 && ((operator_stack->top)/sizeof(double) != 0); j-=16){
        printf("Got into second for loop\n");
	if((operator_stack->items[j] == 94) && (operatorTag!=3)){
	 printf("%s", postfix_String[postfix_String_Index-1]);
	 postfix_String[postfix_String_Index] = "^";
	 double_stack_pop(operator_stack);
	 postfix_String_Index++;
	 continue;
	}
	else if((operator_stack->items[j] == 120.0 /*x*/ || operator_stack->items[j] == 47.0/*/*/) && operatorTag<=2){
	    printf("Got into proper loop for + or -.\n");
	   if(operator_stack->items[j] == 'x'){
	          printf("%s", postfix_String[postfix_String_Index-1]);
	          postfix_String[postfix_String_Index] = "x";
	   	      double_stack_pop(operator_stack);
	          postfix_String_Index++;
	          continue;
	   } else if (operator_stack->items[j] == '/'){
	          printf("%s", postfix_String[postfix_String_Index-1]);
	          postfix_String[postfix_String_Index] = "/";
	   	      double_stack_pop(operator_stack);
	          postfix_String_Index++;
	          continue;
	   } else printf("Weird thing in the infix");
     }//if end
    }//for end
     printf("Hit operator: %s\n", argv[i]);
     double_stack_push(operator_stack, argv[i][0]);
  }
  else if ( argv[i][0] == ')') {											//if ')'
     while (operator_stack->items[((operator_stack->top)/sizeof(double))] != '('){
      double_stack_pop(operator_stack);
     }double_stack_pop(operator_stack);
  }//if end
 //printf("%s", postfix_String[postfix_String_Index]);
}//for end
 printf("Operator stack: %i\n", operator_stack->top);
 while(operator_stack->top != 0){
     int endoperator = double_stack_pop(operator_stack);
     printf("Popping operator Stack of: %i\n", endoperator);
     switch(endoperator){
	case '+': 
	          postfix_String[postfix_String_Index] = "+";
	          postfix_String_Index++;
	          break;
	case '-':
		      postfix_String[postfix_String_Index] = "-";
	          postfix_String_Index++;
	          break;
	case 'x':
		      postfix_String[postfix_String_Index] = "x";
	          postfix_String_Index++;
	          break;
	case '/':
		      postfix_String[postfix_String_Index] = "/";
	          postfix_String_Index++;
	          break;
	 case '^':
		      postfix_String[postfix_String_Index] = "^";
	          postfix_String_Index++;
	          break;
	default: break;
 }
}
 return evaluate_postfix_expression(postfix_String, postfix_String_Index);
}//function end




// main function for a simple bench calculator with command
// line inputs
int main(int argc, char ** argv) {
  if ( argc == 1 ) {
    // command line contains only the name of the program
    printf("Error: No command line parameters provided\n");
    printf("Usage: %s postfix|infix <expression>\n", argv[0]);
    exit(1);
  }
  else if ( argc == 2 ) {
    // command line contains name of prog and one other parameter
    printf("Error: No expression to evaluate provided\n");
    printf("Usage: %s postfix|infix <expression>\n", argv[0]);
    exit(1);
  }
  else {
    // command line has enough parameters for an expression
    double result;
    if ( strcmp(argv[1], "postfix") == 0 ) {
      // pass the command line parameters, but with the first two removed
      result = evaluate_postfix_expression(argv+2, argc-2);
      printf("Result is %lf\n", result);
    }
    else if ( strcmp(argv[1], "infix") == 0 ) {
      // pass the command line parameters, but with the first two removed
      result = evaluate_infix_expression(argv+2, argc-2);
      printf("Result is %lf\n", result);
    }
    else {
      printf("Error: You must specify whether the expression is infix or postfix\n");
      printf("Usage: %s postfix|infix <expression>\n", argv[0]);
      exit(1);
    }

  return 0;
  }
}
// end of code
