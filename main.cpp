#include <iostream>
#include <fstream>

struct LibraryScore
{
	int ID = 0;
	int numBooks = 0;
	int* books = NULL;
};

struct LibraryIN
{
	int numBooks = 0;
	int daysToSignUp = 0;
	int booksShippedPerDay = 0;
	int* books = NULL;
};

int main()
{
	int numLibraries;
	int numLibrariesToScore;
	int* bookScores = NULL;
	bool* bookExists = NULL;
	int numDifferentBooks = 0;
	int days = 0;
	int score = 0;

	LibraryIN* libraries = NULL;
	LibraryScore* librariesScore = NULL;

	//a_example.txt
	//b_read_on.txt
	//c_incunabula.txt
	//d_tough_choices.txt
	//e_so_many_books.txt
	//f_libraries_of_the_world.txt

	std::ifstream inFile;
	inFile.open("b_read_on.txt");
	if (inFile)
	{
		inFile >> numDifferentBooks;
		bookScores = new int[numDifferentBooks];
		bookExists = new bool[numDifferentBooks] {false};
		inFile >> numLibraries;
		libraries = new LibraryIN[numLibraries];
		inFile >> days;
		for (int i = 0; i < numDifferentBooks; i++)
		{
			inFile >> bookScores[i];
		}
		for (int i = 0; i < numLibraries; i++)
		{
			inFile >> libraries[i].numBooks;
			libraries[i].books = new int[libraries[i].numBooks];
			inFile >> libraries[i].daysToSignUp;
			inFile >> libraries[i].booksShippedPerDay;
			for (int b = 0; b < libraries[i].numBooks; b++)
			{
				inFile >> libraries[i].books[b];
			}
		}
		inFile.close();
		inFile.open("OUT_b_read_on.txt");
		if (inFile)
		{
			inFile >> numLibrariesToScore;
			librariesScore = new LibraryScore[numLibrariesToScore];
			for (int i = 0; i < numLibrariesToScore; i++)
			{
				inFile >> librariesScore[i].ID;
				inFile >> librariesScore[i].numBooks;
				librariesScore[i].books = new int[librariesScore[i].numBooks];
				for (int b = 0; b < librariesScore[i].numBooks; b++)
				{
					inFile >> librariesScore[i].books[b];
				}
			}
			inFile.close();
			for (int i = 0; i < numLibrariesToScore; i++)
			{		
				int tempDays = days - libraries[librariesScore[i].ID].daysToSignUp;
				if (tempDays > 0)
				{
					//if (libraries[librariesScore[i].ID].booksShippedPerDay % (days - libraries[librariesScore[i].ID].daysToSignUp))
					//	tempDays = libraries[librariesScore[i].ID].booksShippedPerDay * (days - libraries[librariesScore[i].ID].daysToSignUp) + 1;
					//else
					//	tempDays = libraries[librariesScore[i].ID].booksShippedPerDay * (days - libraries[librariesScore[i].ID].daysToSignUp);
					int b = 0;
					for (int d = 0; d < tempDays && b < librariesScore[i].numBooks; d++)
					{
						for (int k = 0; k < libraries[librariesScore[i].ID].booksShippedPerDay && b < librariesScore[i].numBooks; k++, b++)
						{
							for (int j = 0; j < libraries[librariesScore[i].ID].numBooks; j++)
							{
								if (!bookExists[librariesScore[i].books[b]] && librariesScore[i].books[b] == libraries[librariesScore[i].ID].books[j])
								{
									bookExists[librariesScore[i].books[b]] = true;
									score += bookScores[librariesScore[i].books[b]];
									break;
								}
							}
						}
						if (d == tempDays - 1)
							break;
					}
					days -= libraries[librariesScore[i].ID].daysToSignUp;
				}
			}
			std::cout << "Score : " << score;
		}
		else
			std::cout << "Dummy File didn't open";
	}
	else
		std::cout << "Dummy File didn't open";


}