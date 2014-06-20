#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip> // setw()
#include <cstdlib>

#include "Measure.h"

using namespace std;

#define PRINT(SPACE, FIRST, SYMB, SECOND) \
	setw(SPACE) << first << setw(2) << symb << setw(SPACE) << second;

const unsigned short MODE_PRINT = 0;
const unsigned short MODE_CHECK = 1;
unsigned short MODE = 0;

const unsigned short DIFF_MEDIUM = 1;
const unsigned short DIFF_HARD = 2;
const unsigned short DIFF_EXTREME = 3;
const unsigned short DIFF_PREDATOR = 4;
unsigned short DIFF = 0;

const unsigned short MAX_ADD_MED = 500;
const unsigned short MAX_SUB_MED = 999;
const unsigned short MAX_MUL_MED = 99;
const unsigned short MAX_DIV_MED = 20;
const unsigned short MAX_DIV_K_MED = 15;
const unsigned short MAX_SQR_MED = 99;
const unsigned short MAX_SPACE_MED = 3;
const unsigned short MAX_SIGNLE_MED = 999;
// --
const unsigned short MAX_ADD_HARD = 5000;
const unsigned short MAX_SUB_HARD = 9999;
const unsigned short MAX_MUL_HARD = 199;
const unsigned short MAX_DIV_HARD = 40;
const unsigned short MAX_DIV_K_HARD = 25;
const unsigned short MAX_SQR_HARD = 199;
const unsigned short MAX_SPACE_HARD = 4;
const unsigned short MAX_SIGNLE_HARD = 9999;
//--
const unsigned int MAX_ADD_EXTREME = 99999;
const unsigned int MAX_SUB_EXTREME = 99999;
const unsigned short MAX_MUL_EXTREME = 399;
const unsigned short MAX_DIV_EXTREME = 60;
const unsigned short MAX_DIV_K_EXTREME = 35;
const unsigned short MAX_SQR_EXTREME = 399;
const unsigned short MAX_SPACE_EXTREME = 5;
const unsigned int MAX_SIGNLE_EXTREME = 99999;
//--
const unsigned int MAX_ADD_PREDATOR = 999999;
const unsigned int MAX_SUB_PREDATOR = 999999;
const unsigned short MAX_MUL_PREDATOR = 999;
const unsigned short MAX_DIV_PREDATOR = 100;
const unsigned short MAX_DIV_K_PREDATOR = 50;
const unsigned short MAX_SQR_PREDATOR = 999;
const unsigned short MAX_SPACE_PREDATOR = 6;
const unsigned int MAX_SIGNLE_PREDATOR = 999999;
//--
unsigned int MAX_ADD = 0;
unsigned int MAX_SUB = 0;
unsigned short MAX_MUL = 0;
unsigned short MAX_DIV = 0;
unsigned short MAX_DIV_K = 0;
unsigned short MAX_SQR = 0;
unsigned short MAX_SPACE = 3; // ...
unsigned int MAX_SINGLE = 0;

unsigned short COLLUMNS = 4;
unsigned int AMOUNT = 2000; 


unsigned int getR() {
	unsigned int r = rand() + (unsigned int)(rand()*(time(NULL) % 1083977));
	return r;
}

void xchg(short* f, short* s) {
	bool change = (bool)((rand() % 1) == 1);
	if (change) {
		short temp = *f;
		*f = *s;
		*s = temp;
	}
}

void setup() {
	short m = -1;
	cout << "Set difficulty level. 1 - Medium; 2 - Hard; 3 - Extreme; 4 - Predator; DIFF:";
	cin >> m;
	if (m == 1) {
		DIFF = DIFF_MEDIUM;
	} else if (m == 2) {
		DIFF = DIFF_HARD;
	} else if (m == 3) {
		DIFF = DIFF_EXTREME;
	} else if (m == 4) {
		DIFF = DIFF_PREDATOR;
	} else {
		exit(0); // valid??!
	}

	switch (DIFF) {
	case DIFF_MEDIUM:
		MAX_ADD = MAX_ADD_MED;
		MAX_SUB = MAX_SUB_MED;
		MAX_MUL = MAX_MUL_MED;
		MAX_DIV = MAX_DIV_MED;
		MAX_DIV_K = MAX_DIV_K_MED;
		MAX_SQR = MAX_SQR_MED;
		MAX_SPACE = MAX_SPACE_MED;
		MAX_SINGLE = MAX_SIGNLE_MED;
		break;
	case DIFF_HARD:
		MAX_ADD = MAX_ADD_HARD;
		MAX_SUB = MAX_SUB_HARD;
		MAX_MUL = MAX_MUL_HARD;
		MAX_DIV = MAX_DIV_HARD;
		MAX_DIV_K = MAX_DIV_K_HARD;
		MAX_SQR = MAX_SQR_HARD;
		MAX_SPACE = MAX_SPACE_HARD;
		MAX_SINGLE = MAX_SIGNLE_HARD;
		break;
	case DIFF_EXTREME:
		MAX_ADD = MAX_ADD_EXTREME;
		MAX_SUB = MAX_SUB_EXTREME;
		MAX_MUL = MAX_MUL_EXTREME;
		MAX_DIV = MAX_DIV_EXTREME;
		MAX_DIV_K = MAX_DIV_K_EXTREME;
		MAX_SQR = MAX_SQR_EXTREME;
		MAX_SPACE = MAX_SPACE_EXTREME;
		MAX_SINGLE = MAX_SIGNLE_EXTREME;
		break;
	case DIFF_PREDATOR:
		MAX_ADD = MAX_ADD_PREDATOR;
		MAX_SUB = MAX_SUB_PREDATOR;
		MAX_MUL = MAX_MUL_PREDATOR;
		MAX_DIV = MAX_DIV_PREDATOR;
		MAX_DIV_K = MAX_DIV_K_PREDATOR;
		MAX_SQR = MAX_SQR_PREDATOR;
		MAX_SPACE = MAX_SPACE_PREDATOR;
		MAX_SINGLE = MAX_SIGNLE_PREDATOR;
		break;
	default:
		exit(0); // valid??!
	}

	cout << "Set Mode. 0 - print; 1 - check; MODE:";
	m = -1;
	cin >> m;
	if (m == 0) {
		MODE = MODE_PRINT;

		cout << "How many of those? AMOUNT:";
		unsigned int c = 0;
		cin >> c;
		if ((c > 1) && (c < 10000)) {
			AMOUNT = c;
		} else {
			exit(0); // valid??!
		}

		cout << "How many collumns? AMOUNT:";
		c = -1;
		cin >> c;
		if ((c < 20) && (c > 1)) {
			COLLUMNS = c;
		} else {
			exit(0); // valid??!
		}

	} else if (m == 1) {
		MODE = MODE_CHECK;
	} else {
		exit(0); // valid??!
	}
}

