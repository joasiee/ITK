project(GlobalRegistrationTwoImagesBSpline)

add_executable(GlobalRegistrationTwoImagesBSpline code.cxx)
target_link_libraries(GlobalRegistrationTwoImagesBSpline ${ITK_LIBRARIES})

add_executable(RegionTestSimple region.cxx)
target_link_libraries(RegionTestSimple ${ITK_LIBRARIES})
