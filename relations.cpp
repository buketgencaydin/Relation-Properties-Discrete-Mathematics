#include <iostream> // used for input-output operations
#include <fstream> // used for input-output streams
#include <cstdlib> // used for exit() and atoi() functions
#include <vector> // used for vectors
#include <cctype> // used for isalnum() function
#include <utility> // used for pair
using namespace std;

vector<int> relationNum;
vector<vector<char>> set(100);
vector<vector<pair<char,char>>> relation(100);;
int setCount=0;

void readFile(); // reads the input file
void writeFile(); // reads the output file
bool isWrongRelation(char ch1, char ch2, vector<char> set); // checks whether relation has wrong information or not
void isReflexive(int setNum, ofstream &outStream); // checkes whether the relation set is reflexive or not
void isSymmetric(int setNum,ofstream &outStream); // checkes whether the relation set is symmetric or not
void isAntisymmetric(int setNum, ofstream &outStream); // checkes whether the relation set is antisymmetric or not
bool thirdPair(int setNum, char first, char second); // helper function of isTransitive()
void isTransitive(int setNum, ofstream &outStream); // checkes whether the relation set is transitive or not


int main()
{
	readFile();
	writeFile();
	return 0;
}
void readFile()
{
	string input;
	int num;
	bool flag;
	pair <char, char> rPair; //relation pair

	ifstream inStream; // input stream
	inStream.open("input.txt");

	/* Terminates the program if input file opening fails */
	if(inStream.fail())
	{
		cerr << "Input file opening failed.\n";
		exit(0);
	}
	else
	{
		while(!inStream.eof()) // loop continues unless end-of-file is reached
		{
			getline(inStream, input);// reads the how many relations in R
			num = atoi(input.c_str()); // converts the input string to the integer(relation number)
			relationNum.push_back(num); // pushes the relation number into vector

			getline(inStream, input); // reads the set
			int k=0; // relation counter
			for(int i=0 ; i<input.size() ; i++)
			{
				if(isalnum(input[i])) // if element is alphabetic or numerical i.e not comma ','
				{
					set[setCount].push_back(input[i]); // pushes the i-th element of the set into vector
					k++;
				}
			}
			for(int i=0 ; i<relationNum[setCount]; i++)
			{
				getline(inStream, input); // reads the i-th relation
				flag = isWrongRelation(input[0],input[2],set[setCount]); // checks whether relation has wrong information or not

				if(!flag) // if relation does not have wrong information
				{
					rPair.first = input[0]; rPair.second = input[2];
					relation[setCount].push_back(rPair);
					relation.resize(100+setCount); // resizes the relation vector
				}
			}
			setCount++; // increases the set counter by 1
		}
	}
	inStream.close(); // closes the input file
}
bool isWrongRelation(char ch1, char ch2, vector<char> set)
{
	int flag1=0, flag2=0;
	char res;
	for(int i=0 ;i<set.size(); i++)
	{
		if(set[i]==ch1) flag1++; // if first element of the pair is in the set, increment flag1;
		if(set[i]==ch2) flag2++; // if second element of the pair is in the set, increment flag2;
	}
	if(flag1==0 || flag2==0) // if first or second element of the pair is not in the set, give an error and skip that pair
	{
		/*
		 	 if first element of the pair is not in the set,
		  	 print it as "The element 'ch1' of the relation (ch1, ch2) is not found in the set A
		 */
		flag1==0 ? res=ch1 : res=ch2;
		cout << "\n\nThe element " << res <<" of the relation (" << ch1<<","<<ch2 <<") is not found in the set A={"<< set[0];
		for(int i=1 ; i<set.size() ; i++)
		{
			cout << "," << set[i];
		}
		cout << "}. This relation skipped.\n\n";
		return true;
	}
	else return false;
}
void writeFile()
{
	ofstream outStream; // output stream
	outStream.open("output.txt");

	/* Terminates the program if output file opening fails */
	if(outStream.fail())
	{
		cerr << "Output file opening failed.\n";
		exit(0);
	}
	else
	{
		for(int i=0 ; i<setCount-1 ; i++)
		{
			outStream << "n\n";

			/* prints the relation set */
			for(int j=0 ; j<relationNum[i] ; j++)
			{
				outStream << "(" << relation[i][j].first << "," << relation[i][j].second << ")";
			}
			outStream << endl;

			isReflexive(i, outStream); 	// checkes whether the relation set is reflexive or not
			isSymmetric(i, outStream);	// checkes whether the relation set is symmetric or not
			isAntisymmetric(i, outStream); // checkes whether the relation set is antisymmetric or not
			isTransitive(i, outStream); // checkes whether the relation set is transitive or not
		}
	}
	outStream.close(); // closes the output file
}
void isReflexive(int setNum, ofstream &outStream)
{
	int flag=0;

	for(int i=0 ; i<set[setNum].size() ; i++) // for all elements of set
	{
		for(int j=0 ; j<relationNum[setNum] ; j++) // for all relations
		{
			/* if j-th first = j-th second */
			if(relation[setNum][j].first == set[setNum][i] && relation[setNum][j].second == set[setNum][i]) flag++;
		}
		if(flag==0) // for an element of set, if there is no such a pair (a, a)
		{
			outStream << "Reflexive: No, ("<< set[setNum][i] << "," << set[setNum][i] << ") is not found.\n";
			return;
		}
		flag=0; // for the other pairs, flag is changed to its initial value
	}
	outStream << "Reflexive: Yes, all elements are present.\n";
}
void isSymmetric(int setNum, ofstream &outStream)
{
	int flag=0;
	int same=0; // counter for pairs that two elements are same
	char ex1, ex2; // example pair for why relation is symmetric (ex1,ex2) (ex2, ex1)

	for(int i=0 ; i<relationNum[setNum] ; i++)
	{
		if(relation[setNum][i].first == relation[setNum][i].second) same++; // if two elements of a pair is equal i.e (a,a), skip it
		else
		{
			/*
				for a pair, searches its symmetric pair
				if finds such a pair, takes that elements as examples
				if it can not find such a pair, flag is still 0
				prints that examples and returns
			*/
			for(int j=0 ; j<relationNum[setNum] ; j++)
			{
				/*
				   i = (a, b)  j = (b, a)
				   if j-th first = i-th second and j-th second = i-th first
				*/
				if(relation[setNum][j].first == relation[setNum][i].second && relation[setNum][j].second == relation[setNum][i].first) flag++;
			}
			if(flag==0) // if symmetric pair isn't found, prints that pair and returns
			{
				outStream << "Symmetric: No, ("<< relation[setNum][i].first << "," << relation[setNum][i].second << ") is found where ("
							<< relation[setNum][i].second << "," << relation[setNum][i].first<< ") is not found\n";
				return;
			}
			else
			{
				ex1=relation[setNum][i].first;  // i = (a, b) first=a
				ex2=relation[setNum][i].second; // i = (a, b) second=b
			}
			flag=0; // for the other pairs, flag is changed to its initial value
		}
	}
	if(same==set[setNum].size() && same==relationNum[setNum]) // if number of reflexive pairs equal to the size of set
		outStream << "Symmetric: Yes, all pairs are reflexive\n";
	else
		outStream << "Symmetric: Yes, ("<< ex1 << "," << ex2 << ") and (" << ex2 << "," << ex1<< ") is found.\n";

}
void isAntisymmetric(int setNum, ofstream &outStream)
{
	int flag=0;
	int same=0; // counter for pairs that two elements are same
	char ex1, ex2; // example pair for why relation is antisymmetric (ex1,ex2) (ex2, ex1)
	int i;

	for(int i=0 ; i<relationNum[setNum] ; i++)
	{
		if(relation[setNum][i].first == relation[setNum][i].second) same++; // if two elements of a pair is equal i.e (a,a), skip it
		else
		{
			/*
				for a pair, searches its symmetric pair
			 	if finds such a pair, increments the flag variable and takes that elements as examples
			 	prints that examples and returns
			*/

			for(int j=0 ; j<relationNum[setNum] ; j++)
			{
				/*
				   i = (a, b)  j = (b, a)
				   if j-th first = i-th second and j-th second = i-th first
				*/
				if(relation[setNum][j].first == relation[setNum][i].second && relation[setNum][j].second == relation[setNum][i].first) flag++;
				else
				{
					ex1=relation[setNum][i].first;  // i = (a, b) first=a
					ex2=relation[setNum][i].second; // i = (a, b) second=b
				}
			}
			if(flag!=0) // if a symmetric pair found, prints that pair and returns
			{
				outStream << "Antisymmetric: No, ("<< relation[setNum][i].first << "," << relation[setNum][i].second << ") and ("
							<< relation[setNum][i].second << "," << relation[setNum][i].first<< ") is found.\n";
				return;
			}
			flag=0; // for the other pairs, flag is changed to its initial value
		}
	}

	if(same==set[setNum].size() && same==relationNum[setNum]) // if number of reflexive pairs equal to the size of set
		outStream << "Antisymmetric: Yes, all pairs are reflexive\n";
	else
		outStream << "Antisymmetric: Yes, ("<< ex1 << "," << ex2 << ") is found where (" << ex2 << "," << ex1<< ") is not found.\n";

}
bool thirdPair(int setNum, char first, char second)
{
   for (int i=0; i<relationNum[setNum]; i++)
   {
      if (first==relation[setNum][i].first && second==relation[setNum][i].second)  return true;
   }
   return false;
}
void isTransitive(int setNum , ofstream &outStream)
{
	int same=0; // counter for pairs that two elements are same
	char ex1,ex2,ex3; // example pair elements for why relation is antisymmetric (ex1, ex2) (ex2, ex3) (ex1, ex3)
    for (int i=0; i<relationNum[setNum]; i++)
    {
	   /* first pair (a,b) */
	   char a = relation[setNum][i].first;
	   char b = relation[setNum][i].second;

	   if(a == b) same++; // if two elements of a pair is equal i.e (a,a)

	   for (int j=0; j<relationNum[setNum]; j++)
	   {
		  /* second pair (b,c) */
		  if (relation[setNum][j].first == b)
		  {
			  if (thirdPair(setNum, a, relation[setNum][j].second) == false) // if there is no third pair such as (a,c), then not transitive
			  {
				  /* Transitive: No, (a,c) is not found where (a, b) and (b, c) is found. */
				  outStream << "Transitive: No, (" << a << "," << relation[setNum][j].second << ") is not found where ("
						  << a << "," << b << ") and (" << b << "," << relation[setNum][j].second << ") are found.\n";
				  return;
			  }
			  if(a!=b && b!= relation[setNum][j].second)
			  {
				  ex1=a; // a
				  ex2=b; // b
				  ex3=relation[setNum][j].second; // c
			  }
		  }
	   }
    }
    if(same==set[setNum].size() && same==relationNum[setNum]) // if number of reflexive pairs equal to the size of set
    	outStream << "Transitive: Yes, all pairs are reflexive\n";
    else
    {
    	/* Transitive: Yes, (a,c) is found where (a, b) and (b, c) is found. */
    	outStream << "Transitive: Yes, (" << ex1 << "," << ex3 << ") is found where (" << ex1 << "," << ex2 << ") and (" << ex2 << "," << ex3 << ") are found.\n";
    }
}

