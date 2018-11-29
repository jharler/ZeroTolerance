/**************************************************************************************************************************************************************************************************
** file: zt_dsound.h v 0.00 (active initial development)
**
** This software is dual-licensed to the public domain and under the following
** license: you are granted a perpetual, irrevocable license to copy, modify,
** publish, and distribute this file as you see fit.
**
** No warranty is offered or implied.  Use this at your own risk.
**
***************************************************************************************************************************************************************************************************

Zero Tolerance DirectSound Library

In exactly one c/cpp source file of your project, you must:

#define ZT_DSOUND_IMPLEMENTATION
#include "zt_dsound.h"

***************************************************************************************************************************************************************************************************

Options:


***************************************************************************************************************************************************************************************************

Implimentation Options: (only used with ZT_DSOUND_IMPLEMENTATION #include)


***************************************************************************************************************************************************************************************************/

#ifndef __zt_dsound_h_included__
#define __zt_dsound_h_included__

// ================================================================================================================================================================================================

#define ZT_DSOUND


// ================================================================================================================================================================================================

#include "zt_tools.h"

#if !defined(ZT_WINDOWS)
#	error DirectSound is only supported on Windows
#endif

// ================================================================================================================================================================================================

enum ztDirectSoundContextError_Enum
{
	ztDirectSoundContextError_None,
	ztDirectSoundContextError_LoadLibrary,
	ztDirectSoundContextError_FindFunction,
	ztDirectSoundContextError_Create,
	ztDirectSoundContextError_SetCoopLevel,
	ztDirectSoundContextError_CreatePrimaryBuffer,
	ztDirectSoundContextError_PrimaryBufferFormat,
};

// ================================================================================================================================================================================================

struct ztDirectSoundContext;

ztDirectSoundContext *ztds_contextMake(HWND window, ztDirectSoundContextError_Enum *error = nullptr);
void ztds_contextFree(ztDirectSoundContext *context);

// ================================================================================================================================================================================================

enum ztDirectSoundBufferError_Enum
{
	ztDirectSoundBufferError_None,
	ztDirectSoundBufferError_NoFreeSlots,
	ztDirectSoundBufferError_CreateBuffer,
	ztDirectSoundBufferError_CopyData,
};

struct ztDirectSoundBuffer;

ztDirectSoundBuffer *ztds_bufferMake(ztDirectSoundContext *context, byte* audio_data, i32 audio_data_len, ztDirectSoundBufferError_Enum *error = nullptr);
void ztds_bufferFree(ztDirectSoundBuffer *buffer);

void ztds_bufferGetDetails(ztDirectSoundBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length);

void ztds_bufferPlay(ztDirectSoundBuffer *buffer);
void ztds_bufferPlayLooping(ztDirectSoundBuffer *buffer);
void ztds_bufferStop(ztDirectSoundBuffer *buffer);

void ztds_bufferSetVolume(ztDirectSoundBuffer *buffer, r32 volume);
void ztds_bufferSetFrequency(ztDirectSoundBuffer *buffer, r32 frequency);

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

#if defined(ZT_DSOUND_IMPLEMENTATION) || defined(ZT_DSOUND_INTERNAL_DECLARATIONS)

#ifndef __zt_dsound_h_internal_included__
#define __zt_dsound_h_internal_included__

#include <windows.h>
#include <dsound.h>
#include <mmreg.h>


// ================================================================================================================================================================================================

#ifndef ZT_DSOUND_BUFFERS_PER_SOUND
#define ZT_DSOUND_BUFFERS_PER_SOUND   3
#endif

#ifndef ZT_DSOUND_BUFFER_SIZE_CAP
#define ZT_DSOUND_BUFFER_SIZE_CAP zt_megabytes(1)
#endif

// ================================================================================================================================================================================================

struct ztDirectSoundContext
{
	i32 samples_per_second;
	i32 bytes_per_sample;

	HMODULE             dsound_dll            = NULL;
	LPDIRECTSOUND       dsound                = nullptr;
	LPDIRECTSOUNDBUFFER dsound_primary_buffer = nullptr;
};

// ================================================================================================================================================================================================

struct ztDirectSoundBuffer
{
	ztDirectSoundContext *context;

