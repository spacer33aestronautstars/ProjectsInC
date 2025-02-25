//In this program we use Escape Sequence or Execution Characters of C Programming Language
#include<stdio.h>
#include <windows.h>
int main(){
    printf("C is the best programming language of that time isn't it \a. \nThere are so many other popular language in the world like\vJava\vC++\tPython.\n");
    printf("\\Presents a character with backslash ");
    printf(" \bMoves the cursor to the previous position of the current line\n");
    printf("Moves the cursor to beginning of the current line.\r");
    Beep(1000, 300);          // Windows API Beep
    printf("Vertical Tab Test: Hello\vWorld\n"); 
    printf("New Line Test: Hello\nWorld\n");
    return 0;
}