#include "headers.h"

int comparator(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void format_time(const struct stat *st, char *formatted_time)
{
    struct tm *timeinfo;
    time_t modification_time = st->st_mtime;

    timeinfo = localtime(&modification_time);
    strftime(formatted_time, 13, "%b %d %H:%M", timeinfo);
}

void mode_to_text(mode_t mode, char *text)
{
    const char *permission_chars = "rwx";
    const char *type_chars = "-pc-d-b-l-s";

    text[0] = type_chars[(mode >> 12) & 0xF];

    for (int i = 0; i < 9; i++)
    {
        if (mode & (1 << (8 - i)))
        {
            text[i + 1] = permission_chars[i % 3];
        }
        else
        {
            text[i + 1] = '-';
        }
    }

    text[10] = '\0';
}

void peek(char **argv, char *shell_invk_dir)
{
    // printf("1");

    // qsort(a,2,sizeof(char*),comparator);
    int i = 1;
    int l_flag = 0;
    int a_flag = 0;
    // printf("%s",prev_dir);
    while (strcmp(argv[i], "\0") != 0)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            a_flag = 1;
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            l_flag = 1;
        }
        else if (strcmp(argv[i], "-la") == 0 || strcmp(argv[i], "-al") == 0)
        {
            l_flag = 1;
            a_flag = 1;
        }
        else
        {
            char cwd[2000];
            getcwd(cwd, sizeof(cwd));

            strcat(cwd, "/");
            char *dir_path = (char *)malloc(sizeof(char) * 4096);

            strcpy(dir_path, cwd);
            strcat(dir_path, argv[i]);
            // printf("%s",dir_path);

            // if((strcmp(argv[i],".") != 0) && (strcmp(argv[i], "..") != 0 ))
            // {
            int flag = 0;
            char direct[2000];
            if (strcmp(argv[i], ".") == 0)
            {

                strcpy(direct, cwd);
                flag = 1;
                // strcpy(prev_dir, cwd);
                // int d = chdir(argv[i]);
                // printf("%d", d);
                // continue;
            }
            else if (strcmp(argv[i], "~") == 0)
            {
                strcpy(direct, shell_invk_dir);
                flag = 1;
                // printf("@");
                // strcpy(prev_dir, dir);
                // printf("%s",dir);
                // int d = chdir(dir);
                // printf("%d", d);
            }
            // else if (strcmp(argv[i], "-") == 0)
            // {

            //     strcpy(direct, prev_dir);
            //     flag = 1;
            //     // printf("y");
            //     // printf("%s",prev_dir);
            //     // int d = chdir(prev_dir);
            //     // strcpy(prev_dir, cwd);
            //     // printf("%d", d);
            //     // continue;
            // }
            else if (strcmp(argv[i], "..") == 0)
            {
                int len = (strlen(cwd) - 1);
                int j;
                for (j = len; j >= 0; j--)
                {
                    if (strcmp(&cwd[j], "/") == 0)
                    {
                        break;
                    }
                }
                flag = 1;
                strncpy(direct, cwd, j);
                // printf("%s",direct);
                // strcpy(prev_dir, cwd);
                // int d = chdir(argv[i]);
                // printf("%d", d);
            }
            DIR *dir;
            struct stat buf;
            if ((stat(dir_path, &buf) != -1))
            {
                dir = opendir(dir_path);
            }
            else if (flag == 1)
            {
                dir = opendir(direct);
            }
            else
            {
                dir = opendir(argv[i]);
                if (dir == NULL)
                {
                    perror("");
                    return;
                }
            }
            struct dirent *direntry;
            int count = 0;
            struct stat inode;
            // printf("1sok");
            int max_owner_len = 0;
            int max_group_len = 0;
            int max_size_len = 0;
            while ((direntry = readdir(dir)) != NULL)
            {

                stat(direntry->d_name, &inode);

                struct passwd *owner_info = getpwuid(inode.st_uid);
                struct group *group_info = getgrgid(inode.st_gid);

                int owner_len = strlen(owner_info->pw_name);
                int group_len = strlen(group_info->gr_name);
                int size_len = snprintf(NULL, 0, "%ld", inode.st_size);

                if (owner_len > max_owner_len)
                    max_owner_len = owner_len;
                if (group_len > max_group_len)
                    max_group_len = group_len;
                if (size_len > max_size_len)
                    max_size_len = size_len;

                // printf("%s\n", direntry->d_name);
                count++;
            }

            rewinddir(dir);
            char **list = (char **)malloc(sizeof(char *) * count);
            assert(list != NULL);
            int p = 0;
            while ((direntry = readdir(dir)) != NULL)
            {
                // printf("%s\n",direntry->d_name);
                list[p] = (char *)malloc(sizeof(char) * 2000);
                assert(list[p] != NULL);
                strcpy(list[p], direntry->d_name);
                p++;
            }

            qsort(list, count, sizeof(char *), comparator);

            // closedir(dir);
            if ((l_flag == 1 && a_flag == 0))
            {
                char mode[11];
                int j = 0;
                while (j != count)
                {
                    stat(list[j], &inode);
                    char formatted_time[13];
                    format_time(&inode, formatted_time);
                    mode_to_text(inode.st_mode, mode);
                    struct passwd *owner_info = getpwuid(inode.st_uid);
                    struct group *group_info = getgrgid(inode.st_gid);
                    if (strcmp(list[j], ".") == 0 || strcmp(list[j], "..") == 0)
                    {

                        // printf("%s\n",direntry->d_name);
                        // continue; // Skip . and ..
                    }
                    else if (S_ISDIR(inode.st_mode))
                    {
                        printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                               max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                               max_size_len, inode.st_size, formatted_time, dir_color, list[j], COLOR_RESET);
                    }
                    else if (S_ISREG(inode.st_mode))
                    {
                        if (inode.st_mode & S_IXUSR)
                        {
                            printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                                   max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                                   max_size_len, inode.st_size, formatted_time, exe_color, list[j], COLOR_RESET);
                        }
                        else
                        {
                            printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                                   max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                                   max_size_len, inode.st_size, formatted_time, file_color, list[j], COLOR_RESET);
                        }
                    }
                    else
                    {
                        printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                               max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                               max_size_len, inode.st_size, formatted_time, other, list[j], COLOR_RESET);
                    }
                    j++;
                }
            }
            else if (l_flag == 0 && a_flag == 1)
            {
                int j = 0;
                while (j != count)
                {
                    stat(list[j], &inode);
                    if (S_ISDIR(inode.st_mode))
                    {
                        // printf("dir ");
                        //  printf("%s\n",list[i]);
                        printf("%s%s%s\n", dir_color, list[j], COLOR_RESET);
                    }
                    else if (S_ISREG(inode.st_mode))
                    {
                        if (inode.st_mode & S_IXUSR)
                        {
                            // printf("exe ");
                            // printf("exe ");
                            printf("%s%s%s\n", exe_color, list[j], COLOR_RESET);
                        }
                        else
                        {
                            // printf("fis ");
                            // printf("text ");
                            printf("%s%s%s\n", other, list[j], COLOR_RESET);
                        }
                    }
                    else
                    {
                        // printf("other");
                        // printf("other ");
                        printf("%s%s%s\n", other, list[j], COLOR_RESET);
                    }
                    j++;
                }
            }
            else if (l_flag == 1 && a_flag == 1)
            {
                char mode[11];
                int j = 0;
                while (j != count)
                {
                    stat(list[j], &inode);
                    char formatted_time[13];
                    format_time(&inode, formatted_time);
                    mode_to_text(inode.st_mode, mode);
                    struct passwd *owner_info = getpwuid(inode.st_uid);
                    struct group *group_info = getgrgid(inode.st_gid);

                    if (S_ISDIR(inode.st_mode))
                    {
                        printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                               max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                               max_size_len, inode.st_size, formatted_time, dir_color, list[j], COLOR_RESET);
                    }
                    else if (S_ISREG(inode.st_mode))
                    {
                        if (inode.st_mode & S_IXUSR)
                        {
                            printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                                   max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                                   max_size_len, inode.st_size, formatted_time, exe_color, list[j], COLOR_RESET);
                        }
                        else
                        {
                            printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                                   max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                                   max_size_len, inode.st_size, formatted_time, file_color, list[j], COLOR_RESET);
                        }
                    }
                    else
                    {
                        printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
                               max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
                               max_size_len, inode.st_size, formatted_time, other, list[j], COLOR_RESET);
                    }
                    j++;
                }
            }
            else
            {
                int j = 0;
                while (j != count)
                {
                    stat(list[j], &inode);
                    if (strcmp(list[j], ".") == 0 || strcmp(list[j], "..") == 0)
                    {

                        // printf("%s\n",direntry->d_name);
                        // continue; // Skip . and ..
                    }
                    else if (S_ISDIR(inode.st_mode))
                    {
                        // printf("dir ");
                        //  printf("%s\n",list[i]);
                        printf("%s%s%s\n", dir_color, list[j], COLOR_RESET);
                    }
                    else if (S_ISREG(inode.st_mode))
                    {
                        if (inode.st_mode & S_IXUSR)
                        {
                            // printf("exe ");
                            // printf("exe ");
                            printf("%s%s%s\n", exe_color, list[j], COLOR_RESET);
                        }
                        else
                        {
                            // printf("fis ");
                            // printf("text ");
                            printf("%s%s%s\n", other, list[j], COLOR_RESET);
                        }
                    }
                    else
                    {
                        // printf("other");
                        // printf("other ");
                        printf("%s%s%s\n", other, list[j], COLOR_RESET);
                    }
                    j++;
                }

                // printf("%s", argv[i]);
            }
            l_flag = 0;
            a_flag = 0;
        }
        i++;
    }
    if (i == 1)
    {
        DIR *dir;
        struct dirent *direntry;
        int count = 0;
        struct stat inode;
        // printf("1sok");
        int max_owner_len = 0;
        int max_group_len = 0;
        int max_size_len = 0;
        char cwd[2000];
        getcwd(cwd, sizeof(cwd));
        dir = opendir(cwd);
        while ((direntry = readdir(dir)) != NULL)
        {

            stat(direntry->d_name, &inode);

            struct passwd *owner_info = getpwuid(inode.st_uid);
            struct group *group_info = getgrgid(inode.st_gid);

            int owner_len = strlen(owner_info->pw_name);
            int group_len = strlen(group_info->gr_name);
            int size_len = snprintf(NULL, 0, "%ld", inode.st_size);

            if (owner_len > max_owner_len)
                max_owner_len = owner_len;
            if (group_len > max_group_len)
                max_group_len = group_len;
            if (size_len > max_size_len)
                max_size_len = size_len;

            // printf("%s\n", direntry->d_name);
            count++;
        }

        rewinddir(dir);
        char **list = (char **)malloc(sizeof(char *) * count);
        assert(list != NULL);
        int p = 0;
        while ((direntry = readdir(dir)) != NULL)
        {
            // printf("%s\n",direntry->d_name);
            list[p] = (char *)malloc(sizeof(char) * 2000);
            assert(list[p] != NULL);
            strcpy(list[p], direntry->d_name);
            p++;
        }

        qsort(list, count, sizeof(char *), comparator);

        int j = 0;
        while (j != count)
        {
            stat(list[j], &inode);
            if (strcmp(list[j], ".") == 0 || strcmp(list[j], "..") == 0)
            {

                // printf("%s\n",direntry->d_name);
                // continue; // Skip . and ..
            }
            else if (S_ISDIR(inode.st_mode))
            {
                // printf("dir ");
                //  printf("%s\n",list[i]);
                printf("%s%s%s\n", dir_color, list[j], COLOR_RESET);
            }
            else if (S_ISREG(inode.st_mode))
            {
                if (inode.st_mode & S_IXUSR)
                {
                    // printf("exe ");
                    // printf("exe ");
                    printf("%s%s%s\n", exe_color, list[j], COLOR_RESET);
                }
                else
                {
                    // printf("fis ");
                    // printf("text ");
                    printf("%s%s%s\n", other, list[j], COLOR_RESET);
                }
            }
            else
            {
                // printf("other");
                // printf("other ");
                printf("%s%s%s\n", other, list[j], COLOR_RESET);
            }
            j++;
        }
    }
}
// DIR *dir;
// if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "-al") != 0 && strcmp(argv[1], "-la") != 0)
// {
//     dir = opendir(argv[1]);
// }
// else
// {
//     if (strcmp(argv[2], "-l") != 0 && strcmp(argv[2], "-a") != 0)
//     {
//         // printf("1");
//         dir = opendir(argv[2]);
//     }
//     else
//     {
//         // printf("8");
//         dir = opendir(argv[3]);
//     }
// }
// // printf("%s", dir);

