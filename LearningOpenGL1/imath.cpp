struct vec4
{
	// data structure
	float values[4];
	
	// constructors
	vec4()
	{
		values[0] = values[1] = values[2] = values[3] = 0;
	}

	vec4(float x, float y, float z, float w)
	{
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
	}

	// operators
	const float& operator[](int index) const
	{
		return values[index];
	}

	float& operator[](int index)
	{
		return values[index];
	}

	vec4& operator+(vec4 other)
	{
		vec4 result;
		result[0] = values[0] + other[0];
		result[1] = values[1] + other[1];
		result[2] = values[2] + other[2];
		result[3] = values[3] + other[3];
		return result;
	}

	vec4& operator-(vec4 other)
	{
		vec4 result;
		result[0] = values[0] - other[0];
		result[1] = values[1] - other[1];
		result[2] = values[2] - other[2];
		result[3] = values[3] - other[3];
		return result;
	}
};


struct mat4
{
	// data structure
	vec4 matrix[4];

	mat4()
	{
		matrix[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		matrix[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
		matrix[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
		matrix[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	mat4(vec4 x, vec4 y, vec4 z, vec4 w)
	{
		matrix[0] = x;
		matrix[1] = y;
		matrix[2] = z;
		matrix[3] = w;
	}

	const vec4& operator[](int index) const
	{
		return matrix[index];
	}
	
	vec4& operator[](int index)
	{
		return matrix[index];
	}

};


// Pre-multiply a vector by a matrix on the left.
vec4 operator*(const mat4& m, const vec4& v)
{
	return vec4(
		m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
		m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
		m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
		m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
	);
}


// Post-multiply a vector by a matrix on the right.
vec4 operator*(const vec4& v, const mat4& m)
{
	return vec4(
		v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
		v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
		v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
		v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
	);
}

// Matrix multiplication
mat4 operator*(const mat4& m1, const mat4& m2)
{
	vec4 X(
		m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
		m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
		m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
		m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3]
	);
	vec4 Y(
		m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
		m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
		m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
		m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]
	);
	vec4 Z(
		m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
		m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
		m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
		m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]
	);
	vec4 W(
		m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
		m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3],
		m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3],
		m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3]
	);

	return mat4(X, Y, Z, W);
}



// Matrix multiplication ( Simlified ) By reusing the previous pre-muliplying
//mat4 operator*(const mat4& m1, const mat4& m2)
//{
//	vec4 X = m1 * m2[0];
//	vec4 Y = m1 * m2[1];
//	vec4 Z = m1 * m2[2];
//	vec4 W = m1 * m2[3];
//
//	return mat4(X, Y, Z, W);
//}