	LPDIRECTSOUNDBUFFER   buffer[ZT_DSOUND_BUFFERS_PER_SOUND];
	WAVEFORMATEX          wave_fmt;
	DSBUFFERDESC          buffer_desc;
	i32                   buffer_size;
	byte*                 audio_data;

	i32                   channels;
	i32                   bits_per_sample;
	i32                   samples_per_second;
	r32                   length;

	i32                   frequency;
};

// ================================================================================================================================================================================================

#endif // include guard
#endif // internal declarations

#if defined(ZT_DSOUND_IMPLEMENTATION)

ztDirectSoundContext *ztds_contextMake(HWND window, ztDirectSoundContextError_Enum *error)
{
	ztDirectSoundContext context = {};
	context.samples_per_second = 48000;
	context.bytes_per_sample = zt_sizeof(i16) * 2;

	context.dsound_dll = LoadLibraryA("dsound.dll");
	if(context.dsound_dll == nullptr) {
		zt_logDebug("Unable to load dsound.dll");
		if(error) *error = ztDirectSoundContextError_LoadLibrary;
		return nullptr;
	}

	typedef HRESULT (WINAPI *ztds_create_Func)(LPCGUID, LPDIRECTSOUND*, LPUNKNOWN);
	ztds_create_Func create = (ztds_create_Func)GetProcAddress(context.dsound_dll, "DirectSoundCreate");
	if(create == nullptr) {
		zt_logDebug("Unable to locate function DirectSoundCreate in dsound.dll");
		if(error) *error = ztDirectSoundContextError_FindFunction;
		return nullptr;
	}

	if(!SUCCEEDED(create(0, &context.dsound, nullptr))) {
		zt_logDebug("Unable to create DirectSound object");
		if(error) *error = ztDirectSoundContextError_Create;
		return nullptr;
	}

	WAVEFORMATEX wave_fmt = {};
	wave_fmt.wFormatTag      = WAVE_FORMAT_PCM;
	wave_fmt.nChannels       = 2;
	wave_fmt.nSamplesPerSec  = context.samples_per_second;
	wave_fmt.wBitsPerSample  = 16; 
	wave_fmt.nBlockAlign     = (wave_fmt.nChannels * wave_fmt.wBitsPerSample) / 8;
	wave_fmt.nAvgBytesPerSec = wave_fmt.nSamplesPerSec * wave_fmt.nBlockAlign;
	wave_fmt.cbSize          = 0;

	if (!SUCCEEDED(context.dsound->SetCooperativeLevel(window, DSSCL_PRIORITY))) {
		zt_logDebug("Unable to set DirectSound cooperative level");
		if(error) *error = ztDirectSoundContextError_SetCoopLevel;
		return nullptr;
	}

	DSBUFFERDESC buffer_desc = {};
	buffer_desc.dwSize  = sizeof(buffer_desc);
	buffer_desc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	context.dsound_primary_buffer = nullptr;
	if (!SUCCEEDED(context.dsound->CreateSoundBuffer(&buffer_desc, &context.dsound_primary_buffer, nullptr))) {
		zt_logDebug("Unable to create primary DirectSound sound buffer");
		if(error) *error = ztDirectSoundContextError_CreatePrimaryBuffer;
		return nullptr;
	}

	if (!SUCCEEDED(context.dsound_primary_buffer->SetFormat(&wave_fmt))) {
		zt_logDebug("Unable to set format of primary DirectSound sound buffer");
		if(error) *error = ztDirectSoundContextError_PrimaryBufferFormat;
		return nullptr;
	}

	zt_logDebug("DirectSound successfully initialized");

	ztDirectSoundContext *result = zt_mallocStruct(ztDirectSoundContext);
	*result = context;
	return result;
}

// ================================================================================================================================================================================================

