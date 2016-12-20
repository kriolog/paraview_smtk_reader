if(PARAVIEW_BUILD_QT_GUI)
  include(${QT_USE_FILE})
endif(PARAVIEW_BUILD_QT_GUI)

add_paraview_plugin(SMTKMultiBlockReader "1.0"
  SERVER_MANAGER_XML
    SMTKMultiBlockReader.xml
  SERVER_MANAGER_SOURCES
    vtkSMTKMultiBlockReader.cxx
)

target_link_libraries(SMTKMultiBlockReader PRIVATE smtkCore smtkCGMSession vtkSMTKSourceExt)
