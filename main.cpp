#include "Text_analysis_functions.h"


int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Произвести анализ ключевых слов? \n";

	string anser;

	cin >> anser;

	if (capital_letter(anser) == "YES") {
		
		vector <string> test_word;
		vector <int> test_frequency, number_begin;
		string file_word = "word.txt", file_teacher = "list_of_teachers.txt", stop_word_way = "stop_word.txt";
		vector <fio>  teachers;

		vector_word(test_word, test_frequency, file_word);

		teacher_input(teachers, file_teacher);

		delete_english_word(test_word, test_frequency);

		delete_special_character(test_word, test_frequency);

		delete_stop_word(test_word, test_frequency, stop_word_way);

		lemmatizator(test_word);

		teacher_position_number(test_frequency, number_begin);

		teacher_keyword(teachers, test_word, test_frequency, number_begin);

		delete_repetitions(test_word, test_frequency);

		sort_array(test_word, test_frequency);

		delete_frequency_one(test_word, test_frequency);

		vector<vector<int>> frequency_teachers(test_word.size(), vector<int>(teachers.size(), 0));

		for (size_t i = 0; i < teachers.size(); i++) {
			delete_repetitions(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			sort_array(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		teacher_profiles(teachers, test_word, frequency_teachers);

		ofstream output_file("output.txt");
		for (size_t i = 0; i < test_word.size(); i++) {
			output_file << test_word[i] << ' ' << test_frequency[i] << endl;
		}
		output_file.close();

		ofstream output_file1("output1.txt");
		output_file1 << "\t\t\t";
		for (size_t i = teachers.size() - 1; i > 0; i--) {
			output_file1 << '\t' << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << '.';
		}

		for (size_t i = 0; i < test_word.size(); i++) {
			output_file1 << endl << test_word[i];
			for (size_t j = 0; j < 4 - (int)(test_word[i].size() / 8); j++) {
				output_file1 << '\t';
			}
			for (size_t j = teachers.size() - 1; j > 0; j--) {
				output_file1 << '\t' << frequency_teachers[i][j] << '\t';
			}
		}
		output_file.close();

		cout << endl << test_word.size() << endl;
	}
	return 0;
}