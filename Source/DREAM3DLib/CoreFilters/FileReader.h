/* ============================================================================
* Copyright (c) 2009-2015 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#ifndef _FileReader_H_
#define _FileReader_H_

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/AbstractFilter.h"

/**
 * @brief The FileReader class serves as a superclass for reader filters.
 */
class DREAM3DLib_EXPORT FileReader : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */
  public:
    DREAM3D_SHARED_POINTERS(FileReader)
    DREAM3D_STATIC_NEW_MACRO(FileReader)
    DREAM3D_TYPE_MACRO_SUPER(FileReader, AbstractFilter)

    virtual ~FileReader();

    /* This will internally call readHeader() and readFile() with appropriate
     * error checkes after each one. Subclasses should just implement the readHeader
     * and readFile methods unless special setups are needed.
     */
    virtual void execute();

  protected:
    FileReader();

    virtual int readHeader();

    virtual int readFile();

    virtual void dataCheck();

  private:
    FileReader(const FileReader&); // Copy Constructor Not Implemented
    void operator=(const FileReader&); // Operator '=' Not Implemented
};

#endif /* FileReader_H_ */
