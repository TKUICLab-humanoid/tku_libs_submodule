#include "tku_libs/RobotCupInfo.h"

std::string StrE::object[]    = {"soccer", "goal"};
std::string StrE::enemy[]     = {"enemy1", "enemy2", "enemy3", "enemy4"};
std::string StrE::robot[]     = {"robot1", "robot2", "robot3", "robot4"};
std::string StrE::character[] = {"myself", "attacker", "supporter1", "supporter2", "defender", "free", "null"};
std::string StrE::PRS[]       = {"RA", "R12", "R13", "R14", "R23", "R24", "R34", "R1", "R2", "R3", "R4", "R"};
unsigned int StrE::objectSize = sizeof(StrE::object)/sizeof(StrE::object[0]);
unsigned int StrE::enemySize = sizeof(StrE::enemy)/sizeof(StrE::enemy[0]);
unsigned int StrE::robotSize = sizeof(StrE::robot)/sizeof(StrE::robot[0]);
unsigned int StrE::characterSize = sizeof(StrE::character)/sizeof(StrE::character[0]);
unsigned int StrE::PRSSize = sizeof(StrE::PRS)/sizeof(StrE::PRS[0]);

RobotCupInfo *RobotCupInfo::m_pInstance;

RCObjectInfoBase::WhichData::WhichData()
{
    x_pos = 0;
    y_pos = 0;
    theta = 0.0;
}

RCObjectInfoBase::WhichData::~WhichData()
{

}

void RCObjectInfoBase::WhichData::initialize()
{
    x_pos = 0;
    y_pos = 0;
    theta = 0.0;
}

RCObjectInfoBase::RCObjectInfoBase()
{
    name = StrE::character[(int)ECharacter::null];
    exist_flag = false;
    global.initialize();
    local.initialize();
}

RCObjectInfoBase::~RCObjectInfoBase()
{

}

void RCObjectInfoBase::initialize()
{
    exist_flag = false;
    global.initialize();
    local.initialize();
}

RCObjectInfo::RCObjectInfo() : RCObjectInfoBase()
{

}

RCObjectInfo::~RCObjectInfo()
{

}

CharacterInfo::CharacterInfo() : RCObjectInfoBase()
{
    which_robot = "";
    RCObjectInfo objectTemp;
    for(int i = 0; i < StrE::objectSize; i++) 
    {
        objectTemp.name = StrE::object[i];
        object[StrE::object[i]] = objectTemp;
    }
    for(int i = 0; i < StrE::enemySize; i++)
    {
        objectTemp.name = StrE::enemy[i];
        enemy[StrE::enemy[i]] = objectTemp;
    }
}

CharacterInfo::~CharacterInfo()
{

}

void CharacterInfo::initialize()
{
    name = StrE::character[(int)ECharacter::null];
    exist_flag = false;
    global.initialize();
    local.initialize();
    for(std::map<std::string, RCObjectInfo>::iterator it = object.begin(); it != object.end(); it++)it->second.initialize();
    for(std::map<std::string, RCObjectInfo>::iterator it = enemy.begin(); it != enemy.end(); it++)it->second.initialize();  
}

NormalCharacterBase::NormalCharacterBase()
{
    CharacterInfo *characterTemp = new CharacterInfo[StrE::robotSize];
    for(int i = 0; i < StrE::robotSize; i++)
    {
        characterTemp[i].which_robot = StrE::robot[i];
        who[StrE::robot[i]] = &characterTemp[i];
    }
    TimeClass timeClassTemp;
    timeClassTemp.setTimerPass(3000, false);
    for(int i = 0; i < StrE::robotSize; i++)
    {
        callBackTimer[StrE::robot[i]] = timeClassTemp;
    }
}

NormalCharacterBase::~NormalCharacterBase()
{

}

void NormalCharacterBase::changeMyself(std::string name)
{
    who["myself"]->initialize();
    who["myself"]->name = name;
}

