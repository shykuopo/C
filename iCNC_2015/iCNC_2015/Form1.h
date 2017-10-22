#pragma once
#include <math.h>
#include <string.h>
#include <Windows.h>
#include"../CNC/INC/cnc.h"
#include "../MMI/INC/mmi.h"
#include"../LINK/INC/link.h"
#include"../INTP/INC/intp.h"
#include"../DEF/INC/SWITCH.h"
#include "../DRV/INC/stepMotorDRV.h"


#define M_PI  3.14159265358979323846


SYSTEMTIME st;
INTP_DATA*    intpDataPtr;
MMI_DATA*     mmiDataPtr;
CNC_DATA    cncData;
CNC_DATA    *cncDataPtr;



int rtTimer;
int nrtTimer;

double axisInitValue[3] = {0,90,0};
double resolution[3];
double remainValue[3];

int realUVW(void)
{
	double relDistanceMK;
	double u,v,w;

	for(int i = 0 ; i<3 ; i++)
	{
		 relDistanceMK = cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i]-cncDataPtr->linkData.intpToMmiBlock.newMKPos[i];
	
		if (relDistanceMK != 0)
		{
			cncDataPtr->linkData.intpToMmiBlock.increment[i] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i] )/resolution[i]);
			
			remainValue[i] += ( relDistanceMK - cncDataPtr->linkData.intpToMmiBlock.increment[i] *resolution[i]);
			
			if( !( resolution[i] > remainValue[i] ) )
			{
				cncDataPtr->linkData.intpToMmiBlock.increment[i]++;
				remainValue[i] -= resolution[i];
			}
			
			else if(  !( resolution[i] > (-1)*remainValue[i] ) )
			{
				cncDataPtr->linkData.intpToMmiBlock.increment[i]--;
				remainValue[i] += resolution[i];
			}
		}
		else 
			cncDataPtr->linkData.intpToMmiBlock.increment[i]=0;
	}
	
	
	for(int i=0;i<3;i++)
	{
	cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[i];
	cncDataPtr->linkData.intpToMmiBlock.newMKPos[i]+=cncDataPtr->mmiDataPtr->wheelRatio*cncDataPtr->mmiDataPtr->axisButton[i]*0.1;
	
	}
	
	u=cncDataPtr->linkData.intpToMmiBlock.newMKPos[0];
	v=cncDataPtr->linkData.intpToMmiBlock.newMKPos[1];
	w=cncDataPtr->linkData.intpToMmiBlock.newMKPos[2];

	cncDataPtr->linkData.intpToMmiBlock.newRKPos[2]=w;
	cncDataPtr->linkData.intpToMmiBlock.newRKPos[0]=75*(cos(u*2*M_PI/360)+cos((u+v)*2*M_PI/360));
	cncDataPtr->linkData.intpToMmiBlock.newRKPos[1]=75*(sin(u*2*M_PI/360)+sin((u+v)*2*M_PI/360));

	
	for (int i = 0 ; i < 3 ; i++)
	{
		
#if HD_TIMER
		putAxisValue(i, cncDataPtr->linkData.intpToMmiBlock.increment[i]);
#endif
		
	}

		return 0;
}

int realXYZ(void)
{
	double relDistanceRK;

	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToMmiBlock.oldRKPos[i] = cncDataPtr->linkData.intpToMmiBlock.newRKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] += cncDataPtr->mmiDataPtr->wheelRatio*cncDataPtr->mmiDataPtr->axisButton[i]*0.1;
		cncDataPtr->intpDataPtr->newRKPos[i]=cncDataPtr->linkData.intpToMmiBlock.newRKPos[i];
	}

	trafoXYZtoUVW(cncDataPtr->intpDataPtr);

	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToMmiBlock.newMKPos[i]=cncDataPtr->intpDataPtr->newMKPos[i];

		relDistanceRK=cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i]-cncDataPtr->linkData.intpToMmiBlock.newMKPos[i];

		if(relDistanceRK != 0)
			cncDataPtr->linkData.intpToMmiBlock.increment[i] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i] )/resolution[i]);
		else if (relDistanceRK == 0)
			cncDataPtr->linkData.intpToMmiBlock.increment[i] = 0;

	}

	for (int i = 0 ; i < 3 ; i++)
	{

#if HD_TIMER
		putAxisValue(i, cncDataPtr->linkData.intpToMmiBlock.increment[i]);
#endif

	}

	return 0;
}

#if HD_TIMER
void _stdcall Timer_ISR_Function(LIOINT *pstINTSource)
{
	cncDataPtr->mmiDataPtr->counter++;
	

	if(cncDataPtr->mmiDataPtr->counter > 1000)
			cncDataPtr->mmiDataPtr->counter = 0;

	 cncRtCtrl(cncDataPtr);
	
	 switch((OP_MODE)cncDataPtr->mmiDataPtr->opMode)
	 {
	 case (MEM_MODE):
	 case (MDI_MODE):

		 cncDataPtr->linkData.intpToMmiBlock.increment[0] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[0] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[0] )/0.0018);
		 cncDataPtr->linkData.intpToMmiBlock.increment[1] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[1] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[1] )/0.0018);
		 cncDataPtr->linkData.intpToMmiBlock.increment[2] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[2] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[2] )/0.0025);
		 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[0] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[0];
		 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[1] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[1];
		 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[2] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[2];
		 
	     putAxisValue(0, cncDataPtr->linkData.intpToMmiBlock.increment[0]);
	     putAxisValue(1, cncDataPtr->linkData.intpToMmiBlock.increment[1]);
	     putAxisValue(2, cncDataPtr->linkData.intpToMmiBlock.increment[2]);
	                //(  , 要前進的步數(要前進的角度/解析度0.0018)
		 break;

	 case(JOG_MODE):
		 if(cncDataPtr->mmiDataPtr->UVWtoXYZ == true)
		 {
			 realUVW();
		 }
		 else if (cncDataPtr->mmiDataPtr->UVWtoXYZ == false)
		 {
			 realXYZ();
		 }
		 break;

	 case (WHEEL_MODE):
	 case (TEACH_MODE):
	 case (HOME_MODE):
		 break;

	 }
	

	
}
#endif

namespace iCNC_2015 {

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
	private: System::Windows::Forms::Button^  button_start;
	private: System::Windows::Forms::Timer^  timer_realTime;
	private: System::Windows::Forms::Timer^  timer_nonRealTime;
	private: System::Windows::Forms::Label^  M00;
	private: System::Windows::Forms::Label^  M30;
	private: System::Windows::Forms::Label^  ERR;
	private: System::Windows::Forms::Label^  PGM;
	private: System::Windows::Forms::Label^  HX;
	private: System::Windows::Forms::Label^  HY;
	private: System::Windows::Forms::Label^  HZ;
	private: System::Windows::Forms::Label^  PX;
	private: System::Windows::Forms::Label^  PY;
	private: System::Windows::Forms::Label^  PZ;
	private: System::Windows::Forms::Label^  INX;
	private: System::Windows::Forms::Label^  INY;
	private: System::Windows::Forms::Label^  INZ;
	private: System::Windows::Forms::Label^  NX;
	private: System::Windows::Forms::Label^  NY;
	private: System::Windows::Forms::Label^  NZ;
	private: System::Windows::Forms::Label^  label_year;
	private: System::Windows::Forms::Label^  label_counter;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  X;
	private: System::Windows::Forms::Label^  Y;
	private: System::Windows::Forms::Label^  Z;
	private: System::Windows::Forms::RichTextBox^  richTextBox_ncFile;
	private: System::Windows::Forms::Button^  button_openFile;
	private: System::Windows::Forms::TextBox^  richTextBox_filePath;
	private: System::Windows::Forms::Button^  button_xn;
	private: System::Windows::Forms::Button^  button_xp;
	private: System::Windows::Forms::TrackBar^  trackBar_feedOverride;
	private: System::Windows::Forms::Label^  label_feedOverride;
	private: System::Windows::Forms::Label^  X_position;
	private: System::Windows::Forms::Label^  Y_position;
	private: System::Windows::Forms::Label^  Z_position;
	private: System::Windows::Forms::Button^  UVW;
	private: System::Windows::Forms::Button^  button_yp;
	private: System::Windows::Forms::Button^  button_yn;
	private: System::Windows::Forms::Button^  button_zp;
	private: System::Windows::Forms::Button^  button_zn;
	private: System::Windows::Forms::Label^  U;
	private: System::Windows::Forms::Label^  V;
	private: System::Windows::Forms::Label^  W;
	private: System::Windows::Forms::Label^  U_position;
	private: System::Windows::Forms::Label^  V_position;
	private: System::Windows::Forms::Label^  W_position;
	private: System::Windows::Forms::Button^  X1;
	private: System::Windows::Forms::Button^  X10;
	private: System::Windows::Forms::Button^  X100;
	private: System::Windows::Forms::Button^  button_reset;

