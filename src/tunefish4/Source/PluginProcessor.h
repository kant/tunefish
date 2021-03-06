/*
 ---------------------------------------------------------------------
 Tunefish 4  -  http://tunefish-synth.com
 ---------------------------------------------------------------------
 This file is part of Tunefish.

 Tunefish is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Tunefish is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Tunefish.  If not, see <http://www.gnu.org/licenses/>.
 ---------------------------------------------------------------------
 */

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#define eVSTI

#include "../JuceLibraryCode/JuceHeader.h"
#include "runtime/system.hpp"
#include "tfsynthprogram.hpp"
#include "synth/tf4.hpp"

const eU32 TF_PLUG_NUM_PROGRAMS = 1000;


//==============================================================================
/**
 */
class Tunefish4AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Tunefish4AudioProcessor();
    ~Tunefish4AudioProcessor();

    //==============================================================================
    void                    prepareToPlay (double sampleRate, int samplesPerBlock);
    void                    releaseResources();

    void                    processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void                    processEvents(MidiBuffer &midiMessages, eU32 messageOffset, eU32 frameSize);

    //==============================================================================
    AudioProcessorEditor*   createEditor();
    bool                    hasEditor() const;

    //==============================================================================
    const String            getName() const;

    int                     getNumParameters();

    float                   getParameterMod(int index);

    float                   getParameter (int index);
    void                    setParameter (int index, float newValue);

    const String            getParameterName (int index);
    const String            getParameterText (int index);

    const String            getInputChannelName (int channelIndex) const;
    const String            getOutputChannelName (int channelIndex) const;
    bool                    isInputChannelStereoPair (int index) const;
    bool                    isOutputChannelStereoPair (int index) const;

    bool                    acceptsMidi() const;
    bool                    producesMidi() const;
    bool                    silenceInProducesSilenceOut() const;
    double                  getTailLengthSeconds() const;

    //==============================================================================
    int                     getNumPrograms();
    int                     getCurrentProgram();
    void                    setCurrentProgram (int index);
    const String            getProgramName (int index);
    void                    changeProgramName (int index, const String& newName);

    eTfSynth *              getSynth() const;
    CriticalSection &       getSynthCriticalSection();

    //==============================================================================
    void                    getStateInformation (MemoryBlock& destData);
    void                    setStateInformation (const void* data, int sizeInBytes);

    void                    writeProgramToPresets();
    void                    loadProgramFromPresets();
    bool                    loadProgram();
    bool                    loadProgram(eU32 index);
    bool                    loadProgramAll();
    bool                    saveProgram();
    bool                    saveProgram(eU32 index);
    bool                    saveProgramAll();
    bool                    copyProgram();
    bool                    pasteProgram();

    bool                    isParamDirty(eU32 index);
    bool                    wasProgramSwitched() const;
    void                    resetParamDirty(eBool dirty = eFALSE);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tunefish4AudioProcessor)

    eTfInstrument *         tf;
    eTfSynth *              synth;
    eTfSynthProgram         programs[TF_PLUG_NUM_PROGRAMS];
    eBool                   paramDirty[TF_PARAM_COUNT];
    eBool                   programSwitched;
    eTfSynthProgram         currentProgram;
    eTfSynthProgram         copiedProgram;
    eU32                    currentProgramIndex;
    String                  pluginLocation;
    CriticalSection         csSynth;
    eS32                    recorderIndex;

    eF32 *                  adapterBuffer[2];
    eU32                    adapterWriteOffset;
    eU32                    adapterDataAvailable;
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
