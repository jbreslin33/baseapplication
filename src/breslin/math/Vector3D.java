package breslin.math;

import java.lang.Math;

public class Vector3D
{

double x;
double y;
double z;

public Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

double length()
{
	return Math.sqrt(x*x + y*y + z*z);
}

boolean isZero()
{
	if (x == 0.0 && y == 0.0 && z == 0.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void zero()
{
	x = 0;
	y = 0;
	z = 0;
}

void normalise()
{
	double len = length();
	if (len == 0)
		return;
	x /= len;
	y /= len;
	z /= len;
}

}

