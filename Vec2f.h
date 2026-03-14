#ifndef VEC2F_H
#define VEC2F_H
#include<math.h>

class Vec2f {
public:

    static const int DIM = 2;

    float x;
    float y;

    Vec2f();
    Vec2f( float x, float y );

    void set( float x, float y );

    void set( const Vec2f& vec );

   float length() const;

    bool operator==( const Vec2f& vec ) const;

    bool operator!=( const Vec2f& vec ) const;

    bool match( const Vec2f& vec, float tolerance = 0.0001f ) const;

    Vec2f& operator+=( const Vec2f& vec );

    Vec2f& operator+=( const float f );

    Vec2f  operator+( const Vec2f& vec ) const;

    Vec2f  operator+( const float f ) const;


    Vec2f& operator-=( const Vec2f& vec );

    Vec2f& operator-=( const float f );

    Vec2f  operator-( const Vec2f& vec ) const;

    Vec2f  operator-() const;


    Vec2f  operator*( const Vec2f& vec ) const;

    Vec2f  operator*( const float f ) const;

    Vec2f& operator*=( const Vec2f& vec );

    Vec2f& operator*=( const float f );

    Vec2f  operator/( const Vec2f& vec ) const;


    Vec2f  operator/( const float f ) const;

    Vec2f& operator/=( const Vec2f& vec );

    Vec2f& operator/=( const float f );


    float * getPtr() {
        return (float*)&x;
    }

    const float * getPtr() const {
        return (const float *)&x;
    }

    float& operator[]( int n ){
        return getPtr()[n];
    }

    float operator[]( int n ) const {
        return getPtr()[n];
    }

};

inline Vec2f::Vec2f(): x(0), y(0) {}
inline Vec2f::Vec2f( float _x, float _y ):x(_x), y(_y) {}



inline void Vec2f::set( float _x, float _y ) {
    x = _x;
    y = _y;
}

inline void Vec2f::set( const Vec2f& vec ) {
    x = vec.x;
    y = vec.y;
}


inline bool Vec2f::operator==( const Vec2f& vec ) const {
    return (x == vec.x) && (y == vec.y);
}

inline bool Vec2f::operator!=( const Vec2f& vec ) const {
    return (x != vec.x) || (y != vec.y);
}

inline bool Vec2f::match( const Vec2f& vec, float tolerance ) const {
    return (fabs(x - vec.x) < tolerance)
    && (fabs(y - vec.y) < tolerance);
}



inline Vec2f Vec2f::operator+( const Vec2f& vec ) const {
    return Vec2f( x+vec.x, y+vec.y);
}

inline Vec2f& Vec2f::operator+=( const Vec2f& vec ) {
    x += vec.x;
    y += vec.y;
    return *this;
}
inline Vec2f Vec2f::operator+( const float f ) const {
    return Vec2f( x+f, y+f);
}

inline Vec2f& Vec2f::operator+=( const float f ) {
    x += f;
    y += f;
    return *this;
}


inline Vec2f& Vec2f::operator-=( const float f ) {
    x -= f;
    y -= f;
    return *this;
}

inline Vec2f& Vec2f::operator-=( const Vec2f& vec ) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}


inline Vec2f Vec2f::operator-( const Vec2f& vec ) const {
    return Vec2f(x-vec.x, y-vec.y);
}


inline Vec2f Vec2f::operator-() const {
    return Vec2f(-x, -y);
}


inline Vec2f Vec2f::operator*( const Vec2f& vec ) const {
    return Vec2f(x*vec.x, y*vec.y);
}

inline Vec2f& Vec2f::operator*=( const Vec2f& vec ) {
    x*=vec.x;
    y*=vec.y;
    return *this;
}

inline Vec2f Vec2f::operator*( const float f ) const {
    return Vec2f(x*f, y*f);
}

inline Vec2f& Vec2f::operator*=( const float f ) {
    x*=f;
    y*=f;
    return *this;
}


inline Vec2f Vec2f::operator/( const Vec2f& vec ) const {
    return Vec2f( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y);
}

inline Vec2f& Vec2f::operator/=( const Vec2f& vec ) {
    vec.x!=0 ? x/=vec.x : x;
    vec.y!=0 ? y/=vec.y : y;
    return *this;
}

inline Vec2f Vec2f::operator/( const float f ) const {
    if(f == 0) return Vec2f(x, y);

    return Vec2f(x/f, y/f);
}

inline Vec2f& Vec2f::operator/=( const float f ) {
    if(f == 0) return *this;

    x/=f;
    y/=f;
    return *this;
}

inline float Vec2f::length() const {
    return (float)sqrt( x*x + y*y);
}


#endif // VEC2F_H
