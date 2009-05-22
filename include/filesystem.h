#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include <stdexcept>

namespace fs {

// warning: this is a dummy function that returns contents of file to a string
// string may be rather huge to fit in RAM
std::string read_content( const std::string& path ) throw (std::runtime_error);

template <class BackInsertIterator>
int list_dir( std::string dir, BackInsertIterator bi )
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    std::string name = std::string(dirp->d_name);
    if ( (name != ".") && (name != "..") ) {  
      (*bi)++ = name;
    }
  }

  closedir(dp);
  return 0;
}

} // fs

#endif // _FILESYSTEM_H_
