project(NumericsExamples)

add_executable(FourierDescriptors1 FourierDescriptors1.cxx )
add_executable(AmoebaOptimizer1 AmoebaOptimizer.cxx ExampleCostFunction.h)

target_link_libraries(FourierDescriptors1 ${ITK_LIBRARIES})
target_link_libraries(AmoebaOptimizer1 ${ITK_LIBRARIES})
