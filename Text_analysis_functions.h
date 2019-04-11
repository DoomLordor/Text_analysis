
#ifndef Text_analysis_functions_H
#define Text_analysis_functions_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include "lem/solarix/lemmatizator_engine.h"

using namespace std;

struct fio {
	string surname, patronymic, name;
	int publish;
	vector <string> keyword;
	vector <int> frequency_keyword;
};

void vector_word(vector <string>& array_to_sort, vector <int>& frequency, string file_way); // ������ �������� ���� � �� ����������� �� ����� �� �����
void delete_english_word(vector <string>& array_to_sort, vector <int>& frequency); // �������� ���������� ���� �� ������
void delete_special_character(vector <string>& array_to_sort, vector <int>& frequency); // �������� ����������� ��������
void delete_stop_word(vector <string>& array_to_sort, vector <int>& frequency, string file_way); // �������� ���� ���� ������� ��������� � ��������������� �������
void delete_repetitions(vector <string>& array_to_sort, vector <int>& frequency); // �������� ���������� ���� 
void sort_array(vector <string>& array_to_sort, vector <int>& frequency); // ���������� ������� ���� �� �����������
void lemmatizator(vector <string>& array_to_sort); // ������������ ����
string capital_letter(string word); // �������������� ������ � ������ � ���������� ���������
void delete_frequency_one(vector <string>& array_to_sort, vector <int>& frequency); // �������� ���� �� ����� � ��������� ������������



// ������ � ���������������
void teacher_position_number(vector <int>& frequency, vector <int>& numbers); //����������� ������� �������������
void teacher_input(vector <fio>& input_array, string file_way); // ���� ��� �������������� �� ����� �� ����������
void teacher_keyword(vector <fio>& input_data, vector <string>& input_array_word, vector <int>& frequency, vector <int>& numbers); // ���������� �������������� �� �������� ����
void sort_array(vector<fio>& sort_array); // �������������� �� ��������
void teacher_profiles(vector<fio>& teachers, vector <string>& keyword, vector<vector<int>>& frequency_teachers); // �������� ����� �������������� �� ����� ����

#endif
