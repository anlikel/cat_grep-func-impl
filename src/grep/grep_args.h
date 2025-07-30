#ifndef GREP_ARGS_H
#define GREP_ARGS_H

typedef struct {
  int no_flags;
  int pattern;
  int ignore_case_flag;
  int invert_matches;
  int show_matching_lines_count;
  int show_matching_files;
  int show_lines_with_number;

  int patterns_count;
  char** patterns;

  int files_count;
  char** files;
} options;

options get_opt(int argc, char* argv[]);
int get_args(int argc, char* argv[], options* opt);
void get_file_names(int argc, char* argv[], options* opt, int pos);
void clear_mem(options* opt);
void flag_setter(options* opt);

#endif