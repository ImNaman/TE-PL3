import java.io.*;
import java.net.*;
import java.util.Scanner;

class Client
{
	static Scanner sc=new Scanner(System.in);
	public static void main(String args[]) throws IOException,UnknownHostException
	{
		Socket cs=new Socket("localhost",5001);
		BufferedReader fromserver=new BufferedReader(new InputStreamReader(cs.getInputStream()));
		PrintWriter toserver=new PrintWriter(cs.getOutputStream(),true);
	
		while(true)
		{
			String s=fromserver.readLine();
			System.out.println("From Server :"+s);
			String c=sc.nextLine();
			toserver.println(c);
			if(c.equalsIgnoreCase("bye"))
				break;
		}
		System.out.println("Connection has been terminated !");
		toserver.close();
		fromserver.close();
		cs.close();
	}
}