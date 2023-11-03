#include "file.h"



file::file()
  : m_fd(-1)
{
}

file::file(const char * filename)
  : m_fd(::open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR))
{
}

file::~file()
{
    close();
}

void
file::open(const char * filename)
{
    if (NULL == filename) {
        return;
    }
    m_fd = ::open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
}

void
file::write_binary(const void * bytes, size_t length)
{
    if (NULL == bytes && -1 == m_fd) {
        return;
    }
    write(m_fd, bytes, length);
}

void
file::close()
{
    if (-1 != m_fd) {
        ::close(m_fd);
    }
}

file_info::file_info() {}

void
file_info::search_info(int fd)
{
    fstat(fd, &m_stat);
}

struct stat&
file_info::get_stat()
{
    return m_stat;
}

mode_t
file_info::get_mode()
{
    return m_stat.st_mode;
}

directory::directory() {}

directory::directory(std::string& path):m_path(path) {
    m_dir = opendir(m_path.c_str());
}

directory::~directory() {}

void
directory::readdir()
{
    auto d = ::readdir(m_dir);
    
}

int
directory::make_directory(std::string & path, mode_t mode)
{
    return ::mkdir(path.c_str(),mode);
}

int
directory::remove_directory(std::string & path)
{
    return ::rmdir(path.c_str());
}
