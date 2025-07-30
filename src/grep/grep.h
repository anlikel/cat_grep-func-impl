#ifndef GREP_H
#define GREP_H

void to_lower_case(char* buff);
int find_substring_ignore_case(char* buff, char** patterns, int patterns_count);
int return_match(char* buff, char** patterns, int patterns_count);
void print_matching_lines_count(char* file, int files_count, int count);

void show_matching(char* buff, char* file, int files_count, char** patterns,
                   int patterns_count);
int show_count_matching_strings(char* buff, char** patterns, int patterns_count,
                                int count, int inversion_flag,
                                int ignore_case_flag);
int show_matching_files(char* buff, char** patterns, int patterns_count,
                        int inversion_flag, int ignore_case_flag);
void show_matching_with_args(char* buff, char* file, int files_count,
                             char** patterns, int patterns_count,
                             int inversion_flag, int ignore_case_flag,
                             int lines_number_flag, int line_number);

#endif