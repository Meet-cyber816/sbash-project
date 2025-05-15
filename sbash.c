/* This is the source code of sbash shell "sbash.c" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "sbashfun.h"

#define MAX_PATH 256

// Define PATH_MAX if not already defined
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

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
    char danger_dir[][35]={".bashrc",".profile",".bash_profile",".ssh",".config",".bash_logout",".vimrc",".virc","bin/"};
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
