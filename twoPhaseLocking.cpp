/*
* @Author: doody
* @Date:   2016-04-17 14:04:33
* @Last Modified by:   swapsharma
* @Last Modified time: 2016-04-17 17:17:38
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
#define	W	1
#define	R	0

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
	vector<int>	trnxIndex;
};

struct _schedule
{
	int		trnxIndex;
	char	var;
	bool	op;
};

// Vector of vector to store multiple transactions
vector<vector<_instr> > transList;

bool system(int transNum)
{
	static vector<_resourceTable>	resourceTable;
	static vector<_schedule>		schedule;

	_instr* tempInstr = transList[transNum].begin();

	// ResourceTableIndex variable
	int RTIndex = 0;
	// Check if variable in the instr exists in resourceTable
	for (RTIndex = 0; RTIndex < resourceTable.size() and tempInstr->var != resourceTable[RTIndex].var; ++RTIndex);

	// If it doesn't exists
	if (RTIndex != resourceTable.size())
	{
		_resourceTable tempRRow;
		tempRRow.var = tempInstr->var;
		tempRRow.op = tempInstr->op;
		tempRRow.trnxIndex(transNum);

		resourceTable.push_back(tempRRow);

		_schedule tempSRow;
		tempSRow.trnxIndex = transNum;
		tempSRow.var = tempInstr->var;
		tempSRow.op = tempInstr->op;

		schedule.push_back(tempSRow);
	}
	else // If it does exist
	{

	}
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
	
		cout << (transList.size()*rand())/RAND_MAX << '\n';
	
		// Send transList index to function to take the first
		// instruction from transaction. If error occurs
		// sleep for some time and then retry. If problem still
		// persists then abort.
		if (system(randTransIndex) == -1)
		{
			sleep(10);
			if (system(randTransIndex) == -1)
			{
				cout << "Abort\n";
				transList.erase(transList.begin()+randTransIndex)
			}
		}
		else
			continue;
	}
	
	return 0;
}