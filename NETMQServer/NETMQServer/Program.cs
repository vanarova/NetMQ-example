using NetMQ;
using NetMQ.Sockets;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETMQServer
{
    class Program
    {
        /// SERVER
        
        static void Main(string[] args)
        {
            string message;
            bool status;
            using (var responseSocket = new ResponseSocket("@tcp://*:5252"))
            //using (var requestSocket = new RequestSocket(">tcp://localhost:5252"))
            {
                //Console.WriteLine("requestSocket : Sending 'Hello'");
                //requestSocket.SendFrame("Hello");

                //Start and wait for messages
                //Console.WriteLine("Start and wait for messages");
                //Console.ReadLine();
                while (true)
                {
                    status = responseSocket.TryReceiveFrameString(out message);

                    if (status)
                    {
                        Console.WriteLine("responseSocket : Server Received '{0}'", message);
                        status = responseSocket.TrySendFrame("World");
                        if (status)
                        {
                            continue;
                        }
                        else
                        {
                            //May happen that another frame arrives, before sending, may never happen this scenario.
                            responseSocket.TrySkipFrame();
                        }
                    }
                  
                }
                
                //Console.WriteLine("responseSocket : Server Received '{0}'", message);
                //Console.WriteLine("responseSocket Sending 'World'");

                
                //responseSocket.SendFrame("World");
                //Console.WriteLine("Received executed, Sent reponse");
                //Console.ReadLine();
                ////message = requestSocket.ReceiveFrameString();
                //Console.WriteLine("requestSocket : Received '{0}'", message);
                //Console.WriteLine("All Done..");
                //Console.ReadLine();
            }
        }
    }
}
