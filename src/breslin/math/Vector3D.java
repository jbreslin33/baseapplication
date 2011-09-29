package breslin.math;

import java.lang.Math;
import com.jme3.math.Quaternion;
  import com.jme3.math.Vector3f;

public class Vector3D
{

public float x;
public float y;
public float z;

public Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

public Vector3D(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

public double length()
{
	return Math.sqrt(x*x + y*y + z*z);
}

public boolean isZero()
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

public void zero()
{
	x = 0;
	y = 0;
	z = 0;
}

public void normalise()
{
	double len = length();
	if (len == 0)
		return;
	x /= len;
	y /= len;
	z /= len;
}


//multiply this vector by a scalar
public void multiply(float num)
{
	x = x * num;
	y = y * num;
	z = z * num;
}

//add another vector to this one
public void add(Vector3D vectorToAddtoThisOne)
{
	x = x + vectorToAddtoThisOne.x;
	y = y + vectorToAddtoThisOne.y;
	z = z + vectorToAddtoThisOne.z;
}

//subtract another vector from this one
public void subtract(Vector3D vectorToAddtoThisOne)
{
	x = x - vectorToAddtoThisOne.x;
	y = y - vectorToAddtoThisOne.y;
	z = z - vectorToAddtoThisOne.z;
}

//copy values
public void copyValuesFrom(Vector3D copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;
}


      // Quaternion getRotationTo(const Vector3& dest,
		//	const Vector3& fallbackAxis = Vector3::ZERO) const
      Quaternion getRotationTo(Vector3D vector,
      {

            // Based on Stan Melax's article in Game Programming Gems
            Quaternion q;
            /*
            // Copy, since cannot modify local
            Vector3 v0 = *this;
            Vector3 v1 = dest;
            v0.normalise();
            v1.normalise();

            Real d = v0.dotProduct(v1);
            // If dot == 1, vectors are the same
            if (d >= 1.0f)
            {
                return Quaternion::IDENTITY;
            }
			if (d < (1e-6f - 1.0f))
			{
				// rotate 180 degrees about the fallback axis
				q.FromAngleAxis(Radian(Math::PI), fallbackAxis);

			}
			else
			{
                Real s = Math::Sqrt( (1+d)*2 );
	            Real invs = 1 / s;

				Vector3 c = v0.crossProduct(v1);

    	        q.x = c.x * invs;
        	    q.y = c.y * invs;
            	q.z = c.z * invs;
            	q.w = s * 0.5f;
				q.normalise();
			}
        */
			return q;
}

*/




}