	private: System::Windows::Forms::Button^  TEACH_START;
	private: System::Windows::Forms::Button^  RECORD;
	private: System::Windows::Forms::Button^  TEACH_END;
	private: System::Windows::Forms::Button^  M01;


	private: System::Windows::Forms::Button^  FH;
	private: System::Windows::Forms::Button^  SB;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button_emergencystop;







	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button_mem;
	private: System::Windows::Forms::Button^  button_mdi;
	private: System::Windows::Forms::Button^  button_jog;
	private: System::Windows::Forms::Button^  button_wheel;
	private: System::Windows::Forms::Button^  button_teach;
	private: System::Windows::Forms::Button^  button_home;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openFile;









	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

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
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->timer_realTime = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer_nonRealTime = (gcnew System::Windows::Forms::Timer(this->components));
			this->M00 = (gcnew System::Windows::Forms::Label());
			this->M30 = (gcnew System::Windows::Forms::Label());
			this->ERR = (gcnew System::Windows::Forms::Label());
			this->PGM = (gcnew System::Windows::Forms::Label());
			this->HX = (gcnew System::Windows::Forms::Label());
			this->HY = (gcnew System::Windows::Forms::Label());
			this->HZ = (gcnew System::Windows::Forms::Label());
			this->PX = (gcnew System::Windows::Forms::Label());
			this->PY = (gcnew System::Windows::Forms::Label());
			this->PZ = (gcnew System::Windows::Forms::Label());
			this->INX = (gcnew System::Windows::Forms::Label());
			this->INY = (gcnew System::Windows::Forms::Label());
			this->INZ = (gcnew System::Windows::Forms::Label());
			this->NX = (gcnew System::Windows::Forms::Label());
			this->NY = (gcnew System::Windows::Forms::Label());
			this->NZ = (gcnew System::Windows::Forms::Label());
			this->label_year = (gcnew System::Windows::Forms::Label());
			this->label_counter = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->X = (gcnew System::Windows::Forms::Label());
			this->Y = (gcnew System::Windows::Forms::Label());
			this->Z = (gcnew System::Windows::Forms::Label());
			this->richTextBox_ncFile = (gcnew System::Windows::Forms::RichTextBox());
			this->button_openFile = (gcnew System::Windows::Forms::Button());
			this->richTextBox_filePath = (gcnew System::Windows::Forms::TextBox());
			this->button_xn = (gcnew System::Windows::Forms::Button());
			this->button_xp = (gcnew System::Windows::Forms::Button());
			this->trackBar_feedOverride = (gcnew System::Windows::Forms::TrackBar());
			this->label_feedOverride = (gcnew System::Windows::Forms::Label());
			this->X_position = (gcnew System::Windows::Forms::Label());
			this->Y_position = (gcnew System::Windows::Forms::Label());
			this->Z_position = (gcnew System::Windows::Forms::Label());
			this->UVW = (gcnew System::Windows::Forms::Button());
			this->button_yp = (gcnew System::Windows::Forms::Button());
			this->button_yn = (gcnew System::Windows::Forms::Button());
			this->button_zp = (gcnew System::Windows::Forms::Button());
			this->button_zn = (gcnew System::Windows::Forms::Button());
			this->U = (gcnew System::Windows::Forms::Label());
			this->V = (gcnew System::Windows::Forms::Label());
			this->W = (gcnew System::Windows::Forms::Label());
			this->U_position = (gcnew System::Windows::Forms::Label());
			this->V_position = (gcnew System::Windows::Forms::Label());
			this->W_position = (gcnew System::Windows::Forms::Label());
			this->X1 = (gcnew System::Windows::Forms::Button());
			this->X10 = (gcnew System::Windows::Forms::Button());
			this->X100 = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->TEACH_START = (gcnew System::Windows::Forms::Button());
			this->RECORD = (gcnew System::Windows::Forms::Button());
			this->TEACH_END = (gcnew System::Windows::Forms::Button());
			this->M01 = (gcnew System::Windows::Forms::Button());
			this->FH = (gcnew System::Windows::Forms::Button());
			this->SB = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button_emergencystop = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button_mem = (gcnew System::Windows::Forms::Button());
			this->button_mdi = (gcnew System::Windows::Forms::Button());
			this->button_jog = (gcnew System::Windows::Forms::Button());
			this->button_wheel = (gcnew System::Windows::Forms::Button());
			this->button_teach = (gcnew System::Windows::Forms::Button());
			this->button_home = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_openFile = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->BeginInit();
			this->SuspendLayout();
			// 
			// button_start
			// 
			this->button_start->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->button_start->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button_start->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button_start->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->button_start->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_start->ForeColor = System::Drawing::SystemColors::Desktop;
			this->button_start->Location = System::Drawing::Point(424, 328);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(70, 64);
			this->button_start->TabIndex = 0;
			this->button_start->Text = L"START";
			this->button_start->UseVisualStyleBackColor = false;
			this->button_start->Click += gcnew System::EventHandler(this, &Form1::button_start_Click);
			// 
			// timer_realTime
			// 
			this->timer_realTime->Enabled = true;
			this->timer_realTime->Interval = 50;
			this->timer_realTime->Tick += gcnew System::EventHandler(this, &Form1::timer_realTime_Tick);
			// 
			// timer_nonRealTime
			// 
			this->timer_nonRealTime->Enabled = true;
			this->timer_nonRealTime->Tick += gcnew System::EventHandler(this, &Form1::timer_nonRealTime_Tick);
			// 
			// M00
			// 
			this->M00->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->M00->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->M00->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->M00->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->M00->Location = System::Drawing::Point(134, 24);
			this->M00->Name = L"M00";
			this->M00->Size = System::Drawing::Size(55, 35);
			this->M00->TabIndex = 1;
			this->M00->Text = L"M00";
			// 
			// M30
			// 
			this->M30->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->M30->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->M30->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->M30->Location = System::Drawing::Point(134, 62);
			this->M30->Name = L"M30";
			this->M30->Size = System::Drawing::Size(55, 35);
			this->M30->TabIndex = 2;
			this->M30->Text = L"M30";
			this->M30->Click += gcnew System::EventHandler(this, &Form1::M30_Click);
			// 
			// ERR
			// 
			this->ERR->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ERR->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->ERR->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->ERR->Location = System::Drawing::Point(188, 62);
			this->ERR->Name = L"ERR";
			this->ERR->Size = System::Drawing::Size(55, 35);
			this->ERR->TabIndex = 3;
			this->ERR->Text = L"ERR";
			// 
			// PGM
			// 
			this->PGM->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->PGM->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PGM->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->PGM->Location = System::Drawing::Point(188, 24);
			this->PGM->Name = L"PGM";
			this->PGM->Size = System::Drawing::Size(55, 35);
			this->PGM->TabIndex = 4;
			this->PGM->Text = L"PGM";
			// 
			// HX
			// 
			this->HX->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->HX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->HX->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->HX->Location = System::Drawing::Point(239, 24);
			this->HX->Name = L"HX";
			this->HX->Size = System::Drawing::Size(55, 35);
			this->HX->TabIndex = 5;
			this->HX->Text = L"HX";
			// 
			// HY
			// 
			this->HY->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->HY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->HY->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->HY->Location = System::Drawing::Point(292, 24);
			this->HY->Name = L"HY";
			this->HY->Size = System::Drawing::Size(55, 35);
			this->HY->TabIndex = 6;
			this->HY->Text = L"HY";
			// 
			// HZ
			// 
			this->HZ->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->HZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->HZ->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->HZ->Location = System::Drawing::Point(340, 24);
			this->HZ->Name = L"HZ";
			this->HZ->Size = System::Drawing::Size(55, 35);
			this->HZ->TabIndex = 7;
			this->HZ->Text = L"HZ";
			// 
			// PX
			// 
			this->PX->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->PX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PX->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->PX->Location = System::Drawing::Point(391, 24);
			this->PX->Name = L"PX";
			this->PX->Size = System::Drawing::Size(55, 35);
			this->PX->TabIndex = 8;
			this->PX->Text = L"PX";
			// 
			// PY
			// 
			this->PY->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->PY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PY->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->PY->Location = System::Drawing::Point(437, 24);
			this->PY->Name = L"PY";
			this->PY->Size = System::Drawing::Size(55, 35);
			this->PY->TabIndex = 9;
			this->PY->Text = L"PY";
			// 
			// PZ
			// 
			this->PZ->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->PZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PZ->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->PZ->Location = System::Drawing::Point(487, 24);
			this->PZ->Name = L"PZ";
			this->PZ->Size = System::Drawing::Size(55, 35);
			this->PZ->TabIndex = 10;
			this->PZ->Text = L"PZ";
			// 
			// INX
			// 
			this->INX->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->INX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->INX->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->INX->Location = System::Drawing::Point(239, 62);
			this->INX->Name = L"INX";
			this->INX->Size = System::Drawing::Size(55, 35);
			this->INX->TabIndex = 11;
			this->INX->Text = L"INX";
			// 
			// INY
			// 
			this->INY->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->INY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->INY->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->INY->Location = System::Drawing::Point(292, 62);
			this->INY->Name = L"INY";
			this->INY->Size = System::Drawing::Size(55, 35);
			this->INY->TabIndex = 12;
			this->INY->Text = L"INY";
			// 
			// INZ
			// 
			this->INZ->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->INZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->INZ->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->INZ->Location = System::Drawing::Point(340, 62);
			this->INZ->Name = L"INZ";
			this->INZ->Size = System::Drawing::Size(55, 35);
			this->INZ->TabIndex = 13;
			this->INZ->Text = L"INZ";
			// 
			// NX
			// 
			this->NX->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->NX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->NX->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->NX->Location = System::Drawing::Point(391, 62);
			this->NX->Name = L"NX";
			this->NX->Size = System::Drawing::Size(55, 35);
			this->NX->TabIndex = 14;
			this->NX->Text = L"NX";
			// 
			// NY
			// 
			this->NY->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->NY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->NY->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->NY->Location = System::Drawing::Point(437, 62);
			this->NY->Name = L"NY";
			this->NY->Size = System::Drawing::Size(55, 35);
			this->NY->TabIndex = 15;
			this->NY->Text = L"NY";
			// 
			// NZ
			// 
			this->NZ->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->NZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->NZ->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->NZ->Location = System::Drawing::Point(487, 62);
			this->NZ->Name = L"NZ";
			this->NZ->Size = System::Drawing::Size(55, 35);
			this->NZ->TabIndex = 16;
			this->NZ->Text = L"NZ";
			this->NZ->Click += gcnew System::EventHandler(this, &Form1::NZ_Click);
			// 
			// label_year
			// 
			this->label_year->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->label_year->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_year->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->label_year->Location = System::Drawing::Point(548, 24);
			this->label_year->Name = L"label_year";
			this->label_year->Size = System::Drawing::Size(97, 35);
			this->label_year->TabIndex = 17;
			this->label_year->Text = L"102033130";
			// 
			// label_counter
			// 
			this->label_counter->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->label_counter->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_counter->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F));
			this->label_counter->Location = System::Drawing::Point(548, 62);
			this->label_counter->Name = L"label_counter";
			this->label_counter->Size = System::Drawing::Size(99, 35);
			this->label_counter->TabIndex = 18;
			this->label_counter->Text = L"label_counter";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(13, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(115, 73);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 19;
			this->pictureBox1->TabStop = false;
			// 
			// X
			// 
			this->X->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->X->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->X->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->X->Location = System::Drawing::Point(9, 115);
			this->X->Name = L"X";
			this->X->Size = System::Drawing::Size(28, 30);
			this->X->TabIndex = 20;
			this->X->Text = L"X";
			// 
			// Y
			// 
			this->Y->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->Y->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->Y->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->Y->Location = System::Drawing::Point(8, 157);
			this->Y->Name = L"Y";
			this->Y->Size = System::Drawing::Size(28, 30);
			this->Y->TabIndex = 21;
			this->Y->Text = L"Y";
			// 
			// Z
			// 
			this->Z->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->Z->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->Z->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->Z->Location = System::Drawing::Point(9, 199);
			this->Z->Name = L"Z";
			this->Z->Size = System::Drawing::Size(28, 30);
			this->Z->TabIndex = 22;
			this->Z->Text = L"Z";
			this->Z->Click += gcnew System::EventHandler(this, &Form1::Z_Click);
			// 
			// richTextBox_ncFile
			// 
			this->richTextBox_ncFile->Location = System::Drawing::Point(127, 115);
			this->richTextBox_ncFile->Name = L"richTextBox_ncFile";
			this->richTextBox_ncFile->Size = System::Drawing::Size(428, 123);
			this->richTextBox_ncFile->TabIndex = 23;
			this->richTextBox_ncFile->Text = L"";
			this->richTextBox_ncFile->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox_ncFile_TextChanged);
			// 
			// button_openFile
			// 
			this->button_openFile->Location = System::Drawing::Point(127, 244);
			this->button_openFile->Name = L"button_openFile";
			this->button_openFile->Size = System::Drawing::Size(118, 23);
			this->button_openFile->TabIndex = 24;
			this->button_openFile->Text = L"開檔";
			this->button_openFile->UseVisualStyleBackColor = true;
			this->button_openFile->Click += gcnew System::EventHandler(this, &Form1::button_openFile_Click);
			// 
			// richTextBox_filePath
			// 
			this->richTextBox_filePath->Location = System::Drawing::Point(251, 244);
			this->richTextBox_filePath->Name = L"richTextBox_filePath";
			this->richTextBox_filePath->Size = System::Drawing::Size(304, 22);
			this->richTextBox_filePath->TabIndex = 25;
			// 
			// button_xn
			// 
			this->button_xn->Location = System::Drawing::Point(190, 311);
			this->button_xn->Name = L"button_xn";
			this->button_xn->Size = System::Drawing::Size(55, 23);
			this->button_xn->TabIndex = 26;
			this->button_xn->Text = L"X-";
			this->button_xn->UseVisualStyleBackColor = true;
			this->button_xn->Click += gcnew System::EventHandler(this, &Form1::button_xn_Click);
			this->button_xn->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xn_MouseDown);
			this->button_xn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xn_MouseUp);
			// 
			// button_xp
			// 
			this->button_xp->Location = System::Drawing::Point(127, 311);
			this->button_xp->Name = L"button_xp";
			this->button_xp->Size = System::Drawing::Size(57, 23);
			this->button_xp->TabIndex = 27;
			this->button_xp->Text = L"X+";
			this->button_xp->UseVisualStyleBackColor = true;
			this->button_xp->Click += gcnew System::EventHandler(this, &Form1::button_xp_Click);
			this->button_xp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xp_MouseDown);
			this->button_xp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xp_MouseUp);
			// 
			// trackBar_feedOverride
			// 
			this->trackBar_feedOverride->Location = System::Drawing::Point(424, 280);
			this->trackBar_feedOverride->Maximum = 200;
			this->trackBar_feedOverride->Name = L"trackBar_feedOverride";
			this->trackBar_feedOverride->Size = System::Drawing::Size(131, 45);
			this->trackBar_feedOverride->TabIndex = 28;
			this->trackBar_feedOverride->TickFrequency = 10;
			this->trackBar_feedOverride->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_feedOverride_Scroll);
			// 
			// label_feedOverride
			// 
			this->label_feedOverride->AutoSize = true;
			this->label_feedOverride->Location = System::Drawing::Point(457, 271);
			this->label_feedOverride->Name = L"label_feedOverride";
			this->label_feedOverride->Size = System::Drawing::Size(33, 12);
			this->label_feedOverride->TabIndex = 29;
			this->label_feedOverride->Text = L"label1";
			// 
			// X_position
			// 
			this->X_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->X_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->X_position->Location = System::Drawing::Point(33, 115);
			this->X_position->Name = L"X_position";
			this->X_position->Size = System::Drawing::Size(85, 30);
			this->X_position->TabIndex = 30;
			this->X_position->Text = L"X_position";
			// 
			// Y_position
			// 
			this->Y_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Y_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->Y_position->Location = System::Drawing::Point(33, 157);
			this->Y_position->Name = L"Y_position";
			this->Y_position->Size = System::Drawing::Size(85, 30);
			this->Y_position->TabIndex = 31;
			this->Y_position->Text = L"Y_position";
			// 
			// Z_position
			// 
			this->Z_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Z_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->Z_position->Location = System::Drawing::Point(33, 199);
			this->Z_position->Name = L"Z_position";
			this->Z_position->Size = System::Drawing::Size(85, 30);
			this->Z_position->TabIndex = 32;
			this->Z_position->Text = L"Z_position";
			// 
			// UVW
			// 
			this->UVW->Location = System::Drawing::Point(127, 275);
			this->UVW->Name = L"UVW";
			this->UVW->Size = System::Drawing::Size(118, 23);
			this->UVW->TabIndex = 33;
			this->UVW->Text = L"UVW";
			this->UVW->UseVisualStyleBackColor = true;
			this->UVW->Click += gcnew System::EventHandler(this, &Form1::UVW_Click);
			// 
			// button_yp
			// 
			this->button_yp->Location = System::Drawing::Point(127, 340);
			this->button_yp->Name = L"button_yp";
			this->button_yp->Size = System::Drawing::Size(57, 23);
			this->button_yp->TabIndex = 34;
			this->button_yp->Text = L"Y+";
			this->button_yp->UseVisualStyleBackColor = true;
			this->button_yp->Click += gcnew System::EventHandler(this, &Form1::button_yp_Click);
			this->button_yp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yp_MouseDown);
			this->button_yp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yp_MouseUp);
			// 
			// button_yn
			// 
			this->button_yn->Location = System::Drawing::Point(191, 340);
			this->button_yn->Name = L"button_yn";
			this->button_yn->Size = System::Drawing::Size(54, 23);
			this->button_yn->TabIndex = 35;
			this->button_yn->Text = L"Y-";
			this->button_yn->UseVisualStyleBackColor = true;
			this->button_yn->Click += gcnew System::EventHandler(this, &Form1::button_yn_Click);
			this->button_yn->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yn_MouseDown);
			this->button_yn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yn_MouseUp);
			// 
			// button_zp
			// 
			this->button_zp->Location = System::Drawing::Point(127, 369);
			this->button_zp->Name = L"button_zp";
			this->button_zp->Size = System::Drawing::Size(57, 23);
			this->button_zp->TabIndex = 36;
			this->button_zp->Text = L"Z+";
			this->button_zp->UseVisualStyleBackColor = true;
			this->button_zp->Click += gcnew System::EventHandler(this, &Form1::button_zp_Click);
			this->button_zp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zp_MouseDown);
			this->button_zp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zp_MouseUp);
			// 
			// button_zn
			// 
			this->button_zn->Location = System::Drawing::Point(191, 369);
			this->button_zn->Name = L"button_zn";
			this->button_zn->Size = System::Drawing::Size(54, 23);
			this->button_zn->TabIndex = 37;
			this->button_zn->Text = L"Z-";
			this->button_zn->UseVisualStyleBackColor = true;
			this->button_zn->Click += gcnew System::EventHandler(this, &Form1::button_zn_Click);
			this->button_zn->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zn_MouseDown);
			this->button_zn->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zn_MouseUp);
			// 
			// U
			// 
			this->U->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->U->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->U->Location = System::Drawing::Point(8, 275);
			this->U->Name = L"U";
			this->U->Size = System::Drawing::Size(28, 30);
			this->U->TabIndex = 38;
			this->U->Text = L"U";
			// 
			// V
			// 
			this->V->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->V->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->V->Location = System::Drawing::Point(8, 317);
			this->V->Name = L"V";
			this->V->Size = System::Drawing::Size(28, 30);
			this->V->TabIndex = 39;
			this->V->Text = L"V";
			// 
			// W
			// 
			this->W->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->W->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->W->Location = System::Drawing::Point(8, 364);
			this->W->Name = L"W";
			this->W->Size = System::Drawing::Size(28, 30);
			this->W->TabIndex = 40;
			this->W->Text = L"W";
			// 
			// U_position
			// 
			this->U_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->U_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->U_position->Location = System::Drawing::Point(35, 275);
			this->U_position->Name = L"U_position";
			this->U_position->Size = System::Drawing::Size(85, 30);
			this->U_position->TabIndex = 41;
			this->U_position->Text = L"U_position";
			// 
			// V_position
			// 
			this->V_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->V_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->V_position->Location = System::Drawing::Point(35, 317);
			this->V_position->Name = L"V_position";
			this->V_position->Size = System::Drawing::Size(85, 30);
			this->V_position->TabIndex = 42;
			this->V_position->Text = L"V_position";
			// 
			// W_position
			// 
			this->W_position->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->W_position->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			this->W_position->Location = System::Drawing::Point(35, 364);
			this->W_position->Name = L"W_position";
			this->W_position->Size = System::Drawing::Size(85, 30);
			this->W_position->TabIndex = 43;
			this->W_position->Text = L"W_position";
			// 
			// X1
			// 
			this->X1->Location = System::Drawing::Point(251, 275);
			this->X1->Name = L"X1";
			this->X1->Size = System::Drawing::Size(48, 37);
			this->X1->TabIndex = 44;
			this->X1->Text = L"X1";
			this->X1->UseVisualStyleBackColor = true;
			this->X1->Click += gcnew System::EventHandler(this, &Form1::X1_Click);
			// 
			// X10
			// 
			this->X10->Location = System::Drawing::Point(251, 318);
			this->X10->Name = L"X10";
			this->X10->Size = System::Drawing::Size(48, 33);
			this->X10->TabIndex = 45;
			this->X10->Text = L"X2";
			this->X10->UseVisualStyleBackColor = true;
			this->X10->Click += gcnew System::EventHandler(this, &Form1::X10_Click);
			// 
			// X100
			// 
			this->X100->Location = System::Drawing::Point(251, 357);
			this->X100->Name = L"X100";
			this->X100->Size = System::Drawing::Size(48, 35);
			this->X100->TabIndex = 46;
			this->X100->Text = L"X5";
			this->X100->UseVisualStyleBackColor = true;
			this->X100->Click += gcnew System::EventHandler(this, &Form1::X100_Click);
			// 
			// button_reset
			// 
			this->button_reset->BackColor = System::Drawing::Color::Coral;
			this->button_reset->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_reset->Location = System::Drawing::Point(503, 328);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(62, 64);
			this->button_reset->TabIndex = 47;
			this->button_reset->Text = L"RESET";
			this->button_reset->UseVisualStyleBackColor = false;
			this->button_reset->Click += gcnew System::EventHandler(this, &Form1::button_reset_Click);
			// 
			// TEACH_START
			// 
			this->TEACH_START->Location = System::Drawing::Point(305, 275);
			this->TEACH_START->Name = L"TEACH_START";
			this->TEACH_START->Size = System::Drawing::Size(67, 37);
			this->TEACH_START->TabIndex = 48;
			this->TEACH_START->Text = L"TEACH START";
			this->TEACH_START->UseVisualStyleBackColor = true;
			this->TEACH_START->Click += gcnew System::EventHandler(this, &Form1::TEACH_START_Click);
			// 
			// RECORD
			// 
			this->RECORD->Location = System::Drawing::Point(305, 318);
			this->RECORD->Name = L"RECORD";
			this->RECORD->Size = System::Drawing::Size(67, 33);
			this->RECORD->TabIndex = 49;
			this->RECORD->Text = L"RECORD";
			this->RECORD->UseVisualStyleBackColor = true;
			this->RECORD->Click += gcnew System::EventHandler(this, &Form1::RECORD_Click);
			// 
			// TEACH_END
			// 
			this->TEACH_END->Location = System::Drawing::Point(305, 357);
			this->TEACH_END->Name = L"TEACH_END";
			this->TEACH_END->Size = System::Drawing::Size(67, 35);
			this->TEACH_END->TabIndex = 50;
			this->TEACH_END->Text = L"TEACH END";
			this->TEACH_END->UseVisualStyleBackColor = true;
			this->TEACH_END->Click += gcnew System::EventHandler(this, &Form1::TEACH_END_Click);
			// 
			// M01
			// 
			this->M01->Location = System::Drawing::Point(378, 275);
			this->M01->Name = L"M01";
			this->M01->Size = System::Drawing::Size(40, 37);
			this->M01->TabIndex = 51;
			this->M01->Text = L"M01";
			this->M01->UseVisualStyleBackColor = true;
			this->M01->Click += gcnew System::EventHandler(this, &Form1::M01_Click);
			// 
			// FH
			// 
			this->FH->BackColor = System::Drawing::Color::Transparent;
			this->FH->Location = System::Drawing::Point(378, 318);
			this->FH->Name = L"FH";
			this->FH->Size = System::Drawing::Size(40, 33);
			this->FH->TabIndex = 52;
			this->FH->Text = L"FH";
			this->FH->UseVisualStyleBackColor = false;
			this->FH->Click += gcnew System::EventHandler(this, &Form1::FH_Click);
			// 
			// SB
			// 
			this->SB->Location = System::Drawing::Point(378, 357);
			this->SB->Name = L"SB";
			this->SB->Size = System::Drawing::Size(40, 35);
			this->SB->TabIndex = 53;
			this->SB->Text = L"SB";
			this->SB->UseVisualStyleBackColor = true;
			this->SB->Click += gcnew System::EventHandler(this, &Form1::SB_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LightCoral;
			this->button1->Location = System::Drawing::Point(570, 113);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 54;
			this->button1->Text = L"up";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::LightCoral;
			this->button2->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button2->Location = System::Drawing::Point(570, 146);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 66);
			this->button2->TabIndex = 55;
			this->button2->Text = L"參數";
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::LightCoral;
			this->button3->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button3->Location = System::Drawing::Point(570, 218);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 71);
			this->button3->TabIndex = 56;
			this->button3->Text = L"模擬";
			this->button3->UseVisualStyleBackColor = false;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::LightCoral;
			this->button4->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button4->Location = System::Drawing::Point(570, 297);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 62);
			this->button4->TabIndex = 57;
			this->button4->Text = L"診斷";
			this->button4->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::LightCoral;
			this->button5->Location = System::Drawing::Point(570, 369);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 58;
			this->button5->Text = L"down";
			this->button5->UseVisualStyleBackColor = false;
			// 
			// button_emergencystop
			// 
			this->button_emergencystop->BackColor = System::Drawing::Color::Red;
			this->button_emergencystop->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_emergencystop->Location = System::Drawing::Point(503, 399);
			this->button_emergencystop->Name = L"button_emergencystop";
			this->button_emergencystop->Size = System::Drawing::Size(142, 52);
			this->button_emergencystop->TabIndex = 59;
			this->button_emergencystop->Text = L"EMERGENCY STOP";
			this->button_emergencystop->UseVisualStyleBackColor = false;
			this->button_emergencystop->Click += gcnew System::EventHandler(this, &Form1::button_emergencystop_Click);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::Lime;
			this->button12->Location = System::Drawing::Point(12, 411);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(47, 41);
			this->button12->TabIndex = 66;
			this->button12->Text = L"left";
			this->button12->UseVisualStyleBackColor = false;
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::Color::Lime;
			this->button13->Location = System::Drawing::Point(444, 411);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(48, 41);
			this->button13->TabIndex = 67;
			this->button13->Text = L"right";
			this->button13->UseVisualStyleBackColor = false;
			// 
			// button_mem
			// 
			this->button_mem->BackColor = System::Drawing::Color::Lime;
			this->button_mem->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mem->Location = System::Drawing::Point(65, 411);
			this->button_mem->Name = L"button_mem";
			this->button_mem->Size = System::Drawing::Size(60, 40);
			this->button_mem->TabIndex = 60;
			this->button_mem->Text = L"MEM";
			this->button_mem->UseVisualStyleBackColor = false;
			this->button_mem->Click += gcnew System::EventHandler(this, &Form1::button_mem_Click);
			// 
			// button_mdi
			// 
			this->button_mdi->BackColor = System::Drawing::Color::Lime;
			this->button_mdi->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mdi->Location = System::Drawing::Point(127, 411);
			this->button_mdi->Name = L"button_mdi";
			this->button_mdi->Size = System::Drawing::Size(60, 40);
			this->button_mdi->TabIndex = 61;
			this->button_mdi->Text = L"MDI";
			this->button_mdi->UseVisualStyleBackColor = false;
			this->button_mdi->Click += gcnew System::EventHandler(this, &Form1::button_mdi_Click);
			// 
			// button_jog
			// 
			this->button_jog->BackColor = System::Drawing::Color::Lime;
			this->button_jog->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_jog->Location = System::Drawing::Point(190, 411);
			this->button_jog->Name = L"button_jog";
			this->button_jog->Size = System::Drawing::Size(60, 40);
			this->button_jog->TabIndex = 62;
			this->button_jog->Text = L"JOG";
			this->button_jog->UseVisualStyleBackColor = false;
			this->button_jog->Click += gcnew System::EventHandler(this, &Form1::button_jog_Click);
			// 
			// button_wheel
			// 
			this->button_wheel->BackColor = System::Drawing::Color::Lime;
			this->button_wheel->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_wheel->Location = System::Drawing::Point(252, 411);
			this->button_wheel->Name = L"button_wheel";
			this->button_wheel->Size = System::Drawing::Size(60, 40);
			this->button_wheel->TabIndex = 63;
			this->button_wheel->Text = L"WHEEL";
			this->button_wheel->UseVisualStyleBackColor = false;
			this->button_wheel->Click += gcnew System::EventHandler(this, &Form1::button_wheel_Click_1);
			// 
			// button_teach
			// 
			this->button_teach->BackColor = System::Drawing::Color::Lime;
			this->button_teach->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_teach->Location = System::Drawing::Point(315, 411);
			this->button_teach->Name = L"button_teach";
			this->button_teach->Size = System::Drawing::Size(60, 40);
			this->button_teach->TabIndex = 64;
			this->button_teach->Text = L"TEACH";
			this->button_teach->UseVisualStyleBackColor = false;
			this->button_teach->Click += gcnew System::EventHandler(this, &Form1::button_teach_Click);
			// 
			// button_home
			// 
			this->button_home->BackColor = System::Drawing::Color::Lime;
			this->button_home->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_home->Location = System::Drawing::Point(378, 411);
			this->button_home->Name = L"button_home";
			this->button_home->Size = System::Drawing::Size(60, 40);
			this->button_home->TabIndex = 65;
			this->button_home->Text = L"HOME";
			this->button_home->UseVisualStyleBackColor = false;
			this->button_home->Click += gcnew System::EventHandler(this, &Form1::button_home_Click_1);
			// 
			// openFileDialog_openFile
			// 
			this->openFileDialog_openFile->FileName = L"openFileDialog1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(659, 458);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button_home);
			this->Controls->Add(this->button_teach);
			this->Controls->Add(this->button_wheel);
			this->Controls->Add(this->button_jog);
			this->Controls->Add(this->button_mdi);
			this->Controls->Add(this->button_mem);
			this->Controls->Add(this->button_emergencystop);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->SB);
			this->Controls->Add(this->FH);
			this->Controls->Add(this->M01);
			this->Controls->Add(this->TEACH_END);
			this->Controls->Add(this->RECORD);
			this->Controls->Add(this->TEACH_START);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->X100);
			this->Controls->Add(this->X10);
			this->Controls->Add(this->X1);
			this->Controls->Add(this->W_position);
			this->Controls->Add(this->V_position);
			this->Controls->Add(this->U_position);
			this->Controls->Add(this->W);
			this->Controls->Add(this->V);
			this->Controls->Add(this->U);
			this->Controls->Add(this->button_zn);
			this->Controls->Add(this->button_zp);
			this->Controls->Add(this->button_yn);
			this->Controls->Add(this->button_yp);
			this->Controls->Add(this->UVW);
			this->Controls->Add(this->Z_position);
			this->Controls->Add(this->Y_position);
			this->Controls->Add(this->X_position);
			this->Controls->Add(this->label_feedOverride);
			this->Controls->Add(this->trackBar_feedOverride);
			this->Controls->Add(this->button_xp);
			this->Controls->Add(this->button_xn);
			this->Controls->Add(this->richTextBox_filePath);
			this->Controls->Add(this->button_openFile);
			this->Controls->Add(this->richTextBox_ncFile);
			this->Controls->Add(this->Z);
			this->Controls->Add(this->Y);
			this->Controls->Add(this->X);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label_counter);
			this->Controls->Add(this->label_year);
			this->Controls->Add(this->NZ);
			this->Controls->Add(this->NY);
			this->Controls->Add(this->NX);
			this->Controls->Add(this->INZ);
			this->Controls->Add(this->INY);
			this->Controls->Add(this->INX);
			this->Controls->Add(this->PZ);
			this->Controls->Add(this->PY);
			this->Controls->Add(this->PX);
			this->Controls->Add(this->HZ);
			this->Controls->Add(this->HY);
			this->Controls->Add(this->HX);
			this->Controls->Add(this->PGM);
			this->Controls->Add(this->ERR);
			this->Controls->Add(this->M30);
			this->Controls->Add(this->M00);
			this->Controls->Add(this->button_start);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button_start_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (cncDataPtr->mmiDataPtr->restart == false)
				 {
				 
				if(cncDataPtr->mmiDataPtr->startHold==false)//要有檔案 和MEM
			     {
				   button_start->BackColor = Color::Red;
				   button_reset->BackColor = Color::Coral;
				   cncDataPtr->mmiDataPtr->startHold=true;
                        //************************
				   switch((OP_MODE)cncDataPtr->mmiDataPtr->opMode)
				    {
					 case (MEM_MODE):
						 if ( cncDataPtr->mmiData.ncFileValid == true)
						 {
							strcpy(cncDataPtr->linkData.sysToDecBlock.ncFilePath, cncDataPtr->mmiData.ncFilePath);
				
							cncDataPtr->mmiData.ncFileValid=false;
									//cncDataPtr->linkData.mmiToDec.ncFileValid=false;
						 }
						 break;
					
					 case MDI_MODE:
						{
									
							       pin_ptr<const wchar_t> wch = PtrToStringChars( richTextBox_ncFile->Text );

									size_t  sizeInBytes = ( (richTextBox_ncFile->Text->Length + 1) * 2);

									size_t convertedChars=0;
									if ( (sizeInBytes / 2) <=199)
									{
										wcstombs_s( &convertedChars, cncDataPtr->mmiDataPtr->ncFileCord, sizeInBytes, wch, sizeInBytes);
										//        (              destination        )                            (source)

										strcpy( cncDataPtr->linkData.sysToDecBlock.ncFileCord, cncDataPtr->mmiData.ncFileCord );

										cncDataPtr->linkData.sysToDecBlock.ncFileValid=true;
									}
									else
										 MessageBox::Show("Too Many Bytes Input by MDI Input" , "MDI錯誤" , MessageBoxButtons::OK , MessageBoxIcon::Warning ) ;
						}
							break;

					 case JOG_MODE:
						break;
					 case WHEEL_MODE:
						 break;
					 case TEACH_MODE:
						 break;
					 case HOME_MODE:
						 break;
					 case NULL_MODE:
						 break;
					}
						
			
                    }

			     else  if(cncDataPtr->mmiDataPtr->startHold==true)
			     {
				   button_start->BackColor = Color::DeepSkyBlue;
				   cncDataPtr->mmiDataPtr->startHold=false;
			     }
				 }
				 else if (cncDataPtr->mmiDataPtr->restart ==true)
				 {
				   button_start->BackColor = Color::Red;
				   button_reset->BackColor = Color::Coral;

			       if(cncDataPtr->intpData.intpRestart == false)
			       cncDataPtr->intpData.intpRestart = true;

			       if(cncDataPtr->decData.decRestart == false)
				   cncDataPtr->decData.decRestart = true;

				   cncDataPtr->mmiDataPtr->restart= false;
				 }

			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 rtTimer=0;
                 nrtTimer=0;
				 
				 
				 resolution[0] = 0.0018;	
				 resolution[1] = 0.0018;
				 resolution[2] = 0.0025;

				 

				 cncDataPtr = &cncData ; 
				 cncInit(cncDataPtr);


				 
                 #if HD_TIMER
		
				 initMotionCard(axisInitValue[0], axisInitValue[1], axisInitValue[2],REAL_SAMPLING_TIME,Timer_ISR_Function);
				 enableHDTimer(REAL_SAMPLING_TIME);	
				 timer_realTime->Enabled		= false;
				 timer_nonRealTime->Enabled	= true;
                 #else
				 timer_realTime->Interval = REAL_SAMPLING_TIME;
				 timer_realTime->Enabled		= true;
				 timer_nonRealTime->Enabled	= true;
                 #endif

				 for (int i=0;i<3;i++)
				 {
					 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i]=axisInitValue[i];
					 cncDataPtr->linkData.intpToMmiBlock.newMKPos[i]=axisInitValue[i];
					 remainValue[i]=0;
				 }

				 
			 }
