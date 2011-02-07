/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
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
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef OIMIMPORTWIDGET_H_
#define OIMIMPORTWIDGET_H_

#include <QtCore/QString>
#include <QtCore/QSettings>

#include "ui_OIMImportWidget.h"
#include <AIM/GUI/AIMPluginFrame.h>
#include <AIM/ANG/H5AngImporter.h>


/*
 *
 */
class OIMImportWidget : public AIMPluginFrame, private Ui::OIMImportWidget
{
  Q_OBJECT;

  public:
    OIMImportWidget(QWidget *parent = 0);
    virtual ~OIMImportWidget();

    /**
      * @brief Reads the Preferences from the users pref file
      */
    virtual void readSettings(QSettings &prefs);

     /**
      * @brief Writes the preferences to the users pref file
      */
    virtual void writeSettings(QSettings &prefs);

    /**
     * @brief Enables or Disables all the widgets in a list
     * @param b
     */
    virtual void setWidgetListEnabled(bool b);

    /**
     * @brief Initializes some of the GUI elements with selections or other GUI related items
     */
    virtual void setupGui();


    virtual void checkIOFiles();

    /**
     * @brief Method to attempt the extraction of the .ang max slice value and prefix
     */
    void oim_findAngMaxSliceAndPrefix();
    void oim_generateExampleOimInputFile();

  protected slots:
    /* OIM Data Import Slots */
    void on_oim_InputDirBtn_clicked();
    void on_oim_OutputFileBtn_clicked();
    void on_oim_GoBtn_clicked();

    void on_oim_FilePrefix_textChanged(const QString &string);
    void on_oim_FileSuffix_textChanged(const QString &string);
    void on_oim_FileExt_textChanged(const QString &string);
    void on_oim_TotalDigits_valueChanged(int value);
    void on_oim_ZStartIndex_valueChanged(int value);
    void on_oim_ZEndIndex_valueChanged(int value);

    // slots to catch signals emittd by the various QLineEdit widgets
    void on_oim_InputDir_textChanged(const QString & text);
    void on_oim_OutputFile_textChanged(const QString & text);

  private slots:
    // slots for our worker thread to communicate
    virtual void threadHasMessage(QString message);

    /* Reconstruction Thread communicates throught these methods */
    virtual void threadFinished();
    virtual void threadProgressed(int value);

  private:
    QList<QWidget*>             m_WidgetList;
    H5AngImporter::Pointer      m_H5AngImporter;
    QThread*                    m_WorkerThread;

    QString m_OpenDialogLastDirectory;
    OIMImportWidget(const OIMImportWidget&); // Copy Constructor Not Implemented
    void operator=(const OIMImportWidget&); // Operator '=' Not Implemented
};

#endif /* OIMIMPORTWIDGET_H_ */
