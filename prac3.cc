#include "ns3/core-module.h"
#include "ns3/netanim-module.h"
//#include "ns3/wifi-module.h"
//#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"

using namespace ns3;

int main(int argc,char *argv[])
{
 NodeContainer p2pnode;
 p2pnode.Create(2);

 NodeContainer csmanode;
 csmanode.Add(p2pnode.Get(1));
 csmanode.Create(3);

 PointToPointHelper p2p;
 p2p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
 p2p.SetChannelAttribute("Delay",StringValue("2ms"));

 CsmaHelper csma;
 csma.SetChannelAttribute("DataRate",StringValue("100Mbps"));
 csma.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

 NetDeviceContainer p2pdevice;
 p2pdevice=p2p.Install(p2pnode);

 NetDeviceContainer csmadevice;
 csmadevice=csma.Install(csmanode);

 InternetStackHelper stack;
 stack.Install(p2pnode.Get(0));
 stack.Install(csmanode);

 Ipv4AddressHelper address;
 address.SetBase("10.1.1.0","255.255.255.0");
 
 Ipv4InterfaceContainer p2pinterface=address.Assign(p2pdevice);
 
 address.SetBase("10.1.2.0","255.255.255.0");

 Ipv4InterfaceContainer csmainterface = address.Assign(csmadevice);

 UdpEchoServerHelper echoserver(9);

 ApplicationContainer serverapps = echoserver.Install(csmanode.Get(3));

 serverapps.Start(Seconds(1.0));
 serverapps.Stop(Seconds(10.0));

 UdpEchoClientHelper echoclient(csmainterface.GetAddress(3),9);

 echoclient.SetAttribute("MaxPackets",UintegerValue(1));
 echoclient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
 echoclient.SetAttribute("PacketSize",UintegerValue(1024));

 ApplicationContainer clientapps = echoclient.Install(p2pnode.Get(0));
 clientapps.Start(Seconds(2.0));
 clientapps.Stop(Seconds(10.0));

 Ipv4GlobalRoutingHelper::PopulateRoutingTables();

 p2p.EnablePcapAll("second");
 csma.EnablePcap("second",csmadevice.Get(1),true);

 AnimationInterface anim("prav33.xml");
 Simulator::Run();
 Simulator::Destroy();
return 0;
}


 
 

 
