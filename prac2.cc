//#include <fstream>
#include "ns3/core-module.h"
#include "ns3/netanim-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"

using namespace ns3;

int main(int argc,char *argv[])
{
 NodeContainer nodes;
 nodes.Create(4);

 CsmaHelper csma;
 csma.SetChannelAttribute("DataRate",StringValue("5Mbps"));
 csma.SetChannelAttribute("Delay",StringValue("1ms"));
 csma.SetDeviceAttribute("Mtu",UintegerValue(1400));

 NetDeviceContainer device;
 device=csma.Install(nodes);

 InternetStackHelper stack;
 stack.Install(nodes);

 Ipv4AddressHelper address;
 address.SetBase("10.1.1.0","255.255.255.0");

 Ipv4InterfaceContainer interface = address.Assign(device);

 UdpEchoServerHelper echoserver(9);
 
 ApplicationContainer serverapps=echoserver.Install(nodes.Get(1));

 serverapps.Start(Seconds(1.0));
 serverapps.Stop(Seconds(10.0));

 UdpEchoClientHelper echoclient(interface.GetAddress(1),9);

 echoclient.SetAttribute("MaxPackets",UintegerValue(1));
 echoclient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
 echoclient.SetAttribute("PacketSize",UintegerValue(1024));

 ApplicationContainer clientapps = echoclient.Install(nodes.Get(0));

 clientapps.Start(Seconds(1.0));
 clientapps.Stop(Seconds(10.0));
/*
 #if 0
 echoclient.SetFill(clientapps.Get(0),"Hello World");
 echocleint.SetFill(clientapps.Get(0),0xa5,1024);
 uint8_t fill={0,1,2,3,4,5,6};
 echoclient.SetFill(clientapps.Get(0),fill,sizeof(fill),1024);
 #endif
*/
 AnimationInterface anim("prav222.xml");

 Simulator::Run();
 Simulator::Destroy();

 return 0;
}
 

 
