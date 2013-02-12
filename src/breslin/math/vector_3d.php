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

printValues: function()
{
	this.log('xx: ' + this.x + 'yy: ' + this.y + 'zz: ' + this.z); 	
},

length: function()
{
/*
	this.log('lx:' + this.x);
	this.log('ly:' + this.y);
	this.log('lz:' + this.z);
*/
        return Math.sqrt(this.x*this.x + this.z*this.z);


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
	this.y = 0;
	this.z /= len;
},
//multiply this vector by a scalar
/*
void Vector3D::multiply(float num)
{
        x = x * num;
        y = y * num;
        z = z * num;
}
*/
multiply: function(num)
{
	this.x = parseFloat(this.x) * num;
	this.y = parseFloat(this.y) * num;
	this.z = parseFloat(this.z) * num;
	/*	
	this.x = this.x * num;
	this.y = this.y * num;
	this.z = this.z * num;
*/
},

add: function(v)
{
	this.x = parseFloat(this.x) + parseFloat(v.x);
	this.y = 0;
	this.z = parseFloat(this.z) + parseFloat(v.z);

	this.x = parseFloat(this.x);
	this.z = parseFloat(this.z);
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
