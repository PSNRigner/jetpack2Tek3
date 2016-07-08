#include "client.h"

void			my_exit(char *str, int status)
{
  if (str)
    printf("%s\n", str);
 
  exit(status ? 84 : 0);
}

int 			digit_to_int(char d)
{
 char 			str[2];

 str[0] = d;
 str[1] = '\0';

 return (int) strtol(str, NULL, 10);
}