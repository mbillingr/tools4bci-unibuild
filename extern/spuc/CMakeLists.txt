
# Default settings 
set( BUNDLE_USE_spuc true CACHE BOOL "use the bundled version of the library?" )

# ===================================ff

if( ${BUNDLE_USE_spuc} )
  set( spuc_INCLUDE_DIRS 
    ${T4B_LIBBUNDLE_ROOT}/spuc/include
    ${T4B_LIBBUNDLE_ROOT}/spuc/include/spuc/generic
    CACHE PATH "library include paths" )
  set( HAVE_spuc true CACHE INTERNAL "" )

else()
  if( ${UNIX} )
    find_package( PkgConfig )
    pkg_search_module( spuc_tmp spuc )
    if( ${spuc_tmp_FOUND} )
      message( "Found spuc version ${spuc_tmp_VERSION}." )
      set( spuc_INCLUDE_DIRS ${spuc_tmp_INCLUDE_DIRS} CACHE PATH "" )
      set( HAVE_spuc true CACHE INTERNAL "" )
    else()
      set( HAVE_spuc false CACHE INTERNAL "" )
    endif()
  else()
    message( "Use bundled rapidxml on windows." )
    set( HAVE_spuc false CACHE INTERNAL "" )
  endif()
endif()
