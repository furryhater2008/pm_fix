#include "hooks/detours.h"

HWND game_window;
HRESULT(*present_original)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*resize_original)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediate_context = nullptr;
ID3D11RenderTargetView* render_target_view = nullptr;
Vector2 screen_size = {0, 0};
D3D11_VIEWPORT viewport;