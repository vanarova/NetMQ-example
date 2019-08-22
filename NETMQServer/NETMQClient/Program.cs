using NetMQ;
using NetMQ.Sockets;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETMQClient
{

    //CLIENT
    class Program
    {
        static void Main(string[] args)
        {
            //Start response socket first..
            //using (var responseSocket = new ResponseSocket("@tcp://*:5252"))


            string message;
            try
            {
                Random rand = new Random(1000);
                bool status = true;
                //Now start request socket & send msg
                using (var requestSocket = new RequestSocket(">tcp://localhost:5252"))
                {
                    while (status)
                    {
                        Console.WriteLine("requestSocket : Sending 'Hello'");
                        status = requestSocket.TrySendFrame("Hello");
                        //Console.WriteLine("Send Status:" + status);
                        //var message = responseSocket.ReceiveFrameString();
                        //Console.WriteLine("responseSocket : Server Received '{0}'", message);
                        //Console.WriteLine("responseSocket Sending 'World'");
                        //responseSocket.SendFrame("World");

                        if (status)
                        {
                            for (int i = 0; i < 3; i++)
                            {
                                System.Threading.Thread.Sleep(100);
                                status = requestSocket.TryReceiveFrameString(out message);
                                Console.WriteLine("requestSocket : Received '{0}'", message);
                                if (status)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            //Break
                            break;
                        }
                        //wait to receive
                        //Console.WriteLine("Will execute to receive");
                        //Console.ReadKey();
                
                       
                        
                        //Console.WriteLine("All Done..");
                        //Console.ReadKey();
                        
                        System.Threading.Thread.Sleep(rand.Next(100,1000));
                    }
                }
            }
            catch (Exception)
            {

                throw;
            }

        }
    }
}
