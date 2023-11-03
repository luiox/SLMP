#ifndef BCAT_FILE_FILE_H
#define BCAT_FILE_FILE_H

#include <stdlib.h>
#ifdef __linux
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include <string>

class file_info
{
private:
    struct stat m_stat;

public:
    file_info();

    void search_info(int fd);
    struct stat & get_stat();

    mode_t get_mode();
};

class file
{
private:
    int m_fd;

public:
    file();
    file(const char * filename);
    ~file();

    void open(const char * filename);
    void write_binary(const void * bytes, size_t length);
    void close();
};

class directory
{
private:
    std::string m_path;
    DIR* m_dir;

public:
    directory();
    directory(std::string& path);
    ~directory();
    void readdir();
    static int make_directory(std::string& path, mode_t mode);
    static int remove_directory(std::string & path);
};

#endif
