/*Jose Olivarez Phase 1
2/19/2017  CSCI 3333.06*/



#include <stdio.h>
#include <stdlib.h>

char LoadFileName(char* s) { // function loads the filename the user input using a pointer that we pass in our main.
    printf("I understand your absurd request!\n");
    printf("This function will load the file: ");
    char fname[25]; // starts at 5 because load
    int i=5;
    while (s[i] != '\0') {
      fname[i-5] = s[i];
      i= i+1;
    }
    fname[i-5] = '\0';
    printf("%s\n", fname);
}

void debug() { // later to be used no parameters
  printf("I understand your absurd request!\n");
}
void dumpstartend(char* s) { // supposed to display user input for the start ing and ending address.
  printf("I understand your absurd request!\n");
  char start[25];
  char end[25];
  int i=5;
  while (s[i] != ' ') {
    //printf("%c",s[i]);
    start[i-5] = s[i];
    i++;
  }
  start[i-5] = '\0';
  i = i+1;
  int startChar = i;
  printf("start: %s\n", start);// prints start address
  while (s[i] != '\0') {
    //printf("%c",s[i]);
    end[i-startChar] = s[i];
    i= i+1;
  }
  end[i-startChar] = '\0';
  printf("end: %s\n", end); // prints end
}
void execute() {
  printf("I understand your absurd request!\n"); // to be used later
}
void AssembleFileName(char* s)  { // assembles the user input and the prints it out
    printf("I understand your absurd request!\n");
    printf("This function will load the file: ");
    char fname[25];
    int i=9;
    while (s[i] != '\0') {
      fname[i-9] = s[i];
      i = i+1;
    }
    fname[i-9] = '\0';
    printf("%s\n", fname);
}

void doDirectory() {

  // Will perform the Directory function

  printf("\nThe following are the current directory contents:\n");

  system("ls");

}

void doHelp() { // gives the user a list of commands
  printf("\nLoad <filename>         --Loads the file called <filename>.\n");

  printf("Execute                 --Uses a computer simulation to execute a "

    "program previously loaded.\n");

  printf("Debug                   --Allows you to execute in debug mode.\n");

  printf("Dump start end      --Calls dump between <start> and <end>. "

    "(Note: start and end should be hexadecimal values.)\n");

  printf("Help                    --Prints  help prompt.\n");

  printf("Assemble <filename>     --Assembles a file called <filename>.\n");

  printf("Directory               --Lists the contents of the "

    "current directory.\n");

  printf("Exit                    --Terminates  the program.\n");

}
void parametersneeded() { //a function used whenever parameters are needed.
  printf("Parameters are needed");

}
void main() {
  printf("How are you doing man I am phase 1"); // welcome message
  printf("\n");
  int parameterssatisfied = 1;
  char s[30];
  int shouldContinue = 1;
  while (shouldContinue) {
    fgets(s, 30, stdin);
    if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't') // checks if the characters match the commands and then calls them as functions.
      shouldContinue = 0;
    else if (s[0] == 'h' && s[1] == 'e' && s[2] == 'l' && s[3] == 'p')
      doHelp();
    else if (s[0] == 'd' && s[1] == 'i' && s[2] == 'r' && s[3] == 'e' && s[4] == 'c' && s[5] == 't' && s[6] == 'o' && s[6] == 'r' && s[7] == 'y')
      doDirectory();
    else if (s[0] == 'l' && s[1] == 'o' && s[2] == 'a' && s[3] == 'd') {
      LoadFileName(s);
      //char lfnparameter1[64];
      //char lfnparameter2[64];
      //fgets(lfnparameters, 64, stdin);
      //if (lfnparameters == ' ') {
      //  parametersneeded();
      //  parameterssatisfied = 0;
      //} else if (lfnparameters != NULL) {
      //  parameterssatisfied = 1;
      //  printf(lfnparameters);
    } else if (s[0] == 'e' && s[1] == 'x' && s[2] == 'e' && s[3] == 'c' && s[4] == 'u' && s[5] == 't' && s[6] == 'e')
      execute();
    else if (s[0] == 'd' && s[1] == 'e' && s[2] == 'b' && s[3] == 'g')
      debug();
    else if (s[0] == 'a' && s[1] == 's' && s[2] == 's' && s[3] == 'e' && s[4] == 'm' && s[5] == 'b' && s[6] == 'l' && s[7] == 'e' && s[8] == ' ')
      AssembleFileName(s);
    else if (s[0] == 'd' && s[1] == 'u' && s[2] == 'm' && s[3] == 'p' && s[4] == ' ')
      dumpstartend(s);
    else {
      printf("type out another statement \n");
    }
  }
  //for(int i = 0; i< 2; i++)
  //{
  //gets(s);
  //fgets(s, sizeof(s), stdin);
  //}
  /*char *word = strtok(s, " .");
	char *secondword = strtok(NULL, " .");
  char *thirdword = strtok(NULL, " .");
  printf("%s\n", word);
	printf("%s\n", secondword);
	printf("%s\n", thirdword);
	*/
}
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "errorHandler.h"
#include <ctype.h>
//#include <conio.h>
#include <stdlib.h>

