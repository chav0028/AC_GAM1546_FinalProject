//
// Copyright (c) 2012-2014 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __Vector_H__
#define __Vector_H__

#define vec2 Vector2
#define vec3 Vector3
#define vec4 Vector4
#define ivec2 Vector2Int
#define ivec3 Vector3Int
#define ivec4 Vector4Int

class Vector2
{
public:
    float x;
    float y;

public:
    Vector2() {}
    Vector2(float nxy) { x = nxy; y = nxy; }
    Vector2(float nx, float ny) { x = nx; y = ny; }
    Vector2(int nx, int ny) { x = (float)nx; y = (float)ny; }
    //virtual ~Vector2() {}

    inline void Set(float nx, float ny) { x = nx; y = ny; }
    inline float LengthSquared() const { return x*x + y*y; }
    inline float Length() const { return sqrtf(x*x + y*y); }

    inline Vector2 GetNormalized() const { float len = Length(); if( fequal(len,0) ) return Vector2(x,y); len = 1.0f/len; return Vector2(x*len, y*len); }
    inline Vector2 Normalize() { float len = Length(); if( !fequal(len,0) ) { x /= len; y /= len; } return *this; }
    inline float Dot(const Vector2 &o) const { return x*o.x + y*o.y; }

    inline bool operator ==(const Vector2& o) const { return fequal(this->x, o.x) && fequal(this->y, o.y); }
    inline bool operator !=(const Vector2& o) const { return !fequal(this->x, o.x) || !fequal(this->y, o.y); }

    inline Vector2 operator *(const float o) const { return Vector2(this->x * o, this->y * o); }
    inline Vector2 operator /(const float o) const { return Vector2(this->x / o, this->y / o); }
    inline Vector2 operator +(const Vector2& o) const { return Vector2(this->x + o.x, this->y + o.y); }
    inline Vector2 operator -(const Vector2& o) const { return Vector2(this->x - o.x, this->y - o.y); }

    inline Vector2 operator *=(const float o) { this->x *= o; this->y *= o; return *this; }
    inline Vector2 operator /=(const float o) { this->x /= o; this->y /= o; return *this; }
    inline Vector2 operator +=(const Vector2& o) { this->x += o.x; this->y += o.y; return *this; }
    inline Vector2 operator -=(const Vector2& o) { this->x -= o.x; this->y -= o.y; return *this; }
};

class Vector3
{
public:
    float x;
    float y;
    float z;

public:
    Vector3() {}
    Vector3(float nxyz) { x = nxyz; y = nxyz; z = nxyz; }
    Vector3(float nx, float ny) { x = nx; y = ny; z = 0; }
    Vector3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    Vector3(Vector2 v2) { x = v2.x; y = v2.y; z = 0; }
    Vector3(Vector2 v2, float nz) { x = v2.x; y = v2.y; z = nz; }
    //virtual ~Vector3() {}

    inline Vector2 XY() { return Vector2( x, y ); }

    inline void Set(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }

    inline bool operator ==(const Vector3& o) const { return fequal(this->x, o.x) && fequal(this->y, o.y) && fequal(this->z, o.z); }
    inline bool operator !=(const Vector3& o) const { return !fequal(this->x, o.x) || !fequal(this->y, o.y) || !fequal(this->z, o.z); }

    inline Vector3 operator *(const float o) const { return Vector3(this->x * o, this->y * o, this->z * o); }
    inline Vector3 operator /(const float o) const { return Vector3(this->x / o, this->y / o, this->z / o); }
    inline Vector3 operator +(const float o) const { return Vector3(this->x + o, this->y + o, this->z + o); }
    inline Vector3 operator -(const float o) const { return Vector3(this->x - o, this->y - o, this->z - o); }
    inline Vector3 operator +(const Vector3& o) const { return Vector3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3 operator -(const Vector3& o) const { return Vector3(this->x - o.x, this->y - o.y, this->z - o.z); }

    inline Vector3 operator *=(const float o) { this->x *= o; this->y *= o; this->z *= o; return *this; }
    inline Vector3 operator /=(const float o) { this->x /= o; this->y /= o; this->z /= o; return *this; }
    inline Vector3 operator +=(const float o) { this->x += o; this->y += o; this->z += o; return *this; }
    inline Vector3 operator -=(const float o) { this->x -= o; this->y -= o; this->z -= o; return *this; }
    inline Vector3 operator +=(const Vector3& o) { this->x += o.x; this->y += o.y; this->z += o.z; return *this; }
    inline Vector3 operator -=(const Vector3& o) { this->x -= o.x; this->y -= o.y; this->z -= o.z; return *this; }

    float& operator[] (int i) { if( i == 0 ) return x; if( i == 1 ) return y; if( i == 2 ) return z; assert(false); return x; }
};

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4() {}
    Vector4(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }
    //virtual ~Vector4() {}

