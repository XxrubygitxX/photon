


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <filesystem>
#include "image.h"




extern std::filesystem::path GetExecutableDir();

CImage::CImage()
{

    this->m_Loaded = false;

}

CImage::CImage(const char* p_Path)
{

    this->Load(p_Path);

}

CImage::~CImage()
{

    this->Release();

}

int CImage::Load(const char* p_Path)
{

    this->m_Image = stbi_load((GetExecutableDir() / p_Path).string().c_str(), &this->m_Width, &this->m_Height, &this->m_Channels, 0);

    this->m_Loaded = true;

    return 0;

}

imageinfo_t CImage::GetInfo()
{

    return {this->m_Width, this->m_Height, this->m_Channels};

}

void CImage::Release()
{

    if (this->m_Loaded) { stbi_image_free(this->m_Image); }

    this->m_Loaded = false;

}

unsigned char* CImage::GetImage()
{

    return this->m_Image;

}