void checkLabel();
void checkOpcode();
void processLine();
void itoa(int n, char s[]);

struct optab {
	//char code[10];
	//char objcode[10];
	char* code;
	char* objcode;
} myoptab[25] = { { "ADD", "18" }, { "AND", "58" }, { "COMP", "28" }, { "DIV",
		"24" }, { "J", "3C" }, { "JEQ", "30" }, { "JGT", "34" },
		{ "JLT", "38" }, { "JSUB", "48" }, { "LDA", "00" }, { "LDCH", "50" }, {
				"LDL", "08" }, { "LDX", "04" }, { "MUL", "20" }, { "OR", "44" },
		{ "RD", "D8" }, { "RSUB", "4C" }, { "STA", "0C" }, { "STCH", "54" }, {
				"STL", "14" }, { "STX", "10" }, { "SUB", "1C" }, { "TD", "E0" },
		{ "TIX", "2C" }, { "WD", "DC" } };

struct symtab {
	char symbol[10];
	int addr;
} mysymtab[500];

const int numberOfOpcodes = 25;
unsigned int startaddr, locctr;
int symcount = 0, length, errorFlag = 0, numberOfErrors = 0, errors[500];
char line[160], label[8], opcode[8], operand[10], programname[10];

/*ASSEMBLER PASS 1 */
void PASS1() {
	FILE *input, *inter;
	input = fopen("input.asm", "r");
	inter = fopen("inter.txt", "w");
	printf("LOCATION LABEL\tOPERAND\tOPCODE\n");
	printf("_____________________________________");

	fgets(line, 160, input);
	processLine();

	if (!strcmp(opcode, "START")) {
		//startaddr = atoi(operand);
		startaddr = strtol(operand, NULL, 16);
		if ((errno != 0 && startaddr == 0)
				|| (startaddr == 0 && operand[0] != '0' && operand[1] == '\0')) {
			errorFlag = 1;
			errors[numberOfErrors++] = illegalStartOperand;
		}
		locctr = startaddr;
		strcpy(programname, label);
		fprintf(inter, "%s", line);
		fgets(line, 160, input);
	} else {
		programname[0] = '\0';
		startaddr = 0;
		locctr = 0;
	}
	printf("\n %x\t %s\t%s\t %s", locctr, label, opcode, operand);

	while (strcmp(opcode, "END") != 0) {
		processLine();
		int oldLocctr = locctr;
		printf("\n %x\t %s \t%s\t %s", locctr, label, opcode, operand);
		if (label[0] != '\0')
			checkLabel();
		if (line[0] != '.')
			checkOpcode();
		fprintf(inter, "%x\t %s\t %s\t %s\n", oldLocctr, label, opcode,
				operand);
		fgets(line, 160, input);
	}

	printf("\n %x\t\t%s", locctr, line);
	fprintf(inter, "%s", line);

	fprintf(inter, "Symbol table:\n");
	for (int i = 0; i < 500; i++) {
		if (mysymtab[i].symbol[0] != '\0')
			fprintf(inter, "mysymtab[%x] = symbol = %s, address = %x\n", i,
					mysymtab[i].symbol, mysymtab[i].addr);
	}

	fprintf(inter, "\nError list:\n");
	for (int i = 0; i < numberOfErrors; i++) {
		fprintf(inter, "Error %d = %s\n", i, errorList[errors[i]]);
	}

	length = locctr - startaddr;
	fprintf(inter, "\nProgram length = %x", length);

	if (length > 32768) {
		errorFlag = 1;
		errors[numberOfErrors++] = progTooLong;
	}

	fclose(inter);
	fclose(input);
}

