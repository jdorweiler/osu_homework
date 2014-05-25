#include<iostream>
#include <iomanip>
#include<string>

using namespace std;

bool errorCheck(string);
void firstLetter(string);
void wordTranslate(string);

int main()
{
	string wordInput=""; //array
	bool inputError = false;
	char runSentinel = 'y';
	cout << "			----------------------\n" << endl;
	cout << "			PIG LATIN TRANSLATOR \n" << endl;
	cout << "			----------------------\n" << endl;
	//cin.get();

	cout << "Welcome to the Pig Latin Translator. \n" << endl;
	cout << "Would you like to translate a word? (y/n)";
	cin >> runSentinel;

	do
	{

		if (runSentinel == 'y')
		{
		cout << "Please enter the word you would like to be translated, \n" << endl;
		cout << "and please use only lower case letters. \n" << endl;
		cin >> wordInput;
		inputError = errorCheck(wordInput);
		}

		if (inputError == false)
		{
			firstLetter(wordInput);
			//();
		}
		cin.ignore();
	cout << "Would you like to translate a word? (y/n)";
	cin >> runSentinel;


	} while (runSentinel != 'n');
	return 0;
}

	bool errorCheck(string wordInput)
	{
		bool errorVerif = false;
		int Length = wordInput.length();
		int Counter = 0;
		char *specificLetter = &wordInput.at(0);

		while (Counter < Length && errorVerif == false)
		{
			if (!isalpha(*specificLetter))
			{
				cout << *specificLetter << "is not an acceptable entry. Please re-enter your word.";
				errorVerif = true;
			}

			if (isspace(*specificLetter))
			{
				cout << *specificLetter << "is not an acceptable entry. Please re-enter your word.";
				errorVerif = true;
			}

			cout << "*specificLetter:" << *specificLetter << endl;
			*specificLetter++;
			Counter++;

		}
		return errorVerif;
	}

	void firstLetter(string wordInput)
	{
		char firstLetter;
		firstLetter = wordInput.at(0);

		if (firstLetter == 'a' || firstLetter == 'e' || firstLetter == 'i' || firstLetter == 'o' || firstLetter == 'u')
		{
			cout << "In Pig Latin, that would be " << wordInput << "way" << endl;
		}
		else
		{
			wordTranslate(wordInput);
		}
	}

	void wordTranslate(string wordInput)
	{
		char firstLetter;
		char lastLetter = wordInput.length();

		firstLetter = wordInput.at(0);
		string otherLetters = wordInput.substr((1), (lastLetter - 1));
		cout << "In Pig Latin, that would be " << otherLetters << firstLetter << "ay." << endl;
	}
