#include "readIn.h"
#include <unistd.h>

/******************************
Plays Jungle on any button press
******************************/
int main(int argc, char *argv[]) {

  int button_l = 0; //GPIO pin
  int button_m = 4; //GPIO pin
  int button_r = 6; //GPIO pin
  
  puts("Button test beggining");
  setup_buttons();

  pinMode(button_l, INPUT); //left set to input to be read
  pinMode(button_m, INPUT); //middle set to input to be read
  pinMode(button_r, INPUT); //right set to input to be read

  int running = 1; 
  int playing = 0;
  
  while(running) {
    if(  digitalRead(button_l)
       ||digitalRead(button_m)
       ||digitalRead(button_r)) {

      pid_t pid;
      pid = fork(); //Create child process to run music

      if(pid < 0) {
        perror("failed fork"); //Couldn't create child process
	exit(-1);
      } else if (pid == 0) {
        //child process
        puts("child starts");
        system("omxplayer background_music.mp3");
	puts("playing song");
        return 0; //stop child process
      } else {
        //back to parent
        delay(500); // wait half a second

	while(! (digitalRead(button_l) 
	       ||digitalRead(button_m)
	       ||digitalRead(button_r))) {
	  //wait for button press
	}
        system("sudo killall omxplayer.bin"); //stop the song
	puts("killed"); //tell us we stoped the song
      }
    }
  }

  return 0;
}

void setup_buttons() {
  //Setup Library wiringPi
  if(wiringPiSetup()) {
    perror("wiringPi unable to setup");
    cleanup();
  }
}
