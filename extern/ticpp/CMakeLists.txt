
set( BUNDLE_BUILD_ticpp true CACHE BOOL "(re)build the bundled library?" )

set( ticpp_ROOT ${T4B_LIBBUNDLE_ROOT}/ticpp )

set( ticpp_INCLUDE_DIR ${ticpp_ROOT}/include CACHE PATH "library include paths" )

if( ${BUNDLE_BUILD_ticpp} )
  add_definitions( -DTIXML_USE_TICPP )
  include_directories( ${ticpp_INCLUDE_DIR}/ticpp )
  add_library( ticpp
    ${ticpp_ROOT}/src/ticpp.cpp
    ${ticpp_ROOT}/src/tinystr.cpp
    ${ticpp_ROOT}/src/tinyxml.cpp
    ${ticpp_ROOT}/src/tinyxmlerror.cpp
    ${ticpp_ROOT}/src/tinyxmlparser.cpp
  )

  get_target_property( loc ticpp LOCATION )
  set( ticpp_LIBRARIES ${loc} CACHE INTERNAL "" )
endif()

