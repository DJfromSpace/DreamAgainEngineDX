# Author: DJfromSpace (Dillon E Jones)
cmake_minimum_required(VERSION 3.23)

  project(DreamAgainEngineDX
    VERSION 0.1
  )

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  configure_file(
    ${CMAKE_SOURCE_DIR}/config.h
    ${CMAKE_BINARY_DIR}/generated/config.h
    @ONLY
  )

  add_executable(DreamAgainEngineDX)

  target_include_directories(DreamAgainEngineDX
    PRIVATE
      ${CMAKE_BINARY_DIR}/generated
  )

  target_sources(DreamAgainEngineDX
    PRIVATE
      ./editor/src/main.cpp
      "runtime/core/DreamApp.h"
      "runtime/core/DreamApp.cpp"
      "runtime/core/AppConfig.h"
      "runtime/core/DreamTimer.h"
      "runtime/core/DreamTimer.cpp"
      "runtime/debugtools/DreamDebugTools.h"
      "runtime/debugtools/DreamDebugTools.cpp"
      "runtime/io/DreamFileSystem.h"
      "runtime/io/DreamFileSystem.cpp"
      "runtime/io/RuntimeConfig.h"
      "runtime/io/RuntimeConfig.cpp"
      "runtime/utils/DreamLogger.h"
      "runtime/utils/DreamLogger.cpp"
  )
