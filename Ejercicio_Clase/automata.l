%%
";"                             return SEMICOLON;
"("                             return OPEN_PAR;
")"                             return CLOSE_PAR;
"="                             return ASSIGN;
"=="                            return OP_REL_EQUAL;
"!="                            return OP_REL_DIFF;
"<"                             return OP_REL_LESS;
">"                             return OP_REL_GREATER;
"<="                            return OP_REL_LESS_EQUAL;
">="                            return OP_REL_GREATER_EQUAL;
[0-9]+                          return NUMBER;
[a-zA-Z_][a-zA-Z0-9_]*          return VARIABLE;
[ \n\t\r]                       /* Se supone que ignora */
%%