/**************************************************************************************************
** file: zt_directx.h v 0.00 (active initial development)
**
** This software is dual-licensed to the public domain and under the following
** license: you are granted a perpetual, irrevocable license to copy, modify,
** publish, and distribute this file as you see fit.
**
** No warranty is offered or implied.  Use this at your own risk.
**
**************************************************************************************************

Zero Tolerance DirectX Library

In exactly one c/cpp source file of your project, you must:

#define ZT_DIRECTX_IMPLEMENTATION
#include "zt_directx.h"

**************************************************************************************************

Options:


**************************************************************************************************

Implimentation Options: (only used with ZT_DIRECTX_IMPLEMENTATION #include)


**************************************************************************************************/

#ifndef __zt_directx_h_included__
#define __zt_directx_h_included__

// ------------------------------------------------------------------------------------------------

#define ZT_DIRECTX


// ------------------------------------------------------------------------------------------------

#include "zt_tools.h"

#if !defined(ZT_WINDOWS)
#	error DirectX is only supported on Windows
	// maybe Xbox support later?
#endif

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>


// ------------------------------------------------------------------------------------------------

struct ztContextDX;

ztContextDX *ztdx_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
ztContextDX *ztdx_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
void         ztdx_contextFree(ztContextDX *context);

void         ztdx_contextDisplay(ztContextDX *context);

ztPoint2     ztdx_contextGetSize(ztContextDX *context);
bool         ztdx_contextSetSize(ztContextDX *context, i32 w, i32 h);
bool         ztdx_contextIsFullscreen(ztContextDX *context);
bool         ztdx_contextToggleFullscreen(ztContextDX *context, bool fullscreen);

void         ztdx_clipRegionSet(ztContextDX *context, int left, int top, int right, int bottom);
void         ztdx_clipRegionRemove(ztContextDX *context);

// ------------------------------------------------------------------------------------------------

bool ztdx_setViewport(i32 width, i32 height);
bool ztdx_setViewport(ztContextDX *context);

void ztdx_cullFront(ztContextDX *context);
void ztdx_cullBack(ztContextDX *context);
void ztdx_cullNone(ztContextDX *context);

void ztdx_depthTestOff(ztContextDX *context);
void ztdx_depthTestNever(ztContextDX *context);
void ztdx_depthTestLess(ztContextDX *context);
void ztdx_depthTestLessEqual(ztContextDX *context);
void ztdx_depthTestEqual(ztContextDX *context);
void ztdx_depthTestGreater(ztContextDX *context);
void ztdx_depthTestNotEqual(ztContextDX *context);
void ztdx_depthTestGreaterEqual(ztContextDX *context);
void ztdx_depthTestAlways(ztContextDX *context);

void ztdx_clear(ztContextDX *context, ztVec4& color);
void ztdx_clear(ztContextDX *context, r32 color[4]);
void ztdx_clear(ztContextDX *context, r32 r, r32 g, r32 b, r32 a = 1);


// ------------------------------------------------------------------------------------------------

bool    ztdx_checkAndReportError(const char *function, i32 hr);
int     ztdx_clearErrors();

#define ztdx_callAndReturnOnError(function) if (ztdx_checkAndReportError(#function, (function))) return;
#define ztdx_callAndReturnValOnError(function, retval) if (ztdx_checkAndReportError(#function, (function))) return retval;
#define ztdx_callAndReportOnError(function) ztdx_checkAndReportError(#function, (function));

#if defined(ZT_DIRECTX_DEBUGGING)
#	define ztdx_callAndReportOnErrorFast(function) ztdx_checkAndReportError(#function, (function));
#else
#	define ztdx_callAndReportOnErrorFast(function) function;
#endif


// ------------------------------------------------------------------------------------------------

enum ztTextureDXFlags_Enum
{
	ztTextureDXFlags_MipMaps = (1 << 0),
	ztTextureDXFlags_DepthMap = (1 << 1),
	ztTextureDXFlags_PixelPerfect = (1 << 2),
	ztTextureDXFlags_CubeMap = (1 << 3),
};

// ------------------------------------------------------------------------------------------------

enum ztTextureDXCubeMapFiles_Enum
{
	ztTextureDXCubeMapFiles_Right,
	ztTextureDXCubeMapFiles_Left,
	ztTextureDXCubeMapFiles_Top,
	ztTextureDXCubeMapFiles_Bottom,
	ztTextureDXCubeMapFiles_Back,
	ztTextureDXCubeMapFiles_Front,

