include_directories(${IncludeDIR}/RGFW)
add_library(rgfw INTERFACE)
target_include_directories(rgfw INTERFACE ${IncludeDIR}/RGFW)
find_package(X11 REQUIRED)
target_link_libraries(rgfw INTERFACE X11 Xrandr GL m dl)

# spdlog
add_subdirectory(${IncludeDIR}/spdlog)
include_directories(${spdlog_INCLUDE_DIRS})