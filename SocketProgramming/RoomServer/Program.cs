using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Servers
{
    class RoomServer
    {
        private static byte[] buffer = new byte[1024];
        private static List<Socket> sockets = new List<Socket> ();
        private static Socket roomServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        static void Main(string[] args)
        {
            Console.Title = "Room Server";
            SetupServer();
            TryToSend();
        }

        private static void TryToSend()
        {
            while (true)
            {

                Console.Write("Enter a request: ");
                DetermineFunctionality(Console.ReadLine());
                /*
                byte[] requestBuffer = Encoding.ASCII.GetBytes(request);
                roomServerSocket.Send(requestBuffer);

                byte[] receiveBuffer = new byte[1024];
                int receivedBytes = roomServerSocket.Receive(receiveBuffer);

                byte[] data = new byte[receivedBytes];
                Array.Copy(receiveBuffer, data, receivedBytes);
                Console.WriteLine("Received: " + Encoding.ASCII.GetString(data));
                */
            }
        }

        private static void DetermineFunctionality(string text)
        {
            string startupPath = Path.Combine(Directory.GetParent(System.IO.Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName, "RoomDatabase.txt");
            string databseText = System.IO.File.ReadAllText(startupPath);
            if (text.ToLower().Contains("add room"))   //modify here!!!!
            {
                string roomName = text.Substring(9);
                if (databseText.Contains(roomName))
                {
                    Console.WriteLine("Room already exists!");
                }
                else
                {
                    Console.WriteLine("Room " + roomName + " added!");
                    File.AppendAllText(startupPath, roomName+"\n");
                }
            }
            else if (text.ToLower().Contains("remove room"))
            {
                string roomName = text.Substring(12);
                if (databseText.Contains(roomName))
                {
                    Console.WriteLine("Room " + roomName + " deleted!");
                    File.WriteAllLines(startupPath, File.ReadLines(startupPath).Where(l => l != roomName).ToList());
                }
                else
                {
                    Console.WriteLine("Room " + roomName + " doesn't exist!");
                }
            }
            else if (text.ToLower().Contains("reserve room"))
            {

            }
            else
            {
                Console.WriteLine("Not valid!");
            }
        }

        private static void SetupServer()
        {
            Console.WriteLine("Setting up RoomServer...");
            roomServerSocket.Bind(new IPEndPoint(IPAddress.Any, 100));
            roomServerSocket.Listen(1);
            roomServerSocket.BeginAccept(new AsyncCallback(AcceptCallback), null);
            
        }

        private static void AcceptCallback(IAsyncResult asyncResult)
        {
            Socket socket = roomServerSocket.EndAccept(asyncResult);
            sockets.Add(socket);
            Console.WriteLine("Client connected.");
            socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, new AsyncCallback(Receive), socket);
            roomServerSocket.BeginAccept(new AsyncCallback(AcceptCallback), null);
        }

        private static void Receive(IAsyncResult asyncResult)
        {
            Socket socket = (Socket)asyncResult.AsyncState;
            int received = socket.EndReceive(asyncResult);
            byte[] tempBuffer = new byte[received];
            Array.Copy(buffer, tempBuffer, received);

            string text = Encoding.ASCII.GetString(tempBuffer);
            Console.WriteLine("Text received: " + text);
        }

        private static void SendText(string text, Socket socket)
        {
            byte[] data = Encoding.ASCII.GetBytes(text);
            socket.BeginSend(data, 0, data.Length, SocketFlags.None, new AsyncCallback(SendCallBack), socket);
            socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, new AsyncCallback(Receive), socket);
        }

        private static void SendCallBack(IAsyncResult asyncResult)
        {
            Socket socket = (Socket)asyncResult.AsyncState;
            socket.EndSend(asyncResult);
        }
    }
}