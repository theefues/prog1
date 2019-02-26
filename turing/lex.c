%{
#include <string.h>
int letter_count = 0, word_count = 0, number_count = 0, metacharacter_count = 0;
%}
%%
[0-9]   {++number_count; printf("Single-digit Number: %s\n",yytext);}
[a-zA-ZöüóőúűáéíÖÜÓŐÚÉÁŰÍ]      {++word_count; printf("Letter: %s\n",yytext);}
[0-9]+  {++word_count; ++number_count,
        printf("Multi-digit Number: %s\n",yytext);
        letter_count += strlen(yytext);}
[a-zA-Z0-9öüóőúűáéíÖÜÓŐÚÉÁŰÍ][a-zA-Z0-9öüóőúűáéíÖÜÓŐÚÉÁŰÍ]*     {++word_count; letter_count += strlen(yytext); printf("Word: %s\n",yytext);}
[\-/._,$><'"+:=?!%()#&@] {++metacharacter_count;
                printf("Meta-character: %s\n", yytext);}
%%
int main() {
        printf("Write your string: ");
        yylex();
        return 0;
}
