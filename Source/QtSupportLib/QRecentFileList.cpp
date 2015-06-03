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


#include "QRecentFileList.h"

#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtWidgets/QMenu>


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QRecentFileList::QRecentFileList(QObject* parent) :
  QObject(parent)
{
  //qDebug() << "QRecentFileList()" << "\n";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QRecentFileList::~QRecentFileList()
{
// qDebug() << "~QRecentFileList()" << "\n";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QRecentFileList* QRecentFileList::instance()
{
// qDebug() << "QRecentFileList::instance()" << "\n";
  static QRecentFileList* singleton;

  if (singleton == NULL)
  {
    singleton = new QRecentFileList();
  }
  return singleton;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool QRecentFileList::contains(const QString& file)
{
  return this->recentFiles.contains(file);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::addFile(const QString& file, AddType type)
{
  //qDebug() << "QRecentFileList::addFile()" << "\n";
  //qDebug() << "recentFiles.count: " << recentFiles.count() << "\n";
  if (QFile::exists(file) == true)
  {
    if (this->recentFiles.contains(file) == false)
    {
      if (type == APPEND)
      {
        this->recentFiles.append(file);
      }
      else if (type == PREPEND)
      {
        this->recentFiles.prepend(file);
      }
      emit fileListChanged(file); // Emit the signal so all the menus can update thier contents
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QStringList QRecentFileList::fileList()
{
  return this->recentFiles;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::popBack()
{
  this->recentFiles.pop_back();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::removeFile(const QString& file)
{
  //qDebug() << "QRecentFileList::removeFile()" << "\n";
  this->recentFiles.removeAll(file);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::clear()
{
  this->recentFiles.clear();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::writeList(DREAM3DSettings& prefs)
{
  prefs.setValue("Recent Files", this->fileList());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QRecentFileList::readList(DREAM3DSettings& prefs)
{
  this->clear();

  QStringList list = prefs.value("Recent Files", QStringList());

  for (int i = 0; i < list.size(); i++)
  {
    QString filePath = list[i];
    QFile file(filePath);
    if (file.exists())
    {
      this->addFile(filePath, APPEND);
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString QRecentFileList::strippedName(const QString& fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString QRecentFileList::parentAndFileName(const QString& file)
{
  QFileInfo fileinfo(file);

  QDir parent = fileinfo.dir();
  return parent.dirName() + QDir::separator() + fileinfo.fileName();
}

