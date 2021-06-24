#include "tku_libs/Ros2MultiCommunication.h"

Ros2MultiCommunication *Ros2MultiCommunication::m_pInstance;

Ros2MultiCommunicationBase::Ros2MultiCommunicationBase()
{
    robotCupInfo = RobotCupInfo::getInstance();
    if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot == StrE::robot[(int)ERobot::robot1])
    {
        robotsPub[StrE::robot[(int)ERobot::robot1]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot2]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10, &Ros2MultiCommunicationBase::callBackRobot2, this);
        robotsSub[StrE::robot[(int)ERobot::robot3]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10, &Ros2MultiCommunicationBase::callBackRobot3, this);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot == StrE::robot[(int)ERobot::robot2])
    {
        robotsSub[StrE::robot[(int)ERobot::robot1]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10, &Ros2MultiCommunicationBase::callBackRobot1, this);
        robotsPub[StrE::robot[(int)ERobot::robot2]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot3]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10, &Ros2MultiCommunicationBase::callBackRobot3, this);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot == StrE::robot[(int)ERobot::robot3])
    {
        robotsSub[StrE::robot[(int)ERobot::robot1]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10, &Ros2MultiCommunicationBase::callBackRobot1, this);
        robotsSub[StrE::robot[(int)ERobot::robot2]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10, &Ros2MultiCommunicationBase::callBackRobot2, this);
        robotsPub[StrE::robot[(int)ERobot::robot3]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot == StrE::robot[(int)ERobot::robot4])
    {
        robotsSub[StrE::robot[(int)ERobot::robot1]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10, &Ros2MultiCommunicationBase::callBackRobot1, this);
        robotsSub[StrE::robot[(int)ERobot::robot2]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10, &Ros2MultiCommunicationBase::callBackRobot2, this);
        robotsSub[StrE::robot[(int)ERobot::robot3]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10, &Ros2MultiCommunicationBase::callBackRobot3, this);
        robotsPub[StrE::robot[(int)ERobot::robot4]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10);
    }
    initialized = true;
}

Ros2MultiCommunicationBase::~Ros2MultiCommunicationBase()
{

}

bool Ros2MultiCommunicationBase::Initialized()
{
    if(!initialized)ROS_ERROR("Did you forget to initialize for Ros2MultiCommunicationBase?");
    return initialized;
}

void Ros2MultiCommunicationBase::sendRobotCupInfo(RobotCupInfo *robotCupInfo)
{
    tku_msgs::CharacterInfo characterTemp;
    tku_msgs::RCObjectInfo objectTemp;
    tku_msgs::RCObjectInfo partnerTemp;
    tku_msgs::RCObjectInfo enemyTemp;
    tku_msgs::Ros2MultiCommunication myself;

    characterTemp.which_robot = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot;
    characterTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->name;
    characterTemp.weight = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->weight;
    characterTemp.global.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->global.x_pos;
    characterTemp.global.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->global.y_pos;
    characterTemp.global.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->global.theta;
    characterTemp.local.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->local.x_pos;
    characterTemp.local.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->local.y_pos;
    characterTemp.local.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->local.theta;
    
    for(int i = 0; i < StrE::objectSize; i++)
    {
        objectTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].name;
        objectTemp.exist_flag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].exist_flag;
        objectTemp.global.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].global.x_pos;
        objectTemp.global.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].global.y_pos;
        objectTemp.global.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].global.theta;
        objectTemp.local.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].local.x_pos;
        objectTemp.local.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].local.y_pos;
        objectTemp.local.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].local.theta;
        characterTemp.object.push_back(objectTemp);
    }

    for(int i = 0; i < StrE::robotSize; i++)
    {
        partnerTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].name;
        partnerTemp.exist_flag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].exist_flag;
        partnerTemp.global.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].global.x_pos;
        partnerTemp.global.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].global.y_pos;
        partnerTemp.global.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].global.theta;
        partnerTemp.local.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].local.x_pos;
        partnerTemp.local.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].local.y_pos;
        partnerTemp.local.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->partner[StrE::robot[i]].local.theta;
        characterTemp.partner.push_back(partnerTemp);
    }
    
    for(int i = 0; i < StrE::enemySize; i++)
    {
        enemyTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].name;
        enemyTemp.exist_flag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].exist_flag;
        enemyTemp.global.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].global.x_pos;
        enemyTemp.global.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].global.y_pos;
        enemyTemp.global.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].global.theta;
        enemyTemp.local.x_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].local.x_pos;
        enemyTemp.local.y_pos = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].local.y_pos;
        enemyTemp.local.theta = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].local.theta;
        characterTemp.enemy.push_back(enemyTemp);
    }

    myself.who.push_back(characterTemp);
    robotsPub[robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->which_robot].publish(myself);
}

