
set( HWV_ROOT ${T4B_LIBBUNDLE_ROOT}/hardware_vendors )

# Default settings 
if( ${UNIX} )
  set( HAVE_brainproducts false CACHE INTERNAL "" )
  set( HAVE_dataq false CACHE INTERNAL "" )
  set( HAVE_nirscout false CACHE INTERNAL "" )
  set( HAVE_usbamp false CACHE INTERNAL "" )
  set( HAVE_plux false CACHE INTERNAL "" )
elseif( ${WIN32} )
  set( HAVE_brainproducts true CACHE INTERNAL "" )
  set( HAVE_dataq true CACHE INTERNAL "" )
  set( HAVE_nirscout true CACHE INTERNAL "" )
  set( HAVE_usbamp true CACHE INTERNAL "" )
  set( HAVE_plux true CACHE INTERNAL "" )
  list( APPEND INC_DIRS ${HWV_ROOT} )
else()
endif()

set( HW_VENDORS_INCLUDE_DIRS ${INC_DIRS} CACHE PATH "include directories for bundled hardware vendors" )
