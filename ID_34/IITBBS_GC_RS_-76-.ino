#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <math.h> 
#include <Wire.h>

#define TFT_CS        10
#define TFT_RST        7 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         9


//Set up some default colours
#define GROUNDCOLOR 0x00ff00
#define SKYCOLOR 0x0000ff




Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



int ADXL345 = 0x53;
int X_out, Y_out, Z_out;

//Flag to check is the player is in jump or not, to redce the mid-air velocity for changing direction
int upJump=0, downJump=0;


void setup(void) {
Serial.begin(9600);
	tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
	tft.setRotation(0); // set display orientation 
    tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);
	delay(100);

	Wire.begin();

	Wire.beginTransmission(ADXL345);
	Wire.write(0x2D); //talk to POWER_CTL Register - 0x2D
  
	Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
	Wire.endTransmission();
	delay(10);
	
	//off-set calibration
	Wire.beginTransmission(ADXL345);
	Wire.write(0x1E);
	Wire.write(-3);
	Wire.endTransmission();

	Wire.beginTransmission(ADXL345);
	Wire.write(0x1F);
	Wire.write(+3);
	Wire.endTransmission();
	
	Wire.beginTransmission(ADXL345);
	Wire.write(0x20);
	Wire.write(-74);
	Wire.endTransmission();

	uint8_t time = millis();

	tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);

	//This is the start screen
	bool start=0;
	print_text(10,40,"A WALK IN",2,0xff0000);
	print_text(5,60," THE PARK ",2,0xff0000);
	print_text(20,90,"Whip to start",1,0xff0000);
	while(!start){
		Wire.beginTransmission(ADXL345);
		Wire.write(0x32);
		Wire.endTransmission(false);
		Wire.requestFrom(ADXL345, 6, true);

		Y_out = ( Wire.read() | Wire.read() << 8);

		if(Y_out<-200){
			start=1;	//Wait for a whip to start
		}
	}

	tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);

}


//This is the center of the view, all objects will dynamically shift w.r.t this center
uint8_t center_x=64;
uint8_t center_y=64;

//Positions for the player object
uint8_t playerCenterG_y=90;
uint8_t playerCenter_x=64;

//Obstacle array, an obstacle can be either at the left, middle or right side.
uint8_t obstaclePositions_x[] = {-1,0,1};


//Score
String score = "0000";
uint8_t bonus = 0;	//Bonus on eating an orange



//this layer class contains all the components such as player, tree, puddle, orange, etc.
class Layer {
	
	public:
		uint8_t pos_z ;
		uint8_t horizonCenter_x;
		uint8_t horizonCenter_y;
		uint8_t puddleCenter_x;
		uint8_t puddleCenter_y;
		uint8_t treeCenter_x;
		uint8_t treeCenter_y;
		uint8_t playerCenter_x;
		uint8_t playerCenter_y;


		Layer(uint8_t pos_z)
		{
			//Since this is a 3D game, this will keep track of how far is the layer w.r.t. the player in the z-axis
			this->pos_z = pos_z;
		};
		
		//display the path
		 void displayLayer(){
			/* tft.drawRect(center_x-pos_z/2,center_y-pos_z/2,pos_z,pos_z,ST77XX_YELLOW); */
			this->horizonCenter_x = center_x;
			this->horizonCenter_y = center_y;
			tft.drawLine(horizonCenter_x-20,horizonCenter_y,horizonCenter_x-96,128,ST77XX_BLACK);
			tft.drawLine(horizonCenter_x+20,horizonCenter_y,horizonCenter_x+96,128,ST77XX_BLACK);
		}

