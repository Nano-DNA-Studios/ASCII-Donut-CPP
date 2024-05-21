#pragma once

#include <algorithm>


class Light
{
public:

	float X;

	float Y;

	float Z;

	float Strength;

private:

	const float pi = 3.141f;




public:
	Light(float x, float y, float z, int strength)
	{
		X = x;
		Y = y;
		Z = z;
		Strength = strength;
	}
	
	/// <summary>
		/// Calculates the intensity of the light on an object at a given point based off the Inverse Square Law
		/// </summary>
		/// <param name="ox"> Objects X Position </param>
		/// <param name="oy"> Objects Y Position </param>
		/// <param name="oz"> Objects Z Position </param>
		/// <returns> The Intensity Value at a point on an object. </returns>
	float GetIntensity(float ox, float oy, float oz)
	{
		float rx = ox - X;
		float ry = oy - Y;
		float rz = oz - Z;

		float r = sqrtf(rx * rx + ry * ry + rz + rz);

		return r > 0 ? Strength / (4 * pi * r) : Strength / (4 * pi);
	}







};

