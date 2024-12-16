#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAX_LABEL_SIZE 50

// Structure to hold instruction details
typedef struct {
    char label[MAX_LABEL_SIZE];
    char opcode[10];
    char operand[10];
} Instruction;

// Lookup tables for opcode and operand conversion
const char* opcodes[] = {"ADD", "SUB", "MOV", "MUL", "DIV"};
const char* registers[] = {"AX", "BX", "CX", "DX"};

int get_opcode_code(char *opcode) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(opcode, opcodes[i]) == 0)
            return i;
    }
    return -1; // Invalid opcode
}

int get_register_code(char *reg) {
    for (int i = 0; i < 4; i++) {
        if (strcmp(reg, registers[i]) == 0)
            return i;
    }
    return -1; // Invalid register
}

// Function to parse and process the instruction
void process_instruction(Instruction *instr, int line_no) {
    int opcode_code = get_opcode_code(instr->opcode);
    int reg_code = get_register_code(instr->operand);

    if (opcode_code == -1) {
        printf("Error at line %d: Invalid opcode %s\n", line_no, instr->opcode);
        return;
    }
    
    if (reg_code == -1) {
        printf("Error at line %d: Invalid operand %s\n", line_no, instr->operand);
        return;
    }

    printf("Machine code for line %d: ", line_no);
    printf("%02X ", opcode_code);
    printf("%02X\n", reg_code);
}

// Function to parse the assembly code and convert to machine code
void assemble_code(FILE *input_file) {
    char line[100];
    int line_no = 1;
    Instruction instr;
    
    while (fgets(line, sizeof(line), input_file)) {
        // Clear the instruction struct for each line
        memset(&instr, 0, sizeof(instr));
        
        // Parse label, opcode, and operand
        sscanf(line, "%s %s %s", instr.label, instr.opcode, instr.operand);
        
        if (strlen(instr.opcode) == 0) {
            continue; // Skip empty lines
        }

        // Process the instruction
        process_instruction(&instr, line_no);
        line_no++;
    }
}

int main() {
    FILE *input_file;
    char filename[50];

    // Input assembly file name
    printf("Enter the assembly code file name: ");
    scanf("%s", filename);
    
    input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    assemble_code(input_file);
    
    fclose(input_file);
    return 0;
}