// struct dirent *direntry;
// int count = 0;
// struct stat inode;

// int max_owner_len = 0;
// int max_group_len = 0;
// int max_size_len = 0;
// while ((direntry = readdir(dir)) != NULL)
// {

//     stat(direntry->d_name, &inode);

//     struct passwd *owner_info = getpwuid(inode.st_uid);
//     struct group *group_info = getgrgid(inode.st_gid);

//     int owner_len = strlen(owner_info->pw_name);
//     int group_len = strlen(group_info->gr_name);
//     int size_len = snprintf(NULL, 0, "%ld", inode.st_size);

//     if (owner_len > max_owner_len)
//         max_owner_len = owner_len;
//     if (group_len > max_group_len)
//         max_group_len = group_len;
//     if (size_len > max_size_len)
//         max_size_len = size_len;

//     // printf("%s\n",direntry->d_name);
//     count++;
// }
// // printf("%d",count);
// rewinddir(dir);
// char **list = (char **)malloc(sizeof(char *) * count);
// int i = 0;
// while ((direntry = readdir(dir)) != NULL)
// {
//     list[i] = (char *)malloc(sizeof(char) * 2000);
//     strcpy(list[i], direntry->d_name);
//     i++;
//     // printf("%s", list[i]);
// }

// qsort(list, count, sizeof(char *), comparator);

