#include "headers.h"

void rule(char **argv, char *shell_invok_dir, char *prev_dir, int check)
{
    if (check == 0)
    {
        // printf("%s",argv[0]);
        // printf("%s",argv[1]);
        char *array = (char *)malloc(sizeof(char) * 2000);
        strcpy(array, shell_invok_dir);
        strcat(array, "/pastevents.txt");
        array[strlen(shell_invok_dir) + 15] = '\0';
        // if (strcmp(argv[0], "pastevents") == 0)
        // {
        //     past_flag = 1;
        //     pastevents(argv, count, shell_invok_dir, prev_dir);
        // }
        // printf("%s",prev_dir);
        // printf("1");
        if (strcmp(argv[0], "warp") == 0)
        {
            // printf("&");
            // printf("%s",prev_dir);
            warp(argv, shell_invok_dir, prev_dir);
        }
        else if (strcmp(argv[0], "peek") == 0)
        {
            // printf("1star");
            // int i = 0;
            // while(strcmp(argv[i],"\0") != 0)
            // {
            // printf("%s",argv[i]);
            // i++;
            // }
            // printf("%s",prev_dir);
            peek(argv, shell_invok_dir);
        }
        else if (strcmp(argv[0], "pastevents") == 0)
        {
            pastevents(argv, shell_invok_dir, prev_dir);
        }
        else if (strcmp(argv[0], "exit") == 0)
        {
            FILE *fptr = fopen(array, "a+");
            fputs("exit\n", fptr);
            fclose(fptr);
            exit(0);
        }
        else if (strcmp(argv[0], "proclore") == 0)
        {
            proclore(argv);
        }
        else if (strcmp(argv[0], "seek") == 0)
        {
            // printf("$$$$$");
            seek(argv, shell_invok_dir,prev_dir);
        }
        else
        {
            // warp(argv, shell_invok_dir, prev_dir, count);

            int ans = fork();
            int status;
            if (ans == 0)
            {
                if (execvp(argv[0], argv) == -1)
                {
                    perror("Error executing command");
                    // exit(EXIT_FAILURE);
                }
            }
            else
            {
                // if(!check)
                // {
                waitpid(ans, &status, 0);
                // }
            }
        }
    }
    else
    {
        int ans = fork();
        int status;
        if (ans == 0)
        {
            if (execvp(argv[0], argv) == -1)
            {
                perror("Error executing command");
                // exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("%d\n",ans);
            // if(!check)
            // {
            // waitpid(ans, &status, 0);
            // }
        }
    }
}