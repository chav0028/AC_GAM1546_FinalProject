//
// Copyright (c) 2012-2014 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __MyMatrix_H__
#define __MyMatrix_H__

class MyMatrix3
{
public:
    float x;
    float y;
    float z;

public:
    MyMatrix3() {}
    MyMatrix3(float nxyz) { x = nxyz; y = nxyz; z = nxyz; }
    MyMatrix3(float nx, float ny) { x = nx; y = ny; z = 0; }
    MyMatrix3(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    MyMatrix3(Vector2 v2) { x = v2.x; y = v2.y; z = 0; }
    MyMatrix3(Vector2 v2, float nz) { x = v2.x; y = v2.y; z = nz; }
    //virtual ~MyMatrix3() {}

    inline Vector2 XY() { return Vector2( x, y ); }

    inline void Set(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    inline float LengthSquared() const { return x*x + y*y + z*z; }
    inline float Length() const { return sqrtf(x*x + y*y + z*z); }

    inline MyMatrix3 GetNormalized() const { float len = Length(); if( fequal(len,0) ) return MyMatrix3(x,y,z); len = 1.0f/len; return MyMatrix3(x*len, y*len, z*len);}
    inline MyMatrix3 Normalize() { float len = Length(); if( !fequal(len,0) ) { x /= len; y /= len; z /= len; } return *this; }
    inline MyMatrix3 Cross(const MyMatrix3& o) const { return MyMatrix3( (y*o.z - z*o.y), (z*o.x - x*o.z), (x*o.y - y*o.x) ); }
    inline float Dot(const MyMatrix3 &o) const { return x*o.x + y*o.y + z*o.z; }
    inline MyMatrix3 Add(const MyMatrix3& o) const { return MyMatrix3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline MyMatrix3 Sub(const MyMatrix3& o) const { return MyMatrix3(this->x - o.x, this->y - o.y, this->z - o.z); }
    inline MyMatrix3 Scale(const float o) const { return MyMatrix3(this->x * o, this->y * o, this->z * o); }

    inline bool operator ==(const MyMatrix3& o) const { return fequal(this->x, o.x) && fequal(this->y, o.y) && fequal(this->z, o.z); }
    inline bool operator !=(const MyMatrix3& o) const { return !fequal(this->x, o.x) || !fequal(this->y, o.y) || !fequal(this->z, o.z); }

    inline MyMatrix3 operator *(const float o) const { return MyMatrix3(this->x * o, this->y * o, this->z * o); }
    inline MyMatrix3 operator /(const float o) const { return MyMatrix3(this->x / o, this->y / o, this->z / o); }
    inline MyMatrix3 operator +(const float o) const { return MyMatrix3(this->x + o, this->y + o, this->z + o); }
    inline MyMatrix3 operator -(const float o) const { return MyMatrix3(this->x - o, this->y - o, this->z - o); }
    inline MyMatrix3 operator +(const MyMatrix3& o) const { return MyMatrix3(this->x + o.x, this->y + o.y, this->z + o.z); }
    inline MyMatrix3 operator -(const MyMatrix3& o) const { return MyMatrix3(this->x - o.x, this->y - o.y, this->z - o.z); }

    inline MyMatrix3 operator *=(const float o) { this->x *= o; this->y *= o; this->z *= o; return *this; }
    inline MyMatrix3 operator /=(const float o) { this->x /= o; this->y /= o; this->z /= o; return *this; }
    inline MyMatrix3 operator +=(const float o) { this->x += o; this->y += o; this->z += o; return *this; }
    inline MyMatrix3 operator -=(const float o) { this->x -= o; this->y -= o; this->z -= o; return *this; }
    inline MyMatrix3 operator +=(const MyMatrix3& o) { this->x += o.x; this->y += o.y; this->z += o.z; return *this; }
    inline MyMatrix3 operator -=(const MyMatrix3& o) { this->x -= o.x; this->y -= o.y; this->z -= o.z; return *this; }

    float& operator[] (int i) { if( i == 0 ) return x; if( i == 1 ) return y; if( i == 2 ) return z; assert(false); return x; }

    //inline void operator =(const Vector2& o) { x = o.x; y = o.y; z = 0; } // couldn't make this work, used a constructor instead.
};

class MyMatrix
{
public:
    float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

public:
    MyMatrix() {}
    MyMatrix(const MyMatrix3& right, const MyMatrix3& up, const MyMatrix3& at)
        : m11(right.x), m12(up.x), m13(at.x), m14(0)
        , m21(right.y), m22(up.y), m23(at.y), m24(0)
        , m31(right.z), m32(up.z), m33(at.z), m34(0)
        , m41(0),       m42(0),    m43(0),    m44(1) {}
    MyMatrix(float v11, float v12, float v13, float v14,
             float v21, float v22, float v23, float v24,
             float v31, float v32, float v33, float v34,
             float v41, float v42, float v43, float v44)
        : m11(v11), m12(v12), m13(v13), m14(v14)
        , m21(v21), m22(v22), m23(v23), m24(v24)
        , m31(v31), m32(v32), m33(v33), m34(v34)
        , m41(v41), m42(v42), m43(v43), m44(v44) {}

    // the following function will affect existing values in the matrix
    void Scale(float scale);
    void Scale(float sx, float sy, float sz);
    void Rotate(float angle, float x, float y, float z);
    void TranslatePreRotScale(MyMatrix3 translate);
    void TranslatePreRotScale(float tx, float ty, float tz);
    void Translate(MyMatrix3 pos);
    void Translate(float x, float y, float z);

    // all create/set functions will overright values in the matrix
    void SetIdentity();
    void SetTranslation(Vector3 pos);
    void SetTranslation(float x, float y, float z);
    void CreateScale(float scale);
    void CreateScale(float x, float y, float z);
    void CreateScale(MyMatrix3 scale);
    void CreateSRT(float scale, MyMatrix3 rot, MyMatrix3 pos);
    void CreateSRT(MyMatrix3 scale, MyMatrix3 rot, MyMatrix3 pos);
    void CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    void CreatePerspectiveVFoV(float halfvertfovdegrees, float aspect, float nearZ, float farZ);
    void CreatePerspectiveHFoV(float halfhorfovdegrees, float aspect, float nearZ, float farZ);
    void CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
    void CreateLookAtLeftHanded(const MyMatrix3& eye, const MyMatrix3& up, const MyMatrix3& at);
    void CreateLookAt(const Vector3& eye, const Vector3& up, const Vector3& at);

    // get values from matrix
    MyMatrix3 GetTranslation() { return MyMatrix3( m41, m42, m43 ); }
    MyMatrix3 GetEulerAngles();

    void Transpose()
    {
        float temp;

        temp = m12; m12 = m21; m21 = temp;
        temp = m13; m13 = m31; m31 = temp;
        temp = m14; m14 = m41; m41 = temp;
        temp = m23; m23 = m32; m32 = temp;
        temp = m24; m24 = m42; m42 = temp;
        temp = m34; m34 = m43; m43 = temp;
    }

    inline MyMatrix operator *(const float o) const
    {
        MyMatrix newmat;

        newmat.m11 = this->m11 * o; newmat.m21 = this->m21 * o; newmat.m31 = this->m31 * o; newmat.m41 = this->m41 * o;
        newmat.m12 = this->m12 * o; newmat.m22 = this->m22 * o; newmat.m32 = this->m32 * o; newmat.m42 = this->m42 * o;
        newmat.m13 = this->m13 * o; newmat.m23 = this->m23 * o; newmat.m33 = this->m33 * o; newmat.m43 = this->m43 * o;
        newmat.m14 = this->m14 * o; newmat.m24 = this->m24 * o; newmat.m34 = this->m34 * o; newmat.m44 = this->m44 * o;

        return newmat;
    }

    inline Vector2 operator *(const Vector2 o) const
    {
        Vector4 result = Vector4( m11 * o.x + m21 * o.y + 0 + m41 * 1,
                                  m12 * o.x + m22 * o.y + 0 + m42 * 1,
                                  m13 * o.x + m23 * o.y + 0 + m43 * 1,
                                  m14 * o.x + m24 * o.y + 0 + m44 * 1 );
        if( result.w )
            return Vector2( result.x/result.w, result.y/result.w );
        else
            return Vector2( result.x, result.y );
    }

    inline MyMatrix3 operator *(const MyMatrix3 o) const
    {
        Vector4 result = Vector4( m11 * o.x + m21 * o.y + m31 * o.z + m41 * 1,
                                  m12 * o.x + m22 * o.y + m32 * o.z + m42 * 1,
                                  m13 * o.x + m23 * o.y + m33 * o.z + m43 * 1,
                                  m14 * o.x + m24 * o.y + m34 * o.z + m44 * 1 );
        if( result.w )
            return MyMatrix3( result.x/result.w, result.y/result.w, result.z/result.w );
        else
            return MyMatrix3( result.x, result.y, result.z );
    }

    inline Vector4 operator *(const Vector4 o) const
    {
        return Vector4( m11 * o.x + m21 * o.y + m31 * o.z + m41 * o.w,
                        m12 * o.x + m22 * o.y + m32 * o.z + m42 * o.w,
                        m13 * o.x + m23 * o.y + m33 * o.z + m43 * o.w,
                        m14 * o.x + m24 * o.y + m34 * o.z + m44 * o.w );
    }

    inline MyMatrix operator *(const MyMatrix o) const
    {
        MyMatrix newmat;

        newmat.m11 = this->m11 * o.m11 + this->m21 * o.m12 + this->m31 * o.m13 + this->m41 * o.m14;
        newmat.m12 = this->m12 * o.m11 + this->m22 * o.m12 + this->m32 * o.m13 + this->m42 * o.m14;
        newmat.m13 = this->m13 * o.m11 + this->m23 * o.m12 + this->m33 * o.m13 + this->m43 * o.m14;
        newmat.m14 = this->m14 * o.m11 + this->m24 * o.m12 + this->m34 * o.m13 + this->m44 * o.m14;
        newmat.m21 = this->m11 * o.m21 + this->m21 * o.m22 + this->m31 * o.m23 + this->m41 * o.m24;
        newmat.m22 = this->m12 * o.m21 + this->m22 * o.m22 + this->m32 * o.m23 + this->m42 * o.m24;
        newmat.m23 = this->m13 * o.m21 + this->m23 * o.m22 + this->m33 * o.m23 + this->m43 * o.m24;
        newmat.m24 = this->m14 * o.m21 + this->m24 * o.m22 + this->m34 * o.m23 + this->m44 * o.m24;
        newmat.m31 = this->m11 * o.m31 + this->m21 * o.m32 + this->m31 * o.m33 + this->m41 * o.m34;
        newmat.m32 = this->m12 * o.m31 + this->m22 * o.m32 + this->m32 * o.m33 + this->m42 * o.m34;
        newmat.m33 = this->m13 * o.m31 + this->m23 * o.m32 + this->m33 * o.m33 + this->m43 * o.m34;
        newmat.m34 = this->m14 * o.m31 + this->m24 * o.m32 + this->m34 * o.m33 + this->m44 * o.m34;
        newmat.m41 = this->m11 * o.m41 + this->m21 * o.m42 + this->m31 * o.m43 + this->m41 * o.m44;
        newmat.m42 = this->m12 * o.m41 + this->m22 * o.m42 + this->m32 * o.m43 + this->m42 * o.m44;
        newmat.m43 = this->m13 * o.m41 + this->m23 * o.m42 + this->m33 * o.m43 + this->m43 * o.m44;
        newmat.m44 = this->m14 * o.m41 + this->m24 * o.m42 + this->m34 * o.m43 + this->m44 * o.m44;
    
        return newmat;
    }

    bool Inverse(float tolerance = 0.0001f)
    {
        // Determinants of 2x2 submatrices
        float S0 = m11 * m22 - m12 * m21;
        float S1 = m11 * m23 - m13 * m21;
        float S2 = m11 * m24 - m14 * m21;
        float S3 = m12 * m23 - m13 * m22;
        float S4 = m12 * m24 - m14 * m22;
        float S5 = m13 * m24 - m14 * m23;

        float C5 = m33 * m44 - m34 * m43;
        float C4 = m32 * m44 - m34 * m42;
        float C3 = m32 * m43 - m33 * m42;
        float C2 = m31 * m44 - m34 * m41;
        float C1 = m31 * m43 - m33 * m41;
        float C0 = m31 * m42 - m32 * m41;

        // If determinant equals 0, there is no inverse
        float det = S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
        if( fabs(det) <= tolerance )
            return false;

        // Compute adjugate matrix
        *this = MyMatrix(
             m22 * C5 - m23 * C4 + m24 * C3, -m12 * C5 + m13 * C4 - m14 * C3,
             m42 * S5 - m43 * S4 + m44 * S3, -m32 * S5 + m33 * S4 - m34 * S3,

            -m21 * C5 + m23 * C2 - m24 * C1,  m11 * C5 - m13 * C2 + m14 * C1,
            -m41 * S5 + m43 * S2 - m44 * S1,  m31 * S5 - m33 * S2 + m34 * S1,

             m21 * C4 - m22 * C2 + m24 * C0, -m11 * C4 + m12 * C2 - m14 * C0,
             m41 * S4 - m42 * S2 + m44 * S0, -m31 * S4 + m32 * S2 - m34 * S0,

            -m21 * C3 + m22 * C1 - m23 * C0,  m11 * C3 - m12 * C1 + m13 * C0,
            -m41 * S3 + m42 * S1 - m43 * S0,  m31 * S3 - m32 * S1 + m33 * S0 ) * (1 / det);

        return true;
    }
};

#endif //__MyMatrix_H__
