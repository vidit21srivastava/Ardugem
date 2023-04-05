#include <SPI.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include <string.h>

#define YELLOW 0xFFE0  
#define BLACK 0X0000
#define WHITE 0xFFFF
#define BLUE 0x201C
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF

const int name_offset_x = 8,
          name_offset_y = 8,
          line_spacing = 15,
          padding_x = 10;

// TFT_eSPI display = TFT_eSPI(); 

String coin_dat1[]= {"bitcoin","ethereum","tether","binancecoin","usd-coin","ripple","cardano","dogcoin"};

void infoScreen( DynamicJsonDocument doc, TFT_eSPI display, String name, int coin_index ){
    
    //displaying name of coin
    display.setCursor( name_offset_x, name_offset_y );
    display.setTextSize(2);
    display.setTextColor(CYAN,BLACK);
    display.print(name);


    //displaying price of coin
    display.setTextSize(1);

    display.setCursor( 54, name_offset_y + 2*line_spacing );
    display.setTextColor(WHITE,BLACK);
    float temp = doc[coin_dat1[coin_index]]["usd"];
    display.print((String)temp);

    //displaying change in last 24h
    
    display.setCursor( 66, name_offset_y + 3*line_spacing );
    temp = doc[coin_dat1[coin_index]]["usd_24h_change"];
    temp>=0 ? display.setTextColor(GREEN,BLACK) : display.setTextColor(RED,BLACK);
    display.print((String)temp+"%  ");
    
    //displaying market cap
    display.setCursor( padding_x, name_offset_y + 5*line_spacing );
    temp = doc[coin_dat1[coin_index]]["usd_market_cap"];
    display.setTextColor(WHITE,BLACK);
    display.print("$"+(String)temp);

    //displaying last 24hr volume
    display.setCursor( padding_x, name_offset_y + 7*line_spacing );
    temp = doc[coin_dat1[coin_index]]["usd_24h_vol"];
    display.print("$"+(String)temp);


}