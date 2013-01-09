
#set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )

find_package( Cython REQUIRED )
find_package( PythonLibs REQUIRED )
find_package( Boost REQUIRED COMPONENTS system thread )

add_custom_command(
  OUTPUT ${TOBICORE_ROOT}/python/pytid.cpp
  COMMAND ${CYTHON_EXECUTABLE} --cplus ${TOBICORE_ROOT}/python/pytid.pyx
  DEPENDS ${TOBICORE_ROOT}/python/pytid.pyx
)

include_directories(
  ${PYTHON_INCLUDE_DIRS}
  ${tid_INCLUDE_DIRS}
  ${tobiid_INCLUDE_DIR}
)

add_library( pytid MODULE ${TOBICORE_ROOT}/python/pytid.cpp )
target_link_libraries( pytid tid tobiid tobicore ${Boost_LIBRARIES} ${SDL_LIBRARY} ) 

set_target_properties( pytid PROPERTIES PREFIX "" )
