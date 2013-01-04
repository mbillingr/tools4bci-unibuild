set( HEADERS
	config/xml_parser.h
	config/xml_tags.h
	hardware/hw_access.h
	hardware/hw_thread.h
	hardware/sine_generator.h
	hardware/jstick.h
	hardware/serial_port_base.h
	hardware/g_mobilab.h
	hardware/hw_thread_factory.h
	hardware/hw_thread_builder.h
	sampleblock/sample_block.h
	hardware/artificial_signal_source.h
	hardware/eeg_simulator.h
	hardware/mouse.h
	hardware/eeg_sim_msg_parser.h
	signalserver/signalserver.h
	hardware/gBSamp_base.h
	filewriter/file_writer.h
	filewriter/file_writer_data_types.h
	filewriter/file_writer_impl_base.h
	filewriter/gdf_writer_impl.h
#	hardware/keylogger_base.h
#	hardware/event_listener.h
)

if( ${UNIX} )
  set( HEADERS ${HEADERS}
	hardware/nidaqmx_wrapper.h
#	hardware/keylogger_linux.h
  )
endif( )

if( ${WIN32} )
  set( HEADERS ${HEADERS}
	hardware/brainampseries.h
	hardware/gtec_usbamp_wrapper.h
	hardware/usbamp.h
	hardware/dataq_wrapper.h
	hardware/dataq.h
	hardware/nirscout.h
	hardware/plux.h
#	hardware/keylogger_win.h
  )
endif( )


set( SOURCES
	signalserver/main.cpp
	config/xml_parser.cpp
	hardware/hw_access.cpp
	hardware/hw_thread.cpp
	hardware/sine_generator.cpp
	hardware/jstick.cpp
	hardware/serial_port_base.cpp
	hardware/g_mobilab.cpp
	hardware/hw_thread_factory.cpp
	sampleblock/sample_block.cpp
	hardware/artificial_signal_source.cpp
	hardware/eeg_simulator.cpp
	hardware/mouse.cpp
	hardware/eeg_sim_msg_parser.cpp
	signalserver/signalserver.cpp
	hardware/gBSamp_base.cpp
	filewriter/file_writer.cpp
	filewriter/file_writer_impl_base.cpp
	filewriter/gdf_writer_impl.cpp
#	hardware/keylogger_base.cpp
#	hardware/event_listener.cpp
)

#if( ${UNIX} )
#  set( SOURCES ${SOURCES}	
#	hardware/keylogger_linux.cpp
#  )
#endif( )

if( ${WIN32} )
  set( SOURCES ${SOURCES}
	hardware/brainampseries.cpp
	hardware/usbamp.cpp
	hardware/dataq.cpp
	hardware/nirscout.cpp
	hardware/plux.cpp
#	hardware/keylogger_win.cpp
  )
endif( )

if( ${SIGSERVER_BUILD_MOUSE} )
  if( ${UNIX} )
    set( HEADERS ${HEADERS} hardware/mouse_linux.h )
    set( SOURCES ${SOURCES} hardware/mouse_linux.cpp )
  endif()
  if( ${WIN32} )
    set( HEADERS ${HEADERS} hardware/mouse_win.h )
    set( SOURCES ${SOURCES} hardware/mouse_win.cpp )
  endif()
endif()

if( ${SIGSERVER_BUILD_GBSAMP} )
  if( ${UNIX} )
    set( HEADERS ${HEADERS} hardware/gBSamp_unix.h )
    set( SOURCES ${SOURCES} hardware/gBSamp_unix.cpp )
  endif()
  if( ${WIN32} )
    set( HEADERS ${HEADERS} hardware/gBSamp_win.h )
    set( SOURCES ${SOURCES} hardware/gBSamp_win.cpp )
  endif()
endif()

if( ${SIGSERVER_BUILD_KINECT} )
  set( HEADERS ${HEADERS} hardware/kinect.h )
  set( SOURCES ${SOURCES} hardware/kinect.cpp )
endif()


# add full path to sources and headers

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${SIGSERVER_ROOT}/include/${hdr}" )
endforeach( hdr )

foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${SIGSERVER_ROOT}/src/${src}" )
endforeach( src )


# add LptTools for timing tests if configured

if( ${CONFIG_TIMING_TEST} )
  set( FULL_HEADERS ${FULL_HEADERS} ${SIGSERVER_ROOT}/extern/include/LptTools/LptTools.h )
  if( ${UNIX} )
    set( FULL_SOURCES ${FULL_SOURCES} ${SIGSERVER_ROOT}/extern/include/LptTools/LptToolsLinux.cpp )
  endif()
  if( ${WIN32} )
    set( FULL_SOURCES ${FULL_SOURCES} ${SIGSERVER_ROOT}/extern/include/LptTools/LptTools_.cpp )
  endif()
endif()


# export source files to parent scope
set( HEADERS ${FULL_HEADERS} PARENT_SCOPE )
set( SOURCES ${FULL_SOURCES} PARENT_SCOPE )

