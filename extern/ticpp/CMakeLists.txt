
set( BUNDLE_USE_ticpp true CACHE BOOL "use the bundled version of the library?" )
set( BUNDLE_BUILD_ticpp false CACHE BOOL "(re)build the bundled library?" )

if( NOT ${BUNDLE_USE_ticpp} )
  message( FATAL_ERROR "Must use bundled ticpp." )
endif()

if( ${BUNDLE_BUILD_ticpp} )
  message( FATAL_ERROR "Building ticpp not yet implemented." )
endif()

set( ticpp_INCLUDE_DIRS ${T4B_LIBBUNDLE_ROOT}/include CACHE PATH "library include paths" )