private: System::Void timer_realTime_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				

				 cncDataPtr->mmiDataPtr->counter++;
				 label_counter->Text = cncDataPtr->mmiDataPtr->counter.ToString("0.00");
				
				 if(cncDataPtr->mmiDataPtr->counter >1000)
				 {
					 cncDataPtr->mmiDataPtr->counter = 0;
				 }
				 rtTimer++;
				 cncRtCtrl(cncDataPtr);

				 switch((OP_MODE)cncDataPtr->mmiDataPtr->opMode)
				 {
				 case (MEM_MODE):
				 case (MDI_MODE):

				 cncDataPtr->linkData.intpToMmiBlock.increment[0] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[0] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[0] )/0.0018);
				 cncDataPtr->linkData.intpToMmiBlock.increment[1] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[1] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[1] )/0.0018);
				 cncDataPtr->linkData.intpToMmiBlock.increment[2] = (int)(( cncDataPtr->linkData.intpToMmiBlock.newMKPos[2] - cncDataPtr->linkData.intpToMmiBlock.oldMKPos[2] )/0.0025);
				 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[0] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[0];
				 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[1] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[1];
				 cncDataPtr->linkData.intpToMmiBlock.oldMKPos[2] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[2];
				 break;

				 case(JOG_MODE):
				 
				 if(cncDataPtr->mmiDataPtr->UVWtoXYZ == true)
				 {
					 realUVW();
				 }
				 else if (cncDataPtr->mmiDataPtr->UVWtoXYZ == false)
				 {
					 realXYZ();
				 }
				 

				  break;
			     
				  case (WHEEL_MODE):
				  case (TEACH_MODE):
				  case (HOME_MODE):
				  break;

				 }
			 }
