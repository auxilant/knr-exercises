#define NUMBER '0'
#define COMMAND '$'
#define FUNCTION '~'
#define VARIABLE '?'
#define VAR_ASSIGNMENT '='
#define LAST_PRINTED '_'

int getop(char[]);

void push(double);
double pop(void);
void print_stack(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

int getch(void);
void ungetch(int);
