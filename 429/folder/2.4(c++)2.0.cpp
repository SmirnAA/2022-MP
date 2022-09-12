#include <iostream> 
#include <string>
#include <fstream>
#define CONSONANTS "абвгдеёжзийклмннопрстуфхцчшщъыьэюя"
using namespace std;
//прототипы функции
bool dataSearch(string, int*);
bool isWordVerb(string, int*);

void Merge(string* A, int first, int last, int* diff) {
	int middle, start, final, j;
	string* mas = new string[400];
	middle = (first + last) / 2;  //вычисление среднего элемента
	start = first;                //начало левой части
	final = middle + 1;           //начало правой части
	for (j = first; j <= last; j++)  //выполнять от начала до конца
		(*diff)++;
		if ((start <= middle) && ((final > last) || (A[start].length() > A[final].length()))) {
			mas[j] = A[start];
			start++;
		}
		else {
			mas[j] = A[final];
			final++;
		}
	//возвращение результата в список
		for (j = first; j <= last; j++)
			(*diff)++;
		A[j] = mas[j];
	delete[] mas;
};
void MergeSort(string* A, int first, int last, int* diff) {
	if (first < last) {
		MergeSort(A, first, (first + last) / 2, diff);  //сортировка левой части
		MergeSort(A, (first + last) / 2 + 1, last, diff);  //сортировка правой части
		Merge(A, first, last, diff);  //слияние двух частей
	}
}
bool dataSearch(string word, int* diff) 
{
	ifstream in;
	string path = "C:\\Users\\Саша\\Desktop\\verbs.txt";
	in.open(path);
	if (!in.is_open())
	{
		cout << "Ошибка при открытии файла" << endl;
	}
	else 
	{
		string str = "";
		while (!in.eof())
		{
			(*diff)++;
			in >> str;
			if (str == word) {
				return true;
			}
		}
	}
	return false;
}


bool isWordVerb(string word, int* diff) 
{
	string end[] = { "ешь", "ут", "ют", "ать", "ять", "еть", "уть", "ыть", "оть", "ить", "ишь", "ит", "ите", "яте", "ет", "ться", "ат", "ят", "чь", "ите", "был", "ду", "ёт", "ется", "ются", "лся", "быть", "гли", "сь", "ал" };
	int p = 0;
	int count = 0;
	for (int i = 0; i < 30;i++) {
		(*diff)++;
		p= word.find(end[i]);
		count = word.find("цать");   
		if (count == word.length() - 4) {
			//cout << word<<" verb"<<endl;
			return false;
			break;
		}
		if (p == word.length() - end[i].length() and word.length()>3 and p>2) {
			//cout << word<<" verb"<<endl;
			return true;
			break;
		}
	}
	return false;
}

int main()
{
	int verbs = 0;
	int prep = 0;
	const int n = 400;
	string words[n];
	int difficulty = 0;
	int* diff =&difficulty;
	setlocale(LC_ALL, "rus");
	ifstream in;
	string path = "C:\\Users\\Саша\\Desktop\\text.txt";
	in.open(path);
	int wordsCount = 0;

	if (!in.is_open())
	{
		cout << "Ошибка при открытии файла" << endl;
	}
	else
	{
		
		string str;

		while (!in.eof())//считывем слова по пробельно до конца файла
		{
			difficulty++;
			in >> str;
			words[wordsCount] = str;
			wordsCount++;
		}
	}
	in.close();
	for (int j=0; j < n; j++) //по словам
	{
		for (int i = 0; i < words[j].length(); i++) // по буквам в каждом слове
		{
			difficulty++;
			words[j][i]=tolower(words[j][i]);// понижаем заглавные
			if (words[j][i] == '-' and i!=0 and i!= words[j].length()-1)// проверка на тире в середине слова
			{ 
				if (strchr(CONSONANTS, words[j][i - 1]) and strchr(CONSONANTS, words[j][i + 1]))
				{
					continue;
				}
			}
			if (!strchr(CONSONANTS, words[j][i]))
			{
				words[j].erase(i, 1);
				i--;
			}			
		}

		//получили слово в нижнем индексе без не литеральных символов
		
		if (words[j]=="") {
			continue;
		}
		//cout << words[j]<<endl;

		if (dataSearch(words[j],diff)) {
			cout <<words[j] << " - глагол по списку" << endl;
			verbs++;
			continue;
		}
		if (isWordVerb(words[j],diff)) {
			cout << words[j] << " - глагол по окончанию" << endl;
			verbs++;
		}
		
	}
	//vordsCount показывает количество слов в тексте
	MergeSort(words, 0,wordsCount-1, diff);
	cout << "{";
	for (int j = 0; j < wordsCount; j++) {
		if (j==wordsCount-1) cout << "'" << words[j] << "'} ";
		else cout << "'" << words[j] << "',  ";
	}

	cout <<endl<< "Total words = " << wordsCount << endl;
	cout << "Verbs = " << verbs<<endl;
	cout << "Difficulty = " << *diff<<endl;
	
	//cout << "Difficulty = " << (*diff)/wordsCount << endl;
	return 0;
}