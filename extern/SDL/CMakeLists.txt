
# Default settings 
if( ${UNIX} )
  set( BUNDLE_USE_SDL false CACHE BOOL "use the bundled version of the library?" )
elseif( ${WIN32} )
  set( BUNDLE_USE_SDL true CACHE BOOL "use the bundled version of the library?" )
else()
  set( BUNDLE_USE_SDL false CACHE BOOL "use the bundled version of the library?" )
endif()

# ===================================ff

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
