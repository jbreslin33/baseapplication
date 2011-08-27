
package breslin.clientside.dispatch;

/******************************************************
*				CLASS
********************************************************/
public class Dispatch
{


public Dispatch()
{
	mMaxSize = 1400;
	mCharArray = new byte[mMaxSize];
	mSize		= 0;
	mReadCount	= 0;
}
/**************************************************
*			VARIABLES
**************************************************/

	int				mMaxSize;
	int				mSize;
	int				mReadCount;
	byte[]			mCharArray;

/**************************************************
*			METHODS
**************************************************/
	//admin

int             getReadCount()

{
	return mReadCount;
}

void			BeginReading()
{

}

//char			*GetNewPoint(int length);

void			Clear()
{

}

int				GetSize()
{
	return mSize;
}

void			SetSize(int s)
{
	mSize = s;
}

//write
void			WriteByte  (byte  b)
{

}

void			WriteShort (short s)
{

}

void			WriteFloat (float f)
{

}

//read
byte			ReadByte   ()
{
	return 0;

}

short			ReadShort  ()
{
	return 0;
}
float			ReadFloat  ()
{
	return 0;
}




}