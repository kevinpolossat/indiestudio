

set(command "${make}")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-build-out.log"
  ERROR_FILE "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest build command succeeded.  See also /home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(STATUS "${msg}")
endif()
