/***************************************************************************************************************************************************************************************************
	file: zt_opensl.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
***************************************************************************************************************************************************************************************************

	Zero Tolerance OpenSL Library

	In exactly one c/cpp source file of your project, you must:

	#define ZT_OPENSL_IMPLEMENTATION
	#include "zt_opensl.h"

***************************************************************************************************************************************************************************************************

	Options:


***************************************************************************************************************************************************************************************************

	Implimentation Options: (only used with ZT_OPENSL_IMPLEMENTATION #include)


**************************************************************************************************/

#ifndef __zt_opensl_h_included__
#define __zt_opensl_h_included__

// ================================================================================================================================================================================================

#define ZT_OPENSL


// ================================================================================================================================================================================================

#include "zt_tools.h"


// ================================================================================================================================================================================================

enum ztOpenSLContextError_Enum
{
	ztOpenSLContextError_None,
	ztOpenSLContextError_OpenDevice,
	ztOpenSLContextError_MakeContext,
};

// ================================================================================================================================================================================================

struct ztOpenSLContext;

ztOpenSLContext *ztsl_contextMake(ztOpenSLContextError_Enum *error = nullptr);
void             ztsl_contextFree(ztOpenSLContext *context);

void             ztsl_contextPauseAll(ztOpenSLContext *context);
void             ztsl_contextResumeAll(ztOpenSLContext *context);


// ================================================================================================================================================================================================

enum ztOpenSLBufferError_Enum
{
	ztOpenSLBufferError_None,
	ztOpenSLBufferError_NoFreeSlots,
	ztOpenSLBufferError_CreateAudioPlayer,
	ztOpenSLBufferError_RealizeAudioPlayer,
	ztOpenSLBufferError_GetPlayerInterface,
	ztOpenSLBufferError_GetVolumeInterface,
	ztOpenSLBufferError_GetBufferQueueInterface,
	ztOpenSLBufferError_RegisterPlayerCallback,
	ztOpenSLBufferError_SetCallbackEventsMask,
	ztOpenSLBufferError_CopyData,
};

struct ztOpenSLBuffer;

ztOpenSLBuffer *ztsl_bufferMake(ztOpenSLContext *context, byte* audio_data, i32 audio_data_len, ztOpenSLBufferError_Enum *error = nullptr);
void            ztsl_bufferFree(ztOpenSLBuffer *buffer);

void            ztsl_bufferGetDetails(ztOpenSLBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length);

void            ztsl_bufferPlay(ztOpenSLBuffer *buffer);
void            ztsl_bufferPlayLooping(ztOpenSLBuffer *buffer);
void            ztsl_bufferStop(ztOpenSLBuffer *buffer);

void            ztsl_bufferSetVolume(ztOpenSLBuffer *buffer, r32 volume);
void            ztsl_bufferSetFrequency(ztOpenSLBuffer *buffer, r32 frequency);


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

#if defined(ZT_OPENSL_IMPLEMENTATION) || defined(ZT_OPENSL_INTERNAL_DECLARATIONS)

#ifndef __zt_opensl_h_internal_included__
#define __zt_opensl_h_internal_included__

#include <SLES/OpenSLES.h>

#if defined(ZT_ANDROID)
#include <SLES/OpenSLES_Android.h>
#endif

// ================================================================================================================================================================================================

#ifndef ZT_OPENSL_SOURCES_PER_SOUND
#define ZT_OPENSL_SOURCES_PER_SOUND   1
#endif

#ifndef ZT_OPENSL_MAX_BUFFERS
#define ZT_OPENSL_MAX_BUFFERS 256
#endif

#if defined(ZT_OPENSL_DEBUGGING_LOGALL)
#	define ztsl_callAndReturnOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztsl_checkAndReportError(#function)) return;
#	define ztsl_callAndReturnValOnError(function, retval) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztsl_checkAndReportError(#function)) return retval;
#	define ztsl_callAndReportOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztsl_checkAndReportError(#function);
#else
#	if defined(ZT_EMSCRIPTEN) && !defined(ZT_OPENSL_DEBUGGING) // checking errors is too expensive here
#		define ztsl_callAndReturnOnError(function) function;
#		define ztsl_callAndReturnValOnError(function, retval) function;
#		define ztsl_callAndReportOnError(function) function;
#	else
#		define ztsl_callAndReturnOnError(function) function; if (ztsl_checkAndReportError(#function)) return;
#		define ztsl_callAndReturnValOnError(function, retval) function; if (ztsl_checkAndReportError(#function)) return retval;
#		define ztsl_callAndReportOnError(function) function; ztsl_checkAndReportError(#function);
#	endif
#endif

