cmake_minimum_required (VERSION 2.8)

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

#set(GeneratedFromUiLocation "generated_from_ui")
#file(GLOB_RECURSE FormFiles *.ui)
#message("FormFiles =", ${FormFiles})
#QT4_WRAP_UI_MOD(FormHeaders ${GeneratedFromUiLocation} ${FormFiles} )

#TO_MOC_OR_NOT_TO_MOC(MocHeaderFiles ${FilesList}  )

#set(GeneratedFromMocLocation "generated_from_moc")
#QT4_WRAP_CPP_MOD(MocGeneratedSourceFiles  ${GeneratedFromMocLocation}  ${MocHeaderFiles})

#source_group(ui REGULAR_EXPRESSION "ui/.*\\.ui")
#source_group(generated_from_ui FILES ${FormHeaders})
#source_group(generated_from_moc FILES ${MocGeneratedSourceFiles})

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


############################################
#   Doxygen
#

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Documentation")

    if(NOT EXISTS "${DOXROOT}")
        file(MAKE_DIRECTORY "${DOXROOT}")
    endif()

    set(DOXY_TARGET_OUTPUT_DIR "${DOXROOT}")
    set(DOXY_TARGET_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    set(DOXY_TARGET_NAME "${TARGET_NAME}")
    set(DOXY_TARGET_TITLE "cuteGraph")
    set(DOXY_TARGET_BRIEF "Let's draw dot-Graphs with QT")
    set(DOXY_TARGET_INPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    set(DOXY_TARGET_FILE_VERSION_FILTER "\"${PRINT_FILE_DATE_COMMAND_STR} \"")

configure_file(${CUTEGRAPHLIB_SOURCE_DIR}/cuteGraphLib/Doxyfile.in ${CUTEGRAPHLIB_SOURCE_DIR}/cuteGraphLib/Doxyfile @ONLY)
add_custom_target(doxydoc
${DOXYGEN_EXECUTABLE} ${CUTEGRAPHLIB_SOURCE_DIR}/cuteGraphLib/Doxyfile
WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

#   End Doxygen
#
############################################


include_directories(
    ${Boost_INCLUDE_DIRS}
    $ENV{GRAPHVIZ_INCLUDE_DIR}
)

add_library (cuteGraphLib 
    ${FilesList}
)

target_link_libraries(cuteGraphLib 
	${QT_LIBRARIES} 
	${Boost_LIBRARIES}
    ${GRAPHVIZ_GVC_LIB}
    ${GRAPHVIZ_CDT_LIB}
    ${GRAPHVIZ_GRAPH_LIB}
)