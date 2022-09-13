#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QByteArray>
#include <boost/log/trivial.hpp>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>


#include "plugins/vehicle_plugin.hpp"
#include "app/widgets/climate.hpp"
#include "app/arbiter.hpp"
#include "openauto/Service/InputService.hpp"


#define SAAB_LOG(severity) BOOST_LOG_TRIVIAL(severity) << "[SAABVehiclePlugin] "


class DebugWindow : public QWidget {
    Q_OBJECT

    public:
        DebugWindow(Arbiter &arbiter, QWidget *parent = nullptr);
        QVBoxLayout *verticalLayout;
		QFormLayout *formLayout;
		QLabel *label_2;
		QFrame *line;
		QLabel *label_3;
		QLCDNumber *lcdNumber_volup;
		QLabel *label_4;
		QLCDNumber *lcdNumber_voldown;
		QLabel *label;
		QLCDNumber *lcdNumber_source;
		QLabel *label_6;
		QLCDNumber *lcdNumber_talk;
		QLabel *label_5;
		QLCDNumber *lcdNumber_seekup;
		QLabel *label_7;
		QLCDNumber *lcdNumber_seekdown;
		QLabel *label_8;
		QLCDNumber *lcdNumber_next;
		QLabel *label_9;
		QLCDNumber *lcdNumber_hangup;
		QLabel *label_10;
		QFrame *line_2;
		QLabel *label_11;
		QLCDNumber *lcdNumber_spadist;
		QLabel *label_12;
		QHBoxLayout *horizontalLayout;
		QLCDNumber *lcdNumber_senseHigh;
		QLCDNumber *lcdNumber_SenseMiddle;
		QLCDNumber *lcdNumber_SenseLow;
		QLabel *label_13;
		QLCDNumber *lcdNumber_brightness;

};

class SAAB93 : public QObject, VehiclePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VehiclePlugin_iid)
    Q_INTERFACES(VehiclePlugin)

    public:
        bool init(ICANBus* canbus) override;

    private:
        QList<QWidget *> widgets() override;

        
		//SAAB GMCAN
		void handleMsgSteeringWheel(QByteArray payload); //290 
		void handleMsgDriverDoor(QByteArray payload); //320
		void handleMsgGuages(QByteArray payload); //108
		void handleMsgLightSwitch(QByteArray payload); //300
		void handleMsgBright(QByteArray payload); //460 
		void handleMsgSpaDist(QByteArray payload); //183 
		void handleMsgParkSensorDist(QByteArray payload); //180 



        Climate *climate;
        DebugWindow *debug;
        bool engineRunning = false;
};