		//Clear the path after each rendering frame
		void clearLayer(){
			/* tft.drawRect(center_x-pos_z/2,center_y-pos_z/2 ,pos_z,pos_z,ST77XX_GREEN); */
			tft.drawLine(horizonCenter_x-20,horizonCenter_y,horizonCenter_x-96,128,GROUNDCOLOR);
			tft.drawLine(horizonCenter_x+20,horizonCenter_y,horizonCenter_x+96,128,GROUNDCOLOR);
		}

		
		//Make a tree inside this particular layer 
		void displayTree(uint8_t i){
			this->treeCenter_x = center_x+obstaclePositions_x[i]*pos_z/2;
			this->treeCenter_y = center_y+pos_z/2;
			if(pos_z>30 && pos_z < 110){
				tft.fillTriangle(treeCenter_x,treeCenter_y-pos_z/2,treeCenter_x+pos_z/6,treeCenter_y,treeCenter_x-pos_z/6,treeCenter_y,0x210202);
				tft.fillRect(treeCenter_x-pos_z/20,treeCenter_y-3,pos_z/10,pos_z/4,0x000900);
			}

			if(treeCenter_x > 44  &&  treeCenter_x < 84 && treeCenter_y > 90){
				gameOver("  You hit a    tree!");
			}
		}
		
		//Delete the above made tree after every frame refresh
		void clearTree(uint8_t i){
			if(pos_z>30 && pos_z<110){
				tft.fillTriangle(treeCenter_x,treeCenter_y-pos_z/2,treeCenter_x+pos_z/6,treeCenter_y,treeCenter_x-pos_z/6,treeCenter_y,GROUNDCOLOR);
				tft.fillRect(treeCenter_x-pos_z/20,treeCenter_y-3,pos_z/10,pos_z/4,GROUNDCOLOR);
			}
		}

		
		//Make a puddle
		displayPuddle(uint8_t i){
			/* uint8_t puddleCenter_x = layerCenter_x+pos_z/2; */
			this->puddleCenter_x = center_x + obstaclePositions_x[i]*pos_z/2;
			this->puddleCenter_y = center_y+pos_z/2 + 5;
			this->playerCenter_y = playerCenterG_y;
			if(pos_z>30 && pos_z<105){
				tft.fillCircle(puddleCenter_x,puddleCenter_y,pos_z/7,ST77XX_BLUE);
				tft.fillCircle(puddleCenter_x,puddleCenter_y-pos_z/3,pos_z/20,0xFFA500);
			}

			//Check for collisions b/w the player and the pussle also check for contace b/w the orange and the player to obtain bonus points
			if(puddleCenter_x > 44  &&  puddleCenter_x < 84 && puddleCenter_y>95 ){
				if(puddleCenter_y>95 && playerCenter_y > 85){
					gameOver("You slipped in a puddle!");		//If you hit the puddle
				}else{
					bonus+=1;		//If you eat an orange
				}
			}
			

		}
		
		//Clear the above made puddle and orange after screen refresh
		void clearPuddle(uint8_t i){
			if(pos_z>30 && pos_z<110){
				tft.fillCircle(puddleCenter_x,puddleCenter_y,pos_z/7,GROUNDCOLOR);
				tft.fillCircle(puddleCenter_x,puddleCenter_y-pos_z/3,pos_z/20,GROUNDCOLOR);

				tft.fillRect(40,0,50,10,SKYCOLOR);
			}
		}

		
		//This will be the player at the center bottom of the screen
		void displayPlayer(){
			this->playerCenter_y = playerCenterG_y;
			tft.fillRect(54,playerCenter_y,20,25,ST77XX_RED);
			tft.fillCircle(64,playerCenter_y-6,8,ST77XX_BLACK);
			tft.fillRect(54,110,20,5,0X030303);
		}

		void clearPlayer(){
			tft.fillRect(54,playerCenter_y,20,25,GROUNDCOLOR);
			tft.fillCircle(64,playerCenter_y-6,8,GROUNDCOLOR);

		}

};

//Initailize 2 layers from the Layer class,
//These layers wihh contain all the obstacles and apples
Layer layer1(0);
Layer layer2(40);

Layer layers[] = {layer1,layer2};





