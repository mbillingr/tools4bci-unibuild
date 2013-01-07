
set( BUNDLE_BUILD_filterTools true CACHE BOOL "(re)build the bundled library?" )


set( filterTools_ROOT ${T4B_LIBBUNDLE_ROOT}/filterTools )

set( filterTools_INCLUDE_DIR ${spuc_INCLUDE_DIRS} ${filterTools_ROOT}/include CACHE PATH "library include paths" )

if( ${BUNDLE_BUILD_filterTools} )
  add_definitions( -DFILTERTOOLS_LIBRARY )

  include_directories( 
    ${filterTools_INCLUDE_DIR}/filterTools 
    ${spuc_INCLUDE_DIRS}
    ${spuc_INCLUDE_DIRS}/spuc/generic
  )

  add_library( filterTools
    ${filterTools_ROOT}/src/iirnotch2.cpp
    ${filterTools_ROOT}/src/iirnotch.cpp
    ${filterTools_ROOT}/src/iirchebylpf.cpp
    ${filterTools_ROOT}/src/iirbutterlpf.cpp
    ${filterTools_INCLUDE_DIR}/filterTools/iirnotch2.h
    ${filterTools_INCLUDE_DIR}/filterTools/iirnotch.h
    ${filterTools_INCLUDE_DIR}/filterTools/iirchebylpf.h
    ${filterTools_INCLUDE_DIR}/filterTools/iirbutterlpf.h
    ${filterTools_INCLUDE_DIR}/filterTools/filterTools_global.h
  )

  get_target_property( loc filterTools LOCATION )
  set( filterTools_LIBRARIES ${loc} CACHE INTERNAL "" )
  
  list( APPEND T4B_BUILDLIST "filterTools" )
  set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )
endif()

