#ifndef POSIX_H
#define POSIX_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a file
int create_file(const char *path, mode_t mode) {
    int fd = open(path, O_CREAT | O_WRONLY, mode);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    close(fd);
    return 0;
}

// Function to read from a file
ssize_t read_file(const char *path, void *buf, size_t count) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    ssize_t bytes_read = read(fd, buf, count);
    if (bytes_read == -1) {
        perror("read");
    }
    close(fd);
    return bytes_read;
}

// Function to write to a file
ssize_t write_file(const char *path, const void *buf, size_t count) {
    int fd = open(path, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    ssize_t bytes_written = write(fd, buf, count);
    if (bytes_written == -1) {
        perror("write");
    }
    close(fd);
    return bytes_written;
}

// Function to delete a file
int delete_file(const char *path) {
    if (unlink(path) == -1) {
        perror("unlink");
        return -1;
    }
    return 0;
}

// Function to list directory contents
int list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return -1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}

#endif // POSIX_H