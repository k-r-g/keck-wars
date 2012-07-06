/*****************************************************************************
*
*  geometry.h
*
*  Classes and utility functions for three-dimensional Points, Vectors,
*  Planes, and Rays.
*
*****************************************************************************/
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>

class Point;
class Vector;
class Plane;
class Ray;

// Comparing doubles for equality is useless; allow clients to supply a
// tolerance.

inline bool equal(double x, double y, double epsilon = 0.000001)
{
	double comparison = x - y;
	if (comparison < 0){comparison = -comparison;}
	return(comparison <= epsilon);
}

// ---------------------------------------------------------------------------
// class Vector
//
// A class for 3-D Vectors
//
//   v.i, v.j, v.k				Components of vector v
//   Vector(i, j, k)			Construct from components
//   Vector(p)					Construct from a point
//   u + v, u += v				Vector addition
//   u - v, u -= v				Vector subtraction
//   -v							<0, 0, 0> - v
//   u.dot(v)					Dot product of u and v
//   u.cross(v)					Cross product of u and v
//   v * c, c * v, v *= c		Multiplication of a vector and a scalar
//	 v / c, v /= c				Division of a vector by a scalar
//   v.magnitude()				The length of v
//   unit(v)					The vector of length 1 in the direction of v
//   normalize(v)				Changes v to unit(v)
//   cosine(u, v)				The cosine of the angle from u to v
//   u.isPerpendicularTo(v)		Whether u is almost perpendicular to v
//   u.isParallelTo(v)			Whether u is almost parallel to v
//   u.projectionOnto(v)		The projection of u onto v
//   u.reflectionAbout(v)		The mirror image of u over v
// ---------------------------------------------------------------------------

class Vector {
public:
  double i, j, k;
  Vector(double i = 0, double j = 0, double k = 0): i(i), j(j), k(k) {}
  Vector(Point p);
  Vector operator +(Vector v) {return Vector(i + v.i, j + v.j, k + v.k);}
  Vector& operator +=(Vector v) {i += v.i; j += v.j; k += v.k; return *this;}
  Vector operator -(Vector v) {return Vector(i - v.i, j - v.j, k - v.k);}
  Vector& operator -=(Vector v) {i -= v.i; j -= v.j; k -= v.k; return *this;}
  Vector operator -() {return Vector(-i, -j, -k);}
  double dot(Vector v) {return i * v.i + j * v.j + k * v.k;}
  Vector cross(Vector);
  Vector operator *(double c) {return Vector(i * c, j * c, k * c);}
  friend Vector operator *(double c, Vector v) {return v * c;}
  Vector& operator *=(Vector v) {i *= v.i; j *= v.j; k *= v.k; return *this;}
  Vector operator /(double c) {return Vector(i / c, j / c, k / c);}
  Vector& operator /=(double c) {i /= c; j /= c; k /= c; return *this;}
  double magnitude() {return sqrt(this->dot(*this));}
  friend Vector unit(Vector v) {return v / v.magnitude();}
  friend void normalize(Vector& v) {v /= v.magnitude();}
  friend double cosine(Vector u, Vector v) {return unit(u).dot(unit(v));}
  bool isPerpendicularTo(Vector v) {return equal(this->dot(v), 0);}
  bool isParallelTo(Vector v) {return equal(cosine(*this, v), 1.0);}
  Vector projectionOnto(Vector v) {return this->dot(unit(v)) * unit(v);}
  Vector reflectionAbout(Vector v) {return 2 * projectionOnto(v) - *this;}
};

// ---------------------------------------------------------------------------
// class Point
//
// A class for 3-D Points
//
//   p.x, p.y, p.z				Components (coordinates) of point p
//   p + v, p += v				Add a point to a vector
//   p - q						The vector from q to p
//   p.distanceTo(q)			The distance between p and q
//   p.distanceTo(P)			The distance between p and the Plane P
// ---------------------------------------------------------------------------

class Point {
public:
  double x, y, z;
  Point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
  Point operator +(Vector v) {return Point(x + v.i, y + v.j, z + v.k);}
  Point& operator +=(Vector v) {x += v.i; y += v.j; z += v.k; return *this;}
  Vector operator -(Point p) {return Vector(x - p.x, y - p.y, z - p.z);}
  double distanceTo(Point p) {return (p - *this).magnitude();}
  double distanceTo(Plane);
};

// ---------------------------------------------------------------------------
// class Plane
//
// A class for 3-D Planes.
//
//   P.a, P.b, P.c, P.d			The components of Plane P (P is the set of
//								all points (x, y, z) for which P.a * x +
//								P.b * y + P.c * z + P.d = 0)
//   Plane(a, b, c d)			Construct from components
//   Plane(p1, p2, p3)			Construct by giving three points on the Plane
//								(may fail if the points are collinear): the
//								Plane's normal is obtained by a right hand
//								rule: curl your right hand ccw around p1 to
//								p2 to p3 then your thumb orients the normal
//   P.normal()					The vector <P.a, P.b, P.c>
// ---------------------------------------------------------------------------

class Plane {
public:
  double a, b, c, d;
  Plane(double a = 0, double b = 0, double c = 1, double d = 0);
  Plane(Point p1, Point p2, Point p3);
  Vector normal() {return Vector(a, b, c);}
};

// ---------------------------------------------------------------------------
// class Ray.
//
// A class for 3-D rays.
//
//   r.origin, r.direction		The components of the ray r
//	 Ray(origin, direction)		Construct from components
//   r(u)						The point on r at distance u * |r.direction|
//								from r.origin.
// ---------------------------------------------------------------------------

class Ray {
public:
  Point origin;
  Vector direction;
  Ray(Point origin, Vector direction): origin(origin), direction(direction) {}
  Point operator()(double u) {return origin + u * direction;}
};

// ---------------------------------------------------------------------------
// Bodies of inlined operations.
// ---------------------------------------------------------------------------

inline Vector::Vector(Point p): i(p.x), j(p.y), k(p.z)
{
}

inline Vector Vector::cross(Vector v)
{
  return Vector(j * v.k - k * v.j, k * v.i - i * v.k, i * v.j - j * v.i);
}

inline Plane::Plane(double a, double b, double c, double d):
  a(a), b(b), c(c), d(d)
{
}

inline double Point::distanceTo(Plane P)
{
	double temp = P.a * x + P.b * y + P.c * z + P.d;
	if (temp < 0){temp = -temp;}
	return temp / P.normal().magnitude();
}

inline Plane::Plane(Point p1, Point p2, Point p3)
{
  Vector n = (p2 - p1).cross(p3 - p1);
  a = n.i;
  b = n.j;
  c = n.k;
  d = -(Vector(p1).dot(n));
}

#endif