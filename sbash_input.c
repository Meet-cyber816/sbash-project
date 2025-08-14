#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void format_input (char *ptr, int len)
{
  int i = 0, j = 0;

  while (i < len && ptr[i] == ' ')
    {
      i++;
    }

  while (i < len)
    {
      ptr[j++] = ptr[i++];
    }
  ptr[j] = '\0'; // Null-terminate the string

  // Trim everything after the first space
  for (i = 0; ptr[i] != '\0'; i++)
    {
      if (ptr[i] == ' ')
        {
          ptr[i] = '\0';
          break;
        }
    }
}

int number_sanitization (char *ptr)
{
  int flag = 1;

  if ((ptr[0] >= 'a' && ptr[0] <= 'z'))
    {
      flag = 0;
      return flag;
    }
  return flag;
}

void to_lowercase (char *ptr, int n)
{
  int i;
  for (i = 0; i < n; i++)
    ptr[i] = tolower (ptr[i]);
}

int main ()
{
  system ("clear");
  char str[50];
  FILE *fp;
  fp = fopen ("black_commands.txt", "a");
  printf ("Enter Q to exit...\n");
  if (fp == NULL)
    {
      printf ("File not found!\n");
      exit (1);
    }

  while (1)
    {
      printf ("\nEnter command: ");
      fgets (str, sizeof (str), stdin);

      str[strlen (str) - 1] = '\0';

      format_input (str, strlen (str));

      if (!strncmp (str, "Q", 1))
        {
          system ("clear");
          printf ("\n\nGoodbye...\n");
          break;
        }

      to_lowercase (str, strlen (str));

      if (number_sanitization (str))
        {
          printf ("\nInvalid input, Please try again!");
          getchar ();
          system ("clear");
          continue;
        }

      if (str[0] != '\0' && str[1] != '\0' && str[1] != ' ')
        {
          fprintf (fp, "%s\n", str);
          printf ("\nCommand Insertion successful!");
        }
      else
        printf ("\nInvalid input, Please try again!");

      getchar ();
      system ("clear");
    }

  fclose (fp);

  system ("bash sort_black_commands.sh");

  return 0;
}
