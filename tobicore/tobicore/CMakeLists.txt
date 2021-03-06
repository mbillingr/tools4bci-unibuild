
set( HEADERS
  TCBlock.hpp
  TCTimestamp.hpp
  TCTools.hpp
  TCException.hpp
  TCSerializer.hpp
  TCLanguage.hpp
  TCTypes.hpp
  TCTime.hpp
)

set( SOURCES
  TCBlock.cpp
  TCTimestamp.cpp
  TCTools.cpp
  TCException.cpp
  TCSerializer.cpp
  TCLanguage.cpp
  TCTime.cpp
)

foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${TOBICORE_ROOT}/src/tobicore/${src}" )
endforeach( src )

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${TOBICORE_ROOT}/src/tobicore/${hdr}" )
endforeach( hdr )

add_library( tobicore ${FULL_HEADERS} ${FULL_SOURCES} )
add_dependencies( tobicore tobicore-git )


list( APPEND T4B_BUILDLIST "tobicore" )
set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )

install( FILES ${FULL_HEADERS} DESTINATION include/tobicore )
install( TARGETS tobicore
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
