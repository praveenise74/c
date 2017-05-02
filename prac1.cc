#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

int main(int argc,char *argv[])
{

NodeContainer nodes;
nodes.Create(2);

PointToPointHelper p2p;
p2p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
p2p.SetChannelAttribute("Delay",StringValue("2ms"));

NetDeviceContainer device;
device=p2p.Install(nodes);

InternetStackHelper stack;
stack.Install(nodes);

Ipv4AddressHelper address;
address.SetBase("10.1.1.0","255.255.255.0");

Ipv4InterfaceContainer interface;	
interface=address.Assign(device);

UdpEchoServerHelper echoserver(9);
ApplicationContainer serverapps=echoserver.Install(nodes.Get(1));

serverapps.Start(Seconds(1.0));
serverapps.Stop(Seconds(10.0));

UdpEchoClientHelper echoclient(interface.GetAddress(1),9);
echoclient.SetAttribute("MaxPackets",UintegerValue(1));
echoclient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
echoclient.SetAttribute("PacketSize",UintegerValue(1024));

ApplicationContainer clientapps=echoclient.Install(nodes.Get(0));
clientapps.Start(Seconds(2.0));
clientapps.Stop(Seconds(10.0));

AnimationInterface anima("ex1.xml");

Simulator::Run();
Simulator::Destroy();
return 0;
}



