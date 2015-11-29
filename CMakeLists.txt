################################################################################
#   libbattlecreek CMake Build File                                                 #
################################################################################

project(libbattlecreek)

cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") 
find_package(Daylite REQUIRED)
find_package(BsonBind REQUIRED)

file(GLOB BATTLECREEK_SOURCES src/*.cpp)

if(NOT WIN32)
  set(CXX_FLAGS "-std=c++11")
endif()

set(CMAKE_C_FLAGS ${C_FLAGS})
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

set(INCLUDE ${libbattlecreek_SOURCE_DIR}/include)
set(SRC ${libbattlecreek_SOURCE_DIR}/src)


include_directories(include ${CMAKE_BINARY_DIR})
include_directories(${DAYLITE_INCLUDE_DIRS})

add_bson_binds(BSON_BIND_INCLUDES
  src/motor_state.bsonbind
  src/motor_states.bsonbind
  src/servo_states.bsonbind
  src/digital_states.bsonbind
  src/analog_states.bsonbind
)

SET(BSON_BIND_INCLUDES_TMP "")
FOREACH(f ${BSON_BIND_INCLUDES})
  LIST(APPEND BSON_BIND_INCLUDES_TMP "${CMAKE_CURRENT_BINARY_DIR}/${f}")
ENDFOREACH(f)
SET(BSON_BIND_INCLUDES ${BSON_BIND_INCLUDES_TMP})

file(GLOB BATTLECREEK_INCLUDES ${INCLUDE}/battlecreek/*.hpp)

file(GLOB INCLUDES ${BATTLECREEK_INCLUDES} ${BSON_BIND_INCLUDES})
file(GLOB SOURCES ${SRC}/*)

add_library(battlecreek SHARED ${BATTLECREEK_SOURCES} ${BSON_BIND_INCLUDES})

target_link_libraries(battlecreek ${DAYLITE_LIBRARIES})

################################################################################
#   Install                                                                    #
################################################################################

install(FILES ${BATTLECREEK_INCLUDES} DESTINATION include/battlecreek)
install(FILES ${BSON_BIND_INCLUDES} DESTINATION include/battlecreek/msgs)

if(WIN32)
  install(TARGETS battlecreek
          ARCHIVE DESTINATION lib
          RUNTIME DESTINATION bin)
else()
  install(TARGETS battlecreek LIBRARY DESTINATION lib)
endif()