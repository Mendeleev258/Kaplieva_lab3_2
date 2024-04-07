#include <iostream>
#include <fstream>

const int n = 35;
const int m = 15;
const int LEN = 255;

// interface

bool is_token(char c);
void skip_token(std::ifstream& file, char& c);
int read_word(std::ifstream& file, char& c, char* word);
void create_matrix(std::ifstream& file, char matrix[][m], int len[], int& row);
int check_file(std::ifstream& file);
void print_word(char word[], int len, bool draft = false);
void print_matrix(char matrix[][m], int len[], int row, const char* message, bool draft = false);

// task

bool is_vowel(char c);
bool correct_word(char* word, int len);


int main()
{
	std::ifstream input("inp.txt");
	switch (check_file(input))
	{
	case -1:
		std::cout << "File is not found\n";
		break;
	case 0:
		std::cout << "Empty file\n";
		break;
	default:
		std::cout << "Correct file\n";
		/*char matrix[35][15]; 
		int len[35];
		int row{};
		bool draft = false;
		create_matrix(input, matrix, len, row);
		print_matrix(matrix, len, row, "");*/
		
		
	}
}

// interface

bool is_token(char c)
{
	return (c == ' ' || c == ',' || c == ';' || c == ':' || c == '\n' || c == '.' || c == '-' || c == EOF);
}

void skip_token(std::ifstream& file, char& c)
{
	while (!file.eof() && is_token(c))
		c = file.get();
}

int read_word(std::ifstream& file, char& c, char* word)
{
	int len{};
	while (!file.eof() && !is_token(c))
	{
		word[len++] = c;
		c = file.get();
	}
	return len;
}

void create_matrix(std::ifstream& file, char matrix[][m], int len[], int& row)
{
	row = 0;
	char c = file.get();
	while (!file.eof())
	{
		skip_token(file, c);
		if (!is_token(c))
		{
			len[row] = read_word(file, c, matrix[row]);
			++row;
		}
	}
}

int check_file(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1; // Файл не найден!
	}
	else
		if (file.peek() == EOF)
			res = 0; // Файл пустой!
	return res;
}

void print_word(char word[], int len, bool draft)
{
	if (draft)
		std::cout << '=';
	for (int i = 0; i < len; ++i)
		std::cout << word[i];
	std::cout << (draft ? "=" : "") << '\n';
}

void print_matrix(char matrix[][m], int len[], int row, const char* message, bool draft)
{
	std::cout << message << '\n';
	for (int i = 0; i < row; ++i)
	{
		print_word(matrix[i], len[i], draft);
		if (draft)
			std::cout << "---------------------------\n";
	}
}

// task

bool is_vowel(char c)
{
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'y' || c == 'Y';
}

bool correct_word(char* word, int len)
{
	int i{};
	bool res{ true };
	while (i < len && res)
	{
		if (i % 2 == 0 && is_vowel(word[i]))
			res = false;
		else
			if (i % 2 != 0 && !is_vowel(word[i]))
				res = false;
		++i;
	}
	return res;
}


