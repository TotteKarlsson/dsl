
set(target euler1)

add_executable(${target} main.cpp)
target_link_libraries (${target} mtkCommon)
target_link_libraries (${target} mtkMath)
target_link_libraries (${target} mtkGraphics)
target_link_libraries (${target} mtkMolecule)
target_link_libraries (${target} mtkSpin)
#target_link_libraries(${target} vtkCommon)
#target_link_libraries(${target} vtkFiltering)
#target_link_libraries(${target} vtkGraphics)
#target_link_libraries(${target} vtkHybrid)
#target_link_libraries(${target} vtkImaging)
#target_link_libraries(${target} vtkIO)
#target_link_libraries(${target} vtkRendering)
#target_link_libraries(${target} vtksys)
#target_link_libraries(${target} vtkNetCDF)

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${exe_path}/${target}.tds)

install (TARGETS ${target} DESTINATION bin COMPONENT compiled_examples)