private: System::Void timer_nonRealTime_Tick(System::Object^  sender, System::EventArgs^  e)
			 {//
				 
				 GetSystemTime(&st);//st沒定義
				 cncNrtCtrl(cncDataPtr);
				 //mmiCtrl(cncDataPtr->mmiDataPtr);
				 nrtTimer++;

				 if (cncDataPtr->mmiDataPtr->M30==true)
				 {
					 button_start->BackColor = Color::DeepSkyBlue;
					 cncDataPtr->mmiDataPtr->M30= false;
				 }

				 X_position->Text = cncDataPtr->linkData.intpToMmiBlock.newRKPos[0].ToString("0.00");
				 Y_position->Text = cncDataPtr->linkData.intpToMmiBlock.newRKPos[1].ToString("0.00");
				 Z_position->Text = cncDataPtr->linkData.intpToMmiBlock.newRKPos[2].ToString("0.00");
			     U_position->Text = cncDataPtr->linkData.intpToMmiBlock.newMKPos[0].ToString("0.00");
				 V_position->Text = cncDataPtr->linkData.intpToMmiBlock.newMKPos[1].ToString("0.00");
				 W_position->Text = cncDataPtr->linkData.intpToMmiBlock.newMKPos[2].ToString("0.00");


			 }
private: System::Void button_openFile_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			
			 
			 if(cncDataPtr->mmiDataPtr->opMode == MEM_MODE)
             {
                  openFileDialog_openFile->InitialDirectory = "";
                  openFileDialog_openFile->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.)|*.*";
                  openFileDialog_openFile->FilterIndex = 2;
                  openFileDialog_openFile->DefaultExt = "*.txt";
                  openFileDialog_openFile->FileName = "";
                  openFileDialog_openFile->RestoreDirectory = true;

                  if(openFileDialog_openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                  {
                       richTextBox_filePath->Text = openFileDialog_openFile->FileName ;
                       richTextBox_ncFile->LoadFile(openFileDialog_openFile->FileName , RichTextBoxStreamType::PlainText);

                       strcpy( cncDataPtr->mmiDataPtr->ncFilePath, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( openFileDialog_openFile->FileName ) );
                       cncDataPtr->mmiDataPtr->ncFileValid = true ;
				  }

             }
             else
             {
                  MessageBox::Show("請選擇MEM MODE" , "模式錯誤" , MessageBoxButtons::OK , MessageBoxIcon::Warning );
             }

		 }

