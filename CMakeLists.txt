################################################################################
#   libbattlecreek CMake Build File                                                 #
################################################################################

project(libbattlecreek)

cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") 
find_package(Daylite REQUIRED)
find_package(BsonBind REQUIRED)

set(CMAKE_C_FLAGS ${C_FLAGS})
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

set(INCLUDE ${libbattlecreek_SOURCE_DIR}/include)


include_directories(include ${CMAKE_BINARY_DIR})
include_directories(${DAYLITE_INCLUDE_DIRS})

add_bson_binds(BSON_BIND_INCLUDES
  src/motor_state.bsonbind
  src/motor_states.bsonbind
  src/servo_states.bsonbind
  src/digital_states.bsonbind
  src/analog_states.bsonbind
  src/battery_state.bsonbind
)

SET(BSON_BIND_INCLUDES_TMP "")
FOREACH(f ${BSON_BIND_INCLUDES})
  LIST(APPEND BSON_BIND_INCLUDES_TMP "${CMAKE_CURRENT_BINARY_DIR}/${f}")
ENDFOREACH(f)
SET(BSON_BIND_INCLUDES ${BSON_BIND_INCLUDES_TMP})

file(GLOB INCLUDES ${BSON_BIND_INCLUDES})

add_custom_target(battlecreek ALL DEPENDS ${BSON_BIND_INCLUDES})

################################################################################
#   Install                                                                    #
################################################################################

install(FILES ${BSON_BIND_INCLUDES} DESTINATION include/battlecreek)

