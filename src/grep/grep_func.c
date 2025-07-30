#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep.h"

int return_match(char* buff, char** patterns, int patterns_count) {
  int flag = 0;
  for (int i = 0; i < patterns_count; i++) {
    if (strstr(buff, patterns[i]) != NULL) {
      flag = 1;
      break;
    }
  }
  return flag;
}

void show_matching_with_args(char* buff, char* file, int files_count,
                             char** patterns, int patterns_count,
                             int inversion_flag, int ignore_case_flag,
                             int lines_number_flag, int line_number) {
  char temp[4096] = {0};
  int check_ignore = 1;
  int check_inversion = 1;

  if (ignore_case_flag == 1 && inversion_flag == 0) {
    check_ignore = find_substring_ignore_case(buff, patterns, patterns_count);
  }

  if (inversion_flag == 1 && ignore_case_flag == 0) {
    if (return_match(buff, patterns, patterns_count) == 0) {
      check_inversion = 1;
    }
    if (return_match(buff, patterns, patterns_count) == 1) {
      check_inversion = 0;
    }
  }

  if (inversion_flag == 1 && ignore_case_flag == 1) {
    if (find_substring_ignore_case(buff, patterns, patterns_count) == 1) {
      check_inversion = 0;
    }
  }

  int res = check_ignore * check_inversion;

  if (inversion_flag == 0 && ignore_case_flag == 0) {
    res = return_match(buff, patterns, patterns_count);
  }

  if (res == 1) {
    if (lines_number_flag == 1) {
      sprintf(temp, "%d:%s", line_number, buff);
      memmove(buff, temp, 4096);
    }
    if (files_count == 1) {
      sprintf(temp, "%s", buff);
      memmove(buff, temp, 4096);
    } else {
      sprintf(temp, "%s:%s", file, buff);
      memmove(buff, temp, 4096);
    }
  }
  memmove(buff, temp, 4096);
}

int find_substring_ignore_case(char* buff, char** patterns,
                               int patterns_count) {
  char string[4096] = {0};
  char pat[4096] = {0};
  int flag = 0;
  for (int i = 0; i < patterns_count; i++) {
    memmove(string, buff, 4096);
    memmove(pat, patterns[i], strlen(patterns[i]) + 1);
    to_lower_case(string);
    to_lower_case(pat);
    if (strstr(string, pat) != NULL) {
      flag = 1;
      break;
    }
  }
  return flag;
}

void to_lower_case(char* buff) {
  char* p = buff;
  while (*p != '\0') {
    *p = tolower(*p);
    p++;
  }
}

void show_matching(char* buff, char* file, int files_count, char** patterns,
                   int patterns_count) {
  char temp[4096] = {0};
  if (return_match(buff, patterns, patterns_count) == 1) {
    if (files_count == 1) {
      sprintf(temp, "%s", buff);
      memmove(buff, temp, 4096);
    } else {
      sprintf(temp, "%s:%s", file, buff);
      memmove(buff, temp, 4096);
    }
  } else {
    memmove(buff, temp, 4096);
  }
}

int show_count_matching_strings(char* buff, char** patterns, int patterns_count,
                                int count, int inversion_flag,
                                int ignore_case_flag) {
  int c = count;
  int res = 0;

  if (ignore_case_flag == 1) {
    res = find_substring_ignore_case(buff, patterns, patterns_count);
    if (inversion_flag == 1) {
      if (res == 1) {
        res = 0;
      } else if (res == 0) {
        res = 1;
      }
    }
  }

  if (ignore_case_flag == 0) {
    res = return_match(buff, patterns, patterns_count) == 1;
    if (inversion_flag == 1) {
      if (res == 1) {
        res = 0;
      } else if (res == 0) {
        res = 1;
      }
    }
  }

  if (res == 1) {
    c++;
  }
  return c;
}

void print_matching_lines_count(char* file, int files_count, int count) {
  if (files_count == 1) {
    printf("%d\n", count);
  } else {
    printf("%s:%d\n", file, count);
  }
}

int show_matching_files(char* buff, char** patterns, int patterns_count,
                        int inversion_flag, int ignore_case_flag) {
  int res = 0;
  if (ignore_case_flag == 1) {
    res = find_substring_ignore_case(buff, patterns, patterns_count);
    if (inversion_flag == 1) {
      if (res == 1) {
        res = 0;
      } else if (res == 0) {
        res = 1;
      }
    }
  }

  if (ignore_case_flag == 0) {
    res = return_match(buff, patterns, patterns_count) == 1;
    if (inversion_flag == 1) {
      if (res == 1) {
        res = 0;
      } else if (res == 0) {
        res = 1;
      }
    }
  }
  return res;
}
