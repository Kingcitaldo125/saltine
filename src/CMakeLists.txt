# saltine_zipfile
add_library(saltine_zipfile SHARED zipfile.cpp)

target_include_directories(saltine_zipfile PRIVATE ${CMAKE_SOURCE_DIR}/include)

# SALTINE_LIB_NAME
add_library(${SALTINE_LIB_NAME} SHARED saltine.cpp)

target_link_libraries(${SALTINE_LIB_NAME} PUBLIC saltine_zipfile)
target_include_directories(${SALTINE_LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
