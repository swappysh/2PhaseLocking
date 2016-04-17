/*
* @Author: doody
* @Date:   2016-04-17 14:04:33
* @Last Modified by:   swapsharma
* @Last Modified time: 2016-04-17 16:02:23
* @Aim: To design and implement Two phase locking algo
* @Bugs:
* 	Only Write and Read as permissible value
* 	Abort is the only deadlock resolution method
* 	Nonrecommended random function added
* 	Input method is not perfect
*/

#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

// Definition for Read op and write op
#define W 1
#define R 0

using namespace std;

// Structure to store instructions
struct instr
{
	bool op;
	char var;
};

int main()
{
	// Vector of vector to store multiple transactions
	vector<vector<instr> > transList;

	// Loop for input from user
	char ch;
	while(!cin.eof())
	{
		vector<instr> transaction;

		// Taking the first input, ignoring whitespace
		do {ch = cin.get();} while(ch == ' ');
		while(!cin.eof() and ch != '\n')
		{
			instr tempInstr;

			// Inserting the bool values in operation
			// according to the operation given
			tempInstr.op = ch == 'W'?1:0;
			
			// Taking input for variable
			do {ch = cin.get();} while(ch == ' ');
			tempInstr.var = ch;
		
			// Pushing the new intruction
			transaction.push_back(tempInstr);

			// Taking input for operation
			do {ch = cin.get();} while(ch == ' ');
		}
		// Pushing the new transaction in transaction list
		transList.push_back(transaction);
	}

	// Randomly select the instruction to be executed
	// keeping in mind that instructions from a transaction
	// run in the order present in the transaction

	// Seeding the random number gererator
	srand(time(0));

	// Randomly select the transaction to next go on to the
	// butcher list. It is to be noted that rand() function
	// provides with random number fro 0 to RAND_MAX
	int randTransIndex = transList.size()*rand()/RAND_MAX;

	cout << (transList.size()*rand())/RAND_MAX << '\n';

	return 0;
}