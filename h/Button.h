#pragma once
#include	"GameObject.h"
#include	"Box.h"

//class ButtonInput : public Box {
//protected:
//	ButtonInput() : Box(){}
//	ButtonInput(const ButtonInput& input) : Box(input){}
//
//	virtual ~ButtonInput(){}
//
//	void operator=(const ButtonInput& other) { Box::operator=(other); }
//};
//
//class ButtonStand : public ButtonInput {
//protected:
//	ButtonStand() : ButtonInput(){}
//	ButtonStand(const ButtonStand& stand) : ButtonInput(stand){}
//
//	virtual ~ButtonStand(){}
//
//	void operator=(const ButtonStand& other) { ButtonInput::operator=(other); }
//};

class Button : public Box{
public:
	Button(){}
	Button(const Box& box) : Box(box){}
	Button(const Button& other) : Box(other){}

	void operator=(const Button& other) { if (this != &other) { Box::operator=(other); } }

	virtual ~Button(){}
};

//const int IMAGESIZE = 2; 
//const int SOUNDSIZE = 1; 
//const int VIDEOSIZE = 1; 
//const int DATASIZE = 3; 
//
//enum {
//	IMAGE, SOUND, VIDEO
//};
//
//enum {
//	Switch1, Switch2,DICE_1, DICE_2, DICE_3, DICE_4, DICE_5, DICE_6, DICE_7,DICE_8,DICE_9,BOXING_1,BOXING_2,BOXING_3,
//	BOXING_4,BOXING_5,LEMON_1, LEMON_2, LEMON_3, LEMON_4, LEMON_5, LEMON_6, LEMON_7, LEMON_8,WATER_1, WATER_2, WATER_3,
//	ELECTRICITY_1, ELECTRICITY_2, ELECTRICITY_3, ELECTRICITY_4,BOOSE_1, BOOSE_2, BOOSE_3, BOOSE_4, BOOSE_5, BOOSE_6, BOOSE_7,
//	BOOSE_8, BOOSE_9, BOOSE_10
//};
//
////enum {
////	RORIGAMI
////};
//
//enum {
	//EXPROSSION
//};
//
//class GraphicData {
//public:
//	int** data;
//
//	IntVector2* imagePos;
//	IntVector2* imageSize;
//	DoubleVector2* imageScale;
//
//	IntVector2* soundPos;
//
//	IntVector2* videoPos;
//	IntVector2* videoSize;
//
//	GraphicData(const char** imageFile,const char** soundFile,const char** videoFile,int dynamicAllocation);
//	~GraphicData();
//	void Reassignment(int dynamicAllocation);
//	void Reset(int dynamicAllocation);
//
//private:
//	void SetGraph(const char** imageFile, const char** soundFile, const char** videoFile, int dynamicAllocation);
//
//	void SetImagePos();
//	void SetSoundPos();
//	void SetVideoPos();
//
//	void ErrorCheck(const char** imageFile, const char** soundFile, const char** videoFile);
//	void Error(const int* save, const char** imageFile, const char** soundFile, const char** videoFile);
//};
//
//enum Stage{
//	STAGE_1,STAGE_2,STAGE_3,STAGE_4
//};
//
//enum FLAG{
//	CLEAR,EXPROSSIONFLAG,DICEFLAG,BOXINGFLAG,LEMONFLAG,WATERFLAG,ELECTRICITYFLAG,BOOSEFLAG
//}; //左から順に、ステージクリア・爆発・1d3D(ダイスを1回振り、ハートが1～3個減る)・ボクシンググローブが当たる・レモンを食べる・
//   //上から滝のように水が降る・体全体に静電気・スピリタスを飲む・
//
//class Game {
//public:
//	Stage stage;
//
//	Game();
//	~Game();
//	void Start(const GraphicData& graphic);
//
//private:
//	int start;
//	int mouse;
//
//	int* limit;
//
//	bool** mouseFlag;
//	bool* iventFlag;
//
//	IntVector2 mousePos;
//
//	void Reassignment();
//	FLAG Judge();
//
//	void Exprossion(const GraphicData& graphic);
//	void Dice();
//	void Boxing();
//	void Lemon();
//	void Water();
//	void Electricity();
//	void Boose();
//
//	void SwitchDraw(const GraphicData& graphic);
//	void ExprossionDraw(const GraphicData& graphic);
//};