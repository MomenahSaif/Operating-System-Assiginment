#include <stdio.h>

enum OpCode 
{ADD,SUB,LOAD,STORE,HALT};

int main() {
    int memory[20] = {0}; // Initialize memory with zeros
    int PC = 0, MAR = 0, MBR = 0, IR = 0, ACC = 0; // registers intilized with zero to avoid garbage values
    int InstNo=1;//no of instruction
    int opcode=0,operand1=0,operand2=0;
    
    // Set initial values to avoid non zero values
    memory[6] = 42; 
    memory[10] = 30; 
    ACC = 10; 
    
    // Load instructions into memory
    memory[0] = (ADD << 24) | (6 << 16) | 10; // ADD [6], [10]
    memory[1] = (SUB << 24) | (6 << 16) | 10; // SUB [6], [10]
    memory[2] = (HALT << 24); // Halt the program

    while (1) {
        // Fetch next instruction from memory
        MAR = PC;
        MBR = memory[MAR]; 
        IR = MBR; 

       
        printf("Before execution of instruction no %d:\n",InstNo);
        printf("PC=%d MAR=%d MBR=%d IR=%d ACC=%d\n", PC, MAR, MBR, IR, ACC);
        printf("Memory: ");
        for (int i = 0; i < 20; i++) {
            printf("[%d]=%d ", i, memory[i]);
        }
        printf("\n\n");

        // Extract the opcode and operands from the instruction
        opcode = IR >> 24;
        if (opcode == HALT)//check Halt
            break;       
            
         operand1 = (IR >> 16) & 0xFF; // assign memory address
         operand2 = IR & 0xFFFF;

        // Check opcode of operation
        switch (opcode) {
         case ADD:
                  ACC += memory[operand1]; 
                         break;
         case SUB:
                 ACC -= memory[operand1]; 
                        break;
         case LOAD:
                   ACC = memory[operand1]; 
                         break;
         case STORE:
                   memory[operand1] = ACC; 
                          break;
        }

        
        printf("After execution of instruction no %d:\n",InstNo);
        printf("PC=%d MAR=%d MBR=%d IR=%d ACC=%d\n", PC, MAR, MBR, IR, ACC);
        printf("Memory: ");
        for (int i = 0; i < 20; i++) {
            printf("[%d]=%d ", i, memory[i]);
        }
        printf("\n\n");

        PC++; // add to PC for next instruction
        InstNo++;// next instruction number
    }

    return 0;
}
