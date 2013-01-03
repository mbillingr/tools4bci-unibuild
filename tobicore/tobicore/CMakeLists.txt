
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
