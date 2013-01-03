cmake_minimum_required( VERSION 2.8 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package( Git REQUIRED )

set( T4B_LIBBUNDLE_ROOT ${CMAKE_SOURCE_DIR}/extern CACHE PATH "Path to the tools4bci external library bundle" )

set( BUILD_SHARED_LIBS true CACHE BOOL "Shared libs or static libs..." )

include_directories( ${CMAKE_SOURCE_DIR} )

function( sysinfo )
  message( "Building platform: ${CMAKE_SYSTEM_NAME}" )
  message( "Target platform: ${CMAKE_HOST_SYSTEM_NAME}" )
  if( ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )
    set( T4B_BIT_DEPTH 32 )
  elseif( ${CMAKE_SIZEOF_VOID_P} EQUAL 8 )
    set( T4B_BIT_DEPTH 64 )
  else( )
    message( SEND_ERROR "Cannot determine bit depth from pointer size ${CMAKE_SIZEOF_VOID_P}." )
  endif( )
  message( "Bit depth: " ${T4B_BIT_DEPTH} )
endfunction( sysinfo )

function( git_update TARGET REPO DIR BRANCH )
  execute_process( 
    COMMAND ${GIT_EXECUTABLE} clone ${REPO} ${DIR}
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    WORKING_DIRECTORY ${DIR} )
  add_custom_command( 
    OUTPUT ${DIR} 
    COMMAND ${GIT_EXECUTABLE} clone ${REPO} ${DIR}
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    WORKING_DIRECTORY ${DIR} )
  add_custom_target( ${TARGET} 
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    COMMAND ${GIT_EXECUTABLE} pull 
    DEPENDS ${DIR} WORKING_DIRECTORY ${DIR} )
endfunction( git_update )

function( external_package PKGNAME )
  set( USE_BUNDLE_${PKGNAME} true CACHE BOOL "Use bundled ${PKGNAME}" )

  if( ${USE_BUNDLE_${PKGNAME}} )
    message( "Using bundled ${PKGNAME}" )
    set( ${PKGNAME}_INCLUDE_DIR "${T4B_LIBBUNDLE_ROOT}/include" CACHE PATH "${PKGNAME} include directory" )
  else()
    message( "Attempting to find ${PKGNAME}" )
    find_package( ${PKGNAME} )
  endif()
endfunction( external_package )

sysinfo( )

set( LIBTIA_ROOT ${CMAKE_BINARY_DIR}/tools4bci/libtia )
git_update( libtia-git git://git.code.sf.net/p/tools4bci/libtia/code ${LIBTIA_ROOT} master )
add_subdirectory( libtia )

set( TOBICORE_ROOT ${CMAKE_BINARY_DIR}/tools4bci/tobicore )
git_update( tobicore-git git://git.code.sf.net/p/tools4bci/tobicore/code ${TOBICORE_ROOT} msvc10_porting )
add_subdirectory( tobicore )


