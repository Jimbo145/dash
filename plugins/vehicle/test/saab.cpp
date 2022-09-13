#include "saab.hpp"



bool SAAB93::init(ICANBus* canbus){
    if (this->arbiter) {

        this->debug = new DebugWindow(*this->arbiter);

        canbus->registerFrameHandler(0x290, [this](QByteArray payload){this->handleMsgSteeringWheel(payload);});
        canbus->registerFrameHandler(0x108, [this](QByteArray payload){this->handleMsgDriverDoor(payload);});
        canbus->registerFrameHandler(0x300, [this](QByteArray payload){this->handleMsgGuages(payload);});
        canbus->registerFrameHandler(0x460, [this](QByteArray payload){this->handleMsgLightSwitch(payload);});
        canbus->registerFrameHandler(0x183, [this](QByteArray payload){this->handleMsgSpaDist(payload);});
		canbus->registerFrameHandler(0x180, [this](QByteArray payload){this->handleMsgParkSensorDist(payload);});


        SAAB_LOG(info)<<"loaded successfully";
        return true;
    }
    else{
        SAAB_LOG(error)<<"Failed to get arbiter";
        return false;
    }
    

}

QList<QWidget *> SAAB93::widgets()
{
    QList<QWidget *> tabs;
    //tabs.append(this->climate);
    tabs.append(this->debug);
    return tabs;
}


/* 
ID 290 wheel controls

[byte 0] Msc Steering Wheel 
	bit 0 -- Windshield Washer
	bit 2 -- horn
	bit 4 -- highbeam toggle
	bit 5 -- highbeam on

[byte 1] Wipers
	value 01 -- single
	value 10 -- intermittent
	value 11 -- continuous
	value 13 -- fast
	bit 4 - 7 -- wiper speed
	
[byte 3] radio
	value 1 -- volume up
	value 2 -- volume down
	value 3 -- source
	value 4 -- talk
	value 5 -- seek up
	value 6 -- seek down
	value 17 -- next
	value 18 -- hang up
	
[byte 4] turn signal
	bit 6 -- right turn
	bit 7 -- left turn
*/

void SAAB93::handleMsgSteeringWheel(QByteArray payload){

	//byte 3 (radio)
	
	switch( (unsigned char)payload.at(3) )
	{
		case 1: //volume up
			this->debug->lcdNumber_volup->display(1)));
			Break;
		case 2: //vol down
			this->debug->lcdNumber_voldown->display(1)));
			Break;
		case 3: // source
			this->debug->lcdNumber_source->display(1)));
			Break;
		case 4: // talk
			this->debug->lcdNumber_talk->display(1)));
			Break;
		case 5: // seek up
			this->debug->lcdNumber_seekup->display(1)));
			this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::NEXT );
			Break;
		case 6: // seek down
			this->debug->lcdNumber_seekdown->display(1)));
			this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::PREV );
			Break;
		case 17: // next
			this->debug->lcdNumber_next->display(1)));
			this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::TOGGLE_PLAY );
			Break;
		case 18: // hangup
			this->debug->lcdNumber_hangup->display(1)));
			this->arbiter->send_openauto_button_press(aasdk::proto::enums::ButtonCode::CALL_END );
			Break;
		default:
			this->debug->lcdNumber_volup->display(0)));
			this->debug->lcdNumber_voldown->display(0)));
			this->debug->lcdNumber_source->display(0)));
			this->debug->lcdNumber_talk->display(0)));
			this->debug->lcdNumber_seekup->display(0)));
			this->debug->lcdNumber_seekdown->display(0)));
			this->debug->lcdNumber_next->display(0)));
			this->debug->lcdNumber_hangup->display(0)));
			Break;
	}
	
}

/*
ID 320 
`<code class="byte1">00000001` doors locked  
`<code class="byte1">00000100` door lock button  
`<code class="byte1">00001000` door unlock button  
`<code class="byte2">10010000` mirror in motion  
`<code class="byte3">00000001` trunk release button  
 Passenger mirror  
`<code class="byte4">00010000` left button  
`<code class="byte4">00100000` right button  
`<code class="byte4">01000000` up button  
`<code class="byte4">10000000` down button  
 Front windows  
`<code class="byte6">00000010` passenger window up button  
`<code class="byte6">00000100` passenger window down button  
`<code class="byte6">00001000` passenger comfort open button  
`<code class="byte6">00010000` driver window in motion  
`<code class="byte6">00100000` driver window closed  
`<code class="byte6">10000000` window lock button  
 Rear windows  
`<code class="byte7">00000100` passenger window down button  
`<code class="byte7">00001000` passenger window up button  
`<code class="byte7">00010000` passenger comfort open button  
`<code class="byte7">00100000` driver up button  
`<code class="byte7">01000000` driver down button  
`<code class="byte7">10000000` driver comfort open button
*/