void loop() {

	Wire.beginTransmission(ADXL345);
	Wire.write(0x32);
	Wire.endTransmission(false);
	Wire.requestFrom(ADXL345, 6, true);

	X_out = ( Wire.read() | Wire.read() << 8);
	Y_out = ( Wire.read() | Wire.read() << 8);
	

	if(upJump || downJump){
		X_out = X_out/3;		//Reduce sensitivity when the player is mid air
	}
	center_x -= X_out/10;		//Change pos of player w.r.t. the input from accelerometer
	center_x = min(center_x,118);
	center_x = max(center_x,10);


	center_y = 32-Y_out/10;			//Change pos of player w.r.t. the input from accelerometer
	center_y = min(center_y,64);
	center_y = max(center_y,32);

	if(Y_out<-200){
		upJump=1;		//If a jerk is given, set the upJump flag to 1 to indicate ro jimp
	}

	if(Y_out<-200 || upJump == 1 || downJump == 1){
		jump();		//Execute the jump function, ie. make the player move in y-axis
	}

	//The following loop takes care of rendering, deletion and re-rendering of all the components in the layer object
	for(uint8_t i=0; i<2; i++){
		layers[i].clearTree((5*i)%3);
		layers[i].clearPuddle((5*i+2)%3);
		layers[i].clearLayer();
		layers[i].clearPlayer();
		layers[i].pos_z = layers[i].pos_z + layers[i].pos_z/40 + 2;
		layers[i].pos_z =  layers[i].pos_z%120 ;
		layers[i].displayTree((5*i)%3);
		layers[i].displayPuddle((5*i+2)%3);
		layers[i].displayLayer();
		layers[i].displayPlayer();
	}

	manageHorizon();		//Dynamically manage the horizon level based on the holding position of the console
	
	score = String(millis()/1000 + bonus);		//Count the score and print the score on the screen
	char* scoreChar = score.c_str();
	tft.fillRect(0,0,100,20,SKYCOLOR);
	print_text(0,0,scoreChar,2,ST77XX_WHITE);
	
	delay(10);

}




void manageHorizon(){		//Dynamically manage horizon
	tft.fillRect(0,25,128,center_y-25,SKYCOLOR);
	tft.fillRect(0,center_y,128,65-center_y,GROUNDCOLOR);

}




void jump(){	//Make the player jump in horizontal direction
	if(playerCenterG_y<54 || downJump == 1){
		playerCenterG_y = playerCenterG_y + (playerCenterG_y - 44)/10 + 2;
		/* Serial.println(playerCenter_y); */
		if(playerCenterG_y > 90){
			playerCenterG_y = 90;
			downJump=0;
		}
	}else{
		playerCenterG_y = playerCenterG_y - (playerCenterG_y - 44)/10 - 2 ;
		if(playerCenterG_y<54){
			upJump=0;
			downJump=1;
		}
	}
}

void gameOver(String s){		//Game over screen 
	String s1 = s.substring(0,11);
	String s2 = s.substring(11);
	char* sC1 = s1.c_str();
	char* sC2 = s2.c_str();
	tft.fillRect(20,40,88,50,0xffff00);
	print_text(30,50,sC1,1,0xff0000);
	print_text(25,70,sC2,1,0xff0000);
	delay(2000);
	
	tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);
	delay(100);
	/* tft.fillRect(20,40,88,50,0xffff00); */
	print_text(35,50,"High Score",1,0xff0000);
	char* scoreChar = score.c_str();
	print_text(50,80,scoreChar,3,0xff0000);
	/* print_text(50,70,scoreChar,1,0xff0000); */
	delay(4000);

	tft.fillScreen(GROUNDCOLOR);
	tft.fillRect(0,0,128,32,SKYCOLOR);

	print_text(40,50,"Hit RESET",1,0xff0000);
	print_text(30,70,"To play again",1,0xff0000);
	while(true){
		continue;
	}
}



void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color) {		//print char* array to the screen
  tft.setCursor(x_pos, y_pos);
  tft.setTextSize(text_size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}



