
set( BUNDLE_USE_ticpp true CACHE BOOL "use the bundled version of the library?" )
set( BUNDLE_BUILD_ticpp true CACHE BOOL "(re)build the bundled library?" )

if( NOT ${BUNDLE_USE_ticpp} )
  message( FATAL_ERROR "Must use bundled ticpp." )
endif()

set( ticpp_INCLUDE_DIR ${T4B_LIBBUNDLE_ROOT}/include CACHE PATH "library include paths" )

if( ${BUNDLE_BUILD_ticpp} )
  add_definitions( -DTIXML_USE_TICPP )
  add_library( ticpp
    ${ticpp_INCLUDE_DIR}/ticpp/ticpp.cpp
    ${ticpp_INCLUDE_DIR}/ticpp/tinystr.cpp
    ${ticpp_INCLUDE_DIR}/ticpp/tinyxml.cpp
    ${ticpp_INCLUDE_DIR}/ticpp/tinyxmlerror.cpp
    ${ticpp_INCLUDE_DIR}/ticpp/tinyxmlparser.cpp
  )

  get_target_property( loc ticpp LOCATION )
  set( ticpp_LIBRARIES ${loc} CACHE INTERNAL "" )
endif()

