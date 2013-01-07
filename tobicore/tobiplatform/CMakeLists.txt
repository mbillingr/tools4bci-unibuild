
set( HEADERS
	TPSocket.hpp
	TPMutex.hpp
	TPStreamer.hpp
	TPInterface.hpp
	TPiC.hpp
	TPiD.hpp
)

set( SOURCES
	TPMutex.cpp
	TPStreamer.cpp
	TPSocket.cpp
	TPInterface.cpp
	TPiC.cpp
	TPiD.cpp
)


foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${TOBICORE_ROOT}/src/tobiplatform/${src}" )
endforeach( src )

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${TOBICORE_ROOT}/src/tobiplatform/${hdr}" )
endforeach( hdr )

add_library( tobiplatform ${FULL_HEADERS} ${FULL_SOURCES} )
add_dependencies( tobiplatform tobicore-git )

list( APPEND T4B_BUILDLIST "tobiplatform" )
set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )
