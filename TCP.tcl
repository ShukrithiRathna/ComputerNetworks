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
set tcp0 [new Agent/TCP]
$tcp0 set class_ 2
$ns attach-agent $n0 $tcp0
#Create a new TCP agent and attach it to node n1
set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
$ns attach-agent $n3 $tcp1

$ns duplex-link-op $n2 $n3 queuePos 0.5

#create null agent to acts as traffic sink and attach to node n1
set null0 [new Agent/Null]
$ns attach-agent $n1 $null0


#connect two agents
$ns connect $tcp0 $null0

$tcp0 set fid_ 1

# Set a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp0
$ftp set type_ FTP

#When to start and stop sending data
$ns at 0.2 "$ftp start"
$ns at 4.5 "$ftp stop"

#Call the finish procedure after 5 seconds simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run


