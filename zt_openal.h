/***************************************************************************************************************************************************************************************************
	file: zt_openal.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
***************************************************************************************************************************************************************************************************

	Zero Tolerance OpenAL Library

	In exactly one c/cpp source file of your project, you must:

	#define ZT_OPENAL_IMPLEMENTATION
	#include "zt_openal.h"

***************************************************************************************************************************************************************************************************

	Options:


***************************************************************************************************************************************************************************************************

	Implimentation Options: (only used with ZT_OPENAL_IMPLEMENTATION #include)


**************************************************************************************************/

#ifndef __zt_openal_h_included__
#define __zt_openal_h_included__

// ================================================================================================================================================================================================

#define ZT_OPENAL


// ================================================================================================================================================================================================

#include "zt_tools.h"


// ================================================================================================================================================================================================

enum ztOpenALContextError_Enum
{
	ztOpenALContextError_None,
	ztOpenALContextError_OpenDevice,
	ztOpenALContextError_MakeContext,
};

// ================================================================================================================================================================================================

struct ztOpenALContext;

ztOpenALContext *ztal_contextMake(ztOpenALContextError_Enum *error = nullptr);
void             ztal_contextFree(ztOpenALContext *context);

// ================================================================================================================================================================================================

enum ztOpenALBufferError_Enum
{
	ztOpenALBufferError_None,
	ztOpenALBufferError_NoFreeSlots,
	ztOpenALBufferError_CreateBuffer,
	ztOpenALBufferError_CopyData,
};

struct ztOpenALBuffer;

ztOpenALBuffer *ztal_bufferMake(ztOpenALContext *context, byte* audio_data, i32 audio_data_len, ztOpenALBufferError_Enum *error = nullptr);
void            ztal_bufferFree(ztOpenALBuffer *buffer);

void            ztal_bufferGetDetails(ztOpenALBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length);

void            ztal_bufferPlay(ztOpenALBuffer *buffer);
void            ztal_bufferPlayLooping(ztOpenALBuffer *buffer);
void            ztal_bufferStop(ztOpenALBuffer *buffer);

void            ztal_bufferSetVolume(ztOpenALBuffer *buffer, r32 volume);
void            ztal_bufferSetFrequency(ztOpenALBuffer *buffer, r32 frequency);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard

#if defined(ZT_OPENAL_IMPLEMENTATION) || defined(ZT_OPENAL_INTERNAL_DECLARATIONS)

#ifndef __zt_openal_h_internal_included__
#define __zt_openal_h_internal_included__

#include <AL/al.h>
#include <AL/alc.h>

// ================================================================================================================================================================================================

#ifndef ZT_OPENAL_SOURCES_PER_SOUND
#define ZT_OPENAL_SOURCES_PER_SOUND   3
#endif

#ifndef ZT_OPENAL_BUFFER_SIZE_CAP
#define ZT_OPENAL_BUFFER_SIZE_CAP zt_megabytes(1)
#endif

#if defined(ZT_OPENAL_DEBUGGING_LOGALL)
#	define ztal_callAndReturnOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztal_checkAndReportError(#function)) return;
#	define ztal_callAndReturnValOnError(function, retval) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztal_checkAndReportError(#function)) return retval;
#	define ztal_callAndReportOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztal_checkAndReportError(#function);
#else
#	if defined(ZT_EMSCRIPTEN) && !defined(ZT_OPENAL_DEBUGGING) // checking errors is too expensive here
#		define ztal_callAndReturnOnError(function) function;
#		define ztal_callAndReturnValOnError(function, retval) function;
#		define ztal_callAndReportOnError(function) function;
#	else
#		define ztal_callAndReturnOnError(function) function; if (ztal_checkAndReportError(#function)) return;
#		define ztal_callAndReturnValOnError(function, retval) function; if (ztal_checkAndReportError(#function)) return retval;
#		define ztal_callAndReportOnError(function) function; ztal_checkAndReportError(#function);
#	endif
#endif

