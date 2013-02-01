cmake_minimum_required (VERSION 2.8)
include(macros_for_qt.cmake)
file(GLOB_RECURSE FilesList *.h *.cpp )  


# 1. 	set BOOSTROOT environment var to the desired path
# 2.	set PATH=QTDIR\bin;%PATH%
#		set QTDIR environment var to the Qt dir
# 3.	set GRAPHVIZ_LIBRARY_DIR where libcdt, libgvc and libgraph can be found
# 4.    set GRAPHVIZ_INCLUDE_DIR where the header files for graphviz can be found


############################################
#
#	BOOST LIB
#

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON) #on OS X i could'nt use off. singlethreaded not installed??
set(Boost_USE_STATIC_RUNTIME OFF)
#TODO: only signals required?
find_package(Boost COMPONENTS signals) 

#
#	END BOOST LIB
############################################

############################################
#
# QT 
#

find_package(Qt4 REQUIRED)
set(QT_USE_QTMAIN TRUE)
include(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

set(GeneratedFromUiLocation "generated_from_ui")
file(GLOB_RECURSE FormFiles *.ui)
message(STATUS "FormFiles =", ${FormFiles})
QT4_WRAP_UI_MOD(FormHeaders ${GeneratedFromUiLocation} ${FormFiles} )

set(GeneratedFromQrcLocation "generated_from_qrc")
file(GLOB_RECURSE RessourceFiles *.qrc)
message(STATUS "RessourceFiles =", ${RessourceFiles})
QT4_ADD_RESOURCES(RessourceFiles_RCC ${RessourceFiles})

TO_MOC_OR_NOT_TO_MOC(MocHeaderFiles ${FilesList})

set(GeneratedFromMocLocation "generated_from_moc")
QT4_WRAP_CPP_MOD(MocGeneratedSourceFiles  ${GeneratedFromMocLocation} ${MocHeaderFiles})

source_group(ui REGULAR_EXPRESSION "ui/.*\\.ui")
source_group(qrc REGULAR_EXPRESSION "qrc/.*\\.qrc")
source_group(generated_from_ui FILES ${FormHeaders})
source_group(generated_from_qrc FILES ${RessourceFiles_RCC})
source_group(generated_from_moc FILES ${MocGeneratedSourceFiles})

#
#	END QT
############################################

############################################
#
#   Graphviz
#

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(GRAPHVIZ_LIB_PATH_SUFFIX "release/lib")
  else()
    set(GRAPHVIZ_LIB_PATH_SUFFIX "debug/lib")
  endif()
endif()

find_library(GRAPHVIZ_GVC_LIB gvc PATHS $ENV{GRAPHVIZ_LIBRARY_DIR}/${GRAPHVIZ_LIB_PATH_SUFFIX})
find_library(GRAPHVIZ_CDT_LIB cdt PATHS $ENV{GRAPHVIZ_LIBRARY_DIR}/${GRAPHVIZ_LIB_PATH_SUFFIX})
find_library(GRAPHVIZ_GRAPH_LIB graph PATHS $ENV{GRAPHVIZ_LIBRARY_DIR}/${GRAPHVIZ_LIB_PATH_SUFFIX})

if(EXISTS ${GRAPHVIZ_GVC_LIB} AND EXISTS ${GRAPHVIZ_CDT_LIB} AND EXISTS ${GRAPHVIZ_GRAPH_LIB})
    message(STATUS "Graphviz found")
else()
    message(FATAL_ERROR "Graphviz NOT found")
endif()

message(STATUS "GVC: ${GRAPHVIZ_GVC_LIB}")
message(STATUS "CDT: ${GRAPHVIZ_CDT_LIB}")
message(STATUS "GRAPH: ${GRAPHVIZ_GRAPH_LIB}")
message(STATUS "Graphviz Inlcude: $ENV{GRAPHVIZ_INCLUDE_DIR}")

#
#   End Graphviz
############################################


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/${GeneratedFromUiLocation}
    ${CMAKE_CURRENT_BINARY_DIR}/${GeneratedFromMocLocation}
    ${CMAKE_CURRENT_BINARY_DIR}/${GeneratedFromQrcLocation}
    ${Boost_INCLUDE_DIRS}
    $ENV{GRAPHVIZ_INCLUDE_DIR}
    ${CUTEGRAPHLIB_SOURCE_DIR}/cuteGraphLib
)

link_directories (
    ${CUTEGRAPHLIB_BINARY_DIR}/cuteGraphLib
)

add_executable (cuteClient 
    ${FilesList}
    ${FormFiles}
    ${RessourceFiles_RCC}
    ${FormHeaders}
    ${MocGeneratedSourceFiles}
)

target_link_libraries(cuteClient 
	${QT_LIBRARIES} 
	${Boost_LIBRARIES}
    ${GRAPHVIZ_GVC_LIB}
    ${GRAPHVIZ_CDT_LIB}
    ${GRAPHVIZ_GRAPH_LIB}
    cuteGraphLib
)
