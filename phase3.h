#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Symbol{ //symbol struct to put in symtab
	char lbl[7];
	int loc;
};
struct OP{ //symbol struct to put in symtab
	char operation[5];
	int opcode;
};
void passTwo(struct Symbol symtab[], struct OP optab[], int programLength, int start, int symtabLength)
{				//most ints are either counters or "booleans"
	int i = 0, isHeader = 1, j, isLabel = 0, foundLabel = 0, containsComma = 0, constant, recordSize = 0, containsError = 0, isComment = 0, first = 1;
	char firstAddress[7];  //firstaddress needed for end record
	char sourceLine[128]; //strings for holding needed variables from intermediate
	char errorLine[128];
	char operand[128];
	char operand1[128];
	char operand2[128];
	char opAddress[128]; //string version of address if needed for string functions
	int operandAddress1; // int operand address used if needed for operations
	char label[7]; 
	char location[7];
	char operation[7];
	char opcode[7];
	char recordObjectCodeSize[7]; //string that holds the hex of each text record's code length
	char textRecord[100]; //holds object code of text record
	char initialTextRecord[100]; //this is for the initial part of each text record such as the T and initial address and size 
	char objectCode[10]; //current object code
	initialTextRecord[0] = '\0';
	objectCode[0] = '\0';    //initializing all strings with a null char just in case
	firstAddress[0] = '\0';
	textRecord[0] = '\0';
	opcode[0] = '\0';
	sourceLine[0] = '\0';
	errorLine[0] = '\0';
	operand[0] = '\0';
	operand1[0] = '\0';
	operand2[0] = '\0';
	operandAddress1 = 0;
	label[0] = '\0';
	location[0] = '\0';
	operation[0] = '\0';
	recordObjectCodeSize[0] = '\0';
	int objectCodeSize = 0; //current object code's text size
	int errorsSize = 0;
	char temp = ' ';
	FILE *list;
	list = fopen("listing.txt", "w");  //open file for writing
	FILE *obj;
	obj = fopen("object.txt", "w");  //open file for writing
	FILE *ifp;
	if ((ifp = fopen("intermediate.txt", "r")) == NULL){  //open file for reading
		printf("Cannot open file...\n");
	}
	else{
		fgets(sourceLine, 127, ifp);
		sscanf(sourceLine, "%*s %s %s %s", label, operation, location); //scannign first line to check for START
		if (strcmp(operation, "START") == 0)
		{
			fgets(errorLine, 127, ifp);
			fprintf(list, "%s", sourceLine);
			fprintf(list, "%s\n", location);
			i = 8; //skips to index with actual errors
			while (temp != '\0')
			{
				temp = errorLine[i]; //checks for errors in start line
				i++;
				if (temp == '1')
				{
					fprintf(list, "Invalid operation on line\n");
					containsError = 1;
				}
				if (temp == '2')
				{
					fprintf(list, "Duplicate Label on line\n");
					containsError = 1;
				}
				if (temp == '3')
				{
					fprintf(list, "Illegal Label on line\n");
					containsError = 1;
				}
				if (temp == '4')
				{
					fprintf(list, "Illegal Data Operand on line\n");
					containsError = 1;
				}
				if (temp == '5')
				{
					fprintf(list, "Invalid End operand on line\n");
					containsError = 1;
				}
				if (temp == '6')
				{
					fprintf(list, "Illegal Start operand on line\n");
					containsError = 1;
				}
				if (temp == '7')
				{
					fprintf(list, "Too many symbols on line\n");
					containsError = 1;
				}
				if (temp == '8')
				{
					fprintf(list, "Program is too long on line\n");
					containsError = 1;
				}
			}
			temp = '0';
			fprintf(obj, "H^%-6s^%06X^%06X\n", label, start, programLength); //if we have a start then create header with label (name of program)
		}
		else
		{
			fprintf(obj, "H^      ^%06X^%06X\n", start, programLength); //header without label
			rewind(ifp);
		}
		initialTextRecord[0] = 'T'; //initializing first text record
		initialTextRecord[1] = '^';
		initialTextRecord[2] = '\0';
		recordSize = 1;
		
		while (fgets(sourceLine, 127, ifp) && strcmp(operation, "END") != 0){//gets copy line
			if (sourceLine[4] == '.') //checks if line is a comment
			{
				isComment = 1;
				fgets(errorLine, 127, ifp); //gets error line
			}
			else if (iswspace(sourceLine[3])) //checks if line is a whitespace
			{
				fscanf(ifp, "%s\n", location);
				fscanf(ifp, "%s\n", operation);
				if (strcmp(operation, "RSUB") != 0) //rsub has no operand
				{
					fscanf(ifp, "%s\n", operand);
				}
				fgets(errorLine, 127, ifp);
				if (recordSize == 1) //on the first entry of each record we need to know the starting address
				{
					strcat(initialTextRecord, location);
					strcat(initialTextRecord, "^");
					recordSize += 6;
				}
				if (first == 1) //if very first entry then store address for the END 
				{
					strcpy(firstAddress, location);
					first = 0;
				}
				
			}
			else //final one with label
			{
				fscanf(ifp, "%s\n", location);
				fscanf(ifp, "%s\n", operation);
				fscanf(ifp, "%s\n", operand);
				fgets(errorLine, 127, ifp);
				if (recordSize == 1)
				{
					strcat(initialTextRecord, location);
					strcat(initialTextRecord, "^");
					recordSize += 6;
				}
				if (first == 1)
				{
					strcpy(firstAddress, location);
					first = 0;
				}
				
			}
			fprintf(list, "%s", sourceLine); //pritns source line
			i = 0;
			while (temp != '\0') //checks for errors and pritns to listing
			{
				temp = errorLine[i];
				i++;
				if (temp == '1')
				{
					fprintf(list, "Invalid operation on line\n");
					containsError = 1;
				}
				if (temp == '2')
				{
					fprintf(list, "Duplicate Label on line\n");
					containsError = 1;
				}
				if (temp == '3')
				{
					fprintf(list, "Illegal Label on line\n");
					containsError = 1;
				}
				if (temp == '4')
				{
					fprintf(list, "Illegal Data Operand on line\n");
					containsError = 1;
				}
				if (temp == '5')
				{
					fprintf(list, "Invalid End operand on line\n");
					containsError = 1;
				}
				if (temp == '6')
				{
					fprintf(list, "Illegal Start operand on line\n");
					containsError = 1;
				}
				if (temp == '7')
				{
					fprintf(list, "Too many symbols on line\n");
					containsError = 1;
				}
				if (temp == '8')
				{
					fprintf(list, "Program is too long on line\n");
					containsError = 1;
				}
			}
			if (isComment == 0) //if not a comment search optab for operation
			{
				for (i = 0; i < 25; i++)
				{
					if (strcmp(optab[i].operation, operation) == 0)
					{
						for (j = 0; j < strlen(operand); j++) //checks if operand has a comma
						{
							if (operand[j] == ',')
							{
								sscanf(operand, "%s,%s,", operand1, operand2); //stores the operand after the comma, not sure if it's always X or not :/
								containsComma = 1;
							}
						}
						isLabel = 1; //operand is a label if operation was found 
						sprintf(opcode, "%X", optab[i].opcode); //store opcode
						break;
					}
				}
				if (isLabel == 1) //if there is a label in operand
				{
					for (i = 0; i < symtabLength; i++)
					{
						if (strcmp(symtab[i].lbl, operand) == 0)
						{
							operandAddress1 = symtab[i].loc; //find operand address if operand contained label
							foundLabel = 1;
						}
					}
				}
				if (strcmp(operation, "BYTE") == 0 && containsError == 0) //special case for byte
				{

					if (operand[0] == 'C')
					{
						int substrLength = strlen(operand) - 3; //create substring using memcpy
						char substr[128];
						memcpy(substr, &operand[2], substrLength);
						substr[substrLength] = '\0';
						for (i = 0; i < strlen(substr); i++)
						{
							char temp[5];
							sprintf(temp, "%X", substr[i]); //stores each character in its hexadecimal form
							strcat(objectCode, temp);
						}
					}
					else if (operand[0] == 'X')
					{
						int substrLength = strlen(operand) - 3;
						char substr[128];
						memcpy(substr, &operand[2], substrLength);
						substr[substrLength] = '\0';                //stores hex number given
						sscanf(substr, "%s", objectCode);
					}

				}
				if (strcmp(operation, "WORD") == 0 && containsError == 0)
				{
					sscanf(operand, "%d", &constant); //takes number given and stores in objectCode
					sprintf(objectCode, "%X", constant);
				}
				if (strcmp(operation, "4C") == 0) //rsub just fills address with 0s
				{
					strcpy(objectCode, opcode);
					strcat(objectCode, "0000");
				}
				else if (isLabel && containsError == 0) //if operand contains label and no errors then we can create object code
				{
					if (containsComma)
					{
						operandAddress1 += 0x8000; //if operand contains comma then we must set the 15th bit of the address to 1 since it is accessing the X register
					}
					strcpy(objectCode, opcode);
					sprintf(opAddress, "%X", operandAddress1);
					strcat(objectCode, opAddress);
				}
				if (containsError == 0)
				{
					objectCodeSize = strlen(objectCode);
					if (objectCodeSize + recordSize > 69 || strcmp(operation, "END") == 0) //make sure we won't go over our limit of 69 characters (excluding ^) 
					{																		//and if it will or we reach end then finish off line of text record
						textRecord[strlen(textRecord) - 1] = '\0'; //set last ^ character to null
						recordSize = (recordSize - 9) / 2; //gets true record size in bytes that ignores ^ and the initial text record items
						sprintf(recordObjectCodeSize, "%X", recordSize); //stores size into a string so I can strcat
						strcat(initialTextRecord, recordObjectCodeSize);
						strcat(initialTextRecord, "^");
						strcat(initialTextRecord, textRecord); //combines both text records to create line then prints
						fprintf(obj, "%s\n", initialTextRecord);
						initialTextRecord[0] = 'T'; //initialize new text record
						initialTextRecord[1] = '^';
						initialTextRecord[2] = '\0';
						textRecord[0] = '\0';
						recordSize = 1;
						if (strcmp(operation, "END") == 0)
						{
							initialTextRecord[0] = 'E'; //if end then create end record including start address
							strcat(initialTextRecord, firstAddress);
							fprintf(obj, "%s\n", initialTextRecord);
						}
					}
					if (strcmp(operation, "END") == 0)
					{
					}
					else if (objectCodeSize > 0)
					{
						if (recordSize == 1) //if first record in new text record then we need to add the initial items
						{
							strcat(initialTextRecord, location);
							strcat(initialTextRecord, "^");
							recordSize += 6;
						}
						strcat(textRecord, objectCode); //add objectcode to text record
						recordSize += objectCodeSize;
						strcat(textRecord, "^");
					}
					fprintf(list, "Code: %s\n", objectCode); //print listing to file
					fprintf(list, "Address: %s\n", location);
				}
			}
			i = 0, j = 0, isLabel = 0, foundLabel = 0, containsComma = 0, isComment = 0; //reinitialize a lot of variables
			sourceLine[0] = '\0';
			opcode[0] = '\0';
			errorLine[0] = '\0';
			operand[0] = '\0';
			operand1[0] = '\0';
			operand2[0] = '\0';
			operandAddress1 = 0;
			label[0] = '\0';
			location[0] = '\0';
			operation[0] = '\0';
			recordObjectCodeSize[0] = '\0';
			objectCode[0] = '\0';
			objectCodeSize = 0;
			errorsSize = 0;
			temp = ' ';

		}
		for (i = 0; i < symtabLength; i++) //prints symbel table to file
		{
			fprintf(list, "%s-%X\n", symtab[i].lbl, symtab[i].loc); //prints label and address in hex form
		}
		fclose(list); //close files
		fclose(obj);
		if (containsError) //if there were errors we don't want an object file
		{
			remove("object.txt");
		}
	}
}
