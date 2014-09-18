#include "demo-common.h"
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h> //For Glib::build_filename().
#include <iostream>

#ifdef GLIBMM_WIN32

#undef DEMOCODEDIR

// TODO: Apply scorched earth tactics on code below.
static char *
get_democodedir(void)
{
  static char *result = NULL;

  if (result == NULL)
    {
      result = g_win32_get_package_installation_directory_of_module(0);
      if (result == NULL)
	result = "unknown-location";

      result = g_strconcat (result, "\\share\\gtkmm-3.0\\demo", NULL);
    }

  return result;
}

#define DEMOCODEDIR get_democodedir()

#endif // GLIBMM_WIN32

/**
 * demo_find_file:
 * @base: base filename
 * 
 * Looks for @base first in the current directory, then in the
 * location where gtkmm will be installed on make install,
 * returns the first file found.
 * 
 * Return value: the filename, if found, else throws a Glib::FileError.
 **/
std::string demo_find_file(const std::string& base)
{
  if(Glib::file_test("gtk-logo-rgb.gif", Glib::FILE_TEST_EXISTS) &&
      Glib::file_test (base, Glib::FILE_TEST_EXISTS))
  {
    return base;
  }
  else
  {
    std::string filename = Glib::build_filename(DEMOCODEDIR, base);
    if(!Glib::file_test(filename, Glib::FILE_TEST_EXISTS))
    {
      Glib::ustring msg = "Cannot find demo data file " + base;  

      throw Glib::FileError(Glib::FileError::NO_SUCH_ENTITY, msg);
      return Glib::ustring();
    }
    
    return filename;
  }
}

