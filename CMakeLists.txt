cmake_minimum_required(VERSION 3.28)
project(ClashOfSkeleton LANGUAGES CXX)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_compile_options(-Wall -Wextra)

# --- SFML Dependency (FetchContent) ---
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# --- nlohmann/json Dependency (FetchContent) ---
include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(googletest)

file(GLOB GameEventSource "src/Event/*.cpp")
add_library(GameEvent STATIC
    ${GameEventSource}
)
target_include_directories(GameEvent PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB GameCommandSource "src/Command/*.cpp")
add_library(GameCommand STATIC
        ${GameCommandSource}
)
target_include_directories(GameCommand PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(GameCommand PUBLIC
        SFML::Graphics
        GameEvent
        GameGraphic
        GameState
)

file(GLOB GameUtilitySource "src/Utility/*.cpp")
# Utility Library
add_library(GameUtility STATIC
    ${GameUtilitySource}
)
target_include_directories(GameUtility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries( GameUtility PUBLIC
        SFML::Audio
)
file(GLOB GameGraphicSource "src/Graphic/*.cpp")
# Graphic Library
add_library(GameGraphic STATIC
    ${GameGraphicSource}
)
target_include_directories(GameGraphic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(GameGraphic PUBLIC
    SFML::Graphics
    GameUtility
    GameState
    GameEvent
    GameCommand
    nlohmann_json::nlohmann_json
)

file(GLOB GameResourcesSource "src/Resources/*.cpp")
# Resources Library
add_library(GameResources STATIC
        ${GameResourcesSource}
)
target_include_directories(GameResources PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(GameResources PUBLIC
        SFML::Graphics
        SFML::Audio
        GameUtility
        nlohmann_json::nlohmann_json
)

file(GLOB GameStateSource "src/State/*.cpp")
# State Library
add_library(GameState STATIC
        ${GameStateSource}
)
target_include_directories(GameState PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(GameState PUBLIC
        SFML::Graphics
        GameGraphic
        GameResources
        GameUtility
        GameEvent
        Engine
        nlohmann_json::nlohmann_json
)

file(GLOB EngineSource "src/Engine/*.cpp")
# Engine Library
add_library(Engine STATIC
        ${EngineSource}
)
target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(Engine PUBLIC
        SFML::Window
        SFML::Graphics
        SFML::System
        SFML::Audio
        GameState
        GameGraphic
        GameResources
        GameUtility
        GameEvent
        GameCommand

)

# --- Main Executable ---
add_executable(main src/main.cpp)

target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(main PUBLIC
        Engine
        SFML::Graphics
        SFML::Window
        SFML::System
)
set(ASSETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(ASSETS_DESTINATION_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${ASSETS_SOURCE_DIR}"
        "${ASSETS_DESTINATION_DIR}"
        COMMENT "Copying assets to output directory"
)