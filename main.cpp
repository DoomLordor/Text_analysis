#include "Text_analysis_functions.h"


int main() {
	setlocale(LC_ALL, "Russian");

	string stop_word_way = "stop_word.txt";

	cout << "ѕроизвести анализ ключевых слов? \n";

	string anser = "yes";
	
	//cin >> anser;

	if (capital_letter(anser) == "YES") {
		
		vector <string> Keywords;
		vector <int> frequency_keywords, number_begin;
		string file_word = "word.txt", file_teacher = "list_of_teachers.txt";
		vector <fio>  teachers;

		vector_word(Keywords, frequency_keywords, file_word);
		
		teacher_input(teachers, file_teacher);
		
		delete_english_word(Keywords, frequency_keywords);
		
		delete_special_character(Keywords, frequency_keywords);
		
		lemmatizator(Keywords);
	
		delete_stop_word(Keywords, frequency_keywords, stop_word_way);

		teacher_position_number(frequency_keywords, number_begin);
		
		teacher_keyword(teachers, Keywords, frequency_keywords, number_begin);
		
		delete_repetitions(Keywords, frequency_keywords);
		
		sort_array(Keywords, frequency_keywords);
		
		delete_frequency_one(Keywords, frequency_keywords);
		
		vector<vector<int>> frequency_teachers(teachers.size(), vector<int>(Keywords.size(), 0));

		for (size_t i = 0; i < teachers.size(); i++) {
			delete_repetitions(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			sort_array(teachers[i].keyword, teachers[i].frequency_keyword);
		}

		sort_array(teachers);

		teacher_profiles(teachers, Keywords, frequency_teachers);
		//вывод профил€ кафедры
		ofstream output_file("output.txt");
		for (size_t i = 0; i < Keywords.size(); i++) {
			output_file << Keywords[i];
			for (size_t j = 0; j < 4 - (int)(Keywords[i].size() / 8); j++) {
				output_file << '\t';
			}
			output_file << frequency_keywords[i] << endl;
		}
		output_file.close();
		// вывод матрицы слово - преподватель
		ofstream output_file1("output1.txt");
		output_file1 << "\t\t\t";
		for (size_t i = 0; i < teachers.size(); i++) {
			output_file1 << '\t' << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << '.';
		}

		for (size_t i = 0; i < Keywords.size(); i++) {
			output_file1 << endl << Keywords[i];
			for (size_t j = 0; j < 4 - (int)(Keywords[i].size() / 8); j++) {
				output_file1 << '\t';
			}
			for (size_t j = 0; j < teachers.size(); j++) {
				output_file1 << '\t' << frequency_teachers[j][i] << '\t';
			}
		}
		output_file.close();
		// вывод косинусной меры близости 
		ofstream output_file_comparison_cos("output_comparison_cos.txt");
		output_file_comparison_cos << "\t\t";
		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison_cos << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison_cos << endl << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
			for (size_t j = 0; j < teachers.size(); j++) {
				if (i != j) {
					output_file_comparison_cos << fixed;
					output_file_comparison_cos.precision(6);
					output_file_comparison_cos << measure_of_closeness(frequency_teachers[i], frequency_teachers[j]) << '\t';
				}
				else {
					output_file_comparison_cos << "1.000000\t";
				}
			}
		}
		output_file_comparison_cos.close();
		
		// вывод евклидовой меры близости
		ofstream output_file_comparison_evcl("output_comparison_evcl.txt");
		output_file_comparison_evcl << "\t\t";
		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison_evcl << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
		}

		for (size_t i = 0; i < teachers.size(); i++) {
			output_file_comparison_evcl << endl << teachers[i].surname << ' ' << teachers[i].name[0] << '.' << teachers[i].patronymic[0] << ".\t";
			for (size_t j = 0; j < teachers.size(); j++) {
				output_file_comparison_evcl << fixed;
				output_file_comparison_evcl.precision(6);
				output_file_comparison_evcl << euclidean_value(frequency_teachers[i], frequency_teachers[j]) << '\t';
			}
		}
		output_file_comparison_evcl.close();

		cout << Keywords.size() << endl;
	}
	
	cout << "ѕроизвести анализ содержани€ курсов? \n";
	anser = "NO";
	//cin >> anser;
	
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