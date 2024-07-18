#include "headers.h"

int twosubpart(char **argv, char *token, char *delimitter)
{
    char *yep = (char *)malloc(sizeof(char) * (strlen(token) + 1));
    // printf("%s",token);
    strcpy(yep, token);
    char *dummy = strtok(token, delimitter);
    int count = 0;
    while (dummy != NULL)
    {
        count++;
        dummy = strtok(NULL, delimitter);
    }
    // printf("%d",count);

    dummy = strtok(yep, delimitter);
    // argv = (char **)malloc(sizeof(char *) * (count + 1));
    // argv[count] = NULL;

    int k = 0;
    while (dummy != NULL)
    {
        argv[k] = (char *)malloc(sizeof(char) * (strlen(dummy) + 1));
        strcpy(argv[k], dummy);
        argv[k][strlen(argv[k])] = '\0';
        // printf("d%s a%s", dummy, argv[k]);
        dummy = strtok(NULL, delimitter);
        k++;
    }
    argv[count] = NULL;
    if (strcmp(argv[0], "warp") == 0 || strcmp(argv[0], "peek") == 0 || strcmp(argv[0], "seek") == 0 || strcmp(argv[0], "pastevents") == 0 || strcmp(argv[0], "proclore") == 0)
    {
        argv[count] = (char *)malloc(sizeof(char) * 2000);
        strcpy(argv[count], "\0");
    }
    

    return count;
}