#if defined(ZT_OPENSL_DEBUGGING)
#if defined(ZT_OPENSL_DEBUGGING_LOGALL)
#	define ztsl_callAndReportOnErrorFast(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztsl_checkAndReportError(#function);
#else
#	define ztsl_callAndReportOnErrorFast(function) function; ztsl_checkAndReportError(#function);
#endif
#else
#	define ztsl_callAndReportOnErrorFast(function) function;
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

struct ztOpenSLContext;

// ================================================================================================================================================================================================

enum ztOpenSLBufferPlayState_Enum
{
	ztOpenSLBufferPlayState_Idle,
	ztOpenSLBufferPlayState_Playing,
	ztOpenSLBufferPlayState_NeedsStopped,

	ztOpenSLBufferPlayState_MAX,
};

// ================================================================================================================================================================================================

struct ztOpenSLBuffer
{
	
	struct SLObjects
	{	
		SLObjectItf                   object;
		SLPlayItf                     play;
		SLVolumeItf                   volume;
		SLAndroidSimpleBufferQueueItf simple_buffer_queue;
		ztOpenSLBufferPlayState_Enum  play_state;
	};
	
	SLObjects objects     [ZT_OPENSL_SOURCES_PER_SOUND];
	bool      objects_used[ZT_OPENSL_SOURCES_PER_SOUND];

	void* audio_data;
	int32 audio_data_len;

	WAVEFORMATEX     wave_fmt;
	i32              channels;
	i32              bits_per_sample;
	i32              samples_per_second;
	r32              length;

	i32              frequency;
	
	ztOpenSLContext *context;


	ztOpenSLBuffer *next;
};

// ================================================================================================================================================================================================

struct ztOpenSLContext
{
	SLObjectItf      sl_object;
	SLEngineItf      sl_engine;
	SLObjectItf      sl_output_mix;

	ztOpenSLBuffer  *buffers;
};

// ================================================================================================================================================================================================

#endif // include guard
#endif // internal declarations

#if defined(ZT_OPENSL_IMPLEMENTATION)

// ================================================================================================================================================================================================

bool ztsl_checkAndReportError(const char *function)
{
	return false;
}

// ================================================================================================================================================================================================

ztOpenSLContext *ztsl_contextMake(ztOpenSLContextError_Enum *error)
{
	ztOpenSLContext *context = zt_mallocStruct(ztOpenSLContext);

	context->sl_object = nullptr;
	context->sl_engine = nullptr;

	slCreateEngine(&context->sl_object, 0, nullptr, 0, nullptr, nullptr);
	if (context->sl_object == nullptr) {
		zt_logCritical("opensl: unable to create engine");
		zt_free(context);
		return nullptr;
	}

	(*context->sl_object)->Realize(context->sl_object, SL_BOOLEAN_FALSE);
	if ((*context->sl_object)->GetInterface(context->sl_object, SL_IID_ENGINE, &context->sl_engine) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: unable to get engine interface");
		zt_free(context);
		return nullptr;
	}

	//SLVolumeItf sl_output_vol;

	zt_logCritical("opensl: creating output mix");
	if ((*context->sl_engine)->CreateOutputMix(context->sl_engine, &context->sl_output_mix, 0, nullptr, nullptr) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: unable to get output interface");
		zt_free(context);
		return nullptr;
	}

	zt_logCritical("opensl: realizing output mix");
	if ((*context->sl_output_mix)->Realize(context->sl_output_mix, SL_BOOLEAN_FALSE) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: unable to realize output interface");
		zt_free(context);
		return nullptr;
	}
 
	//if ((*sl_output_mix)->GetInterface(sl_output_mix, SL_IID_VOLUME, &sl_output_vol) != SL_RESULT_SUCCESS) {
	//	zt_logCritical("opensl: Unable to get output volume interface");
	//	return nullptr;
	//}

	zt_logCritical("opensl: successfully initialized");

	return context;
}

// ================================================================================================================================================================================================

void ztsl_contextFree(ztOpenSLContext *context)
{
	if (context == nullptr) {
		return;
	}

//	if (context->sl_output_vol != nullptr) {
//		(*context->sl_output_vol)->Destroy(context->sl_output_vol);
//		context->sl_output_vol = nullptr;
//	}
	if (context->sl_output_mix != nullptr) {
		(*context->sl_output_mix)->Destroy(context->sl_output_mix);
		context->sl_output_mix = nullptr;
	}
//	if (context->sl_engine != nullptr) {
//		(*context->sl_engine)->Destroy(context->sl_engine);
//		context->sl_engine = nullptr;
//	}
	if (context->sl_object != nullptr) {
		(*context->sl_object)->Destroy(context->sl_object);
		context->sl_object = nullptr;
	}

	zt_free(context);
}

