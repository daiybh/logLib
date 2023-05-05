cmake_minimum_required (VERSION 3.8)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

project (LogLib)
find_package(spdlog CONFIG REQUIRED)
#find_package(RapidJSON CONFIG REQUIRED)

file(GLOB source_cpp "./*.cpp")
add_library (${PROJECT_NAME} ${source_cpp})
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_link_libraries(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:spdlog::spdlog_header_only>
#							 PRIVATE $<BUILD_INTERFACE:rapidjson>
							 )
							  
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>									
                                  PUBLIC $<INSTALL_INTERFACE:include>)
