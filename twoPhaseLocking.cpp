/*
* @Author: doody
* @Date:   2016-04-17 14:04:33
* @Last Modified by:   doody
* @Last Modified time: 2016-04-17 14:15:25
* @Aim: To design and implement Two phase locking algo
* @Bugs:
* 	Only Write and Read as permissible value
* 	Abort is the only deadlock resolution method
*/

#include <iostream>
#include <vector>

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
	cin >> ch;
	while(!cin.eof())
	{
		vector<instr> transaction;
		while(!cin.eof() and ch != '\n')
		{
			instr tempInstr;

			// Inserting the bool values in operation
			// according to the operation given
			tempInstr.op = ch == 'W'?1:0;
			
			// Taking input for variable
			cin >> ch;
			tempInstr.var = ch;
		
			// Pushing the new intruction
			transaction.push_back(tempInstr);

			// Taking input for operation
			cin >> ch;
		}
		// Pushing the new transaction in transaction list
		transList.push_back(transaction);
	}

	return 0;
}