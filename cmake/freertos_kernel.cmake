message(CHECK_START "Include FreeRTOS-kernel")

if(NOT FREERTOS_KERNEL_REPOSITORY)
  set(FREERTOS_KERNEL_REPOSITORY file://${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel)
  message(STATUS "Select default FreeRTOS-kernel repository.")
endif()

if(NOT FREERTOS_CONFIG_FILE_DIRECTORY)
  set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_SOURCE_DIR}/src CACHE STRING "")
  message(STATUS "Select default FreeRTOSConfig.h directory.")
endif()

if(NOT FREERTOS_PORT)
  set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "")
  message(STATUS "Select default FreeRTOS port.")
endif()

if(NOT FREERTOS_HEAP)
  set(FREERTOS_HEAP "4" CACHE STRING "")
  message(STATUS "Select default heap model.")
endif()

string(ASCII 27 ESC)
message(STATUS "${ESC}[33mUse repository: " ${FREERTOS_KERNEL_REPOSITORY} "${ESC}[0m")
message(STATUS "${ESC}[33mFreeRTOSConfig.h directory: " ${FREERTOS_CONFIG_FILE_DIRECTORY} "${ESC}[0m")
message(STATUS "${ESC}[33mSelected FreeRTOS port: " ${FREERTOS_PORT} "${ESC}[0m")
message(STATUS "${ESC}[33mSelected heap model: " ${FREERTOS_HEAP} "${ESC}[0m")


include(FetchContent)

FetchContent_Declare(freertoskernel_repo
  GIT_REPOSITORY ${FREERTOS_KERNEL_REPOSITORY}
  GIT_TAG        main
)

FetchContent_MakeAvailable(freertoskernel_repo)

message(CHECK_PASS "done")

