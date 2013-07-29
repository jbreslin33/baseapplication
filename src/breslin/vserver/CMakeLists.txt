cmake_minimum_required(VERSION 2.6)
 
project(Server)
 
	set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		/usr/local/share/OGRE/samples/Common/include/
	)

set(PostgreSQL_INCLUDE_PATH_DESCRIPTION "top-level directory containing the PostgreSQL include directories. E.g /usr/local/include/PostgreSQL/8.4 or C:/Program Files/PostgreSQL/8.4/include")
set(PostgreSQL_INCLUDE_DIR_MESSAGE "Set the PostgreSQL_INCLUDE_DIR cmake cache entry to the ${PostgreSQL_INCLUDE_PATH_DESCRIPTION}")
set(PostgreSQL_LIBRARY_PATH_DESCRIPTION "top-level directory containing the PostgreSQL libraries.")
set(PostgreSQL_LIBRARY_DIR_MESSAGE "Set the PostgreSQL_LIBRARY_DIR cmake cache entry to the ${PostgreSQL_LIBRARY_PATH_DESCRIPTION}")
set(PostgreSQL_ROOT_DIR_MESSAGE "Set the PostgreSQL_ROOT system variable to where PostgreSQL is found on the machine E.g C:/Program Files/PostgreSQL/8.4")


set(PostgreSQL_KNOWN_VERSIONS ${PostgreSQL_ADDITIONAL_VERSIONS}
    "9.1" "9.0" "8.4" "8.3" "8.2" "8.1" "8.0")

# Define additional search paths for root directories.
set( PostgreSQL_ROOT_DIRECTORIES
   ENV PostgreSQL_ROOT
   ${PostgreSQL_ROOT}
   ${PostgreSQL_ADDITIONAL_SEARCH_PATHS}
)

find_path(PostgreSQL_INCLUDE_DIR
  NAMES libpq-fe.h
  PATHS
   # Look in other places.
   ${PostgreSQL_ROOT_DIRECTORIES}
  PATH_SUFFIXES
    pgsql
    postgresql
    include
  # Help the user find it if we cannot.
  DOC "The ${PostgreSQL_INCLUDE_DIR_MESSAGE}"
)

find_path(PostgreSQL_TYPE_INCLUDE_DIR
  NAMES catalog/pg_type.h
  PATHS
   # Look in other places.
   ${PostgreSQL_ROOT_DIRECTORIES}
  PATH_SUFFIXES
    postgresql
    pgsql/server
    postgresql/server
    include/server
  # Help the user find it if we cannot.
  DOC "The ${PostgreSQL_INCLUDE_DIR_MESSAGE}"
)

# The PostgreSQL library.
set (PostgreSQL_LIBRARY_TO_FIND pq)
# Setting some more prefixes for the library
set (PostgreSQL_LIB_PREFIX "")
if ( WIN32 )
  set (PostgreSQL_LIB_PREFIX ${PostgreSQL_LIB_PREFIX} "lib")
  set ( PostgreSQL_LIBRARY_TO_FIND ${PostgreSQL_LIB_PREFIX}${PostgreSQL_LIBRARY_TO_FIND})
endif()

find_library( PostgreSQL_LIBRARY
 NAMES ${PostgreSQL_LIBRARY_TO_FIND}
 PATHS
   ${PostgreSQL_ROOT_DIRECTORIES}
 PATH_SUFFIXES
   lib
)
get_filename_component(PostgreSQL_LIBRARY_DIR ${PostgreSQL_LIBRARY} PATH)

if (PostgreSQL_INCLUDE_DIR AND EXISTS "${PostgreSQL_INCLUDE_DIR}/pg_config.h")
  file(STRINGS "${PostgreSQL_INCLUDE_DIR}/pg_config.h" pgsql_version_str
       REGEX "^#define[\t ]+PG_VERSION[\t ]+\".*\"")

  string(REGEX REPLACE "^#define[\t ]+PG_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
         PostgreSQL_VERSION_STRING "${pgsql_version_str}")
  unset(pgsql_version_str)
endif()

# Did we find anything?
#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
#find_package_handle_standard_args(PostgreSQL
##                                  REQUIRED_VARS PostgreSQL_LIBRARY PostgreSQL_INCLUDE_DIR PostgreSQL_TYPE_INCLUDE_DIR
#                                  VERSION_VAR PostgreSQL_VERSION_STRING)
set( PostgreSQL_FOUND  ${POSTGRESQL_FOUND})

# Now try to get the include and library path.
if(PostgreSQL_FOUND)

  set(PostgreSQL_INCLUDE_DIRS ${PostgreSQL_INCLUDE_DIR} ${PostgreSQL_TYPE_INCLUDE_DIR} )
  set(PostgreSQL_LIBRARY_DIRS ${PostgreSQL_LIBRARY_DIR} )
  set(PostgreSQL_LIBRARIES ${PostgreSQL_LIBRARY_TO_FIND})

  #message("Final PostgreSQL include dir: ${PostgreSQL_INCLUDE_DIRS}")
  #message("Final PostgreSQL library dir: ${PostgreSQL_LIBRARY_DIRS}")
  #message("Final PostgreSQL libraries:   ${PostgreSQL_LIBRARIES}")
endif()

mark_as_advanced(PostgreSQL_INCLUDE_DIR PostgreSQL_TYPE_INCLUDE_DIR PostgreSQL_LIBRARY )

#END POSTGRES

# link the libraries to the executable
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
 
find_package(OGRE REQUIRED)
 
