#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st; // Declare a struct stat variable to store file status information

    // Check that a command-line argument specifying a file or directory was provided
    if (argc < 2) 
    {
        printf("Usage: %s <file or directory>\n", argv[0]);
        return 1;
    }

    // Get file status information for the specified file or directory
    if (stat(argv[1], &st) < 0) 
    {
        printf("Error: Could not get file status.\n");
        return 1;
    }

    printf("File size: %ld bytes\n", st.st_size); // Print file size in bytes
    printf("Blocks allocated: %ld\n", st.st_blocks); // Print number of blocks allocated to the file
    printf("Reference count: %ld\n", st.st_nlink); // Print number of hard links to the file
    printf("File permissions: "); // Print file permissions in the form of "rwxrwxrwx"
    printf((S_ISDIR(st.st_mode)) ? "d" : "-"); // check if file is a directory
    printf((st.st_mode & S_IRUSR) ? "r" : "-"); // check if owner has read permission
    printf((st.st_mode & S_IWUSR) ? "w" : "-"); // check if owner has write permission
    printf((st.st_mode & S_IXUSR) ? "x" : "-"); // check if owner has execute permission
    printf((st.st_mode & S_IRGRP) ? "r" : "-"); // check if group has read permission
    printf((st.st_mode & S_IWGRP) ? "w" : "-"); // check if group has write permission
    printf((st.st_mode & S_IXGRP) ? "x" : "-"); // check if group has execute permission
    printf((st.st_mode & S_IROTH) ? "r" : "-"); // check if others have read permission
    printf((st.st_mode & S_IWOTH) ? "w" : "-"); // check if others have write permission
    printf((st.st_mode & S_IXOTH) ? "x" : "-"); // check if others have execute permission
    printf("\n");

    // Print file inode number
    printf("File inode: %ld\n", st.st_ino);

    return 0;
}






