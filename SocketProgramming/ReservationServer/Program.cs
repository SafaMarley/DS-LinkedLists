using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Servers
{
    class ReservationServer
    {
        private static Socket reservationServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        static void Main(string[] args)
        {
            Console.Title = "Reservation Server";
            TryToConnect();
            TryToSend();
            Console.ReadLine();
        }

        private static void TryToSend()
        {
            while (true)
            {
                Console.Write("Enter a request: ");
                DetermineFunctionality(Console.ReadLine());
                /*
                byte[] requestBuffer = Encoding.ASCII.GetBytes(request);
                reservationServerSocket.Send(requestBuffer);

                byte[] receiveBuffer = new byte[1024];
                int receivedBytes = reservationServerSocket.Receive(receiveBuffer);

                byte[] data = new byte[receivedBytes];
                Array.Copy(receiveBuffer, data, receivedBytes);
                Console.WriteLine("Received: " + Encoding.ASCII.GetString(data));
                */
            }
        }

        private static void DetermineFunctionality(string text)
        {
            string startupPath = Path.Combine(Directory.GetParent(System.IO.Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName, "ActivityDatabase.txt");
            string databseText = System.IO.File.ReadAllText(startupPath);
            if (text.ToLower().Contains("add reservation"))
            {
                string roomName = text.Substring(16);
                if (databseText.Contains(roomName))
                {
                    Console.WriteLine("Reservation already exists!");
                }
                else
                {
                    Console.WriteLine("Reservation " + roomName + " added!");
                    File.AppendAllText(startupPath, roomName + "\n");
                }
            }
            else if (text.ToLower().Contains("remove reservation"))
            {
                string roomName = text.Substring(19);
                if (databseText.Contains(roomName))
                {
                    Console.WriteLine("Reservation " + roomName + " deleted!");
                    File.WriteAllLines(startupPath, File.ReadLines(startupPath).Where(l => l != roomName).ToList());
                }
                else
                {
                    Console.WriteLine("Reservation " + roomName + " doesn't exist!");
                }
            }
        }

        private static void TryToConnect()
        {
            int attemptsToConnect = 0;

            while (!reservationServerSocket.Connected)
            {
                try
                {
                    attemptsToConnect++;
                    reservationServerSocket.Connect(IPAddress.Loopback, 100);
                }
                catch (SocketException)
                {
                    Console.WriteLine("Connection attempts: " + attemptsToConnect.ToString());
                }
            }

            Console.Clear();
            Console.WriteLine("Connected");
        }
    }
}