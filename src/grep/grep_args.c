#include "grep_args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

options get_opt(int argc, char *argv[]) {
  options opt = {0};
  int arg_position = get_args(argc, argv, &opt);
  get_file_names(argc, argv, &opt, arg_position);
  flag_setter(&opt);

  return opt;
}

int get_args(int argc, char *argv[], options *opt) {
  int i = 1;
  int opt_count = 0;
  opt->patterns = (char **)malloc(argc * sizeof(char *));

  while (i < argc && argv[i][0] == '-') {
    if (strcmp(argv[i], "-e") == 0) {
      opt->pattern = 1;
      i++;
      opt->patterns[opt->patterns_count] = argv[i];
      opt->patterns_count++;
      i++;
    } else if (strcmp(argv[i], "-i") == 0) {
      opt->ignore_case_flag = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-v") == 0) {
      opt->invert_matches = 1;
      i++;
      opt_count++;
    }

    else if (strcmp(argv[i], "-c") == 0) {
      opt->show_matching_lines_count = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-l") == 0) {
      opt->show_matching_files = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-n") == 0) {
      opt->show_lines_with_number = 1;
      i++;
      opt_count++;
    } else {
      perror("arg input error");
      exit(1);
    }
  }
  if (opt_count == 0 && opt->pattern >= 0) {
    opt->no_flags = 1;
  }
  if (opt->pattern == 0) {
    opt->patterns[opt->patterns_count] = argv[i];
    opt->patterns_count++;
    opt->pattern = 1;
    i++;
  }
  return i;
}

void get_file_names(int argc, char *argv[], options *opt, int pos) {
  opt->files = (char **)malloc(argc * sizeof(char *));
  int i = pos;
  int j = 0;
  while (i < argc) {
    opt->files[j] = argv[i];
    j++;
    i++;
  }
  opt->files_count = j;
}

void clear_mem(options *opt) {
  free(opt->files);
  free(opt->patterns);
}

void flag_setter(options *opt) {
  if (opt->show_matching_files == 1) {
    opt->no_flags = 0;
    opt->show_matching_lines_count = 0;
    opt->show_lines_with_number = 0;
  } else if (opt->show_matching_lines_count == 1) {
    opt->no_flags = 0;
    opt->show_lines_with_number = 0;
  }
}