/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int i,j;
    //PrintString("add\n");
    /* not reached */    
    //PrintString("Bye");
    PrintString("HELLO\n");
    Exec("add2");
    Sleep(50000);
    while(1){
        for(i=0;i<1000;i++)
        {
            for(j=0;j<100;j++);
        }
        PrintString("In ADD1 \n");
    }
}
