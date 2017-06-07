

set(command "/usr/bin/cmake;-P;/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also /home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(STATUS "${msg}")
endif()
