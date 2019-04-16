
#ifndef Text_analysis_functions_H
#define Text_analysis_functions_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include "lem/solarix/lemmatizator_engine.h"
#include <cmath>

using namespace std;

struct fio {
	string surname, patronymic, name;
	int publish;
	vector <string> keyword;
	vector <int> frequency_keyword;
};

void vector_word(vector <string>& array_to_sort, vector <int>& frequency, string file_way); // чтение ключевых слов и их частотности из файла из файла
void delete_english_word(vector <string>& array_to_sort, vector <int>& frequency); // удаление английских слов из списка
void delete_special_character(vector <string>& array_to_sort, vector <int>& frequency); // удаление специальных символов
void delete_stop_word(vector <string>& array_to_sort, vector <int>& frequency, string file_way); // удаление стоп слов которые находятся в соответствующем словаре
void delete_repetitions(vector <string>& array_to_sort, vector <int>& frequency); // удаление одинаковых слов 
void sort_array(vector <string>& array_to_sort, vector <int>& frequency); // сортировка масиива слов по частотности
void lemmatizator(vector <string>& array_to_sort); // лемматизация слов
string capital_letter(string word); // преобразование строки в строку с заглавными символами
void delete_frequency_one(vector <string>& array_to_sort, vector <int>& frequency); // удаление слов из мешка с еденичной частотностью
void vector_word(vector <string>& input_array, string file_way);// чтение слов из файла
void delete_numbers(vector <string>& input_array, vector <int>& frequency);//удаление цифр из списка слов
double measure_of_closeness(vector<int> first_vector, vector <int> second_vector);//косинус между векторами
double euclidean_value(vector<int> first_vector, vector <int> second_vector); // евклидова величина для определения близости векторов

// работа с преподавателями
void teacher_position_number(vector <int>& frequency, vector <int>& numbers); //определение позиций преподвателей
void teacher_input(vector <fio>& input_array, string file_way); // ввод ФИО преподавателей их числа их публикаций
void teacher_keyword(vector <fio>& input_data, vector <string>& input_array_word, vector <int>& frequency, vector <int>& numbers); // добавление преподавателям их ключевых слов
void sort_array(vector<fio>& sort_array); // преподавателей по фамилиям
void teacher_profiles(vector<fio>& teachers, vector <string>& keyword, vector<vector<int>>& frequency_teachers); // ключевые слова преподавателей из мешка слов


#endif
