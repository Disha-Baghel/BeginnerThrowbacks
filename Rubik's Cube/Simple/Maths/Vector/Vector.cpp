#include "Vector.h"
#include <cmath>

 Vector2D Vector2D::operator-() const{
	return Vector2D(-x, -y);
}

 Vector2D Vector2D::operator+(const Vector2D& rhs) const{
	return Vector2D(x+rhs.x, y+rhs.y);
}

 Vector2D Vector2D::operator-(const Vector2D& rhs) const{
	return Vector2D(x-rhs.x, y-rhs.y);
}

 Vector2D& Vector2D::operator+=(const Vector2D& rhs){
	x += rhs.x; y += rhs.y; return *this;
}

 Vector2D& Vector2D::operator-=(const Vector2D& rhs){
	x -= rhs.x; y -= rhs.y; return *this;
}

 Vector2D Vector2D::operator*(const float a) const{
	return Vector2D(x*a, y*a);
}

 Vector2D Vector2D::operator*(const Vector2D& rhs) const{
	return Vector2D(x*rhs.x, y*rhs.y);
}

 Vector2D& Vector2D::operator*=(const float a){
	x *= a; y *= a; return *this;
}

 Vector2D& Vector2D::operator*=(const Vector2D& rhs) {
	x *= rhs.x; y *= rhs.y; return *this;
}

 Vector2D Vector2D::operator/(const float a) const {
	return Vector2D(x/a, y/a);
}

 Vector2D& Vector2D::operator/=(const float a){
	x /= a; y /= a; return *this;
}

 bool Vector2D::operator==(const Vector2D& rhs) const{
	return  (x == rhs.x) && (y == rhs.y);
}

 bool Vector2D::operator!=(const Vector2D& rhs) const{
	return (x != rhs.x) || (y != rhs.y);
}

 bool Vector2D::operator<(const Vector2D& rhs) const{
	if(x < rhs.x) return true;
	if(x > rhs.x) return false;
	if(y < rhs.y) return true;
	if(y > rhs.y) return false;
	return false;
}

 float Vector2D::operator[](int index) const {
	return (&x)[index];
}

 float& Vector2D::operator[](int index) {
	return (&x)[index];
}

 void Vector2D::set(float x,float y){
	this->x = x; this->y = y;
}

 float Vector2D::length() const {
	return sqrt(x*x + y*y);
}

 float Vector2D::distance(const Vector2D& vec) const {
	return sqrt((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y));
}

 Vector2D& Vector2D::normalize(){
	float invLength = 1.0f / length();
	x *= invLength;
	y *= invLength;
	return *this;
}

 float Vector2D::dot(const Vector2D& rhs) const {
	return (x*rhs.x + y*rhs.y);
}

 bool Vector2D::equal(const Vector2D& rhs, float epsilon) const{
	return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

 Vector2D operator*(const float a,const Vector2D vec){
	return Vector2D(a*vec.x, a*vec.y);
}

 std::ostream& operator<<(std::ostream& os,const Vector2D& vec){
	os << '[' << vec.x << ',' << vec.y << ']';
	return os;
}

 Vector3D Vector3D::operator-() const {
    return Vector3D(-x, -y, -z);
}

 Vector3D Vector3D::operator+(const Vector3D& rhs) const {
    return Vector3D(x+rhs.x, y+rhs.y, z+rhs.z);
}

 Vector3D Vector3D::operator-(const Vector3D& rhs) const {
    return Vector3D(x-rhs.x, y-rhs.y, z-rhs.z);
}

 Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; return *this;
}

 Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
}

 Vector3D Vector3D::operator*(const float a) const {
    return Vector3D(x*a, y*a, z*a);
}

 Vector3D Vector3D::operator*(const Vector3D& rhs) const {
    return Vector3D(x*rhs.x, y*rhs.y, z*rhs.z);
}

 Vector3D& Vector3D::operator*=(const float a) {
    x *= a; y *= a; z *= a; return *this;
}

 Vector3D& Vector3D::operator*=(const Vector3D& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this;
}

 Vector3D Vector3D::operator/(const float a) const {
    return Vector3D(x/a, y/a, z/a);
}

 Vector3D& Vector3D::operator/=(const float a) {
    x /= a; y /= a; z /= a; return *this;
}

 bool Vector3D::operator==(const Vector3D& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

 bool Vector3D::operator!=(const Vector3D& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

 bool Vector3D::operator<(const Vector3D& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    return false;
}

 float Vector3D::operator[](int index) const {
    return (&x)[index];
}

 float& Vector3D::operator[](int index) {
    return (&x)[index];
}

 void Vector3D::set(float x, float y, float z) {
    this->x = x; this->y = y; this->z = z;
}

 float Vector3D::length() const {
    return sqrtf(x*x + y*y + z*z);
}

 float Vector3D::distance(const Vector3D& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z));
}

 float Vector3D::angle(const Vector3D& vec) const {
    // return angle between [0, 180]
    float l1 = this->length();
    float l2 = vec.length();
    float d = this->dot(vec);
    float angle = acosf(d / (l1 * l2)) / 3.141592f * 180.0f;
    return angle;
}

 Vector3D& Vector3D::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is ~zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

 float Vector3D::dot(const Vector3D& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

 Vector3D Vector3D::cross(const Vector3D& rhs) const {
    return Vector3D(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

 bool Vector3D::equal(const Vector3D& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

 Vector3D operator*(const float a, const Vector3D vec) {
    return Vector3D(a*vec.x, a*vec.y, a*vec.z);
}

 std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
// END OF Vector3D /////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  functions for Vector4D
///////////////////////////////////////////////////////////////////////////////
 Vector4D Vector4D::operator-() const {
    return Vector4D(-x, -y, -z, -w);
}

 Vector4D Vector4D::operator+(const Vector4D& rhs) const {
    return Vector4D(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

 Vector4D Vector4D::operator-(const Vector4D& rhs) const {
    return Vector4D(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

 Vector4D& Vector4D::operator+=(const Vector4D& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this;
}

 Vector4D& Vector4D::operator-=(const Vector4D& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this;
}

 Vector4D Vector4D::operator*(const float a) const {
    return Vector4D(x*a, y*a, z*a, w*a);
}

 Vector4D Vector4D::operator*(const Vector4D& rhs) const {
    return Vector4D(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
}

 Vector4D& Vector4D::operator*=(const float a) {
    x *= a; y *= a; z *= a; w *= a; return *this;
}

 Vector4D& Vector4D::operator*=(const Vector4D& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this;
}

 Vector4D Vector4D::operator/(const float a) const {
    return Vector4D(x/a, y/a, z/a, w/a);
}

 Vector4D& Vector4D::operator/=(const float a) {
    x /= a; y /= a; z /= a; w /= a; return *this;
}

 bool Vector4D::operator==(const Vector4D& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

 bool Vector4D::operator!=(const Vector4D& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

 bool Vector4D::operator<(const Vector4D& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    if(w < rhs.w) return true;
    if(w > rhs.w) return false;
    return false;
}

 float Vector4D::operator[](int index) const {
    return (&x)[index];
}

 float& Vector4D::operator[](int index) {
    return (&x)[index];
}

 void Vector4D::set(float x, float y, float z, float w) {
    this->x = x; this->y = y; this->z = z; this->w = w;
}

 float Vector4D::length() const {
    return sqrtf(x*x + y*y + z*z + w*w);
}

 float Vector4D::distance(const Vector4D& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z) + (vec.w-w)*(vec.w-w));
}

 Vector4D& Vector4D::normalize() {
    //NOTE: leave w-component untouched
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

 float Vector4D::dot(const Vector4D& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
}

 bool Vector4D::equal(const Vector4D& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon &&
           fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

 Vector4D operator*(const float a, const Vector4D vec) {
    return Vector4D(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
}

 std::ostream& operator<<(std::ostream& os, const Vector4D& vec) {
    os << '[' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << ']';
    return os;
}