	ztTextureDXCubeMapFiles_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztTextureDX
{
	ID3D11Texture2D          *tex;
	ID3D11ShaderResourceView *shader_resource_view;
	ID3D11SamplerState       *sampler_state;

	ID3D11Texture2D          *depth_stencil_buffer;
	ID3D11DepthStencilView   *depth_stencil_view;
	ID3D11RenderTargetView   *render_target_view;

	ztPoint2 size;
	i32 flags;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeFromPixelData(ztContextDX *context, byte *pixels, int w, int h, int d, i32 flags);
ztTextureDX *ztdx_textureMakeFromPixelData(ztMemoryArena *arena, ztContextDX *context, byte *pixels, int w, int h, int d, i32 flags);
ztTextureDX *ztdx_textureMakeCubeMapFromPixelData(ztContextDX *context, byte **pixels, int w, int h, int d);
ztTextureDX *ztdx_textureMakeCubeMapFromPixelData(ztMemoryArena *arena, ztContextDX *context, byte **pixels, int w, int h, int d);
ztTextureDX *ztdx_textureMakeRenderTarget(ztContextDX *context, int w, int h, i32 flags);
ztTextureDX *ztdx_textureMakeRenderTarget(ztMemoryArena *arena, ztContextDX *context, int w, int h, i32 flags);
ztTextureDX *ztdx_textureMakeDepthRenderTarget(ztContextDX *context, int w, int h);
ztTextureDX *ztdx_textureMakeDepthRenderTarget(ztMemoryArena *arena, ztContextDX *context, int w, int h);

void         ztdx_textureFree(ztTextureDX *texture);

void         ztdx_textureRenderTargetPrepare(ztContextDX *context, ztTextureDX *texture);
void         ztdx_textureRenderTargetCommit(ztContextDX *context, ztTextureDX *texture);

bool         ztdx_textureIsRenderTarget(ztTextureDX *texture);


// ------------------------------------------------------------------------------------------------

enum ztShaderDXVariableType_Enum
{
	ztShaderDXVariableType_Invalid,

	ztShaderDXVariableType_Float,
	ztShaderDXVariableType_Vec2,
	ztShaderDXVariableType_Vec3,
	ztShaderDXVariableType_Vec4,
	ztShaderDXVariableType_Int,
	ztShaderDXVariableType_Mat3,
	ztShaderDXVariableType_Mat4,
	ztShaderDXVariableType_Tex,
	ztShaderDXVariableType_TexCube,

	ztShaderDXVariableType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztShaderDX
{
	ID3D11VertexShader *vert;
	ID3D11PixelShader  *frag;
	ID3D11InputLayout  *layout;

	struct ConstantBuffer
	{
		ID3D11Buffer *buffer;
		int           shader; // 0 - vert, 1 - frag
	};

	ConstantBuffer     *cbuffers;
	i32                 cbuffers_count;

	struct Variable
	{
		char                        name[64];
		u32                         name_hash;
		int                         cbuffer;
		int                         size;
		int                         offset;
		int                         shader; // 0 - vert, 1 - frag
		ztShaderDXVariableType_Enum type;
		byte                       *data;
	};

	Variable            *variables;
	int                  variables_count;

	ztMemoryArena       *arena;
};

// ------------------------------------------------------------------------------------------------

ztShaderDX *ztdx_shaderMake(ztContextDX *context, const char *vert_src, const char *vert_func, const char *frag_src, const char *frag_func);
ztShaderDX *ztdx_shaderMake(ztMemoryArena *arena, ztContextDX *context, const char *vert_src, const char *vert_func, const char *frag_src, const char *frag_func);
void        ztdx_shaderFree(ztContextDX *context, ztShaderDX *shader);

void        ztdx_shaderBegin(ztContextDX *context, ztShaderDX *shader);
void        ztdx_shaderEnd(ztContextDX *context, ztShaderDX *shader);

bool        ztdx_shaderHasVariable(ztShaderDX *shader, u32 name_hash);

void        ztdx_shaderVariableFloat(ztShaderDX *shader, u32 name_hash, r32 value);
void        ztdx_shaderVariableInt(ztShaderDX *shader, u32 name_hash, i32 value);
void        ztdx_shaderVariableVec2(ztShaderDX *shader, u32 name_hash, r32 value[2]);
void        ztdx_shaderVariableVec3(ztShaderDX *shader, u32 name_hash, r32 value[3]);
void        ztdx_shaderVariableVec4(ztShaderDX *shader, u32 name_hash, r32 value[4]);
void        ztdx_shaderVariableMat4(ztShaderDX *shader, u32 name_hash, r32 value[16]);
void        ztdx_shaderVariableMat3(ztShaderDX *shader, u32 name_hash, r32 value[9]);
void        ztdx_shaderVariableTex(ztShaderDX *shader, u32 name_hash, ztTextureDX *tex);

void        ztdx_shaderPopulateConstantBuffers(ztContextDX *context, ztShaderDX *shader);


// ------------------------------------------------------------------------------------------------

struct ztVertexEntryDX
{
	int size;
};

// ------------------------------------------------------------------------------------------------

struct ztVertexArrayDX
{
	ID3D11Buffer    *buff_vert;
	i32              stride;

	ztVertexEntryDX *entries;
	int              entries_count;

	int              vert_count;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztVertexArrayDX *ztdx_vertexArrayMake(ztContextDX *context, ztVertexEntryDX *entries, int entries_count, void *vert_data, int vert_count);
ztVertexArrayDX *ztdx_vertexArrayMake(ztMemoryArena *arena, ztContextDX *context, ztVertexEntryDX *entries, int entries_count, void *vert_data, int vert_count);
void             ztdx_vertexArrayFree(ztVertexArrayDX *vertex_array);
void             ztdx_vertexArrayUpdate(ztContextDX *context, ztVertexArrayDX *vertex_array, void *vert_data, int vert_count);
void             ztdx_vertexArrayDraw(ztContextDX *context, ztVertexArrayDX *vertex_array, D3D11_PRIMITIVE_TOPOLOGY topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // include guard

#if defined(ZT_DIRECTX_IMPLEMENTATION) || defined(ZT_DIRECTX_INTERNAL_DECLARATIONS)

#ifndef __zt_directx_h_internal_included__
#define __zt_directx_h_internal_included__


struct ztContextDX
{
	HWND handle;

	IDXGISwapChain          *swapchain;
	ID3D11Device            *device;
	ID3D11DeviceContext     *context;
	ID3D11RenderTargetView  *backbuffer;
	ID3D11BlendState        *transparency;
	ID3D11RasterizerState   *cull_mode_ccw;
	ID3D11RasterizerState   *cull_mode_cw;
	ID3D11RasterizerState   *cull_mode_none;
	ID3D11DepthStencilView  *depth_stencil_view;
	ID3D11Texture2D         *depth_stencil_buffer;
	ID3D11DepthStencilState *stencil_state_enabled;
	ID3D11DepthStencilState *stencil_state_disabled;
	ID3D11DepthStencilState *stencil_state_enabled_leq;

	ID3D11RenderTargetView  *active_render_target;
	ID3D11DepthStencilView  *active_render_target_depth_stencil_view;

	int texture_count;

	ztPoint2 size;
	i32      pixels_per_unit;
	i32      flags;

	ztMemoryArena *arena;
};

#endif // include guard
#endif // internal declarations

#if defined(ZT_DIRECTX_IMPLEMENTATION)

enum ztRendererFlagsDX_Enum
{
	ztRendererFlagsDX_Windowed   = (1 << 0),
	ztRendererFlagsDX_Fullscreen = (1 << 1),
	ztRendererFlagsDX_Vsync      = (1 << 2),
	ztRendererFlagsDX_LockAspect = (1 << 5),
	ztRendererFlagsDX_HideCursor = (1 << 6),
};

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// ------------------------------------------------------------------------------------------------

ztContextDX *ztdx_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags) // ztRendererFlags
{
	return ztdx_contextMake(zt_memGetGlobalArena(), window, client_w, client_h, pixels_per_unit, flags);
}

// ------------------------------------------------------------------------------------------------

ztContextDX *ztdx_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 renderer_flags) // ztRendererFlags
{
	ztContextDX *context = zt_mallocStructArena(ztContextDX, arena);
	context->size.x          = client_w;
	context->size.y          = client_h;
	context->pixels_per_unit = pixels_per_unit;
	context->flags           = renderer_flags;
	context->handle          = (HWND)window;
	context->arena           = arena;

	DXGI_MODE_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(DXGI_MODE_DESC));

	buffer_desc.Width                   = client_w;
	buffer_desc.Height                  = client_h;
	buffer_desc.RefreshRate.Numerator   = 60;
	buffer_desc.RefreshRate.Denominator = 1;
	buffer_desc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	buffer_desc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	buffer_desc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount      = 1;                                    // one back buffer
	scd.BufferDesc       = buffer_desc;
	scd.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow     = context->handle;                 // the window to be used
	scd.SampleDesc.Count = 1;                               // how many multisamples
	scd.SwapEffect       = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed         = zt_bitIsSet(renderer_flags, ztRendererFlags_Windowed) ? TRUE : FALSE;

	zt_logInfo("DirectX: Creating swap chain");
	// create a device, device context and swap chain using the information in the scd struct
	i32 flags = 0;
#if defined(_DEBUG) && defined(ZT_DIRECTX_DEBUGGING)
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL feature_level;
	ztdx_callAndReturnValOnError(D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&context->swapchain,
		&context->device,
		&feature_level,
		&context->context), false);

	// get the address of the back buffer
	zt_logInfo("DirectX: Finding back buffer address");
	ID3D11Texture2D *backbuffer;
	ztdx_callAndReturnValOnError(context->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer), nullptr);

	// use the back buffer address to create the render target
	zt_logInfo("DirectX: Creating back buffer render target");
	ztdx_callAndReturnValOnError(context->device->CreateRenderTargetView(backbuffer, NULL, &context->backbuffer), nullptr);
	backbuffer->Release();

	D3D11_TEXTURE2D_DESC dsdesc;
	dsdesc.Width              = client_w;
	dsdesc.Height             = client_h;
	dsdesc.MipLevels          = 1;
	dsdesc.ArraySize          = 1;
	dsdesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsdesc.SampleDesc.Count   = 1;
	dsdesc.SampleDesc.Quality = 0;
	dsdesc.Usage              = D3D11_USAGE_DEFAULT;
	dsdesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	dsdesc.CPUAccessFlags     = 0;
	dsdesc.MiscFlags          = 0;

	//Create the Depth/Stencil View
	ztdx_callAndReturnValOnError(context->device->CreateTexture2D(&dsdesc, NULL, &context->depth_stencil_buffer), nullptr);
	ztdx_callAndReturnValOnError(context->device->CreateDepthStencilView(context->depth_stencil_buffer, NULL, &context->depth_stencil_view), nullptr);

	// set the render target as the back buffer
	zt_logInfo("DirectX: Setting context back buffer");
	context->context->OMSetRenderTargets(1, &context->backbuffer, context->depth_stencil_view);

