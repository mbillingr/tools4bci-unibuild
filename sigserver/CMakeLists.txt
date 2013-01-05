project( signalserver )

if( ${HAVE_libusb} AND ${HAVE_Xrandr} AND ${HAVE_X11} )
  set( SIGSERVER_BUILD_MOUSE true CACHE BOOL "Hardware Device: Mouse" )
else()
  set( SIGSERVER_BUILD_MOUSE false CACHE BOOL "Hardware Device: Mouse" FORCE)
endif()

if( ${HAVE_libcomedi} )
  set( SIGSERVER_BUILD_GBSAMP true CACHE BOOL "Hardware Device: gBSamp" )
else()
  set( SIGSERVER_BUILD_GBSAMP false CACHE BOOL "Hardware Device: gBSamp" FORCE)
endif()

set( SIGSERVER_BUILD_KINECT true CACHE BOOL "Hardware Device: Kinect" FORCE)

# ============================

configure_libtia()

find_package( Boost REQUIRED COMPONENTS filesystem program_options )

include_directories(
  ${SIGSERVER_ROOT}/include
  ${libtia_INCLUDE_DIRS}
  ${TOBICORE_INCLUDE_DIRS}
  ${ticpp_INCLUDE_DIR}
  ${libusb_INCLUDE_DIRS}
  ${libgdf_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${SDL_INCLUDE_DIR}
)

#message( ${libtia_INCLUDE_DIRS} )

set( CONFIG_TIMING_TEST true CACHE BOOL "Build SigServer with timing tests (LptTools)" )

add_subdirectory( src )

add_executable( signalserver ${HEADERS} ${SOURCES} )
add_dependencies( signalserver sigserver-git )

target_link_libraries( signalserver GDF ticpp tia ${libtia_LIBRARIES} ${libtid_LIBRARIES} ${Boost_LIBRARIES} ${SDL_LIBRARY} )

if( ${SIGSERVER_BUILD_MOUSE} )
  target_link_libraries( signalserver ${libusb_LIBRARIES} ${Xrandr_LIBRARIES} ${X11_LIBRARIES} )
endif()

if( ${SIGSERVER_BUILD_KINECT} )
  if( ${UNIX} )
    target_link_libraries( signalserver rt )
  endif()
endif()


