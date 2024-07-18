#include "headers.h"
int matches_found = 0;

void rec_dir(char *arr, char *target, char *homedir, int flag, char *buffer)
{
    DIR *dir;
    dir = opendir(arr);
    if (dir == NULL)
    {
        return;
    }

    struct dirent *dire;
    while ((dire = readdir(dir)) != NULL)
    {
        char array[1000];
        // strcpy(yep,dire->d_name);
        strcpy(array, arr);
        strcat(array, "/");

        strcat(array, dire->d_name);

        if (strcmp(dire->d_name, ".") == 0 || strcmp(dire->d_name, "..") == 0)
        {
            continue;
        }

        if (strncmp(dire->d_name, target, strlen(target)) == 0)
        {
            char directory[2000];
            strcpy(directory, array + strlen(homedir));
            int len = strlen(arr) - strlen(homedir);
            if (flag == 1)
            {
                if (dire->d_type == DT_DIR)
                {
                    // *count++;
                    matches_found++;
                    strcpy(buffer, array);
                    printf(".%s%s%s/\n", dir_color, directory, COLOR_RESET);
                }
            }
            else if (flag == 2)
            {
                if (dire->d_type == DT_DIR)
                {
                    printf(".%s%s%s/\n", dir_color, directory, COLOR_RESET);
                }
            }
            else if (flag == 3)
            {
                if (dire->d_type != DT_DIR)
                {
                    // *count++;
                    matches_found++;
                    strcpy(buffer, array);
                    // printf("%s\n",buffer);
                    printf(".%s%s%s/\n", file_color, directory, COLOR_RESET);
                    // file: directory content
                }
            }
            else if (flag == 4)
            {
                if (dire->d_type != DT_DIR)
                {
                    printf(".%s%s%s/\n", file_color, directory, COLOR_RESET);
                }
            }
            else if (flag == 5)
            {
                if (dire->d_type == DT_DIR)
                {
                    printf(".%s%s%s/\n", dir_color, directory, COLOR_RESET);
                }
                else
                {
                    printf(".%s%s%s/\n", file_color, directory, COLOR_RESET);
                }
            }

            // char directory[2000];
            // strcpy(directory, array + strlen(homedir));
            // int len = strlen(arr) - strlen(homedir);
            // printf(".%s\n", directory);
        }

        rec_dir(array, target, homedir, flag, buffer);
    }
    return;
}

void seek(char **argv, char *shell_invok_dir,char* prev_dir)
{
    int i = 1;
    int e_flag = 0;
    int f_flag = 0;
    int d_flag = 0;
    char cwd[2000];
    getcwd(cwd, sizeof(cwd));

    while (strcmp(argv[i], "\0") != 0)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            e_flag = 1;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            f_flag = 1;
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            d_flag = 1;
        }
        else
        {
            int flag = 0;
            if (d_flag == 1 && f_flag == 0)
            {
                if (e_flag == 1)
                {
                    flag = 1;
                }
                else
                {
                    flag = 2;
                }
            }
            else if (d_flag == 0 && f_flag == 1)
            {
                if (e_flag == 1)
                {
                    flag = 3;
                }
                else
                {
                    flag = 4;
                }
            }
            else
            {
                flag = 5;
            }
            char *buffer = (char *)malloc(sizeof(char) * 2000);
            int count = 0;
            if (strcmp(argv[i + 1], "\0") == 0)
            {
                rec_dir(cwd, argv[i], cwd, flag, buffer);
            }
            else
            {
                if (strcmp(argv[i + 1], ".") == 0)
                {
                    // printf("1");
                    rec_dir(cwd, argv[i], cwd, flag, buffer);
                }
                else if (strcmp(argv[i + 1], "~") == 0)
                {
                    // printf("2");
                    rec_dir(shell_invok_dir, argv[i], shell_invok_dir, flag, buffer);
                }
                else if (strncmp("~/", argv[i + 1], 2) == 0)
                {
                    // printf("3");
                    char fine[2000];
                    strcpy(fine, shell_invok_dir);
                    strcat(fine, "/");
                    strcat(fine, argv[i + 1] + 2);
                    // printf("%s\n",fine);
                    rec_dir(fine, argv[i], fine, flag, buffer);
                }
                else if (strncmp("./", argv[i + 1], 2) == 0)
                {
                    char fine[2000];
                    strcpy(fine, cwd);
                    strcat(fine, "/");
                    strcat(fine, argv[i + 1] + 2);
                    printf("%s\n", fine);
                    rec_dir(fine, argv[i], fine, flag, buffer);
                }
                 
                // printf("%s",buffer);
                // printf("%d",count);
                if (matches_found == 1 && flag == 1)
                {
                    char cw[1000];
                    getcwd(cw,sizeof(cw));
                    strcpy(prev_dir,cw);
                    int d = chdir(buffer);
                    if (d == -1)
                    {
                        perror("");
                    }
                }
                else if (flag == 3 && matches_found == 1)
                {
                    char barry[2000];
                    FILE *fptr = fopen(buffer, "r");
                    while (fgets(barry, sizeof(barry), fptr) != NULL)
                    {
                        printf("%s", barry);
                    }
                }
                // printf("4");
                // rec_dir(argv[i + 1], argv[i]);

                // dir = opendir(argv[i + 1]);
                // if (dir == NULL)
                // {
                //     perror("No such file or directory");
                //     return;
                // }
                // while ((direntry = readdir(dir)) != NULL)
                // {
                //     DIR *rec_dir;
                //     rec_dir = opendir(direntry->d_name);
                //     if (rec_dir == NULL)
                //     {
                //         continue;
                //     }
                //     else
                //     {
                //         struct dirent *rec_direct;
                //         while ((rec_direct = readdir(rec_dir)) != NULL)
                //         {
                //             if (strcmp(argv[i], rec_direct->d_name) == 0)
                //             {
                //                 printf("%s\n", rec_direct->d_name);
                //             }
                //         }
                //         closedir(rec_dir);
                //     }
                // }
                // closedir(dir);
            }

            e_flag = 0;
            f_flag = 0;
        }
        i++;
    }
}