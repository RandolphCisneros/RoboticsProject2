/*
 * Robotics class project #2, part 2
 * Modified version of bumper.cc, which was initially written by Simon Parsons
 * Used to navigate a Roomba/Create around a maze
 * Group 5: Randolph Cisneros, Arsenii Lyzenko, Peggy Li, Osi Eastman
 */

#include <iostream>
#include <cstdlib>
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

int main(int argc, char *argv[])
{  	
	//set up proxies to talk to simulator & robot.
	PlayerClient robot("localhost");  
	BumperProxy bp(&robot,0);
	Position2dProxy pp(&robot,0);
	pp.SetMotorEnable(true);

	while(!(pp.GetXPos() < 0 && pp.GetYPos() > 10)
	{    
		double turnrate, speed;
		robot.Read();
	
     		if(bp[0] || bp[1] || pp.GetStall()) {
			//if the robot is stuck, random chance of going forwards or backwards
			if (pp.GetStall() && rand()%2 == 0)
				speed = 2.0;
			else speed = -1.0;
			
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
		pp.SetSpeed(speed, turnrate); //send turnrate & speed settings to robot
		
		//print out information about robot
		std::cout << "x: " << pp.GetXPos()  << std::endl;
      		std::cout << "y: " << pp.GetYPos()  << std::endl;
      		std::cout << "a: " << pp.GetYaw()  << std::endl;
      		std::cout << "Left  bumper: " << bp[0] << std::endl;
      		std::cout << "Right bumper: " << bp[1] << std::endl;
		std::cout << "Speed: " << speed << std::endl;      
      		std::cout << "Turn rate: " << turnrate << std::endl << std::endl;
	}
}