// // for(int i=0;i<count;i++)
// // {
// // printf("%s\n",list[i]);
// // }
// if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "-al") != 0 && strcmp(argv[1], "-la") != 0)
// {
//     i = 0;

//     while (i != count)
//     {
//         printf("%s\n", direntry->d_name);
//         int d = stat(list[i], &inode);
//         // printf("%d",d);
//         if (strcmp(list[i], ".") == 0 || strcmp(list[i], "..") == 0)
//         {

//             // printf("%s\n",direntry->d_name);
//             // continue; // Skip . and ..
//         }

//         else if (S_ISDIR(inode.st_mode))
//         {
//             // printf("dir ");
//             //  printf("%s\n",list[i]);
//             printf("%s%s%s\n", dir_color, list[i], COLOR_RESET);
//         }
//         else if (S_ISREG(inode.st_mode))
//         {
//             if (inode.st_mode & S_IXUSR)
//             {
//                 // printf("exe ");
//                 // printf("exe ");
//                 printf("%s%s%s\n", exe_color, list[i], COLOR_RESET);
//             }
//             else
//             {
//                 // printf("fis ");
//                 // printf("text ");
//                 printf("%s%s%s\n", other, list[i], COLOR_RESET);
//             }
//         }
//         else
//         {
//             // printf("other");
//             // printf("other ");
//             printf("%s%s%s\n", other, list[i], COLOR_RESET);
//         }
//         // printf("%s\n",list[i]);
//         i++;
//     }
// }
// else
// {
//     if (strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "-a") != 0)
//     {
//         char mode[11];
//         i = 0;
//         while (i != count)
//         {
//             stat(list[i], &inode);
//             char formatted_time[13];
//             format_time(&inode, formatted_time);
//             mode_to_text(inode.st_mode, mode);
//             struct passwd *owner_info = getpwuid(inode.st_uid);
//             struct group *group_info = getgrgid(inode.st_gid);
//             if (strcmp(list[i], ".") == 0 || strcmp(list[i], "..") == 0)
//             {

