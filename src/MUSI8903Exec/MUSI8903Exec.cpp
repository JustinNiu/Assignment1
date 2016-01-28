
#include <iostream>
#include <ctime>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>

#include "PROJECT1Config.h"
#include "MUSI8903Config.h"

#include "AudioFileIf.h"
#include "MyProject.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath,
                            outputTxtPath;
    
    float                   **inputAudioData    = 0,
                            **outputAudioData   = 0;
    
    static const int        kBlockSize           = 1024;
    int                     type                = 0;//what is this?


    float                   delayTimeInSec      = 0.0,
                            gain                = 0.0;
    CMyProject              *filter             = 0;
    Error_t                 error_check;

    CAudioFileIf            *phAudioFile        = 0;
    std::fstream            hOutputFile;
    std::ofstream           outfile,infile;


    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    if (argc < 2)
    {
        return -1;
    }
    else
    {
        sInputFilePath  = argv[1];
        sOutputFilePath = sInputFilePath + ".txt";
    }

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file

    //point to the object
    CAudioFileIf::create(phAudioFile);
    
    //open file
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::FileIoType_t::kFileRead);

    sOutputFilePath = sInputFilePath + "output.txt";
    outputTxtPath = sInputFilePath + "input.txt";
    outfile.open(sOutputFilePath);
    infile.open(outputTxtPath);
    
    CAudioFileIf::FileSpec_t spec;
    phAudioFile->getFileSpec(spec);
    
    //allocate memory for pointers for input and output
    inputAudioData = new float*[spec.iNumChannels];
    outputAudioData = new float*[spec.iNumChannels];
    
    //point all the pointers in each channel to corresponding blocks
    for(int i = 0; i < spec.iNumChannels; i++)
    {
        inputAudioData[i] = new float[kBlockSize];
        outputAudioData[i] = new float[kBlockSize];
    }
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
    
    error_check = CMyProject::create(filter, type, delayTimeInSec, gain, spec.fSampleRateInHz, spec.iNumChannels);
    
    //process audio until reach the end of the file
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(inputAudioData, iNumFrames);
        filter->filtering(inputAudioData, outputAudioData, iNumFrames);
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int j = 0; j < spec.iNumChannels; j++)
            {
                outfile << outputAudioData[j][i] << " ";
                infile << inputAudioData[j][i] << " ";
            }
            outfile << endl;
            infile << endl;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    outfile.close();
    infile.close();
    
    for (int i = 0; i < spec.iNumChannels; i++)
    {
        delete[] inputAudioData[i];
        delete[] outputAudioData[i];
    }
    delete[] inputAudioData;
    delete[] outputAudioData;
    
    CAudioFileIf::destroy(phAudioFile);
    CMyProject::destroy(filter);
}


void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Siyuan & Hua" << endl;
    cout  << endl;

    return;
}

