/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Groeber (US Air Force Research Laboratories
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

#ifndef PHWRITER_HPP_
#define PHWRITER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>

/**
 * @class PhWriter PhWriter.h DREAM3D/Common/PhWriter.h
 * @brief This class writes a "Ph" file from the Grain Generator Data but is templated
 * so that possibly other classes can use this writing method. This code was adapted
 * from code supplied by S. Sintay and J. Tucker.
 * @author Michael A. Jackson for BlueQuartz Software
 * @date Jun 7, 2011
 * @version 1.0
 */
class PhWriter
{
  public:
    PhWriter()
    {
    }
    virtual ~PhWriter()
    {
    }

    template<typename T>
    int writeGrainPhFile(const std::string &filename, T &grain_index, int xpoints, int ypoints, int zpoints)
    {
      std::string OutputName;
      int totalpoints = xpoints * ypoints * zpoints;
      // Change the name of the input filename for outout
      // std::vector<std::string> tokens;
      // std::string delimeters = "."; // Only a period
      //  std::tokenize(filename, tokens, delimeters);

      //OutputName = tokens[0] + ".ph";
      std::ofstream outfile;
      outfile.open(filename.c_str());
      if(!outfile)
      {
        std::cout << "Failed to open: " << filename << std::endl;
        return -1;
      }

      // Find the unique number of grains
      std::map<int, bool> used;

      for (int i = 0; i < totalpoints; ++i)
      {
        used[grain_index[i]] = true;
      }

      int grains = 0;
      typedef std::map<int, bool>::iterator iterator;
      for (iterator i = used.begin(); i != used.end(); i++)
      {
        if((*i).second == true)
        {
          grains++;
        }
      }

      //std::cout<<grains<< " " << used.size() << std::endl;

      outfile << "     " << xpoints << "     " << ypoints << "     " << zpoints << "\n";
      outfile << "\'DREAM3\'              52.00  1.000  1.0       " << grains << "\n";
      outfile << " 3.000 0.000 0.000          0        \n"; // << grains << endl;

      int count = 0;
      for (int k = 0; k < totalpoints; k++)
      {
        outfile << std::setw(6) << grain_index[k];
        count++;
        if(count == 20)
        {
          outfile << "\n";
          count = 0;
        }
        //                    outfile << grid[i][j][k] << endl;
      }
      outfile << "\n";
      outfile.close();
      return 0;
    }

  private:
    PhWriter(const PhWriter&); // Copy Constructor Not Implemented
    void operator=(const PhWriter&); // Operator '=' Not Implemented
};

#endif /* PHWRITER_HPP_ */