// ================================================================================================================================================================================================

void ztsl_contextPauseAll(ztOpenSLContext *context)
{
	zt_returnOnNull(context);

	zt_flink(buffer, context->buffers) {
		zt_fize(buffer->objects) {
			if (buffer->objects_used[i]) {
				SLuint32 play_state = 0;
				(*buffer->objects[i].play)->GetPlayState(buffer->objects[i].play, &play_state);

				if (play_state == SL_PLAYSTATE_PLAYING) {
					(*buffer->objects[i].play)->SetPlayState(buffer->objects[i].play, SL_PLAYSTATE_PAUSED);
				}
			}
		}
	}
}

// ================================================================================================================================================================================================

void ztsl_contextResumeAll(ztOpenSLContext *context)
{
	zt_returnOnNull(context);

	zt_flink(buffer, context->buffers) {
		zt_fize(buffer->objects) {
			if (buffer->objects_used[i]) {
				SLuint32 play_state = 0;
				(*buffer->objects[i].play)->GetPlayState(buffer->objects[i].play, &play_state);

				if (play_state == SL_PLAYSTATE_PAUSED) {
					(*buffer->objects[i].play)->SetPlayState(buffer->objects[i].play, SL_PLAYSTATE_PLAYING);
				}
			}
		}
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


ztInternal void SLAPIENTRY _ztsl_bufferPlayCallback(SLPlayItf player, void* context, SLuint32 event)
{
	//zt_logDebug("opensl: play callback function called");
	if (zt_bitIsSet(event, SL_PLAYEVENT_HEADATEND)) {
		//zt_logDebug("opensl: head is at the end");
		ztOpenSLBuffer::SLObjects* sl_objects = (ztOpenSLBuffer::SLObjects*)context;
		if (sl_objects != nullptr) {
			//zt_logDebug("opensl: audio buffer found");
			if (sl_objects->play_state == ztOpenSLBufferPlayState_Playing) {
				sl_objects->play_state = ztOpenSLBufferPlayState_NeedsStopped;
			}
		}
	}
}

// ================================================================================================================================================================================================

ztInternal bool _ztsl_sourceFillNextSlot(ztOpenSLBuffer *buffer, ztOpenSLBufferError_Enum *error = nullptr)
{
	int didx = -1;
	zt_fize(buffer->objects_used) {
		if (buffer->objects_used[i] == false) {
			didx = i;
			break;
		}
	}
	
	if (didx == -1) {
		if (error) *error = ztOpenSLBufferError_NoFreeSlots;
		return false;
	}

	buffer->objects_used[didx] = true;	

#	if defined(ZT_ANDROID)
	SLDataLocator_AndroidSimpleBufferQueue in_loc;
	in_loc.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	in_loc.numBuffers = 1;
#	else
	#error Non-android support needs added for OpenSL
#	endif

	SLDataFormat_PCM format;
	format.formatType    = SL_DATAFORMAT_PCM;
	format.numChannels   = buffer->channels;
	format.samplesPerSec = buffer->samples_per_second * 1000;
	format.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;//buffer->bits_per_sample;
	format.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;//buffer->bits_per_sample;
	format.channelMask   = buffer->channels == 2 ? SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT : SL_SPEAKER_FRONT_CENTER;
	format.endianness    = SL_BYTEORDER_LITTLEENDIAN;

	SLDataSource src;
	src.pLocator = &in_loc;
	src.pFormat  = &format;

	SLDataLocator_OutputMix out_loc;
	out_loc.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	out_loc.outputMix   = buffer->context->sl_output_mix;
 
	SLDataSink dst;
	dst.pLocator = &out_loc;
	dst.pFormat  = nullptr;

	const SLInterfaceID ids[] = { SL_IID_VOLUME, SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
	const SLboolean req[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	if ((*buffer->context->sl_engine)->CreateAudioPlayer(buffer->context->sl_engine, &buffer->objects[didx].object, &src, &dst, zt_elementsOf(ids), ids, req) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to create audio player");
		if (error) *error = ztOpenSLBufferError_CreateAudioPlayer;
		return false;
	}
 
	if ((*buffer->objects[didx].object)->Realize(buffer->objects[didx].object, SL_BOOLEAN_FALSE) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to realize audio player");
		if (error) *error = ztOpenSLBufferError_RealizeAudioPlayer;
		return false;
	}

	if ((*buffer->objects[didx].object)->GetInterface(buffer->objects[didx].object, SL_IID_PLAY, &buffer->objects[didx].play) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to get player interface");
		if (error) *error = ztOpenSLBufferError_GetPlayerInterface;
		return false;
	}

	if ((*buffer->objects[didx].object)->GetInterface(buffer->objects[didx].object, SL_IID_VOLUME, &buffer->objects[didx].volume) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to get audio player volume interface");
		if (error) *error = ztOpenSLBufferError_GetVolumeInterface;
		return false;
	}

	if ((*buffer->objects[didx].object)->GetInterface(buffer->objects[didx].object, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &buffer->objects[didx].simple_buffer_queue) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to get buffer queue interface");
		if (error) *error = ztOpenSLBufferError_GetBufferQueueInterface;
		return false;
	}

	if ((*buffer->objects[didx].play)->RegisterCallback(buffer->objects[didx].play, _ztsl_bufferPlayCallback, &buffer->objects[didx]) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to register player callback");
		if (error) *error = ztOpenSLBufferError_RegisterPlayerCallback;
		return false;
	}

	if ((*buffer->objects[didx].play)->SetCallbackEventsMask(buffer->objects[didx].play, SL_PLAYEVENT_HEADATEND) != SL_RESULT_SUCCESS) {
		zt_logCritical("opensl: Unable to set callback events mask");
		if (error) *error = ztOpenSLBufferError_SetCallbackEventsMask;
		return false;
	}

	return true;
}

// ================================================================================================================================================================================================

ztOpenSLBuffer *ztsl_bufferMake(ztOpenSLContext *context, byte* audio_data, i32 audio_data_len, ztOpenSLBufferError_Enum *error)
{
	zt_returnValOnNull(context, nullptr);
	zt_returnValOnNull(audio_data, nullptr);
	
	ztOpenSLBuffer *buffer = zt_mallocStruct(ztOpenSLBuffer);
	zt_memSet(buffer, zt_sizeof(ztOpenSLBuffer), 0);

	zt_fize(buffer->objects) {
		buffer->objects_used[i] = false;
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
		
			if (data_chunk[0] != compare_to[0] || data_chunk[1] != compare_to[1] || data_chunk[2] != compare_to[2] || data_chunk[3] != compare_to[3]) {
				if (error_message) {
					zt_logDebug("%s", error_message);
				}
				return false;
			}
			return true;
		}
	};

	ztWaveFileHeader wfh = {};
	if (audio_data_len < zt_sizeof(wfh)) {
		zt_logCritical("opensl: Audio data length too short for wave header");
		return nullptr;
	}

	// todo: add support for ogg from stb libraries
	// todo: support streaming audio

	zt_memCpy(&wfh, zt_sizeof(wfh), audio_data, zt_sizeof(wfh));
	audio_data += zt_sizeof(wfh);
	audio_data_len -= zt_sizeof(wfh);

	if (!local::checkDataChunk(wfh.chunk_id,      "RIFF", "opensl: Unsupported data chunk encountered") || 
		!local::checkDataChunk(wfh.format,        "WAVE", "opensl: Unsupported wave format encountered")) {
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
				zt_logCritical("opensl: Unsupported audio format encountered (only PCM supported)");
				return nullptr;
			}

			buffer->channels = wcf.num_channels;
			buffer->bits_per_sample = wcf.bits_per_sample;
			buffer->samples_per_second = wcf.sample_rate;

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

	buffer->wave_fmt = {};
	buffer->wave_fmt.wFormatTag      = WAVE_FORMAT_PCM;
	buffer->wave_fmt.nChannels       = buffer->channels;
	buffer->wave_fmt.nSamplesPerSec  = buffer->samples_per_second;
	buffer->wave_fmt.wBitsPerSample  = buffer->bits_per_sample;
	buffer->wave_fmt.nBlockAlign     = buffer->wave_fmt.nChannels * (buffer->wave_fmt.wBitsPerSample / 8);
	buffer->wave_fmt.nAvgBytesPerSec = buffer->wave_fmt.nSamplesPerSec * buffer->wave_fmt.nBlockAlign;
	buffer->wave_fmt.cbSize          = 0;

	buffer->audio_data_len = wch.chunk_size;
	buffer->audio_data = zt_mallocStructArray(byte, wch.chunk_size);
	zt_memCpy(buffer->audio_data, wch.chunk_size, data, wch.chunk_size);

	buffer->context = context;

	zt_logDebug("opensl: buffer data: %d  channels: %d  bits_per_sample: %d  chunk_size: %d  samples_per_sec: %d", buffer->audio_data_len, buffer->wave_fmt.nChannels, buffer->wave_fmt.wBitsPerSample, wch.chunk_size, buffer->wave_fmt.nSamplesPerSec);
	
	if (!_ztsl_sourceFillNextSlot(buffer, error)) {
		zt_free(buffer->audio_data);
		return nullptr;
	}

	while (_ztsl_sourceFillNextSlot(buffer, error)) {
		;
	}

	zt_singleLinkAddToEnd(context->buffers, buffer);

	return buffer;
}

// ================================================================================================================================================================================================

void ztsl_bufferFree(ztOpenSLBuffer* buffer)
{
	if (buffer == nullptr) {
		return;
	}

	ztOpenSLBuffer *prev = nullptr;
	zt_flink(node, buffer->context->buffers) {
		if (node == buffer) {
			if (prev) {
				prev->next = node->next;
			}
			break;
		}
	}


	zt_fize(buffer->objects) {
		if (buffer->objects_used[i]) {
			(*buffer->objects[i].object)->Destroy(buffer->objects[i].object);

			buffer->objects_used[i] = false;
		}
	}

	zt_free(buffer->audio_data);
	zt_free(buffer);
}

// ================================================================================================================================================================================================

void ztsl_bufferGetDetails(ztOpenSLBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length)
{
	if (channels         ) *channels            = buffer->channels;
	if (bits_per_sample  ) *bits_per_sample     = buffer->bits_per_sample;
	if (samples_per_second) *samples_per_second = buffer->samples_per_second;
	if (length           ) *length              = (buffer->audio_data_len / ((buffer->channels * buffer->bits_per_sample) / 8.f)) / (r32)buffer->samples_per_second;
}

// ================================================================================================================================================================================================

void ztsl_bufferPlay(ztOpenSLBuffer *buffer, bool loop)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->objects) {
		if (buffer->objects_used[i]) {
			if (buffer->objects[i].play_state == ztOpenSLBufferPlayState_NeedsStopped) {
				(*buffer->objects[i].play)->SetPlayState(buffer->objects[i].play, SL_PLAYSTATE_STOPPED);
				(*buffer->objects[i].simple_buffer_queue)->Clear(buffer->objects[i].simple_buffer_queue);
				buffer->objects[i].play_state = ztOpenSLBufferPlayState_Idle;
			}

			if (buffer->objects[i].play_state == ztOpenSLBufferPlayState_Idle) {
				(*buffer->objects[i].simple_buffer_queue)->Clear(buffer->objects[i].simple_buffer_queue);
				(*buffer->objects[i].simple_buffer_queue)->Enqueue(buffer->objects[i].simple_buffer_queue, buffer->audio_data, buffer->audio_data_len);
				(*buffer->objects[i].play)->SetPlayState(buffer->objects[i].play, SL_PLAYSTATE_PLAYING);
				buffer->objects[i].play_state = ztOpenSLBufferPlayState_Playing;
			}
		}
	}

	// todo: looping

	zt_fize(buffer->objects) {
		if (buffer->objects_used[i] == false) {
			_ztsl_sourceFillNextSlot(buffer);
			ztsl_bufferPlay(buffer, loop);
			return;
		}
	}
}

// ================================================================================================================================================================================================

void ztsl_bufferPlay(ztOpenSLBuffer *buffer)
{
	ztsl_bufferPlay(buffer, false);
}

// ================================================================================================================================================================================================

void ztsl_bufferPlayLooping(ztOpenSLBuffer *buffer)
{
	ztsl_bufferPlay(buffer, true);
}

// ================================================================================================================================================================================================

void ztsl_bufferStop(ztOpenSLBuffer *buffer)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->objects) {
		if (buffer->objects_used[i] && buffer->objects[i].play_state == ztOpenSLBufferPlayState_Playing) {
			(*buffer->objects[i].play)->SetPlayState(buffer->objects[i].play, SL_PLAYSTATE_STOPPED);
			buffer->objects[i].play_state = ztOpenSLBufferPlayState_Idle;
		}
	}
}

// ================================================================================================================================================================================================

void ztsl_bufferSetVolume(ztOpenSLBuffer *buffer, r32 volume)
{
	zt_returnOnNull(buffer);

	volume = volume < 0.01F ? -96.0F : 20 * log10(volume);

	zt_fize(buffer->objects) {
		if (buffer->objects_used[i]) {
			(*buffer->objects[i].volume)->SetVolumeLevel(buffer->objects[i].volume, (SLmillibel)volume);
		}
	}
}

// ================================================================================================================================================================================================

void ztsl_bufferSetFrequency(ztOpenSLBuffer *buffer, r32 frequency)
{
	zt_returnOnNull(buffer);

	zt_fize(buffer->objects) {
		if (buffer->objects_used[i]) {
			// todo
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // implementation
