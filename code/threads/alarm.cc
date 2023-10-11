// alarm.cc
//	Routines to use a hardware timer device to provide a
//	software alarm clock.  For now, we just provide time-slicing.
//
//	Not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "alarm.h"
#include "main.h"
#include "thread.h"

//----------------------------------------------------------------------
// Alarm::Alarm
//      Initialize a software alarm clock.  Start up a timer device
//
//      "doRandom" -- if true, arrange for the hardware interrupts to
//		occur at random, instead of fixed, intervals.
//----------------------------------------------------------------------

Alarm::Alarm(bool doRandom) { 
    timer = new Timer(doRandom, this); 
    // sleepingProcess=NULL;
}

//----------------------------------------------------------------------
// Alarm::CallBack
//	Software interrupt handler for the timer device. The timer device is
//	set up to interrupt the CPU periodically (once every TimerTicks).
//	This routine is called each time there is a timer interrupt,
//	with interrupts disabled.
//
//	Note that instead of calling Yield() directly (which would
//	suspend the interrupt handler, not the interrupted thread
//	which is what we wanted to context switch), we set a flag
//	so that once the interrupt handler is done, it will appear as
//	if the interrupted thread called Yield at the point it is
//	was interrupted.
//
//	For now, just provide time-slicing.  Only need to time slice
//      if we're currently running something (in other words, not idle).
//----------------------------------------------------------------------

// void Alarm::WaitUntil(int x){
//     struct sleepDetails* sleepProcess=(struct sleepDetails*)malloc(sizeof(struct sleepDetails));
//     sleepProcess->nextProcess=sleepingProcess;
//     sleepProcess->timeLeft=x;
//     sleepProcess->process=kernel->currentThread;
//     sleepingProcess=sleepProcess;
// }
void Alarm::CallBack() {

    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    if (status != IdleMode) {
        interrupt->YieldOnReturn();
    }
    globalTime++;
    Thread *th=NULL;
    if(kernel->scheduler->sleepList.size()>0) th=kernel->scheduler->sleepList.top();
    while(th && th->wakeupTime<=globalTime){
        kernel->scheduler->sleepList.pop();
        kernel->scheduler->ReadyToRun(th);

        if(kernel->scheduler->sleepList.size()>0) th=kernel->scheduler->sleepList.top();
        else th=NULL;
    }
}

int Alarm::getTime(){
    return globalTime;
}