cmake_minimum_required( VERSION 2.8 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package( Git REQUIRED )

set( T4B_LIBBUNDLE_ROOT ${CMAKE_SOURCE_DIR}/extern_bundle CACHE PATH "Path to the tools4bci external library bundle" )

set( T4B_EXTERNALS_SOURCE ${CMAKE_SOURCE_DIR}/extern CACHE PATH "Path to build files for external libraries" )
set( T4B_EXTERNALS_BINARY ${CMAKE_BINARY_DIR}/extern CACHE PATH "Where to build external libraries" )

if( ${UNIX} )
  set( BUILD_SHARED_LIBS true CACHE BOOL "Shared libs or static libs..." )
  set( BUILD_SIGSERVER true CACHE BOOL "" )
  set( BUILD_TIASCOPE true CACHE BOOL "" )
else()
  set( BUILD_SHARED_LIBS false CACHE BOOL "Shared libs or static libs..." )
  set( BUILD_SIGSERVER true CACHE BOOL "" )
  set( BUILD_TIASCOPE false CACHE BOOL "" )
endif()

if( ${WIN32} )
	set( Boost_USE_STATIC_LIBS true CACHE BOOL "" )
endif()

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
    COMMAND ${GIT_EXECUTABLE} pull 
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    WORKING_DIRECTORY ${DIR}
    DEPENDS ${DIR} )
  add_custom_target( ${TARGET} 
    COMMAND ${GIT_EXECUTABLE} pull 
    COMMAND ${GIT_EXECUTABLE} checkout ${BRANCH}
    DEPENDS ${TARGET}_CHECKOUT WORKING_DIRECTORY ${DIR} )
endfunction( git_update )


sysinfo( )

if( ${BUILD_SHARED_LIBS} )
  list( APPEND T4B_BUILDLIST "shared libraries..." )
else()
  list( APPEND T4B_BUILDLIST "static libraries..." )
endif()

####################################################################################ü

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

####################################################################################ü

add_subdirectory( extern )

set( LIBTIA_ROOT ${CMAKE_BINARY_DIR}/tools4bci/libtia )
git_update( libtia-git git://git.code.sf.net/p/tools4bci/libtia/code ${LIBTIA_ROOT} master )
add_subdirectory( libtia )

set( TOBICORE_ROOT ${CMAKE_BINARY_DIR}/tools4bci/tobicore )
git_update( tobicore-git git://git.code.sf.net/p/tools4bci/tobicore/code ${TOBICORE_ROOT} msvc10_porting )
add_subdirectory( tobicore )

if( ${BUILD_SIGSERVER} )
  set( SIGSERVER_ROOT ${CMAKE_BINARY_DIR}/tools4bci/sigserver )
  git_update( sigserver-git git://git.code.sf.net/p/tools4bci/sigserver/code ${SIGSERVER_ROOT} unibuild )
  add_subdirectory( sigserver )
endif()

if( ${BUILD_TIASCOPE} )
  set( TIASCOPE_ROOT ${CMAKE_BINARY_DIR}/tools4bci/tiascope )
  git_update( tiascope-git git://git.code.sf.net/p/tools4bci/tiascope/code ${TIASCOPE_ROOT} master )
  add_subdirectory( tiascope )
endif()
  
foreach( item IN LISTS T4B_BUILDLIST )
  message( "Building ${item}" )
endforeach()

