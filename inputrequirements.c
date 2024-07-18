#include "headers.h"

void input(char *shell_invok_dir, char *prev_dir)
{
    char lineptr[4096];
    fgets(lineptr, 4096, stdin);
    int n = strlen(lineptr) + 1;
    char *delim = ";&\n";
    char *lineptr_cpy = (char *)malloc(sizeof(char) * n);
    strcpy(lineptr_cpy, lineptr);
    char *token = strtok(lineptr_cpy, delim);
    int num_tokens = 0;
    while (token != NULL)
    {
        num_tokens++;
        token = strtok(NULL, delim);
    }
    char **tokens = (char **)malloc(sizeof(char *) * num_tokens);
    char *copy = (char *)malloc(sizeof(char) * n);
    strcpy(copy, lineptr);
    char *res = lineptr;
    token = strtok_r(res, delim, &res);
    int i = 0;
    int sum = 0;
    int past_flag = 0;
    while (token != NULL)
    {
        char **argv = (char **)malloc(sizeof(char *) * 2000);
        tokens[i] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(tokens[i], token);
        if (i == 0)
        {
            sum += strlen(token);
        }
        else
        {
            sum = sum + strlen(token) + 1;
        }
        char *delimitter = " \n\t";
        int background = 0;
        if (strcmp(&copy[sum], "&") == 0)
        {
            background = 1;
        }
  
        int count = twosubpart(argv, tokens[i], delimitter);
        int l = 0;
        // while(strcmp(argv[l],"\0") != 0)
        // {
        // printf("%s",argv[l]);
        // l++;
        // }
        // printf("count : %d", count);
        
        if(strcmp(argv[0],"pastevents") == 0)
        {
            past_flag = 1;
        }

        rule(argv, shell_invok_dir, prev_dir, background);

        token = strtok_r(res, delim, &res);
        i++;
        // for(int j=0;j<=count;j++)
        // {
        //     free(argv[j]);
        // }
        // free(argv);
        // argv = NULL;
    }

    if (past_flag == 0)
    {
        // printf("1");
        addcommand(copy,shell_invok_dir);
    }

    return;
}