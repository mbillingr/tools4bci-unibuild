project( tobicore )

set( TOBICORE_INCLUDE_DIRS ${TOBICORE_ROOT}/src CACHE PATH "include directories for all tobicore libraries" )

include_directories( ${TOBICORE_INCLUDE_DIRS} )

add_subdirectory( tobicore )
add_subdirectory( tobiic )
add_subdirectory( tobiid )
add_subdirectory( libtid )

if( ${UNIX} )
  add_subdirectory( tobiplatform )
endif()

if( ${BUILD_PYTHON_MODULES} )
  add_subdirectory( python )
endif()


set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )
