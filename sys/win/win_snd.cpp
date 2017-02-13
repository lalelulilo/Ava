/* Windows WASAPI Interface */

#include <assert.h>

#include "win_local.h"

#define BITS_IN_BYTE    8

int Sound_FillSoundBuffer( BYTE *sourceBuffer, uint32_t samplesToWrite ) {
    HRESULT hr = S_OK;
    XAUDIO2_BUFFER soundBuffer = { 0 };

    /* TODO(szucs): The audio data must exist until the audio is finished playing,
       thus we should probably have a static buffer here, and copy over the audio data
       instead of just pointing straight to it */
    soundBuffer.AudioBytes = samplesToWrite;
    soundBuffer.pAudioData = sourceBuffer;

    if ( FAILED( hr = win32.sourceVoice->SubmitSourceBuffer( &soundBuffer ) ) ) {
        // TODO(szucs): log this failure
        return hr;
    }

    return hr;
}

int Sound_Init( int samplesPerSecond ) {
    HRESULT hr = S_OK;
    WAVEFORMATEX waveFormat;

    // Grab XAudio2 engine
    if ( FAILED( hr = XAudio2Create( &win32.soundEngine, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) ) {
        // TODO(szucs): log this failure
        return hr;
    }

    // Create the mastering voice
    if ( FAILED ( hr = win32.soundEngine->CreateMasteringVoice( &win32.masterVoice ) ) ) {
        // TODO(szucs): log this failure
        return hr;
    }

    /* Format we'll be using to output audio, we may want to
       make this more configurable in the future
    */
    waveFormat.cbSize = 0;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.wBitsPerSample = sizeof(int16_t) * BITS_IN_BYTE;
    waveFormat.nChannels = 2;
    waveFormat.nSamplesPerSec = samplesPerSecond;
    waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.wBitsPerSample * waveFormat.nChannels / BITS_IN_BYTE;

    // Create the source voice
    if ( FAILED( hr = win32.soundEngine->CreateSourceVoice( &win32.sourceVoice, &waveFormat ) ) ) {
        // TODO(szucs): log this failure
        return hr;
    }

    if ( FAILED( hr = win32.sourceVoice->Start( 0 ) ) ) {
        // TODO(szucs): log this failure
        return hr;
    }

    return hr;
}