/*
 void PASSTWO() {
 FILE *inter, *output;
 char record[30], part[8], value[5];
 int currentlength = 0, foundopcode, foundoperand, check, operandadder,
 recadress = 0;
 inter = fopen("inter.txt", "r");
 symbol = fopen("input.txt", "r");
 output = fopen("output.txt", "w");
 fgets(line, 160, inter);
 processLine();
 if(!strcmp(opcode, "START")
 fgets(line, 20, inter);
 printf("\n\nCorresponding Object code is..\n");
 printf("\nH^ %s ^ %d ^ %d ", programname, startaddr, length);
 fprintf(output, "\nH^ %s ^ %d ^ %d ", programname, startaddr,
 length);
 recaddr = startaddr;
 record[0] = "\0";
 while (strcmp(line, "END") != 0) {
 operandaddr = foundoperand = foundopcode = 0;
 value[0] = part[0] = '\0';

  processLine();
  for (chk = 0; chk < 3; chk++)   {
 if (!strcmp(opcode, myoptab[chk].code)) {
 foundopcode = 1;
 strcpy(part, myoptab[chk].objcode);
 if (operand[0] != '\0') {
 for (chk = 0; chk < symcount; chk++)
   if (!strcmp(mysymtab[chk].symbol,
 operand))   {
 itoa(mysymtab[chk].addr, value);
 strcat(part, value);
 foundoperand = 1;
 }
 if (!foundoperand)
 strcat(part, "err");
 }
 }
 }
 if (!foundopcode) {
 if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD")
 || strcmp(opcode, "RESB")) {
 strcat(part, operand);
 }
 }
 if ((currtxtlen + strlen(part)) <= 8)
 //This step was having buffer overflow issue since part[6]
 //was defined previously which i corrected to part[8].
 //Because of this first two bytes of stack are getting lost
 {
 strcat(record, "^");
 strcat(record, part);
 currtxtlen += strlen(part);
 } else {
 printf("\nT^ %d ^%d %s", recaddr, currtxtlen, record);
 fprintf(output, "\nT^ %d ^%d %s", recaddr, currtxtlen,
 record);
 recaddr += currtxtlen;
 currtxtlen = strlen(part);
 strcpy(record, part);
 }
 fgets(line, 20, inter);
 }
 printf("\nT^ %d ^%d %s", recaddr, currtxtlen, record);
 fprintf(output, "\nT^ %d ^%d %s", recaddr, currtxtlen, record);
 printf("\nE^ %d\n", startaddr);
 fprintf(output, "\nE^ %d\n", startaddr);
 fclose(inter);
 fclose(output);
 }
 */

void processLine() {
	char buff[24];
	int i, j = 0;
	label[0] = opcode[0] = operand[0] = '\0';
	//fgets(line, 160, input);
	if (line[0] != '.') {
		if (!isspace(line[0])) {
			// there is a label, so parse it
			i = 0;
			do {
				buff[i] = toupper(line[i]);
				i++;
			} while (!isspace(line[i]));
			buff[i] = '\0';
			strcpy(label, buff);
		}

		// skip whitespace
		do {
			i++;
		} while (isspace(line[i]));

		// store the character number of the start of the instruction
		j = i;
		do {
			buff[i - j] = toupper(line[i]);
			i++;
		} while (!isspace(line[i]));
		buff[i - j] = '\0';
		strcpy(opcode, buff);

		// skip whitespace
		do {
			i++;
		} while (isspace(line[i]));

		// store the character number of the start of the operand
		j = i;
		do {
			buff[i - j] = toupper(line[i]);
			i++;
		} while (!isspace(line[i]));
		buff[i - j] = '\0';
		strcpy(operand, buff);

		//printf("\n");
		//printf("label = %s\n", label);
		//printf("opcode = %s\n", opcode);
		//printf("operand = %s\n", operand);
		//printf("\n");
	}
}