private: System::Void trackBar_feedOverride_Scroll(System::Object^  sender, System::EventArgs^  e)
		 {
			 cncDataPtr->mmiDataPtr->FeedOverride = trackBar_feedOverride->Value;
			 label_feedOverride->Text = trackBar_feedOverride->Value.ToString() + "%";
		 }
private: System::Void NZ_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		 }

private: System::Void button_xp_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		 }
private: System::Void button_xn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 /*if(cncDataPtr->mmiDataPtr->axisButton[0] == 2)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0] = 0;
				 button_xn->BackColor = Color::Transparent;
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0] = 2;
				 button_xn->BackColor = Color::Red;
				 button_xn->BackColor = Color::Transparent;
				 
			 }*/
		 }
private: System::Void button_yp_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 /*if(cncDataPtr->mmiDataPtr->axisButton[1] == 1)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1] = 0;
				 button_yp->BackColor = Color::Transparent;
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1] = 1;
				 button_yp->BackColor = Color::Red;
				 button_yp->BackColor = Color::Transparent;
				 
			 }*/
		 }
private: System::Void button_yn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 /*if(cncDataPtr->mmiDataPtr->axisButton[1] == 2)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1] = 0;
				 button_yn->BackColor = Color::Transparent;
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1] = 2;
				 button_yn->BackColor = Color::Red;
				 button_yn->BackColor = Color::Transparent;
			 }*/
		 }
