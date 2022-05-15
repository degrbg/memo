function(add_gtest)
  set(options "")
  set(oneValueArgs NAME)
  set(multiValueArgs LINK)
  cmake_parse_arguments(
      TEST_H
      "${options}"
      "${oneValueArgs}"
      "${multiValueArgs}"
      ${ARGN}
  )

  set(FILENAME ${TEST_H_NAME}_test)
  add_executable(${FILENAME} ${FILENAME}.cpp)

  target_link_libraries(${FILENAME} PUBLIC gtest_main)

  foreach(LINK ${TEST_H_LINK})
    target_link_libraries(${FILENAME} PUBLIC ${LINK})
  endforeach()
endfunction()