#if defined(ZT_OPENAL_DEBUGGING)
#if defined(ZT_OPENAL_DEBUGGING_LOGALL)
#	define ztal_callAndReportOnErrorFast(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztal_checkAndReportError(#function);
#else
#	define ztal_callAndReportOnErrorFast(function) function; ztal_checkAndReportError(#function);
#endif
#else
#	define ztal_callAndReportOnErrorFast(function) function;
#endif


// ================================================================================================================================================================================================

struct WAVEFORMATEX
{
    u16 wFormatTag;
    u16 nChannels;
    u32 nSamplesPerSec;
    u32 nAvgBytesPerSec;
    u16 nBlockAlign;
    u16 wBitsPerSample;
    u16 cbSize;
};

// ================================================================================================================================================================================================

#define WAVE_FORMAT_PCM     1

// ================================================================================================================================================================================================

struct ztOpenALContext
{
	ALCdevice   *device                = nullptr;
	ALCcontext  *context               = nullptr;
};

// ================================================================================================================================================================================================

struct ztOpenALBuffer
{
	ztOpenALContext *context;

	ALuint           buffer;
	ALuint           sources     [ZT_OPENAL_SOURCES_PER_SOUND];
	bool             sources_used[ZT_OPENAL_SOURCES_PER_SOUND];
	i32              buffer_size;
	byte*            audio_data;
	
	WAVEFORMATEX     wave_fmt;
	i32              channels;
	i32              bits_per_sample;
	i32              samples_per_second;
	r32              length;

	i32              frequency;
};

// ================================================================================================================================================================================================

#endif // include guard
#endif // internal declarations

#if defined(ZT_OPENAL_IMPLEMENTATION)

// ================================================================================================================================================================================================

bool ztal_checkAndReportError(const char *function)
{
#	if defined(ZT_OPENAL_DEBUGGING_LOGALL)
	//zt_logDebug("Checking for errors after call to %s", function);
#	endif
	ALint error = alGetError();
	if (error != AL_NO_ERROR) {
		zt_logCritical("OpenAL: error from function %s: 0x%08x (%d)", function, error, error);
		return true;
	}
	
	return false;
}

// ================================================================================================================================================================================================