void SAAB93::handleMsgDriverDoor(QByteArray payload){
	//Stub
	
}

/* Gauges
ID 108 
Length:7 bytes  

[byte 0]
UNK
[byte 1]
SPEED Low
[byte 2]
Speed High
[byte 3]
RPM low
[byte 4]
RPM high
[byte 5]
Accel Pos
[byte 6]
UNK


Speed[kph] = high << 8 + LOW / 130 
RPM = high << 8 + LOW
*/

void SAAB93::handleMsgGuages(QByteArray payload){
	//Stub
	
}

/* Light Switch
ID 300 
00 LL 00 

[byte 1]
 bit 3 -- handbrake
 bit 4 -- main lights
 bit 5 -- Corner lights
 bit 6 -- Rear Fog
 bit 7 -- Front Fog
 

0000 0000 = Lights Off
0000 1000 = handbrake
0001 0000 = Main lights
0010 0000 = Corner Lights
0100 0000 = Rear foglights button
1000 0000 = Front foglights button

*/

void SAAB93::handleMsgLightSwitch(QByteArray payload){
	//Stub
	
}

/* Brightness
ID 460 


*/

void SAAB93::handleMsgBright(QByteArray payload){
	//Stub
	
	//Display to debug values
	
}

/* SPA
ID 183 
zz pp ww
zz 43 SPA not active
zz 62 SPA active
ww SPA distance 

[byte 0] 
	Distance
[byte 1]
 
[byte 2]
	value 43 -- Active
	value 62 -- unactive
	
 0011 1110 SPA Active
 0010 1011 SPA Unactive

*/

void SAAB93::handleMsgSpaDist(QByteArray payload){
	//Stub
	
}

/* Parking Sensor Distance
ID 180
3C 06 XX YY ZZ

[byte 0] 
	Distance LOW 
[byte 1]

	Distance MIDDLE
[byte 2]
	Distance HIGH
	

*/

void SAAB93::handleMsgParkSensorDist(QByteArray payload){
	
			this->debug->lcdNumber_senseHigh->display((uint8_t)payload.at(2))));
			this->debug->lcdNumber_SenseMiddle->display((uint8_t)payload.at(1))));
			this->debug->lcdNumber_SenseLow->display((uint8_t)payload.at(0))));
	//Stub
	
}