void ztds_contextFree(ztDirectSoundContext *context)
{
	if(context == nullptr) {
		return;
	}

	if( context->dsound_primary_buffer != nullptr ) {
		context->dsound_primary_buffer->Release();
	}
	if( context->dsound != nullptr ) {
		context->dsound->Release();
	}
	if (context->dsound_dll != NULL) {
		FreeLibrary(context->dsound_dll);
		context->dsound_dll = NULL;
	}

	zt_free(context);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal bool _ztds_bufferFillNextSlot(ztDirectSoundBuffer *buffer, ztDirectSoundBufferError_Enum *error = nullptr)
{
	int didx = -1;
	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] == nullptr) {
			didx = i;
			break;
		}
	}
	if (didx == -1 || (didx != 0 && buffer->buffer_size >= ZT_DSOUND_BUFFER_SIZE_CAP)) {
		if(error) *error = ztDirectSoundBufferError_NoFreeSlots;
		return false;
	}

	//zt_logDebug("Creating DirectSound audio buffer (channels: %d; samples per sec: %d; bits per sample: %d)", buffer->wave_fmt.nChannels, buffer->wave_fmt.nSamplesPerSec, buffer->wave_fmt.wBitsPerSample);

	if (!SUCCEEDED(buffer->context->dsound->CreateSoundBuffer(&buffer->buffer_desc, &buffer->buffer[didx], nullptr))) {
		if(error) *error = ztDirectSoundBufferError_CreateBuffer;
		zt_logDebug("Unable to create DirectSound sound buffer (%d)", GetLastError());
		return false;
	}

	void* region_1 = nullptr;
	DWORD region_1_size = 0;

	if (!SUCCEEDED(buffer->buffer[didx]->Lock(0, buffer->buffer_size, &region_1, &region_1_size, NULL, NULL, 0))) {
		if(error) *error = ztDirectSoundBufferError_CopyData;
		zt_logDebug("Unable to copy audio data to DirectSound buffer (%d)", GetLastError());
		return false;
	}

	zt_memCpy(region_1, region_1_size, buffer->audio_data, buffer->buffer_size);
	buffer->buffer[didx]->Unlock(region_1, region_1_size, 0, 0);

	if(didx == 0) {
		buffer->frequency = 0;
		DWORD freq;
		buffer->buffer[didx]->GetFrequency(&freq);
		buffer->frequency = freq;
	}

	return true;
}

// ================================================================================================================================================================================================