	context->active_render_target = context->backbuffer;
	context->active_render_target_depth_stencil_view = context->depth_stencil_view;

	context->texture_count = 0;

	D3D11_DEPTH_STENCIL_DESC dssdesc;
	dssdesc.DepthEnable                  = true;
	dssdesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
	dssdesc.DepthFunc                    = D3D11_COMPARISON_LESS;
	dssdesc.StencilEnable                = true;
	dssdesc.StencilReadMask              = 0xFF;
	dssdesc.StencilWriteMask             = 0xFF;
	dssdesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	dssdesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dssdesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	dssdesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
	dssdesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
	dssdesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
	dssdesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
	dssdesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

	ztdx_callAndReturnValOnError(context->device->CreateDepthStencilState(&dssdesc, &context->stencil_state_enabled), nullptr);

	dssdesc.DepthEnable = true;
	dssdesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	ztdx_callAndReturnValOnError(context->device->CreateDepthStencilState(&dssdesc, &context->stencil_state_enabled_leq), nullptr);

	dssdesc.DepthEnable = true;
	dssdesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	ztdx_callAndReturnValOnError(context->device->CreateDepthStencilState(&dssdesc, &context->stencil_state_disabled), nullptr);

	if (!ztdx_setViewport(context)) {
		return false;
	}

