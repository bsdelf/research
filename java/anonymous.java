//package test;
import java.util.*;

class User
{
    public String getName()
    {
	return name;
    }

    public void setName(String name)
    {
	this.name = name;
    }

    public int getId()
    {
	return id;
    }

    public void setId(int id)
    {
	this.id = id;
    }

    private String name = null;
    private int id;
}

public class anonymous
{
    public static void test(final User user)
    {
	(new Thread() {
	     public void run() {
		 System.out.println("user.name:" + user.getName());
	     }
	 }
	).start();
    }

    private static int lowerBound(ArrayList<Integer> array, Integer value)
    {
	int first = 0;
	int count = array.size();
	while (count > 0)
	{
	    int step = count / 2;
	    int it = first+step;
	    if (array.get(it) < value)
	    {
		first = ++it;
		count -= step;
	    }
	    else
	    {
		count = step;
	    }
	}

	return first;
    }

    public static void main(String[] args)
    {
	User user = new User();
	user.setId(02);
	user.setName("shen");

	anonymous testFinal = new anonymous();
	anonymous.test(user);

	ArrayList<Integer> list = new ArrayList<Integer>();
	list.add(0);
	list.add(10);
	list.add(30);
	list.add(35);
	list.add(65);
	list.add(75);
	list.add(85);

	System.out.println(lowerBound(list, 1));
	System.out.println(lowerBound(list, 88));
    }
}
