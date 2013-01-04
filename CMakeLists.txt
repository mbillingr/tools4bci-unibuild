cmake_minimum_required( VERSION 2.8 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package( Git REQUIRED )

set( T4B_LIBBUNDLE_ROOT ${CMAKE_SOURCE_DIR}/extern_bundle CACHE PATH "Path to the tools4bci external library bundle" )

set( T4B_EXTERNALS_SOURCE ${CMAKE_SOURCE_DIR}/extern CACHE PATH "Path to build files for external libraries" )
set( T4B_EXTERNALS_BINARY ${CMAKE_BINARY_DIR}/extern CACHE PATH "Where to build external libraries" )

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
    message( FATAL_ERROR "Cannot determine bit depth from pointer size ${CMAKE_SIZEOF_VOID_P}." )
  endif( )
  message( "Bit depth: " ${T4B_BIT_DEPTH} )
  
  if( ${UNIX} )
    if( ${T4B_BIT_DEPTH} EQUAL 64 )
	  set( T4B_LIBPART "linux/amd64" )
	elseif( ${T4B_BIT_DEPTH} EQUAL 32 )
	  set( T4B_LIBPART "linux/x86" )
	else()
	  message( "Library Bundle not available for your platform and bit depth." )
	endif()
  elseif( ${WIN32} )
    if( ${T4B_BIT_DEPTH} EQUAL 64 )
	  set( T4B_LIBPART "win/x64" )
	elseif( ${T4B_BIT_DEPTH} EQUAL 32 )
	  set( T4B_LIBPART "win/Win32" )
	else()
	  message( "Library Bundle not available for your platform and bit depth." )
	endif()
  else()
    message( "Library Bundle not available for your platform." )
  endif()
  
  set( T4B_LIBPART ${T4B_LIBPART} CACHE INTERNAL "" )
  message( "Bundle-libraries: ${T4B_LIBPART}" )

endfunction( sysinfo )

function( git_clone TARGET REPO DIR BRANCH )
  execute_process( COMMAND ${GIT_EXECUTABLE} clone ${REPO} ${DIR} )
  execute_process( COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}  WORKING_DIRECTORY ${DIR} )
endfunction( git_clone )

function( git_update TARGET REPO DIR BRANCH )
  git_clone( ${TARGET} ${REPO} ${DIR} ${BRANCH} )
  add_custom_command( 
    OUTPUT ${DIR} 
    COMMAND ${GIT_EXECUTABLE} clone ${REPO} ${DIR} )
  add_custom_target( ${TARGET}_CHECKOUT
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    WORKING_DIRECTORY ${DIR}
    DEPENDS ${DIR} )
  add_custom_target( ${TARGET} 
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    COMMAND ${GIT_EXECUTABLE} pull 
    DEPENDS ${TARGET}_CHECKOUT WORKING_DIRECTORY ${DIR} )
endfunction( git_update )


sysinfo( )

add_subdirectory( extern )

set( LIBTIA_ROOT ${CMAKE_BINARY_DIR}/tools4bci/libtia )
git_update( libtia-git git://git.code.sf.net/p/tools4bci/libtia/code ${LIBTIA_ROOT} master )
add_subdirectory( libtia )

set( TOBICORE_ROOT ${CMAKE_BINARY_DIR}/tools4bci/tobicore )
git_update( tobicore-git git://git.code.sf.net/p/tools4bci/tobicore/code ${TOBICORE_ROOT} msvc10_porting )
add_subdirectory( tobicore )

set( SIGSERVER_ROOT ${CMAKE_BINARY_DIR}/tools4bci/sigserver )
git_update( sigserver-git git://git.code.sf.net/p/tools4bci/sigserver/code ${SIGSERVER_ROOT} master )
add_subdirectory( sigserver )


