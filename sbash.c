/* This is the source code of sbash shell "sbash.c" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define MAX_PATH 256

// Define PATH_MAX if not already defined
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void handle_sigint(int sig) {
   //Do nothing (ignore the signal)
    fflush(stdout);
    rl_on_new_line();
    rl_redisplay();
}

void print_sbash_info() {
    printf("Sbash - Secure Bash Shell\n");
    printf("---------------------------\n");
    printf("Creator: Meet Panchal\n");
    printf("Description: A secure version of Bash for Organizations, enterprises, and \neducational institutions seeking to secure their systems, by restricting dangerous commands.\n");
    printf("Usage: Use sbash as a regular shell, but restricted commands are blocked for security.\n");
    printf("LinkedIn: https://www.linkedin.com/in/meet-panchal-434709316/\n");
    printf("Contact: tedomanoffsec@gmail.com\n");
}

int is_special_ch_in_command(char *str, int len)
{
                int flag = 0;
                for(int i=0;i<len;i++)
                {
                                if(str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$'
                                        || str[i] == '%' || str[i] == '|' || str[i] == '&'
                                        || str[i] == '(' || str[i] == ')' ||  str[i] == '{'
                                        || str[i] == '}' || str[i] == '[' || str[i] == ']' || str[i] == ':'
                                        || str[i] == ';' || str[i] == '\''|| str[i] == '<'
                                        || str[i] == '?' )
                                {
                                                printf("sbash: \033[1;37mspecial symbols are not allowed for security reasons!\033[0m\n");
                                                flag = 1;
                                                break;
                                }
                }
                return flag;
}

//Removing white spaces before and after the command if any
void format_input(char *ptr, int len)
{
    int start = 0, end = len - 1;

    while (ptr[start] == ' ')
        start++;

    while (end > start && ptr[end] == ' ')
        end--;

    // Shift the trimmed string to the beginning and null-terminate
    int i = 0;
    while (start <= end)
        ptr[i++] = ptr[start++];
}

int flag_check(char *command, char danger[][35])
{
    char *token;
    int i, flag = 0,len;
    char temp_command[1000];

    for(len=0;danger[len][0]!='\0';len++);

    strncpy(temp_command, command, sizeof(temp_command) - 1);
    temp_command[sizeof(temp_command) - 1] = '\0';

    token = strtok(temp_command, " "); // Split the command by spaces
    while(token != NULL)
    {
        for (i = 0; i < len; i++)
        {
            if (strcmp(token, danger[i]) == 0)
            {
                flag = 1;
                printf("sbash: \033[0;31m%s\033[0m is restricted!\n", danger[i]);
                return flag;
            }
        }
        token = strtok(NULL, " "); // Get the next word in the command
    }
    return flag;
}

int dir_check(char *command, char danger_dir[][35])
{
    int i, flag = 0, len;

    for(len=0;danger_dir[len][0]!='\0';len++);

    for(i = 0; i < len; i++)
    {
        if( strstr(command, danger_dir[i]) )
           return 1;
        
    }
    return 0;
}

int editor_check(char *command)
{
    char temp_command[1000];
    char *token;

    strncpy(temp_command, command, sizeof(temp_command) - 1);
    temp_command[sizeof(temp_command) - 1] = '\0';

    token = strtok(temp_command, " ");

    if(strcmp(token,"vim") == 0 || strcmp(token,"vi") == 0)
    {
        token = strtok(NULL, " ");
        strcpy(command, "vi -Z");

        while( token != NULL )
        {      
           strcat(command, " "); 
           strcat(command, token);
           token = strtok(NULL, " ");        
        }
        system(command);
        return 1;
    }
    return 0;
}

// Main method
int main(int argc, char *argv[])
{
	system("clear");	
	const char *home = getenv("HOME");
	char HISTORY_FILE[MAX_PATH];
	char prompt[PATH_MAX + 150];
	int flag=0;
	char cwd[PATH_MAX];
	char temp_command[250];
	char black_command[25];
	char danger_flags[][35]={"/bin/bash","/bin/sh","bin/bash","bin/sh","bash","sh","shell","-rf","-a","-al","-la","-f","--no-preserve-root","-R","alias","--norc","/dev/null","-exec","--overwrite"};
        char danger_dir[][35]={".bashrc",".bash_profile",".ssh",".config",".bash_logout",".vimrc",".virc"};
	char *command;
	char *dir;
        char *token;
	FILE *fp;

	// Configure readline for proper line wrapping
	rl_variable_bind("horizontal-scroll-mode", "off");
	rl_variable_bind("bell-style", "none");
	
	// Set up signal handling for readline
	signal(SIGINT, handle_sigint);

	fp=fopen("/usr/local/bin/_sbash_restricted_commands.txt","r");
	
	snprintf(HISTORY_FILE, sizeof(HISTORY_FILE), "%s/.sbash_history", home);

	read_history(HISTORY_FILE); 

    	printf("\033[1;32mWelcome to sbash - Secure Bash Shell\033[0m\n");
        printf("Type 'sbashinfo' for more information\n\n");
 
	while(1)
	{	
		getcwd(cwd, sizeof(cwd));
				
		if(strcmp(home,cwd)==0)
			flag=1;
		else 
			flag=0;

		if(strcmp("/home",cwd)==0 || strcmp("/",cwd)==0)
			chdir(home);

		// Create the prompt with proper ANSI escape sequences
		snprintf(prompt, sizeof(prompt), "\001\033[1;32m\002user@securebash\001\033[0;37m\002:\001\033[1;32m\002~%s\001\033[0;37m\002$\001\033[0m\002 ", cwd + strlen(home));
		
		// Use readline with proper line wrapping
		command = readline(prompt);

        format_input(command, strlen(command));

		if(*command)
			add_history(command);
		else {
			free(command);
			continue;
		}

		if(is_special_ch_in_command(command,strlen(command)))
                        goto a;

		if(strcmp(command,"sbashinfo")==0)
		{
			print_sbash_info();
			continue;
		}	

		if(strstr(command,".sh"))
		{
			 printf("sbash: \033[0;31mPermission denied!\033[0m\n");
			 continue;
		}	

		if( !strcmp(command,"exit") )
		{	
			free(command);
			break;
		}

		if( dir_check(command, danger_dir) )
            continue;

		strncpy(temp_command, command, sizeof(temp_command) - 1);
		temp_command[sizeof(temp_command) - 1] = '\0';

        if(editor_check(command))
               continue;
        

        dir = strtok(temp_command, " ");
        if(strcmp(dir,"cd") == 0)
        {
              dir = strtok(NULL, " ");
              if (dir == NULL || strlen(dir) == 0  || strcmp(dir, " ") == 0 )chdir(home);
              else if(strstr(dir, "~/")){
                      chdir(home);
                      chdir(dir+2);
              }        
              else if (strcmp(dir, "/") == 0 || (flag==1 && strcmp(dir, "..") == 0) )
                      printf("sbash: \033[0;31mPermission denied!\033[0m\n");
              else{
                      if (chdir(dir) != 0) {  // Check if chdir() fails
                            perror("cd failed");
                      }
              }
                  goto a;
        }

		// Checking if entered command is restricted or not
		rewind(fp); // Ensure the file pointer is at the start of the file
        while (fscanf(fp, "%s", black_command) != EOF)
        {
            format_input(black_command, strlen(black_command));
            if (strncmp(command, black_command, strlen(black_command)) == 0)
            {
                    printf("sbash: \033[0;31m%s\033[0m command is restricted!\n", black_command);
                    goto a;
            }
        }
	
		if( flag_check(command,danger_flags) )
			goto a;
			

		system(command); // Exeuting command after all the checkings
		signal(SIGINT, handle_sigint);	
		a:
                free(command);
	}	
	
	write_history(HISTORY_FILE);
	fclose(fp);
	return 0;
}	
