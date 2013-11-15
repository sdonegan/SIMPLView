#include "FindFeatureClustering.h"

#include "DREAM3DLib/Math/DREAM3DMath.h"
#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/StatisticsFilters/FindSizes.h"
#include "DREAM3DLib/GenericFilters/FindFeaturePhases.h"
#include "DREAM3DLib/GenericFilters/FindFeatureCentroids.h"



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindFeatureClustering::FindFeatureClustering() :
  AbstractFilter(),
  m_DataContainerName(DREAM3D::HDF5::VolumeDataContainerName),
  m_CentroidsArrayName(DREAM3D::FeatureData::Centroids),
  m_EquivalentDiametersArrayName(DREAM3D::FeatureData::EquivalentDiameters),
  m_FeaturePhasesArrayName(DREAM3D::FeatureData::Phases),
  m_ClusteringListArrayName(DREAM3D::FeatureData::ClusteringList),
  m_ErrorOutputFile(),
  m_FeaturePhases(NULL),
  m_Centroids(NULL),
  m_EquivalentDiameters(NULL),
  m_ClusteringList(NULL)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindFeatureClustering::~FindFeatureClustering()
{
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindFeatureClustering::setupFilterParameters()
{
}
// -----------------------------------------------------------------------------
void FindFeatureClustering::readFilterParameters(AbstractFilterParametersReader* reader, int index)
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
int FindFeatureClustering::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindFeatureClustering::dataCheck(bool preflight, size_t voxels, size_t features, size_t ensembles)
{
  setErrorCondition(0);
  VolumeDataContainer* m = getDataContainerArray()->getDataContainerAs<VolumeDataContainer>(getDataContainerName());

  // Feature Data
  // Do this whole block FIRST otherwise the side effect is that a call to m->getNumFeatureTuples will = 0
  // because we are just creating an empty NeighborList object.
  // Now we are going to get a "Pointer" to the NeighborList object out of the DataContainer
  m_ClusteringList = NeighborList<float>::SafeObjectDownCast<IDataArray*, NeighborList<float>* >
                     (m->getCellFeatureData(m_ClusteringListArrayName).get());
  if(m_ClusteringList == NULL)
  {
    NeighborList<float>::Pointer clusteringPtr = NeighborList<float>::New();
    clusteringPtr->SetName(m_ClusteringListArrayName);
    clusteringPtr->Resize(features);
    clusteringPtr->setNumNeighborsArrayName(m_ClusteringListArrayName);
    m->addCellFeatureData(m_ClusteringListArrayName, clusteringPtr);
    if (clusteringPtr.get() == NULL)
    {
      QString ss = QObject::tr("Clustering Array Not Initialized at Beginning of FindFeatureClustering Filter");
      setErrorCondition(-308);
      addErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }
    m_ClusteringList = NeighborList<float>::SafeObjectDownCast<IDataArray*, NeighborList<float>* >
                       (m->getCellFeatureData(m_ClusteringListArrayName).get());

    CreatedArrayHelpIndexEntry::Pointer e = CreatedArrayHelpIndexEntry::New();
    e->setFilterName(this->getNameOfClass());
    e->setFilterHumanLabel(this->getHumanLabel());
    e->setFilterGroup(this->getGroupName());
    e->setFilterSubGroup(this->getSubGroupName());
    e->setArrayDefaultName(m_ClusteringListArrayName);
    e->setArrayGroup("Feature");
    e->setArrayNumComponents(0);
    e->setArrayType("NeighborList");
    addCreatedArrayHelpIndexEntry(e);
  }

  QVector<int> dims(1,1);
  GET_PREREQ_DATA(m, DREAM3D, CellFeatureData, EquivalentDiameters, -302, float, FloatArrayType, features, dims)

  GET_PREREQ_DATA(m, DREAM3D, CellFeatureData, FeaturePhases, -304, int32_t, Int32ArrayType, features, dims)
  dims[0] = 3;
  GET_PREREQ_DATA(m, DREAM3D, CellFeatureData, Centroids, -305, float, FloatArrayType, features, dims)
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindFeatureClustering::preflight()
{
  dataCheck(true, 1, 1, 1);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindFeatureClustering::execute()
{
  VolumeDataContainer* m = getDataContainerArray()->getDataContainerAs<VolumeDataContainer>(getDataContainerName());
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The DataContainer Object was NULL", -999);
    return;
  }
  setErrorCondition(0);

  dataCheck(false, m->getTotalPoints(), m->getNumCellFeatureTuples(), m->getNumCellEnsembleTuples());
  if (getErrorCondition() < 0)
  {
    return;
  }

  find_clustering();
  notifyStatusMessage("FindFeatureClustering Completed");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindFeatureClustering::find_clustering()
{
  bool writeErrorFile = true;
  std::ofstream outFile;
  if(m_ErrorOutputFile.isEmpty() == false)
  {
    outFile.open(m_ErrorOutputFile.toLatin1().data(), std::ios_base::binary);
    writeErrorFile = true;
  }

  VolumeDataContainer* m = getDataContainerArray()->getDataContainerAs<VolumeDataContainer>(getDataContainerName());

  float x, y, z;
  float xn, yn, zn;
  float r;

  std::vector<std::vector<float> > clusteringlist;

  int totalFeatures = int(m->getNumCellFeatureTuples());

  clusteringlist.resize(totalFeatures);

  for (size_t i = 1; i < totalFeatures; i++)
  {
    x = m_Centroids[3 * i];
    y = m_Centroids[3 * i + 1];
    z = m_Centroids[3 * i + 2];
  }
  for (size_t i = 1; i < totalFeatures; i++)
  {
    if (i % 1000 == 0)
    {

      QString ss = QObject::tr("Working On Feature %1 of %2").arg(i).arg(totalFeatures);
      notifyStatusMessage(ss);
    }
    x = m_Centroids[3 * i];
    y = m_Centroids[3 * i + 1];
    z = m_Centroids[3 * i + 2];
    for (size_t j = i + 1; j < totalFeatures; j++)
    {
      if (m_FeaturePhases[i] == m_FeaturePhases[j])
      {
        xn = m_Centroids[3 * j];
        yn = m_Centroids[3 * j + 1];
        zn = m_Centroids[3 * j + 2];
        r = sqrtf((x - xn) * (x - xn) + (y - yn) * (y - yn) + (z - zn) * (z - zn));
        clusteringlist[i].push_back(r);
        clusteringlist[j].push_back(r);

        if(writeErrorFile == true && m_FeaturePhases[j] == 2)
        {
          outFile << r << "\n" << r << "\n";
        }
      }
    }
  }
  for (size_t i = 1; i < totalFeatures; i++)
  {
    // Set the vector for each list into the Clustering Object
    NeighborList<float>::SharedVectorType sharedClustLst(new std::vector<float>);
    sharedClustLst->assign(clusteringlist[i].begin(), clusteringlist[i].end());
    m_ClusteringList->setList(static_cast<int>(i), sharedClustLst);
  }
}

