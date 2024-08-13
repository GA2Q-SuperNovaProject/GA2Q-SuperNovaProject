#pragma once

struct Vec2 {
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);

	~Vec2() = default;

	void Add(const Vec2& v);                 // v1.Add(v2)
	void Sub(const Vec2& v);                 // v1.Sub(v2)
	void Scale(const float n);               // v1.Scale(n)
	Vec2 Rotate(const float angle) const;    // v1.Rotate(angle)

	float Magnitude() const;                 // v1.Magnitude()
	float MagnitudeSquared() const;          // v1.MagnitudeSquared()

	Vec2& Normalize();                       // v1.Normalize()
	Vec2 UnitVector() const;                 // v1.UnitVector()
	Vec2 Normal() const;                     // n = v1.Normal()
	Vec2 Perpendicular() const; //자신을 수직인 벡터로 바꿔준다.
	float Dot(const Vec2& v) const;          // v1.Dot(v2)
	float Cross(const Vec2& v) const;        // v1.Cross(v2)

	//자신은 사영시키는 물체, 매개변수가 사영되는 대상 (i.e: this: 물체, v : 운동장)
	float Project(const Vec2& v) const; 
	
	Vec2& operator = (const Vec2& v);        // v1 = v2
	bool operator == (const Vec2& v) const;  // v1 == v2
	bool operator != (const Vec2& v) const;  // v1 != v2

	Vec2 operator + (const Vec2& v) const;   // v1 + v2
	Vec2 operator - (const Vec2& v) const;   // v1 - v2
	Vec2 operator * (const float n) const;   // v1 * n
	Vec2 operator / (const float n) const;   // v1 / n
	Vec2 operator - ();                      // -v1

	Vec2& operator += (const Vec2& v);       // v1 += v2
	Vec2& operator -= (const Vec2& v);       // v1 -= v2
	Vec2& operator *= (const float n);       // v1 *= n
	Vec2& operator /= (const float n);       // v1 /= n
};

