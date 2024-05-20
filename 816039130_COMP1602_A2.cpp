#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstring>
#include<ctime>

// 816039130- DEVERN CHATTERGOON- COMP1602 A2

using namespace std;


struct Puzzle{
	string category;
	char puzzle[80];
};

void stringToCString(string word, char cString[])
{
	int size = word.length() + 1;
	cString[size];
	for(int i=0;i<size-1;i++)
	{
		cString[i] = word[i];
	}
	cString[size-1] = '\0';
}

void upperToLower(char str[])
{
	int i=0;
	while(str[i] != '\0')
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + ' ';
		}
		i++;
	}
}

char lowerToUpperLetter(char c)
{
	if(c >= 'a' && c <= 'z')
		return (c - ' ');
	else if (c >= 'A' && c <= 'Z')
		return c;
	else
		return c;
}

void removeNonLettersCString(char str[])
{
	char temp[25];
	int i=0, j=0;
	
	while(str[i] != '\0')
	{
		if(str[i] >= 'A' && str[i] <= 'z')
		{
			temp[j] = str[i];
			j++;	
		}
		i++;
	}
	temp[j] = '\0';
	strcpy(str,temp);
}

string removeNonLetters(string word)
{
	int size = word.length() + 1;
	char cString[size], temp[size];
	int i=0, j=0;
	stringToCString(word, cString);
	
	while(cString[i] != '\0')
	{
		if(cString[i] >= 'A' && cString[i] <= 'z')
		{
			temp[j] = cString[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	upperToLower(temp);
	word = temp;
	return word;
}

int readCategories(string category[])
{
	ifstream in;
	char cword[80];
	int i=0;
	
	in.open("Categories.txt");
	if(!in.is_open())
	{
		cout << "Error opening Categories file...";
		exit(1);
	}
	
	in.getline(cword, 80);
	while(!in.eof())
	{
		category[i]= cword;
		i++;
		in.getline(cword, 80);
	}
	in.close();
	return i;
}

int readPuzzles(Puzzle puzzle[])
{
	ifstream in;
	int i=0;
	char cCategory[80];
	
	in.open("WOF-Puzzles.txt");
	if(!in.is_open())
	{
		cout << "Error opening Categories file...";
		exit(1);
	}
	
	in.getline(cCategory, 80);
	while(!in.eof())
	{
		puzzle[i].category = cCategory;
		in.getline(puzzle[i].puzzle, 80);
		i++;
		in.getline(cCategory, 80);
	}
	in.close();
	return i;
}

string chooseCategory(string category[], int size)
{
	int choice;

	int random1 = rand() % size;
	string choice1 = category[random1];
	
	
	int random2 = rand() % size;
	while(random2 == random1)
	{
		random2 = rand() % size;
	}
	string choice2 = category[random2];
	
	
	int random3 = rand() % size;
	while(random3 == random1 || random3 == random2)
	{
		random3 = rand() % size;
	}
	string choice3 = category[random3];
	
	string decision;
	cout << "Please choose from one of the following categories:"<<endl<<endl;
	cout << "1. "<<choice1<<"\n2. "<<choice2<<"\n3. "<<choice3<<endl<<endl;
	cout << "Your choice? ";
	cin >> choice;
	
	if(choice == 1)
		decision = choice1;
	else if(choice == 2)
		decision = choice2;
	else if(choice == 3)
		decision = choice3;
	
	cout << endl << "Category chosen for bonus round is: "<<decision<<endl<<endl;
	
	return decision;
}

void decryptPuzzle(char str[], char decrypt[])
{
	int i=0;
	while(str[i] != '\0')
	{
		if(str[i] >= 'F' && str[i] <= 'Z')
		{
			decrypt[i] = str[i] - 5;  
		}
		else if(str[i] >= 'A' && str[i] <= 'E')
		{
			decrypt[i] = (str[i] - 'A') + 'V';
		}
		else
			decrypt[i] = str[i];
		i++;
	}
}

void blankOutPuzzle(char str[], char blocked[])
{
	int i=0;
	while(str[i] != '\0')
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			blocked[i] = '#';
		else
			blocked[i] = str[i];
		i++;
	}
}


void choosePuzzle(Puzzle puzzle[], string decision, int size, char key[], char blocked[])
{
	decision = removeNonLetters(decision);
	int random;
	string match;
	char encrypted[80];
	
	random = rand() % size;
	match = puzzle[random].category;
	match = removeNonLetters(match);
	while(match.compare(decision) != 0)
	{
		if(match.compare(decision) == 0)
			break;
		else
		{
			random = rand() % size;
			match = puzzle[random].category;
			match = removeNonLetters(match);
		}
	}
	
	strcpy(encrypted, puzzle[random].puzzle);
	decryptPuzzle(encrypted, key);
	blankOutPuzzle(key, blocked);
	cout <<endl<< "The puzzle to start with is: " <<blocked<< endl;
}

bool hasWildcard(int answer)
{
	if(answer == 1)
		return true;
	else
		return false;
}
void rstlne(char key[], char block[])
{
	int i=0;
	while(key[i] != '\0')
	{
		if(key[i] == 'R')
			block[i] = 'R';
		else if(key[i] == 'S')
			block[i] = 'S';
		else if(key[i] == 'T')
			block[i] = 'T';
		else if(key[i] == 'L')
			block[i] = 'L';
		else if(key[i] == 'N')
			block[i] = 'N';
		else if(key[i] == 'E')
			block[i] = 'E';	
		i++;
	}
//	cout << key << endl;
	cout << "\nRevealing R, S, T, L, N, E...\n\n";
	cout <<"The puzzle is now: "<< block << endl;
}

void revealLetter(char key[], char blocked[], char guess[])
{
	int i=0;
	while(key[i] != '\0')
	{
		int j=0;
		while(guess[j] != '\0')
		{
			guess[j] = lowerToUpperLetter(guess[j]);
			if(key[i] == guess[j])
				blocked[i] = guess[j];
			j++;
		}	
		i++;
	}
	cout << "The puzzle is now: " <<blocked<<endl;
}

void revealPrize()
{
	cout << "\n\nCongratulations! You got it out!\n";
	cout << "OK, let's see your prize.\n";
	cout << "It is ..... ";

	int random = 1 + rand() % 25;
	if(random <= 3)
		cout << "A brand new Car";
	else if(random <= 22)
		cout << "$40,000.00";
	else if (random <= 24)
		cout << "$45,000.00";
	else
		cout << "\n\nCongrats!\nYou hit the jackpot! ($100,000.00)";
}

int main()
{
	srand(time(NULL));
	//srand(100);
	int categoryCount, puzzleCount;
	Puzzle puzzle[1125];
	string category[50];
	char key[80], tempKey[80], blocked[80];
	int wildcard;
	char additional[2];
	
	categoryCount = readCategories(category);
	puzzleCount = readPuzzles(puzzle);
	
	cout << "# of categories read from the file: "<<categoryCount<<endl<<endl;
	cout << "# of puzzles read from the file: "<<puzzleCount<<endl<<endl;
	
	string choice = chooseCategory(category, categoryCount);
	
	choosePuzzle(puzzle, choice, puzzleCount, key, blocked);
	rstlne(key, blocked);
	

	cin.ignore(INT_MAX, '\n');
	char guess[20]="";
	cout << "\n\nPlease enter three consonants and a vowel: ";
	cin.getline(guess, 20);
	removeNonLettersCString(guess);
	cout << "Do you have the wildcard?  (0-No, 1-Yes) ";
	cin >> wildcard;
	if(hasWildcard(wildcard))
	{
		cin.ignore(INT_MAX, '\n');
		int guessLength = strlen(guess);
		cout << "Since you have the wildcard, please enter another consonant: ";
		cin.getline(additional, 2);
		guess[guessLength] = additional[0];
		guess[guessLength+1] = '\0';
		removeNonLettersCString(guess);
		revealLetter(key, blocked, guess);
	} 
	else
	{
		removeNonLettersCString(guess);
		revealLetter(key, blocked, guess);
		cin.ignore(INT_MAX, '\n');
	}
	
	
	if(strcmp(blocked, key) == 0)
	{
			revealPrize();
			exit(0);
	}
	
	strcpy(tempKey, key);
	upperToLower(tempKey);
	
	for(int i=2;i>=0;i--)
	{
		char wordGuess[80];
		cout << "\nMake guess:\n";
		cin.getline(wordGuess, 80);
		
		upperToLower(wordGuess);
		int comparison = strcmp(tempKey, wordGuess);
		if(comparison == 0)
		{
			revealPrize();
			exit(0);
		}
		else
		{
			cout << "\nSorry. "<<wordGuess<<" is not correct."<<endl;
			cout << "You have "<<i<< " tries left.\n";
		}
	}
	cout << "\nI am sorry. You will not get a prize."<<endl;
	cout << "The puzzle is "<<key;
	
}
