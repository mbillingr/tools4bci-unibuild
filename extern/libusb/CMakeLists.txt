
# Default settings 
if( ${UNIX} )
  set( BUNDLE_USE_libusb false CACHE BOOL "use the bundled version of the library?" )
elseif( ${WIN32} )
  set( BUNDLE_USE_libusb true CACHE BOOL "use the bundled version of the library?" )
else()
  set( BUNDLE_USE_libusb false CACHE BOOL "use the bundled version of the library?" )
endif()

# ===================================ff

if( ${BUNDLE_USE_libusb} )
  set( libusb_INCLUDE_DIRS ${T4B_LIBBUNDLE_ROOT}/libusb/include CACHE PATH "library include paths" )
  if( ${UNIX} )
    set( libusb_LIBRARIES "${T4B_LIBBUNDLE_ROOT}/libusb/lib/${T4B_LIBPART}/libusb0.a" CACHE FILEPATH "" )
  elseif( ${WIN32} )
    set( libusb_LIBRARIES 
	  debug "${T4B_LIBBUNDLE_ROOT}/libusb/lib/${T4B_LIBPART}/debug/libusb0.lib" 
	  optimized "${T4B_LIBBUNDLE_ROOT}/libusb/lib/${T4B_LIBPART}/release/libusb0.lib" 
	  CACHE FILEPATH "" )
  else()
    message( FATAL_ERROR "sorry, libusb is not bundled for your system." )
  endif()
  set( HAVE_libusb true CACHE INTERNAL "" )

else()
  if( ${UNIX} )
    find_package( PkgConfig )
    pkg_search_module( libusb_tmp libusb-1.0 )
    if( ${libusb_tmp_FOUND} )
      message( "Found libusb version ${libusb_tmp_VERSION}." )
      set( libusb_LIBRARIES ${libusb_tmp_LIBRARIES} CACHE STRING "" )
      set( libusb_INCLUDE_DIRS ${libusb_tmp_INCLUDE_DIRS} CACHE STRING "" )
      set( HAVE_libusb true CACHE INTERNAL "" )
    else()
      set( HAVE_libusb false CACHE INTERNAL "" )
    endif()
  else()
    message( "Use bundled libusb on windows." )
    set( HAVE_libusb false CACHE INTERNAL "" )
  endif()
endif()

if( ${BUNDLE_BUILD_libusb} )
  message( FATAL_ERROR "Building libusb not yet implemented." )
endif()
