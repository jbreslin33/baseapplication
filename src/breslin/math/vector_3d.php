var Vector3D = new Class(
{
	
initialize: function()
{
	this.x = 0;
	this.y = 0;
	this.z = 0;
},

initialize: function(x1,y1,z1)
{
	this.x = x1;
	this.y = y1;
	this.z = z1;
},

length: function()
{
        //return sqrt(x*x + y*y + z*z);
},

isZero: function()
{
        if (this.x == 0.0 && this.y == 0.0 && this.z == 0.0)
        {
                return true;
        }
        else
        {
                return false;
        }
	
},

zero: function()
{
	this.x = 0
	this.y = 0
	this.z = 0
},

normalise: function()
{
	len = this.length();
	if (len == 0)
	{
		return;
	}
	x /= len;
	y /= len;
	z /= len;
}


});
/*


*/
