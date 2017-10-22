#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

enum GAME_STATE {INIT, READY, START, OVER, RUN, END_WP, END_GG}; // 狀態機設計!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct   GAME_DATA
{
    enum GAME_STATE   state;
    int block[4][4];
    bool blockTrue[4][4];
    int numCount;
    int highScore;                                                                                                                                            
	int tempHigh;

	int  temp[4][4];
	int  firstNum;
	int  secondNum;
	int  thirdNum;
	int  num1;
	int  num2;
	int  num3;
	int highestpoint;

	bool endGameGG;
	bool endGameWP;  
	bool horizontalEnd; 
	bool verticalEnd; 
	
	int control; //上下左右分別為1234

	FILE         *filePtr;

};

GAME_DATA   gameData;
GAME_DATA   *gameDataPtr = &gameData;

void refresh(void);
void randBlock(GAME_DATA *dataPtr);
int rand2or4(void);
int randPosition_1(void);
int randPosition_2(void);
void startGame(GAME_DATA *dataPtr);
void init(GAME_DATA *dataPtr);
void check(GAME_DATA *dataPtr);
void end_gg(GAME_DATA *dataPtr);
void end_wp(GAME_DATA *dataPtr);
void reset(GAME_DATA *dataPtr);
void upFunc(GAME_DATA *dataPtr);
void downFunc(GAME_DATA *dataPtr);
void leftFunc(GAME_DATA *dataPtr);
void rightFunc(GAME_DATA *dataPtr);
int returnPost_0_1(GAME_DATA *dataPtr);
int returnPost_1_1(GAME_DATA *dataPtr);
int returnPost_2_1(GAME_DATA *dataPtr);
int returnPost_3_1(GAME_DATA *dataPtr);
int returnPost_0_2(GAME_DATA *dataPtr);
int returnPost_1_2(GAME_DATA *dataPtr);
int returnPost_2_2(GAME_DATA *dataPtr);
int returnPost_3_2(GAME_DATA *dataPtr);
int returnPost_0_3(GAME_DATA *dataPtr);
int returnPost_1_3(GAME_DATA *dataPtr);
int returnPost_2_3(GAME_DATA *dataPtr);
int returnPost_3_3(GAME_DATA *dataPtr);
int returnPost_4_1(GAME_DATA *dataPtr);
int returnPost_5_1(GAME_DATA *dataPtr);
int returnPost_6_1(GAME_DATA *dataPtr);
int returnPost_7_1(GAME_DATA *dataPtr);
int returnPost_4_2(GAME_DATA *dataPtr);
int returnPost_5_2(GAME_DATA *dataPtr);
int returnPost_6_2(GAME_DATA *dataPtr);
int returnPost_7_2(GAME_DATA *dataPtr);
int returnPost_4_3(GAME_DATA *dataPtr);
int returnPost_5_3(GAME_DATA *dataPtr);
int returnPost_6_3(GAME_DATA *dataPtr);
int returnPost_7_3(GAME_DATA *dataPtr);

void readyFunc(GAME_DATA *dataPtr);
void overFunc_1(GAME_DATA *dataPtr);
void overFunc_2(GAME_DATA *dataPtr);


/***************************************************************************************************************/

