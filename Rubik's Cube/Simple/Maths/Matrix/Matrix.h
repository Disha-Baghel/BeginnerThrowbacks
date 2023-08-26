#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix2D
{
public:

	Matrix2D();
	Matrix2D(const float src[4]);
	Matrix2D(float m0, float m1,float m2,float m3);

	void 		set(const float src[4]);
	void 		set(float m0,float m1,float m2,float m3);
	void 		setRow(int index, const float row[2]);
	void 		setRow(int index, const Vector2D& v);
	void		SetColumn(int index, const float col[2]);
	void		SetColumn(int index, const Vector2D& v);

	const float* get() const;
	const float* getTranspose();
	Vector2D	getRow(int index) const;
	Vector2D	getColumn(int index) const;
	float 		getDeterminant() const;
	float 		getAngle() const;

	Matrix2D& 	identity();
	Matrix2D&	transpose();
	Matrix2D& 	invert();

	// operations
	Matrix2D	operator+(const Matrix2D& rhs) const;
	Matrix2D	operator-(const Matrix2D& rhs) const;
	Matrix2D&	operator+=(const Matrix2D& rhs);
	Matrix2D&	operator-=(const Matrix2D& rhs);
	Vector2D	operator*(const Vector2D& rhs) const;
	Matrix2D	operator*(const Matrix2D& rhs) const;
	Matrix2D&	operator*=(const Matrix2D& rhs);
	bool		operator==(const Matrix2D& rhs) const;
	bool 		operator!=(const Matrix2D& rhs) const;
	float 		operator[](int index) const;

	friend Matrix2D operator-(const Matrix2D& m);
	friend Matrix2D operator*(float scalar, const Matrix2D& m);
	friend Vector2D operator*(const Vector2D& vec, const Matrix2D& m);
	friend std::ostream& operator<<(std::ostream& os, const Matrix2D& m);

private:
	float m[4];
	float tm[4];
};

class Matrix3D
{
public:
    // constructors
    Matrix3D();  // init with identity
    Matrix3D(const float src[9]);
    Matrix3D(float m0, float m1, float m2,           // 1st column
            float m3, float m4, float m5,           // 2nd column
            float m6, float m7, float m8);          // 3rd column

    void        set(const float src[9]);
    void        set(float m0, float m1, float m2,   // 1st column
                    float m3, float m4, float m5,   // 2nd column
                    float m6, float m7, float m8);  // 3rd column
    void        setRow(int index, const float row[3]);
    void        setRow(int index, const Vector3D& v);
    void        setColumn(int index, const float col[3]);
    void        setColumn(int index, const Vector3D& v);

    const float* get() const;
    const float* getTranspose();
    Vector3D     getRow(int index) const;
    Vector3D     getColumn(int index) const;
    float        getDeterminant() const;
    Vector3D     getAngle() const;                       // return (pitch, yaw, roll) in degree
    Matrix3D&    identity();
    Matrix3D&    transpose();                            // transpose itself and return reference
    Matrix3D&    invert();

    // operators
    Matrix3D     operator+(const Matrix3D& rhs) const;    // add rhs
    Matrix3D     operator-(const Matrix3D& rhs) const;    // subtract rhs
    Matrix3D&    operator+=(const Matrix3D& rhs);         // add rhs and update this object
    Matrix3D&    operator-=(const Matrix3D& rhs);         // subtract rhs and update this object
    Vector3D     operator*(const Vector3D& rhs) const;    // multiplication: v' = M * v
    Matrix3D     operator*(const Matrix3D& rhs) const;    // multiplication: M3 = M1 * M2
    Matrix3D&    operator*=(const Matrix3D& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const Matrix3D& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Matrix3D& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    // friends functions
    friend Matrix3D operator-(const Matrix3D& m);                     // unary operator (-)
    friend Matrix3D operator*(float scalar, const Matrix3D& m);       // pre-multiplication
    friend Vector3D operator*(const Vector3D& vec, const Matrix3D& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const Matrix3D& m);

protected:

private:
    float m[9];
    float tm[9];
};

class Matrix4D
{
public:
    // constructors
    Matrix4D();  // init with identity
    Matrix4D(const float src[16]);
    Matrix4D(float m00, float m01, float m02, float m03, // 1st column
            float m04, float m05, float m06, float m07, // 2nd column
            float m08, float m09, float m10, float m11, // 3rd column
            float m12, float m13, float m14, float m15);// 4th column

