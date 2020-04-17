#diffuse
pybind11_add_module(diffuse_module ${CMAKE_CURRENT_SOURCE_DIR}/diffuse/diffuse_module.cpp)
set_target_properties(diffuse_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
                    "${CMAKE_CURRENT_SOURCE_DIR}/diffuse")
target_link_libraries(diffuse_module PRIVATE common diffuse)

#total_glass


#total_reflect