namespace my2048 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
			

		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  playingBoard;
	private: System::Windows::Forms::Label^  block00;
	private: System::Windows::Forms::Label^  block01;
	private: System::Windows::Forms::Label^  block02;
	private: System::Windows::Forms::Label^  block03;
	private: System::Windows::Forms::Label^  block13;
	protected: 





	private: System::Windows::Forms::Label^  block12;

	private: System::Windows::Forms::Label^  block11;

	private: System::Windows::Forms::Label^  block10;
	private: System::Windows::Forms::Label^  block20;
	private: System::Windows::Forms::Label^  block21;
	private: System::Windows::Forms::Label^  block22;
	private: System::Windows::Forms::Label^  block23;
	private: System::Windows::Forms::Label^  block33;






	private: System::Windows::Forms::Label^  block32;

	private: System::Windows::Forms::Label^  block31;

	private: System::Windows::Forms::Label^  block30;

	private: System::Windows::Forms::Button^  newGame;
	private: System::Windows::Forms::Label^  score;
	private: System::Windows::Forms::Label^  bestScoreValue;
	private: System::Windows::Forms::Label^  bestScore;
	private: System::Windows::Forms::Label^  scoreValue;
	private: System::Windows::Forms::Button^  upBotton;
	private: System::Windows::Forms::Button^  leftButton;
	private: System::Windows::Forms::Button^  downButton;
	private: System::Windows::Forms::Button^  rightButton;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->playingBoard = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->block00 = (gcnew System::Windows::Forms::Label());
			this->block01 = (gcnew System::Windows::Forms::Label());
			this->block02 = (gcnew System::Windows::Forms::Label());
			this->block03 = (gcnew System::Windows::Forms::Label());
			this->block13 = (gcnew System::Windows::Forms::Label());
			this->block12 = (gcnew System::Windows::Forms::Label());
			this->block11 = (gcnew System::Windows::Forms::Label());
			this->block10 = (gcnew System::Windows::Forms::Label());
			this->block20 = (gcnew System::Windows::Forms::Label());
			this->block21 = (gcnew System::Windows::Forms::Label());
			this->block22 = (gcnew System::Windows::Forms::Label());
			this->block23 = (gcnew System::Windows::Forms::Label());
			this->block33 = (gcnew System::Windows::Forms::Label());
			this->block32 = (gcnew System::Windows::Forms::Label());
			this->block31 = (gcnew System::Windows::Forms::Label());
			this->block30 = (gcnew System::Windows::Forms::Label());
			this->newGame = (gcnew System::Windows::Forms::Button());
			this->score = (gcnew System::Windows::Forms::Label());
			this->bestScoreValue = (gcnew System::Windows::Forms::Label());
			this->bestScore = (gcnew System::Windows::Forms::Label());
			this->scoreValue = (gcnew System::Windows::Forms::Label());
			this->upBotton = (gcnew System::Windows::Forms::Button());
			this->leftButton = (gcnew System::Windows::Forms::Button());
			this->downButton = (gcnew System::Windows::Forms::Button());
			this->rightButton = (gcnew System::Windows::Forms::Button());
			this->playingBoard->SuspendLayout();
			this->SuspendLayout();
			// 
			// playingBoard
			// 
			this->playingBoard->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->playingBoard->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->playingBoard->ColumnCount = 4;
			this->playingBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->Controls->Add(this->block00, 0, 0);
			this->playingBoard->Controls->Add(this->block01, 1, 0);
			this->playingBoard->Controls->Add(this->block02, 2, 0);
			this->playingBoard->Controls->Add(this->block03, 3, 0);
			this->playingBoard->Controls->Add(this->block13, 3, 1);
			this->playingBoard->Controls->Add(this->block12, 2, 1);
			this->playingBoard->Controls->Add(this->block11, 1, 1);
			this->playingBoard->Controls->Add(this->block10, 0, 1);
			this->playingBoard->Controls->Add(this->block20, 0, 2);
			this->playingBoard->Controls->Add(this->block21, 1, 2);
			this->playingBoard->Controls->Add(this->block22, 2, 2);
			this->playingBoard->Controls->Add(this->block23, 3, 2);
			this->playingBoard->Controls->Add(this->block33, 3, 3);
			this->playingBoard->Controls->Add(this->block32, 2, 3);
			this->playingBoard->Controls->Add(this->block31, 1, 3);
			this->playingBoard->Controls->Add(this->block30, 0, 3);
			this->playingBoard->Location = System::Drawing::Point(13, 13);
			this->playingBoard->Name = L"playingBoard";
			this->playingBoard->RowCount = 4;
			this->playingBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->playingBoard->Size = System::Drawing::Size(450, 450);
			this->playingBoard->TabIndex = 0;
			// 
			// block00
			// 
			this->block00->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block00->Location = System::Drawing::Point(4, 1);
			this->block00->Name = L"block00";
			this->block00->Size = System::Drawing::Size(105, 111);
			this->block00->TabIndex = 0;
			this->block00->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block01
			// 
			this->block01->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block01->Location = System::Drawing::Point(116, 1);
			this->block01->Name = L"block01";
			this->block01->Size = System::Drawing::Size(105, 111);
			this->block01->TabIndex = 0;
			this->block01->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block02
			// 
			this->block02->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block02->Location = System::Drawing::Point(228, 1);
			this->block02->Name = L"block02";
			this->block02->Size = System::Drawing::Size(105, 111);
			this->block02->TabIndex = 0;
			this->block02->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block03
			// 
			this->block03->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block03->Location = System::Drawing::Point(340, 1);
			this->block03->Name = L"block03";
			this->block03->Size = System::Drawing::Size(105, 111);
			this->block03->TabIndex = 0;
			this->block03->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block13
			// 
			this->block13->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block13->Location = System::Drawing::Point(340, 113);
			this->block13->Name = L"block13";
			this->block13->Size = System::Drawing::Size(105, 111);
			this->block13->TabIndex = 0;
			this->block13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block12
			// 
			this->block12->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block12->Location = System::Drawing::Point(228, 113);
			this->block12->Name = L"block12";
			this->block12->Size = System::Drawing::Size(105, 111);
			this->block12->TabIndex = 0;
			this->block12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block11
			// 
			this->block11->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block11->Location = System::Drawing::Point(116, 113);
			this->block11->Name = L"block11";
			this->block11->Size = System::Drawing::Size(105, 111);
			this->block11->TabIndex = 0;
			this->block11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block10
			// 
			this->block10->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block10->Location = System::Drawing::Point(4, 113);
			this->block10->Name = L"block10";
			this->block10->Size = System::Drawing::Size(105, 111);
			this->block10->TabIndex = 0;
			this->block10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block20
			// 
			this->block20->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block20->Location = System::Drawing::Point(4, 225);
			this->block20->Name = L"block20";
			this->block20->Size = System::Drawing::Size(105, 111);
			this->block20->TabIndex = 0;
			this->block20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block21
			// 
			this->block21->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block21->Location = System::Drawing::Point(116, 225);
			this->block21->Name = L"block21";
			this->block21->Size = System::Drawing::Size(105, 111);
			this->block21->TabIndex = 0;
			this->block21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block22
			// 
			this->block22->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block22->Location = System::Drawing::Point(228, 225);
			this->block22->Name = L"block22";
			this->block22->Size = System::Drawing::Size(105, 111);
			this->block22->TabIndex = 0;
			this->block22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block23
			// 
			this->block23->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block23->Location = System::Drawing::Point(340, 225);
			this->block23->Name = L"block23";
			this->block23->Size = System::Drawing::Size(105, 111);
			this->block23->TabIndex = 0;
			this->block23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block33
			// 
			this->block33->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block33->Location = System::Drawing::Point(340, 337);
			this->block33->Name = L"block33";
			this->block33->Size = System::Drawing::Size(105, 111);
			this->block33->TabIndex = 0;
			this->block33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block32
			// 
			this->block32->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block32->Location = System::Drawing::Point(228, 337);
			this->block32->Name = L"block32";
			this->block32->Size = System::Drawing::Size(105, 111);
			this->block32->TabIndex = 0;
			this->block32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block31
			// 
			this->block31->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block31->Location = System::Drawing::Point(116, 337);
			this->block31->Name = L"block31";
			this->block31->Size = System::Drawing::Size(105, 111);
			this->block31->TabIndex = 0;
			this->block31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// block30
			// 
			this->block30->Font = (gcnew System::Drawing::Font(L"標楷體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->block30->Location = System::Drawing::Point(4, 337);
			this->block30->Name = L"block30";
			this->block30->Size = System::Drawing::Size(105, 111);
			this->block30->TabIndex = 0;
			this->block30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// newGame
			// 
			this->newGame->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->newGame->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->newGame->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->newGame->Location = System::Drawing::Point(489, 13);
			this->newGame->Name = L"newGame";
			this->newGame->Size = System::Drawing::Size(157, 76);
			this->newGame->TabIndex = 1;
			this->newGame->Text = L"New Game";
			this->newGame->UseVisualStyleBackColor = false;
			this->newGame->Click += gcnew System::EventHandler(this, &Form1::newGame_Click);
			this->newGame->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::newGame_KeyDown);
			// 
			// score
			// 
			this->score->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->score->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->score->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->score->Location = System::Drawing::Point(487, 142);
			this->score->Name = L"score";
			this->score->Size = System::Drawing::Size(100, 40);
			this->score->TabIndex = 2;
			this->score->Text = L"SCORE";
			this->score->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// bestScoreValue
			// 
			this->bestScoreValue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->bestScoreValue->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->bestScoreValue->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->bestScoreValue->Location = System::Drawing::Point(605, 211);
			this->bestScoreValue->Name = L"bestScoreValue";
			this->bestScoreValue->Size = System::Drawing::Size(100, 40);
			this->bestScoreValue->TabIndex = 2;
			this->bestScoreValue->Text = L"0";
			this->bestScoreValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->bestScoreValue->Click += gcnew System::EventHandler(this, &Form1::bestScoreValue_Click);
			// 
			// bestScore
			// 
			this->bestScore->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->bestScore->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->bestScore->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->bestScore->Location = System::Drawing::Point(487, 211);
			this->bestScore->Name = L"bestScore";
			this->bestScore->Size = System::Drawing::Size(100, 40);
			this->bestScore->TabIndex = 2;
			this->bestScore->Text = L"BEST";
			this->bestScore->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// scoreValue
			// 
			this->scoreValue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->scoreValue->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->scoreValue->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->scoreValue->Location = System::Drawing::Point(605, 142);
			this->scoreValue->Name = L"scoreValue";
			this->scoreValue->Size = System::Drawing::Size(100, 40);
			this->scoreValue->TabIndex = 2;
			this->scoreValue->Text = L"0";
			this->scoreValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// upBotton
			// 
			this->upBotton->Location = System::Drawing::Point(581, 287);
			this->upBotton->Name = L"upBotton";
			this->upBotton->Size = System::Drawing::Size(75, 50);
			this->upBotton->TabIndex = 3;
			this->upBotton->Text = L"W↑";
			this->upBotton->UseVisualStyleBackColor = true;
			this->upBotton->Click += gcnew System::EventHandler(this, &Form1::upBotton_Click);
			this->upBotton->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::upBotton_KeyDown);
			// 
			// leftButton
			// 
			this->leftButton->Location = System::Drawing::Point(500, 336);
			this->leftButton->Name = L"leftButton";
			this->leftButton->Size = System::Drawing::Size(75, 50);
			this->leftButton->TabIndex = 4;
			this->leftButton->Text = L"A←";
			this->leftButton->UseVisualStyleBackColor = true;
			this->leftButton->Click += gcnew System::EventHandler(this, &Form1::leftButton_Click);
			this->leftButton->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::leftButton_KeyDown);
			// 
			// downButton
			// 
			this->downButton->Location = System::Drawing::Point(581, 390);
			this->downButton->Name = L"downButton";
			this->downButton->Size = System::Drawing::Size(75, 50);
			this->downButton->TabIndex = 5;
			this->downButton->Text = L"S↓";
			this->downButton->UseVisualStyleBackColor = true;
			this->downButton->Click += gcnew System::EventHandler(this, &Form1::downButton_Click);
			this->downButton->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::downButton_KeyDown);
			// 
			// rightButton
			// 
			this->rightButton->Location = System::Drawing::Point(662, 336);
			this->rightButton->Name = L"rightButton";
			this->rightButton->Size = System::Drawing::Size(75, 50);
			this->rightButton->TabIndex = 6;
			this->rightButton->Text = L"D→";
			this->rightButton->UseVisualStyleBackColor = true;
			this->rightButton->Click += gcnew System::EventHandler(this, &Form1::rightButton_Click);
			this->rightButton->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::rightButton_KeyDown);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(763, 484);
			this->Controls->Add(this->rightButton);
			this->Controls->Add(this->downButton);
			this->Controls->Add(this->leftButton);
			this->Controls->Add(this->upBotton);
			this->Controls->Add(this->scoreValue);
			this->Controls->Add(this->bestScoreValue);
			this->Controls->Add(this->bestScore);
			this->Controls->Add(this->score);
			this->Controls->Add(this->newGame);
			this->Controls->Add(this->playingBoard);
			this->Name = L"Form1";
			this->Text = L"2048";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->playingBoard->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 
				 startGame(gameDataPtr);
			 }
