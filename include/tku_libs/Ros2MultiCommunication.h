#ifndef ROS2MULTICOMMUNICATION_H
#define ROS2MULTICOMMUNICATION_H
#include <ros/node_handle.h>
#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/time_synchronizer.h>
#include <map>
#include <vector>
#include "tku_libs/RobotCupInfo.h"
#include "tku_msgs/Ros2MultiCommunication.h"

class Ros2MultiCommunicationBase
{
    public:
        Ros2MultiCommunicationBase();
        ~Ros2MultiCommunicationBase();

        virtual bool Initialized();
        void sendRobotCupInfo(RobotCupInfo *robotCupInfo);

    protected:
        void saveCallBackData(const tku_msgs::Ros2MultiCommunication&);
        void callBackRobot1(const tku_msgs::Ros2MultiCommunication&);
        void callBackRobot2(const tku_msgs::Ros2MultiCommunication&);
        void callBackRobot3(const tku_msgs::Ros2MultiCommunication&);
        void callBackRobot4(const tku_msgs::Ros2MultiCommunication&);

    private:
        ros::NodeHandle nh;
        std::map<std::string, ros::Publisher> robotsPub;
        std::map<std::string, ros::Subscriber> robotsSub;

	protected:
        bool initialized;
        RobotCupInfo *robotCupInfo;
};

class Ros2MultiCommunication : public Ros2MultiCommunicationBase
{
    public:
        Ros2MultiCommunication();
        ~Ros2MultiCommunication();

        //using get rosparam to set topic name
        static Ros2MultiCommunication* getInstance();
        static void deleteInstance();
		virtual bool Initialized() override;

	private:
        static Ros2MultiCommunication *m_pInstance;
};

#endif