project( signalserver )

configure_libtia()

external_package( ticpp )

include_directories(
  ${SIGSERVER_ROOT}/include
  ${ticpp_INCLUDE_DIR}
)

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
	hardware/kinect.h
	filewriter/file_writer.h
	filewriter/file_writer_data_types.h
	filewriter/file_writer_impl_base.h
	filewriter/gdf_writer_impl.h
)

set( SOURCES
	signalserver/main.cpp
)

foreach( hdr ${HEADERS} )
  set( FULL_HEADERS ${FULL_HEADERS} "${SIGSERVER_ROOT}/include/${hdr}" )
endforeach( hdr )

foreach( src ${SOURCES} )
  set( FULL_SOURCES ${FULL_SOURCES} "${SIGSERVER_ROOT}/src/${src}" )
endforeach( src )

add_executable( signalserver ${FULL_HEADERS} ${FULL_SOURCES} )
