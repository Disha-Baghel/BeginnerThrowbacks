#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector2D
{
	float x;
	float y;

	// ctors
	Vector2D(): x(0), y(0){}
	Vector2D(float x, float y) : x(x),y(y){}

	// utils Functions
	void 		set(float x,float y);
	float 		length() const;
	float 		distance(const Vector2D& vec) const;
	Vector2D&	normalize();
	float		dot(const Vector2D& vec) const;
	bool		equal(const Vector2D& vec,float e) const;

	// operators
	Vector2D	operator-() const;
	Vector2D	operator+(const Vector2D& rhs) const;
	Vector2D	operator-(const Vector2D& rhs) const;
	Vector2D&	operator+=(const Vector2D& rhs);
	Vector2D& 	operator-=(const Vector2D& rhs);
	Vector2D	operator*(const float scale) const;
	Vector2D	operator*(const Vector2D& rhs) const;
	Vector2D&	operator*=(const float scale);
	Vector2D&	operator*=(const Vector2D& rhs);
	Vector2D	operator/(const float scale) const;
	Vector2D&	operator/=(const float scale);
	bool 		operator==(const Vector2D& rhs) const;
	bool 		operator!=(const Vector2D& rhs) const;
	bool 		operator<(const Vector2D& rhs) const;
	float		operator[](int index) const;
	float&		operator[](int index);

	friend Vector2D operator*(const float a,const Vector2D vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D vec);
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(float x,float y,float z) : x(x), y(y), z(z) {}

	void		set(float x,float y,float z);
	float		length() const;
	float 		distance(const Vector3D& vec) const;
	float 		angle(const Vector3D& vec) const;
	Vector3D&	normalize();
	float		dot(const Vector3D& vec) const;
	Vector3D	cross(const Vector3D& vec) const;
	void 		translate(float _x,float _y,float _z);
	void		rotate(float angle,float _x,float _y,float _z);
	bool 		equal(const Vector3D& vec,float e) const;

	// operators
	Vector3D	operator-() const;
	Vector3D	operator+(const Vector3D& rhs) const;
	Vector3D	operator-(const Vector3D& rhs) const;
	Vector3D&	operator+=(const Vector3D& rhs);
	Vector3D& 	operator-=(const Vector3D& rhs);
	Vector3D	operator*(const float scale) const;
	Vector3D	operator*(const Vector3D& rhs) const;
	Vector3D&	operator*=(const float scale);
	Vector3D&	operator*=(const Vector3D& rhs);
	Vector3D	operator/(const float scale) const;
	Vector3D&	operator/=(const float scale);
	bool 		operator==(const Vector3D& rhs) const;
	bool 		operator!=(const Vector3D& rhs) const;
	bool 		operator<(const Vector3D& rhs) const;
	float		operator[](int index) const;
	float&		operator[](int index);

	friend Vector3D operator*(const float a,const Vector3D vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
};

struct Vector4D
{
	float x;
	float y;
	float z;
	float w;

	// ctors
	Vector4D() : x(0), y(0), z(0), w(0) {}
	Vector4D(float x,float y,float z,float w) : x(x),y(y),z(z),w(w) {}

	// utils Functions
	void 		set(float x,float y,float z,float w);
	float 		length() const;
	float 		distance(const Vector4D& vec) const;
	Vector4D& 	normalize();
	float		dot(const Vector4D& vec) const;
	bool 		equal(const Vector4D& vec, float e) const;

	// operators
	Vector4D	operator-() const;
	Vector4D	operator+(const Vector4D& rhs) const;
	Vector4D	operator-(const Vector4D& rhs) const;
	Vector4D&	operator+=(const Vector4D& rhs);
	Vector4D& 	operator-=(const Vector4D& rhs);
	Vector4D	operator*(const float scale) const;
	Vector4D	operator*(const Vector4D& rhs) const;
	Vector4D&	operator*=(const float scale);
	Vector4D&	operator*=(const Vector4D& rhs);
	Vector4D	operator/(const float scale) const;
	Vector4D&	operator/=(const float scale);
	bool 		operator==(const Vector4D& rhs) const;
	bool 		operator!=(const Vector4D& rhs) const;
	bool 		operator<(const Vector4D& rhs) const;
	float		operator[](int index) const;
	float&		operator[](int index);

	friend Vector4D operator*(const float a,const Vector4D vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector4D vec);
};

#endif // VECTOR_H
