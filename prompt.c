#include "headers.h"

// char cwd[2000];
// getcwd(shell_invok_dir, sizeof(shell_invok_dir));
// int invk_dir_len = strlen(shell_invok_dir);
// char *point;
// int length;

void prompt()
{
    // Do not hardcode the prmopt
    printf("<Everything is a file> ");
}

void sigchld_handler(int signo) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
}

int main()
{
    // char** all = (char**)malloc(sizeof(char*)*2000);
    char shell_invok_dir[2000];
    char cwd[2000];
    getcwd(shell_invok_dir, sizeof(shell_invok_dir));
    // point = shell_invok_dir;
    int invk_dir_len = strlen(shell_invok_dir);
    int y = 0;
    getcwd(cwd, sizeof(cwd));
    char *prev_dir = (char *)malloc(sizeof(char) * 2000);
    strcpy(prev_dir, cwd);
    char *array = (char *)malloc(sizeof(char) * 2000);
    strcpy(array, shell_invok_dir);
    strcat(array, "/pastevents.txt");
    array[strlen(shell_invok_dir) + 15] = '\0';
    // printf("%s",prev_dir);
    while (1)
    {
        signal(SIGCHLD, sigchld_handler);
        struct utsname *buf = (struct utsname *)malloc(sizeof(struct utsname));
        uname(buf);
        char *prompt = getenv("USER");
        getcwd(cwd, sizeof(cwd));
        // printf("%s",cwd);

        int cwd_len = strlen(cwd);
        if (strncmp(cwd, shell_invok_dir, invk_dir_len) == 0)
        {
            int dir_len = ((cwd_len) - (invk_dir_len));
            // printf("%d",dir_len);
            char dir[dir_len + 1];
            strcpy(dir, cwd + invk_dir_len);
            dir[dir_len + 1] = '\0';
            if (strcmp(cwd, shell_invok_dir) > 0)
            {
                //  printf("$");
                printf("%c%s%c%s:%c%s%c", '<', prompt, '@', buf->sysname, '~', dir, '>');
            }
            else
            {
                printf("%c%s%c%s:%c%c", '<', prompt, '@', buf->sysname, '~', '>');
            }
        }
        else
        {
            printf("<%s@%s:%s>", prompt, buf->sysname, cwd);
        }
        input(shell_invok_dir, prev_dir);
        //     char lineptr[4096];
        //     // long int n = 0;
        //     fgets(lineptr, 4096, stdin);
        //     // printf("%d",n);
        //     int n = strlen(lineptr);
        //     // printf("%ld",strlen(lineptr));
        //     // length = n;
        //     char *delim = ";&\n";
        //     char *lineptr_cpy = (char *)malloc(sizeof(char) * n);
        //     // printf("%ld",n);
        //     strcpy(lineptr_cpy, lineptr);
        //     char *token = strtok(lineptr_cpy, delim);
        //     int num_tokens = 0;
        //     while (token != NULL)
        //     {
        //         // printf("%s",token);
        //         num_tokens++;
        //         token = strtok(NULL, delim);
        //     }
        //     char **tokens = (char **)malloc(sizeof(char *) * num_tokens);
        //     // printf("line:%s\n",lineptr);
        //     char *copy = (char *)malloc(sizeof(char) * n);
        //     strcpy(copy, lineptr);
        //     char *res = lineptr;
        //     token = strtok_r(res, delim, &res);
        //     // printf("token:%s\n",token);
        //     //  printf("%s", lineptr);
        //     int i = 0;
        //     // while(token != NULL)
        //     // {
        //     int sum = 0;
        //     int past_flag = 0;
        //     while (token != NULL)
        //     {

        //         // char *delimiter_location = strpbrk(token, "&");
        //         // if (delimiter_location != NULL) {
        //         // if (*delimiter_location == '&')
        //         // {
        //         //     printf("%s",delimiter_location);
        //         // }
        //         // else
        //         // {
        //         //     printf("1");
        //         // }
        //         // }
        //         // // else
        //         // // {
        //         // //     printf("1");
        //         // // }
        //         tokens[i] = (char *)malloc(sizeof(char) * strlen(token));
        //         strcpy(tokens[i], token);
        //         sum += strlen(token);
        //         // printf("%s\n",token);
        //         char *delimitter = " \n\t";
        //         char *yep = (char *)malloc(sizeof(char) * strlen(token));
        //         strcpy(yep, tokens[i]);
        //         // printf("ype:%s\n",yep);

        //         char *dummy = strtok(tokens[i], delimitter);
        //         int count = 0;
        //         while (dummy != NULL)
        //         {
        //             // printf("%s", dummy);
        //             count++;
        //             dummy = strtok(NULL, delimitter);
        //         }

        //         // printf("%d",count);
        //         dummy = strtok(yep, delimitter);
        //         // if(dummy != NULL)
        //         // {
        //         all = (char **)malloc(sizeof(char *) * (count));
        //         int k = 0;
        //         while (dummy != NULL)
        //         {
        //             all[k] = (char *)malloc(sizeof(char) * strlen(dummy));
        //             strcpy(all[k], dummy);
        //             // printf(" 1");
        //             // printf("%s",all[k]);
        //             dummy = strtok(NULL, delimitter);
        //             k++;
        //         }

        //         if (strcmp(all[0], "pastevents") == 0)
        //         {
        //             past_flag = 1;
        //             pastevents(all,count);
        //         }
        //         // printf("%ld",n);

        //         // command_exe(all, copy[sum], shell_invok_dir, prev_dir, count);
        //         if (strcmp(all[0], "peek") == 0)
        //         {
        //             peek(all);
        //         }
        //         // printf("%s", all[0]);
        //         // printf("%s\n",token);
        //         // }
        //         // break;
        //         // }
        //         // else
        //         // {
        //         // all = (char **)malloc(sizeof(char *) * (count));
        //         // int k = 0;
        //         // while (dummy != NULL)
        //         // {
        //         // all[k] = (char *)malloc(sizeof(char) * strlen(dummy));
        //         // strcpy(all[k], dummy);
        //         // printf("%s",all[k]);
        //         // dummy = strtok(NULL, delimitter);
        //         // k++;
        //         // }
        //         // command_exe(all);
        //         // printf("%s", all[0]);
        //         // token = strtok(NULL, delim);
        //         // }
        //         i++;
        //         // }

        //         token = strtok_r(res, delim, &res);
        //         // printf("%s\n",token);
        //         // printf("%s",res);
        //     }
        //     // printf("%s",copy);

        //     if (past_flag == 0)
        //     {
        //         int MAX_LINES = 15;
        //         int MAX_LINE_LENGTH = 4096;
        //         FILE *f;
        //         f = fopen("pastevents.txt", "a+");
        //         if (f == NULL)
        //         {
        //             perror("Error opening file");
        //             return 1;
        //         }

        //         char arr[MAX_LINES][MAX_LINE_LENGTH];
        //         int nof_commands = 0;

        //         // Set the file pointer to the beginning
        //         fseek(f, 0, SEEK_SET);

        //         // Read existing lines into the array
        //         while (nof_commands < MAX_LINES && fgets(arr[nof_commands], sizeof(arr[0]), f) != NULL)
        //         {
        //             nof_commands++;
        //         }

        //         // If the last line is different from the new line (copy)
        //         if (strcmp(arr[nof_commands - 1], copy) != 0)
        //         {
        //             if (nof_commands < MAX_LINES)
        //             {
        //                 // If there's space in the array, just append the new line
        //                 fputs(copy, f);
        //             }
        //             else
        //             {
        //                 // Shift lines in the array to remove the first line
        //                 for (int i = 0; i < MAX_LINES - 1; i++)
        //                 {
        //                     strcpy(arr[i], arr[i + 1]);
        //                 }
        //                 strcpy(arr[MAX_LINES - 1], copy);

        //                 // Close the file and reopen it for writing
        //                 fclose(f);
        //                 f = fopen("pastevents.txt", "w+");
        //                 if (f == NULL)
        //                 {
        //                     perror("Error opening file");
        //                     return 1;
        //                 }

        //                 // Write the updated array back to the file
        //                 for (int i = 0; i < MAX_LINES; i++)
        //                 {
        //                     fputs(arr[i], f);
        //                 }
        //             }
        //         }

        //         fclose(f);

        //     }
        // }
        // return 0;
    }
    
}
