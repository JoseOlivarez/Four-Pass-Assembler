//jose olivarez 20290204
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "errorHandler.h"
//#include <ctype.h>
//#include <conio.h>

void checkLabel();
void checkOpcode();
void processLine();
void itoa(int n, char s[]);

struct optab
{
	//char code[10];
	//char objcode[10];
	char* code;
	char* objcode;
}myoptab[25] = {
	{ "ADD","18" },
	{ "AND","58" },
	{ "COMP","28" },
	{ "DIV", "24" },
	{ "J", "3C" },
	{ "JEQ", "30" },
	{ "JGT", "34" },
	{ "JLT", "38" },
	{ "JSUB", "48" },
	{ "LDA", "00" },
	{ "LDCH","50" },
	{ "LDL", "08" },
	{ "LDX", "04" },
	{ "MUL", "20" },
	{ "OR", "44" },
	{ "RD", "D8" },
	{ "RSUB", "4C" },
	{ "STA", "0C" },
	{ "STCH", "54" },
	{ "STL", "14" },
	{ "STX", "10" },
	{ "SUB", "1C" },
	{ "TD", "E0" },
	{ "TIX", "2C" },
	{ "WD", "DC" }
};

struct symtab {
	char symbol[10];
	int addr;
}mysymtab[500];

const int numberOfOpcodes = 25;
long startaddr, locctr;
int symcount = 0, length, errorFlag = 0, numberOfErrors = 0, errors[500];
char line[160], label[8], opcode[8], operand[8], programname[10];

/*ASSEMBLER PASS 1 */
void PASS1()
{
	FILE *input, *inter;
	input = fopen("input.asm", "r");
	inter = fopen("inter.txt", "w");
	printf("LOCATION LABEL\tOPERAND\tOPCODE\n");
	printf("_____________________________________");

	fgets(line, 160, input);
	processLine();

	if (!strcmp(opcode, "START"))
	{
		//startaddr = atoi(operand);
		startaddr = strtol(operand, NULL, 16);
		if ((errno != 0 && startaddr == 0) || (startaddr == 0 && operand[0] != '0' && operand[1] == '\0')) {
			errorFlag = 1;
			errors[numberOfErrors++] = illegalStartOperand;
		}
		locctr = startaddr;
		strcpy(programname, label);
		fprintf(inter, "%s", line);
		fgets(line, 160, input);
	}
	else
	{
		programname[0] = '\0';
		startaddr = 0;
		locctr = 0;
	}
	printf("\n %d\t %s\t%s\t %s", locctr, label, opcode, operand);

	while (strcmp(opcode, "END") != 0)
	{
		processLine();
		int oldLocctr = locctr;
		printf("\n %d\t %s \t%s\t %s", locctr, label, opcode, operand);
		if (label[0] != '\0')
			checkLabel();
		if (line[0] != '.')
			checkOpcode();
		fprintf(inter, "%d\t %s\t %s\t %s\n", oldLocctr, label, opcode, operand);
		fgets(line, 160, input);
	}

	printf("\n %d\t\t%s", locctr, line);
	fprintf(inter, "%s", line);

	fprintf(inter, "Symbol table:\n");
	for (int i=0; i<500; i++) {
		if (mysymtab[i].symbol[0] != '\0')
			fprintf(inter, "mysymtab[%d] = symbol = %s, address = %d\n",
				i, mysymtab[i].symbol, mysymtab[i].addr);
	}

	fprintf(inter, "\nError list:\n");
	for (int i=0; i<numberOfErrors; i++) {
		fprintf(inter, "Error %d = %s\n", i, errorList[errors[i]]);
	}

	length = locctr - startaddr;
	fprintf(inter, "\nProgram length = %d", length);

	if (length > 32768) {
		errorFlag = 1;
		errors[numberOfErrors++] = progTooLong;
	}

	fclose(inter);
	fclose(input);
}

