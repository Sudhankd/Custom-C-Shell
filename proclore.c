#include "headers.h"

void proclore(char **arg)
{
    int pid;
    if (strcmp(arg[1], "\0") != 0)
    {
        pid = atoi(arg[1]);
    }
    else
    {
        pid = getpid();
    }
    // Replace with the PID of the process you're interested in
    char path[50];

    // char line[100];
    snprintf(path, sizeof(path), "/proc/%d/", pid);

    // printf("%s",path);
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("invalid process id");
        return;
    }

    struct dirent *dirent;
    char *buffer = (char *)malloc(sizeof(char) * 2000);
    char status[2000];
    unsigned long vm_size;
    while ((dirent = readdir(dir)) != NULL)
    {
        char *copy = (char *)malloc(sizeof(char) * 50);
        if (strcmp(dirent->d_name, "stat") == 0)
        {
            strcpy(copy, path);
            strcat(copy, "/stat");
            FILE *stat_file = fopen(copy, "r");
            char arr[2000];
            // char barr[2000];/
            while (fgets(arr, sizeof(arr), stat_file) != NULL)
            {
                // strcpy(barr, arr);
                int i = 0;
                // printf("%s", arr);

                char *token = strtok(arr, " ");
                while (i < 2)
                {
                    i++;
                    token = strtok(NULL, " ");
                }
                strcpy(status, token);
                break;
            }

            // if(strcmp(,"\0") == 0)
            // // {
            // printf("%s", token);

            // printf("%d",tc_pgid);
            fclose(stat_file);
        }
        else if (strcmp(dirent->d_name, "status") == 0)
        {
            strcpy(copy, path);
            strcat(copy, "status");
            FILE *status_file = fopen(copy, "r");
            char arr[2000];
            char *target = "VmSize:";
            size_t target_len = strlen(target);
            while (fgets(arr, sizeof(arr), status_file) != NULL)
            {
                if (strncmp(target, arr, target_len) == 0)
                {
                    if (sscanf(arr + target_len, "%lu", &vm_size) == 1)
                    {
                        break;
                    }
                }
            }
            fclose(status_file);
        }
        else if (strcmp(dirent->d_name, "exe") == 0)
        {
            // printf("1");
            char exe_path[2000];
            snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
            int len = readlink(exe_path, buffer, 2000);

            if (len != -1)
            {
                buffer[len] = '\0'; // Null-terminate the string
                // return 0;           // Success
            }
            else
            {
                perror("Failed to read symbolic link");
                // return -1; // Error
            }
        }
    }
    printf("process id: %d\n", pid);
    pid_t foreground_pgid = tcgetpgrp(STDIN_FILENO);
    pid_t process_pgid = getpgid(pid);

    if (foreground_pgid == process_pgid)
    {
        // pid_t tc_pgid = tcspgrp(STDIN_FILENO);
        printf("process status : %s+\n", status);
    }
    else
    {
        printf("process status : %s\n", status);
    }
    // pid_t shell_pgid = getpgrp();
    pid_t my_pgid = getpgid(pid);

    printf("process group: %d\n", my_pgid);
    printf("Virtual memory : %lu KB\n", vm_size);
    printf("executable path: %s\n", buffer);

    return;
}