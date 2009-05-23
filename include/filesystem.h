#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include <stdexcept>

namespace fs {

// warning: this is a dummy function that returns contents of file to a string
// string may be rather huge to fit in RAM
std::string cat( const std::string& path ) throw (std::runtime_error);

int mkdir( const std::string& path );
int rmdir( const std::string& path );
int cd( const std::string& path );
std::string pwd();

// dummy way: no permision care
int cp( const std::string& witch, const std::string& where );

template <class BackInsertIterator>
int ls( std::string dir, BackInsertIterator bi, int deep = 256 )
{
  if ( deep <= 0 ) {
    return 0;
  }
  
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    return errno;
  }
  
  errno = 0;

  while ((dirp = readdir(dp)) != NULL) {
    std::string name = std::string(dirp->d_name);
    if ( (name != ".") && (name != "..") ) {
      if ( dirp->d_type == DT_DIR ) {
        if ( ls( dir + "/" + name, bi, deep - 1 ) != 0 ) {
          return errno;
        }
      } else {
        (*bi)++ = (dir + "/" + name);
      }
    }
  }
  
  closedir(dp);
  return errno;
}


} // fs
 

#endif // _FILESYSTEM_H_