int isValidSymbol(char* s) {
	int len = strlen(s);

	if (s[len - 2] == ',' && s[len - 1] == 'X')
		s[len - 2] = '\0';

	//printf("\n***buffer** %s", s);

	if (s[0] < 'A' || s[0] > 'Z' || strlen(s) > 6) {
		//if (strlen(s) > 6)
		//  if (s[strlen(s)-3] == ',' && s[strlen(s)-2] == 'X')
		//    return 1;
		return 0;
	} else {
		for (int i = 1; i < strlen(s); i++) {
			if (!(s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')) {
				return 0;
			}
		}
		return 1;
	}
}

void checkLabel() {
	int k, dupsym = 0;
	// check if valid symbol
	if (isValidSymbol(label) == 0) {
		// set error flag
		errorFlag = 1;
		errors[numberOfErrors++] = illegalLabel;
	}
	for (k = 0; k < symcount; k++)
		if (!strcmp(label, mysymtab[k].symbol)) {
			mysymtab[k].addr = -1;
			dupsym = 1;
			break;
		}
	if (dupsym) {
		errorFlag = 1;
		errors[numberOfErrors++] = duplicateLabel;
	} else {
		strcpy(mysymtab[symcount].symbol, label);
		mysymtab[symcount++].addr = locctr;
		if (symcount > 500) {
			// set error flag
			errorFlag = 1;
			errors[numberOfErrors++] = tooManySymbols;
			symcount--;
		}
	}
}

void checkOpcode() {
	int k = 0, found = 0;
	for (k = 0; k < numberOfOpcodes; k++)
		if (!strcmp(opcode, myoptab[k].code)) {
			locctr += 3;
			found = 1;
			// check for validity of storage operands
			if ((opcode[0] == 'S' && opcode[1] == 'T') ||
					(opcode[0] == 'L' && opcode[1] == 'D')) {
				//if (operand[strlen(operand)-3] == ',' && operand[strlen(operand)-2] == 'X') {
				////memcpy(operand, &operand, strlen(operand) - 2);
				//  operand[strlen(operand)-2] == '\0';
				//  printf("***** %s\n", operand);
				//}
				if (!isValidSymbol(operand)) {
					printf("\n***storage operand = %s", operand);
					errorFlag = 1;
					errors[numberOfErrors++] = illegalOperand;
				}
			}
			break;
		}
	if (!found) {
		if (!strcmp(opcode, "WORD"))
			locctr += 3;
		else if (!strcmp(opcode, "RESW"))
			locctr += (3 * atoi(operand));
		else if (!strcmp(opcode, "RESB"))
			locctr += atoi(operand);
		else if (!strcmp(opcode, "BYTE")) {
			int numberOfBytes = 0;
			if (operand[0] == 'C') {
				do {
				} while (operand[++numberOfBytes + 1] != '\'');
				numberOfBytes -= 1;
			} else if (operand[0] == 'X') {
				do {
				} while (operand[++numberOfBytes + 1] != '\'');
				numberOfBytes -= 1;
			} else {
				// set error flag
				errorFlag = 1;
				errors[numberOfErrors++] = illegalOperand;
				//printf("\nERROR: opcode = %s\n", opcode);
			}
			locctr += numberOfBytes;
			//printf("\nNUMBER OF BYTES = %d", numberOfBytes);
		} else if (!strcmp(opcode, "END")) {
			if (!isValidSymbol(operand)) {
				// set error flag
				errorFlag = 1;
				errors[numberOfErrors++] = illegalEndOperand;
			}
		} else {
			// set error flag
			errorFlag = 1;
			errors[numberOfErrors++] = illegalInstruction;
		}

	}
	if (locctr == 8192)
		printf("***ERROR\n");
}

void itoa(int n, char s[])

{
	int i, j, sign;
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do {
		/* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0);
	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	/* reverse the string */
	for (j = 0; j < i / 2; j++) {
		char c = s[j];
		s[j] = s[i - j - 1];
		s[i - j - 1] = c;
	}
	//printf("reverse = %s\n", s);
}

int main() {
	//char s[10];
	//itoa(2361,s);
	//printf("itoa() = %s\n", s);

	PASS1();

	//PASS2();
	//getch();
}