private: System::Void button_zp_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			/*if(cncDataPtr->mmiDataPtr->axisButton[2] == 1)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2] = 0;
				 button_zp->BackColor = Color::Transparent;
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2] = 1;
				 button_zp->BackColor = Color::Red;
				 button_zp->BackColor = Color::Transparent;
			 }*/
		 }
private: System::Void button_zn_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 /*if(cncDataPtr->mmiDataPtr->axisButton[2] == 2)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2] = 0;
				 button_zn->BackColor = Color::Transparent;
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2] = 2;
				 button_zn->BackColor = Color::Red;
				 button_zn->BackColor = Color::Transparent;
			 }*/
		 }

private: System::Void FH_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 
			 if(cncDataPtr->mmiDataPtr->feedHold == true)
			 {
				 cncDataPtr->mmiDataPtr->feedHold = false;
				 FH->BackColor = Color::Transparent; 
				 // change button's backcolor to silver
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->feedHold = true;
				 FH->BackColor=Color::Red;
				 // change button's backcolor to red
			 }
		 }
private: System::Void M01_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->M01Hold == false)
			 {
				 M01->BackColor = Color::Red; //Transparent
				 cncDataPtr->mmiDataPtr->M01Hold=true;
			 }
			 else if(cncDataPtr->mmiDataPtr->M01Hold == true)
			 {
				 M01->BackColor = Color::Transparent; 
				 cncDataPtr->mmiDataPtr->M01Hold=false;
			 }
		 }