/***************************************************************************************************************/
private: System::Void newGame_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 startGame(gameDataPtr);

				 gameDataPtr->tempHigh = 0;
				 refresh();

			 } // newGame click
private: System::Void newGame_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(e->KeyCode == Keys::A)
			 {
				leftFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::W)
			 {
				upFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::S)
			 {
				downFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::D)
			 {
				rightFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::Q)
			 {
				 gameDataPtr->block[0][0] = 2048;
				 gameDataPtr->tempHigh = 16888;
				 check(gameDataPtr);
				 refresh();
			 }
			 else if(e->KeyCode == Keys::G)
			 {
				 for(int i = 0; i<4;i++ )
				 {
					 for(int j = 0; j<4;j++)
					 {
						 gameDataPtr->block[i][j] = i + j + 1;
					 }
				 }
				 check(gameDataPtr);
				 refresh();
			 }

		 }
private: System::Void upBotton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 upFunc(gameDataPtr);
		 }
private: System::Void leftButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			leftFunc(gameDataPtr);
		 }
private: System::Void downButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 downFunc(gameDataPtr);
		 }
private: System::Void rightButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 rightFunc(gameDataPtr);
		 }
private: System::Void upBotton_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(e->KeyCode == Keys::A)
			 {
				leftFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::W)
			 {
				upFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::S)
			 {
				downFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::D)
			 {
				rightFunc(gameDataPtr);
			}
			 else if(e->KeyCode == Keys::Q)
			 {
				 gameDataPtr->block[0][0] = 2048;
				 gameDataPtr->tempHigh = 16888;
				 check(gameDataPtr);
				 refresh();
			 }
			 else if(e->KeyCode == Keys::G)
			 {
				 for(int i = 0; i<4;i++ )
				 {
					 for(int j = 0; j<4;j++)
					 {
						 gameDataPtr->block[i][j] = i + j + 1;
					 }
				 }
				 check(gameDataPtr);
				 refresh();
			 }
		 }
private: System::Void leftButton_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(e->KeyCode == Keys::A)
			 {
				leftFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::W)
			 {
				upFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::S)
			 {
				downFunc(gameDataPtr);
				}
			 else if(e->KeyCode == Keys::D)
			 {
				rightFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::Q)
			 {
				 gameDataPtr->block[0][0] = 2048;
				 gameDataPtr->tempHigh = 16888;
				 check(gameDataPtr);
				 refresh();
			 }
			 else if(e->KeyCode == Keys::G)
			 {
				 for(int i = 0; i<4;i++ )
				 {
					 for(int j = 0; j<4;j++)
					 {
						 gameDataPtr->block[i][j] = i + j + 1;
					 }
				 }
				 check(gameDataPtr);
				 refresh();
			 }
		 }
private: System::Void downButton_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(e->KeyCode == Keys::A)
			 {
				leftFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::W)
			 {
				upFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::S)
			 {
				downFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::D)
			 {
				rightFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::Q)
			 {
				 gameDataPtr->block[0][0] = 2048;
				 gameDataPtr->tempHigh = 16888;
				 check(gameDataPtr);
				 refresh();
			 }
			 else if(e->KeyCode == Keys::G)
			 {
				 for(int i = 0; i<4;i++ )
				 {
					 for(int j = 0; j<4;j++)
					 {
						 gameDataPtr->block[i][j] = i + j + 1;
					 }
				 }
				 check(gameDataPtr);
				 refresh();
			 }
		 }
private: System::Void rightButton_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(e->KeyCode == Keys::A)
			 {
				leftFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::W)
			 {
				upFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::S)
			 {
			 	downFunc(gameDataPtr);
			 }
			else if(e->KeyCode == Keys::D)
			 {
			 	rightFunc(gameDataPtr);
			 }
			 else if(e->KeyCode == Keys::Q)
			 {
				 gameDataPtr->block[0][0] = 2048;
				 gameDataPtr->tempHigh = 16888;
				 check(gameDataPtr);
				 refresh();
			 }
			else if(e->KeyCode == Keys::G)
			 {
				 for(int i = 0; i<4;i++ )
				 {
					 for(int j = 0; j<4;j++)
					 {
						 gameDataPtr->block[i][j] = i + j + 1;
					 }
				 }
				 check(gameDataPtr);
				 refresh();
			 }
		}
