#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

const int MAX_MEM_SIZE  = (1 << 13);

void fetchStage(int *icode, int *ifun, int *rA, int *rB, wordType *valC, wordType *valP) {
    // Get command location and value
    wordType pc = getPC();
    byteType byte = getByteFromMemory(pc);

    // Get first and second command
    *icode = (byte >> 4) & 0xf;
    *ifun = byte & 0xf;

    // For halts and nops
    if(*icode == HALT || *icode == NOP || *icode == RET){
        // Increase pc counter by 1 instruction set
        *valP = pc + 1;

        // If halted, set halt status
        if(*icode == HALT)
            setStatus(STAT_HLT);
    }

    // For 'rr' move, opq, push, and pop
    else if(*icode == OPQ || *icode == RRMOVQ || *icode == PUSHQ || *icode == POPQ){
        byte = getByteFromMemory(pc + 1);
        *rA = (byte >> 4) & 0xf;
        *rB = byte & 0xf;

        *valP = pc + 2;
    }

    // For 'i' and 'm' moves
    else if(*icode == IRMOVQ || *icode == RMMOVQ || *icode == MRMOVQ){
        // get memory address and rA, rB, valC
        byte = getByteFromMemory(pc + 1);
        *rA = (byte >> 4) & 0xf;
        *rB = byte & 0xf;
        *valC = getWordFromMemory(pc + 2);

        // increase counter
        *valP = pc + 10;
    }

    // For jumps and call
    else if(*icode == JXX || *icode == CALL){
        *valC = getWordFromMemory(pc + 1);
        *valP = pc + 9;
    }

}

void decodeStage(int icode, int rA, int rB, wordType *valA, wordType *valB) {
    // For halts, nop, 'i' move, and jump
    if(icode == HALT || icode == NOP || icode == IRMOVQ || icode == JXX)
        return;

    // For opq and rm move
    else if(icode == OPQ || icode == RMMOVQ){
        *valA = getRegister(rA);
        *valB = getRegister(rB);
    }

    // For rr move
    else if(icode == RRMOVQ)
        *valA = getRegister(rA);

    // For mr move
    else if(icode == MRMOVQ)
        *valB = getRegister(rB);

    // For push
    else if(icode == PUSHQ){
        *valA = getRegister(rA);
        *valB = getRegister(RSP);
    }

    // For pop or return
    else if(icode == POPQ || icode == RET){
        *valA = getRegister(RSP);
        *valB = getRegister(RSP);
    }

    // For call
    else if(icode == CALL)
        *valB = getRegister(RSP);
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
    // For halts and nop
    if(icode == HALT || icode == NOP)
        return;

    // For opq
    else if(icode == OPQ){
        bool cond = FALSE;

        // For Add, Sub
        if(ifun == ADD || ifun == SUB){
            if(ifun == ADD)
                *valE = valB + valA;
            else {
                *valE = valB - valA;
                valA = -valA;
            }

            cond = (((valA < 0) && (valB < 0)) && (*valE >= 0)) || (((valA > 0) && (valB > 0)) && (*valE < 0));

        }

        // For AND
        else if (ifun == AND)
            *valE = valB & valA;

        // For XOR
        else if (ifun == XOR)
            *valE = valB ^ valA;

        // Set flags
        setFlags(*valE < 0, *valE == 0, cond);
    }

    // For 'rr' move
    else if(icode == RRMOVQ)
        *valE = valA;

    // For 'i' move
    else if(icode == IRMOVQ)
        *valE = valC;

    // For 'm' moves
    else if(icode == MRMOVQ || icode == RMMOVQ)
        *valE = valB + valC;

    // For push and call
    else if(icode == PUSHQ || icode == CALL)
        *valE = valB - 8;

    // For pop and return
    else if(icode == POPQ || icode == RET)
        *valE = valB + 8;

    // For jump
    else if(icode == JXX)
        *Cnd = Cond(ifun);
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
    // For halt, nop, opq, 'rr' and 'i' moves, and jump
    if(icode == HALT || icode == NOP || icode == OPQ || icode == RRMOVQ || icode == IRMOVQ || icode == JXX)
        return;

    // For 'rm' move and push
    else if(icode == RMMOVQ || icode == PUSHQ)
        setWordInMemory(valE, valA);

    // For 'mr' move
    else if(icode == MRMOVQ)
        *valM = getWordFromMemory(valE);

    // For pop and return
    else if(icode == POPQ || icode == RET)
        *valM = getWordFromMemory(valA);

    // For call
    else if(icode == CALL)
        setWordInMemory(valE, valP);
}

void writebackStage(int icode, int rA, int rB, wordType valE, wordType valM) {
    // For halt, nop, 'rm' move, jump
    if(icode == HALT || icode == NOP || icode == RMMOVQ || icode == JXX)
        return;

    // For opq, 'rr' and 'i' moves
    else if(icode == OPQ || icode == RRMOVQ || icode == IRMOVQ)
        setRegister(rB, valE);

    // For 'mr' move
    else if(icode == MRMOVQ)
        setRegister(rA, valM);

    // For push, call, and return
    else if(icode == PUSHQ || icode == CALL || icode == RET)
        setRegister(RSP, valE);

    // For pop
    else if(icode == POPQ){
        setRegister(RSP, valE);
        setRegister(rA, valM);
    }

}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {
    // For halt, nop, opq, moves, push, pop
    if(icode == HALT || icode == NOP || icode == OPQ || icode == RRMOVQ || icode == IRMOVQ || icode == RMMOVQ || icode == MRMOVQ || icode == PUSHQ || icode == POPQ)
        setPC(valP);

    // For jump
    else if(icode == JXX)
        setPC(Cnd ? valC : valP);

    // For call
    else if(icode == CALL)
        setPC(valC);

    // For return
    else if(icode == RET)
        setPC(valM);
}

void stepMachine(int stepMode) {
  /* FETCH STAGE */
  int icode = 0, ifun = 0;
  int rA = 0, rB = 0;
  wordType valC = 0;
  wordType valP = 0;
 
  /* DECODE STAGE */
  wordType valA = 0;
  wordType valB = 0;

  /* EXECUTE STAGE */
  wordType valE = 0;
  bool Cnd = 0;

  /* MEMORY STAGE */
  wordType valM = 0;

  fetchStage(&icode, &ifun, &rA, &rB, &valC, &valP);
  applyStageStepMode(stepMode, "Fetch", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  decodeStage(icode, rA, rB, &valA, &valB);
  applyStageStepMode(stepMode, "Decode", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  executeStage(icode, ifun, valA, valB, valC, &valE, &Cnd);
  applyStageStepMode(stepMode, "Execute", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  memoryStage(icode, valA, valP, valE, &valM);
  applyStageStepMode(stepMode, "Memory", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  writebackStage(icode, rA, rB, valE, valM);
  applyStageStepMode(stepMode, "Writeback", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  pcUpdateStage(icode, valC, valP, Cnd, valM);
  applyStageStepMode(stepMode, "PC update", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  incrementCycleCounter();
}

/** 
 * main
 * */
int main(int argc, char **argv) {
  int stepMode = 0;
  FILE *input = parseCommandLine(argc, argv, &stepMode);

  initializeMemory(MAX_MEM_SIZE);
  initializeRegisters();
  loadMemory(input);

  applyStepMode(stepMode);
  while (getStatus() != STAT_HLT) {
    stepMachine(stepMode);
    applyStepMode(stepMode);
#ifdef DEBUG
    printMachineState();
    printf("\n");
#endif
  }
  printMachineState();
  return 0;
}