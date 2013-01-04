
  if( ${UNIX} )
    find_package( PkgConfig )
    pkg_search_module( xrandr_tmp xrandr )
    if( ${libusb_tmp_FOUND} )
      message( "Found Xrandr version ${xrandr_tmp_VERSION}." )
      set( Xrandr_LIBRARIES ${xrandr_tmp_LIBRARIES} CACHE STRING "" )
      set( Xrandr_INCLUDE_DIRS ${xrandr_tmp_INCLUDE_DIRS} CACHE STRING "" )
      set( HAVE_Xrandr true CACHE INTERNAL "" )
    else()
      set( HAVE_Xrandr false CACHE INTERNAL "" )
    endif()
  else()
    # don't need xrandr on windows, so pretend we have it...
    set( HAVE_Xrandr true CACHE INTERNAL "" )
  endif()

