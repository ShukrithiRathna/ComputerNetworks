#Create a simulator object
set ns [new Simulator]

#Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Define a 'finish' procedure
proc finish {} {
        global ns nf
        $ns flush-trace
	#Close the trace file
        close $nf
	#Execute nam on the trace file
        exec nam out.nam &
        exit 0
}



#Create new objects 
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Connect the two nodes
$ns duplex-link $n0 $n2 1Mb 10ms DropTail 
$ns duplex-link $n1 $n2 1Mb 10ms DropTail 
$ns duplex-link $n3 $n2 1Mb 10ms DropTail 
#bandwidth 1Megabit, delay - 10 ms queue DropTail

$ns duplex-link-op $n0 $n2 orient right-down      
$ns duplex-link-op $n1 $n2 orient right-up 
$ns duplex-link-op $n2 $n3 orient right 

#Data always sent from one agent to another
#Create a new UDP agent and attach it to node n0
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

#Create a CBR(constant bit rate) traffic generator and attach to agent
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$udp0 set class_ 1
$cbr0 attach-agent $udp0

#Create a UDP agent and attach it to node n1
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1

# Create a CBR traffic source and attach it to udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$udp1 set class_ 2
$cbr1 attach-agent $udp1

#create null agent to acts as traffic sink and attach to node n1
set null0 [new Agent/Null]
$ns attach-agent $n1 $null0
$ns duplex-link-op $n2 $n3 queuePos 0.5

#connect two agents
$ns connect $udp0 $null0
$ns connect $udp1 $null0

#when to start and stop sending data
$ns at 0.2 "$cbr0 start"
$ns at 1.0 "$cbr0 start"
$ns at 4.0 "$cbr0 stop"
$ns at 4.5 "$cbr0 stop"



#Call the finish procedure after 5 seconds simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run


