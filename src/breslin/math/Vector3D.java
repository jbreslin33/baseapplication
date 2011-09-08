package breslin.math;

import java.lang.Math;
import com.jme3.math.Quaternion;
  import com.jme3.math.Vector3f;

public class Vector3D
{

public double x;
public double y;
public double z;

public Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

public Vector3D(double x1, double y1, double z1)
{
	x = x1;
	y = y1;
	z = z1;
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

/*
 public      Quaternion getRotationTo(Vector3f dest)
        {


			Vector3f fallbackAxis = new Vector3f();

			Vector3f thisVector3f = new Vector3f();
            // Based on Stan Melax's article in Game Programming Gems
            Quaternion q;
            // Copy, since cannot modify local
            Vector3f v0 = thisVector3f;
            Vector3f v1 = dest;
            v0.normalize();
            v1.normalize();

            float d = v0.dot(v1);
            // If dot == 1, vectors are the same
            if (d >= 1.0f)
            {
                //return Quaternion::IDENTITY;
                return new Quaternion(1.0f,0.0f,0.0f,0.0f);
            }
			if (d < (1e-6f - 1.0f))
			{
				if (fallbackAxis != new Vector3f())
				{
					// rotate 180 degrees about the fallback axis
					//q.FromAngleAxis(Radian(java.lang.Math.PI), fallbackAxis);
				}
				else
				{
					// Generate an axis
					Vector3f axis = new Vector3f(1,0,0).crossProduct(thisVector3f);
					if (axis.isZeroLength()) // pick another if colinear
						axis = new Vector3f(0,1,0).crossProduct(thisVector3f);
					axis.normalise();
					q.FromAngleAxis(Radian(PI), axis);
				}
			}
			else
			{
                Real s = Math.sqrt( (1+d)*2 );
	            Real invs = 1 / s;

				Vector3 c = v0.crossProduct(v1);

    	        q.x = c.x * invs;
        	    q.y = c.y * invs;
            	q.z = c.z * invs;
            	q.w = s * 0.5f;
				q.normalise();
			}
            return q;
        }
*/

}

