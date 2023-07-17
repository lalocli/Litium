/*
 * Litium: Lalo's Suitium
 * Copyright (C) 2023 Eduardo "lalocli"
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#if __cplusplus
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <string.h>
#endif

#include "../litium.h"

#if __cplusplus
extern "C"
{
#endif

#if !__cplusplus
#define CS_VECTOR3D(x, y, z) { x, y, z }
#define CS_VECTOR3D_ZERO() CS_VECTOR3D(0.0f, 0.0f, 0.0f)
#define CS_VECTOR3D_ONE() CS_VECTOR3D(1.0f, 1.0f, 1.0f)
#define CS_ORIENTATION(n) { CS_VECTOR3D(n, 0.0f, 0.0f), CS_VECTOR3D(0.0f, n, 0.0f), CS_VECTOR3D(0.0f, 0.0f, n) }
#define CS_ORIENTATION_IDENTITY() CS_ORIENTATION(1.0f)

typedef float *cs_vector3dptr_t;
typedef float *cs_orientationptr_t;
#else
#define CS_VECTOR3D(x, y, z) cs_vector3d { x, y, z }
#define CS_VECTOR3D_ZERO() CS_VECTOR3D(0.0f, 0.0f, 0.0f)
#define CS_VECTOR3D_ONE() CS_VECTOR3D(1.0f, 1.0f, 1.0f)
#define CS_ORIENTATION(n) cs_orientation { CS_VECTOR3D(n, 0.0f, 0.0f), CS_VECTOR3D(0.0f, n, 0.0f), CS_VECTOR3D(0.0f, 0.0f, n) }
#define CS_ORIENTATION_IDENTITY() CS_ORIENTATION(1.0f)

typedef struct cs_vector3d *cs_vector3dptr_t;
typedef struct cs_orientation *cs_orientationptr_t;
#endif

#if !__cplusplus
typedef float cs_vector3d_t[3];
#else
struct cs_vector3d
{
    float c[3];

    LITIUM_INLINE const float &operator [](size_t n) const
    {
        return (this->c[n]);
    }
    LITIUM_INLINE float &operator [](size_t n)
    {
        return (this->c[n]);
    }

    LITIUM_INLINE cs_vector3d &operator=(const cs_vector3d &right)
    {
        memcpy(this->c, right.c, sizeof(float [3]));
        return (*this);
    }
    LITIUM_INLINE operator cs_vector3dptr_t()
    {
        return (this);
    }

    LITIUM_INLINE cs_vector3d operator+(const cs_vector3d &right) const
    {
        return (cs_vector3d { (*this)[0] + right[0], (*this)[1] + right[1], (*this)[2] + right[2] });
    }
    LITIUM_INLINE cs_vector3d &operator+=(const cs_vector3d &right)
    {
        return (*this = *this + right);
    }
    LITIUM_INLINE cs_vector3d operator-(const cs_vector3d &right) const
    {
        return (cs_vector3d { (*this)[0] - right[0], (*this)[1] - right[1], (*this)[2] - right[2] });
    }
    LITIUM_INLINE cs_vector3d &operator-=(const cs_vector3d &right)
    {
        return (*this = *this - right);
    }
    LITIUM_INLINE cs_vector3d operator*(const cs_vector3d &right) const
    {
        return (cs_vector3d { (*this)[0] * right[0], (*this)[1] * right[1], (*this)[2] * right[2] });
    }
    LITIUM_INLINE cs_vector3d &operator*=(const cs_vector3d &right)
    {
        return (*this = *this * right);
    }
    LITIUM_INLINE cs_vector3d operator*(float right) const
    {
        return (cs_vector3d { (*this)[0] * right, (*this)[1] * right, (*this)[2] * right });
    }
    LITIUM_INLINE cs_vector3d &operator*=(float right)
    {
        return (*this = *this * right);
    }
    LITIUM_INLINE cs_vector3d operator/(const cs_vector3d &right) const
    {
        return (cs_vector3d { (*this)[0] / right[0], (*this)[1] / right[1], (*this)[2] / right[2] });
    }
    LITIUM_INLINE cs_vector3d &operator/=(const cs_vector3d &right)
    {
        return (*this = *this / right);
    }
    LITIUM_INLINE cs_vector3d operator/(float right) const
    {
        float s = 1.0f / right;
        return (cs_vector3d { (*this)[0] * s, (*this)[1] * s, (*this)[2] * s });
    }
    LITIUM_INLINE cs_vector3d &operator/=(float right)
    {
        return (*this = *this / right);
    }

    LITIUM_INLINE float length() const
    {
        float x = (*this)[0];
        float y = (*this)[1];
        float z = (*this)[2];
        return (sqrtf(x * x + y * y + z * z));
    }
    LITIUM_INLINE float dot(const cs_vector3d &right) const
    {
        float x = (*this)[0];
        float y = (*this)[1];
        float z = (*this)[2];
        return (x * right[0] + y * right[1] + z * right[2]);
    }
    LITIUM_INLINE cs_vector3d cross(const cs_vector3d &right) const
    {
        float x = (*this)[0];
        float y = (*this)[1];
        float z = (*this)[2];
        return (cs_vector3d {
            y * right[2] - z * right[1],
            z * right[0] - x * right[2],
            x * right[1] - y * right[0]
        });
    }

    std::string str() const
    {
        char buf[256];
        sprintf(buf, "%f, %f, %f", (*this)[0], (*this)[1], (*this)[2]);
        return (buf);
    }
};
typedef struct cs_vector3d cs_vector3d_t;
#endif

#if !__cplusplus
typedef cs_vector3d_t cs_orientation_t[3];
#else
struct cs_orientation
{
    cs_vector3d_t c[3];

    LITIUM_INLINE const cs_vector3d &operator [](std::size_t n) const
    {
        return (this->c[n]);
    }
    LITIUM_INLINE cs_vector3d &operator [](std::size_t n)
    {
        return (this->c[n]);
    }

    LITIUM_INLINE cs_orientation &operator=(const cs_orientation &right)
    {
        memcpy(this->c, right.c, sizeof(cs_vector3d [3]));
        return (*this);
    }
    LITIUM_INLINE operator cs_orientationptr_t()
    {
        return (this);
    }

    // TODO: multiplications

    cs_orientation transpose() const
    {
        cs_orientation result;
        for (int collumn = 0; collumn < 3; collumn++)
        {
            for (int row = 0; row < 3; row++)
                result[collumn][row] = (*this)[2 - collumn][2 - row];
        }
        return (result);
    }

    std::string str() const
    {
        char buf[256];
        sprintf(buf, "%s,\n%s,\n%s", (*this)[0].str().c_str(), (*this)[1].str().c_str(), (*this)[2].str().c_str());
        return (buf);
    }
};
typedef struct cs_orientation cs_orientation_t;
#endif

#if __cplusplus
}
#endif