ztDirectSoundBuffer *ztds_bufferMake(ztDirectSoundContext *context, byte* audio_data, i32 audio_data_len, ztDirectSoundBufferError_Enum *error)
{
	zt_returnValOnNull(context, nullptr);
	zt_returnValOnNull(audio_data, nullptr);

	ztDirectSoundBuffer buffer = {};
	buffer.context = context;

	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		buffer.buffer[i] = nullptr;
	}

	struct ztWaveFileHeader
	{
		char chunk_id[4];
		u32  chunk_size;
		char format[4];
		//char sub_chunk_id[4];
		//u32  sub_chunk_size;
		//u16  audio_format;
		//u16  num_channels;
		//u32  sample_rate;
		//u32  bytes_per_second;
		//u16  block_align;
		//u16  bits_per_sample;
		//char data_chunk_id[4];
		//u32  data_size;
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
	};

	ztWaveFileHeader wfh = {};
	if (audio_data_len < zt_sizeof(wfh)) {
		zt_logDebug("DirectSound: Audio data length too short for wave header");
		return nullptr;
	}

	// todo: add support for ogg from stb libraries
	// todo: support streaming audio

	zt_memCpy(&wfh, zt_sizeof(wfh), audio_data, zt_sizeof(wfh));
	audio_data += zt_sizeof(wfh);
	audio_data_len -= zt_sizeof(wfh);

	if( !local::checkDataChunk(wfh.chunk_id,      "RIFF", "DirectSound: Unsupported data chunk encountered") || 
		!local::checkDataChunk(wfh.format,        "WAVE", "DirectSound: Unsupported wave format encountered") ) {
		//!local::checkDataChunk(wfh.sub_chunk_id,  "fmt ", "DirectSound: Unsupported sub chunk id encountered") ||
		//!local::checkDataChunk(wfh.data_chunk_id, "data", "DirectSound: Unsupported data chunk id encountered") ) {
		return false;
	}

	ztWavChunkHeader wch;
	zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
	audio_data += zt_sizeof(wch);
	audio_data_len -= zt_sizeof(wch);

	bool found_fmt = false;
	while (true) {
		if (local::checkDataChunk(wch.chunk_id, "fmt ", nullptr)) {
			found_fmt = true;

			ztWavChunkFormat wcf;
			int size = zt_min(wch.chunk_size, zt_sizeof(wcf));
			zt_memCpy(&wcf, size, audio_data, audio_data_len);
			audio_data += size;
			audio_data_len -= size;

			if (wcf.audio_format != WAVE_FORMAT_PCM) {
				zt_logDebug("DirectSound: Unsupported audio format encountered (only PCM supported)");
				return false;
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

			if(audio_data_len <= 0) {
				break;
			}
		}
		else break;
	}

#if 0
	if(!local::checkDataChunk(wch.chunk_id, "fmt ", "DirectSound: Unsupported sub chunk id encountered")) {
		return false;
	}

	ztWavChunkFormat wcf;
	int size = zt_min(wch.chunk_size, zt_sizeof(wcf));
	zt_memCpy(&wcf, size, audio_data, audio_data_len);
	audio_data += size;
	audio_data_len -= size;

	if( wcf.audio_format != WAVE_FORMAT_PCM ) {
		zt_logDebug("DirectSound: Unsupported audio format encountered (only PCM supported)");
		return false;
	}

	buffer.channels           = wcf.num_channels;
	buffer.bits_per_sample    = wcf.bits_per_sample;
	buffer.samples_per_second = wcf.sample_rate;

	zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
	audio_data += zt_sizeof(wch);
	audio_data_len -= zt_sizeof(wch);

	while(!local::checkDataChunk(wch.chunk_id, "data", nullptr)) { //&& !local::checkDataChunk(wch.chunk_id, "bext", nullptr)) {
		audio_data += wch.chunk_size;
		audio_data_len -= wch.chunk_size;

		zt_memCpy(&wch, zt_sizeof(wch), audio_data, audio_data_len);
		audio_data += zt_sizeof(wch);
		audio_data_len -= zt_sizeof(wch);

		if(audio_data_len <= 0) {
			break;
		}
	}
#endif
	byte* data = audio_data;

	buffer.wave_fmt = {};
	buffer.wave_fmt.wFormatTag      = WAVE_FORMAT_PCM;
	buffer.wave_fmt.nChannels       = buffer.channels;
	buffer.wave_fmt.nSamplesPerSec  = buffer.samples_per_second;
	buffer.wave_fmt.wBitsPerSample  = buffer.bits_per_sample;
	buffer.wave_fmt.nBlockAlign     = buffer.wave_fmt.nChannels * (buffer.wave_fmt.wBitsPerSample / 8);
	buffer.wave_fmt.nAvgBytesPerSec = buffer.wave_fmt.nSamplesPerSec * buffer.wave_fmt.nBlockAlign;
	buffer.wave_fmt.cbSize          = 0;

	buffer.buffer_desc = {};
	buffer.buffer_desc.dwSize        = sizeof(buffer.buffer_desc);
	buffer.buffer_desc.dwFlags       = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	buffer.buffer_desc.dwBufferBytes = wch.chunk_size;
	buffer.buffer_desc.lpwfxFormat   = &buffer.wave_fmt;

	buffer.buffer_size = wch.chunk_size;

	//zt_fizr(256) {
	//	char *info = (char*)data + (wch.chunk_size - i);
	//	if(info[0] == 'L' && info[1] == 'I' && info[2] == 'S' && info[3] == 'T') {
	//		buffer.buffer_size -= i;
	//		break;
	//	}
	//}

	if (wch.chunk_size <= ZT_DSOUND_BUFFER_SIZE_CAP) {
		buffer.audio_data = zt_mallocStructArray(byte, wch.chunk_size);
		zt_memCpy(buffer.audio_data, wch.chunk_size, data, wch.chunk_size);
		//zt_logDebug("Copying audio data into memory");
	}
	else {
		buffer.audio_data = (byte*)data;
		//zt_logDebug("Not copying audio data into memory (audio data is too large)");
	}

	if (!_ztds_bufferFillNextSlot(&buffer, error)) {
		if (audio_data_len <= ZT_DSOUND_BUFFER_SIZE_CAP) {
			zt_free(buffer.audio_data);
		}
		return nullptr;
	}

	while(_ztds_bufferFillNextSlot(&buffer, error)) {
		;
	}

	ztDirectSoundBuffer *result = zt_mallocStruct(ztDirectSoundBuffer);
	*result = buffer;
	return result;
}

// ================================================================================================================================================================================================

