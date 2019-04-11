#include "Text_analysis_functions.h"



void vector_word(vector <string> &array_to_sort, vector <int>& frequency, string file_way) {
	fstream input_file(file_way);
	string word;
	size_t k = 0;
	for (size_t i = 0; !input_file.eof(); i++) {
	
		input_file >> word;

		if (((int)word[0] < 48) or ((int)word[0] > 57)) {
			array_to_sort.insert(array_to_sort.end(),word);
			k++;
		}
		else {
			for (size_t i = 0; i < k; i++){
				frequency.insert(frequency.end(), atoi(word.c_str()));
			}
			k = 0;
		}
		
	}
	input_file.close();
}

void delete_english_word(vector <string>& array_to_sort, vector <int>& frequency){

	for (size_t i = 0; i < array_to_sort.size(); i++) {
		if ( ( (int)array_to_sort[i][0] < 65) or ( (int)array_to_sort[i][0] > 122)) {
			if (array_to_sort[i].size() > 1) {
				if (((int)array_to_sort[i][1] >= 65) and ((int)array_to_sort[i][1] <= 122)) {
					array_to_sort.erase(array_to_sort.begin() + i);
					frequency.erase(frequency.begin() + i);
					i--;
				}
			}	
		}
		else {
			array_to_sort.erase(array_to_sort.begin() + i);
			frequency.erase(frequency.begin() + i);
			i--;
		}
	}
}

void delete_special_character(vector <string>& array_to_sort, vector <int>& frequency) {
	string special_character = ".,\"()";
	for (size_t i = 0; i < array_to_sort.size(); i++) {
		for (size_t j = 0; j < special_character.size(); j++) {
			while (array_to_sort[i].find(special_character[j]) != string::npos ) {
				if (array_to_sort[i].find(special_character[j]) != string::npos) {
					if (array_to_sort[i].size() == 1) {
						frequency.erase(frequency.begin() + i);
						array_to_sort.erase(array_to_sort.begin() + i);
						i--;
						j = 0;
					}
					else {
					 	array_to_sort[i].erase(array_to_sort[i].find(special_character[j]), 1);
					}
				}

			}
		}
	}
}

void delete_stop_word(vector <string>& array_to_sort, vector <int>& frequency, string file_way) {
	fstream stop_word_file(file_way);
	vector <string> stop_word;
	string word;
	for (size_t i = 0; !stop_word_file.eof(); i++) {
		stop_word_file >> word;
		word = capital_letter(word);
		stop_word.insert(stop_word.end(), word);
	}
	stop_word_file.close();
	for (size_t i = 0; i < array_to_sort.size(); i++) {
		for (size_t j = 0; j < stop_word.size(); j++) {
			if (array_to_sort[i] == stop_word[j]) {
				array_to_sort.erase(array_to_sort.begin() + i);
				frequency.erase(frequency.begin() + i);
				i--;
				break;
			}
		}
	}
}

void delete_repetitions(vector <string>& array_to_sort, vector <int>& frequency) {
	for (size_t i = 0; i < array_to_sort.size(); i++) {
		for (size_t j = i + 1; j < array_to_sort.size(); j++) {
			if (array_to_sort[j] == array_to_sort[i]) {
				array_to_sort.erase(array_to_sort.begin() + j);
				frequency[i] += frequency[j];
				frequency.erase(frequency.begin() + j);
				j--;
			}
		}
	}
}

void sort_array(vector <string>& array_to_sort, vector <int>& frequency) {
	bool flag = true;
	string y;
	int x;
	while (flag) {
		flag = false;
		for (size_t i = 0; i < frequency.size() - 1; i++) {
			if (frequency[i] < frequency[i + 1]) {
				x = frequency[i];
				frequency[i] = frequency[i + 1];
				frequency[i + 1] = x;
				y = array_to_sort[i];
				array_to_sort[i] = array_to_sort[i + 1];
				array_to_sort[i + 1] = y;
				flag = true;
			}
		}
	}

}