DebugWindow::DebugWindow(Arbiter &arbiter, QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Debug");

    verticalLayout = new QVBoxLayout(Debug);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	formLayout = new QFormLayout();
	formLayout->setObjectName(QString::fromUtf8("formLayout"));
	label_2 = new QLabel(Debug);
	label_2->setObjectName(QString::fromUtf8("label_2"));

	formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

	line = new QFrame(Debug);
	line->setObjectName(QString::fromUtf8("line"));
	line->setMinimumSize(QSize(0, 20));
	line->setBaseSize(QSize(0, 10));
	line->setFrameShadow(QFrame::Raised);
	line->setLineWidth(3);
	line->setMidLineWidth(0);
	line->setFrameShape(QFrame::HLine);

	formLayout->setWidget(0, QFormLayout::FieldRole, line);

	label_3 = new QLabel(Debug);
	label_3->setObjectName(QString::fromUtf8("label_3"));

	formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

	lcdNumber_volup = new QLCDNumber(Debug);
	lcdNumber_volup->setObjectName(QString::fromUtf8("lcdNumber_volup"));
	lcdNumber_volup->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(1, QFormLayout::FieldRole, lcdNumber_volup);

	label_4 = new QLabel(Debug);
	label_4->setObjectName(QString::fromUtf8("label_4"));

	formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

	lcdNumber_voldown = new QLCDNumber(Debug);
	lcdNumber_voldown->setObjectName(QString::fromUtf8("lcdNumber_voldown"));
	lcdNumber_voldown->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(2, QFormLayout::FieldRole, lcdNumber_voldown);

	label = new QLabel(Debug);
	label->setObjectName(QString::fromUtf8("label"));

	formLayout->setWidget(3, QFormLayout::LabelRole, label);

	lcdNumber_source = new QLCDNumber(Debug);
	lcdNumber_source->setObjectName(QString::fromUtf8("lcdNumber_source"));
	lcdNumber_source->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(3, QFormLayout::FieldRole, lcdNumber_source);

	label_6 = new QLabel(Debug);
	label_6->setObjectName(QString::fromUtf8("label_6"));

	formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

	lcdNumber_talk = new QLCDNumber(Debug);
	lcdNumber_talk->setObjectName(QString::fromUtf8("lcdNumber_talk"));
	lcdNumber_talk->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(4, QFormLayout::FieldRole, lcdNumber_talk);

	label_5 = new QLabel(Debug);
	label_5->setObjectName(QString::fromUtf8("label_5"));

	formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

	lcdNumber_seekup = new QLCDNumber(Debug);
	lcdNumber_seekup->setObjectName(QString::fromUtf8("lcdNumber_seekup"));
	lcdNumber_seekup->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(5, QFormLayout::FieldRole, lcdNumber_seekup);

	label_7 = new QLabel(Debug);
	label_7->setObjectName(QString::fromUtf8("label_7"));

	formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

	lcdNumber_seekdown = new QLCDNumber(Debug);
	lcdNumber_seekdown->setObjectName(QString::fromUtf8("lcdNumber_seekdown"));
	lcdNumber_seekdown->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(6, QFormLayout::FieldRole, lcdNumber_seekdown);

	label_8 = new QLabel(Debug);
	label_8->setObjectName(QString::fromUtf8("label_8"));

	formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

	lcdNumber_next = new QLCDNumber(Debug);
	lcdNumber_next->setObjectName(QString::fromUtf8("lcdNumber_next"));
	lcdNumber_next->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(7, QFormLayout::FieldRole, lcdNumber_next);

	label_9 = new QLabel(Debug);
	label_9->setObjectName(QString::fromUtf8("label_9"));

	formLayout->setWidget(8, QFormLayout::LabelRole, label_9);

	lcdNumber_hangup = new QLCDNumber(Debug);
	lcdNumber_hangup->setObjectName(QString::fromUtf8("lcdNumber_hangup"));
	lcdNumber_hangup->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(8, QFormLayout::FieldRole, lcdNumber_hangup);

	label_10 = new QLabel(Debug);
	label_10->setObjectName(QString::fromUtf8("label_10"));

	formLayout->setWidget(9, QFormLayout::LabelRole, label_10);

	line_2 = new QFrame(Debug);
	line_2->setObjectName(QString::fromUtf8("line_2"));
	line_2->setMinimumSize(QSize(0, 15));
	line_2->setLineWidth(3);
	line_2->setFrameShape(QFrame::HLine);
	line_2->setFrameShadow(QFrame::Sunken);

	formLayout->setWidget(9, QFormLayout::FieldRole, line_2);

	label_11 = new QLabel(Debug);
	label_11->setObjectName(QString::fromUtf8("label_11"));

	formLayout->setWidget(10, QFormLayout::LabelRole, label_11);

	lcdNumber_spadist = new QLCDNumber(Debug);
	lcdNumber_spadist->setObjectName(QString::fromUtf8("lcdNumber_spadist"));
	lcdNumber_spadist->setSegmentStyle(QLCDNumber::Flat);

	formLayout->setWidget(10, QFormLayout::FieldRole, lcdNumber_spadist);

	label_12 = new QLabel(Debug);
	label_12->setObjectName(QString::fromUtf8("label_12"));

	formLayout->setWidget(11, QFormLayout::LabelRole, label_12);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	lcdNumber_senseHigh = new QLCDNumber(Debug);
	lcdNumber_senseHigh->setObjectName(QString::fromUtf8("lcdNumber_senseHigh"));
	lcdNumber_senseHigh->setSegmentStyle(QLCDNumber::Flat);

	horizontalLayout->addWidget(lcdNumber_senseHigh);

	lcdNumber_SenseMiddle = new QLCDNumber(Debug);
	lcdNumber_SenseMiddle->setObjectName(QString::fromUtf8("lcdNumber_SenseMiddle"));
	lcdNumber_SenseMiddle->setSegmentStyle(QLCDNumber::Flat);

	horizontalLayout->addWidget(lcdNumber_SenseMiddle);

	lcdNumber_SenseLow = new QLCDNumber(Debug);
	lcdNumber_SenseLow->setObjectName(QString::fromUtf8("lcdNumber_SenseLow"));
	lcdNumber_SenseLow->setSegmentStyle(QLCDNumber::Flat);

	horizontalLayout->addWidget(lcdNumber_SenseLow);


	formLayout->setLayout(11, QFormLayout::FieldRole, horizontalLayout);

	label_13 = new QLabel(Debug);
	label_13->setObjectName(QString::fromUtf8("label_13"));

	formLayout->setWidget(12, QFormLayout::LabelRole, label_13);

	lcdNumber_brightness = new QLCDNumber(Debug);
	lcdNumber_brightness->setObjectName(QString::fromUtf8("lcdNumber_brightness"));
	lcdNumber_brightness->setDigitCount(10);
	lcdNumber_brightness->setMode(QLCDNumber::Dec);
	lcdNumber_brightness->setSegmentStyle(QLCDNumber::Flat);
	lcdNumber_brightness->setProperty("value", QVariant(0.000000000000000));
	lcdNumber_brightness->setProperty("intValue", QVariant(0));

	formLayout->setWidget(12, QFormLayout::FieldRole, lcdNumber_brightness);


	verticalLayout->addLayout(formLayout);




}