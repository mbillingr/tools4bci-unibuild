project( tobicore )

set( TOBICORE_INCLUDE_DIRS ${TOBICORE_ROOT}/src CACHE PATH "include directories for all tobicore libraries" )

include_directories( ${TOBICORE_INCLUDE_DIRS} )

add_subdirectory( tobicore )
add_subdirectory( tobiic )
add_subdirectory( tobiid )
add_subdirectory( tobiplatform )
add_subdirectory( libtid )
