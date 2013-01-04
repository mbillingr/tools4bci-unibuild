project( signalserver )

configure_libtia()

external_package( ticpp )
external_package( libgdf )
external_package( libusb )

include_directories(
  ${SIGSERVER_ROOT}/include
  ${libtia_INCLUDE_DIRS}
  ${TOBICORE_INCLUDE_DIRS}
  ${ticpp_INCLUDE_DIR}
  ${libusb_INCLUDE_DIR}
)

#message( ${libtia_INCLUDE_DIRS} )

set( CONFIG_TIMING_TEST true CACHE BOOL "Build SigServer with timing tests (LptTools)" )

add_subdirectory( src )

add_executable( signalserver ${HEADERS} ${SOURCES} )
