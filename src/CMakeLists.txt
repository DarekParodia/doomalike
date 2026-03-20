# get files
file(GLOB_RECURSE ROOT_FILES CONFIGURE_DEPENDS ./*.cpp ./*.c ./*.h ./*.hpp)

# create executables
add_executable(${PROJECT_DISPLAYNAME} ${ROOT_FILES})

# assets script
add_custom_target(assets
    COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/copy_assets.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Copying assets...")

add_dependencies(${PROJECT_DISPLAYNAME} assets)

# RGFW
target_link_libraries(${PROJECT_DISPLAYNAME} PRIVATE rgfw)


# spdlog
target_link_libraries(${PROJECT_DISPLAYNAME} PRIVATE spdlog)