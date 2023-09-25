#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


int main(int argc, char *argv[]) 
{
    char path[1024]; // A character array to store the path of the directory to be listed
    struct dirent *dirPointer; // A pointer to the directory entry structure
    DIR *dir;  // A pointer to the directory structure

    // get directory path
    if (argc == 1) // If no arguments provided, use the current directory
    {
        if (getcwd(path, sizeof(path)) == NULL) // Get the current working directory
        {

        }
    } 
    else if (argc == 2 && strcmp(argv[1], "-l")  == 0) // If the "-l" option is provided, use the current directory
    {
        if (getcwd(path, sizeof(path)) == NULL) // Get the current working directory
        {

        }
    } 
    else if (argc == 2 && strcmp(argv[1], "-l")  != 0) // If a directory name is provided, use that
    {
        dir = opendir(argv[1]); // Open the specified directory.
        if (getcwd(path, sizeof(path)) == NULL) // Get the current working directory
        {

        }
    } 
    else if (argc == 3 && strcmp(argv[1], "-l") == 0) // If both the "-l" option and a directory name are provided, use the specified directory
    {
        strncpy(path, argv[2], sizeof(path));
    } 
    else // Invalid usage
    {
        printf("Usage: myls [-l] [directory]\n");
    }

    // open directory
    if(dir==NULL)
    {
        dir = opendir(path);
    }

    // If both the "-l" option and a directory name are provided, use the specified directory    
    while ((dirPointer = readdir(dir)) != NULL) 
    {
        if (strcmp(dirPointer->d_name, ".") != 0 && strcmp(dirPointer->d_name, "..") != 0) // Exclude the current and parent directories from the listing
        {
            if (argc == 1 || (argc == 2 ) || (argc == 3 && strcmp(argv[1], "-l") == 0)) // If no options are provided or only the "-l" option is provided, print only the file names
            {
                // Get information about the file using the stat() function.
                struct stat file_stat;
                char file_path[1024];
                snprintf(file_path, sizeof(file_path), "%s/%s", path, dirPointer->d_name);
                if (stat(file_path, &file_stat) == -1 && dir==NULL) 
                {
                    printf("Unable to get file information for %s\n", dirPointer->d_name);
                } 
                else 
                {
                    // Get the owner and group names for the file
                    struct passwd *pw = getpwuid(file_stat.st_uid);
                    struct group  *gr = getgrgid(file_stat.st_gid);
                    char *user_name = pw ? pw->pw_name : "unknown";
                    char *group_name = gr ? gr->gr_name : "unknown";
                    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-l") != 0)) // If no options are specified, print just the file name
                    {
                        printf("%s\n", dirPointer->d_name);
                    } 
                    else // If the -l option is specified, print detailed file information
                    {
                        // Print the file type and permissions
                        printf("%c%s%s%s%s%s%s%s%s %ld %s %s %lld %s %s\n",
                        (S_ISDIR(file_stat.st_mode)) ? 'd' : '-',
                        (file_stat.st_mode & S_IRUSR) ? "r" : "-",
                        (file_stat.st_mode & S_IWUSR) ? "w" : "-",
                        (file_stat.st_mode & S_IXUSR) ? "x" : "-",
                        (file_stat.st_mode & S_IRGRP) ? "r" : "-",
                        (file_stat.st_mode & S_IWGRP) ? "w" : "-",
                        (file_stat.st_mode & S_IXGRP) ? "x" : "-",
                        (file_stat.st_mode & S_IROTH) ? "r" : "-",
                        (file_stat.st_mode & S_IWOTH) ? "w" : "-",
                        (long) file_stat.st_nlink,
                        user_name,
                        group_name,
                        (long long) file_stat.st_size,
                        strtok(ctime(&file_stat.st_mtime), "\n"),
                        dirPointer->d_name);
                    }
                }
            }
        }
    }

    // close directory
    closedir(dir);
    return 0;
}