//                 // printf("%s\n",direntry->d_name);
//                 // continue; // Skip . and ..
//             }
//             else if (S_ISDIR(inode.st_mode))
//             {
//                 printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                        max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                        max_size_len, inode.st_size, formatted_time, dir_color, list[i], COLOR_RESET);
//             }
//             else if (S_ISREG(inode.st_mode))
//             {
//                 if (inode.st_mode & S_IXUSR)
//                 {
//                     printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                            max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                            max_size_len, inode.st_size, formatted_time, exe_color, list[i], COLOR_RESET);
//                 }
//                 else
//                 {
//                     printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                            max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                            max_size_len, inode.st_size, formatted_time, file_color, list[i], COLOR_RESET);
//                 }
//             }
//             else
//             {
//                 printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                        max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                        max_size_len, inode.st_size, formatted_time, other, list[i], COLOR_RESET);
//             }
//             i++;
//         }
//     }
//     else if (strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "-l") != 0)
//     {
//         // rewinddir(dir);
//         i = 0;
//         while (i != count)
//         {
//             stat(list[i], &inode);
//             if (S_ISDIR(inode.st_mode))
//             {
//                 // printf("dir ");
//                 //  printf("%s\n",list[i]);
//                 printf("%s%s%s\n", dir_color, list[i], COLOR_RESET);
//             }
//             else if (S_ISREG(inode.st_mode))
//             {
//                 if (inode.st_mode & S_IXUSR)
//                 {
//                     // printf("exe ");
//                     // printf("exe ");
//                     printf("%s%s%s\n", exe_color, list[i], COLOR_RESET);
//                 }
//                 else
//                 {
//                     // printf("fis ");
//                     // printf("text ");
//                     printf("%s%s%s\n", other, list[i], COLOR_RESET);
//                 }
//             }
//             else
//             {
//                 // printf("other");
//                 // printf("other ");
//                 printf("%s%s%s\n", other, list[i], COLOR_RESET);
//             }
//             i++;
//         }
//     }
//     else if (strcmp(argv[1], "-la") == 0 || (strcmp(argv[1], "-al") == 0) || (strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "-a") == 0) || (strcmp(argv[1], "-a") == 0 && strcmp(argv[2], "-l") == 0))
//     {
//         // rewinddir(dir);

