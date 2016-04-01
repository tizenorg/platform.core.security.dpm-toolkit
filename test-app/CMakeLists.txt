CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(org.tizen.dpm-toolkit-app C)

INCLUDE_DIRECTORIES(./include)


#INCLUDE(FindPkgConfig)
#IF (with_x)
#	FIND_PACKAGE(PkgConfig REQUIRED)
#	PKG_CHECK_MODULES(test_pkgs REQUIRED ${PKG_LIST} x11)
#ENDIF (with_x)	IIIF (with_wayland)

#SET(PKG_LIST "dlog elementary efl-extension capi-appfw-application appcore-common appcore-efl ug-gadget-1 aul evas notification ecore libtzplatform-config")
	#FIND_PACKAGE(PkgConfig REQUIRED)
#	INCLUDE(FindPkgConfig)
#	PKG_CHECK_MODULES(test_pkgs REQUIRED ${PKG_LIST})

IF (with_wayland)
        ADD_DEFINITIONS("-DUG_WAYLAND")
        SET(UG_FLAG "-DUG_WAYLAND")
ENDIF (with_wayland)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(test_pkgs REQUIRED
	dlog
	glib-2.0
	efl-extension
	elementary
	capi-appfw-application
	libxml-2.0
	capi-system-system-settings
)


INCLUDE_DIRECTORIES(${test_pkgs_INCLUDE_DIRS})
LINK_DIRECTORIES(${test_pkgs_LIBRARY_DIRS})
#TARGET_LINK_LIBRARIES(${PKG_NAME} ${PKG_LDFLAGS} -ldl)


SET(PKG_NAME "${PROJECT_NAME}")
SET(PKG_SRCS ./src/dpm-toolkit.c
			 ./src/password.c
			 ./src/security.c
			 ./src/wifi.c)


SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")

ADD_EXECUTABLE(${PKG_NAME} ${PKG_SRCS})
INSTALL(TARGETS ${PKG_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/${PKG_NAME}/bin)

TARGET_LINK_LIBRARIES(${PKG_NAME} ${test_pkgs_LIBRARIES})

#Install app data
INSTALL(FILES res/${PKG_NAME}.png DESTINATION ${CMAKE_DESKTOP_ICON_DIR})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PKG_NAME}.xml DESTINATION ${CMAKE_APP_SHARE_PACKAGES_DIR})
INSTALL(FILES data/test.xml DESTINATION ${CMAKE_INSTALL_PREFIX}/${PKG_NAME})


