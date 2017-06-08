if (NOT PARAVIEW_BUILD_QT_GUI)
  message(FATAL_ERROR
    "${PROJECT_NAME} requires PARAVIEW_BUILD_QT_GUI to be enabled. "
    "Please rebuild ParaView (or point to a different build of ParaView) "
    "with PARAVIEW_BUILD_QT_GUI set to ON")
endif()

if(PARAVIEW_QT_VERSION VERSION_GREATER "4")
  set(Qt5_FIND_COMPONENTS Core)
else()
  include(${QT_USE_FILE})
endif()

add_paraview_plugin(SMTKMultiBlockReader "1.0"
  SERVER_MANAGER_XML
    SMTKMultiBlockReader.xml
  SERVER_MANAGER_SOURCES
    vtkSMTKMultiBlockReader.cxx
)

target_link_libraries(SMTKMultiBlockReader PRIVATE smtkCore smtkCGMSession vtkSMTKSourceExt)