/*Assembler pass 2 */
void PASS2()
{
	FILE *inter, *output;
	char record[30], part[8], value[5];/*Part array was defined as part[6] previously*/
	int currtxtlen = 0, foundopcode, foundoperand, chk, operandaddr, recaddr = 0;
	inter = fopen("inter.txt", "r");
	output = fopen("output.txt", "w");
	fgets(line, 160, inter);

	processLine();
	if (!strcmp(opcode, "START")) fgets(line, 20, inter);
	printf("\n\nCorresponding Object code is..\n");
	printf("\nH^ %s ^ %d ^ %d ", programname, startaddr, length);
	fprintf(output, "\nH^ %s ^ %d ^ %d ", programname, startaddr, length);
	recaddr = startaddr; record[0] = '\0';
	while (strcmp(line, "END") != 0)
	{
		operandaddr = foundoperand = foundopcode = 0;
		value[0] = part[0] = '\0';
		processLine();
		for (chk = 0; chk<3; chk++)
		{
			if (!strcmp(opcode, myoptab[chk].code))
			{
				foundopcode = 1;
				strcpy(part, myoptab[chk].objcode);
				if (operand[0] != '\0')
				{
					for (chk = 0; chk<symcount; chk++)

						if (!strcmp(mysymtab[chk].symbol, operand))
						{
							itoa(mysymtab[chk].addr, value);
							strcat(part, value);
							foundoperand = 1;
						}
					if (!foundoperand)strcat(part, "err");
				}
			}
		}
		if (!foundopcode)
		{
			if(strcmp(opcode,"BYTE")==0 || strcmp(opcode,"WORD")||strcmp(opcode,"RESB"))
			{
				strcat(part, operand);
			}
		}
		if ((currtxtlen + strlen(part)) <= 8)
			/*This step was having buffer overflow issue since part[6]
			was defined previously which i corrected to part[8].
			Because of this first two bytes of stack are getting lost*/
		{
			strcat(record, "^");
			strcat(record, part);
			currtxtlen += strlen(part);
		}
		else
		{
			printf("\nT^ %d ^%d %s", recaddr, currtxtlen, record);
			fprintf(output, "\nT^ %d ^%d %s", recaddr, currtxtlen, record);
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

void processLine()
{
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
			} while(!isspace(line[i]));
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
			buff[i-j] = toupper(line[i]);
			i++;
		} while (!isspace(line[i]));
		buff[i-j] = '\0';
		strcpy(opcode, buff);

		// skip whitespace
		do {
			i++;
		} while (isspace(line[i]));

		// store the character number of the start of the operand
		j = i;
		do {
			buff[i-j] = toupper(line[i]);
			i++;
		} while (!isspace(line[i]));
		buff[i-j] = '\0';
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
	if (s[len-4] == ',' && s[len-3] == 'X')
		s[len-4] = '\0';
	//printf("\n***buffer** %s", s);

	if (s[0] < 'A' || s[0] > 'Z' || strlen(s) > 6) {
		//if (strlen(s) > 6)
		//	if (s[strlen(s)-3] == ',' && s[strlen(s)-2] == 'X')
		//		return 1;
		return 0;
	} else {
		for (int i=1; i<strlen(s); i++) {
			if (!(s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')) {
				return 0;
			}
		}
		return 1;
	}
}

void checkLabel()
{
	int k, dupsym = 0;
	// check if valid symbol
	if (isValidSymbol(label) == 0) {
		// set error flag
		errorFlag = 1;
		errors[numberOfErrors++] = illegalLabel;
	}
	for (k = 0; k<symcount; k++)
		if (!strcmp(label, mysymtab[k].symbol))
		{
			mysymtab[k].addr = -1;
			dupsym = 1;
			break;
		}
	if (dupsym) {
		errorFlag = 1;
		errors[numberOfErrors++] = duplicateLabel;
	}
	else {
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

void checkOpcode()
{
	int k = 0, found = 0;
	for (k = 0; k<numberOfOpcodes; k++)
		if (!strcmp(opcode, myoptab[k].code))
		{
			locctr += 3;
			found = 1;
			// check for validity of storage operands
			if (opcode[0] == 'S' && opcode[1] == 'T') {
				//if (operand[strlen(operand)-3] == ',' && operand[strlen(operand)-2] == 'X') {
					////memcpy(operand, &operand, strlen(operand) - 2);
				//	operand[strlen(operand)-2] == '\0';
				//	printf("***** %s\n", operand);
				//}
				if (!isValidSymbol(operand)) {
					printf("\n***storage operand = %s", operand);
					errorFlag = 1;
					errors[numberOfErrors++] = illegalOperand;
				}
			}
			break;
		}
	if (!found)
	{
		if (!strcmp(opcode, "WORD"))
			locctr += 3;
		else if (!strcmp(opcode, "RESW"))
			locctr += (3 * atoi(operand));
		else if (!strcmp(opcode, "RESB"))
			locctr += atoi(operand);
		else if (!strcmp(opcode, "BYTE")) {
			int numberOfBytes = 0;
			if (operand[0] == 'C') {
				do {}
				while (operand[++numberOfBytes+1] != '\'');
				numberOfBytes -= 1;
			}
			else if (operand[0] == 'X') {
				do {}
				while (operand[++numberOfBytes+1] != '\'');
				numberOfBytes -= 1;
			}
			else {
				// set error flag
				errorFlag = 1;
				errors[numberOfErrors++] = illegalOperand;
				//printf("\nERROR: opcode = %s\n", opcode);
			}
			locctr += numberOfBytes;
			//printf("\nNUMBER OF BYTES = %d", numberOfBytes);
		}
		else if (!strcmp(opcode, "END")) {
			if (!isValidSymbol(operand)) {
				// set error flag
				errorFlag = 1;
				errors[numberOfErrors++] = illegalEndOperand;
			}
		}
		else  {
				// set error flag
				errorFlag = 1;
				errors[numberOfErrors++] = illegalInstruction;
		}

	}
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
	for (j = 0; j < i/2; j++)
	{
		char c = s[j];
		s[j] = s[i-j-1];
		s[i-j-1] = c;
	}
	//printf("reverse = %s\n", s);
}

int main()
{
	//char s[10];
	//itoa(2361,s);
	//printf("itoa() = %s\n", s);

	PASS1();

	//PASS2();
	//getch();
}
