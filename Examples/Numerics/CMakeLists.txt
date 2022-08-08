project(NumericsExamples)

add_executable(FourierDescriptors1 FourierDescriptors1.cxx )
target_link_libraries(FourierDescriptors1 ${ITK_LIBRARIES})

add_executable(EvaluationTest EvaluationTest.cxx )
target_link_libraries(EvaluationTest ${ITK_LIBRARIES})