	// alpha blending
	D3D11_BLEND_DESC blend_desc;
	ZeroMemory(&blend_desc, sizeof(blend_desc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable           = true;
	rtbd.SrcBlend              = D3D11_BLEND_SRC_ALPHA; //D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;// D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp               = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha         = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha        = D3D11_BLEND_ONE;
	rtbd.BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blend_desc.AlphaToCoverageEnable = false;
	blend_desc.RenderTarget[0] = rtbd;

	context->device->CreateBlendState(&blend_desc, &context->transparency);

	//Create the Counter Clockwise and Clockwise Culling States
	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.ScissorEnable = TRUE;

	cmdesc.FrontCounterClockwise = true;
	ztdx_callAndReturnValOnError(context->device->CreateRasterizerState(&cmdesc, &context->cull_mode_ccw), nullptr);

	cmdesc.FrontCounterClockwise = false;
	ztdx_callAndReturnValOnError(context->device->CreateRasterizerState(&cmdesc, &context->cull_mode_cw), nullptr);

	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = true;
	ztdx_callAndReturnValOnError(context->device->CreateRasterizerState(&cmdesc, &context->cull_mode_none), nullptr);

	return context;
}

// ------------------------------------------------------------------------------------------------

void ztdx_contextFree(ztContextDX *context)
{
	if (context->swapchain != nullptr) {
		context->swapchain->Release();
		context->backbuffer->Release();
		context->device->Release();
		context->context->Release();
		context->cull_mode_ccw->Release();
		context->cull_mode_cw->Release();
		context->cull_mode_none->Release();
		context->transparency->Release();
		context->depth_stencil_view->Release();
		context->depth_stencil_buffer->Release();
		context->stencil_state_enabled->Release();
		context->stencil_state_enabled_leq->Release();
		context->stencil_state_disabled->Release();
	}

	zt_freeArena(context, context->arena);
}

// ------------------------------------------------------------------------------------------------

void ztdx_contextDisplay(ztContextDX *context)
{
	context->swapchain->Present(0, 0);
}

// ------------------------------------------------------------------------------------------------

ztPoint2 ztdx_contextGetSize(ztContextDX *context)
{
	return context->size;
}

// ------------------------------------------------------------------------------------------------

bool ztdx_contextSetSize(ztContextDX *context, i32 w, i32 h)
{
	context->size.x = w;
	context->size.y = h;
	return ztdx_setViewport(context);
}

// ------------------------------------------------------------------------------------------------

bool ztdx_contextIsFullscreen(ztContextDX *context)
{
	return zt_bitIsSet(context->flags, ztRendererFlagsDX_Fullscreen);
}

// ------------------------------------------------------------------------------------------------

bool ztdx_contextToggleFullscreen(ztContextDX *context, bool fullscreen)
{
#if 0
	ztdx_callAndReturnValOnError(context->swapchain->SetFullscreenState(fullscreen ? TRUE : FALSE, NULL), false);
	ztdx_setViewport(context);
	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

void ztdx_clipRegionSet(ztContextDX *context, int left, int top, int right, int bottom)
{
	D3D11_RECT rect; rect.left = left; rect.top = top; rect.right = right; rect.bottom = bottom;
	context->context->RSSetScissorRects(1, &rect);
}

// ------------------------------------------------------------------------------------------------

void ztdx_clipRegionRemove(ztContextDX *context)
{
	D3D11_RECT rect; rect.left = 0; rect.top = 0; rect.right = context->size.x; rect.bottom = context->size.y;
	context->context->RSSetScissorRects(1, &rect);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool ztdx_checkAndReportError(const char *function, i32 hr)
{
	switch (hr)
	{
		case S_OK: return false;
		case D3D11_ERROR_FILE_NOT_FOUND                              : zt_logCritical("DirectX: Error: D3D11_ERROR_FILE_NOT_FOUND"); return true;
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS               : zt_logCritical("DirectX: Error: D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS"); return true;
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS                : zt_logCritical("DirectX: Error: D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS"); return true;
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD: zt_logCritical("DirectX: Error: D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD"); return true;
		case DXGI_ERROR_INVALID_CALL                                 : zt_logCritical("DirectX: Error: DXGI_ERROR_INVALID_CALL"); return true;
		case DXGI_ERROR_WAS_STILL_DRAWING                            : zt_logCritical("DirectX: Error: DXGI_ERROR_WAS_STILL_DRAWING"); return true;
		case E_FAIL                                                  : zt_logCritical("DirectX: Error: E_FAIL"); return true;
		case E_INVALIDARG                                            : zt_logCritical("DirectX: Error: E_INVALIDARG"); return true;
		case E_OUTOFMEMORY                                           : zt_logCritical("DirectX: Error: E_OUTOFMEMORY"); return true;
		case E_NOTIMPL                                               : zt_logCritical("DirectX: Error: E_NOTIMPL"); return true;
		case S_FALSE                                                 : zt_logCritical("DirectX: Error: S_FALSE"); return true;
		default                                                      : zt_logCritical("DirectX: Unknown error code: 0x%x (%d)", hr, hr); return true;
	}
}

// ------------------------------------------------------------------------------------------------

i32 ztdx_clearErrors()
{
	return 0;
}

// ------------------------------------------------------------------------------------------------

bool ztdx_setViewport(ztContextDX *context, i32 width, i32 height)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	viewport.Width = (r32)width;
	viewport.Height = (r32)height;

	context->context->RSSetViewports(1, &viewport);

	D3D11_RECT rect; rect.left = 0; rect.top = 0; rect.right = width; rect.bottom = height;
	context->context->RSSetScissorRects(1, &rect);
	return true;
}

// ------------------------------------------------------------------------------------------------

bool ztdx_setViewport(ztContextDX *context)
{
	return ztdx_setViewport(context, context->size.x, context->size.y);
}

// ------------------------------------------------------------------------------------------------

void ztdx_cullFront(ztContextDX *context)
{
	context->context->RSSetState(context->cull_mode_cw);
}

// ------------------------------------------------------------------------------------------------

void ztdx_cullBack(ztContextDX *context)
{
	context->context->RSSetState(context->cull_mode_ccw);
}

// ------------------------------------------------------------------------------------------------

void ztdx_cullNone(ztContextDX *context)
{
	context->context->RSSetState(context->cull_mode_none);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestOff(ztContextDX *context)
{
	context->context->OMSetDepthStencilState(context->stencil_state_disabled, 1);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestNever(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestLess(ztContextDX *context)
{
	context->context->OMSetDepthStencilState(context->stencil_state_enabled, 1);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestLessEqual(ztContextDX *context)
{
	context->context->OMSetDepthStencilState(context->stencil_state_enabled_leq, 1);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestEqual(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestGreater(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestNotEqual(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestGreaterEqual(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_depthTestAlways(ztContextDX *context)
{
	zt_assert(false);
}

// ------------------------------------------------------------------------------------------------

void ztdx_clear(ztContextDX *context, ztVec4& color)
{
	ztdx_clear(context, color.values);
}

// ------------------------------------------------------------------------------------------------

void ztdx_clear(ztContextDX *context, r32 color[4])
{
	context->context->ClearRenderTargetView(context->active_render_target, color);
	context->context->ClearDepthStencilView(context->active_render_target_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

// ------------------------------------------------------------------------------------------------

void ztdx_clear(ztContextDX *context, r32 r, r32 g, r32 b, r32 a)
{
	r32 color[] = { r, g, b, a };
	ztdx_clear(context, color);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztShaderDX *ztdx_shaderMake(ztContextDX *context, const char *vert_src, const char *vert_func, const char *frag_src, const char *frag_func)
{
	return ztdx_shaderMake(zt_memGetGlobalArena(), context, vert_src, vert_func, frag_src, frag_func);
}

// ------------------------------------------------------------------------------------------------

ztShaderDX *ztdx_shaderMake(ztMemoryArena *arena, ztContextDX *context, const char *vert_src, const char *vert_func, const char *frag_src, const char *frag_func)
{
	struct local
	{
		static bool load_shader(const char *src, const char *entry, const char *target, ID3DBlob **shader)
		{
			ID3DBlob *blob_error = nullptr;
			i32 hr = D3DCompile(src, zt_strLen(src), NULL, NULL, NULL, entry, target, 0, 0, shader, &blob_error);
			if (blob_error != nullptr) {
				char *b_error = (char*)blob_error->GetBufferPointer();
				SIZE_T b_error_len = blob_error->GetBufferSize();

				char error_buffer[1024 * 16];
				zt_strCpy(error_buffer, sizeof(error_buffer), b_error, (int)b_error_len);
				zt_logCritical("DirectX compile failure: %s", error_buffer);
				return false;
			}

			return true;
		}
	};

	ID3D10Blob *vert = nullptr, *frag = nullptr;

	if (!local::load_shader(vert_src, vert_func, "vs_4_0", &vert)) {
		zt_logCritical("Unable to compile DirectX vertex shader.");
		return nullptr;
	}
	if (!local::load_shader(frag_src, frag_func, "ps_4_0", &frag)) {
		zt_logCritical("Unable to compile DirectX pixel shader.");
		return nullptr;
	}

	ztShaderDX *shader = zt_mallocStructArena(ztShaderDX, arena);
	shader->arena = arena;

	ztdx_callAndReturnValOnError(context->device->CreateVertexShader(vert->GetBufferPointer(), vert->GetBufferSize(), NULL, &shader->vert), nullptr);
	ztdx_callAndReturnValOnError(context->device->CreatePixelShader(frag->GetBufferPointer(), frag->GetBufferSize(), NULL, &shader->frag), nullptr);

	context->context->VSSetShader(shader->vert, NULL, NULL);
	context->context->PSSetShader(shader->frag, NULL, NULL);

	shader->cbuffers_count = 0;
	int cbuffers_count = 0;
	int variables_count = 0;

	zt_fkz(2) {
		ID3D11ShaderReflection *reflection = nullptr;

		ID3D10Blob *shad = k == 0 ? vert : frag;
		ztdx_callAndReportOnError(D3DReflect(shad->GetBufferPointer(), shad->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection));
		if (reflection) {
			D3D11_SHADER_DESC shader_desc;
			if (SUCCEEDED(reflection->GetDesc(&shader_desc))) {
				cbuffers_count += shader_desc.ConstantBuffers;

				zt_fiz(shader_desc.BoundResources) {
					variables_count += 1;
				}

				zt_fiz(shader_desc.ConstantBuffers) {
					ID3D11ShaderReflectionConstantBuffer *buffer = reflection->GetConstantBufferByIndex(i);
					if (!buffer) {
						zt_logCritical("DirectX: Unable to get constant buffer index %d", i);
						return nullptr;
					}
					D3D11_SHADER_BUFFER_DESC bdesc;
					buffer->GetDesc(&bdesc);

					variables_count += bdesc.Variables;

					zt_fjz(bdesc.Variables) {
						ID3D11ShaderReflectionVariable* variable = buffer->GetVariableByIndex(j);
						if (!variable) {
							zt_logCritical("DirectX: Unable to get variables for constant buffer index %d", i);
							return nullptr;
						}
						D3D11_SHADER_VARIABLE_DESC vdesc;
						variable->GetDesc(&vdesc);

						ID3D11ShaderReflectionType* type = variable->GetType();
						D3D11_SHADER_TYPE_DESC tdesc;
						type->GetDesc(&tdesc);

						if (tdesc.Class == D3D_SVC_STRUCT) {
							variables_count += (tdesc.Elements * tdesc.Members) - 1;
						}
					}
				}
			}
		}
	}

	shader->cbuffers = zt_mallocStructArrayArena(ztShaderDX::ConstantBuffer, cbuffers_count, arena);
	shader->variables = zt_mallocStructArrayArena(ztShaderDX::Variable, variables_count, arena);

	zt_fkz(2) {
		ID3D11ShaderReflection *reflection = nullptr;

		ID3D10Blob *shad = k == 0 ? vert : frag;
		ztdx_callAndReportOnError(D3DReflect(shad->GetBufferPointer(), shad->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection));
		if (reflection) {
			D3D11_SHADER_DESC shader_desc;
			if (SUCCEEDED(reflection->GetDesc(&shader_desc))) {
				int layouts_size = variables_count;
				D3D11_INPUT_ELEMENT_DESC *layouts = zt_mallocStructArrayArena(D3D11_INPUT_ELEMENT_DESC, variables_count, arena);
				int layouts_count = 0;
				i32 bytes_offset = 0;
				if (k == 0) {
					zt_fiz(zt_min(layouts_size, (i32)shader_desc.InputParameters)) {
						D3D11_SIGNATURE_PARAMETER_DESC param_desc;
						if (FAILED(reflection->GetInputParameterDesc(i, &param_desc))) {
							continue;
						}

						int idx = layouts_count++;
						zt_assert(idx < layouts_size);

						layouts[idx].SemanticName         = param_desc.SemanticName;
						layouts[idx].SemanticIndex        = param_desc.SemanticIndex;
						layouts[idx].InputSlot            = 0;
						layouts[idx].AlignedByteOffset    = bytes_offset;
						layouts[idx].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
						layouts[idx].InstanceDataStepRate = 0;

						if (param_desc.Mask == 1) {
							if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) layouts[idx].Format = DXGI_FORMAT_R32_UINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) layouts[idx].Format = DXGI_FORMAT_R32_SINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) layouts[idx].Format = DXGI_FORMAT_R32_FLOAT;
							bytes_offset += 4;
						}
						else if (param_desc.Mask <= 3) {
							if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) layouts[idx].Format = DXGI_FORMAT_R32G32_UINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) layouts[idx].Format = DXGI_FORMAT_R32G32_SINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) layouts[idx].Format = DXGI_FORMAT_R32G32_FLOAT;
							bytes_offset += 8;
						}
						else if (param_desc.Mask <= 7) {
							if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32_UINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32_SINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32_FLOAT;
							bytes_offset += 12;
						}
						else if (param_desc.Mask <= 15) {
							if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32A32_UINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32A32_SINT;
							else if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) layouts[idx].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
							bytes_offset += 16;
						}
					}
				}
				else {
					zt_fiz((i32)shader_desc.BoundResources) {
						D3D11_SHADER_INPUT_BIND_DESC ibdesc;
						reflection->GetResourceBindingDesc(i, &ibdesc);

						int idx = shader->variables_count++;
						zt_strCpy(shader->variables[idx].name, zt_sizeof(shader->variables[idx].name), ibdesc.Name);
						shader->variables[idx].type = ztShaderDXVariableType_Invalid;
						shader->variables[idx].name_hash = zt_strHash(shader->variables[idx].name);

						shader->variables[idx].cbuffer = -1;
						shader->variables[idx].offset  = -1;
						shader->variables[idx].shader  = -1;

						switch (ibdesc.Type)
						{
							case D3D_SIT_TEXTURE: {
								shader->variables[idx].type   = ztShaderDXVariableType_Tex;
								shader->variables[idx].size   = zt_sizeof(pointer);
								shader->variables[idx].data   = zt_mallocStructArrayArena(byte, shader->variables[idx].size, arena);
								shader->variables[idx].offset = ibdesc.BindPoint;
							} break;
						}
					}
				}

				if (layouts_count > 0) {
					ztdx_callAndReportOnError(context->device->CreateInputLayout(layouts, layouts_count, vert->GetBufferPointer(), vert->GetBufferSize(), &shader->layout));
				}

				bytes_offset = 0;
				zt_fiz(shader_desc.ConstantBuffers) {
					u32 register_idx = 0;
					ID3D11ShaderReflectionConstantBuffer *buffer = reflection->GetConstantBufferByIndex(i);
					if (!buffer) {
						zt_logCritical("DirectX: Unable to get constant buffer index %d", i);
						return nullptr;
					}
					D3D11_SHADER_BUFFER_DESC bdesc;
					buffer->GetDesc(&bdesc);

					zt_fjz((i32)shader_desc.BoundResources) {
						D3D11_SHADER_INPUT_BIND_DESC ibdesc;
						reflection->GetResourceBindingDesc(j, &ibdesc);

						if (zt_strEquals(ibdesc.Name, bdesc.Name)) {
							register_idx = ibdesc.BindPoint;
							break;
						}
					}

					zt_fjz((i32)bdesc.Variables) {
						ID3D11ShaderReflectionVariable* variable = buffer->GetVariableByIndex(j);
						if (!variable) {
							zt_logCritical("DirectX: Unable to get variables for constant buffer index %d", i);
							return nullptr;
						}
						D3D11_SHADER_VARIABLE_DESC vdesc;
						variable->GetDesc(&vdesc);

						if (shader->variables_count < ZT_SHADER_MAX_VARIABLES) {
							struct local
							{
								static int processReflectionType(int which_shader, int cbuffer, ztShaderDX *shader, ID3D11ShaderReflectionType *type, D3D11_SHADER_VARIABLE_DESC *vdesc, const char *element_name, int element_struct_size, ztMemoryArena *arena)
								{
									D3D11_SHADER_TYPE_DESC tdesc;
									type->GetDesc(&tdesc);

									if (tdesc.Class == D3D_SVC_STRUCT) {
										int offset = vdesc->StartOffset;
										zt_fkz(tdesc.Elements) {
											zt_fiz(tdesc.Members) {
												ID3D11ShaderReflectionType *mtype = type->GetMemberTypeByIndex(i);
												const char *name = type->GetMemberTypeName(i);
												zt_strMakePrintf(var_name, 256, "%s[%d].%s", vdesc->Name, k, name);
												offset += processReflectionType(which_shader, cbuffer, shader, mtype, vdesc, var_name, offset, arena);
											}
										}
									}
									else {
										int idx = shader->variables_count++;
										if (element_name) {
											zt_strCpy(shader->variables[idx].name, zt_sizeof(shader->variables[idx].name), element_name);
										}
										else {
											zt_strCpy(shader->variables[idx].name, zt_sizeof(shader->variables[idx].name), vdesc->Name);
										}
										shader->variables[idx].name_hash = zt_strHash(shader->variables[idx].name);
										shader->variables[idx].type = ztShaderDXVariableType_Invalid;

										int size = 0;
										switch (tdesc.Class)
										{
											case D3D_SVC_SCALAR: {
												if (tdesc.Type == D3D_SVT_FLOAT) { shader->variables[idx].type = ztShaderDXVariableType_Float; size = 4; }
												else if (tdesc.Type == D3D_SVT_INT) { shader->variables[idx].type = ztShaderDXVariableType_Int; size = 4; }
											} break;

											case D3D_SVC_VECTOR: {
												if (tdesc.Type == D3D_SVT_FLOAT) {
													if (tdesc.Rows == 1 && tdesc.Columns == 4) { shader->variables[idx].type = ztShaderDXVariableType_Vec4; size = 16; }
													else if (tdesc.Rows == 1 && tdesc.Columns == 3) { shader->variables[idx].type = ztShaderDXVariableType_Vec3; size = 12; }
													else if (tdesc.Rows == 1 && tdesc.Columns == 2) { shader->variables[idx].type = ztShaderDXVariableType_Vec2; size = 8; }
												}
											} break;

											case D3D_SVC_MATRIX_COLUMNS: {
												if (tdesc.Type == D3D_SVT_FLOAT) {
													if (tdesc.Rows == 4 && tdesc.Columns == 4) { shader->variables[idx].type = ztShaderDXVariableType_Mat4; size = 64; }
													else if (tdesc.Rows == 3 && tdesc.Columns == 3) { shader->variables[idx].type = ztShaderDXVariableType_Mat3; size = 36; }
													else if (tdesc.Rows == 1 && tdesc.Columns == 2) { shader->variables[idx].type = ztShaderDXVariableType_Vec2; size = 8; }
												}
											} break;

											default: {
												shader->variables_count--;
												return 0;
											} break;
										}

										int size_add = 0;
										if (element_struct_size != 0) {
											if (16 - (element_struct_size % 16) < size) {
												size_add = 16 - (element_struct_size % 16);
												element_struct_size += size_add;
											}
										}

										shader->variables[idx].offset  = element_struct_size == 0 ? vdesc->StartOffset : element_struct_size;
										shader->variables[idx].size    = size;
										shader->variables[idx].shader  = which_shader;
										shader->variables[idx].cbuffer = cbuffer;
										shader->variables[idx].data    = zt_mallocStructArrayArena(byte, size, arena);

										return size + size_add;
									}

									return 0;
								}
							};

							ID3D11ShaderReflectionType* type = variable->GetType();
							local::processReflectionType(k, shader->cbuffers_count, shader, type, &vdesc, nullptr, 0, arena);
						}
					}

					D3D11_BUFFER_DESC cbbd;
					ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

					i32 size = bdesc.Size;
					if (size % 16 != 0) {
						size += 16 - (size % 16);
					}

					cbbd.Usage          = D3D11_USAGE_DEFAULT;
					cbbd.ByteWidth      = size;
					cbbd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
					cbbd.CPUAccessFlags = 0;// D3D11_CPU_ACCESS_WRITE;
					cbbd.MiscFlags      = 0;

					shader->cbuffers[shader->cbuffers_count].shader = k;
					ztdx_callAndReportOnError(context->device->CreateBuffer(&cbbd, NULL, &shader->cbuffers[shader->cbuffers_count++].buffer));
				}
				zt_freeArena(layouts, arena);
			}
			reflection->Release();
		}

#		if 0
		ID3D10Blob *disassembly = nullptr;
		D3DDisassemble(shad->GetBufferPointer(), shad->GetBufferSize(), D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS | D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING, NULL, &disassembly);
		if (disassembly) {
			char temp[1024 * 32];
			zt_strCpy(temp, zt_sizeof(temp), (char*)disassembly->GetBufferPointer(), disassembly->GetBufferSize());
			zt_logDebug(temp);
		}
#		endif
	}

	zt_assert(variables_count >= shader->variables_count);
	zt_assert(cbuffers_count >= shader->cbuffers_count);

	return shader;
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderFree(ztContextDX *context, ztShaderDX *shader)
{
	if (shader == nullptr) {
		return;
	}

	if (shader->vert) {
		shader->vert->Release();
	}
	if (shader->frag) {
		shader->frag->Release();
	}
	if (shader->layout) {
		shader->layout->Release();
	}
	zt_fiz(shader->cbuffers_count) {
		shader->cbuffers[i].buffer->Release();
	}
	zt_fiz(shader->variables_count) {
		zt_freeArena(shader->variables[i].data, shader->arena);
	}

	zt_freeArena(shader->cbuffers, shader->arena);
	zt_freeArena(shader->variables, shader->arena);
	zt_freeArena(shader, shader->arena);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderBegin(ztContextDX *context, ztShaderDX *shader)
{
	context->context->VSSetShader(shader->vert, NULL, NULL);
	context->context->PSSetShader(shader->frag, NULL, NULL);

	ID3D11ShaderResourceView *srvnull = nullptr;
	ID3D11SamplerState       *ssnull  = nullptr;

	zt_fiz(context->texture_count) {
		context->context->PSSetShaderResources(i, 1, &srvnull);
		context->context->PSSetSamplers(i, 1, &ssnull);
	}
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderEnd(ztContextDX *context, ztShaderDX *shader)
{
	context->context->VSSetShader(NULL, NULL, NULL);
	context->context->PSSetShader(NULL, NULL, NULL);
}

// ------------------------------------------------------------------------------------------------

bool ztdx_shaderHasVariable(ztShaderDX *shader, u32 name_hash)
{
	zt_returnValOnNull(shader, false);
	zt_fiz(shader->variables_count) {
		if (shader->variables[i].name_hash == name_hash) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _ztdx_shaderVariableValue(ztShaderDX *shader, u32 name_hash, void *value, i32 value_size)
{
	zt_returnOnNull(shader);
	int idx = -1;
	zt_fiz(shader->variables_count) {
		if (shader->variables[i].name_hash == name_hash) {
			idx = i;
			break;
		}
	}
	if (idx == -1) {
		return;
	}

	zt_memCpy(shader->variables[idx].data, shader->variables[idx].size, value, value_size);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableFloat(ztShaderDX *shader, u32 name_hash, r32 value)
{
	_ztdx_shaderVariableValue(shader, name_hash, &value, zt_sizeof(value));
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableInt(ztShaderDX *shader, u32 name_hash, i32 value)
{
	_ztdx_shaderVariableValue(shader, name_hash, &value, zt_sizeof(value));
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableVec2(ztShaderDX *shader, u32 name_hash, r32 value[2])
{
	_ztdx_shaderVariableValue(shader, name_hash, value, zt_sizeof(r32) * 2);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableVec3(ztShaderDX *shader, u32 name_hash, r32 value[3])
{
	_ztdx_shaderVariableValue(shader, name_hash, value, zt_sizeof(r32) * 3);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableVec4(ztShaderDX *shader, u32 name_hash, r32 value[4])
{
	_ztdx_shaderVariableValue(shader, name_hash, value, zt_sizeof(r32) * 4);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableMat4(ztShaderDX *shader, u32 name_hash, r32 value[16])
{
	_ztdx_shaderVariableValue(shader, name_hash, value, zt_sizeof(r32) * 16);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableMat3(ztShaderDX *shader, u32 name_hash, r32 value[9])
{
	_ztdx_shaderVariableValue(shader, name_hash, value, zt_sizeof(r32) * 9);
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderVariableTex(ztShaderDX *shader, u32 name_hash, ztTextureDX *value)
{
	_ztdx_shaderVariableValue(shader, name_hash, &value, zt_sizeof(value));
}

// ------------------------------------------------------------------------------------------------

void ztdx_shaderPopulateConstantBuffers(ztContextDX *context, ztShaderDX *shader)
{
	zt_returnOnNull(shader);

	int cbuffer_count[2] = { 0 };

	zt_fkz(shader->cbuffers_count) {
		i32 cbuffer_idx = k;
		byte cbuffer_data[1024 * 4];

		zt_fiz(shader->variables_count) {
			if (shader->variables[i].cbuffer != cbuffer_idx || shader->variables[i].type == ztShaderDXVariableType_Tex || shader->variables[i].type == ztShaderDXVariableType_TexCube) {
				continue;
			}

			int cbuffer_pos = shader->variables[i].offset;

			r32 data[128];
			zt_memCpy(data, shader->variables[i].size, shader->variables[i].data, shader->variables[i].size);

			i32 size = 0;
			switch (shader->variables[i].type)
			{
				case ztShaderDXVariableType_Float  : size = zt_sizeof(r32); break;
				case ztShaderDXVariableType_Int    : size = zt_sizeof(i32); break;
				case ztShaderDXVariableType_Vec2   : size = zt_sizeof(r32) * 2; break;
				case ztShaderDXVariableType_Vec3   : size = zt_sizeof(r32) * 3; break;
				case ztShaderDXVariableType_Vec4   : size = zt_sizeof(r32) * 4; break;
				case ztShaderDXVariableType_Mat3: {
					size = zt_sizeof(r32) * 9;
					r32 *value = (r32*)shader->variables[i].data;
					data[1] = value[3];
					data[2] = value[6];
					data[3] = value[1];
					data[5] = value[7];
					data[6] = value[2];
					data[7] = value[5];
				} break;
				case ztShaderDXVariableType_Mat4: {
					size = zt_sizeof(r32) * 16;
					r32 *value = (r32*)shader->variables[i].data;
					data[0] = value[ 0]; data[4] = value[ 1]; data[ 8] = value[ 2]; data[12] = value[ 3];
					data[1] = value[ 4]; data[5] = value[ 5]; data[ 9] = value[ 6]; data[13] = value[ 7];
					data[2] = value[ 8]; data[6] = value[ 9]; data[10] = value[10]; data[14] = value[11];
					data[3] = value[12]; data[7] = value[13]; data[11] = value[14]; data[15] = value[15];
				} break;
			}

			zt_memCpy(cbuffer_data + cbuffer_pos, size, data, size);
		}

		cbuffer_count[shader->cbuffers[cbuffer_idx].shader] += 1;

		context->context->UpdateSubresource(shader->cbuffers[cbuffer_idx].buffer, 0, NULL, cbuffer_data, 0, 0);
		int slot = cbuffer_count[shader->cbuffers[cbuffer_idx].shader] - 1;
		if (shader->cbuffers[cbuffer_idx].shader == 0) {
			context->context->VSSetConstantBuffers(slot, 1, &shader->cbuffers[cbuffer_idx].buffer);
		}
		else {
			context->context->PSSetConstantBuffers(slot, 1, &shader->cbuffers[cbuffer_idx].buffer);
		}
	}

	context->context->IASetInputLayout(shader->layout);

	context->texture_count = 0;
	zt_fiz(shader->variables_count) {
		if (shader->variables[i].type == ztShaderDXVariableType_Tex || shader->variables[i].type == ztShaderDXVariableType_TexCube) {
			ztTextureDX *tex = nullptr;
			zt_memCpy(&tex, zt_sizeof(tex), shader->variables[i].data, zt_sizeof(tex));
			if (tex) {
				context->context->PSSetShaderResources(shader->variables[i].offset, 1, &tex->shader_resource_view);
				context->context->PSSetSamplers(shader->variables[i].offset, 1, &tex->sampler_state);
			}
			context->texture_count += 1;
		}
	}

	if (context->texture_count > 0) {
		float blend_factor[] = { 1.f, 1.f, 1.f, 1.f };
		context->context->OMSetBlendState(context->transparency, blend_factor, 0xffffffff);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal ztTextureDX *_ztdx_textureMakeBase(ztMemoryArena *arena, ztContextDX *context, byte *pixel_data, i32 width, i32 height, i32 depth, i32 flags)
{
#if 1
	if (pixel_data) {
		int half_height = height / 2;
		u32* pix_u32 = ((u32*)pixel_data);
		for (int y = 0; y < half_height; ++y) {
			for (int x = 0; x < width; ++x) {
				int idx_1 = (y * width) + x;
				int idx_2 = (((height - y) - 1) * width) + x;
				uint32 pixel = pix_u32[idx_2];
				pix_u32[idx_2] = pix_u32[idx_1];
				pix_u32[idx_1] = pixel;
			}
		}
	}
#endif
	bool render_target = pixel_data == nullptr;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width              = width;
	desc.Height             = height;
	desc.MipLevels          = 1; // zt_bitIsSet(flags, ztTextureFlags_MipMaps) ? 0 : 1; // this is crashing
	desc.ArraySize          = 1;
	desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
	desc.Usage              = D3D11_USAGE_DEFAULT;
	desc.BindFlags          = (render_target ? D3D11_BIND_RENDER_TARGET : 0) | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags     = 0;
	desc.MiscFlags          = 0;

	D3D11_SUBRESOURCE_DATA subr;
	subr.pSysMem          = pixel_data;
	subr.SysMemPitch      = width * 4;
	subr.SysMemSlicePitch = width * height * 4; // not needed in 2d tex

	ID3D11Texture2D *dx_tex;
	if (FAILED(context->device->CreateTexture2D(&desc, (render_target ? nullptr : &subr), &dx_tex))) {
		zt_logCritical("CreateTexture2D failed.");
		return nullptr;
	}

	ID3D11RenderTargetView *dx_render_target_view   = nullptr;
	ID3D11Texture2D        *dx_depth_stencil_buffer = nullptr;
	ID3D11DepthStencilView *dx_depth_stencil_view   = nullptr;

	if (render_target) {
		D3D11_TEXTURE2D_DESC dsdesc;

		dsdesc.Width              = width;
		dsdesc.Height             = height;
		dsdesc.MipLevels          = 1;
		dsdesc.ArraySize          = 1;
		dsdesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsdesc.SampleDesc.Count   = 1;
		dsdesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
		dsdesc.Usage              = D3D11_USAGE_DEFAULT;
		dsdesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		dsdesc.CPUAccessFlags     = 0;
		dsdesc.MiscFlags          = 0;

		if (FAILED(context->device->CreateTexture2D(&dsdesc, NULL, &dx_depth_stencil_buffer))) {
			zt_logCritical("CreateTexture2D failed.");
			return nullptr;
		}
		if (FAILED(context->device->CreateDepthStencilView(dx_depth_stencil_buffer, NULL, &dx_depth_stencil_view))) {
			zt_logCritical("CreateDepthStencilView failed.");
			return nullptr;
		}


		D3D11_RENDER_TARGET_VIEW_DESC rtvd;
		ZeroMemory(&rtvd, zt_sizeof(rtvd));
		rtvd.Format             = desc.Format;
		rtvd.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = 0;

		if (FAILED(context->device->CreateRenderTargetView(dx_tex, &rtvd, &dx_render_target_view))) {
			zt_logCritical("CreateRenderTargetView failed.");
			return nullptr;
		}
	}

	ID3D11ShaderResourceView *dx_shader_resource_view;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, zt_sizeof(srvd));

	srvd.Format                    = desc.Format;
	srvd.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels       = 1;

	if (FAILED(context->device->CreateShaderResourceView(dx_tex, (render_target ? &srvd : nullptr), &dx_shader_resource_view))) {
		zt_logCritical("CreateShaderResourceView failed.");
		return nullptr;
	}

	ID3D11SamplerState *dx_sampler_state;

	D3D11_SAMPLER_DESC samp_desc;
	ZeroMemory(&samp_desc, sizeof(samp_desc));
	if (zt_bitIsSet(flags, ztTextureFlags_PixelPerfect)) {
		samp_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	}
	else {
		samp_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	}
	samp_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samp_desc.MinLOD         = 0;
	samp_desc.MaxLOD         = D3D11_FLOAT32_MAX;

	if (FAILED(context->device->CreateSamplerState(&samp_desc, &dx_sampler_state))) {
		zt_logCritical("CreateSamplerState failed.");
		return nullptr;
	}

	ztTextureDX *texture = zt_mallocStructArena(ztTextureDX, arena);

	texture->arena                = arena;
	texture->size.x               = width;
	texture->size.y               = height;
	texture->tex                  = dx_tex;
	texture->shader_resource_view = dx_shader_resource_view;
	texture->sampler_state        = dx_sampler_state;
	texture->depth_stencil_buffer = dx_depth_stencil_buffer;
	texture->depth_stencil_view   = dx_depth_stencil_view;
	texture->render_target_view   = dx_render_target_view;
	texture->flags                = flags;

	return texture;
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeFromPixelData(ztContextDX *context, byte *pixels, int w, int h, int d, i32 flags)
{
	return ztdx_textureMakeFromPixelData(zt_memGetGlobalArena(), context, pixels, w, h, d, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeFromPixelData(ztMemoryArena *arena, ztContextDX *context, byte *pixels, int w, int h, int d, i32 flags)
{
	return _ztdx_textureMakeBase(arena, context, pixels, w, h, d, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeCubeMapFromPixelData(ztContextDX *context, byte **pixels, int w, int h, int d)
{
	return ztdx_textureMakeCubeMapFromPixelData(zt_memGetGlobalArena(), context, pixels, w, h, d);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeCubeMapFromPixelData(ztMemoryArena *arena, ztContextDX *context, byte **pixels, int w, int h, int d)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width              = w;
	desc.Height             = h;
	desc.MipLevels          = 1;
	desc.ArraySize          = 6;
	desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage              = D3D11_USAGE_DEFAULT;
	desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags     = 0;
	desc.MiscFlags          = D3D11_RESOURCE_MISC_TEXTURECUBE;

	ID3D11ShaderResourceView *dx_shader_resource_view;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, zt_sizeof(srvd));

	srvd.Format                    = desc.Format;
	srvd.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvd.Texture2D.MipLevels       = desc.MipLevels;
	srvd.Texture2D.MostDetailedMip = 0;

	D3D11_SUBRESOURCE_DATA subr[ztTextureCubeMapFiles_MAX];
	zt_fiz(ztTextureCubeMapFiles_MAX) {
		subr[i].pSysMem          = pixels[i];
		subr[i].SysMemPitch      = w * 4;
		subr[i].SysMemSlicePitch = w * h * 4;
		desc.Width  = w;
		desc.Height = h;
	}

	ID3D11Texture2D *dx_tex;
	if (FAILED(context->device->CreateTexture2D(&desc, subr, &dx_tex))) {
		zt_logCritical("CreateTexture2D failed.");
		return nullptr;
	}

	if (FAILED(context->device->CreateShaderResourceView(dx_tex, &srvd, &dx_shader_resource_view))) {
		zt_logCritical("CreateShaderResourceView failed.");
		return nullptr;
	}

	ID3D11SamplerState *dx_sampler_state;

	D3D11_SAMPLER_DESC samp_desc;
	ZeroMemory(&samp_desc, sizeof(samp_desc));
	samp_desc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samp_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
	samp_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samp_desc.MinLOD         = 0;
	samp_desc.MaxLOD         = D3D11_FLOAT32_MAX;

	if (FAILED(context->device->CreateSamplerState(&samp_desc, &dx_sampler_state))) {
		zt_logCritical("CreateSamplerState failed.");
		return nullptr;
	}

	ztTextureDX *texture = zt_mallocStructArena(ztTextureDX, arena);

	texture->arena                = arena;
	texture->size.x               = w;
	texture->size.y               = h;
	texture->tex                  = dx_tex;
	texture->shader_resource_view = dx_shader_resource_view;
	texture->sampler_state        = dx_sampler_state;
	texture->depth_stencil_buffer = nullptr;
	texture->depth_stencil_view   = nullptr;
	texture->render_target_view   = nullptr;
	texture->flags                = ztTextureDXFlags_CubeMap;

	return texture;
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeRenderTarget(ztContextDX *context, int w, int h, i32 flags)
{
	return ztdx_textureMakeRenderTarget(zt_memGetGlobalArena(), context, w, h, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeRenderTarget(ztMemoryArena *arena, ztContextDX *context, int w, int h, i32 flags)
{
	return _ztdx_textureMakeBase(arena, context, nullptr, w, h, 4, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeDepthRenderTarget(ztContextDX *context, int w, int h)
{
	return ztdx_textureMakeDepthRenderTarget(zt_memGetGlobalArena(), context, w, h);
}

// ------------------------------------------------------------------------------------------------

ztTextureDX *ztdx_textureMakeDepthRenderTarget(ztMemoryArena *arena, ztContextDX *context, int w, int h)
{
	return _ztdx_textureMakeBase(arena, context, nullptr, w, h, 4, ztTextureDXFlags_DepthMap);
}

// ------------------------------------------------------------------------------------------------

void ztdx_textureFree(ztTextureDX *texture)
{
	if (texture == nullptr) {
		return;
	}

	texture->sampler_state->Release();
	texture->shader_resource_view->Release();
	texture->tex->Release();

	if (texture->render_target_view) {
		texture->render_target_view->Release();
		texture->depth_stencil_buffer->Release();
		texture->depth_stencil_view->Release();
	}

	zt_freeArena(texture, texture->arena);
}

// ------------------------------------------------------------------------------------------------

void ztdx_textureRenderTargetPrepare(ztContextDX *context, ztTextureDX *texture)
{
	ID3D11ShaderResourceView *srvnull = nullptr;
	ID3D11SamplerState       *ssnull  = nullptr;

	zt_fiz(context->texture_count) {
		context->context->PSSetShaderResources(i, 1, &srvnull);
		context->context->PSSetSamplers(i, 1, &ssnull);
	}
	context->texture_count = 0;

	ID3D11RenderTargetView *rtvnull = nullptr;
	context->context->OMSetRenderTargets(1, &rtvnull, NULL);
	context->context->OMSetRenderTargets(1, &texture->render_target_view, texture->depth_stencil_view);

//	context->context->ClearRenderTargetView(texture->render_target_view, clear.values);
	context->context->ClearDepthStencilView(texture->depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

	context->active_render_target = texture->render_target_view;
	context->active_render_target_depth_stencil_view = texture->depth_stencil_view;

	if (zt_bitIsSet(texture->flags, ztTextureDXFlags_DepthMap)) {
		ztdx_cullNone(context);
	}

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	viewport.Width  = (r32)texture->size.x;
	viewport.Height = (r32)texture->size.y;

	context->context->RSSetViewports(1, &viewport);
	D3D11_RECT rect; rect.left = 0; rect.top = 0; rect.right = (i32)viewport.Width; rect.bottom = (i32)viewport.Height;
	context->context->RSSetScissorRects(1, &rect);
}

// ------------------------------------------------------------------------------------------------

void ztdx_textureRenderTargetCommit(ztContextDX *context, ztTextureDX *texture)
{
	if (zt_bitIsSet(texture->flags, ztTextureDXFlags_DepthMap)) {
		ztdx_cullBack(context);
	}

	ID3D11RenderTargetView *rtvnull = nullptr;
	context->context->OMSetRenderTargets(1, &rtvnull, nullptr);
	context->context->OMSetRenderTargets(1, &context->backbuffer, context->depth_stencil_view);
	context->active_render_target = context->backbuffer;
	context->active_render_target_depth_stencil_view = context->depth_stencil_view;

	ztdx_setViewport(context);
}

// ------------------------------------------------------------------------------------------------

bool ztdx_textureIsRenderTarget(ztTextureDX *texture)
{
	zt_returnValOnNull(texture, false);
	return texture->render_target_view != nullptr;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztVertexArrayDX *ztdx_vertexArrayMake(ztContextDX *context, ztVertexEntryDX *entries, int entries_count, void *vert_data, int vert_count)
{
	return ztdx_vertexArrayMake(zt_memGetGlobalArena(), context, entries, entries_count, vert_data, vert_count);
}

// ------------------------------------------------------------------------------------------------

ztVertexArrayDX *ztdx_vertexArrayMake(ztMemoryArena *arena, ztContextDX *context, ztVertexEntryDX *entries, int entries_count, void *vert_data, int vert_count)
{
	zt_assertReturnValOnFail(entries_count > 0, nullptr);

	ztVertexArrayDX *vertex_array = zt_mallocStructArena(ztVertexArrayDX, arena);
	vertex_array->entries = zt_mallocStructArrayArena(ztVertexEntryDX, entries_count, arena);
	vertex_array->entries_count = entries_count;
	zt_memCpy(vertex_array->entries, entries_count * zt_sizeof(ztVertexEntryDX), entries, entries_count *  zt_sizeof(ztVertexEntryDX));

	int vert_size = 0;
	zt_fiz(entries_count) {
		vert_size += entries[i].size;
	}

	// vertex buffer
	D3D11_BUFFER_DESC vb;
	ZeroMemory(&vb, sizeof(vb));

	vb.Usage          = D3D11_USAGE_DEFAULT;
	vb.ByteWidth      = vert_size * vert_count;
	vb.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	vb.CPUAccessFlags = 0;

	if (vert_data != nullptr) {
		D3D11_SUBRESOURCE_DATA vb_data;
		ZeroMemory(&vb_data, sizeof(vb_data));
		vb_data.pSysMem = vert_data;

		ztdx_callAndReturnValOnError(context->device->CreateBuffer(&vb, &vb_data, &vertex_array->buff_vert), nullptr);
	}
	else {
		vb.Usage          = D3D11_USAGE_DYNAMIC;
		vb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ztdx_callAndReturnValOnError(context->device->CreateBuffer(&vb, nullptr, &vertex_array->buff_vert), nullptr);
	}
	vertex_array->stride     = vert_size;
	vertex_array->vert_count = vert_count;
	vertex_array->arena      = arena;

	return vertex_array;
}

// ------------------------------------------------------------------------------------------------

void ztdx_vertexArrayFree(ztVertexArrayDX *vertex_array)
{
	if (vertex_array == nullptr) {
		return;
	}

	if (vertex_array->buff_vert) {
		vertex_array->buff_vert->Release();
	}

	zt_freeArena(vertex_array->entries, vertex_array->arena);
	zt_freeArena(vertex_array, vertex_array->arena);
}

// ------------------------------------------------------------------------------------------------

void ztdx_vertexArrayUpdate(ztContextDX *context, ztVertexArrayDX *vertex_array, void *vert_data, int vert_count)
{
	D3D11_MAPPED_SUBRESOURCE ms;
	ztdx_callAndReportOnErrorFast(context->context->Map(vertex_array->buff_vert, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms));
	memcpy(ms.pData, vert_data, vertex_array->stride * vert_count);
	context->context->Unmap(vertex_array->buff_vert, NULL);

	vertex_array->vert_count = vert_count;
}

// ------------------------------------------------------------------------------------------------

void ztdx_vertexArrayDraw(ztContextDX *context, ztVertexArrayDX *vertex_array, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	UINT stride = vertex_array->stride, offset = 0;
	context->context->IASetVertexBuffers(0, 1, &vertex_array->buff_vert, &stride, &offset);
	context->context->IASetPrimitiveTopology(topology);
	context->context->Draw(vertex_array->vert_count, 0);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // implementation
