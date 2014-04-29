if (LibNewt_LIBRARIES AND LibNewt_INCLUDE_DIRS)
  set (LibNewt_FIND_QUIETLY TRUE)
endif (LibNewt_LIBRARIES AND LibNewt_INCLUDE_DIRS)

find_path (LibNewt_INCLUDE_DIRS NAMES newt.h)
find_library (LibNewt_LIBRARIES NAMES newt)

include (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibNewt DEFAULT_MSG
    LibNewt_LIBRARIES
    LibNewt_INCLUDE_DIRS)

mark_as_advanced(LibNewt_INCLUDE_DIRS LibNewt_LIBRARIES)