void ztds_bufferFree(ztDirectSoundBuffer* buffer)
{
	if(buffer == nullptr) {
		return;
	}

	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] != nullptr) {
			buffer->buffer[i]->Release();
		}
	}
	if (buffer->buffer_size <= ZT_DSOUND_BUFFER_SIZE_CAP) {
		zt_free(buffer->audio_data);
	}
	zt_free(buffer);
}

// ================================================================================================================================================================================================

void ztds_bufferGetDetails(ztDirectSoundBuffer *buffer, i32 *channels, i32 *bits_per_sample, i32 *samples_per_second, r32 *length)
{
	if(channels          ) *channels           = buffer->channels;
	if(bits_per_sample   ) *bits_per_sample    = buffer->bits_per_sample;
	if(samples_per_second) *samples_per_second = buffer->samples_per_second;
	if(length            ) *length             = (buffer->buffer_size / ((buffer->channels * buffer->bits_per_sample) / 8.f)) / (r32)buffer->samples_per_second;
}

// ================================================================================================================================================================================================

void ztds_bufferPlay(ztDirectSoundBuffer *buffer, bool loop)
{
	zt_returnOnNull(buffer);

	DWORD status = 0;
	if (buffer->buffer[0] != nullptr) {
		buffer->buffer[0]->GetStatus(&status);
		if (zt_bitIsSet(status, DSBSTATUS_PLAYING) || zt_bitIsSet(status, DSBSTATUS_LOOPING)) {
			_ztds_bufferFillNextSlot(buffer); // make sure we allocate another buffer if needed
		}
	}
	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] != nullptr) {
			status = 0;
			buffer->buffer[i]->GetStatus(&status);
			if (!zt_bitIsSet(status, DSBSTATUS_PLAYING) && !zt_bitIsSet(status, DSBSTATUS_LOOPING)) {
				buffer->buffer[i]->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);
				return;
			}
		}
	}

	// if we're here, we have no free buffers and need to just reset the buffer to play it
	if (buffer->buffer[0] != nullptr) {
		buffer->buffer[0]->Stop();
		buffer->buffer[0]->SetCurrentPosition(0);
		buffer->buffer[0]->Play(0, 0, 0);
	}
}

// ================================================================================================================================================================================================

void ztds_bufferPlay(ztDirectSoundBuffer *buffer)
{
	ztds_bufferPlay(buffer, false);
}

// ================================================================================================================================================================================================

void ztds_bufferPlayLooping(ztDirectSoundBuffer *buffer)
{
	ztds_bufferPlay(buffer, true);
}

// ================================================================================================================================================================================================

void ztds_bufferStop(ztDirectSoundBuffer *buffer)
{
	zt_returnOnNull(buffer);

	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] != nullptr) {
			buffer->buffer[i]->Stop();
			buffer->buffer[i]->SetCurrentPosition(0);
		}
	}
}

// ================================================================================================================================================================================================

void ztds_bufferSetVolume(ztDirectSoundBuffer *buffer, r32 volume)
{
	zt_returnOnNull(buffer);

	LONG lvol = zt_real32Eq(volume, 0) ? DSBVOLUME_MIN : DSBVOLUME_MAX + zt_convertToi32Floor((DSBVOLUME_MIN * (1 - volume)) * .5f);

	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] != nullptr) {
			buffer->buffer[i]->SetVolume(lvol);
		}
	}
}

// ================================================================================================================================================================================================

void ztds_bufferSetFrequency(ztDirectSoundBuffer *buffer, r32 frequency)
{
	zt_returnOnNull(buffer);

	i32 amount_below = buffer->frequency - DSBFREQUENCY_MIN;
	i32 amount_above = DSBFREQUENCY_MAX - buffer->frequency;

	i32 lfreq;

	if (frequency < .5f) {
		lfreq = zt_convertToi32Floor(amount_below * zt_linearRemap(frequency, 0, .5f, 0, 1)) + DSBFREQUENCY_MIN;
	}
	else {
		lfreq = zt_convertToi32Floor(amount_above * zt_linearRemap(frequency, .5f, 1.f, 0, 1)) + buffer->frequency;
	}

	zt_fiz(ZT_DSOUND_BUFFERS_PER_SOUND) {
		if (buffer->buffer[i] != nullptr) {
			buffer->buffer[i]->SetFrequency(lfreq);
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // implementation
