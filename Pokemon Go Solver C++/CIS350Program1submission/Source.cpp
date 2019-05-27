/*
Name: Evan Joseph
Date: 1/24/2017
Assignment: CIS 350-001, Program 1 Pokemon GoGo
Purpose: (I got all of my test cases to yield all possible combinations, except they wouldn't print
out in lexographical order, so I failed many test cases in the autograder, just a heads up.)
This part of the program will take locations and pokemon names as input. It will store these
in a vector of Pokemon structs. All combinations of unique pokemon will be the output of this section
of the program. The next part of the program, due the following week, will find the best permutation
of these combinations, based on the most optimal route to catch them all (the most optimal route is
the one with the shortest total distance from start to finish).
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//used to track how many pokemon of a certain type there are
struct UniquePokemon
{
	int indexToUse = 0;
	int numberOfPokemon;
	//this vector stores the indices of where the certain type of Pokemon is
	vector<int> indexOfPokemon;
	string name;
};

//will be used for calculating distances
struct Pokemon
{
	int northSouth;
	int eastWest;
	string name;
};

/*
pre: myPokemonVector should not be empty
post: prints all the combinations of unique Pokemon
*/
void nextOneFromEach(vector<Pokemon> myPokemonVector)
{
	vector<int> orderOfStops;
	vector<UniquePokemon> uniquePokemonVector;

	//this for loop will help sort each Pokemon according to their type and will store
	//the indices of where they were found
	for (int i = 0; i < myPokemonVector.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < uniquePokemonVector.size(); j++)
		{
			if (myPokemonVector[i].name == uniquePokemonVector[j].name)
			{
				(uniquePokemonVector[j].numberOfPokemon)++;
				uniquePokemonVector[j].indexOfPokemon.push_back(i);
				found = true;
			}
		}

		if (!found)
		{
			UniquePokemon tempPokemon;
			tempPokemon.name = myPokemonVector[i].name;
			tempPokemon.numberOfPokemon = 1;
			tempPokemon.indexOfPokemon.push_back(i);
			uniquePokemonVector.push_back(tempPokemon);
		}

	}

	vector<int> printThesePokemon;
	printThesePokemon.resize(uniquePokemonVector.size());
	bool moreCombos = true;
	while (moreCombos)
	{
		//this loop steps through the vector containing all the UniquePokemon structs, so it
		//visits each Pokemon
		//this is the base case. if all are at the last index, set to false
		for (int i = 0; i < uniquePokemonVector.size(); i++)
		{
			//if the last index we used is the last one of that type of Pokemon
			if ((uniquePokemonVector[i].indexToUse + 1) == uniquePokemonVector[i].numberOfPokemon)
			{
				moreCombos = false;
			}
			else
			{
				moreCombos = true;
				//if we don't break the loop, moreCombos could be overwritten to be false by another Pokemon
				break;
			}
		}

		//if the current choice for that set is the last, set it to first choice for that set, and try to increment the next set
		for (int i = 0; i < uniquePokemonVector.size(); i++)
		{
			if (uniquePokemonVector[i].indexToUse + 1 == uniquePokemonVector[i].numberOfPokemon)
			{
				uniquePokemonVector[i].indexToUse = 0;
			}
			else
			{
				uniquePokemonVector[i].indexToUse++;

				//this break is necessary because if we increment once, we don't want to increment the rest,
				//so we break it for now until the outermost while loop executes again
				break;
			}
		}

		//adding the location (index) of the pokemon to the printThesePokemon vector so we can later print them
		for (int i = 0; i < uniquePokemonVector.size(); i++)
		{
			printThesePokemon[i] = (uniquePokemonVector[i].indexOfPokemon[uniquePokemonVector[i].indexToUse]);
		}

		//the indices should be sorted
		sort(printThesePokemon.begin(), printThesePokemon.end());

		//simply prints the pokemon combination that was found
		for (int i = 0; i < printThesePokemon.size(); i++)
		{
			cout << printThesePokemon[i] + 1 << " ";
		}
		cout << endl;
	}
}

int main()
{
	vector<Pokemon> locationVector;
	int numOfLocations = 0;
	cin >> numOfLocations;

	for (int i = 0; i < numOfLocations; i++)
	{
		Pokemon myPokemon;
		cin >> myPokemon.northSouth >> myPokemon.eastWest >> myPokemon.name;
		locationVector.push_back(myPokemon);
	}

	nextOneFromEach(locationVector);

	//system("pause");
	return 0;
}