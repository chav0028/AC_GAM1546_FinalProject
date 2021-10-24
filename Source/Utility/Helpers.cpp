#include "CommonHeader.h"

void myassert(bool condition)
{
    if( condition == false )
    {
        __debugbreak();
    }
}

void OutputMessage(const char* message, ...)
{
#define MAX_MESSAGE 1024
    char szBuff[MAX_MESSAGE];
    va_list arg;
    va_start(arg, message);
    vsnprintf_s( szBuff, sizeof(szBuff), _TRUNCATE, message, arg );
    va_end(arg);

    szBuff[MAX_MESSAGE-1] = 0; // vsnprintf_s might do this, but docs are unclear
    OutputDebugStringA( szBuff );
}

void CheckForGLErrors()
{
    GLenum error = glGetError();

    if( error != 0 )
    {
        OutputDebugString( "glGetError\n" );
        myassert( false );
    }
}

char* LoadCompleteFile(const char* filename)
{
    FILE* file;
    errno_t err = fopen_s( &file, filename, "rb" );

    char* buffer;

    if( file )
    {
        fseek( file, 0, SEEK_END );
        long size = ftell( file );
        rewind( file );

        buffer = new char[size+1];
        fread( buffer, size, 1, file );
        buffer[size] = 0;

        fclose( file );

        return buffer;
    }

    return 0;
}

double MyGetSystemTime()
{
    unsigned __int64 freq;
    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );

    unsigned __int64 time;
    QueryPerformanceCounter( (LARGE_INTEGER*)&time );

    static double timegamestarted = (double)time / freq;
    double timeseconds = (double)time / freq;

    return timeseconds - timegamestarted;
}

GLuint LoadTexture(const char* filename)
{
    unsigned char* pngbuffer;
    unsigned int width, height;
    lodepng_decode32_file( &pngbuffer, &width, &height, filename );

    Flip32BitImageVertically( pngbuffer, width, height );

    GLuint texhandle = 0;
    glGenTextures( 1, &texhandle );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texhandle );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    delete( pngbuffer );

    return texhandle;
}

void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height)
{
    // flip the image in buffer.  Assumes RGBA 32 bit.
    
    {
        // temp allocation big enough for one line
        unsigned int* temp;
        temp = new unsigned int[width];
        int linesize = width * sizeof(unsigned int);

        unsigned int* buffer32 = (unsigned int*)buffer;
        for( unsigned int y=0; y<height/2; y++ )
        {
            int LineOffsetY = y*width;
            int LineOffsetHminusY = (height-1-y)*width;

            memcpy( temp, &buffer32[LineOffsetY], linesize );
            memcpy( &buffer32[LineOffsetY], &buffer32[LineOffsetHminusY], linesize );
            memcpy( &buffer32[LineOffsetHminusY], temp, linesize );
        }

        delete temp;
    }

    // slower but one less memory allocation.
    //{
    //    unsigned int* pngbuffer32 = buffer;
    //    for( unsigned int y=0; y<height/2; y++ )
    //    {
    //        int LineOffsetY = y*width;
    //        int LineOffsetHminusY = (height-1-y)*width;

    //        for( unsigned int x=0; x<width; x++ )
    //        {
    //            int tempcolor = pngbuffer32[LineOffsetY + x];
    //            pngbuffer32[LineOffsetY + x] = pngbuffer32[LineOffsetHminusY + x];
    //            pngbuffer32[LineOffsetHminusY + x] = tempcolor;
    //        }
    //    }
    //}
}

void GetMouseCoordinates(int* mx, int* my)
{
    extern HWND hWnd;

    POINT p;
    if( GetCursorPos( &p ) )
    {
        if( ScreenToClient( hWnd, &p ) )
        {
            *mx = p.x;
            *my = p.y;
        }
    }
}
