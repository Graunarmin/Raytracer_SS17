add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

#Build tests
add_executable(tests
 tests.cpp)
target_link_libraries(tests
${FRAMEWORK_NAME}
  ${GLFW_LIBRARIES}
 )

#fileGenerator bauen
add_executable(fileGenerator fileGenerator.cpp)
target_link_libraries(fileGenerator ${FRAMEWORK_NAME} ${LIBRARIES}
        glfw
        ${GLFW_LIBRARIES}
        )
add_dependencies(fileGenerator glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS fileGenerator DESTINATION .)

#animation bauen
add_executable(animation animation.cpp)
target_link_libraries(animation ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(animation glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS animation DESTINATION .)
