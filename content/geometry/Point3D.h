/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long (same T as in Point.h).
 * Usage: P3 a(1,0,0), b(0,1,0); P3 n = a.cross(b); // (0,0,1)
 * Status: tested, except for phi and theta
 */
#pragma once

#ifndef POINT_T /// exclude-line
typedef double T;
#endif /// exclude-line
struct P3 {
	T x, y, z;
	explicit P3(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(P3 p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(P3 p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P3 operator+(P3 p) const { return P3(x+p.x, y+p.y, z+p.z); }
	P3 operator-(P3 p) const { return P3(x-p.x, y-p.y, z-p.z); }
	P3 operator*(T d) const { return P3(x*d, y*d, z*d); }
	P3 operator/(T d) const { return P3(x/d, y/d, z/d); }
	T dot(P3 p) const { return x*p.x + y*p.y + z*p.z; }
	P3 cross(P3 p) const {
		return P3(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); }
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P3 unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P3 normal(P3 p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P3 rotate(double angle, P3 axis) const {
		double s = sin(angle), c = cos(angle); P3 u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};