short generate(ofstream* out) {
	short oper = rand() % 6;
	unsigned int first;
	unsigned int second;
	char symb;	
	unsigned int res;

	switch(oper) {
	case 0: // +
		first = rand() % MAX_ADD + 1;
		second = rand() % MAX_ADD + 1;
		symb = '+';
		res = first + second;
		break;
	case 1: // -
		first = getR() % MAX_SUB + 1;
		second = getR() % first + 1;
		symb = '-';
		res = first - second;
		break;
	case 2: // *
		first = getR() % MAX_MUL + 1;
		second = getR() % MAX_MUL + 1;
		symb = '*';
		res = first * second;
		break;
	case 3: // :
		second = getR() % MAX_DIV + 1;
		res = getR() % MAX_DIV_K + 1;
		first = second * res;
		symb = ':';
		break;
	case 4: // ^2
		first = getR() % MAX_SQR + 1;
		second = first;
		symb = '*';
		res = first * second;
		break;
	case 5: // 5849 * 7
		first = getR() % MAX_SINGLE + 1;
		second = getR() % 8 + 2;
		res = first * second;
		symb = '*';
		break;
	}

	/*
	switch( oper ) {
	case 0: // +
		first = rand() % MAX_ADD + 1;
		second = rand() % MAX_ADD + 1;
		symb = '+';
		res = first + second;
		break;
	case 1: // -
		first = rand() % MAX_SUB + 1;
		second = rand() % first + 1;
		symb = '-';
		res = first - second;
		break;
	case 2: // *
		first = rand() % MAX_MUL + 1;
		second = rand() % MAX_MUL + 1;
		symb = '*';
		res = first * second;
		break;
	case 3: // :
		second = rand() % MAX_DIV + 1;
		res = rand() % MAX_DIV_K + 1;
		first = second * res;
		symb = ':';
		break;
	case 4: // ^2
		first = rand() % MAX_SQR + 1;
		second = first;
		symb = '*';
		res = first * second;
		break;
	case 5: // 5849 * 7
		first = rand() % MAX_SINGLE + 1;
		second = rand() % 8 + 2;
		res = first * second;
		symb = '*';
		break;
	}
	*/

	switch (MODE) {
	case MODE_PRINT:
		if (out != NULL) {
			*out << PRINT(MAX_SPACE, first, symb, second);
			*out << "=        "; // 8 spaces
		}
		break;
	case MODE_CHECK:
		cout << PRINT(MAX_SPACE, first, symb, second);
		break;
	}

	return res;

	/*
	*out << PRINT(first, symb, second);
	cout << PRINT(first, symb, second);
	*/
}	

int main(int argc, char *argv[]) {

	setup();		

	srand (time(NULL));
	
	switch (MODE) {
	case MODE_PRINT: {
		ofstream* output = new ofstream();
		output->open("task1.txt");

		for (int i = 1; i <= AMOUNT; i++) {		
			short t = generate(output); // t is not needed!

			if (i % COLLUMNS == 0) {
				*output << "\n\n";
			}			
		}

		output->close();
		delete output;

		break;
	}
	case MODE_CHECK: {		
		for (int i = 0; i < 30; i++) {
			cout << i+1 << ") ";
			short ans = generate(NULL);
			short userAns = -1;
			cout << "=";
			cin >> userAns;

			if (userAns != ans) {
				cout << " | " << ans;
				cin.get();
				cout << "\n";
			}			
		}	

		cout << "Completed!";
		cin.get();

		break;
		}
	}
	
	return 0;
}