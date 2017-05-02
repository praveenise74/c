#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main(int argc,char *argv[])
{
 NodeContainer nodes;
 nodes.Create(2);
 
 PointToPointHelper p2p;
 p2p.SetDeviceAttribute("DataRate",StringValue("500Kbps"));
 p2p.SetChannelAttribute("Delay",StringValue("5ms"));

 NetDeviceContainer device;
 device=p2p.Install(nodes);

 InternetStackHelper stack;
 stack.Install(nodes);

 Ipv4AddressHelper addr;
 addr.SetBase("10.1.1.0","255.255.255.0");

 Ipv4InterfaceContainer interface = addr.Assign(device);

 BulkSendHelper source ("ns3::TcpSocketFactory",InetSocketAddress(interface.GetAddress(0),9));
 source.SetAttribute("MaxBytes",UintegerValue(0));
 
 ApplicationContainer sourceapps=source.Install(nodes.Get(1));
 sourceapps.Start(Seconds(0.0)) ;
 sourceapps.Stop(Seconds(10.0));

 PacketSinkHelper sink ("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),9));

 ApplicationContainer sinkapps = sink.Install(nodes.Get(0));
 sinkapps.Start(Seconds(0.0));
 sinkapps.Stop(Seconds(10.0));

 AnimationInterface anim("prav44.xml");
 anim.EnablePacketMetadata(true);

 Simulator::Run();
 Simulator::Destroy();

return 0;
}