    void        set(const float src[16]);
    void        set(float m00, float m01, float m02, float m03, // 1st column
                    float m04, float m05, float m06, float m07, // 2nd column
                    float m08, float m09, float m10, float m11, // 3rd column
                    float m12, float m13, float m14, float m15);// 4th column
    void        setRow(int index, const float row[4]);
    void        setRow(int index, const Vector4D& v);
    void        setRow(int index, const Vector3D& v);
    void        setColumn(int index, const float col[4]);
    void        setColumn(int index, const Vector4D& v);
    void        setColumn(int index, const Vector3D& v);

    const float* get() const;
    const float* getTranspose();                        // return transposed matrix
    Vector4D     getRow(int index) const;                // return the selected row vector
    Vector4D     getColumn(int index) const;             // return the selected col vector
    float       getDeterminant() const;
    Vector3D     getAngle() const;                       // return (pitch, yaw, roll) in degree
    Vector3D     getLeftAxis() const;                    // return left vector
    Vector3D     getUpAxis() const;                      // return up vector
    Vector3D     getForwardAxis() const;                 // return forward vector

    Matrix4D&    identity();
    Matrix4D&    transpose();                            // transpose itself and return reference
    Matrix4D&    invert();                               // check best inverse method before inverse
    Matrix4D&    invertEuclidean();                      // inverse of Euclidean transform matrix
    Matrix4D&    invertAffine();                         // inverse of affine transform matrix
    Matrix4D&    invertProjective();                     // inverse of projective matrix using partitioning
    Matrix4D&    invertGeneral();                        // inverse of generic matrix

    // transform matrix
    Matrix4D&    translate(float x, float y, float z);   // translation by (x,y,z)
    Matrix4D&    translate(const Vector3D& v);            //
    Matrix4D&    rotate(float angle, const Vector3D& axis); // rotate angle(degree) along the given axix
    Matrix4D&    rotate(float angle, float x, float y, float z);
    Matrix4D&    rotateX(float angle);                   // rotate on X-axis with degree
    Matrix4D&    rotateY(float angle);                   // rotate on Y-axis with degree
    Matrix4D&    rotateZ(float angle);                   // rotate on Z-axis with degree
    Matrix4D&    scale(float scale);                     // uniform scale
    Matrix4D&    scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
    Matrix4D&    lookAt(float tx, float ty, float tz);   // face object to the target direction
    Matrix4D&    lookAt(float tx, float ty, float tz, float ux, float uy, float uz);
    Matrix4D&    lookAt(const Vector3D& target);
    Matrix4D&    lookAt(const Vector3D& target, const Vector3D& up);
    //@@Matrix4D&    skew(float angle, const Vector3D& axis); //

    // operators
    Matrix4D     operator+(const Matrix4D& rhs) const;    // add rhs
    Matrix4D     operator-(const Matrix4D& rhs) const;    // subtract rhs
    Matrix4D&    operator+=(const Matrix4D& rhs);         // add rhs and update this object
    Matrix4D&    operator-=(const Matrix4D& rhs);         // subtract rhs and update this object
    Vector4D     operator*(const Vector4D& rhs) const;    // multiplication: v' = M * v
    Vector3D     operator*(const Vector3D& rhs) const;    // multiplication: v' = M * v
    Matrix4D     operator*(const Matrix4D& rhs) const;    // multiplication: M3 = M1 * M2
    Matrix4D&    operator*=(const Matrix4D& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const Matrix4D& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Matrix4D& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    // friends functions
    friend Matrix4D operator-(const Matrix4D& m);                     // unary operator (-)
    friend Matrix4D operator*(float scalar, const Matrix4D& m);       // pre-multiplication
    friend Vector3D operator*(const Vector3D& vec, const Matrix4D& m); // pre-multiplication
    friend Vector4D operator*(const Vector4D& vec, const Matrix4D& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const Matrix4D& m);

protected:

private:
    float       getCofactor(float m0, float m1, float m2,
                            float m3, float m4, float m5,
                            float m6, float m7, float m8) const;

    float m[16];
    float tm[16];                                       // transpose m

};

#endif // MATRIX_H
