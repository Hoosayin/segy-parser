#include "BinaryHeader.h"

void BinaryHeader::Unmarshal(DataStream &dataStream, size_t& readPosition)
{
    dataStream.ReadBytes(m_jobIDNumber, readPosition);
    dataStream.ReadBytes(m_lineNumber, readPosition);
    dataStream.ReadBytes(m_reelNumber, readPosition);
    dataStream.ReadBytes(m_numberOfDataTracesPerRecord, readPosition);
    dataStream.ReadBytes(m_numberOfAuxTracesPerRecord, readPosition);
    dataStream.ReadBytes(m_reelSampleInterval, readPosition);
    dataStream.ReadBytes(m_fieldSampleInterval, readPosition);
    dataStream.ReadBytes(m_numberOfSamplesForReel, readPosition);
    dataStream.ReadBytes(m_numberOfSamplesForField, readPosition);
    dataStream.ReadBytes(m_dataSampleFormatCode, readPosition);
    dataStream.ReadBytes(m_cdpFold, readPosition);
    dataStream.ReadBytes(m_traceSortingCode, readPosition);
    dataStream.ReadBytes(m_verticalSumCode, readPosition);
    dataStream.ReadBytes(m_sweepFrequencyStart, readPosition);
    dataStream.ReadBytes(m_sweepFrequencyEnd, readPosition);
    dataStream.ReadBytes(m_sweepLength, readPosition);
    dataStream.ReadBytes(m_sweepTypeCode, readPosition);
    dataStream.ReadBytes(m_traceNumberOfSweepChannel, readPosition);
    dataStream.ReadBytes(m_sweepTraceTaperLengthStart, readPosition);
    dataStream.ReadBytes(m_sweepTraceTaperLengthEnd, readPosition);
    dataStream.ReadBytes(m_taperType, readPosition);
    dataStream.ReadBytes(m_correlatedDataTraces, readPosition);
    dataStream.ReadBytes(m_binaryGainRecovered, readPosition);
    dataStream.ReadBytes(m_amplitudeRecoveryMethod, readPosition);
    dataStream.ReadBytes(m_measurementSystem, readPosition);
    dataStream.ReadBytes(m_impulseSignal, readPosition);
    dataStream.ReadBytes(m_vibratoryPolarityCode, readPosition);
    dataStream.ReadBytes(m_padding1, readPosition);
    dataStream.ReadBytes(m_sscSEGYSamplesNumber, readPosition);
    dataStream.ReadBytes(m_padding2, 234, readPosition);
    dataStream.ReadBytes(m_segyRevision, readPosition);
    dataStream.ReadBytes(m_fixedTraceFlag, readPosition);
    dataStream.ReadBytes(m_numberOfExtendedTextualHeaders, readPosition);
    dataStream.ReadBytes(m_padding3, 94, readPosition);
}

void BinaryHeader::WriteHeader(std::ofstream& stream) const
{
    stream << std::endl << std::endl
        << "BINARY HEADER" << std::endl;

    stream << "[1 - 4]       Job ID Number:                              " << m_jobIDNumber << std::endl;
    stream << "[5 - 8]       Line Number:                                " << m_lineNumber << std::endl;
    stream << "[9 - 12]      Reel Number:                                " << m_reelNumber << std::endl;
    stream << "[13 - 14]     Number of Data Traces Per Record:           " << m_numberOfDataTracesPerRecord << std::endl;
    stream << "[15 - 16]     Number of Aux Traces Per Record:            " << m_numberOfAuxTracesPerRecord << std::endl;
    stream << "[17 - 18]     Sample Interval for Reel:                   " << m_reelSampleInterval << std::endl;
    stream << "[19 - 20]     Sample Interval for Field:                  " << m_fieldSampleInterval << std::endl;
    stream << "[21 - 22]     Number of Samples for Reel:                 " << m_numberOfSamplesForReel << std::endl;
    stream << "[23 - 24]     Number of Samples for Field:                " << m_numberOfSamplesForField << std::endl;
    stream << "[25 - 26]     Data Sample Format Code:                    " << m_dataSampleFormatCode << std::endl;
    stream << "[27 - 28]     CDP Fold:                                   " << m_cdpFold << std::endl;
    stream << "[29 - 30]     Trace Sorting Code:                         " << m_traceSortingCode << std::endl;
    stream << "[31- 32]      Vertical Sum Code:                          " << m_verticalSumCode << std::endl;
    stream << "[33 - 34]     Sweep Frequency at Start:                   " << m_sweepFrequencyStart << std::endl;
    stream << "[35 - 36]     Sweep Frequency at End:                     " << m_sweepFrequencyEnd << std::endl;
    stream << "[37 - 38]     Sweep Length:                               " << m_sweepLength << std::endl;
    stream << "[39 - 40]     Sweep Type Code:                            " << m_sweepTypeCode << std::endl;
    stream << "[41 - 42]     Trace Number of Sweep Channel:              " << m_traceNumberOfSweepChannel << std::endl;
    stream << "[43 - 44]     Sweep Trace Taper Length at Start:          " << m_sweepTraceTaperLengthStart << std::endl;
    stream << "[45 - 46]     Sweep Trace Taper Length at End:            " << m_sweepTraceTaperLengthEnd << std::endl;
    stream << "[47 - 48]     Taper Type:                                 " << m_taperType << std::endl;
    stream << "[49 - 50]     Correlated Data Traces:                     " << m_correlatedDataTraces << std::endl;
    stream << "[51 - 52]     Binary Gain Recovered:                      " << m_binaryGainRecovered << std::endl;
    stream << "[53 - 54]     Amlitude Recovery Method:                   " << m_amplitudeRecoveryMethod << std::endl;
    stream << "[55 - 56]     Measurement System:                         " << m_measurementSystem << std::endl;
    stream << "[57 - 58]     Impulse Signal:                             " << m_impulseSignal << std::endl;
    stream << "[59 - 60]     Vibratory Polarity Code:                    " << m_vibratoryPolarityCode << std::endl;
    stream << "[61 - 62]     Unused:                                     " << "0" << std::endl;
    stream << "[63 - 66]     SSC SEGY Samples Number:                    " << m_sscSEGYSamplesNumber << std::endl;
    stream << "[67 - 300]    Unused:                                     " << "0" << std::endl;
    stream << "[301 - 302]   SEGY Revision:                              " << m_segyRevision << std::endl;
    stream << "[303 - 304]   Fixed Trace Flag:                           " << m_fixedTraceFlag << std::endl;
    stream << "[305- 306]    Number of Extended Textual Headers:         " << m_numberOfExtendedTextualHeaders << std::endl;
    stream << "[307 - 400]   Unused:                                     " << "0" << std::endl;
}

short BinaryHeader::GetNumberOfDataTracesForReel() const
{
    return m_numberOfSamplesForReel;
}

short BinaryHeader::GetNumberOfExtendedTextualHeaders() const
{
    return m_numberOfExtendedTextualHeaders;
}

short BinaryHeader::GetSampleInterval() const
{
    return m_reelSampleInterval;
}
