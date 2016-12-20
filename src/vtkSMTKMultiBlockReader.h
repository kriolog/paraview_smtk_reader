// Copyright (c) Maxim Torgonskiy
// All rights reserved.
// See LICENSE.txt for details.

#ifndef VTK_SMTK_MULTIBLOCK_READER_H
#define VTK_SMTK_MULTIBLOCK_READER_H

#include <string>

#include "vtkIOGeometryModule.h" // For export macro
#include "vtkMultiBlockDataSetAlgorithm.h"

class VTKIOGEOMETRY_EXPORT vtkSMTKMultiBlockReader : public vtkMultiBlockDataSetAlgorithm
{
public:
  static vtkSMTKMultiBlockReader* New();
  vtkTypeMacro(vtkSMTKMultiBlockReader, vtkMultiBlockDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkGetMacro(FileName, std::string);
  vtkSetMacro(FileName, std::string);

protected:
  vtkSMTKMultiBlockReader();
  ~vtkSMTKMultiBlockReader();

  int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*);
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);

  std::string FileName;

private:
  vtkSMTKMultiBlockReader(const vtkSMTKMultiBlockReader&) VTK_DELETE_FUNCTION;
  void operator=(const vtkSMTKMultiBlockReader&) VTK_DELETE_FUNCTION;
};

#endif // VTK_SMTK_MULTIBLOCK_READER_H
