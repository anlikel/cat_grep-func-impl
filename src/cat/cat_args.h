#ifndef CAT_ARGS_H
#define CAT_ARGS_H

typedef struct {
  int no_flags;
  int num_all_lines;
  int num_nonblank_lines;
  int show_endlines;
  int squeeze_blank_lines;
  int show_tabs;
  int files_count;
  char** files;
} options;

options get_opt(int argc, char* argv[]);
int get_args(int argc, char* argv[], options* opt);
void get_file_names(int argc, char* argv[], options* opt, int pos);
void clear_mem(options* opt);
void flag_setter(options* opt);

#endif