ztOpenALContext *ztal_contextMake(ztOpenALContextError_Enum *error)
{
	ztOpenALContext context = {};

	context.device = alcOpenDevice(nullptr);
	if (context.device == nullptr) {
		zt_logDebug("openal: Unable to open device");
		if (error) *error = ztOpenALContextError_OpenDevice;
		return nullptr;
	}
	
	context.context = alcCreateContext(context.device, NULL);
	if (context.context == nullptr) {
		zt_logDebug("openal: Unable to create context");
		if (error) *error = ztOpenALContextError_MakeContext;
		return nullptr;
	}
	
	ztal_callAndReportOnError(alcMakeContextCurrent(context.context));
	
	ztal_callAndReportOnError(alListener3f(AL_POSITION, 0, 0, 1.f));
	ztal_callAndReportOnError(alListener3f(AL_VELOCITY, 0, 0, 0));

	ALfloat listener_orient[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	ztal_callAndReportOnError(alListenerfv(AL_ORIENTATION, listener_orient));

	zt_logDebug("openal: Successfully initialized");

	ztOpenALContext *result = zt_mallocStruct(ztOpenALContext);
	*result = context;
	return result;
}

// ================================================================================================================================================================================================

void ztal_contextFree(ztOpenALContext *context)
{
	if (context == nullptr) {
		return;
	}

	ztal_callAndReportOnError(alcMakeContextCurrent(NULL));
	ztal_callAndReportOnError(alcDestroyContext(context->context));
	ztal_callAndReportOnError(alcCloseDevice(context->device));

	zt_free(context);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal bool _ztal_sourceFillNextSlot(ztOpenALBuffer *buffer, ztOpenALBufferError_Enum *error = nullptr)
{
	int didx = -1;
	zt_fize(buffer->sources) {
		if (buffer->sources_used[i] == false) {
			didx = i;
			break;
		}
	}
	
	if (didx == -1) {
		if(error) *error = ztOpenALBufferError_NoFreeSlots;
		return false;
	}

	ztal_callAndReturnValOnError(alGenSources((ALuint)1, &buffer->sources[didx]), false);
	
	zt_logDebug("openal: source: %d for buffer %d (index %d)", buffer->sources[didx], buffer->buffer, didx);
	
	buffer->sources_used[didx] = true;	

	ztal_callAndReportOnError(alSourcei (buffer->sources[didx], AL_BUFFER, buffer->buffer));
	ztal_callAndReportOnError(alSourcef (buffer->sources[didx], AL_PITCH, 1));
	ztal_callAndReportOnError(alSourcef (buffer->sources[didx], AL_GAIN, 1));
	ztal_callAndReportOnError(alSource3f(buffer->sources[didx], AL_POSITION, 0, 0, 0));
	ztal_callAndReportOnError(alSource3f(buffer->sources[didx], AL_VELOCITY, 0, 0, 0));
	ztal_callAndReportOnError(alSourcei (buffer->sources[didx], AL_LOOPING, AL_FALSE));

	return true;
}

// ================================================================================================================================================================================================

ztOpenALBuffer *ztal_bufferMake(ztOpenALContext *context, byte* audio_data, i32 audio_data_len, ztOpenALBufferError_Enum *error)
{
	zt_returnValOnNull(context, nullptr);
	zt_returnValOnNull(audio_data, nullptr);
	
	ztOpenALBuffer buffer = {};
	zt_memSet(&buffer, zt_sizeof(ztOpenALBuffer), 0);

	zt_fize(buffer.sources) {
		buffer.sources[i] = 0;
		buffer.sources_used[i] = false;
	}

	struct ztWaveFileHeader
	{
		char chunk_id[4];
		u32  chunk_size;
		char format[4];
	};

	struct ztWavChunkHeader
	{
		char chunk_id[4];
		u32  chunk_size;
	};

	struct ztWavChunkFormat
	{
		u16  audio_format;
		u16  num_channels;
		u32  sample_rate;
		u32  bytes_per_second;
		u16  block_align;
		u16  bits_per_sample;

		char padding[32];
	};

	struct local
	{
		static bool checkDataChunk(char *data_chunk, const char *compare_to, const char *error_message)
		{
		
			if (data_chunk[0] != compare_to[0] || data_chunk[1] != compare_to[1] || data_chunk[2] != compare_to[2] || data_chunk[3] != compare_to[3] ) {
				if (error_message) {
					zt_logDebug("%s", error_message);
				}
				return false;
			}
			return true;
		}
		
		static inline ALenum format(short channels, short samples)
		{
			bool stereo = channels > 1;

			switch (samples)
			{
				case 16: {
					return stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
				} break;
				
				case 8: {
					return stereo ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
				} break;
			}
			
			zt_logDebug("openal: invalid format.  channels: %d; samples: %d", channels, samples);
			
			return -1;
		}
	};

	ztWaveFileHeader wfh = {};
	if (audio_data_len < zt_sizeof(wfh)) {
		zt_logCritical("openal: Audio data length too short for wave header");
		return nullptr;
	}

	// todo: add support for ogg from stb libraries
	// todo: support streaming audio

	zt_memCpy(&wfh, zt_sizeof(wfh), audio_data, zt_sizeof(wfh));
	audio_data += zt_sizeof(wfh);
	audio_data_len -= zt_sizeof(wfh);

	if( !local::checkDataChunk(wfh.chunk_id,      "RIFF", "openal: Unsupported data chunk encountered") || 
		!local::checkDataChunk(wfh.format,        "WAVE", "openal: Unsupported wave format encountered") ) {
		//!local::checkDataChunk(wfh.sub_chunk_id,  "fmt ", "DirectSound: Unsupported sub chunk id encountered") ||
		//!local::checkDataChunk(wfh.data_chunk_id, "data", "DirectSound: Unsupported data chunk id encountered") ) {
		return nullptr;
	}

	ztWavChunkHeader wch;
	zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
	audio_data += zt_sizeof(wch);
	audio_data_len -= zt_sizeof(wch);

	bool found_fmt = false;
	int iterations = 0;
	while (++iterations < 12) {
		if (local::checkDataChunk(wch.chunk_id, "fmt ", nullptr)) {
			found_fmt = true;

			ztWavChunkFormat wcf;
			int size = zt_min(wch.chunk_size, zt_sizeof(wcf));
			zt_memCpy(&wcf, size, audio_data, audio_data_len);
			audio_data += size;
			audio_data_len -= size;
	
			if (wcf.audio_format != WAVE_FORMAT_PCM) {
				zt_logCritical("openal: Unsupported audio format encountered (only PCM supported)");
				return nullptr;
			}

			buffer.channels = wcf.num_channels;
			buffer.bits_per_sample = wcf.bits_per_sample;
			buffer.samples_per_second = wcf.sample_rate;

			zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
			audio_data += zt_sizeof(wch);
			audio_data_len -= zt_sizeof(wch);
		}
		else if (!local::checkDataChunk(wch.chunk_id, "data", nullptr)) { //&& !local::checkDataChunk(wch.chunk_id, "bext", nullptr)) {
			audio_data += wch.chunk_size;
			audio_data_len -= wch.chunk_size;

			zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
			audio_data += zt_sizeof(wch);
			audio_data_len -= zt_sizeof(wch);

			if (audio_data_len <= 0) {
				break;
			}
		}
		else break;
	}

	byte* data = audio_data;

	buffer.wave_fmt = {};
	buffer.wave_fmt.wFormatTag      = WAVE_FORMAT_PCM;
	buffer.wave_fmt.nChannels       = buffer.channels;
	buffer.wave_fmt.nSamplesPerSec  = buffer.samples_per_second;
	buffer.wave_fmt.wBitsPerSample  = buffer.bits_per_sample;
	buffer.wave_fmt.nBlockAlign     = buffer.wave_fmt.nChannels * (buffer.wave_fmt.wBitsPerSample / 8);
	buffer.wave_fmt.nAvgBytesPerSec = buffer.wave_fmt.nSamplesPerSec * buffer.wave_fmt.nBlockAlign;
	buffer.wave_fmt.cbSize          = 0;

	buffer.buffer_size = wch.chunk_size;

	if (wch.chunk_size <= ZT_OPENAL_BUFFER_SIZE_CAP) {
		buffer.audio_data = zt_mallocStructArray(byte, wch.chunk_size);
		zt_memCpy(buffer.audio_data, wch.chunk_size, data, wch.chunk_size);
		//zt_logDebug("Copying audio data into memory");
	}
	else {
		buffer.audio_data = (byte*)data;
		//zt_logDebug("Not copying audio data into memory (audio data is too large)");
	}
	
	zt_logDebug("openal: buffer data: %d format: %d  chunk_size: %d  samples_per_sec: %d", buffer.buffer, local::format(buffer.wave_fmt.nChannels, buffer.wave_fmt.wBitsPerSample), wch.chunk_size, buffer.wave_fmt.nSamplesPerSec);
	
	ztal_callAndReturnValOnError(alGenBuffers(1, &buffer.buffer), nullptr);
	ztal_callAndReturnValOnError(alBufferData(buffer.buffer, local::format(buffer.wave_fmt.nChannels, buffer.wave_fmt.wBitsPerSample), buffer.audio_data, wch.chunk_size, buffer.wave_fmt.nSamplesPerSec), nullptr);

	if (!_ztal_sourceFillNextSlot(&buffer, error)) {
		if (audio_data_len <= ZT_OPENAL_BUFFER_SIZE_CAP) {
			zt_free(buffer.audio_data);
		}
		return nullptr;
	}

	while (_ztal_sourceFillNextSlot(&buffer, error)) {
		;
	}

	ztOpenALBuffer *result = zt_mallocStruct(ztOpenALBuffer);
	*result = buffer;
	return result;
}

// ================================================================================================================================================================================================

void ztal_bufferFree(ztOpenALBuffer* buffer)
{
	if (buffer == nullptr) {
		return;
	}
	zt_fize(buffer->sources) {
		if (buffer->sources_used[i]) {
			ztal_callAndReportOnError(alDeleteSources(1, &buffer->sources[i]));
			buffer->sources_used[i] = false;
		}
	}

	ztal_callAndReportOnError(alDeleteBuffers(1, &buffer->buffer));
	
	if (buffer->buffer_size <= ZT_OPENAL_BUFFER_SIZE_CAP) {
		zt_free(buffer->audio_data);
	}
	zt_free(buffer);
}

// ================================================================================================================================================================================================

void ztal_bufferGetDetails(ztOpenALBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length)
{
	if(channels          ) *channels           = buffer->channels;
	if(bits_per_sample   ) *bits_per_sample    = buffer->bits_per_sample;
	if(samples_per_second) *samples_per_second = buffer->samples_per_second;
	if(length            ) *length             = (buffer->buffer_size / ((buffer->channels * buffer->bits_per_sample) / 8.f)) / (r32)buffer->samples_per_second;
}

// ================================================================================================================================================================================================

void ztal_bufferPlay(ztOpenALBuffer *buffer, bool loop)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->sources) {
		if(buffer->sources_used[i]) {
			ALint source_state = 0;
			ztal_callAndReportOnError(alGetSourcei(buffer->sources[i], AL_SOURCE_STATE, &source_state));
			
			if (source_state != AL_PLAYING) {
				ztal_callAndReportOnError(alSourcei (buffer->sources[i], AL_LOOPING, loop ? AL_TRUE : AL_FALSE));
				ztal_callAndReportOnError(alSourcePlay(buffer->sources[i]));
				return;
			}
		}
	}

	zt_fize(buffer->sources) {
		if(buffer->sources_used[i] == false) {
			_ztal_sourceFillNextSlot(buffer);
			ztal_bufferPlay(buffer, loop);
			return;
		}
	}

	// if we're here, we have no free buffers and need to just reset the buffer to play it
	if (buffer->sources_used[0]) {
		ztal_callAndReportOnError(alSourceStop(buffer->sources[0]));
		ztal_callAndReportOnError(alSourcePlay(buffer->sources[0]));
		return;
	}
}

// ================================================================================================================================================================================================

void ztal_bufferPlay(ztOpenALBuffer *buffer)
{
	ztal_bufferPlay(buffer, false);
}

// ================================================================================================================================================================================================

void ztal_bufferPlayLooping(ztOpenALBuffer *buffer)
{
	ztal_bufferPlay(buffer, true);
}

// ================================================================================================================================================================================================

void ztal_bufferStop(ztOpenALBuffer *buffer)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->sources) {
		if (buffer->sources_used[i]) {
			ztal_callAndReportOnError(alSourceStop(buffer->sources[i]));
		}
	}
}

// ================================================================================================================================================================================================

void ztal_bufferSetVolume(ztOpenALBuffer *buffer, r32 volume)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->sources) {
		if (buffer->sources_used[i]) {
			ztal_callAndReportOnError(alSourcef (buffer->sources[i], AL_GAIN, volume));
		}
	}
}

// ================================================================================================================================================================================================

void ztal_bufferSetFrequency(ztOpenALBuffer *buffer, r32 frequency)
{
	zt_returnOnNull(buffer);

}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // implementation
