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
	while(true) 
    {    
		double turnrate, speed;
		
		robot.Read();
      	std::cout << "x: " << pp.GetXPos()  << std::endl;
      	std::cout << "y: " << pp.GetYPos()  << std::endl;
      	std::cout << "a: " << pp.GetYaw()  << std::endl;
      	std::cout << "Left  bumper: " << bp[0] << std::endl;
      	std::cout << "Right bumper: " << bp[1] << std::endl;
      
		int turnCounter = 0;
	
     	if(bp[0] || bp[1]){
			speed=-1.0;
			// Left bumper
			if (bp[0] && !bp[1]) {  
				 turnrate=dtor(-30);  
			}
			//right bumper
			if (!bp[0] && bp[1]) {
				turnrate=dtor(70);
			}
			// Both
			if (bp[0] && bp[1]) {
				if(pp.GetYPos()<2.0){
					turnrate = dtor(70);
				}
				if(pp.GetYPos() < 6.0){
					turnrate = dtor(-70);
				}
				else if(pp.GetYPos() > 2.0 && pp.GetXPos() > 10.0){
					turnrate = dtor(70);
					if(pp.GetStall()){
						speed = -3.0;
					}
				} 
			}
		} 
		else {
			turnrate = 0;   
			speed=2.0;
		}     

      	std::cout << "Speed: " << speed << std::endl;      
      	std::cout << "Turn rate: " << turnrate << std::endl << std::endl;

		if(pp.GetXPos() > 10 && pp.GetYPos() < 2){
			turnrate = dtor(70);
		}
		if(pp.GetYPos() > 2 && pp.GetXPos() > 10){
			turnrate = dtor(50);
		}
		if(pp.GetYPos() > 2 && pp.GetYPos() < 6 && pp.GetXPos() < 2) {
			turnrate = dtor(-70);
		}
		if(pp.GetYPos() > 6 && pp.GetXPos() < 2){
			turnrate = dtor(-70);
		}
		if(pp.GetYPos() > 10 && pp.GetXPos() < 1){
			speed = 0;
			turnrate = dtor(0);
		}
		pp.SetSpeed(speed, turnrate);
	}
}
