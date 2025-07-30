#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"

void option_without_arg(char *buff) { printf("%s", buff); }

int option_numeration_all_lines(char *buff, int c) {
  char temp[4096];
  int count = c;
  count++;
  sprintf(temp, "%6d\t%s", count, buff);
  memmove(buff, temp, 4096);
  return count;
}

int option_numeration_nonblank_lines(char *buff, int c) {
  int count = c;
  char temp[4096];
  if (strlen(buff) <= 1) {
    sprintf(temp, "%s", buff);
    memmove(buff, temp, 4096);
  } else {
    count++;
    sprintf(temp, "%6d\t%s", count, buff);
    memmove(buff, temp, 4096);
  }
  return count;
}

int is_string_with_spaces(char *buff) {
  int res = 1;
  while (*buff != '\n') {
    if (!isspace(*buff)) {
      res = 0;
      break;
    }
    buff++;
  }
  return res;
}

int is_string_empty(char *buff) {
  int res = 0;
  char *p = buff;
  while (*p != '\0') {
    p++;
  }
  if (p > buff && *(p - 1) == '\n') {
    res = 1;
  }
  return res;
}

void option_show_endlines(char *buff) {
  char temp[4096];
  addDollar(buff);
  sprintf(temp, "%s", buff);
  memmove(buff, temp, 4096);
}

void addDollar(char *buff) {
  char *p = buff;
  while (*p != '\0') {
    p++;
  }
  if (p > buff && *(p - 1) == '\n') {
    *(p - 1) = '$';
    *p++ = '\n';
    *p = '\0';
  } else {
    *p = '\0';
  }
}

int option_squeeze_nonblank_lines(char *buff, int space) {
  int flag = space;
  char temp[4096];
  if (strlen(buff) <= 1 && flag == 0) {
    flag = 1;
    sprintf(temp, "%s", buff);
    memmove(buff, temp, 4096);
  } else if (strlen(buff) > 1 && flag == 1) {
    flag = 0;
    sprintf(temp, "%s", buff);
    memmove(buff, temp, 4096);
  } else if (strlen(buff) > 1 && flag == 0) {
    flag = 0;
    sprintf(temp, "%s", buff);
    memmove(buff, temp, 4096);
  } else {
    memset(buff, 0, 4096);
    buff[0] = '\0';
  }
  return flag;
}

void option_show_tab_in_lines(char *buff) {
  char temp[4096];
  print_tab(buff);
  sprintf(temp, "%s", buff);
  memmove(buff, temp, 4096);
}

void print_tab(char *buff) {
  char *p = buff;
  char temp[4096] = {0};
  int flag = 0;
  while (*(p) != '\0') {
    if (*p == '\t') {
      strncpy(temp, buff, p - buff);
      strcat(temp, "^I");
      strcat(temp, p + 1);
      memmove(buff, temp, 4096);
      memset(temp, 0, 4096);
      flag = 1;
    }
    if (flag == 1) {
      p = buff;
      flag = 0;
    } else {
      p++;
    }
  }

  return;
}