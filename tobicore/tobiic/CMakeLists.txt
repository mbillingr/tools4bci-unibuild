
set( HEADERS
	ICTypes.hpp
	ICClass.hpp
	ICClassifier.hpp
	ICMessage.hpp
	ICMapClass.hpp
	ICMapClassifier.hpp
	ICSetClass.hpp
	ICSetClassifier.hpp
	ICSerializer.hpp
	ICSerializerRapid.hpp
)

set( SOURCES
	ICClass.cpp
	ICClassifier.cpp
	ICMessage.cpp
	ICSetClass.cpp
	ICSetClassifier.cpp
	ICSerializer.cpp
	ICSerializerRapid.cpp
)


foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${TOBICORE_ROOT}/src/tobiic/${src}" )
endforeach( src )

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${TOBICORE_ROOT}/src/tobiic/${hdr}" )
endforeach( hdr )

add_library( tobiic ${FULL_HEADERS} ${FULL_SOURCES} )
add_dependencies( tobiic tobicore-git )

list( APPEND T4B_BUILDLIST "tobiic" )
set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )

install( FILES ${FULL_HEADERS} DESTINATION include/tobiic )
install( TARGETS tobiic
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
