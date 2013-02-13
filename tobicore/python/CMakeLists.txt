
#set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )

find_package( Boost REQUIRED COMPONENTS system thread date_time regex chrono )

find_package( Cython REQUIRED )
find_package( PythonLibs REQUIRED )

if( WIN32 )
  get_filename_component( CYX ${CYTHON_EXECUTABLE} PROGRAM PROGRAM_ARGS CYARG )
  string( STRIP ${CYARG} CYARG )
else()
  set( CYX ${CYTHON_EXECUTABLE} )
endif()

message( "${CYX} ${CYARG} --cplus ${TOBICORE_ROOT}/python/pytid.pyx")

add_custom_command(
  OUTPUT ${TOBICORE_ROOT}/python/pytid.cpp
  COMMAND ${CYX} ${CYARG} --cplus ${TOBICORE_ROOT}/python/pytid.pyx
  DEPENDS ${TOBICORE_ROOT}/python/pytid.pyx
)

include_directories(
  ${Boost_INCLUDE_DIR}
  ${PYTHON_INCLUDE_DIRS}
  ${tid_INCLUDE_DIRS}
  ${tobiid_INCLUDE_DIR}
)

add_library( pytid MODULE ${TOBICORE_ROOT}/python/pytid.cpp )
target_link_libraries( pytid tid tobiid tobicore ${Boost_LIBRARIES} ${SDL_LIBRARY} ${PYTHON_LIBRARY} ) 

set_target_properties( pytid PROPERTIES PREFIX "" )

install( TARGETS pytid
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
