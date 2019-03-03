/* Fordításhoz:
$ lex -t lex.c > lex_l.c
$ gcc lex_l.c -o lex -lfl
$ ./lex

Output:
Type * to show stats.
Enter your string: ez 1 sor b
ez 1 sor
Word: ez
Single-digit Number: 1
Word: sor
Letter: b

*
Numbers: 1
Words: 2
Letters: 7
Meta-characters: 0

CTRL+D
All occured numbers: 1
$
*/
%{
#include <string.h>
int letter_count = 0, word_count = 0, number_count = 0, metacharacter_count = 0, stat = 0;
%}
%%
[0-9]   {++number_count; printf("Single-digit Number: %s\n",yytext);}
[a-zA-ZöüóőúűáéíÖÜÓŐÚÉÁŰÍ]      {++word_count; printf("Letter: %s\n",yytext);}
[0-9]+  {++number_count; printf("Multi-digit Number: %s\n",yytext);}
[0-9]+\.[0-9]+? {++number_count;
        printf("Fraction: %s\n",yytext);}
[a-zA-Z0-9öüóőúűáéíÖÜÓŐÚÉÁŰÍ][a-zA-Z0-9öüóőúűáéíÖÜÓŐÚÉÁŰÍ]*     {++word_count; letter_count += strlen(yytext); printf("Word: %s\n",yytext);}
[\-/._,$><'"+:=?!%()#&@] {++metacharacter_count;
                printf("Meta-character: %s\n", yytext);}
[*] {++stat; printf("Numbers: %d\nWords: %d\nLetters: %d\nMeta-characters: %d\n",number_count,word_count,letter_count,metacharacter_count);}
%%
int main() {
        printf("Type * to show stat.\nEnter your string: ");
        yylex();
        printf("All occured numbers: %d\n", number_count);
        return 0;

}