private: void refresh(void)
		 {
			 block00->Text = System::Convert::ToString(gameDataPtr->block[0][0]);
				block01->Text = System::Convert::ToString(gameDataPtr->block[0][1]);
				block02->Text = System::Convert::ToString(gameDataPtr->block[0][2]);
				block03->Text = System::Convert::ToString(gameDataPtr->block[0][3]);
				block10->Text = System::Convert::ToString(gameDataPtr->block[1][0]);
				block11->Text = System::Convert::ToString(gameDataPtr->block[1][1]);
				block12->Text = System::Convert::ToString(gameDataPtr->block[1][2]);
				block13->Text = System::Convert::ToString(gameDataPtr->block[1][3]);
				block20->Text = System::Convert::ToString(gameDataPtr->block[2][0]);
				block21->Text = System::Convert::ToString(gameDataPtr->block[2][1]);
				block22->Text = System::Convert::ToString(gameDataPtr->block[2][2]);
				block23->Text = System::Convert::ToString(gameDataPtr->block[2][3]);
				block30->Text = System::Convert::ToString(gameDataPtr->block[3][0]);
				block31->Text = System::Convert::ToString(gameDataPtr->block[3][1]);
				block32->Text = System::Convert::ToString(gameDataPtr->block[3][2]);
				block33->Text = System::Convert::ToString(gameDataPtr->block[3][3]);
				if(gameDataPtr->block[0][0] == 0)
					block00->Text = "";
				if(gameDataPtr->block[0][1] == 0)
					block01->Text = "";
				if(gameDataPtr->block[0][2] == 0)
					block02->Text = "";
				if(gameDataPtr->block[0][3] == 0)
					block03->Text = "";
				if(gameDataPtr->block[1][0] == 0)
					block10->Text = "";
				if(gameDataPtr->block[1][1] == 0)
					block11->Text = "";
				if(gameDataPtr->block[1][2] == 0)
					block12->Text = "";
				if(gameDataPtr->block[1][3] == 0)
					block13->Text = "";
				if(gameDataPtr->block[2][0] == 0)
					block20->Text = "";
				if(gameDataPtr->block[2][1] == 0)
					block21->Text = "";
				if(gameDataPtr->block[2][2] == 0)
					block22->Text = "";
				if(gameDataPtr->block[2][3] == 0)
					block23->Text = "";
				if(gameDataPtr->block[3][0] == 0)
					block30->Text = "";
				if(gameDataPtr->block[3][1] == 0)
					block31->Text = "";
				if(gameDataPtr->block[3][2] == 0)
					block32->Text = "";
				if(gameDataPtr->block[3][3] == 0)
					block33->Text = "";
				scoreValue->Text =  System::Convert::ToString(gameDataPtr->tempHigh);
				bestScoreValue->Text =  System::Convert::ToString(gameDataPtr->highestpoint);
		 }
private: void resetFunc(GAME_DATA *dataPtr)
		{
			return;
		}
private: int randPosition_1(void)
		{
			int a=0;
			srand(time(NULL));
			a = rand()%4;
			return a;
		}
private: int randPosition_2(void)
		{
			int a=0;
    
			a = rand()%4;
			return a;
    
		}
