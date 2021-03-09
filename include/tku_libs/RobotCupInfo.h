#ifndef ROBOTCUPINFO_H
#define ROBOTCUPINFO_H

#include <string>
#include <ros/node_handle.h>
#include <ros/package.h>
#include <map>

#include "tku_libs/TKU_tool.h"

enum class EObject {soccer, goal};
enum class EEnemy {enemy1, enemy2, enemy3, enemy4};
enum class ERobot {robot1, robot2, robot3, robot4};
enum class ECharacter {myself, attacker, supporter1, supporter2, defender, free, null};
enum class PRS {RA, R12, R13, R14, R23, R24, R34, R1, R2, R3, R4, R};
//PRS = Partner Robot State

class StrE
{
    public:
        StrE(){}
        ~StrE(){}

    public:
        static std::string object[];
        static std::string enemy[];
        static std::string robot[];
        static std::string character[];
        static std::string PRS[];
        static unsigned int objectSize;
        static unsigned int enemySize;
        static unsigned int robotSize;
        static unsigned int characterSize;
        static unsigned int PRSSize;
};

class RCObjectInfoBase
{
    class WhichData
    {
        public:
            WhichData();
            ~WhichData();

            void initialize();

        public:
            int x_pos;
            int y_pos;
            float theta;
    };

    public:
        RCObjectInfoBase();
        ~RCObjectInfoBase();

        virtual void initialize();

    public:
        std::string name;
        bool exist_flag;
        WhichData global;
        WhichData local;
};

class RCObjectInfo : public RCObjectInfoBase
{
	public:
        RCObjectInfo();
        ~RCObjectInfo();
};

class CharacterInfo : public RCObjectInfoBase
{
	public:
        CharacterInfo();
        ~CharacterInfo();

        virtual void initialize() override;

    public:
        std::string which_robot;
        std::map<std::string, RCObjectInfo> object;
        std::map<std::string, RCObjectInfo> enemy;
};

class NormalCharacterBase
{
    public:
        friend class Ros2MultiCommunicationBase;

    public:
        NormalCharacterBase();
        ~NormalCharacterBase();

        void changeMyself(std::string name);
        bool checkRobotCharacter();
        std::string getPRS();
        void setTimerPass(double checkTimeMs, bool initFlag = true);
        void testShow();
        void testShowTimer();

    public:
        std::map<std::string, CharacterInfo*> who;

    private:
        std::map<std::string, TimeClass> callBackTimer;
};

class NormalCharacter : public NormalCharacterBase
{
    public:
        NormalCharacter();
        ~NormalCharacter();
};

class RobotCupInfoBase
{
    public:
        RobotCupInfoBase();
        ~RobotCupInfoBase();

        void initialize();

    public:
        NormalCharacter *characterInfo;
        std::map<std::string, std::string> topicNames;

    private:
        ros::NodeHandle nh;
        XmlRpc::XmlRpcValue paramData;
};

class RobotCupInfo : public RobotCupInfoBase
{
    public:
        RobotCupInfo();
        ~RobotCupInfo();
        static RobotCupInfo* getInstance();
        static void deleteInstance();

    private:
        static RobotCupInfo *m_pInstance;
};

#endif