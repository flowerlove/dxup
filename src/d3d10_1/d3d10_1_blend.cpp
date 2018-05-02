#include "d3d10_1_blend.h"
#include "d3d10_1_device.h"

namespace dxup
{
	D3D10BlendState::D3D10BlendState(const D3D10_BLEND_DESC1* pDesc, D3D10Device* pDevice, ID3D11BlendState1* pBlendState)
	{
		m_device = pDevice;
		SetBase(pBlendState);
		m_desc = *pDesc;
	}
	HRESULT STDMETHODCALLTYPE D3D10BlendState::QueryInterface(REFIID riid, void** ppvObject)
	{
		*ppvObject = nullptr;

		if (riid == __uuidof(IUnknown)
			|| riid == __uuidof(ID3D10DeviceChild)
			|| riid == __uuidof(ID3D10BlendState)
			|| riid == __uuidof(ID3D10BlendState1))
		{
			AddRef();
			*ppvObject = this;
			return S_OK;
		}

		DXUP_Log(Warn, "Couldn't find interface!");
		return E_FAIL;
	}
	void D3D10BlendState::GetDesc(D3D10_BLEND_DESC* pDesc)
	{
		pDesc->AlphaToCoverageEnable = m_desc.AlphaToCoverageEnable;

		pDesc->BlendOp = m_desc.RenderTarget[0].BlendOp;
		pDesc->BlendOpAlpha = m_desc.RenderTarget[0].BlendOpAlpha;
		pDesc->DestBlend = m_desc.RenderTarget[0].DestBlend;
		pDesc->DestBlendAlpha = m_desc.RenderTarget[0].DestBlendAlpha;
		pDesc->SrcBlend = m_desc.RenderTarget[0].SrcBlend;
		pDesc->SrcBlendAlpha = m_desc.RenderTarget[0].SrcBlendAlpha;

		for (int i = 0; i < 8; i++)
		{
			pDesc->BlendEnable[i] = m_desc.RenderTarget[i].BlendEnable;
			pDesc->RenderTargetWriteMask[i] = m_desc.RenderTarget[i].RenderTargetWriteMask;
		}
	}
}