private: int rand2or4(void)
{
    int a = 0;
    srand(time(NULL));
    
    a = rand()%9;
    if(a == 0)
    {
        return 4;     
    }    
	else
	{
	    return 2;
	}
}
private: void randBlock(GAME_DATA *dataPtr)
{
    int a = 0;
    int b = 0;
    
	bool end = false;
	srand(time(NULL));

	
	while(end == false)
	{
    a = randPosition_1();
    b = randPosition_2();
	
	if(dataPtr->blockTrue[a][b]==false)
	{
    dataPtr->block[a][b] = rand2or4();
    dataPtr->blockTrue[a][b] = true;
	end = true;
	}
	}
	

	
}
private: void startGame(GAME_DATA *dataPtr)
{
   
	 char highpt[20] = {'\0'};
	 char *highestpointer = &highpt[20];
	

    if(gameDataPtr->filePtr==NULL)
	{
dataPtr->filePtr = fopen("..\\highestpoint.txt","r");

	 
	 //highestpoint = 
		 fgets( highpt , 20 ,dataPtr->filePtr );
	 //fclose(dataPtr->filePtr);
	 gameDataPtr-> highestpoint = atoi(highpt);

	 //dataPtr->filePtr = fopen("..\\highestpoint.txt","r");
		 //fgets( highestpointer , 20 ,dataPtr->filePtr );
	 fclose(dataPtr->filePtr);
	 gameDataPtr-> highestpoint = atoi(highpt);
	}
	
	 

	int a = 0;
	for(int i = 0;i<4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			dataPtr->block[i][j] = 0;
		}
	}
	for(int i = 0;i<4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			dataPtr->blockTrue[i][j] = false;
		}
	}
    while(a == 0)
    {
    dataPtr->numCount = 0;

    randBlock(dataPtr);
    randBlock(dataPtr);
    
    for(int i =0;i < 4 ; i++)
    {
		for(int j = 0;j < 4;j++)
		{
        if(dataPtr->blockTrue[i][j] == true)
            {
                dataPtr->numCount++;   
            }
		}
    }
    if(dataPtr->numCount == 2)
    {
        a = 1;                     
    }
    
    }
	refresh();
	

	return;
}
private: void init(GAME_DATA *dataPtr)
{
	//if (dataPtr->filePtr == NULL)
    //{
     //dataPtr->filePtr = fopen("highScore.txt","w");
    //}
    // 開完檔要讀檔,把最高分數讀入   若沒有寫0
	
	dataPtr->state = READY;

	return;
}
private: void check(GAME_DATA *dataPtr)
{
    dataPtr->endGameGG = false;
	dataPtr->endGameWP = false;
	dataPtr->horizontalEnd = false;
	dataPtr->verticalEnd = false;
	bool zero = false;
	int a=0;
	int b=0;
	int c=0;
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
		    if(dataPtr->block[i][j] == 2048)
			{
			    dataPtr->endGameWP = true;
				return;
			}
		}
	
	} // 檢查成功的與否
	for(int i = 0;i<4;i++)
	{
	    for(int j = 0;j<4;j++)
		{
		    if(dataPtr->block[i][j] == 0)
			{
				a++;
			}
		}
	}
	
	if(a<1)
	{
	    zero = true;
	}
	if(zero == true)
	{
	    for(int j = 0;j<4;j++)
		{
		for(int i=0;i<3;i++)
		{
		    if(dataPtr->block[i][j]!=dataPtr->block[i][j+1])
			{
			    b++;
			}
		}
		}	
	}

	if(zero == true)
	{
	    for(int i= 0;i<4;i++)
		{
		for(int j=0;j<3;j++)
		{
		    if(dataPtr->block[j][i]!=dataPtr->block[j+1][i])
			{
			    c++;
			}
		}
		}	
	}
	if(b>11)
	{
	    
		
		dataPtr->horizontalEnd = true;
	}
	if(c>11)
	{
		
		dataPtr->verticalEnd = true;
	}


	if((dataPtr->horizontalEnd == true)&&(dataPtr->verticalEnd == true))
	{
	    dataPtr->endGameGG = true;
	}
	

	
	
	

    return;
}
private: void end_gg(GAME_DATA *dataPtr) 
{
	//若分數大於讀入的最高分，則複寫

	MessageBox::Show("你好爛");
	
	if (gameDataPtr->highestpoint  >= gameDataPtr->tempHigh)
	 {
		 return  ;

	 }
	 else 
	 {
		 gameDataPtr-> highestpoint = gameDataPtr->tempHigh;
	 }
	dataPtr->filePtr  = fopen("..\\highestpoint.txt" , "w");//開一個新黨txt,w=write

	
	fprintf(dataPtr->filePtr , "%d" ,  gameDataPtr->highestpoint);

	fclose(dataPtr->filePtr);//記得要關檔
	//把最高分寫入檔案裡


	return;
}
private: void end_wp(GAME_DATA *dataPtr) 
{
	
	//若分數大於讀入的最高分，則複寫
	MessageBox::Show("太神啦~");
	if (gameDataPtr->highestpoint  >= gameDataPtr->tempHigh)
	 {
		 return  ;

	 }
	 else 
	 {
		 gameDataPtr-> highestpoint = gameDataPtr->tempHigh;
	 }
	dataPtr->filePtr  = fopen("..\\highestpoint.txt" , "w");//開一個新黨txt,w=write


	fprintf(dataPtr->filePtr , "%d" ,  gameDataPtr->highestpoint);

	fclose(dataPtr->filePtr);//記得要關檔
	//把最高分寫入檔案裡


	return;
}
private: void reset(GAME_DATA *dataPtr)
{
	for(int i = 0;i < 4;i++)
	{
	    for(int j = 0;i < 4;i++)
		{
		    dataPtr->block[i][j] = 0;
		}
	}
	dataPtr->state = INIT;
	return;
} 
private: void leftFunc(GAME_DATA  *dataPtr)
{
	int count = 0;
	int a;
	

	for(int i = 0; i<4; i++)
	{
		
		count = 0;
		for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
		for(int j = 0; j<4; j++)
		{
			if(gameDataPtr->block[i][j] != 0)
			{
				count++;
				gameDataPtr->blockTrue[i][j] = true;
			}
			
		}
		switch(count)
		{
			case 1:
				for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
				for(int n = 0; n<4; n++)
				{
					if(gameDataPtr->blockTrue[i][n] == true)
					{
						int temp = 0;
						temp = gameDataPtr->block[i][n];
						gameDataPtr->block[i][n] = 0;
						gameDataPtr->block[i][0] = temp;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->blockTrue[i][2] = false;
						gameDataPtr->blockTrue[i][3] = false;
					} //移動格子到最左邊
				}
				
				break;
			case 2: //case 2未完成
				
				
				
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					
					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_0_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_0_2(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_1_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_1_2(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_2_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_2_2(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_3_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_3_2(gameDataPtr);
							   break;
					 
					}


					

					gameDataPtr->num1 = gameDataPtr->temp[i][gameDataPtr->firstNum];
					gameDataPtr->num2 = gameDataPtr->temp[i][gameDataPtr->secondNum];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[i][0] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[i][1] = 0;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->block[i][2] = 0;
						gameDataPtr->blockTrue[i][2] = false;
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][0];
					}

					else
					{
					     gameDataPtr->block[i][0] = gameDataPtr->num1;
						 gameDataPtr->block[i][1] = gameDataPtr->num2;
						 gameDataPtr->block[i][2] = 0;
						 gameDataPtr->blockTrue[i][2] = false;
						 gameDataPtr->block[i][3] = 0;
						 gameDataPtr->blockTrue[i][3] = false;
					}
				break;
				
				
			case 3:
				
			
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_0_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_0_2(gameDataPtr);
							    gameDataPtr->thirdNum = returnPost_0_3(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_1_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_1_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_1_3(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_2_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_2_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_2_3(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_3_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_3_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_3_3(gameDataPtr);
							   break;
					 
					}

					gameDataPtr->num1 = gameDataPtr->temp[i][gameDataPtr->firstNum];
					gameDataPtr->num2 = gameDataPtr->temp[i][gameDataPtr->secondNum];
					gameDataPtr->num3 = gameDataPtr->temp[i][gameDataPtr->thirdNum];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[i][0] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[i][1] = gameDataPtr->num3;
						gameDataPtr->block[i][2] = 0;
						gameDataPtr->blockTrue[i][2] = false;
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][0];
					}

					else if(gameDataPtr->num2 == gameDataPtr->num3)
					{
					     gameDataPtr->block[i][0] = gameDataPtr->num1;
						 gameDataPtr->block[i][1] = (gameDataPtr->num2+gameDataPtr->num3);
						 gameDataPtr->block[i][2] = 0;
						 gameDataPtr->blockTrue[i][2] = false;
						 gameDataPtr->block[i][3] = 0;
						 gameDataPtr->blockTrue[i][3] = false;
						 gameDataPtr->tempHigh+=gameDataPtr->block[i][1];
					}
					else
					{
					    gameDataPtr->block[i][0] = gameDataPtr->num1;
						gameDataPtr->block[i][1] = gameDataPtr->num2;
						gameDataPtr->block[i][2] = gameDataPtr->num3;
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
					}
				
					break;

			case 4:
			
	
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					
					if(gameDataPtr->temp[i][0] == gameDataPtr->temp[i][1] && gameDataPtr->temp[i][2] == gameDataPtr->temp[i][3])
					{
					    gameDataPtr->block[i][0] = (gameDataPtr->temp[i][0]+gameDataPtr->temp[i][1]);
						gameDataPtr->block[i][1] = (gameDataPtr->temp[i][2]+gameDataPtr->temp[i][3]);
						gameDataPtr->block[i][2] = 0;
						gameDataPtr->blockTrue[i][2] = false;
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][0];
						gameDataPtr->tempHigh+=gameDataPtr->block[i][1];
					}

					else if(gameDataPtr->temp[i][0] == gameDataPtr->temp[i][1] && gameDataPtr->temp[i][2] != gameDataPtr->temp[i][3])
					{
					     gameDataPtr->block[i][0] = (gameDataPtr->temp[i][0]+gameDataPtr->temp[i][1]);
						 gameDataPtr->block[i][1] = gameDataPtr->temp[i][2];
						 gameDataPtr->block[i][2] = gameDataPtr->temp[i][3];
						 gameDataPtr->block[i][3] = 0;
						 gameDataPtr->blockTrue[i][3] = false;
						 gameDataPtr->tempHigh+=gameDataPtr->block[i][0];
					}
					else if(gameDataPtr->temp[i][1] == gameDataPtr->temp[i][2])
					{
					    gameDataPtr->block[i][0] = gameDataPtr->temp[i][0];
						gameDataPtr->block[i][1] = (gameDataPtr->temp[i][1]+gameDataPtr->temp[i][2]);
						gameDataPtr->block[i][2] = gameDataPtr->temp[i][3];
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][1];
					}
					else if(gameDataPtr->temp[i][2] == gameDataPtr->temp[i][3])
					{
					    gameDataPtr->block[i][0] = gameDataPtr->temp[i][0];
						gameDataPtr->block[i][1] = gameDataPtr->temp[i][1];
						gameDataPtr->block[i][2] = (gameDataPtr->temp[i][2]+gameDataPtr->temp[i][3]);
						gameDataPtr->block[i][3] = 0;
						gameDataPtr->blockTrue[i][3] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][2];
					}
			
				break;
				
		} 
	}
	
	a=0;

	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != gameDataPtr->temp[i][j])
			{
			    a++;
			}
			
		}
	}

	


	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != 0)
			{
			    gameDataPtr->blockTrue[i][j] = true;
			}
			else
			{
			    gameDataPtr->blockTrue[i][j] = false;
			}
		}
	}
	if(a==0)
	{
		overFunc_2(gameDataPtr);
	    refresh();
	    
	}
	else
	{
	
	overFunc_1(gameDataPtr);
	refresh();
	
	}
}
private: void rightFunc(GAME_DATA  *dataPtr)
{
	int count = 0;
	
	

	for(int i = 0; i<4; i++)
	{
		
		count = 0;
		for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
		for(int j = 0; j<4; j++)
		{
			if(gameDataPtr->block[i][j] != 0)
			{
				count++;
				gameDataPtr->blockTrue[i][j] = true;
			}
			
		}


		switch(count)
		{
		

			case 1:
				for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
				for(int n = 0; n<4; n++)
				{
					if(gameDataPtr->blockTrue[i][n] == true)
					{
						int temp = 0;
						temp = gameDataPtr->block[i][n];
						gameDataPtr->block[i][n] = 0;
						gameDataPtr->block[i][3] = temp;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->blockTrue[i][2] = false;
					} //移動格子到最左邊
				}
				
				break;
			case 2: //case 2未完成
				
				
				
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					
					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_0_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_0_2(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_1_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_1_2(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_2_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_2_2(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_3_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_3_2(gameDataPtr);
							   break;
					 
					}

					gameDataPtr->num1 = gameDataPtr->block[i][gameDataPtr->firstNum];
					gameDataPtr->num2 = gameDataPtr->block[i][gameDataPtr->secondNum];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = 0;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->block[i][2] = 0;
						gameDataPtr->blockTrue[i][2] = false;
						gameDataPtr->block[i][3] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->tempHigh+=gameDataPtr->block[i][3];
					}

					else
					{
					     gameDataPtr->block[i][0] = 0;
						 gameDataPtr->blockTrue[i][0] = false;
						 gameDataPtr->block[i][1] = 0;
						 gameDataPtr->blockTrue[i][1] = false;
						 gameDataPtr->block[i][2] = gameDataPtr->num1;
						 gameDataPtr->block[i][3] = gameDataPtr->num2;
					}
				break;
				
				
			case 3:
				
			
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_0_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_0_2(gameDataPtr);
							    gameDataPtr->thirdNum = returnPost_0_3(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_1_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_1_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_1_3(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_2_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_2_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_2_3(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_3_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_3_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_3_3(gameDataPtr);
							   break;
					 
					}

					gameDataPtr->num1 = gameDataPtr->temp[i][gameDataPtr->firstNum];
					gameDataPtr->num2 = gameDataPtr->temp[i][gameDataPtr->secondNum];
					gameDataPtr->num3 = gameDataPtr->temp[i][gameDataPtr->thirdNum];

				    if(gameDataPtr->num2 == gameDataPtr->num3)
					{
					     gameDataPtr->block[i][0] = 0;
						 gameDataPtr->blockTrue[i][0] = false;
						 gameDataPtr->block[i][1] = 0;
						 gameDataPtr->blockTrue[i][1] = false;
						 gameDataPtr->block[i][2] = gameDataPtr->num1;
						 gameDataPtr->block[i][3] = (gameDataPtr->num2+gameDataPtr->num3);
						 gameDataPtr->tempHigh+=gameDataPtr->block[i][3];
					}
					else if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = 0;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->block[i][2] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[i][3] = gameDataPtr->num3;
						gameDataPtr->tempHigh+=gameDataPtr->block[i][2];
					}

					
					else
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = gameDataPtr->num1;
						gameDataPtr->block[i][2] = gameDataPtr->num2;
						gameDataPtr->block[i][3] = gameDataPtr->num3;
					}
				
					break;

			case 4:
			
	
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[i][j] = gameDataPtr->block[i][j];
					}
					
					if(gameDataPtr->temp[i][0] == gameDataPtr->temp[i][1] && gameDataPtr->temp[i][2] == gameDataPtr->temp[i][3])
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = 0;
						gameDataPtr->blockTrue[i][1] = false;
						gameDataPtr->block[i][2] = (gameDataPtr->temp[i][0]+gameDataPtr->temp[i][1]);
						gameDataPtr->block[i][3] = (gameDataPtr->temp[i][2]+gameDataPtr->temp[i][3]);
						gameDataPtr->tempHigh+=gameDataPtr->block[i][2];
						gameDataPtr->tempHigh+=gameDataPtr->block[i][3];
					}

					else if(gameDataPtr->temp[i][0] != gameDataPtr->temp[i][1] && gameDataPtr->temp[i][2] == gameDataPtr->temp[i][3] )
					{
					     gameDataPtr->block[i][0] = 0;
						 gameDataPtr->blockTrue[i][0] = false;
						 gameDataPtr->block[i][1] = gameDataPtr->temp[i][0];
						 gameDataPtr->block[i][2] = gameDataPtr->temp[i][1];
						 gameDataPtr->block[i][3] = (gameDataPtr->temp[i][2]+gameDataPtr->temp[i][3]);
						 gameDataPtr->tempHigh+=gameDataPtr->block[i][3];
					}
					else if(gameDataPtr->temp[i][1] == gameDataPtr->temp[i][2])
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = gameDataPtr->temp[i][0];
						gameDataPtr->block[i][2] = (gameDataPtr->temp[i][1]+gameDataPtr->temp[i][2]);
						gameDataPtr->block[i][3] = gameDataPtr->temp[i][3];
						gameDataPtr->tempHigh+=gameDataPtr->block[i][2];
					}
					else if(gameDataPtr->temp[i][0] == gameDataPtr->temp[i][1])
					{
					    gameDataPtr->block[i][0] = 0;
						gameDataPtr->blockTrue[i][0] = false;
						gameDataPtr->block[i][1] = (gameDataPtr->temp[i][0]+gameDataPtr->temp[i][1]);
						gameDataPtr->block[i][2] = gameDataPtr->temp[i][2];
						gameDataPtr->block[i][3] = gameDataPtr->temp[i][3];
						gameDataPtr->tempHigh+=gameDataPtr->block[i][1];
					}
			
				break;
				
		} 
	
	}
	int a=0;

	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != gameDataPtr->temp[i][j])
			{
			    a++;
			}
			
		}
	}
	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != 0)
			{
			    gameDataPtr->blockTrue[i][j] = true;
			}
			else
			{
			    gameDataPtr->blockTrue[i][j] = false;
			}
		}
	}
	if(a==0)
	{
		overFunc_2(gameDataPtr);
	    refresh();
	    
	}
	else
	{
	
	overFunc_1(gameDataPtr);
	refresh();
	
	}
}
private: void upFunc(GAME_DATA  *dataPtr)
{
	int count = 0;
	
	

	for(int i = 0; i<4; i++)
	{
		
		count = 0;
		for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
		for(int j = 0; j<4; j++)
		{
			if(gameDataPtr->block[j][i] != 0)
			{
				count++;
				gameDataPtr->blockTrue[j][i] = true;
			}
			
		}
		switch(count)
		{
			case 1:
				for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
				
				for(int n = 0; n<4; n++)
				{
					if(gameDataPtr->blockTrue[n][i] == true)
					{
						int temp = 0;
						temp = gameDataPtr->block[n][i];
						gameDataPtr->block[n][i] = 0;
						gameDataPtr->block[0][i] = temp; 
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->blockTrue[2][i] = false;
						gameDataPtr->blockTrue[1][i] = false;
					} //移動格子到最左邊
				}
				
				break;
			case 2: //case 2未完成
				
				
				
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_4_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_4_2(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_5_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_5_2(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_6_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_6_2(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_7_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_7_2(gameDataPtr);
							   break;
					 
					}

					gameDataPtr->num1 = gameDataPtr->temp[gameDataPtr->firstNum][i];
					gameDataPtr->num2 = gameDataPtr->temp[gameDataPtr->secondNum][i];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[0][i] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[1][i] = 0;
						gameDataPtr->blockTrue[1][i] = false;
						gameDataPtr->block[2][i] = 0;
						gameDataPtr->blockTrue[2][i] = false;
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[0][i];
					}

					else
					{
					     gameDataPtr->block[0][i] = gameDataPtr->num1;
						 gameDataPtr->block[1][i] = gameDataPtr->num2;
						 gameDataPtr->block[2][i] = 0;
						 gameDataPtr->blockTrue[2][i] = false;
						 gameDataPtr->block[3][i] = 0;
						 gameDataPtr->blockTrue[3][i] = false;
					}
				break;
				
				
			case 3:
				
			
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_4_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_4_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_4_3(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_5_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_5_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_5_3(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_6_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_6_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_6_3(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_7_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_7_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_7_3(gameDataPtr);
							   break;
					}

					gameDataPtr->num1 = gameDataPtr->temp[gameDataPtr->firstNum][i];
					gameDataPtr->num2 = gameDataPtr->temp[gameDataPtr->secondNum][i];
					gameDataPtr->num3 = gameDataPtr->temp[gameDataPtr->thirdNum][i];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[0][i] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[1][i] = gameDataPtr->num3;
						gameDataPtr->block[2][i] = 0;
						gameDataPtr->blockTrue[2][i] = false;
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[0][i];
					}

					else if(gameDataPtr->num2 == gameDataPtr->num3)
					{
					     gameDataPtr->block[0][i] = gameDataPtr->num1;
						 gameDataPtr->block[1][i] = (gameDataPtr->num2+gameDataPtr->num3);
						 gameDataPtr->block[2][i] = 0;
						 gameDataPtr->blockTrue[2][i] = false;
						 gameDataPtr->block[3][i] = 0;
						 gameDataPtr->blockTrue[3][i] = false;
						 gameDataPtr->tempHigh+=gameDataPtr->block[1][i];
					}
					else
					{
					    gameDataPtr->block[0][i] = gameDataPtr->num1;
						gameDataPtr->block[1][i] = gameDataPtr->num2;
						gameDataPtr->block[2][i] = gameDataPtr->num3;
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
					}
				
					break;

			case 4:
			
	
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					
					if(gameDataPtr->temp[0][i] == gameDataPtr->temp[1][i] && gameDataPtr->temp[2][i] == gameDataPtr->temp[3][i])
					{
					    gameDataPtr->block[0][i] = (gameDataPtr->temp[0][i]+gameDataPtr->temp[1][i]);
						gameDataPtr->block[1][i] = (gameDataPtr->temp[2][i]+gameDataPtr->temp[3][i]);
						gameDataPtr->block[2][i] = 0;
						gameDataPtr->blockTrue[2][i] = false;
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[0][i];
						gameDataPtr->tempHigh+=gameDataPtr->block[1][i];
					}

					else if(gameDataPtr->temp[0][i] == gameDataPtr->temp[1][i] && gameDataPtr->temp[2][i] != gameDataPtr->temp[3][i])
					{
					     gameDataPtr->block[0][i] = (gameDataPtr->temp[0][i]+gameDataPtr->temp[1][i]);
						 gameDataPtr->block[1][i] = gameDataPtr->temp[2][i];
						 gameDataPtr->block[2][i] = gameDataPtr->temp[3][i];
						 gameDataPtr->block[3][i] = 0;
						 gameDataPtr->blockTrue[3][i] = false;
						 gameDataPtr->tempHigh+=gameDataPtr->block[0][i];
					}
					else if(gameDataPtr->temp[1][i] == gameDataPtr->temp[2][i])
					{
					    gameDataPtr->block[0][i] = gameDataPtr->temp[0][i];
						gameDataPtr->block[1][i] = (gameDataPtr->temp[1][i]+gameDataPtr->temp[2][i]);
						gameDataPtr->block[2][i] = gameDataPtr->temp[3][i];
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[1][i];
					}
					else if(gameDataPtr->temp[2][i] == gameDataPtr->temp[3][i])
					{
					    gameDataPtr->block[0][i] = gameDataPtr->temp[0][i];
						gameDataPtr->block[1][i] = gameDataPtr->temp[1][i];
						gameDataPtr->block[2][i] = (gameDataPtr->temp[2][i]+gameDataPtr->temp[3][i]);
						gameDataPtr->block[3][i] = 0;
						gameDataPtr->blockTrue[3][i] = false;
						gameDataPtr->tempHigh+=gameDataPtr->block[2][i];
					}
			
				break;
				
		} 
	
	}
	int a=0;

	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != gameDataPtr->temp[i][j])
			{
			    a++;
			}
			
		}
	}
	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != 0)
			{
			    gameDataPtr->blockTrue[i][j] = true;
			}
			else
			{
			    gameDataPtr->blockTrue[i][j] = false;
			}
		}
	}
	if(a==0)
	{
		overFunc_2(gameDataPtr);
	    refresh();
	    
	}
	else
	{
	
	overFunc_1(gameDataPtr);
	refresh();
	
	}
}
private: void downFunc(GAME_DATA  *dataPtr)
{
	int count = 0;
	
	

	for(int i = 0; i<4; i++)
	{
		
		count = 0;
		for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
		for(int j = 0; j<4; j++)
		{
			if(gameDataPtr->block[j][i] != 0)
			{
				count++;
				gameDataPtr->blockTrue[j][i] = true;
			}
			
		}
		switch(count)
		{
			case 1:
				for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}

				for(int n = 0; n<4; n++)
				{
					if(gameDataPtr->blockTrue[n][i] == true)
					{
						int temp = 0;
						temp = gameDataPtr->block[n][i];
						gameDataPtr->block[n][i] = 0;
						gameDataPtr->block[3][i] = temp; 
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->blockTrue[1][i] = false;
						gameDataPtr->blockTrue[2][i] = false;
					} //移動格子到最左邊
				}
				
				break;
			case 2: //case 2未完成
				
				
				
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_4_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_4_2(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_5_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_5_2(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_6_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_6_2(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_7_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_7_2(gameDataPtr);
							   break;
					 
					}

					gameDataPtr->num1 = gameDataPtr->temp[gameDataPtr->firstNum][i];
					gameDataPtr->num2 = gameDataPtr->temp[gameDataPtr->secondNum][i];

					if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = 0;
						gameDataPtr->blockTrue[1][i] = false;
						gameDataPtr->block[2][i] = 0;
						gameDataPtr->blockTrue[2][i] = false;
						gameDataPtr->block[3][i] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->tempHigh+=gameDataPtr->block[3][i];
					}

					else
					{
					     gameDataPtr->block[0][i] = 0;
						 gameDataPtr->blockTrue[0][i] = false;
						 gameDataPtr->block[1][i] = 0;
						 gameDataPtr->blockTrue[1][i] = false;
						 gameDataPtr->block[2][i] = gameDataPtr->num1;
						 gameDataPtr->block[3][i] = gameDataPtr->num2;
					}
				break;
				
				
			case 3:
				
			
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					

					switch(i)
					{  
					    case 0: 
					           gameDataPtr->firstNum = returnPost_4_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_4_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_4_3(gameDataPtr);
							   break;
						case 1: 
					           gameDataPtr->firstNum = returnPost_5_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_5_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_5_3(gameDataPtr);
							   break;
					    case 2: 
					           gameDataPtr->firstNum = returnPost_6_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_6_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_6_3(gameDataPtr);
							   break;
					    case 3: 
					           gameDataPtr->firstNum = returnPost_7_1(gameDataPtr);
					           gameDataPtr->secondNum = returnPost_7_2(gameDataPtr);
							   gameDataPtr->thirdNum = returnPost_7_3(gameDataPtr);
							   break;
					}

					gameDataPtr->num1 = gameDataPtr->temp[gameDataPtr->firstNum][i];
					gameDataPtr->num2 = gameDataPtr->temp[gameDataPtr->secondNum][i];
					gameDataPtr->num3 = gameDataPtr->temp[gameDataPtr->thirdNum][i];

				    if(gameDataPtr->num2 == gameDataPtr->num3)
					{
					     gameDataPtr->block[0][i] = 0;
						 gameDataPtr->blockTrue[0][i] = false;
						 gameDataPtr->block[1][i] = 0;
						 gameDataPtr->blockTrue[1][i] = false;
						 gameDataPtr->block[2][i] = gameDataPtr->num1;
						 gameDataPtr->block[3][i] = (gameDataPtr->num2+gameDataPtr->num3);
						 gameDataPtr->tempHigh+=gameDataPtr->block[3][i];
					}
					else if(gameDataPtr->num1 == gameDataPtr->num2)
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = 0;
						gameDataPtr->blockTrue[1][i] = false;
						gameDataPtr->block[2][i] = (gameDataPtr->num1+gameDataPtr->num2);
						gameDataPtr->block[3][i] = gameDataPtr->num3;
						gameDataPtr->tempHigh+=gameDataPtr->block[2][i];
					}

					
					else
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = gameDataPtr->num1;
						gameDataPtr->block[2][i] = gameDataPtr->num2;
						gameDataPtr->block[3][i] = gameDataPtr->num3;
					}
				
					break;

			case 4:
			
	
					for(int j = 0;j<4;j++)
					{
					    gameDataPtr->temp[j][i] = gameDataPtr->block[j][i];
					}
					
					if(gameDataPtr->temp[0][i] == gameDataPtr->temp[1][i] && gameDataPtr->temp[2][i] == gameDataPtr->temp[3][i])
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = 0;
						gameDataPtr->blockTrue[1][i] = false;
						gameDataPtr->block[2][i] = (gameDataPtr->temp[0][i]+gameDataPtr->temp[1][i]);
						gameDataPtr->block[3][i] = (gameDataPtr->temp[2][i]+gameDataPtr->temp[3][i]);
						gameDataPtr->tempHigh+=gameDataPtr->block[2][i];
						gameDataPtr->tempHigh+=gameDataPtr->block[3][i];
					}

					else if(gameDataPtr->temp[0][i] != gameDataPtr->temp[1][i] && gameDataPtr->temp[2][i] == gameDataPtr->temp[3][i] )
					{
					     gameDataPtr->block[0][i] = 0;
						 gameDataPtr->blockTrue[0][i] = false;
						 gameDataPtr->block[1][i] = gameDataPtr->temp[0][i];
						 gameDataPtr->block[2][i] = gameDataPtr->temp[1][i];
						 gameDataPtr->block[3][i] = (gameDataPtr->temp[2][i]+gameDataPtr->temp[3][i]);
						 gameDataPtr->tempHigh+=gameDataPtr->block[3][i];
					}
					else if(gameDataPtr->temp[1][i] == gameDataPtr->temp[2][i])
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = gameDataPtr->temp[0][i];
						gameDataPtr->block[2][i] = (gameDataPtr->temp[1][i]+gameDataPtr->temp[2][i]);
						gameDataPtr->block[3][i] = gameDataPtr->temp[3][i];
						gameDataPtr->tempHigh+=gameDataPtr->block[2][i];
					}
					else if(gameDataPtr->temp[0][i] == gameDataPtr->temp[1][i])
					{
					    gameDataPtr->block[0][i] = 0;
						gameDataPtr->blockTrue[0][i] = false;
						gameDataPtr->block[1][i] = (gameDataPtr->temp[0][i]+gameDataPtr->temp[1][i]);
						gameDataPtr->block[2][i] = gameDataPtr->temp[2][i];
						gameDataPtr->block[3][i] = gameDataPtr->temp[3][i];
						gameDataPtr->tempHigh+=gameDataPtr->block[1][i];
					}
			
				break;
				
		} 
	
	}
	int a=0;

	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != gameDataPtr->temp[i][j])
			{
			    a++;
			}
			
		}
	}
	for(int i = 0;i<4;i++)
	{
	    for(int j=0;j<4;j++)
		{
		    if(gameDataPtr->block[i][j] != 0)
			{
			    gameDataPtr->blockTrue[i][j] = true;
			}
			else
			{
			    gameDataPtr->blockTrue[i][j] = false;
			}
		}
	}
	if(a==0)
	{
		overFunc_2(gameDataPtr);
	    refresh();
	    
	}
	else
	{
	
	overFunc_1(gameDataPtr);
	refresh();
	
	}
}
private: int returnPost_0_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[0][i]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_1_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[1][i]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_2_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[2][i]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}