    inline void Set(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; }
    inline float LengthSquared() const {return x*x + y*y + z*z + w*w;}
    inline float Length() const { return sqrtf(x*x + y*y + z*z + w*w); }

    inline Vector4 Normalize() const { float len = Length(); if( fequal(len,0) ) return Vector4(x,y,z,w); len = 1.0f/len; return Vector4(x*len, y*len, z*len, w*len); }
    //Vector4 CrossProduct(const Vector4& b, const Vector4& c)
    // from http://www.gamedev.net/topic/269241-4d-vector-class/
    //  not sure if right and have no use for it.
    //{
    //    //Precompute some 2x2 matrix determinants for speed
    //    float Pxy = b.x*c.y - c.x*b.y;
    //    float Pxz = b.x*c.z - c.x*b.z;
    //    float Pxw = b.x*c.w - c.x*b.w;
    //    float Pyz = b.y*c.z - c.y*b.z;
    //    float Pyw = b.y*c.w - c.y*b.w;
    //    float Pzw = b.z*c.w - c.z*b.w;
    //    return Vector4(
    //        y*Pzw - z*Pyw + w*Pyz,    //Note the lack of 'x' in this line
    //        z*Pxw - x*Pzw - w*Pxz,    //y, Etc.
    //        x*Pyw - y*Pxw + w*Pxy,
    //        y*Pxz - x*Pyz - z*Pxy
    //        );
    //}

    inline Vector4 operator *(const float o) const { return Vector4(this->x * o, this->y * o, this->z * o, this->w * o); }
    inline Vector4 operator /(const float o) const { return Vector4(this->x / o, this->y / o, this->z / o, this->w / o); }
    inline Vector4 operator +(const Vector4& o) const { return Vector4(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w); }
    inline Vector4 operator -(const Vector4& o) const { return Vector4(this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w); }
};

class Vector2Int
{
public:
    int x;
    int y;

public:
    Vector2Int() {}
    Vector2Int(int nx, int ny) { x = nx; y = ny; }
    //virtual ~Vector2Int() {}

    inline void Set(int nx, int ny) { x = nx; y = ny; }
    inline float LengthSquared() const {return (float)x*x + y*y;}
    inline float Length() const {return sqrtf((float)x*x + y*y);}

    //inline Vector2Int Normalize() const {float len = Length(); if( fequal(len,0) ) return Vector2Int(x,y); len = 1.0f/len; return Vector2Int(x*len, y*len);}

    inline bool operator ==(const Vector2Int& o) const { return this->x == o.x && this->y == o.y; }
    inline bool operator !=(const Vector2Int& o) const { return this->x != o.x || this->y != o.y; }
    inline Vector2Int operator +(const Vector2Int& o) const { return Vector2Int(this->x + o.x, this->y + o.y); }
    inline Vector2Int operator -(const Vector2Int& o) const { return Vector2Int(this->x - o.x, this->y - o.y); }
};

class Vector3Int
{
public:
    int x;
    int y;
    int z;

public:
    Vector3Int() {}
    Vector3Int(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }
    //virtual ~Vector3Int() {}

    inline void Set(int nx, int ny, int nz) { x = nx; y = ny; z = nz; }
    inline float LengthSquared() const {return (float)x*x + y*y + z*z;}
    inline float Length() const {return sqrtf((float)x*x + y*y + z*z);}

    //inline Vector3Int Normalize() const {float len = Length(); if( fequal(len,0) ) return Vector3Int(x,y,z); len = 1.0f/len; return Vector3Int(x*len, y*len, z*len);}
    //inline Vector3Int Cross(const Vector3Int& o) const {return Vector3Int( (y*o.z - z*o.y), (z*o.x - x*o.z), (x*o.y - y*o.x) );}

