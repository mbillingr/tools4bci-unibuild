project( signalserver )

if( ${WIN32} )
  set( WIN true )
else()
  set( WIN false )
endif()

if( ${HAVE_libusb} AND ${HAVE_Xrandr} AND ${HAVE_X11} )
  set( SIGSERVER_BUILD_MOUSE true CACHE BOOL "Hardware Device: Mouse" )
else()
  set( SIGSERVER_BUILD_MOUSE false CACHE BOOL "Hardware Device: Mouse" FORCE )
endif()

if( "${HAVE_libcomedi}" OR "${WIN}" )
  set( SIGSERVER_BUILD_GBSAMP true CACHE BOOL "Hardware Device: gBSamp" )
else()
  set( SIGSERVER_BUILD_GBSAMP false CACHE BOOL "Hardware Device: gBSamp" FORCE )
endif()

if( ${HAVE_brainproducts} )
  set( SIGSERVER_BUILD_BRAINPRODUCTS true CACHE BOOL "Hardware Device: brainamp series" )
else()
  set( SIGSERVER_BUILD_BRAINPRODUCTS false CACHE BOOL "Hardware Device: brainamp series" FORCE )
endif()

if( ${HAVE_dataq} )
  set( SIGSERVER_BUILD_DATAQ true CACHE BOOL "Hardware Device: dataq" )
else()
  set( SIGSERVER_BUILD_DATAQ false CACHE BOOL "Hardware Device: dataq" FORCE )
endif()

if( ${HAVE_nirscout} )
  set( SIGSERVER_BUILD_NIRSCOUT true CACHE BOOL "Hardware Device: NIRScout" )
else()
  set( SIGSERVER_BUILD_NIRSCOUT false CACHE BOOL "Hardware Device: NIRScout" FORCE )
endif()

if( ${HAVE_usbamp} )
  set( SIGSERVER_BUILD_USBAMP true CACHE BOOL "Hardware Device: gUSBamp" )
else()
  set( SIGSERVER_BUILD_USBAMP false CACHE BOOL "Hardware Device: gUSBamp" FORCE )
endif()

if( ${HAVE_plux} )
  set( SIGSERVER_BUILD_PLUX true CACHE BOOL "Hardware Device: Plux" )
else()
  set( SIGSERVER_BUILD_PLUX false CACHE BOOL "Hardware Device: Plux" FORCE )
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
  ${filterTools_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${SDL_INCLUDE_DIR}
  ${HW_VENDORS_INCLUDE_DIRS}
)

#message( "************** ${HW_VENDORS_INCLUDE_DIRS}" )

set( CONFIG_TIMING_TEST true CACHE BOOL "Build SigServer with timing tests (LptTools)" )

add_subdirectory( src )
  
list( APPEND T4B_BUILDLIST "Signalserver" )
set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )

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


