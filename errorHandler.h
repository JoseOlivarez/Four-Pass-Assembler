#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

typedef enum {noError, opSymbolUndef, progTooLong, tooManySymbols, illegalEndOperand,
	illegalStartOperand, illegalOperand, illegalInstruction, illegalLabel, duplicateLabel,
	noEnd
} error;

const char * errorList[] = {
    "No Error",
    "Symbol in operand undefined",
    "Program too long!",
	"Too many symbols in source program!",
	"Missing or illegal operand on END directive!",
	"Missing or illegal operand on START directive!",
	"Missing or illegal operand on data storage directive!",
	"Illegal instruction!",
	"Illegal label!",
	"Duplicate label!",
	"END directive not found!"
};

void errorHndlg(char* comm, int errortype);

void warningHndlg(int warnType);

void setErrors(FILE* fp, char *psw);

#endif /* ERRORHANDLER_H_ */