private: int returnPost_3_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[3][i]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_0_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[0][i]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
		 private: int returnPost_1_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[1][i]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
				  private: int returnPost_2_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[2][i]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_3_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[3][i]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_0_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[0][i]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
		 private: int returnPost_1_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[1][i]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_2_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[2][i]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}

		 private: int returnPost_3_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[3][i]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_4_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[i][0]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
		 private: int returnPost_5_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[i][1]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_6_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[i][2]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}

private: int returnPost_7_1(GAME_DATA *dataPtr) //回傳第1個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 2 || i<4)
	{
	    if(dataPtr->block[i][3]!=0)
		{
		    count++;
		}
	    if (count == 1)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_4_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[i][0]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
		 private: int returnPost_5_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[i][1]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
				  private: int returnPost_6_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[i][2]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_7_2(GAME_DATA *dataPtr) //回傳第2個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 3 || i<4)
	{
	    if(dataPtr->block[i][3]!=0)
		{
		    count++;
		}
	    if (count == 2)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_4_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[i][0]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
		 private: int returnPost_5_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[i][1]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: int returnPost_6_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[i][2]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}

		 private: int returnPost_7_3(GAME_DATA *dataPtr) //回傳第3個有值格子的位置
{
   int count=0;
   int i = 0;

	
	while(count < 4 || i<4)
	{
	    if(dataPtr->block[i][3]!=0)
		{
		    count++;
		}
	    if (count == 3)
		{	
			
			return i;
		}
		i++;
	}
	
}
private: void readyFunc(GAME_DATA *dataPtr)
{
	switch(dataPtr->control)
	{
	case 1:
			upFunc(dataPtr);
			break;
		case 2:
			downFunc(dataPtr);
			break;
		case 3:
			leftFunc(dataPtr);
			break;
		case 4:
			rightFunc(dataPtr);
			break;
		default :
			break;
	}
			
//	overFunc(gameDataPtr);
    dataPtr->state = OVER;


	return;

}
private: void overFunc_1(GAME_DATA *dataPtr)
{
    check(dataPtr);
	
    if(dataPtr->endGameGG == true)
	{
	    end_gg(dataPtr);
	}
	else if(dataPtr->endGameWP == true)
	{
	    end_wp(dataPtr);
	}
	else
	{
	randBlock(gameDataPtr);

	dataPtr->state = READY;
	}
	return;
}

private: void overFunc_2(GAME_DATA *dataPtr)
{
    check(dataPtr);
	
    if(dataPtr->endGameGG == true)
	{
	    end_gg(dataPtr);
	}
	else if(dataPtr->endGameWP == true)
	{
	    end_wp(dataPtr);
	}
	else
	{
	

	dataPtr->state = READY;
	}
	return;
}




	
private: System::Void bestScoreValue_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
	}
	/***************************************************************************************************************/
	
	

/***************************************************************************************************************/