void teacher_position_number(vector <int>& frequency, vector <int>& numbers) {
	numbers.insert(numbers.begin(),0);
	for (size_t i = 0; i < frequency.size()-1; i++) {
		if (frequency[i] < frequency[i + 1]) {
			numbers.insert(numbers.end(), i + 1);
		}
	}
	numbers.insert(numbers.end(), frequency.size()-1);
}

void lemmatizator(vector <string>& array_to_sort) {
	HLEM hEngine = sol_LoadLemmatizatorA("lemmatizer.db", LEME_DEFAULT);
	char res_word[256];
	for (size_t i = 0; i < array_to_sort.size(); i++) {

		int res = sol_GetLemmaA(hEngine, array_to_sort[i].c_str(), res_word, sizeof(res_word));

		string res_word_str = capital_letter(string(res_word));
		
		if (array_to_sort[i].c_str() != res_word_str) {
			array_to_sort[i] = res_word_str;
		}
	}
	sol_DeleteLemmatizator(hEngine);
}

string capital_letter(string word) {
	for (size_t i = 0; i < word.size(); i++) {
		word[i] = toupper(word[i]);
	}
	return word;
}

void teacher_input(vector <fio>& input_data, string file_way) {
	fstream input_file(file_way);
	fio data_acquisition;
	while (!input_file.eof()) {
		input_file >> data_acquisition.surname >> data_acquisition.name >> data_acquisition.patronymic >> data_acquisition.publish;
		input_data.insert(input_data.end(), data_acquisition);
	}
}

void teacher_keyword(vector <fio>& input_data, vector <string>& input_array_word, vector <int>& frequency, vector <int>& numbers){
	for (size_t i = 0; i < input_data.size(); i++) {
		input_data[i].keyword.insert(input_data[i].keyword.end(),&input_array_word[numbers[i]],&input_array_word[numbers[i+1]]);
		input_data[i].frequency_keyword.insert(input_data[i].frequency_keyword.end(), &frequency[numbers[i]], &frequency[numbers[i + 1] ]);
	}
	input_data[input_data.size() - 1].keyword.insert(input_data[input_data.size() - 1].keyword.end(), input_array_word[input_array_word.size()-1]);
	input_data[input_data.size() - 1].frequency_keyword.insert(input_data[input_data.size() - 1].frequency_keyword.end(), frequency[ frequency.size() - 1]);
}

void delete_frequency_one(vector <string>& array_to_sort, vector <int>& frequency) {
	for (size_t i = 0; i < frequency.size(); i++) {
		if (frequency[i] == 1) {
			frequency.erase(frequency.begin() + i, frequency.end());
			array_to_sort.erase(array_to_sort.begin() + i, array_to_sort.end());
		}

	}
}

void teacher_profiles(vector<fio>& teachers, vector <string>& keyword, vector<vector<int>>& frequency_teachers) {
	for (size_t i = 0; i < teachers.size(); i++) {
		for (size_t j = 0; j < keyword.size(); j++) {
			for (size_t k = 0; k < teachers[i].keyword.size(); k++) {
				if (teachers[i].keyword[k] == keyword[j]) {
					frequency_teachers[j][i] = teachers[i].frequency_keyword[k];
				}
			}
		}
	}
}

void sort_array(vector<fio>& sort_array) {
	bool flag = true;
	fio buf;
	while (flag) {
		flag = false;
		for (size_t i = 0; i < sort_array.size() - 1; i++) {
			for (size_t j = 0; (j < sort_array[i].surname.size()) && (j < sort_array[i+1].surname.size()); j++) {
				if ((int)sort_array[i].surname[j] > (int)sort_array[i + 1].surname[j]) {
					buf = sort_array[i];
					sort_array[i] = sort_array[i + 1];
					sort_array[i + 1] = buf;
					flag = true;
					break;
				}
				else {
					if ((int)sort_array[i].surname[j] < (int)sort_array[i + 1].surname[j]) {
						break;
					}
				}
			}
		}
		
	}
	
}

















































