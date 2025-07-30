#include "grep.h"

#include <stdio.h>
#include <stdlib.h>

#include "grep_args.h"

void print_result(options* opt);

int main(int argc, char* argv[]) {
  options grep = get_opt(argc, argv);

  print_result(&grep);

  clear_mem(&grep);

  return 0;
}

void print_result(options* opt) {
  for (int i = 0; i < opt->files_count; i++) {
    int matching_lines = 0;
    int matching_file = 0;
    int line_number = 0;
    char buff[4096] = {0};
    FILE* fin = fopen(opt->files[i], "r");
    if (fin == NULL) {
      perror("error open file");
      continue;
    }
    while ((fgets(buff, 4096, fin)) != NULL) {
      line_number++;

      if (opt->show_matching_files == 1) {
        matching_file +=
            show_matching_files(buff, opt->patterns, opt->patterns_count,
                                opt->invert_matches, opt->ignore_case_flag);
        continue;
      }

      if (opt->show_matching_lines_count == 1) {
        matching_lines = show_count_matching_strings(
            buff, opt->patterns, opt->patterns_count, matching_lines,
            opt->invert_matches, opt->ignore_case_flag);
        continue;
      }

      if (opt->no_flags == 1) {
        show_matching(buff, opt->files[i], opt->files_count, opt->patterns,
                      opt->patterns_count);
      }

      if (opt->no_flags == 0) {
        show_matching_with_args(buff, opt->files[i], opt->files_count,
                                opt->patterns, opt->patterns_count,
                                opt->invert_matches, opt->ignore_case_flag,
                                opt->show_lines_with_number, line_number);
      }
      printf("%s", buff);
    }

    if (opt->show_matching_lines_count == 1) {
      print_matching_lines_count(opt->files[i], opt->files_count,
                                 matching_lines);
    }
    if (opt->show_matching_files == 1 && matching_file != 0) {
      printf("%s\n", opt->files[i]);
    }

    fclose(fin);
  }
}