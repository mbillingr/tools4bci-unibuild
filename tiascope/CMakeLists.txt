project( TiAscope )

# ============================

configure_libtia()

add_definitions( -DTIA_BRUTEFORCE_SIGNALHACK )

find_package( Boost REQUIRED COMPONENTS system thread )

set( QT_USE_IMPORTED_TARGETS true )
set( QT_USE_QTNETWORK true )
#set( QT_USE_QTOPENGL true )
#set( QT_USE_QTSQL true )
set( QT_USE_QTXML true )
#set( QT_USE_QTTEST true )
#set( QT_USE_QTDBUS true )
#set( QT_USE_QTSCRIPT true )
#set( QT_USE_QTWEBKIT true )
#set( QT_USE_QTXMLPATTERNS true )
#set( QT_USE_PHONON true )
find_package( Qt4 REQUIRED )

set( HEADERS
  ${TIASCOPE_ROOT}/src/main_window.h

  ${TIASCOPE_ROOT}/src/base/data_buffer.h
  ${TIASCOPE_ROOT}/src/base/signal_view_settings.h
  ${TIASCOPE_ROOT}/src/base/FFTReal.h
  ${TIASCOPE_ROOT}/src/base/helpers.h
  ${TIASCOPE_ROOT}/src/base/user_types.h
  ${TIASCOPE_ROOT}/src/base/ft_view_settings.h

  ${TIASCOPE_ROOT}/src/config_widget/signal_info_dock_widget.h
  ${TIASCOPE_ROOT}/src/config_widget/subject_info_dock_widget.h
  ${TIASCOPE_ROOT}/src/config_widget/view_settings_dock_widget.h
  ${TIASCOPE_ROOT}/src/config_widget/application_monitor_dock_widget.h
  ${TIASCOPE_ROOT}/src/config_widget/filter_dockwidget.h
  ${TIASCOPE_ROOT}/src/config_widget/signal_properties_dock_widget.h
  ${TIASCOPE_ROOT}/src/config_widget/signal_presentation_dock_widget.h

  ${TIASCOPE_ROOT}/src/connection_widget/connect_dialog.h
  ${TIASCOPE_ROOT}/src/connection_widget/welcome_widget.h
  ${TIASCOPE_ROOT}/src/connection_widget/customize_signalinfo_dialog.h

  ${TIASCOPE_ROOT}/src/data_collector/reader_thread.h
  ${TIASCOPE_ROOT}/src/data_collector/fourier_transform_thread.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/qt_tia_client.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_client_version02.h
  ${TIASCOPE_ROOT}/src/data_collector/filters.h
  ${TIASCOPE_ROOT}/src/data_collector/filters/filter.h
  ${TIASCOPE_ROOT}/src/data_collector/filters/butterworth_filter.h  
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/datapacket.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_datapacket_version2.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/tia_exception.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_control_message.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/data_receive_blocker.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/line_receive_blocker.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_datapacket_basedlibtia.h
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_client_based_libtia.h

  ${TIASCOPE_ROOT}/src/visualisation/channel_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/signal_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/frequency_spectrum_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/signal_graphics_scene.h
  ${TIASCOPE_ROOT}/src/visualisation/base_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/button_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/base_signal_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/aperiodic_data_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/joystick_graphics_object.h
  ${TIASCOPE_ROOT}/src/visualisation/signal_graphics_view.h
)

