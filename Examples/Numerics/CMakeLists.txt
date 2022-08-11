project(NumericsExamples)

add_executable(FourierDescriptors1 FourierDescriptors1.cxx )
target_link_libraries(FourierDescriptors1 ${ITK_LIBRARIES})

add_executable(IntermediateResultsTest IntermediateResultsTest.cxx )
target_link_libraries(IntermediateResultsTest ${ITK_LIBRARIES})