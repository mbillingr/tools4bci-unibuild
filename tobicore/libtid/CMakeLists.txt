
#external_package( SDL )

find_package( Boost REQUIRED COMPONENTS system thread )

set( libtid_INCLUDE_DIRS "${TOBICORE_ROOT}/src/libtid" CACHE PATH "include directories for libTiD" )

#set( LIBTID_INCLUDE_DIRS 
#  ${libtid_INCLUDE_DIRS}
#  ${Boost_INCLUDE_DIR}
#)

include_directories( ${libtid_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${SDL_INCLUDE_DIR} )

set( TID_HEADERS
	tid_server.h
	tid_exceptions.h
	tid_connection.h
	tcp_connection.h
	input_stream_socket.h
	tid_client_base.h
	tid_client.h
	sdl_tid_client.h
	tcp_server.h
	input_stream.h
)

set( MSG_HEADERS
	messages/tid_message_types.h
	messages/tid_message_tags_1_0.h
	messages/tid_message_parser_1_0.h
	messages/tid_message_parser.h
	messages/tid_message_builder_1_0.h
	messages/tid_message_builder.h
	messages/tid_message.h
)

set( SOURCES
	tid_server.cpp
	tid_connection.cpp
	tcp_connection.cpp
	input_stream_socket.cpp
	tid_client_base.cpp
	tid_client.cpp
	sdl_tid_client.cpp
	tcp_server.cpp
	messages/tid_message_parser_1_0.cpp
)

set( SERVER_SOURCES
	${TOBICORE_ROOT}/src/libtid/main_server.cpp
)

set( CLIENT_SOURCES
	${TOBICORE_ROOT}/src/libtid/main_client.cpp
)


foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${TOBICORE_ROOT}/src/libtid/${src}" )
endforeach( src )

foreach( hdr ${TID_HEADERS} )
  set( FULL_TID_HEADERS ${FULL_TID_HEADERS} "${TOBICORE_ROOT}/src/libtid/${hdr}" )
endforeach( hdr )

foreach( hdr ${MSG_HEADERS} )
  set( FULL_MSG_HEADERS ${FULL_MSG_HEADERS} "${TOBICORE_ROOT}/src/libtid/${hdr}" )
endforeach( hdr )

list( APPEND T4B_BUILDLIST "libtid" )

add_library( tid ${FULL_TID_HEADERS} ${FULL_MSG_HEADERS} ${FULL_SOURCES} )
add_dependencies( tid tobicore-git )

set( libtid_LIBRARIES tid tobiid tobicore ${Boost_LIBRARIES} CACHE INTERNAL "")

set( BUILD_TID_SERVER true CACHE BOOL "build TiD Server?" )
set( BUILD_TID_CLIENT true CACHE BOOL "build TiD Client?" )

link_directories( ${Boost_LIBRARY_DIRS} )

install( FILES ${FULL_TID_HEADERS} DESTINATION include/tid )
install( FILES ${FULL_MSG_HEADERS} DESTINATION include/tid/messages )
install( TARGETS tid
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

if( ${BUILD_TID_SERVER} )
  add_executable( tid-server ${SERVER_SOURCES} )
  target_link_libraries( tid-server ${libtid_LIBRARIES} ${SDL_LIBRARY} )
  list( APPEND T4B_BUILDLIST "TiD Server" )
  install( TARGETS tid-server
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )
endif()

if( ${BUILD_TID_CLIENT} )
  add_executable( tid-client ${CLIENT_SOURCES} )
  target_link_libraries( tid-client ${libtid_LIBRARIES} ${SDL_LIBRARY} )
  list( APPEND T4B_BUILDLIST "TiD Client" )
  install( TARGETS tid-client
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )
endif()

set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )



