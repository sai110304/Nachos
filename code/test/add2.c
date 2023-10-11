/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int i,j;
    // int pid;
    // int result;
    // result = Add(42, 54);
    // pid=Exec("../test/add");
    // Join(pid);
    // PrintStringUC("add2\n");
    // PrintNum(result);
    while(1){
        for(i=0;i<1000;i++)
        {
            for(j=0;j<100;j++);
        }
        PrintString("In ADD2 \n");
    }
}
