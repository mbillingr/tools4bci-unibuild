
set( BUNDLE_USE_libgdf true CACHE BOOL "use the bundled version of the library?" )
set( BUNDLE_BUILD_libgdf true CACHE BOOL "build the library?" )

if( ${BUNDLE_BUILD_libgdf} )
  git_update( libgdf-git git://libgdf.git.sourceforge.net/gitroot/libgdf/libgdf ${CMAKE_BINARY_DIR}/extern_bundle/libgdf master )
  
  set( CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/extern_bundle/test" )
  add_subdirectory( ${CMAKE_BINARY_DIR}/extern_bundle/libgdf/libgdf ${CMAKE_BINARY_DIR}/extern_bundle/libgdf/build )
  add_dependencies( GDF libgdf-git )

  set( libgdf_INCLUDE_DIR ${CMAKE_BINARY_DIR}/extern_bundle/libgdf/libgdf/include CACHE PATH "library include paths" FORCE )
  set( libgdf_LIBRARY ${CMAKE_BINARY_DIR}/extern_bundle/libgdf/build CACHE PATH "library" FORCE )
      
  list( APPEND T4B_BUILDLIST "libGDF" )
  set( T4B_BUILDLIST ${T4B_BUILDLIST} PARENT_SCOPE )
elseif( ${BUNDLE_USE_libgdf} )
  set( libgdf_INCLUDE_DIR ${T4B_LIBBUNDLE_ROOT}/libgdf/include CACHE PATH "library include paths" FORCE )
#  set( libgdf_LIBRARY ${liblist} CACHE PATH "library search paths" FORCE )

else()
  message( "TODO: Support system's libGDF" )
endif()
