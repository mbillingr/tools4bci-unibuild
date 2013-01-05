
  if( ${UNIX} )
    find_package( PkgConfig )
    pkg_search_module( X11_tmp x11 )
    if( ${libusb_tmp_FOUND} )
      message( "Found Xrandr version ${X11_tmp_VERSION}." )
      set( X11_LIBRARIES ${X11_tmp_LIBRARIES} CACHE STRING "" )
      set( X11_INCLUDE_DIRS ${X11_tmp_INCLUDE_DIRS} CACHE STRING "" )
      set( HAVE_X11 true CACHE INTERNAL "" )
    else()
      set( HAVE_X11 false CACHE INTERNAL "" )
    endif()
  else()
    # don't need X11 on windows, so pretend we have it...
    set( HAVE_X11 true CACHE INTERNAL "" )
  endif()

