#pragma once
#define num_of_dogs 6
#define num_of_coins 5 
#define RUNNING 1 
#define NOT_RUNNING 0

//SIZE
#define ITEMS_NR 3
#define ButtonSize 150
#define LogoSize_W 500
#define LogoSize_H 250
#define PLAYER_W 50
#define PLAYER_H 100
#define COIN_SIZE 50
#define MUL_SIZE 50
#define Enemy_W 398
#define Enemy_H 215
#define Enemy_WD 200
#define Enemy_HD 100 //Height Destination
//BENZI
#define max_coin_bands 10
#define min_coin_bands 0
#define max_dog_bands 5 
#define min_dog_bands 0

//speed
#define maxs 15 
#define mins 5

//SCREEN SETTINGS
#define SCREEN_W 1280
#define SCREEN_H 720
//#define COIN_BAND_VAL ((SCREEN_H-COIN_SIZE) / (max_coin_bands - min_coin_bands - 1))
constexpr unsigned int COIN_BAND_VAL = ((SCREEN_H - COIN_SIZE) / (max_coin_bands - min_coin_bands - 1));
//#define DOG_BAND_VAL ((SCREEN_H-Enemy_HD) / (max_dog_bands - min_dog_bands )) //+1 ca mereu trb sa ramana o banda libera
constexpr unsigned int DOG_BAND_VAL = ((SCREEN_H - Enemy_HD) / (max_dog_bands - min_dog_bands));

