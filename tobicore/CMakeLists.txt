project( tobicore )

set( TOBICORE_INCLUDE_DIRS ${TOBICORE_ROOT}/src )

include_directories( ${TOBICORE_INCLUDE_DIRS} )

add_subdirectory( tobicore )
add_subdirectory( tobiic )
add_subdirectory( tobiid )
add_subdirectory( tobiplatform )
add_subdirectory( libtid )
