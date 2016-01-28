
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
                            sInput2TxtPath;
    
    float                   **inputAudioData    = 0,
                            **outputAudioData   = 0,
                            **ppfAudioData      = 0;
    
    static const int        blockSize           = 1024;
    int                     type                = 0;//what is this?  

    clock_t                 time                = 0;

    float                   delayTimeInSec      = 0.0,
                            gain                = 0.0;
    CMyProject              *filter             = 0;
    Error_t                 error_check;

    CAudioFileIf            *phAudioFile        = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;
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
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::FileIoType_t::kFileRead);
    sOutputFilePath = sInputFilePath + "output.txt";
    sInput2TxtPath = sInputFilePath + "input.txt";
    outfile.open(sOutputFilePath);
    infile.open(sInput2TxtPath);
    
    CAudioFileIf::FileSpec_t spec;
    phAudioFile->getFileSpec(spec);
    
    inputAudioData = new float*[spec.iNumChannels];
    outputAudioData = new float*[spec.iNumChannels];
    
    for(int i = 0; i < spec.iNumChannels; i++)
    {
        inputAudioData[i] = new float[blockSize];
        outputAudioData[i] = new float[blockSize];
    }
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
    
    error_check = CMyProject::create(filter, type, delayTimeInSec, gain, spec.fSampleRateInHz, spec.iNumChannels);
    if (error_check == kFunctionIllegalCallError)
        cout << "Illegal filter type, use 0 for FIR and 1 for IIR"<<endl;
    else if (error_check == kFunctionInvalidArgsError)
        cout << "Invalid filter parameters used. Delay should be positive and Gain should be between -1 and +1."<<endl;
    
    cout << "Processing....." << endl;
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = blockSize;
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
    
    cout << "Exited" << endl;
    
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
    cout << "(c) 2016 by Hua & Siyuan" << endl;
    cout  << endl;

    return;
}

