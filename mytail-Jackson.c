#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) 
{
    int i, n, lines_seen = 0;
    char buffer[BUFFER_SIZE];
    FILE *fp;
    
    // check that the correct number of arguments have been provided
    if (argc != 3) 
    {
        fprintf(stderr, "Usage: %s -n file\n", argv[0]);
        return 1;
    }
    
    // parse the number of lines to print
    n = atoi(argv[1]);
    if (n <= 0) 
    {
        fprintf(stderr, "Invalid number of lines: %s\n", argv[1]);
        return 1;
    }
    
    // open the file and check for errors
    fp = fopen(argv[2], "r");
    if (fp == NULL) 
    {
        perror("fopen");
        return 1;
    }
    
    // read through the file and count the number of lines
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) 
    {
        lines_seen++;
    }
    
    // reset the file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);
    
    // skip over the first (lines_seen - n) lines
    if (lines_seen > n) 
    {
        for (i = 0; i < (lines_seen - n); i++) 
        {
            fgets(buffer, BUFFER_SIZE, fp);
        }
    }
    
    // print out the last n lines of the file
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) 
    {
        fputs(buffer, stdout);
    }
    
    // close the file and return
    fclose(fp);
    return 0;
}