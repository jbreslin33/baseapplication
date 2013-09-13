class Singleton{

	private static Singleton singletonObject;

	/** A private Constructor prevents any other class from instantiating. */
	private Singleton(){
		  //	 Optional Code
	}

	public static synchronized Singleton getSingletonObject()
	{
	    if (singletonObject == null){
	    	singletonObject = new Singleton();
	    }
	    return singletonObject;
	}

	public Object clone()throws CloneNotSupportedException
	{
	    throw new CloneNotSupportedException();
	}

}