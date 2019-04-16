#include "Text_analysis_functions.h"


int main() {
	setlocale(LC_ALL, "Russian");

	string stop_word_way = "stop_word.txt";

	cout << "Произвести анализ ключевых слов? \n";

	string anser;
	
	cin >> anser;

	if (capital_letter(anser) == "YES") {
		
		vector <string> test_word;
		vector <int> test_frequency, number_begin;
		string file_word = "word.txt", file_teacher = "list_of_teachers.txt";
		vector <fio>  teachers;

		vector_word(test_word, test_frequency, file_word);
		
		teacher_input(teachers, file_teacher);
		
		delete_english_word(test_word, test_frequency);
		
		delete_special_character(test_word, test_frequency);
		
		lemmatizator(test_word);
	
		delete_stop_word(test_word, test_frequency, stop_word_way);

		teacher_position_number(test_frequency, number_begin);
		
		teacher_keyword(teachers, test_word, test_frequency, number_begin);
		
		delete_repetitions(test_word, test_frequency);
		
		sort_array(test_word, test_frequency);
		
		delete_frequency_one(test_word, test_frequency);
		
		vector<vector<int>> frequency_teachers(teachers.size(), vector<int>(test_word.size(), 0));

		for (size_t i = 0; i < teachers.size(); i++) {
			delete_repetitions(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			sort_array(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		sort_array(teachers);

		teacher_profiles(teachers, test_word, frequency_teachers);

		ofstream output_file("output.txt");
		for (size_t i = 0; i < test_word.size(); i++) {
			output_file << test_word[i];
			for (size_t j = 0; j < 4 - (int)(test_word[i].size() / 8); j++) {
				output_file << '\t';
			}
			output_file << test_frequency[i] << endl;
		}
		output_file.close();

		ofstream output_file1("output1.txt");
		output_file1 << "\t\t\t";
		for (size_t i = 0; i < teachers.size(); i++) {
			output_file1 << '\t' << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << '.';
		}

		for (size_t i = 0; i < test_word.size(); i++) {
			output_file1 << endl << test_word[i];
			for (size_t j = 0; j < 4 - (int)(test_word[i].size() / 8); j++) {
				output_file1 << '\t';
			}
			for (size_t j = 0; j < teachers.size(); j++) {
				output_file1 << '\t' << frequency_teachers[j][i] << '\t';
			}
		}
		output_file.close();

		ofstream output_file_comparison("output_comparison.txt");
		output_file_comparison << "\t\t";
		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison << endl << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
			for (size_t j = 0; j < teachers.size(); j++) {
				if (i != j) {
					output_file_comparison << fixed;
					output_file_comparison.precision(6);
					output_file_comparison  << measure_of_closeness(frequency_teachers[i], frequency_teachers[j]) << '\t';
				}
				else {
					output_file_comparison  << "1.000000\t";
				}
			}
		}
		output_file_comparison.close();

		cout << test_word.size() << endl;
	}
	
	cout << "Произвести анализ содержания курсов? \n";
	
	cin >> anser;
	
	if (capital_letter(anser) == "YES") {
		vector <string> word_course;
		string file_word_course = "word_course.txt";

		vector_word(word_course, file_word_course);

		vector <int> frequency_course(word_course.size(), 1);

		delete_special_character(word_course, frequency_course);

		delete_stop_word(word_course, frequency_course, stop_word_way);

		delete_numbers(word_course, frequency_course);

		lemmatizator(word_course);

		delete_repetitions(word_course, frequency_course);

		sort_array(word_course, frequency_course);

		ofstream output_file_course("output_course.txt");
		for (size_t i = 0; i < word_course.size(); i++) {
			output_file_course << word_course[i] << ' ' << frequency_course[i] << endl;
		}
		output_file_course.close();
	}

	return 0;
}