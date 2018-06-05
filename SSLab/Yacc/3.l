%{
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+		{yylval = atoi(yytext); return NUM;}//works only for positive numbers
\n			return NL;
.			return yytext[0];
%%

int yywrap()
{
	return 1;
}
