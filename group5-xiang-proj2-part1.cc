/*
 * Robotics class project #2, part 1
 * Modified version of bumper.cc, which was initially written by Simon Parsons
 * Used to navigate a Roomba/Create around a oddly shaped object
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
	double turnrate, speed;
	double xPosStart = pp.GetXPos(), yPosStart = pp.GetYPos();
	bool quad4 = false;

  // Control loop
	while(!(quad4 && pp.GetYPos() < 1)) 
    {    
		robot.Read(); //read robot status
		if (pp.GetXPos() < 6 && pp.GetYPos() > 6)
			quad4 = true;
		
		if (bp[0] || bp[1] || pp.GetStall()) {//if robot hits something or is stuck
			//if the robot is stuck, random chance of going forwards or backwards
			if (pp.GetStall() && rand()%2 == 0)
				speed = 2.0;
			else speed = -1.0;
			
			if (pp.GetXPos() > 12 || pp.GetXPos() < 0) //if outside of x bounds
				turnrate = 3.14; //turn left
			else if (pp.GetYPos() > 12 || pp.GetYPos() < 0) //if outside of y bounds
				turnrate = 3.14; //turn left
			else //hit middle object
				turnrate = -3.14; //turn right
		} 
		else if (quad4 && pp.GetYaw() < 0) { //nearing end; direct robot to x = 0
			speed = 2;
			if (pp.GetXPos() > 0) {
				if (pp.GetYaw() > -2.36)
					turnrate = -3.14;
				else turnrate = 3.14;
			}
			else if (pp.GetXPos() < 0) {
				if (pp.GetYaw() < -.79)
					turnrate = 3.14;
				else turnrate = -3.14;
			}
			else turnrate = 0; //x = 0; go straight
		}
		else { //go straight
			turnrate = 0;
			speed = 2;
		}     
		pp.SetSpeed(speed, turnrate); //send turnrate & speed settings to robot
		
		//print out information about robot
		std::cout << "x: " << pp.GetXPos()  << std::endl;
      	std::cout << "y: " << pp.GetYPos()  << std::endl;
		std::cout << "a: " << pp.GetYaw()  << std::endl;
      	std::cout << "Bumpers: " << (bp[0] || bp[1]) << std::endl;
		std::cout << "Speed: " << speed << std::endl;      
      	std::cout << "Turn rate: " << turnrate << std::endl << std::endl;
    }
}