bool NormalCharacterBase::checkRobotCharacter()
{
    bool flag = true;
    if(who[StrE::robot[(int)ERobot::robot1]]->name == who[StrE::robot[(int)ERobot::robot2]]->name
     && (who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot1 and robot2 Character are %s", who[StrE::robot[(int)ERobot::robot1]]->name.c_str());
        ros::Duration(1).sleep();
    }
    if(who[StrE::robot[(int)ERobot::robot1]]->name == who[StrE::robot[(int)ERobot::robot3]]->name
     && (who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot1 and robot3 Character are %s", who[StrE::robot[(int)ERobot::robot1]]->name.c_str());
        ros::Duration(1).sleep();
    }
    if(who[StrE::robot[(int)ERobot::robot1]]->name == who[StrE::robot[(int)ERobot::robot4]]->name
     && (who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot1]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot1 and robot4 Character are %s", who[StrE::robot[(int)ERobot::robot1]]->name.c_str());
        ros::Duration(1).sleep();
    }
    if(who[StrE::robot[(int)ERobot::robot2]]->name == who[StrE::robot[(int)ERobot::robot3]]->name
     && (who[StrE::robot[(int)ERobot::robot2]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot2]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot2 and robot3 Character are %s", who[StrE::robot[(int)ERobot::robot2]]->name.c_str());
        ros::Duration(1).sleep();
    }
    if(who[StrE::robot[(int)ERobot::robot2]]->name == who[StrE::robot[(int)ERobot::robot4]]->name
     && (who[StrE::robot[(int)ERobot::robot2]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot2]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot2 and robot4 Character are %s", who[StrE::robot[(int)ERobot::robot2]]->name.c_str());
        ros::Duration(1).sleep();
    }
    if(who[StrE::robot[(int)ERobot::robot3]]->name == who[StrE::robot[(int)ERobot::robot4]]->name
     && (who[StrE::robot[(int)ERobot::robot3]]->name != StrE::character[(int)ECharacter::null] && who[StrE::robot[(int)ERobot::robot3]]->name != StrE::character[(int)ECharacter::free]))
    {
        flag = false;
        ROS_ERROR("RobotCharacter redefine, robot3 and robot4 Character are %s", who[StrE::robot[(int)ERobot::robot3]]->name.c_str());
        ros::Duration(1).sleep();
    }
    return flag;
}

std::string NormalCharacterBase::getPRS()
{
    std::string temp = "R";
    for(std::map<std::string, TimeClass>::iterator it = callBackTimer.begin(); it != callBackTimer.end(); it++)
    {
        if(it->first != who[StrE::character[(int)ECharacter::myself]]->which_robot)
        {
            if(it->second.checkTimePass())
            {
                who[it->first]->initialize();
            }
            else
            {
                temp += it->first[it->first.length()-1];
            }
        }
    }
    return temp;
}

void NormalCharacterBase::setTimerPass(double checkTimeMs, bool initFlag)
{
    for(std::map<std::string, TimeClass>::iterator it = callBackTimer.begin(); it != callBackTimer.end(); it++)
    {
        if(it->first != who[StrE::character[(int)ECharacter::myself]]->which_robot)
        {
            it->second.setTimerPass(checkTimeMs, initFlag);
        }
    }
}

void NormalCharacterBase::testShow()
{
    std::printf("\n");
    for(std::map<std::string, CharacterInfo*>::iterator it = who.begin(); it != who.end(); it++)
    {
        while(it->first == StrE::character[(int)ECharacter::myself]  || it->first == StrE::character[(int)ECharacter::attacker]
         || it->first == StrE::character[(int)ECharacter::supporter1] || it->first == StrE::character[(int)ECharacter::supporter2]
         || it->first == StrE::character[(int)ECharacter::defender]  || it->first == StrE::character[(int)ECharacter::free]
         || it->first == StrE::character[(int)ECharacter::null])
        {
            it++;
            if(it == who.end())return;
        }
        std::printf("%-10s {%-10sexist_flag = %-d, global[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f], local[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f]}\n"
        , it->second->which_robot.c_str(), it->second->name.c_str(), it->second->exist_flag
        , it->second->global.x_pos, it->second->global.y_pos, it->second->global.theta
        , it->second->local.x_pos, it->second->local.y_pos, it->second->local.theta);

        for(std::map<std::string, RCObjectInfo>::iterator itt = it->second->object.begin(); itt != it->second->object.end(); itt++)
        {
            std::printf("%-10s {%-10sexist_flag = %-d, global[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f], local[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f]}\n"
            , it->second->name.c_str(), itt->second.name.c_str(), itt->second.exist_flag
            , itt->second.global.x_pos, itt->second.global.y_pos, itt->second.global.theta
            , itt->second.local.x_pos, itt->second.local.y_pos, itt->second.local.theta);
        }
        for(std::map<std::string, RCObjectInfo>::iterator itt = it->second->enemy.begin(); itt != it->second->enemy.end(); itt++)
        {
            std::printf("%-10s {%-10sexist_flag = %-d, global[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f], local[ x_pos = %-10d, y_pos = %-10d, theta = %-8.2f]}\n"
            , it->second->name.c_str(), itt->second.name.c_str(), itt->second.exist_flag
            , itt->second.global.x_pos, itt->second.global.y_pos, itt->second.global.theta
            , itt->second.local.x_pos, itt->second.local.y_pos, itt->second.local.theta);
        }
    }
}

void NormalCharacterBase::testShowTimer()
{
    for(int i = 0; i < StrE::robotSize; i++)
    {
        ROS_INFO("%s timer = %f", StrE::robot[i].c_str(), callBackTimer[StrE::robot[i]].getTimeMs());
    }
}

NormalCharacter::NormalCharacter() : NormalCharacterBase()
{

}

NormalCharacter::~NormalCharacter()
{

}

RobotCupInfoBase::RobotCupInfoBase()
{
    characterInfo = new NormalCharacter();
    std::string strTemp = "rosparam load " + ros::package::getPath("strategy") + "/Parameter/RobotCupInfo.yaml /robotCupInfo";
    system(strTemp.c_str());
    if (nh.getParam("/robotCupInfo", paramData) && paramData.getType() == XmlRpc::XmlRpcValue::TypeArray)
    {
        std::string which_robot = (std::string)paramData[0]["state"]["which_robot"];
        if(which_robot == StrE::robot[(int)ERobot::robot1] || which_robot == StrE::robot[(int)ERobot::robot2]
         || which_robot == StrE::robot[(int)ERobot::robot3] || which_robot == StrE::robot[(int)ERobot::robot4])
        {
            for(int i = 0; i < StrE::robotSize; i++)
            {
                characterInfo->who[StrE::robot[i]]->name = (std::string)paramData[0]["state"][StrE::robot[i]];
                topicNames[StrE::robot[i]] = (std::string)paramData[0]["topic"][StrE::robot[i]];
            }
            characterInfo->who[StrE::character[(int)ECharacter::myself]] = characterInfo->who[which_robot];
        }
        else
        {
            ROS_ERROR("which_robot name = %s", which_robot.c_str());
            ROS_ERROR("Correct which_robot name is robot1 or robot2 or robot3 or robot4");
            ROS_INFO("Please Ctrl+C to exit");
            while(ros::ok());
        }
    }
}

RobotCupInfoBase::~RobotCupInfoBase()
{
    delete characterInfo;
}

void RobotCupInfoBase::initialize()
{
    
}

RobotCupInfo::RobotCupInfo() : RobotCupInfoBase()
{
    m_pInstance = nullptr;
}

RobotCupInfo::~RobotCupInfo()
{

}

RobotCupInfo* RobotCupInfo::getInstance()
{
    if(!m_pInstance)m_pInstance = new RobotCupInfo();
    return m_pInstance;
}

void RobotCupInfo::deleteInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}
