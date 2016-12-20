// Copyright (c) Maxim Torgonskiy
// All rights reserved.
// See LICENSE.txt for details.

#include "vtkSMTKMultiBlockReader.h"

#include <vtkObjectFactory.h> // for new() macro
#include <vtkMultiBlockDataSet.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>

#include "smtk/attribute/FileItem.h"
#include "smtk/attribute/IntItem.h"
#include "smtk/model/Manager.h"
#include "smtk/model/Operator.h"
#include "smtk/extension/vtk/source/vtkModelMultiBlockSource.h"

vtkStandardNewMacro(vtkSMTKMultiBlockReader);

vtkSMTKMultiBlockReader::vtkSMTKMultiBlockReader() :
  FileName()
{
  this->SetNumberOfInputPorts(0);
}

vtkSMTKMultiBlockReader::~vtkSMTKMultiBlockReader()
{}

int vtkSMTKMultiBlockReader::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* vtkNotUsed(outputVector)
) {
  if(this->FileName.empty()) {
    vtkErrorMacro("FileName not specified");
    return 0;
  }

  return 1;
}

void vtkSMTKMultiBlockReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

int vtkSMTKMultiBlockReader::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector
) {
  static const std::string cgm_session_type = "cgm";
  static const std::string cgm_session_read_op_name = "read";

  if(this->FileName.empty()) {
    vtkErrorMacro("File name not specified");
    return 0;
  }

  auto manager = smtk::model::Manager::create();

  // Check if cgm session exists
  #ifndef NDEBUG
  {
    auto sessions = manager->sessionTypeNames();
    bool cgm_ok = false;
    for(const auto& session_type_name : sessions)
      if(session_type_name == cgm_session_type) {
        cgm_ok = true;
        break;
      }
    if(!cgm_ok) {
      vtkErrorMacro("Impossible to create a " << cgm_session_type << " session");
      return 0;
    }
  }
  #endif // NDEBUG

//   // List formats supported by sessions
//   std::cout << cgm_session_type << " session supported formats:" << std::endl;
//   for(const auto& engine_formats : manager->sessionFileTypes(cgm_session_type)) {
//     std::cout << "  " << engine_formats.first << " engine:" << std::endl;
//     for(const auto& format : engine_formats.second)
//       std::cout << "    " << format << std::endl;
//   }

  auto session_ptr = manager->createSessionOfType(cgm_session_type);
  auto session_ref = manager->registerSession(session_ptr);

  auto read_op = session_ptr->op(cgm_session_read_op_name);
  if (!read_op) {
    vtkErrorMacro("Model cannot be read");
    return 0;
  }
  read_op->specification()->findFile("filename")->setValue(FileName);
  auto read_op_result = read_op->operate();
  if(read_op_result->findInt("outcome")->value() != smtk::model::OPERATION_SUCCEEDED) {
    vtkErrorMacro("Model cannot be read");
    return 0;
  }
  auto model = read_op_result->findModelEntity("created")->value();
  manager->assignDefaultNames();
  if (!model.isValid()) {
    vtkErrorMacro("Model cannot be created");
    return 0;
  }

  vtkNew<vtkModelMultiBlockSource> multiblock_source;
  multiblock_source->SetModelManager(manager);
  // multiblock_source->SetAllowNormalGeneration(true); // Uncomment if necessary

  int global_warning_display = GetGlobalWarningDisplay();
  GlobalWarningDisplayOff(); // Update always causes a warning, suppress it.
  multiblock_source->Update();
  SetGlobalWarningDisplay(global_warning_display);

  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkMultiBlockDataSet* output = vtkMultiBlockDataSet::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
  output->ShallowCopy(multiblock_source->GetOutput());

  return 1;
}
