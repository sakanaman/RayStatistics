#diffuse
pybind11_add_module(diffuse_module ${CMAKE_CURRENT_SOURCE_DIR}/diffuse/diffuse_module.cpp)
set_target_properties(diffuse_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
                    "${CMAKE_CURRENT_SOURCE_DIR}/diffuse")
target_link_libraries(diffuse_module PRIVATE common diffuse)

#phase
pybind11_add_module(phase_module ${CMAKE_CURRENT_SOURCE_DIR}/phase/phase_module.cpp)
set_target_properties(phase_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
                    "${CMAKE_CURRENT_SOURCE_DIR}/phase")
target_link_libraries(phase_module PRIVATE common phase)

#total_glass


#total_reflect