    inline bool operator ==(const Vector3Int& o) const { return this->x == o.x && this->y == o.y && this->z == o.z; }
    inline bool operator !=(const Vector3Int& o) const { return this->x != o.x || this->y != o.y || this->z != o.z; }
    inline Vector3Int operator +(const Vector3Int& o) const { return Vector3Int(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline Vector3Int operator -(const Vector3Int& o) const { return Vector3Int(this->x - o.x, this->y - o.y, this->z - o.z); }
};

class Vector4Int
{
public:
    int x;
    int y;
    int z;
    int w;

public:
    Vector4Int() {}
    Vector4Int(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }
    //virtual ~Vector4Int() {}

    inline void Set(int nx, int ny, int nz, int nw) { x = nx; y = ny; z = nz; w = nw; }
    inline float LengthSquared() const {return (float)x*x + y*y + z*z + w*w;}
    inline float Length() const {return sqrtf((float)x*x + y*y + z*z + w*w);}

    //inline Vector4Int Normalize() const {float len = Length(); if( fequal(len,0) ) return Vector4Int(x,y,z); len = 1.0f/len; return Vector4Int(x*len, y*len, z*len);}
    //inline Vector4Int Cross(const Vector4Int& o) const {return Vector4Int( (y*o.z - z*o.y), (z*o.x - x*o.z), (x*o.y - y*o.x) );}

    inline bool operator ==(const Vector4Int& o) const { return this->x == o.x && this->y == o.y && this->z == o.z && this->w == o.w; }
    inline bool operator !=(const Vector4Int& o) const { return this->x != o.x || this->y != o.y || this->z != o.z || this->w != o.w; }
    inline Vector4Int operator +(const Vector4Int& o) const { return Vector4Int(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w); }
    inline Vector4Int operator -(const Vector4Int& o) const { return Vector4Int(this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w); }
};

class MyRect
{
public:
    int x;
    int y;
    int w;
    int h;

public:
    MyRect() {}
    MyRect(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }
};

template <class MyType> class Vector2T
{
public:
    MyType x;
    MyType y;

public:
    Vector2T() {}
    Vector2T(MyType nx, MyType ny) { x = nx; y = ny; }
    //Vector2T(MyType nx, MyType ny) { x = (float)nx; y = (float)ny; }
    //virtual ~Vector2Int() {}

    inline void Set(MyType nx, MyType ny) { x = nx; y = ny; }
    inline float LengthSquared() const {return (float)x*x + y*y;}
    inline float Length() const {return sqrtf((float)x*x + y*y);}

    inline Vector2T<MyType> GetNormalized() const { float len = Length(); if( fequal(len,0) ) return Vector2T<MyType>(x,y); len = 1.0f/len; return Vector2T<MyType>(x*len, y*len); }
    //inline Vector2T<MyType> Normalize() const {float len = Length(); if( fequal(len,0) ) return Vector2T<MyType>(x,y); len = 1.0f/len; return Vector2T<MyType>(x*len, y*len);}

    inline bool operator ==(const Vector2T<MyType>& o) const { return this->x == o.x && this->y == o.y; }
    inline bool operator !=(const Vector2T<MyType>& o) const { return this->x != o.x || this->y != o.y; }

    inline Vector2T<MyType> operator *(const float o) const { return Vector2T<MyType>(this->x * o, this->y * o); }
    inline Vector2T<MyType> operator /(const float o) const { return Vector2T<MyType>(this->x / o, this->y / o); }
    inline Vector2T<MyType> operator +(const Vector2& o) const { return Vector2T<MyType>(this->x + o.x, this->y + o.y); }
    inline Vector2T<MyType> operator -(const Vector2& o) const { return Vector2T<MyType>(this->x - o.x, this->y - o.y); }

    inline Vector2T<MyType> operator *=(const float o) { this->x *= o; this->y *= o; return *this; }
    inline Vector2T<MyType> operator /=(const float o) { this->x /= o; this->y /= o; return *this; }
    inline Vector2T<MyType> operator +=(const Vector2T<MyType>& o) { this->x += o.x; this->y += o.y; return *this; }
    inline Vector2T<MyType> operator -=(const Vector2T<MyType>& o) { this->x -= o.x; this->y -= o.y; return *this; }
};

#endif //__Vector_H__
