
# Default settings 
set( BUNDLE_USE_rapidxml true CACHE BOOL "use the bundled version of the library?" )

# ===================================ff

if( ${BUNDLE_USE_rapidxml} )
  set( rapidxml_INCLUDE_DIRS ${T4B_LIBBUNDLE_ROOT}/rapidxml/include CACHE PATH "library include paths" )
  set( HAVE_rapidxml true CACHE INTERNAL "" )

else()
  if( ${UNIX} )
    find_package( PkgConfig )
    pkg_search_module( rapidxml_tmp rapidxml )
    if( ${rapidxml_tmp_FOUND} )
      message( "Found rapidxml version ${rapidxml_tmp_VERSION}." )
      set( rapidxml_INCLUDE_DIRS ${libusb_tmp_INCLUDE_DIRS} CACHE PATH "" )
      set( HAVE_rapidxml true CACHE INTERNAL "" )
    else()
      set( HAVE_rapidxml false CACHE INTERNAL "" )
    endif()
  else()
    message( "Use bundled rapidxml on windows." )
    set( HAVE_rapidxml false CACHE INTERNAL "" )
  endif()
endif()
