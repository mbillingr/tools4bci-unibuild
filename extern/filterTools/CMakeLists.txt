
set( BUNDLE_USE_filterTools true CACHE BOOL "use the bundled version of the library?" )
set( BUNDLE_BUILD_filterTools false CACHE BOOL "(re)build the bundled library?" )

if( NOT ${BUNDLE_USE_filterTools} )
  message( FATAL_ERROR "Must use bundled ticpp." )
endif()

if( ${BUNDLE_BUILD_filterTools} )
  message( FATAL_ERROR "Building ticpp not yet implemented." )
endif()

set( filterTools_INCLUDE_DIRS ${T4B_LIBBUNDLE_ROOT}/include CACHE PATH "library include paths" )
