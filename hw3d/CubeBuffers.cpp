#include "CubeBuffers.h"
#include "Graphics.h"
#include "Bindable.h"
#include <iostream>
#include "GraphicsThrowMacros.h"

CubeBuffers::CubeBuffers() {

}

//Pass a list of cube structs into here. TODO: Make cube structs. Will convert cubes from the generated chunk into more appropriate cube strucks.
bool CubeBuffers::createInputBuffer(Graphics& gfx, CubeData cubes[], int array_size)
{
    
    if (m_srcDataGPUBuffer)
        m_srcDataGPUBuffer->Release();
    m_srcDataGPUBuffer = NULL;

    if (cubes)
    {
        // First we create a buffer in GPU memory
        D3D11_BUFFER_DESC descGPUBuffer;
        ZeroMemory(&descGPUBuffer, sizeof(descGPUBuffer));
        descGPUBuffer.BindFlags = D3D11_BIND_UNORDERED_ACCESS |
            D3D11_BIND_SHADER_RESOURCE;
        descGPUBuffer.ByteWidth = array_size;
        descGPUBuffer.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        descGPUBuffer.StructureByteStride = sizeof(CubeData);    //Set this to structure byte stride...
                                                  
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = cubes;
        if (FAILED(gfx.getDevice()->CreateBuffer(&descGPUBuffer, &InitData,
            &m_srcDataGPUBuffer)))
            return false;

        // Now we create a view on the resource. DX11 requires you to send the data
        // to shaders using a "shader view"
        D3D11_BUFFER_DESC descBuf;
        ZeroMemory(&descBuf, sizeof(descBuf));
        m_srcDataGPUBuffer->GetDesc(&descBuf);

        D3D11_SHADER_RESOURCE_VIEW_DESC descView;
        ZeroMemory(&descView, sizeof(descView));
        descView.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
        descView.BufferEx.FirstElement = 0;

        descView.Format = DXGI_FORMAT_UNKNOWN;
        descView.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

        if (FAILED(gfx.getDevice()->CreateShaderResourceView(m_srcDataGPUBuffer,
            &descView, &m_srcDataGPUBufferView)))
            return false;

        return true;
    }
    else
        return false;
	
}

bool CubeBuffers::createOutputBuffer(Graphics& gfx, CubeData cubes[], int array_size)
{
    
    // The compute shader will need to output to some buffer so here 
   // we create a GPU buffer for that.
    D3D11_BUFFER_DESC descGPUBuffer;
    ZeroMemory(&descGPUBuffer, sizeof(descGPUBuffer));
    descGPUBuffer.BindFlags = D3D11_BIND_UNORDERED_ACCESS |
        D3D11_BIND_SHADER_RESOURCE;
    descGPUBuffer.ByteWidth = array_size;
    descGPUBuffer.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    descGPUBuffer.StructureByteStride = sizeof(CubeData); 

    if (FAILED(gfx.getDevice()->CreateBuffer(&descGPUBuffer, NULL,
        &m_destDataGPUBuffer)))
        return false;

    // The view we need for the output is an unordered access view. 
    // This is to allow the compute shader to write anywhere in the buffer.
    D3D11_BUFFER_DESC descBuf;
    ZeroMemory(&descBuf, sizeof(descBuf));
    m_destDataGPUBuffer->GetDesc(&descBuf);

    D3D11_UNORDERED_ACCESS_VIEW_DESC descView;
    ZeroMemory(&descView, sizeof(descView));
    descView.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    descView.Buffer.FirstElement = 0;

    // Format must be must be DXGI_FORMAT_UNKNOWN, when creating 
    // a View of a Structured Buffer
    descView.Format = DXGI_FORMAT_UNKNOWN;
    descView.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

    if (FAILED(gfx.getDevice()->CreateUnorderedAccessView(m_destDataGPUBuffer,
        &descView, &m_destDataGPUBufferView)))
        return false;

    return true;
}

void CubeBuffers::getResults(Graphics& gfx, CubeData destination[], int array_size) {

    INFOMAN(gfx);
    //Creates a buffer to store the information retrieved from the GPU?
    ID3D11Buffer* pResultBuffer;
    D3D11_BUFFER_DESC outputDesc;
    outputDesc.Usage = D3D11_USAGE_STAGING;
    outputDesc.ByteWidth = array_size;
    outputDesc.BindFlags = 0;
    outputDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    outputDesc.StructureByteStride = sizeof(CubeData); // cube size 
    outputDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
   
    GFX_THROW_INFO(gfx.getDevice()->CreateBuffer(&outputDesc, NULL, &pResultBuffer));

    //Copy's the resources from the buffer previous indicated as the shaders output buffer to this new buffer.
   
    gfx.getContext()->CopyResource(pResultBuffer, m_destDataGPUBuffer);
    //int k = sizeof(*m_destDataGPUBuffer);
   
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    GFX_THROW_INFO(gfx.getContext()->Map(pResultBuffer, 0, D3D11_MAP_READ, 0, &mappedResource));
    
    //slaps the data from the mapped resource into the destination. No need to reinterpret cast. 
    memcpy(destination, mappedResource.pData, array_size);
    
    
    //Unmaps the data so the GPU can access it... this part might not be necessary, but it might be during the copy
    gfx.getContext()->Unmap(m_destDataGPUBuffer, 0);
    
    pResultBuffer->Release();
    m_srcDataGPUBufferView->Release();
    m_destDataGPUBufferView->Release();
    m_srcDataGPUBuffer->Release();
    m_destDataGPUBuffer->Release();
   
}



