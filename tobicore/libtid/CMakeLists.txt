
external_package( SDL )

find_package( Boost REQUIRED COMPONENTS system thread )

set( LIBTID_INCLUDE_DIRS 
  ${TOBICORE_ROOT}/src/libtid
  ${Boost_INCLUDE_DIR}
)

include_directories( ${LIBTID_INCLUDE_DIRS} )

set( HEADERS
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

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${TOBICORE_ROOT}/src/libtid/${hdr}" )
endforeach( hdr )

add_library( tid ${FULL_HEADERS} ${FULL_SOURCES} )
add_dependencies( tid tobicore-git )

set( LIBTID_LIBRARIES tid tobiid tobicore ${Boost_LIBRARIES} ${SDL_LIBRARY} )

set( BUILD_TID_SERVER true CACHE BOOL "build TiD Server?" )
set( BUILD_TID_CLIENT true CACHE BOOL "build TiD Client?" )

if( ${BUILD_TID_SERVER} )
  add_executable( tid-server ${SERVER_SOURCES} )
  target_link_libraries( tid-server ${LIBTID_LIBRARIES} )
endif()

if( ${BUILD_TID_CLIENT} )
  add_executable( tid-client ${CLIENT_SOURCES} )
  target_link_libraries( tid-client ${LIBTID_LIBRARIES} )
endif()
