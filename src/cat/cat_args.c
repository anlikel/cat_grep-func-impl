#include "cat_args.h"

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

  while (i < argc && argv[i][0] == '-') {
    if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
      opt->num_all_lines = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-b") == 0 ||
               strcmp(argv[i], "--number-nonblank") == 0) {
      opt->num_nonblank_lines = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-ev") == 0 ||
               strcmp(argv[i], "-E") == 0) {
      opt->show_endlines = 1;
      i++;
      opt_count++;
    }

    else if (strcmp(argv[i], "-s") == 0 ||
             strcmp(argv[i], "--squeeze-blank") == 0) {
      opt->squeeze_blank_lines = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-tv") == 0 ||
               strcmp(argv[i], "-T") == 0) {
      opt->show_tabs = 1;
      i++;
      opt_count++;
    } else if (strcmp(argv[i], "-v") == 0) {
      i++;
      continue;
    } else {
      perror("arg input error");
      exit(1);
    }
  }
  if (opt_count == 0) {
    opt->no_flags = 1;
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

void clear_mem(options *opt) { free(opt->files); }

void flag_setter(options *opt) {
  if (opt->num_nonblank_lines == 1) {
    opt->num_all_lines = 0;
  }
}