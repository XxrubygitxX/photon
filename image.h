

#ifndef IMAGE_H
#define IMAGE_H



#include "graphics.h"



typedef struct imageinfo_t
{

    int width;
    int height;
    int channels;

} imageinfo_t; 

class CImage
{

    public:

        int Load(const char* p_Path);
        void Release();

        imageinfo_t GetInfo();

        unsigned char* GetImage();

        explicit CImage();
        explicit CImage(const char* p_Path);
        virtual ~CImage();

    private:

        unsigned char* m_Image;

        int m_Width;
        int m_Height;
        int m_Channels;

        bool m_Loaded;

};


#endif