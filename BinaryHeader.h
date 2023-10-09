#pragma once

#include "DataStream.h"
#include <fstream>

class BinaryHeader
{
private:
    int m_jobIDNumber{}; // 1 - 4
    int m_lineNumber{}; // 5 - 8
    int m_reelNumber{}; // 9 - 12
    short m_numberOfDataTracesPerRecord{}; // 13 - 14
    short m_numberOfAuxTracesPerRecord{}; // 15 - 16
    short m_reelSampleInterval{}; // 17 - 18
    short m_fieldSampleInterval{}; // 19 - 20
    short m_numberOfSamplesForReel{}; // 21 - 22
    short m_numberOfSamplesForField{}; // 23 - 24
    short m_dataSampleFormatCode{}; // 25 - 26
    short m_cdpFold{}; // 27 - 28
    short m_traceSortingCode{}; // 29 - 30
    short m_verticalSumCode{}; // 31 - 32
    short m_sweepFrequencyStart{}; // 33 - 34
    short m_sweepFrequencyEnd{}; // 35 - 36
    short m_sweepLength{}; // 37 - 38
    short m_sweepTypeCode{}; // 39 - 40
    short m_traceNumberOfSweepChannel{}; // 41 - 42
    short m_sweepTraceTaperLengthStart{}; // 43 - 44
    short m_sweepTraceTaperLengthEnd{}; // 45 - 46
    short m_taperType{}; // 47 - 48
    short m_correlatedDataTraces{}; // 49 - 50
    short m_binaryGainRecovered{}; // 51 - 52
    short m_amplitudeRecoveryMethod{}; // 53 - 54
    short m_measurementSystem{}; // 55 - 56
    short m_impulseSignal{}; // 57 - 58
    short m_vibratoryPolarityCode{}; // 59 - 60
    short m_padding1{}; // 61 - 62
    int m_sscSEGYSamplesNumber{}; // 63 - 66
    char m_padding2[234]{}; // 67 - 300
    short m_segyRevision{}; // 301 - 302
    short m_fixedTraceFlag{}; // 303 - 304
    short m_numberOfExtendedTextualHeaders{}; // 305 - 306
    char m_padding3[94]{}; // 307 - 400

public:
    BinaryHeader() = default;
    virtual ~BinaryHeader() = default;

    void Unmarshal(DataStream& dataStream, size_t& readPosition);
    void WriteHeader(std::ofstream& stream) const;

    short GetNumberOfDataTracesForReel() const;
    short GetNumberOfExtendedTextualHeaders() const;
    short GetSampleInterval() const;
};