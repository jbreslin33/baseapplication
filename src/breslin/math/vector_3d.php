var Vector3D = new Class(
{
	
initialize: function()
{
	this.x = 0;
	this.y = 0;
	this.z = 0;
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

initialize: function(x1,y1,z1)
{
	this.x = x1;
	this.y = y1;
	this.z = z1;
},

length: function()
{
	this.log('lx:' + this.x);
	this.log('ly:' + this.y);
	this.log('lz:' + this.z);
        return Math.sqrt(this.x*this.x + this.y*this.y + this.z*this.z);
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
//	this.log('l:' + len);
	if (len == 0)
	{
		return;
	}
	this.x /= len;
	this.y /= len;
	this.z /= len;
},

multiply: function(num)
{
	this.x = this.x * num;
	this.y = this.y * num;
	this.z = this.z * num;
},

add: function(vectorToAddtoThisOne)
{
	this.x = this.x + vectorToAddtoThisOne.x;
	this.y = this.y + vectorToAddtoThisOne.y;
	this.z = this.z + vectorToAddtoThisOne.z;
},

subtract: function(vectorToSubtract)
{
        this.x = this.x - vectorToSubtract.x;
        this.y = this.y - vectorToSubtract.y;
        this.z = this.z - vectorToSubtract.z;

},

subtract: function(sub1,sub2)
{
	this.x = sub1.x - sub2.x;
	this.y = sub1.y - sub2.y;
	this.z = sub1.z - sub2.z;
},

copyValuesFrom: function(copyFrom)
{
	this.x = copyFrom.x;
	this.y = copyFrom.y;
	this.z = copyFrom.z;
},

dot: function(v2)
{
	d = this.x * v2.x + this.y * v2.y + this.z * v2.z;
}

});
/*



*/
