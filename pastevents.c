#include "headers.h"

void pastevents(char **argv, char *shell_invk_dir, char *prev_dir)
{
    char *arr1 = "purge";
    char *arr2 = "execute";
    int i = 1;
    char *array = (char *)malloc(sizeof(char) * 2000);
    strcpy(array, shell_invk_dir);
    strcat(array, "/pastevents.txt");
    array[strlen(shell_invk_dir) + 15] = '\0';

    if (strcmp(argv[1], "\0") != 0)
    {
        // printf("ok");
        if (strcmp(argv[1], arr1) == 0)
        {
            FILE *f = fopen(array, "w");
            fclose(f);
        }

        else if (strcmp(argv[1], arr2) == 0)
        {
            FILE *f = fopen(array, "r");
            char arr3[4096];
            int i = 1;
            int d = atoi(argv[2]);
            // printf("%d\n", d);
            while (i <= d && fgets(arr3, sizeof(arr3), f) != NULL)
            {
                // command_exe();
                i++;
            }
            if (i != 1)
            {
                char *lineptr = (char *)malloc(sizeof(char) * 2000);
                strcpy(lineptr, arr3);
                char *delimit = ";&\n";
                char *delim = " \n";
                char **tokens = (char **)malloc(sizeof(char *) * 2000);
                int count = twosubpart(tokens, arr3, delimit);
                int sum = 0;
                for (int i = 0; i < count; i++)
                {
                    char* copy = (char*)malloc(sizeof(char)*(strlen(tokens[i]+1)));
                    strcpy(copy,tokens[i]);
                    char **arg = (char **)malloc(sizeof(char *) * 2000);
                    if (i == 0)
                    {
                        sum += strlen(tokens[i]);
                    }
                    else
                    {
                        sum = sum + strlen(tokens[i]) + 1;
                    }
                    char *delimitter = " \n\t";
                    int background = 0;
                    if (strcmp(&lineptr[sum], "&") == 0)
                    {
                        background = 1;
                    }
                    int yo = twosubpart(arg, tokens[i], delim);
                    rule(arg, shell_invk_dir, prev_dir, background);
                    addcommand(copy,shell_invk_dir);
                }
            }
            else
            {
                printf("invalid index");
            }
            // char *arr4 = (char *)malloc(sizeof(char) * strlen(arr3));
            // strcpy(arr4, arr3);
            // int count = 0;
            // char *token = strtok(arr3, delim);
            // while (token != NULL)
            // {
            //     count++;
            //     token = strtok(NULL, delim);
            // }
            // // printf("%d",count);
            // char **arr5 = (char **)malloc(sizeof(char *) * count);
            // token = strtok(arr4, delim);
            // i = 0;
            // while (token != NULL)
            // {
            //     arr5[i] = (char *)malloc(sizeof(char) * strlen(token));
            //     // printf("%s\n",token);
            //     strcpy(arr5[i], token);
            //     token = strtok(NULL, delim);
            //     i++;
            // }
            // printf("%d",i);
            // if(strcmp(arr5[0],"warp") == 0)
            // {
            //     char** arr = (char**)malloc(sizeof(char*)*2000);
            //     twosubpart(arr,argv);
            //     // warp(argv,,shell_invk_dir,prev_dir,);
            // }
            // rule(arr5,0);
            fclose(f);
        }
    }
    else
    {
        // printf("fine");
        FILE *f = fopen(array, "r");
        char arr[4096];
        while (fgets(arr, sizeof(arr), f) != NULL)
        {
            printf("%s", arr);
        }
        fclose(f);
    }
    //     else
    //     {
    //         if (purge_flag == 1 && execute_flag == 1)
    //         {
    //             FILE* f = fopen("pastevents.txt","w");
    //             fclose(f);

    //         }
    //         else if (purge_flag != 1 && execute_flag == 1)
    //         {
    //         }
    //         else
    //         {
    //         }
    //     }
    //     i++;
    // }
}