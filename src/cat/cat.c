#include "cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat_args.h"

void print_result(options* opt);

int main(int argc, char* argv[]) {
  options cat = get_opt(argc, argv);
  print_result(&cat);
  clear_mem(&cat);
  return 0;
}

void print_result(options* opt) {
  int lines_number = 0;
  int non_blank_lines_number = 0;
  int space_flag = 0;
  for (int i = 0; i < opt->files_count; i++) {
    char buff[4096] = {0};
    FILE* fin = fopen(opt->files[i], "r");
    if (fin == NULL) {
      perror("error open file");
      continue;
    }
    while ((fgets(buff, 4096, fin)) != NULL) {
      if (opt->no_flags == 1) {
        option_without_arg(buff);
        continue;
      }

      if (opt->squeeze_blank_lines == 1) {
        space_flag = option_squeeze_nonblank_lines(buff, space_flag);
        if (strlen(buff) == 0) {
          continue;
        }
      }

      if (opt->num_all_lines == 1) {
        lines_number = option_numeration_all_lines(buff, lines_number);
      }

      if (opt->num_nonblank_lines == 1) {
        non_blank_lines_number =
            option_numeration_nonblank_lines(buff, non_blank_lines_number);
      }

      if (opt->show_endlines == 1) {
        option_show_endlines(buff);
      }

      if (opt->show_tabs == 1) {
        option_show_tab_in_lines(buff);
      }

      printf("%s", buff);
    }

    fclose(fin);
  }
}
