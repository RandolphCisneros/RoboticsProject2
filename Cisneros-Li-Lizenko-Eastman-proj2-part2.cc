/*
 *  bumper.cc
 *  Sample code for a robot that has two front bumpers and uses them to avoid obstacles. Suitable for use with the Roomba and Create. 
 */

#include <iostream>
#include <cstdlib>
#include <libplayerc++/playerc++.h>

int main(int argc, char *argv[])
{  
	using namespace PlayerCc;  
	
	//Set up proxies. Proxies are the datastructures that Player uses to talk to the simulator and the real robot.
	PlayerClient    robot("localhost");  
	BumperProxy     bp(&robot,0);       // The bumper proxy reads from the bumpers.
	Position2dProxy pp(&robot,0);       // The 2D proxy reads odometry from the robot and sends motion commands.

	// Allow the program to take charge of the motors (take care now)
	pp.SetMotorEnable(true);

	// Control loop
	while(!(pp.GetXPos() < 0 && pp.GetYPos() > 10))
    {    
		double turnrate, speed;
		robot.Read();
	
     	if(bp[0] || bp[1] || pp.GetStall()){
			if (pp.GetStall() && rand()%2 == 0)
				speed = 2.0;
			else
				speed = -1.0;
			
			if (pp.GetXPos() > 12 || pp.GetYPos() < 0 || pp.GetYPos() > 12)
				turnrate = 3.14; //turn left
			else if (pp.GetXPos() < 0 || pp.GetYPos() < 4 || pp.GetYPos() > 8)
				turnrate = -3.14; //turn right
			else //middle area
				turnrate = 3.14; //turn left
		} 
		else {
			turnrate = 0;   
			speed = 2.0;
		}
		pp.SetSpeed(speed, turnrate);
		
		std::cout << "x: " << pp.GetXPos()  << std::endl;
      	std::cout << "y: " << pp.GetYPos()  << std::endl;
      	std::cout << "a: " << pp.GetYaw()  << std::endl;
      	std::cout << "Left  bumper: " << bp[0] << std::endl;
      	std::cout << "Right bumper: " << bp[1] << std::endl;
		std::cout << "Speed: " << speed << std::endl;      
      	std::cout << "Turn rate: " << turnrate << std::endl << std::endl;
	}
}
