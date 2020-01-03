// License: BSD 2 Clause
// Copyright (C) 2010, Google Inc. All rights reserved.
// Copyright (C) 2015+, The LabSound Authors. All rights reserved.

#ifndef AudioDestinationNode_h
#define AudioDestinationNode_h

#include "LabSound/core/AudioNode.h"
#include "LabSound/core/AudioIOCallback.h"


namespace lab {

class AudioBus;
class AudioContext;
class AudioSourceProvider;
class LocalAudioInputProvider;

class AudioDestinationNode : public AudioNode, public AudioIOCallback 
{
    class LocalAudioInputProvider;
    LocalAudioInputProvider * m_localAudioInputProvider;

public:

    AudioDestinationNode(AudioContext * context, size_t channelCount, float sampleRate);
    virtual ~AudioDestinationNode();
    
    // AudioNode   
    virtual void process(ContextRenderLock&) override { } // DestinationNode is pulled by hardware so this is never called
    virtual void reset(ContextRenderLock &) override;
    
    // The audio hardware calls render() to get the next render quantum of audio into destinationBus.
    // It will optionally give us local/live audio input in sourceBus (if it's not 0).
    virtual void render(AudioBus * sourceBus, AudioBus * destinationBus, size_t numberOfFrames) override;

    uint64_t currentSampleFrame() const;
    double currentTime() const;
    double currentSampleTime() const; // extrapolated exact time

    virtual size_t numberOfChannels() const { return m_channelCount; }

    virtual void startRendering() = 0;

    float sampleRate() const { return m_sampleRate; }

    AudioSourceProvider * localAudioInputProvider();
    
protected:

    virtual double tailTime(ContextRenderLock & r) const override { return 0; }
    virtual double latencyTime(ContextRenderLock & r) const override { return 0; }

    float m_sampleRate;
    AudioContext * m_context;

private:
};

} // namespace lab

#endif // AudioDestinationNode_h
