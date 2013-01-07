
set( HEADERS
	IDTypes.hpp
	IDMessage.hpp
	IDSerializer.hpp
	IDSerializerRapid.hpp
	IDAsClient.hpp
)

set( SOURCES
	IDMessage.cpp
	IDSerializer.cpp
	IDSerializerRapid.cpp
	IDAsClient.cpp
)


foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${TOBICORE_ROOT}/src/tobiid/${src}" )
endforeach( src )

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${TOBICORE_ROOT}/src/tobiid/${hdr}" )
endforeach( hdr )

add_library( tobiid ${FULL_HEADERS} ${FULL_SOURCES} )
add_dependencies( tobiid tobicore-git )

list( APPEND T4B_BUILDLIST "tobiid" )
set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )

install( FILES ${FULL_HEADERS} DESTINATION include/tobiid )
install( TARGETS tobiid
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
