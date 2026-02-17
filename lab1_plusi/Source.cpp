#include <iostream>  
#include <sstream>  
#include <string>
#include <vector>
#include <fstream>
#include <locale>

using namespace std;

int mid_align(int str_size, string filename) {
	ifstream text;
	text.open(filename, ios::in); //ios::in файл открывается для чтения

	string line; //строка
	vector<string> words; //разбитые слова со строки
	vector<vector<string>> text_lines; // все разбитые слова со строк
	
	//добавление строк в вектор
	while (getline(text, line))
	{
		istringstream line_stream(line);
		istream_iterator<string> iter(line_stream);
		istream_iterator<string> end;

		while (iter != end) {
			words.push_back(*iter);
			
			if (iter->length() > str_size) { //проверка длин отдельных слов
				cout << "Есть слишком длинное слово, нельзя разбить\n";
				return -1;
			}
			
			++iter;
		}
		text_lines.push_back(words);
		words.clear();
	}

	//перенос слов
	auto text_lines_it = text_lines.begin();
	while (text_lines_it != text_lines.end()) {
		vector<string>& cur_line = *text_lines_it; //ссылка чтобы сразу менять элемент в самом векторе
		
		int cur_len = 0;
		for (const auto& word : cur_line) {
			cur_len += word.length();
		}
		cur_len += cur_line.size() - 1; //пробелы

		if (cur_len > str_size) {
			vector<string> excess_words;
			int cnt_len = 0;//перебираю слова и считаю их длины
			int new_len = 0;

			for (auto word = cur_line.begin(); word != cur_line.end(); word++) {
				new_len = cnt_len + (*word).length() + (cnt_len > 0 ? 1 : 0);

				if (new_len <= str_size) {
					cnt_len = new_len;
				}
				else {
					excess_words.assign(word, cur_line.end()); //скопировали все лишние слова в другой вектор
					cur_line.erase(word, cur_line.end()); //удалили их из начального вектора
					text_lines_it = text_lines.insert(text_lines_it + 1, excess_words); //т.к прошлый итератор стал недействительным
					//text_lines_it указывает на вставленный вектор лишних слов из прошлой строки
					break;
				}
			}
		}
		else {
			++text_lines_it; //если не было вставки
		}
	}

	//добавление пробелов
	for (auto line : text_lines) {
		int line_len = 0;
		int space_num = 0;
		int right_num = 0;
		int left_num = 0;

		for (auto word : line) {
			line_len += word.length();
		}
		line_len += (line.size() - 1); //пробелы

		space_num = str_size - line_len;
		left_num = space_num / 2;
		right_num = space_num - left_num;

		cout << "|";
		for (int i = 0; i < left_num; i++) {
				cout << " ";
		}
			
		for (int i = 0; i < line.size(); i++) {
			cout << line[i];
			if (i != line.size() - 1) {
				cout << " ";
			}
		}
			
		for (int i = 0; i < right_num; i++) {
				cout << " ";
		}
		cout << "|";

		cout << "\n";
	}
	return 1;
}

int main() {
	setlocale(LC_ALL, "");

	string filename;
	int str_size;
	
	cout << "Имя файла: ";
	cin >> filename;
	cout << "Размер строки: ";
	cin >> str_size;
	cout << "\n";

	mid_align(str_size, filename);
}