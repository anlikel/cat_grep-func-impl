#ifndef CAT_H
#define CAT_H

void print_tab(char *buff);
int is_string_with_spaces(char *buff);
void addDollar(char *buff);
int is_string_empty(char *buff);

void option_without_arg(char *buff);
int option_numeration_all_lines(char *buff, int c);
int option_numeration_nonblank_lines(char *buff, int c);
void option_show_endlines(char *buff);
int option_squeeze_nonblank_lines(char *buff, int space);
void option_show_tab_in_lines(char *buff);

#endif