#include "headers.h"

void addcommand(char* copy, char *shell_invok_dir)
{
    int MAX_LINES = 15;
    int MAX_LINE_LENGTH = 4096;
    char *array = (char *)malloc(sizeof(char) * 2000);
    strcpy(array, shell_invok_dir);
    strcat(array, "/pastevents.txt");
    array[strlen(shell_invok_dir) + 15] = '\0';
    FILE *f;
    f = fopen(array, "a+");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }
    char arr[MAX_LINES][MAX_LINE_LENGTH];
    int nof_commands = 0;

    // Set the file pointer to the beginning
    fseek(f, 0, SEEK_SET);

    // Read existing lines into the array
    while (nof_commands < MAX_LINES && fgets(arr[nof_commands], sizeof(arr[0]), f) != NULL)
    {
        nof_commands++;
    }

    // If the last line is different from the new line (copy)
    if (strcmp(arr[nof_commands - 1], copy) != 0)
    {
        if (nof_commands < MAX_LINES)
        {
            // If there's space in the array, just append the new line
            fputs(copy, f);
        }
        else
        {
            // Shift lines in the array to remove the first line
            for (int i = 0; i < MAX_LINES - 1; i++)
            {
                strcpy(arr[i], arr[i + 1]);
            }
            strcpy(arr[MAX_LINES - 1], copy);

            // Close the file and reopen it for writing
            fclose(f);
            f = fopen("pastevents.txt", "w+");
            if (f == NULL)
            {
                perror("Error opening file");
            }

            // Write the updated array back to the file
            for (int i = 0; i < MAX_LINES; i++)
            {
                fputs(arr[i], f);
            }
        }
    }

    fclose(f);
}