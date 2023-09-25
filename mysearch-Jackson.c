#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to print the contents of a directory tree
void print_tree(char* root_dir) 
{
    // Declare variables for directory and file information
    DIR* dir;
    struct dirent* entry;
    struct stat info;
    
    // Open the directory for reading
    dir = opendir(root_dir);
    if (dir == NULL) // Check if directory was opened successfully
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Loop through each item in the directory
    while ((entry = readdir(dir)) != NULL) 
    {
        // Create a string with the path to the current item
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", root_dir, entry->d_name);
        
        if (stat(path, &info) != 0) // Check if stat function returns an error
        {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        
        // Skip printing the "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }
        
        // Print the current item (file or directory)
        printf("%s\n", path);
        
        // Recursively print the contents of any sub-directories
        if (S_ISDIR(info.st_mode)) 
        {
            print_tree(path); // Recursively call print_tree with the sub-directory as the root directory
        }
    }
    
    closedir(dir); // Close the directory
}

// The main function 
int main(int argc, char* argv[]) 
{
    char* start_dir; // Declare a variable for the starting directory
    
    if (argc < 2)     // Check if a starting directory was provided as a command line argument
    {
        start_dir = "."; // If no argument was provided, use the current directory
    } 
    else 
    {
        start_dir = argv[1]; // Use the argument as the starting directory
    }
    
    // Call the print_tree function with the starting directory
    print_tree(start_dir);
    
    return EXIT_SUCCESS;
}