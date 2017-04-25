import java.io.*;
import java.net.*;

public class Server 
{
	int no_clients=0;
	ServerSocket ss=new ServerSocket(5001);
	public static void main(String args[]) throws IOException
	{
		new Server();
	}
	
	public Server() throws IOException
	{
		while(true)
		{
			no_clients++;
			Client_runnable tmp_client_runnable = new Client_runnable(no_clients,ss.accept());
			Thread t = new Thread(tmp_client_runnable);
			t.start();
		}
	}
}

class Client_runnable implements Runnable
{
	int id;
	Socket cs;

	Client_runnable(int id,Socket cs)
	{
		this.id=id;
		this.cs=cs;
	}
		
	public void run()
	{
		try
		{
			BufferedReader fromclient=new BufferedReader(new InputStreamReader(cs.getInputStream()));
			PrintWriter toclient=new PrintWriter(cs.getOutputStream(),true);
			toclient.println("Welcome Client Id :"+id+" to Multithreaded Echo Server");
			while(true)
			{
				String s=fromclient.readLine();
				System.out.println("From Client "+id+" :"+s);
				toclient.println(s);
				if(s.equalsIgnoreCase("bye"))
					break;
			}
			System.out.println("Connection with Client Id :"+id+" Terminated");
			toclient.close();
			fromclient.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
