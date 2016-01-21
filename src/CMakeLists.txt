project(squid-gui)

cmake_minimum_required(VERSION 2.6)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )


if(WIN32)
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -mwindows -fPIC" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -fPIC" )
ENDIF()

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} 
		    ${Qt5Core_INCLUDE_DIRS})
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)

set(squid-gui "squid-gui")

set(squid-gui_includes
${CMAKE_BINARY_DIR}/src
)

include_directories(${squid-gui_includes})

set(squid-gui_moc_hdrs 
	about.h
	dansguardian_config.h
	mainwindow.h
	defines.h
	settingsmanager.h
	squid_config.h
	status_service.h
)


qt5_wrap_cpp(squid-gui_mocs ${squid-gui_moc_hdrs})


set(squid-gui_uis 
	gui/about.ui
	gui/mainwindow.ui
	gui/status_service.ui
)

qt5_wrap_ui(squid-gui_ui_hdrs ${squid-gui_uis})


set(squid-gui_srcs 
	about.cpp
	dansguardian_config.cpp
	mainwindow.cpp
	squid_config.cpp
	status_service.cpp
	settingsmanager.cpp
	main.cpp
)


qt5_add_resources(RESOURCE_FILES images.qrc lang.qrc) 


LINK_LIBRARIES(-lpthread)


ADD_EXECUTABLE(squid-gui ${squid-gui_srcs} ${squid-gui_mocs} ${squid-gui_ui_hdrs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})


target_link_libraries( squid-gui
  Qt5::Widgets Qt5::Gui 
  Qt5::Core 
)


if(SQUID_GUI_BUILD_LINUX)
    INSTALL( TARGETS squid-gui RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
    INSTALL( FILES "desktop/squid-gui.desktop" DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications )
    INSTALL( FILES "images/logo_ico.png" DESTINATION ${CMAKE_INSTALL_PREFIX}/share/squid-gui )
    INSTALL( FILES "policy/com.github.kratos83.squid-gui.policy" DESTINATION ${CMAKE_INSTALL_PREFIX}/share/polkit-1/actions )
    INSTALL( FILES ${CMAKE_CURRENT_BINARY_DIR}/policy/squid-gui_polkit DESTINATION ${CMAKE_INSTALL_PREFIX}/bin 
	     PERMISSIONS
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_EXECUTE
		WORLD_READ WORLD_EXECUTE)    
elseif(SQUID_GUI_BUILD_FREEBSD)
endif()
