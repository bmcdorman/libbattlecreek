project(libbattlecreek)

cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") 
find_package(Daylite REQUIRED)
find_package(BsonBind REQUIRED)

file(GLOB BATTLECREEK_SOURCES src/*.cpp)

if(NOT WIN32)
  set(CXX_FLAGS "-std=c++11")
endif()

set(CMAKE_C_FLAGS ${C_FLAGS})
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

include_directories(include ${CMAKE_BINARY_DIR})

include_directories(${DAYLITE_INCLUDE_DIRS})

add_bson_binds(BSON_BIND_INCLUDES
  src/motor_state.bsonbind
  src/motor_states.bsonbind
  src/servo_states.bsonbind
  src/digital_states.bsonbind
  src/analog_states.bsonbind
)

add_library(battlecreek SHARED ${BATTLECREEK_SOURCES} ${BSON_BIND_INCLUDES})

target_link_libraries(battlecreek ${DAYLITE_LIBRARIES})

if(WIN32)
  install(TARGETS battlecreek
          ARCHIVE DESTINATION lib
          RUNTIME DESTINATION bin)
else()
  install(TARGETS battlecreek LIBRARY DESTINATION lib)
endif()