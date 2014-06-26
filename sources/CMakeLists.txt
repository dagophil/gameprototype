CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
 
PROJECT(GameProject)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET(CMAKE_CXX_WARNING_LEVEL 4)
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_MODULE_PATH /usr/share/cmake/Modules/ )
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Modules" ${CMAKE_MODULE_PATH})

# Additions for Bullet
IF(WIN32)
  SET(BULLET_ROOT "C:\lib_x86\bullet-2.81-rev2613")
ENDIF(WIN32)
FIND_PACKAGE(Bullet)

IF(NOT BULLET_FOUND)
  MESSAGE(FATAL_ERROR "Bullet libraries not found. Please set the library manually..." )
ENDIF()


INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIR})
LINK_LIBRARIES(${BULLET_LIBRARIES})


#find_package(Boost 1.54.0 COMPONENTS *boost libraries here*)
find_package(Boost 1.54.0 COMPONENTS system)
IF(Boost_FOUND)
    LINK_LIBRARIES(${Boost_LIBRARIES})
ENDIF()


IF(WIN32)
	SET(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	SET(OGRE_SAMPLES_INCLUDEPATH $ENV{OGRE_HOME}/Samples/include)
ENDIF(WIN32)
 
IF(UNIX)
	IF(EXISTS "/usr/local/lib/OGRE/cmake")
	  SET(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
    SET(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	ELSEIF(EXISTS "/usr/lib/OGRE/cmake")
	  SET(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  SET(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

  ELSE()
	  MESSAGE(SEND_ERROR "Failed to find module path.")
    ENDIF(EXISTS "/usr/local/lib/OGRE/cmake")
ENDIF(UNIX)
 
IF (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release ." FORCE)
ENDIF ()
 
 
SET(CMAKE_DEBUG_POSTFIX "_d")
SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

FIND_PACKAGE(OGRE REQUIRED Overlay)
 
IF(OGRE_FOUND)
  IF(WIN32)
    # Ogree needs this but don't know about it - bad configuration files...
    SET(BOOST_INCLUDEDIR $ENV{OGRE_HOME}/boost )
    SET(BOOST_LIBRARYDIR $ENV{OGRE_HOME}/boost/lib )
    SET(Boost_USE_STATIC_LIBS true)
    FIND_PACKAGE(Boost COMPONENTS thread date_time)

    IF((NOT Boost_THREAD_FOUND) OR (NOT Boost_DATE_TIME_FOUND))
      MESSAGE(FATAL_ERROR "Boost libraries not found. Please set the library manually..." )
    ENDIF()

    SET(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
    SET(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
  ENDIF()
ENDIF()


FIND_PACKAGE(OIS REQUIRED)

IF(NOT OIS_FOUND)
  MESSAGE(SEND_ERROR "Failed to find OIS.")
ENDIF()


# Set all source files

SET(SRCS
	./BaseApplication.cpp
	./TopManager.cpp
	./GraphicManager.cpp
	./PhysicsManager.cpp
	./InputManager.cpp
	./Keyboard.cpp
	./MeshStrider.cpp
	./MotionState.cpp
	./Map.cpp
	./Player.cpp
	./GameObject.cpp
	./GameMovableObject.cpp
	./Vehicle.cpp
	./GameMapObject.cpp
	./PlayerInput.cpp
	./GameOverlayManager.cpp
	./DebugDrawer.cpp
	./Upgrade.cpp
	./Graph.cpp
	./PointReader.cpp
	./AStar.cpp
	./SortedList.cpp
	./main.cpp	
)

SOURCE_GROUP ("sources" FILES ${SRCS})

SET(HDRS
	./BaseApplication.h
	./TopManager.h
	./GraphicManager.h
	./PhysicsManager.h
	./InputManager.h
	./Keyboard.h
	./MeshStrider.h
	./MotionState.h
	./Map.h
	./Player.h
	./GameObject.h
	./GameMovableObject.h
	./Vehicle.h
	./GameMapObject.h
	./PlayerInput.h
	./GameOverlayManager.h
	./DebugDrawer.h
	./PointReader.h
	./AStar.h
	./SortedList.h
	./Graph.h
	./Upgrade.h
)

SOURCE_GROUP ("headers" FILES ${HDRS})
 
INCLUDE_DIRECTORIES( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${BULLET_INCLUDE_DIRS}
)
 
LINK_LIBRARIES( ${OGRE_LIBRARIES} )

ADD_EXECUTABLE(GameProject ${SRCS} ${HDRS})
 
SET_TARGET_PROPERTIES(GameProject PROPERTIES DEBUG_POSTFIX _d)
 
TARGET_LINK_LIBRARIES(GameProject ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${BULLET_LIBRARIES} ${OPENAL_LIBRARIES} ${Boost_LIBRARIES} )

 
IF(WIN32)
 
	INSTALL(TARGETS GameProject
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	INSTALL(FILES ${CMAKE_SOURCE_DIR}/../dist/bin/win32/plugins.cfg
		${CMAKE_SOURCE_DIR}/../dist/bin/resources.cfg
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints.txt
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints1.txt
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	INSTALL(FILES ${CMAKE_SOURCE_DIR}/../dist/bin/win32/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/../dist/bin/resources_d.cfg
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints.txt
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints1.txt
		DESTINATION ./
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	INSTALL(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
    ${OGRE_PLUGIN_DIR_REL}/OIS.dll
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	INSTALL(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
    ${OGRE_PLUGIN_DIR_DBG}/OIS_d.dll
		DESTINATION ./
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   INSTALL(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION ./
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   INSTALL(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION ./
      CONFIGURATIONS Debug
   )
ENDIF(WIN32)

IF(UNIX)
	INSTALL(TARGETS GameProject
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
  INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../dist/media
    DESTINATION ./
    CONFIGURATIONS Release Debug
  )
 
  INSTALL(FILES ${CMAKE_SOURCE_DIR}/../dist/bin/linux/plugins.cfg
    ${CMAKE_SOURCE_DIR}/../dist/bin/linux/plugins.cfg
    ${CMAKE_SOURCE_DIR}/../dist/bin/resources.cfg
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints.txt
		${CMAKE_SOURCE_DIR}/../dist/bin/waypoints1.txt
    DESTINATION ./
    CONFIGURATIONS Release Debug
  )
ENDIF(UNIX)

IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  MESSAGE("CREATING DEBUG BUILD")
ELSE()
  MESSAGE("CREATING RELEASE BUILD")
ENDIF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
