

if( ${WIN32} )
  set( HAVE_comedi false CACHE INTERNAL "" )
else()
  find_package( PkgConfig )
  pkg_search_module( comedi_tmp comedi )
  if( ${libusb_tmp_FOUND} )
    set( HAVE_comedi true CACHE INTERNAL "" )
  else()
    set( HAVE_comedi false CACHE INTERNAL "" )
  endif()
endif()