private: System::Void SB_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->SBHold  == false)
			 {
				 SB->BackColor = Color::Red; //Transparent
				 cncDataPtr->mmiDataPtr->SBHold =true;
			 }
			 else if(cncDataPtr->mmiDataPtr->SBHold == true)
			 {
				 SB->BackColor = Color::Transparent; 
				 cncDataPtr->mmiDataPtr->SBHold =false;
			 }
		 }

private: System::Void X1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 if (cncDataPtr->mmiDataPtr->X1Valid==false)
				 {
					 cncDataPtr->mmiDataPtr->X1Valid=true;
					 cncDataPtr->mmiDataPtr->wheelRatio = 1;
					 X1->BackColor = Color::Red;
					 X10->BackColor = Color::Transparent;
					 X100->BackColor = Color::Transparent;
				 }
				 else
				 {
					 cncDataPtr->mmiDataPtr->X1Valid=false;
					 cncDataPtr->mmiDataPtr->wheelRatio = 0;
					 X1->BackColor = Color::Transparent;
				 }
	
			 }
		 }
private: System::Void X10_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 if (cncDataPtr->mmiDataPtr->X10Valid==false)
				 {
					 cncDataPtr->mmiDataPtr->X10Valid=true;
					 cncDataPtr->mmiDataPtr->wheelRatio = 2;
					 X1->BackColor = Color::Transparent;
					 X10->BackColor = Color::Red;
					 X100->BackColor = Color::Transparent;
				 }
				 else
				 {
					 cncDataPtr->mmiDataPtr->X10Valid=true;
					 cncDataPtr->mmiDataPtr->wheelRatio = 0;
					 X10->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void X100_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 if (cncDataPtr->mmiDataPtr->X100Valid==false)
				 {
					 cncDataPtr->mmiDataPtr->X100Valid=true;
					 cncDataPtr->mmiDataPtr->wheelRatio = 5;
					 X1->BackColor = Color::Transparent;
					 X10->BackColor = Color::Transparent;
					 X100->BackColor = Color::Red;
				 }
				 else
				 {
					 cncDataPtr->mmiDataPtr->X100Valid=false;
					 cncDataPtr->mmiDataPtr->wheelRatio = 0;
					 X100->BackColor = Color::Transparent;
				 }
			 }
		 }

