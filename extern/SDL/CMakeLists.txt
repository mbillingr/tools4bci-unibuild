
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
  
  if( ${UNIX} )
    set( liblist
      "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/libSDL.so"
      "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/libSDLmain.a" 
      "-lpthread"	  
    )
    set( SDL_LIBRARY ${liblist} CACHE PATH "library search paths" FORCE )
  endif()
  
  if( ${WIN32} )
    set( liblist_dbg
      debug "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/Debug/SDL.lib"
      debug "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/Debug/SDLmain.lib" 
    )
    set( liblist_rel
      optimized "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/Release/SDL.lib"
      optimized "${T4B_LIBBUNDLE_ROOT}/lib/SDL/${T4B_LIBPART}/Release/SDLmain.lib" 
    )	
    set( SDL_LIBRARY ${liblist_dbg} ${liblist_rel} CACHE PATH "library search paths" FORCE )
  endif()
  
  set( SDL_INCLUDE_DIR ${T4B_LIBBUNDLE_ROOT}/include CACHE PATH "library include paths" FORCE )
else()
  #unset( SDL_INCLUDE_DIR CACHE )
  #unset( SDL_LIBRARY CACHE )
  find_package( SDL )
endif()
