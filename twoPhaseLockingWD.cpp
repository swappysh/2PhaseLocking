/*
* @Author: doody
* @Date:   2016-04-17 14:04:33
* @Last Modified by:   swapsharma
* @Last Modified time: 2016-04-17 23:18:59
* @Aim: To design and implement Two phase locking algo
* @Bugs:
* -	Only Write and Read as permissible value
* -	Abort is the only deadlock resolution method
* -	Nonrecommended random function added
* -	Input method is not perfect
* -	Need to create insertion fnc for schedule table
* 	insertion
* -	schedule was declared outside the function
* -	Prints new index after older transaction is removed
* -	Gives priority to readers
* -	No need for temporary Istruction iterator
* @To Do:
* -	Need to insert Wait-die Deadlock prevention protocol
*/

#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <unistd.h>

// Definition for Read op and write op
#define	W	1
#define	R	0

// Definition for wait-die deadlock revention protocol
#define	WAIT	1
#define	SUCCESS	0
#define	DIE	-1

// Function to debug
#define	debug(i)	{cout << "Error :" << i << '\n';}

using namespace std;

// Structure to store instructions
struct _instr
{
	bool	op;
	char	var;
};

struct _resourceTable
{
	char		var;
	bool		op;
	vector<int>	trnxIndexVector;
};

struct _schedule
{
	int	trnxIndex;
	char	var;
	bool	op;
};

// Vector of vector to store multiple transactions
vector<vector<_instr> > transList;
vector<_schedule>	schedule;

bool system(int transNum)
{
	static vector<_resourceTable>	resourceTable;

	vector<_instr>::iterator tempInstr = transList[transNum].begin();

	// ResourceTableIndex variable
	int RTIndex = 0;
	// Check if variable in the instr exists in resourceTable
	for (RTIndex = 0; RTIndex < resourceTable.size() and tempInstr->var != resourceTable[RTIndex].var; ++RTIndex);

	// If it doesn't exists
	if (RTIndex == resourceTable.size())
	{
		_resourceTable tempRRow;
		tempRRow.var = tempInstr->var;
		tempRRow.op = tempInstr->op;
		tempRRow.trnxIndexVector.push_back(transNum);

		resourceTable.push_back(tempRRow);

		// Pass the schedule to schedule table
		_schedule tempSRow;
		tempSRow.trnxIndex = transNum;
		tempSRow.var = tempInstr->var;
		tempSRow.op = tempInstr->op;

		schedule.push_back(tempSRow);

		return SUCCESS;
	}
	else // If it does exist
	{
		// Check whether the operation associated is W or R
		if (resourceTable[RTIndex].op == R)	// If it is R
		{
			if (tempInstr->op == R)	// If the selected instr has R as op
			{
				// Then pass the permission to use resource
				resourceTable[RTIndex].trnxIndexVector.push_back(transNum);

				// Pass the schedule to schedule table
				_schedule tempSRow;
				tempSRow.trnxIndex = transNum;
				tempSRow.var = tempInstr->var;
				tempSRow.op = tempInstr->op;

				schedule.push_back(tempSRow);

				return SUCCESS;
			}
			else	// If it has W as instr
			{
				// Check if reader is one
				if (resourceTable[RTIndex].trnxIndexVector.size() == 1)
				{
					// Check whether the instruction is of same transaction
					if (resourceTable[RTIndex].trnxIndexVector.front() == transNum)
					{
						resourceTable[RTIndex].op = W;

						// Push instr in schedule
						_schedule tempSRow;
						tempSRow.trnxIndex = transNum;
						tempSRow.var = tempInstr->var;
						tempSRow.op = tempInstr->op;

						schedule.push_back(tempSRow);
					}
					// Checks Wait-die condition
					// Checks whether the new instr is old
					else if (transNum < resourceTable[RTIndex].trnxIndexVector.front())
						return WAIT;
					else
						return DIE;
				}
				else
					// Give priority to readers
					return DIE;
			}
		}
		else	// If op is W
		{
			// If selected instr has op W and is of
			// same transaction
			if (resourceTable[RTIndex].trnxIndexVector.front() == transNum)
			{
				resourceTable[RTIndex].op = W;

				// Push instr in schedule
				_schedule tempSRow;
				tempSRow.trnxIndex = transNum;
				tempSRow.var = tempInstr->var;
				tempSRow.op = tempInstr->op;

				schedule.push_back(tempSRow);

				return SUCCESS;
			}
			// Check for Wait-die condition
			// Check whether the new instr is old
			else if (transNum < resourceTable[RTIndex].trnxIndexVector.front())
				return WAIT;
			else
				return DIE;
		}
	}

	return DIE;
}

int main()
{
	// Loop for input from user
	char ch;
	while(!cin.eof())
	{
		vector<_instr> transaction;

		// Taking the first input, ignoring whitespace
		do {ch = cin.get();} while(ch == ' ');
		while(!cin.eof() and ch != '\n')
		{
			_instr tempInstr;

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

	// Execution loop
	while (transList.size() != 0)
	{
		// Randomly select the instruction to be executed
		// keeping in mind that instructions from a transaction
		// run in the order present in the transaction
	
		// Seeding the random number gererator
		srand(time(0));
	
		// Randomly select the transaction to next go on to the
		// butcher list. It is to be noted that rand() function
		// provides with random number fro 0 to RAND_MAX
		int randTransIndex = transList.size()*rand()/RAND_MAX;
	
		// Send transList index to function to take the first
		// instruction from transaction. If older trnx then,
		// Wait occurs and continue to next instruction and
		// if younger trnx then die occurs
		if (system(randTransIndex) == WAIT)
			continue;
		else if (system(randTransIndex) == DIE)
		{
			cout << "Abort\n";
			transList.erase(transList.begin()+randTransIndex);
		}
		else
		{
			// Remove instr or remove transaction if no more instr
			if (transList[randTransIndex].size() > 1)
				transList[randTransIndex].erase(transList[randTransIndex].begin());
			else
				transList.erase(transList.begin()+randTransIndex);
		}
	}

	// Print schedule if completed
	for (vector<_schedule>::iterator i = schedule.begin(); i != schedule.end(); ++i)
	{
		cout << i->trnxIndex << " " << i->var << " " << i->op << '\n';
	}
	
	return 0;
}
