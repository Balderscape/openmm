#ifndef OPENMM_VEC4_H_
#define OPENMM_VEC4_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2013 Stanford University and the Authors.      *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include <cassert>
#include <iosfwd>

namespace OpenMM {

/**
 * This class represents a four component vector.  It is used for storing positions,
 * velocities, and forces.
 */

class Vec4 {
public:
    /**
     * Create a Vec4 whose elements are all 0.
     */
    Vec3() {
        data[0] = data[1] = data[2] = data[3] = 0.0;
    }
    /**
     * Create a Vec4 with specified x, y, and z components.
     */
    Vec3(double x, double y, double z, double w) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }    
    double operator[](int index) const {
        assert(index >= 0 && index < 4);
        return data[index];
    }
    double& operator[](int index) {
        assert(index >= 0 && index < 4);
        return data[index];
    }

    bool operator==(const Vec4& rhs) const {
        return (data[0] == rhs[0] && data[1] == rhs[1] && data[2] == rhs[2] && data[3] == rhs[3]);
    }

    bool operator!=(const Vec4& rhs) const {
        return (data[0] != rhs[0] || data[1] != rhs[1] || data[2] != rhs[2] || data[3] != rhs[3]);
    }
    
    // Arithmetic operators
    
    // unary plus
    Vec4 operator+() const {
        return Vec4(*this);
    }
    
    // plus
    Vec4 operator+(const Vec4& rhs) const {
        const Vec4& lhs = *this;
        return Vec4(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]);
    }
    
    Vec4& operator+=(const Vec4& rhs) {
        data[0] += rhs[0];
        data[1] += rhs[1];
        data[2] += rhs[2];
        data[3] += rhs[3];
        return *this;
    }

    // unary minus
    Vec4 operator-() const {
        const Vec4& lhs = *this;
        return Vec4(-lhs[0], -lhs[1], -lhs[2], -lhs[3]);
    }
    
    // minus
    Vec4 operator-(const Vec4& rhs) const {
        const Vec4& lhs = *this;
        return Vec4(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]);
    }

    Vec4& operator-=(const Vec4& rhs) {
        data[0] -= rhs[0];
        data[1] -= rhs[1];
        data[2] -= rhs[2];
        data[3] -= rhs[3];
        return *this;
    }

    // scalar product
    Vec4 operator*(double rhs) const {
        const Vec4& lhs = *this;
        return Vec4(lhs[0]*rhs, lhs[1]*rhs, lhs[2]*rhs, lhs[3]*rhs);
    }

    Vec4& operator*=(double rhs) {
        data[0] *= rhs;
        data[1] *= rhs;
        data[2] *= rhs;
        data[3] *= rhs;
        return *this;
    }

    // scalar division
    Vec4 operator/(double rhs) const {
        const Vec4& lhs = *this;
        double scale = 1.0/rhs;
        return Vec4(lhs[0]*scale, lhs[1]*scale, lhs[2]*scale, lhs[3]*scale);
    }

    Vec4& operator/=(double rhs) {
        double scale = 1.0/rhs;
        data[0] *= scale;
        data[1] *= scale;
        data[2] *= scale;
        data[3] *= scale;
        return *this;
    }
    
    // dot product
    double dot(const Vec4& rhs) const {
        const Vec4& lhs = *this;
        return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2] + lhs[3]*rhs[3];
    }

    // cross product
    // Vec3 cross(const Vec3& rhs) const {
    //     return Vec3(data[1]*rhs[2]-data[2]*rhs[1], data[2]*rhs[0]-data[0]*rhs[2], data[0]*rhs[1]-data[1]*rhs[0]);
    // }
    
private:
    double data[4];
};

template <class CHAR, class TRAITS>
std::basic_ostream<CHAR,TRAITS>& operator<<(std::basic_ostream<CHAR,TRAITS>& o, const Vec4& v) {
    o<<'['<<v[0]<<", "<<v[1]<<", "<<v[2]<<", "<<v[3]<<']';
    return o;
}

} // namespace OpenMM

#endif /*OPENMM_VEC4_H_*/