private: System::Void UVW_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if( cncDataPtr->mmiDataPtr->UVWtoXYZ==false)
			 {
				 cncDataPtr->mmiDataPtr->UVWtoXYZ=true;
				 UVW->Text ="XYZ";
				 button_xn->Text = "U-";
				 button_yn->Text = "V-";
				 button_zn->Text = "W-";
				 button_xp->Text = "U+";
				 button_yp->Text = "V+";
				 button_zp->Text = "W+";
				
			 }
			 else
			 {
				 cncDataPtr->mmiDataPtr->UVWtoXYZ=false;
				 UVW->Text = "UVW";
				 button_xn->Text = "X-";
				 button_yn->Text = "Y-";
				 button_zn->Text = "Z-";
				 button_xp->Text = "X+";
				 button_yp->Text = "Y+";
				 button_zp->Text = "Z+";
				 
			 }


			/* if (cncDataPtr->mmiDataPtr->xyzJog == true)
			 {
				 UVW->Text = "UVW";
				 button_xn->Text = "X-";
				 button_yn->Text = "Y-";
				 button_zn->Text = "Z-";
				 button_xp->Text = "X+";
				 button_yp->Text = "Y+";
				 button_zp->Text = "Z+";
				 cncDataPtr->mmiDataPtr->xyzJog = false;

			 }
			 else
			 {
				 UVW->Text ="XYZ";
				 button_xn->Text = "U-";
				 button_yn->Text = "V-";
				 button_zn->Text = "W-";
				 button_xp->Text = "U+";
				 button_yp->Text = "V+";
				 button_zp->Text = "W+";
				 cncDataPtr->mmiDataPtr->xyzJog = true;
			 }*/
		 }

private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 cncDataPtr->mmiDataPtr->restart = true;

			 if(cncDataPtr->intpData.intpReset == false)
				 cncDataPtr->intpData.intpReset =true;
			 if (cncDataPtr->decDataPtr->decReset==false)
			     cncDataPtr->decDataPtr->decReset=true;

			 button_reset->BackColor = Color::Red;
			 button_start->BackColor = Color::DeepSkyBlue;
			 
		 }
private: System::Void button_emergencystop_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (cncDataPtr->mmiDataPtr->EmStopHoldValid ==false)
			 {
				 cncDataPtr->mmiDataPtr->EmStopHold = true;
				 cncDataPtr->mmiDataPtr->EmStopHoldValid = true;

			 }
		 }
private: System::Void TEACH_START_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if (cncDataPtr->mmiDataPtr->teachStartValid ==false)
			 {
				 cncDataPtr->mmiDataPtr->teachStart = true;
				 cncDataPtr->mmiDataPtr->teachStartValid = true;

			 }
		 }
private: System::Void RECORD_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 if (cncDataPtr->mmiDataPtr->recordValid ==false)
			 {
				 cncDataPtr->mmiDataPtr->record = true;
				 cncDataPtr->mmiDataPtr->recordValid = true;

			 }
		 }
private: System::Void TEACH_END_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (cncDataPtr->mmiDataPtr->teachEndValid ==false)
			 {
				 cncDataPtr->mmiDataPtr->teachEnd = true;
				 cncDataPtr->mmiDataPtr->teachEndValid = true;

			 }
		 }

private: System::Void button_xp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0]=1;
				 button_xp->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[0] = true;
			 }
		 }
private: System::Void button_xp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0]=0;
				 button_xp->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[0] = true;
			 }
		 }
private: System::Void button_xn_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0]=-1;
				 button_xn->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[0] = true;
			 }
		 }
private: System::Void button_xn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[0]=0;
				 button_xn->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[0] = true;
			 }
		 }
private: System::Void button_yp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1]=1;
				 button_yp->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[1] = true;
			 }
		 }
private: System::Void button_yp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1]=0;
				 button_yp->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[1] = true;
			 }
		 }
private: System::Void button_yn_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1]=-1;
				 button_yn->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[1] = true;
			 }
		 }
private: System::Void button_yn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[1]=0;
				 button_yn->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[1] = true;
			 }
		 }
private: System::Void button_zp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2]=1;
				 button_zp->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[2] = true;
			 }
		 }
private: System::Void button_zp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2]=0;
				 button_zp->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[2] = true;
			 }
		 }
private: System::Void button_zn_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2]=-1;
				 button_zn->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->axisButtonValid[2] = true;
			 }
		 }
private: System::Void button_zn_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if(cncDataPtr->mmiDataPtr->opMode == JOG_MODE)
			 {
				 cncDataPtr->mmiDataPtr->axisButton[2]=0;
				 button_zn->BackColor = Color::Transparent;
				 cncDataPtr->mmiDataPtr->axisButtonValid[2] = true;
			 }
		 }

private: System::Void button_mem_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_mem->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode = MEM_MODE;
				 break;
			 case MEM_MODE:
				 button_mem->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MDI_MODE:
			 case JOG_MODE:
			 case WHEEL_MODE:
			 case TEACH_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=MEM_MODE;

				 button_mem->BackColor = Color::Red;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_mdi_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_mdi->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=MDI_MODE;
				 break;
			 case MDI_MODE:
				 button_mdi->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case JOG_MODE:
			 case WHEEL_MODE:
			 case TEACH_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=MDI_MODE;

				 button_mdi->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_jog_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_jog->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=JOG_MODE;
				 
				 break;
			 case JOG_MODE:
				 button_jog->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case WHEEL_MODE:
			 case TEACH_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=JOG_MODE;

				 button_jog->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_wheel_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_wheel->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=WHEEL_MODE;
				 break;
			 case WHEEL_MODE:
				 button_wheel->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case JOG_MODE:
			 case TEACH_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=WHEEL_MODE;

				 button_wheel->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_teach_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_teach->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=TEACH_MODE;
				 break;
			 case TEACH_MODE:
				 button_teach->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case JOG_MODE:
			 case WHEEL_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=TEACH_MODE;

				 button_teach->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_home_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_home->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=HOME_MODE;
				 break;
			 case HOME_MODE:
				 button_home->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case JOG_MODE:
			 case WHEEL_MODE:
			 case TEACH_MODE:

				 cncDataPtr->mmiDataPtr->opMode=HOME_MODE;

				 button_home->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 break;
		 }
};
private: System::Void Z_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void M30_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
          #if HD_TIMER
			 disableHDTimer();
			 closeMotionCard();
          #endif
		 }

private: System::Void button_wheel_Click_1(System::Object^  sender, System::EventArgs^  e)
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_wheel->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=WHEEL_MODE;
				 break;
			 case WHEEL_MODE:
				 button_wheel->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case JOG_MODE:
			 case TEACH_MODE:
			 case HOME_MODE:

				 cncDataPtr->mmiDataPtr->opMode=WHEEL_MODE;

				 button_wheel->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 button_home->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void button_home_Click_1(System::Object^  sender, System::EventArgs^  e)
		 {
			 switch(cncDataPtr->mmiDataPtr->opMode)
			 {
			 case NULL_MODE:
				 button_home->BackColor = Color::Red;
				 cncDataPtr->mmiDataPtr->opMode=HOME_MODE;
				 break;
			 case HOME_MODE:
				 button_home->BackColor = Color::Lime;
				 cncDataPtr->mmiDataPtr->opMode=NULL_MODE;
				 break;
			 case MEM_MODE:
			 case MDI_MODE:
			 case JOG_MODE:
			 case WHEEL_MODE:
			 case TEACH_MODE:

				 cncDataPtr->mmiDataPtr->opMode=HOME_MODE;

				 button_home->BackColor = Color::Red;
				 button_mem->BackColor = Color::Lime;
				 button_mdi->BackColor = Color::Lime;
				 button_jog->BackColor = Color::Lime;
				 button_wheel->BackColor = Color::Lime;
				 button_teach->BackColor = Color::Lime;
				 break;
			 }
		 }
private: System::Void richTextBox_ncFile_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

