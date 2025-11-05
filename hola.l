%%
/* PATTERN */                    /* ACTION */
"*"                              return OP_MUL;
"="                              return OP_ASSIGN;
[a-zA-Z_][a-zA-Z0-9_]*           return ASCII_IDENTIFIER;
[0-9]+                           return CONST_NUMBER;
\"([^\\\"\n]|\\[\x20-\xff])*\"   return CONST_STRING;
[ \t\r\n]+                       /* no action: ignore all white space */
"//".*                           /* no action: ignore single-line comments */
"/*"([^*]|\*+[^*/])*\*+"/"       /* no action: ignore multi-line comments */
%%