//         char mode[11];
//         i = 0;
//         while (i != count)
//         {
//             stat(list[i], &inode);
//             char formatted_time[13];
//             format_time(&inode, formatted_time);
//             mode_to_text(inode.st_mode, mode);
//             struct passwd *owner_info = getpwuid(inode.st_uid);
//             struct group *group_info = getgrgid(inode.st_gid);

//             if (S_ISDIR(inode.st_mode))
//             {
//                 printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                        max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                        max_size_len, inode.st_size, formatted_time, dir_color, list[i], COLOR_RESET);
//             }
//             else if (S_ISREG(inode.st_mode))
//             {
//                 if (inode.st_mode & S_IXUSR)
//                 {
//                     printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                            max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                            max_size_len, inode.st_size, formatted_time, exe_color, list[i], COLOR_RESET);
//                 }
//                 else
//                 {
//                     printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                            max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                            max_size_len, inode.st_size, formatted_time, file_color, list[i], COLOR_RESET);
//                 }
//             }
//             else
//             {
//                 printf("%s %*ld %-*s %-*s %*ld %s %s %s %s\n", mode, 2, inode.st_nlink,
//                        max_owner_len, owner_info->pw_name, max_group_len, group_info->gr_name,
//                        max_size_len, inode.st_size, formatted_time, other, list[i], COLOR_RESET);
//             }
//             i++;
//         }
//     }
// }
// }
