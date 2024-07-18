#include "headers.h"

void warp(char **argv, char *dir, char *prev_dir)
{
    int i = 1;
    char cwd[2000];
    while (strcmp(argv[i], "\0)") != 0)
    {

        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        char *dir_path = (char *)malloc(sizeof(char) * 2000);
        // printf("%s",cwd);
        // printf("%ld",strlen(cwd));
        strcpy(dir_path, cwd);
        strcat(dir_path, argv[i]);
        // printf("%ld",strlen(dir_path));
        int len = (strlen(cwd) + strlen(argv[i]) + 1);
        // printf("%d",len);
        dir_path[len] = '\0';
        // printf("%s",argv[i]);
        struct stat buf;
        // if((strcmp(argv[i],".") != 0) && (strcmp(argv[i], "..") != 0 ))
        // {
        int flag = 0;
        if (strcmp(argv[i], ".") == 0)
        {

            // strcpy(prev_dir, cwd);
            int d = chdir(argv[i]);
            // printf("%d", d);
            flag = 1;
            // continue;
        }
        else if (strcmp(argv[i], "~") == 0)
        {
            // printf("@");
            // strcpy(prev_dir, dir);
            // printf("%s",dir);
            int d = chdir(dir);
            // printf("%d", d);
            flag = 1;
        }
        else if (strcmp(argv[i], "-") == 0)
        {

            // printf("y");
            // printf("%s",prev_dir);
            int d = chdir(prev_dir);
            // strcpy(prev_dir, cwd);
            // printf("%d", d);
            flag = 1;
            // continue;
        }
        else if (strcmp(argv[i], "..") == 0)
        {
            // strcpy(prev_dir, cwd);
            int d = chdir(argv[i]);
            // printf("%d", d);
            flag = 1;
        }
        // printf("flag:%d",flag);
        if (flag != 1)
        {
            if ((stat(dir_path, &buf) != -1))
            {
                // printf("*");

                // else
                // {
                // strcpy(prev_dir, cwd);

                // char *path = (char *)malloc(sizeof(char) * 4096);
                // path[0] = '/';
                // strcat(path, dir_path);
                // printf("%s",path);
                // printf("%s",dir_path);
                // printf("%ld",strlen(dir_path));
                int d = chdir(dir_path);
                // strcpy(prev_dir,cwd);
                // printf("found");
                // printf("%d", d);
                // }
                // }
            }
            else
            {
                // printf("not found");

                // if (strcmp(argv[i], ".") == 0)
                // {
                //     strcpy(prev_dir, cwd);
                //     // continue;
                // }
                // else if (strcmp(argv[i], "~") == 0)
                // {
                //     // printf("@");
                //     strcpy(prev_dir, cwd);
                //     // printf("%s",dir);
                //     int d = chdir(dir);
                //     printf("%d", d);
                // }
                // else if (strcmp(argv[i], "-") == 0)
                // {
                //     // printf("y");
                //     // printf("%s",prev_dir);
                //     int d = chdir(prev_dir);
                //     printf("%d", d);
                //     // continue;
                // }
                // else
                // {
                // strcpy(prev_dir, cwd);
                // printf("%s", prev_dir);
                // char *path = (char *)malloc(sizeof(char) * 4096);
                // path[0] = '/';
                // strcat(path, argv[i]);
                // printf("%s",path);
                int d = chdir(argv[i]);
                if(d == -1)
                {
                    perror("");
                }
                // printf("%d", d);
                //         }
            }
        }
        // printf("%s", path);
        // }
        // else
        // {
        // int ans = fork();
        // int status;
        // if (ans == 0)
        // {
        //     if (execvp(argv[0], argv) == -1)
        //     {
        //         perror("Error executing command");
        //         exit(EXIT_FAILURE);
        //     }
        // }
        // else
        // {
        //     waitpid(ans, &status, 0);
        // }

        // if(flag == 1)
        // {
        // printf("%s", cwd);
        strcpy(prev_dir, cwd);
        // }
        i++;
    }
    if (i == 1)
    {
        int d = chdir(dir);
        strcpy(prev_dir, cwd);
        // printf("%d", d);
    }
return;
}