if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
  message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
endif()
 
find_package(OIS REQUIRED)
 
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()
 
# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 
	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

set(HDRS
	
	#main
	./main.h

	#baseEntity
	../baseentity/baseEntity.h

	#fsm
	../fsm/state.h	
	../fsm/stateMachine.h	

	#mailman
	../serverside/mailman/mailMan.h

	#letter
	../serverside/letter/letter.h
	
	#game
	../serverside/game/game.h
	../serverside/game/partido/gamePartido.h
	
	#network
	../serverside/network/network.h
	
	#tdreamsock
	../serverside/tdreamsock/dreamSockLog.h
	../serverside/tdreamsock/dreamLinuxSock.h
	
		#shape
	../serverside/shape/shape.h
	../serverside/shape/partido/shapePartido.h

	#shape states
	../serverside/shape/partido/states/shapePartidoStates.h
	
	#move
	../serverside/move/move.h
	
	#move states
	../serverside/move/states/moveStates.h
	
	#steering
	../serverside/steering/steering.h
	
	#steering states
	../serverside/steering/states/steeringStates.h
	
	#seek
	../serverside/seek/seek.h
	
	#seek states
	../serverside/seek/states/seekStates.h
	
	#avoid
	../serverside/avoid/avoid.h
	
	#avoid states
	../serverside/avoid/states/avoidStates.h
	
	#computer
	../serverside/computer/computer.h
	../serverside/computer/partido/computerPartido.h
	
	#computer states
	../serverside/computer/states/computerStates.h	
	../serverside/computer/partido/states/computerPartidoStates.h	
	
	#rotation
	../serverside/rotation/rotation.h
	
	#rotation states
	../serverside/rotation/states/rotationStates.h	
		
	#math
	../math/vector3D.h
	
	#utility
	../utility/utility.h

	#bounds
	../serverside/bounds/bounds.h
	
	#message
	../serverside/message/message.h
	
	#server
	../serverside/server/server.h
	../serverside/server/partido/serverPartido.h
	
	#client
	../serverside/client/client.h
	../serverside/client/robust/clientRobust.h
	../serverside/client/robust/partido/clientPartido.h
	
	#client states
	../serverside/client/states/clientStates.h
	../serverside/client/robust/states/clientRobustStates.h
	../serverside/client/robust/partido/states/clientPartidoStates.h

	#quiz
	../serverside/quiz/quiz.h

	#question
	../serverside/question/question.h
)
 
set(SRCS

	#main
	./main.cpp

	#baseEntity
	../baseentity/baseEntity.cpp

	#mailman
	../serverside/mailman/mailMan.cpp

	#letter
	../serverside/letter/letter.cpp
	
	#game
	../serverside/game/game.cpp
	../serverside/game/partido/gamePartido.cpp

	#dreamsock
	../serverside/tdreamsock/dreamSockLog.cpp
	../serverside/tdreamsock/dreamLinuxSock.cpp

	#network
	../serverside/network/network.cpp
	
	#shape
	../serverside/shape/shape.cpp
	../serverside/shape/partido/shapePartido.cpp
	
	#shape states
	../serverside/shape/partido/states/shapePartidoStates.cpp

	#move
	../serverside/move/move.cpp
	
	#move states
	../serverside/move/states/moveStates.cpp
	
	#steering
	../serverside/steering/steering.cpp
	
	#steering states
	../serverside/steering/states/steeringStates.cpp
	
	#seek
	../serverside/seek/seek.cpp
	
	#seek states
	../serverside/seek/states/seekStates.cpp
	
	#avoid
	../serverside/avoid/avoid.cpp
	
	#avoid states
	../serverside/avoid/states/avoidStates.cpp
	
	#computer
	../serverside/computer/computer.cpp
	../serverside/computer/partido/computerPartido.cpp
	
	#computer states
	../serverside/computer/states/computerStates.cpp
	../serverside/computer/partido/states/computerPartidoStates.cpp
	
	#rotation
	../serverside/rotation/rotation.cpp
	
	#rotation states
	../serverside/rotation/states/rotationStates.cpp
	
	#math
	../math/vector3D.cpp

	#utility
	../utility/utility.cpp
	
	#bounds
	../serverside/bounds/bounds.cpp
	
	#message
	../serverside/message/message.cpp
	
	#server
	../serverside/server/server.cpp
	../serverside/server/partido/serverPartido.cpp
	
	#client
	../serverside/client/client.cpp
	../serverside/client/robust/clientRobust.cpp
	../serverside/client/robust/partido/clientPartido.cpp

	#client states
	../serverside/client/states/clientStates.cpp
	../serverside/client/robust/states/clientRobustStates.cpp
	../serverside/client/robust/partido/states/clientPartidoStates.cpp

	#quiz
	../serverside/quiz/quiz.cpp

	#question
	../serverside/question/question.cpp
)
include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
)
 
add_executable(Server WIN32 ${HDRS} ${SRCS})
 
set_target_properties(Server PROPERTIES DEBUG_POSTFIX _d)
 
target_link_libraries(Server ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
 
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
# post-build copy for win32
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
 
install(TARGETS Server
	RUNTIME DESTINATION bin
	CONFIGURATIONS All)
  
install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/linux/plugins.cfg
	${CMAKE_SOURCE_DIR}/dist/bin/linux/resources.cfg
	DESTINATION bin
	CONFIGURATIONS Release RelWithDebInfo Debug
)
 

#need this to link to postgresql 
target_link_libraries (Server pq) 
