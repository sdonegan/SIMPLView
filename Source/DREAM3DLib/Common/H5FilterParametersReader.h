/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
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
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _H5FilterParametersREADER_H_
#define _H5FilterParametersREADER_H_

#include "hdf5.h"

#include <string>

#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/QualityMetricFilter.h"

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "AbstractFilterParametersReader.h"
#include "QualityMetricFilter.h"

/*
 *
 */
class DREAM3DLib_EXPORT H5FilterParametersReader : public AbstractFilterParametersReader
{
  public:
    DREAM3D_SHARED_POINTERS(H5FilterParametersReader)
    DREAM3D_STATIC_NEW_MACRO(H5FilterParametersReader)
    DREAM3D_TYPE_MACRO_SUPER(H5FilterParametersReader, AbstractFilterParametersReader)


    virtual ~H5FilterParametersReader();

    DREAM3D_INSTANCE_PROPERTY(hid_t, GroupId)

    virtual int openOptionsGroup(AbstractFilter* filter);
    virtual int closeOptionsGroup();

    virtual int readValue(const std::string name, std::string &value);

    virtual int readValue(const std::string name, int8_t &value);
    virtual int readValue(const std::string name, int16_t &value);
    virtual int readValue(const std::string name, int32_t &value);
    virtual int readValue(const std::string name, int64_t &value);
    virtual int readValue(const std::string name, uint8_t &value);
    virtual int readValue(const std::string name, uint16_t &value);
    virtual int readValue(const std::string name, uint32_t &value);
    virtual int readValue(const std::string name, uint64_t &value);
    virtual int readValue(const std::string name, float &value);
    virtual int readValue(const std::string name, double &value);

    virtual int readValue(const std::string name, QualityMetricFilter* f);
    virtual int readValue(const std::string name, IntVec3Widget_t v);
    virtual int readValue(const std::string name, FloatVec3Widget_t v);
    virtual int readValue(const std::string name, ComparisonInput_t v);

	virtual int setStringValue(std::string value, std::string name);

	virtual int setInt8Value(int8_t value, std::string name);
	virtual int setInt16Value(int16_t value, std::string name);
	virtual int setInt32Value(int32_t value, std::string name);
	virtual int setInt64Value(int64_t value, std::string name);
	virtual int setUInt8Value(uint8_t value, std::string name);
	virtual int setUInt16Value(uint16_t value, std::string name);
	virtual int setUInt32Value(uint32_t value, std::string name);
	virtual int setUInt64Value(uint64_t value, std::string name);
	virtual int setFloatValue(float value, std::string name);
	virtual int setDoubleValue(double value, std::string name);

	virtual int setQualityMetricFilter(QualityMetricFilter* value, std::string name);
	virtual int setIntVec3Widget(IntVec3Widget_t value, std::string name);
	virtual int setFloatVec3Widget(FloatVec3Widget_t value, std::string name);
	virtual int setComparisonInput(ComparisonInput_t value, std::string name);

  protected:
    H5FilterParametersReader();

  private:
    hid_t m_CurrentGroupId;


    H5FilterParametersReader(const H5FilterParametersReader&); // Copy Constructor Not Implemented
    void operator=(const H5FilterParametersReader&); // Operator '=' Not Implemented
};

#endif /* _H5FilterParametersREADER_H_ */