set( SOURCES
  ${TIASCOPE_ROOT}/src/main.cpp
  ${TIASCOPE_ROOT}/src/main_window.cpp
  
  ${TIASCOPE_ROOT}/src/base/data_buffer.cpp
  ${TIASCOPE_ROOT}/src/base/signal_view_settings.cpp
  ${TIASCOPE_ROOT}/src/base/FFTReal.cpp
  ${TIASCOPE_ROOT}/src/base/helpers.cpp
  ${TIASCOPE_ROOT}/src/base/user_types.cpp
  ${TIASCOPE_ROOT}/src/base/ft_view_settings.cpp

  ${TIASCOPE_ROOT}/src/config_widget/signal_info_dock_widget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/subject_info_dock_widget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/view_settings_dock_widget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/application_monitor_dock_widget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/filter_dockwidget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/signal_info_utils.cpp
  ${TIASCOPE_ROOT}/src/config_widget/signal_properties_dock_widget.cpp
  ${TIASCOPE_ROOT}/src/config_widget/signal_presentation_dock_widget.cpp

  ${TIASCOPE_ROOT}/src/connection_widget/connect_dialog.cpp
  ${TIASCOPE_ROOT}/src/connection_widget/welcome_widget.cpp
  ${TIASCOPE_ROOT}/src/connection_widget/customize_signalinfo_dialog.cpp

  ${TIASCOPE_ROOT}/src/data_collector/reader_thread.cpp
  ${TIASCOPE_ROOT}/src/data_collector/fourier_transform_thread.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/qt_tia_client.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_client_version02.cpp
  ${TIASCOPE_ROOT}/src/data_collector/filters.cpp
  ${TIASCOPE_ROOT}/src/data_collector/filters/butterworth_filter.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/qt_tia_client.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_client_version02.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_datapacket_version2.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/data_receive_blocker.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/line_receive_blocker.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_datapacket_basedlibtia.cpp
  ${TIASCOPE_ROOT}/src/data_collector/qt_tia_client/impl/tia_client_based_libtia.cpp

  ${TIASCOPE_ROOT}/src/visualisation/channel_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/signal_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/frequency_spectrum_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/signal_graphics_scene.cpp
  ${TIASCOPE_ROOT}/src/visualisation/button_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/aperiodic_data_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/joystick_graphics_object.cpp
  ${TIASCOPE_ROOT}/src/visualisation/base_graphics_object.cpp
)

set( FORMS
  ${TIASCOPE_ROOT}/src/main_window.ui

  ${TIASCOPE_ROOT}/src/config_widget/signal_info_dock_widget.ui
  ${TIASCOPE_ROOT}/src/config_widget/subject_info_dock_widget.ui
  ${TIASCOPE_ROOT}/src/config_widget/view_settings_dock_widget.ui
  ${TIASCOPE_ROOT}/src/config_widget/application_monitor_dock_widget.ui
  ${TIASCOPE_ROOT}/src/config_widget/filter_dockwidget.ui
  ${TIASCOPE_ROOT}/src/config_widget/signal_properties_dock_widget.ui
  ${TIASCOPE_ROOT}/src/config_widget/signal_presentation_dock_widget.ui

  ${TIASCOPE_ROOT}/src/connection_widget/connect_dialog.ui
  ${TIASCOPE_ROOT}/src/connection_widget/connect_wizard.ui
  ${TIASCOPE_ROOT}/src/connection_widget/welcome_widget.ui
  ${TIASCOPE_ROOT}/src/connection_widget/customize_signalinfo_dialog.ui
)

set( RESOURCES
  ${TIASCOPE_ROOT}/resources.qrc
)

qt4_wrap_ui( FORMS_HEADERS ${FORMS} )
qt4_wrap_cpp( HEADERS_MOC ${HEADERS} )
qt4_add_resources( RESOURCES_RCC ${RESOURCES} )

include( ${QT_USE_FILE} )

include_directories( 
  ${CMAKE_CURRENT_BINARY_DIR}
  ${libtia_INCLUDE_DIRS}
  ${TIASCOPE_ROOT}/src
  ${TIASCOPE_ROOT}/external/include
  ${Boost_INCLUDE_DIR}
)

link_directories( ${Boost_LIBRARY_DIRS} )

add_executable( tiascope ${SOURCES} ${HEADERS_MOC} ${FORMS_HEADERS} ${RESOURCES_RCC} )
target_link_libraries( tiascope tia ticpp ${QT_LIBRARIES} ${Boost_LIBRARIES} )
add_dependencies( tiascope tiascope-git libtia )


install( TARGETS tiascope
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

if( WIN32 )
	foreach( qlib IN LISTS QT_LIBRARIES )
		string( REPLACE "Qt4::" "" qlib ${qlib} )
		message( ${qlib} )
		install( FILES ${QT_BINARY_DIR}/${qlib}4.dll DESTINATION bin
		)
	endforeach()
endif()