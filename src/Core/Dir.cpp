//
// Created by kevin on 15/06/17.
//

#include "Dir.hh"

bool Dir::exists(const std::string &dir_path) {
#ifdef __unix__
    struct stat sb;
    return (stat(dir_path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
#else
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
#endif //__unix__
}

Dir::Dir(std::string const & dir) {
    if (!exists(dir)) {
#ifdef __unix__
        mkdir(dir.c_str(), 0755);
#else
        _mkdir(dir.c_str())
#endif // __unix__
    }
}

Dir::~Dir() {

}