void Ros2MultiCommunicationBase::saveCallBackData(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    for(int i = 0; i < unknownRobot.who.size(); i++)
    {
        if(unknownRobot.who[i].name != StrE::character[(int)ECharacter::attacker] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::supporter1] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::supporter2]
         && unknownRobot.who[i].name != StrE::character[(int)ECharacter::defender] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::free] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::null])break;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->which_robot = unknownRobot.who[i].which_robot;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->name = unknownRobot.who[i].name;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->weight = unknownRobot.who[i].weight;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->global.x_pos = unknownRobot.who[i].global.x_pos;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->global.y_pos = unknownRobot.who[i].global.y_pos;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->global.theta = unknownRobot.who[i].global.theta;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->local.x_pos = unknownRobot.who[i].local.x_pos;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->local.y_pos = unknownRobot.who[i].local.y_pos;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->local.theta = unknownRobot.who[i].local.theta;
        
        for(int j = 0; j < unknownRobot.who[i].object.size(); j++)
        {
            if(unknownRobot.who[i].object[j].name == "null")break;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].name = unknownRobot.who[i].object[j].name;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].exist_flag = unknownRobot.who[i].object[j].exist_flag;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].global.x_pos = unknownRobot.who[i].object[j].global.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].global.y_pos = unknownRobot.who[i].object[j].global.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].global.theta = unknownRobot.who[i].object[j].global.theta;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].local.x_pos = unknownRobot.who[i].object[j].local.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].local.y_pos = unknownRobot.who[i].object[j].local.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->object[unknownRobot.who[i].object[j].name].local.theta = unknownRobot.who[i].object[j].local.theta;
        }

        for(int j = 0; j < unknownRobot.who[i].partner.size(); j++)
        {
            if(unknownRobot.who[i].partner[j].name == "null")break;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].name = unknownRobot.who[i].partner[j].name;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].exist_flag = unknownRobot.who[i].partner[j].exist_flag;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].global.x_pos = unknownRobot.who[i].partner[j].global.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].global.y_pos = unknownRobot.who[i].partner[j].global.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].global.theta = unknownRobot.who[i].partner[j].global.theta;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].local.x_pos = unknownRobot.who[i].partner[j].local.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].local.y_pos = unknownRobot.who[i].partner[j].local.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->partner[unknownRobot.who[i].partner[j].name].local.theta = unknownRobot.who[i].partner[j].local.theta;
        }

        for(int j = 0; j < unknownRobot.who[i].enemy.size(); j++)
        {
            if(unknownRobot.who[i].enemy[j].name == "null")break;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].name = unknownRobot.who[i].enemy[j].name;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].exist_flag = unknownRobot.who[i].enemy[j].exist_flag;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].global.x_pos = unknownRobot.who[i].enemy[j].global.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].global.y_pos = unknownRobot.who[i].enemy[j].global.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].global.theta = unknownRobot.who[i].enemy[j].global.theta;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].local.x_pos = unknownRobot.who[i].enemy[j].local.x_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].local.y_pos = unknownRobot.who[i].enemy[j].local.y_pos;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].which_robot]->enemy[unknownRobot.who[i].enemy[j].name].local.theta = unknownRobot.who[i].enemy[j].local.theta;
        }
    }
}

void Ros2MultiCommunicationBase::callBackRobot1(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    saveCallBackData(unknownRobot);
    robotCupInfo->characterInfo->callBackTimer[StrE::robot[(int)ERobot::robot1]].initialize();
}

void Ros2MultiCommunicationBase::callBackRobot2(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    saveCallBackData(unknownRobot);
    robotCupInfo->characterInfo->callBackTimer[StrE::robot[(int)ERobot::robot2]].initialize();
}

void Ros2MultiCommunicationBase::callBackRobot3(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    saveCallBackData(unknownRobot);
    robotCupInfo->characterInfo->callBackTimer[StrE::robot[(int)ERobot::robot3]].initialize();
}

void Ros2MultiCommunicationBase::callBackRobot4(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    saveCallBackData(unknownRobot);
    robotCupInfo->characterInfo->callBackTimer[StrE::robot[(int)ERobot::robot4]].initialize();
}

Ros2MultiCommunication::Ros2MultiCommunication() : Ros2MultiCommunicationBase()
{
    m_pInstance = nullptr;
}

Ros2MultiCommunication::~Ros2MultiCommunication()
{

}

Ros2MultiCommunication* Ros2MultiCommunication::getInstance()
{
    if(!m_pInstance)m_pInstance = new Ros2MultiCommunication();
    return m_pInstance;
}

void Ros2MultiCommunication::deleteInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

bool Ros2MultiCommunication::Initialized()
{
    if(!initialized)ROS_ERROR("Did you forget to initialize for Ros2MultiCommunication?");
    return initialized;
}
