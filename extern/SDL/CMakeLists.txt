
set( BUNDLE_USE_SDL true CACHE BOOL "use the bundled version of the library?" )
set( BUNDLE_BUILD_SDL false CACHE INTERNAL "(re)build the bundled library?" )

if( ${BUNDLE_BUILD_SDL} )
  message( FATAL_ERROR "Building SDL not yet implemented." )
endif()

message( "Bundle-libraries: ${T4B_LIBPART}" )

if( ${BUNDLE_USE_SDL} )
  set( liblist 
    "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/libSDL.so"
    "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/libSDLmain.a"
    "-lpthread"
  )
  set( SDL_INCLUDE_DIR ${T4B_LIBBUNDLE_ROOT}/include CACHE PATH "library include paths" FORCE )
  set( SDL_LIBRARY ${liblist} CACHE PATH "library search paths" FORCE )
else()
  unset( SDL_INCLUDE_DIR CACHE )
  unset( SDL_LIBRARY CACHE )
  find_package( SDL )
endif()
