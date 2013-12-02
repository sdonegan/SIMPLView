/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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

#include "FindMisorientations.h"

#include "DREAM3DLib/Math/DREAM3DMath.h"
#include "DREAM3DLib/Common/Constants.h"

#include "DREAM3DLib/StatisticsFilters/FindNeighbors.h"
#include "DREAM3DLib/GenericFilters/FindSurfaceFeatures.h"
#include "DREAM3DLib/GenericFilters/FindFeaturePhases.h"



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindMisorientations::FindMisorientations()  :
  AbstractFilter(),
  m_DataContainerName(DREAM3D::Defaults::VolumeDataContainerName),
  m_CellFeatureAttributeMatrixName(DREAM3D::Defaults::CellFeatureAttributeMatrixName),
  m_CellEnsembleAttributeMatrixName(DREAM3D::Defaults::CellEnsembleAttributeMatrixName),
  m_AvgQuatsArrayName(DREAM3D::FeatureData::AvgQuats),
  m_FeaturePhasesArrayName(DREAM3D::FeatureData::Phases),
  m_CrystalStructuresArrayName(DREAM3D::EnsembleData::CrystalStructures),
  m_NeighborListArrayName(DREAM3D::FeatureData::NeighborList),
  m_MisorientationListArrayName(DREAM3D::FeatureData::MisorientationList),
  m_avgMisorientationArrayName(DREAM3D::FeatureData::avgMisorientation),
  m_AvgQuats(NULL),
  m_FeaturePhases(NULL),
  m_NeighborList(NULL),
  m_MisorientationList(NULL),
  m_avgMisorientation(NULL),
  m_CrystalStructures(NULL)
{
  m_OrientationOps = OrientationOps::getOrientationOpsVector();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindMisorientations::~FindMisorientations()
{
}
// -----------------------------------------------------------------------------
void FindMisorientations::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  /* Code to read the values goes between these statements */
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE BEGIN*/
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE END*/
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int FindMisorientations::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindMisorientations::dataCheck(bool preflight, size_t voxels, size_t features, size_t ensembles)
{
  setErrorCondition(0);

  VolumeDataContainer* m = getDataContainerArray()->getPrereqDataContainer<VolumeDataContainer, FindMisorientations>(this, getDataContainerName(), false);
  if(getErrorCondition() < 0) { return; }

  QVector<int> dims(1, 4);
  m_AvgQuatsPtr = attrMat->getPrereqArray<DataArray<float>, AbstractFilter>(this, m_CellFeatureAttributeMatrixName,  m_AvgQuatsArrayName, -301, features, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if( NULL != m_AvgQuatsPtr.lock().get() ) /* Validate the Weak Pointer wraps a non-NULL pointer to a DataArray<T> object */
  { m_AvgQuats = m_AvgQuatsPtr.lock()->getPointer(0); } /* Now assign the raw pointer to data from the DataArray<T> object */
  dims[0] = 1;
  m_FeaturePhasesPtr = attrMat->getPrereqArray<DataArray<int32_t>, AbstractFilter>(this, m_CellFeatureAttributeMatrixName,  m_FeaturePhasesArrayName, -303, features, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if( NULL != m_FeaturePhasesPtr.lock().get() ) /* Validate the Weak Pointer wraps a non-NULL pointer to a DataArray<T> object */
  { m_FeaturePhases = m_FeaturePhasesPtr.lock()->getPointer(0); } /* Now assign the raw pointer to data from the DataArray<T> object */
  m_avgMisorientationPtr = attrMat->createNonPrereqArray<DataArray<float>, AbstractFilter, float>(this, m_CellFeatureAttributeMatrixName,  m_avgMisorientationArrayName, 0, features, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if( NULL != m_avgMisorientationPtr.lock().get() ) /* Validate the Weak Pointer wraps a non-NULL pointer to a DataArray<T> object */
  { m_avgMisorientation = m_avgMisorientationPtr.lock()->getPointer(0); } /* Now assign the raw pointer to data from the DataArray<T> object */
  typedef DataArray<unsigned int> XTalStructArrayType;
  m_CrystalStructuresPtr = attrMat->getPrereqArray<DataArray<unsigned int>, AbstractFilter>(this, m_CellEnsembleAttributeMatrixName,  m_CrystalStructuresArrayName, -305, ensembles, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if( NULL != m_CrystalStructuresPtr.lock().get() ) /* Validate the Weak Pointer wraps a non-NULL pointer to a DataArray<T> object */
  { m_CrystalStructures = m_CrystalStructuresPtr.lock()->getPointer(0); } /* Now assign the raw pointer to data from the DataArray<T> object */

  // Now we are going to get a "Pointer" to the NeighborList object out of the DataContainer
  IDataArray::Pointer neighborListPtr = m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getAttributeArray(m_NeighborListArrayName);
  if (NULL == neighborListPtr.get())
  {
    QString ss = QObject::tr("NeighborLists are not available and are required for this filter to run. A filter that generates NeighborLists needs to be placed before this filter in the pipeline.");
    setErrorCondition(-305);
    addErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else
  {
    m_NeighborList = NeighborList<int>::SafeObjectDownCast<IDataArray*, NeighborList<int>*>(neighborListPtr.get());
  }

  IDataArray::Pointer misorientationPtr = m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getAttributeArray(m_MisorientationListArrayName);
  if(NULL == misorientationPtr.get())
  {
    NeighborList<float>::Pointer misorientationListPtr = NeighborList<float>::New();
    misorientationListPtr->SetName(m_MisorientationListArrayName);
    misorientationListPtr->Resize(features);
    m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->addAttributeArray(m_MisorientationListArrayName, misorientationListPtr);
    m_MisorientationList = misorientationListPtr.get();
    if (misorientationListPtr.get() == NULL)
    {
      QString ss = QObject::tr("MisorientationLists Array Not Initialized correctly");
      setErrorCondition(-308);
      addErrorMessage(getHumanLabel(), ss, -308);
    }
  }
  else
  {
    m_MisorientationList = NeighborList<float>::SafeObjectDownCast<IDataArray*, NeighborList<float>*>(misorientationPtr.get());
    m_MisorientationList->Resize(features);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindMisorientations::preflight()
{

  dataCheck(true, 1, 1, 1);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindMisorientations::execute()
{
  VolumeDataContainer* m = getDataContainerArray()->getPrereqDataContainer<VolumeDataContainer, AbstractFilter>(this, getDataContainerName(), false);
  if(getErrorCondition() < 0) { return; }
  setErrorCondition(0);

  size_t totalFeatures = m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getNumTuples();
  size_t totalEnsembles = m->getAttributeMatrix(getCellEnsembleAttributeMatrixName())->getNumTuples();
  dataCheck(false, 0, totalFeatures, totalEnsembles);
  if (getErrorCondition() < 0)
  {
    return;
  }

  // But since a pointer is difficult to use operators with we will now create a
  // reference variable to the pointer with the correct variable name that allows
  // us to use the same syntax as the "vector of vectors"
  NeighborList<int>& neighborlist = *m_NeighborList;

  QVector<QVector<float> > misorientationlists;

  float n1 = 0.0f, n2 = 0.0f, n3 = 0.0f;
  //float r1= 0.0f, r2 = 0.0f, r3 = 0.0f;
  // int mbin = 0;
  float w;
  float neighMisoTot = 0.0f;
  QuatF q1;
  QuatF q2;
  QuatF* avgQuats = reinterpret_cast<QuatF*>(m_AvgQuats);


  size_t numfeatures = m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getNumTuples();
  unsigned int phase1, phase2;

  float radToDeg = 180.0 / DREAM3D::Constants::k_Pi;

  size_t nname;
  // float nsa;
  misorientationlists.resize(numfeatures);
  for (size_t i = 1; i < numfeatures; i++)
  {
    QuaternionMathF::Copy(avgQuats[i], q1);
    phase1 = m_CrystalStructures[m_FeaturePhases[i]];
    misorientationlists[i].fill(-1.0, neighborlist[i].size() );
    for (size_t j = 0; j < neighborlist[i].size(); j++)
    {
      w = 10000.0;
      nname = neighborlist[i][j];
      QuaternionMathF::Copy(avgQuats[nname], q2);
      phase2 = m_CrystalStructures[m_FeaturePhases[nname]];
      if (phase1 == phase2)
      {
        w = m_OrientationOps[phase1]->getMisoQuat( q1, q2, n1, n2, n3);
        misorientationlists[i][j] = w * radToDeg;
      }
      else
      {
        misorientationlists[i][j] = -100;
      }
      neighMisoTot += misorientationlists[i][j];
    }
    m_avgMisorientation[i] = neighMisoTot / neighborlist[i].size();
    neighMisoTot = 0.0f;
  }

  // We do this to create new set of MisorientationList objects
  totalFeatures = m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getNumTuples();
  totalEnsembles = m->getAttributeMatrix(getCellEnsembleAttributeMatrixName())->getNumTuples();
  dataCheck(false, 0, totalFeatures, totalEnsembles);

  for (size_t i = 1; i < m->getAttributeMatrix(getCellFeatureAttributeMatrixName())->getNumTuples(); i++)
  {
    // Set the vector for each list into the NeighborList Object
    NeighborList<float>::SharedVectorType misoL(new std::vector<float>);
    misoL->assign(misorientationlists[i].begin(), misorientationlists[i].end());
    m_MisorientationList->setList(static_cast<int>(i), misoL);
  }

  notifyStatusMessage("FindMisorientations Completed");
}
