// This Headerfile contains the functions that sbash.c uses

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
