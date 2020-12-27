#include "tku_libs/Ros2MultiCommunication.h"

Ros2MultiCommunication* Ros2MultiCommunication::m_pInstance;

Ros2MultiCommunicationBase::Ros2MultiCommunicationBase()
{
    robotCupInfo = RobotCupInfo::getInstance();
    if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot == StrE::robot[(int)ERobot::robot1])
    {
        robotsPub[StrE::robot[(int)ERobot::robot1]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot2]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10, &Ros2MultiCommunicationBase::callBackRobot2, this);
        robotsSub[StrE::robot[(int)ERobot::robot3]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10, &Ros2MultiCommunicationBase::callBackRobot3, this);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot == StrE::robot[(int)ERobot::robot2])
    {
        robotsSub[StrE::robot[(int)ERobot::robot1]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10, &Ros2MultiCommunicationBase::callBackRobot1, this);
        robotsPub[StrE::robot[(int)ERobot::robot2]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot3]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10, &Ros2MultiCommunicationBase::callBackRobot3, this);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot == StrE::robot[(int)ERobot::robot3])
    {
        robotsSub[StrE::robot[(int)ERobot::robot1]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot1]], 10, &Ros2MultiCommunicationBase::callBackRobot1, this);
        robotsSub[StrE::robot[(int)ERobot::robot2]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot2]], 10, &Ros2MultiCommunicationBase::callBackRobot2, this);
        robotsPub[StrE::robot[(int)ERobot::robot3]] = nh.advertise<tku_msgs::Ros2MultiCommunication>(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot3]], 10);
        robotsSub[StrE::robot[(int)ERobot::robot4]] = nh.subscribe(robotCupInfo->topicNames[StrE::robot[(int)ERobot::robot4]], 10, &Ros2MultiCommunicationBase::callBackRobot4, this);
    }
    else if(robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot == StrE::robot[(int)ERobot::robot4])
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
    tku_msgs::ObjectInfo enemyTemp;
    tku_msgs::ObjectInfo objectTemp;
    tku_msgs::CharacterInfo characterTemp;
    tku_msgs::Ros2MultiCommunication myself;

    characterTemp.whichRobot = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot;
    characterTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->name;
    characterTemp.x = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->x;
    characterTemp.y = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->y;
    characterTemp.existFlag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->existFlag;
    characterTemp.theta.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->theta.local;
    characterTemp.theta.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->theta.global;
    characterTemp.dist.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->dist.local;
    characterTemp.dist.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->dist.global;

    for(int i = 0; i < StrE::objectSize; i++)
    {
        objectTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].name;
        objectTemp.x = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].x;
        objectTemp.y = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].y;
        objectTemp.existFlag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].existFlag;
        objectTemp.theta.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].theta.local;
        objectTemp.theta.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].theta.global;
        objectTemp.dist.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].dist.local;
        objectTemp.dist.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->object[StrE::object[i]].dist.global;
        characterTemp.object.push_back(objectTemp);
    }
    
    for(int i = 0; i < StrE::enemySize; i++)
    {
        enemyTemp.name = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].name;
        enemyTemp.x = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].x;
        enemyTemp.y = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].y;
        enemyTemp.existFlag = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].existFlag;
        enemyTemp.theta.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].theta.local;
        enemyTemp.theta.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].theta.global;
        enemyTemp.dist.local = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].dist.local;
        enemyTemp.dist.global = robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->enemy[StrE::enemy[i]].dist.global;
        characterTemp.enemy.push_back(enemyTemp);
    }

    myself.who.push_back(characterTemp);
    robotsPub[robotCupInfo->characterInfo->who[StrE::character[(int)ECharacter::myself]]->whichRobot].publish(myself);
}

void Ros2MultiCommunicationBase::saveCallBackData(const tku_msgs::Ros2MultiCommunication& unknownRobot)
{
    for(int i = 0; i < unknownRobot.who.size(); i++)
    {
        if(unknownRobot.who[i].name != StrE::character[(int)ECharacter::attacker] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::suporter1] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::suporter2]
         && unknownRobot.who[i].name != StrE::character[(int)ECharacter::defender] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::free] && unknownRobot.who[i].name != StrE::character[(int)ECharacter::null])break;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->whichRobot = unknownRobot.who[i].whichRobot;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->name = unknownRobot.who[i].name;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->x = unknownRobot.who[i].x;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->y = unknownRobot.who[i].y;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->existFlag = unknownRobot.who[i].existFlag;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->theta.local = unknownRobot.who[i].theta.local;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->theta.global = unknownRobot.who[i].theta.global;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->dist.local = unknownRobot.who[i].dist.local;
        robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->dist.global = unknownRobot.who[i].dist.global;
        for(int j = 0; j < unknownRobot.who[i].enemy.size(); j++)
        {
            if(unknownRobot.who[i].enemy[j].name == "null")break;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].name = unknownRobot.who[i].enemy[j].name;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].x = unknownRobot.who[i].enemy[j].x;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].y = unknownRobot.who[i].enemy[j].y;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].existFlag = unknownRobot.who[i].enemy[j].existFlag;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].theta.local = unknownRobot.who[i].enemy[j].theta.local;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].theta.global = unknownRobot.who[i].enemy[j].theta.global;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].dist.local = unknownRobot.who[i].enemy[j].dist.local;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->enemy[unknownRobot.who[i].enemy[j].name].dist.global = unknownRobot.who[i].enemy[j].dist.global;
        }
        for(int j = 0; j < unknownRobot.who[i].object.size(); j++)
        {
            if(unknownRobot.who[i].object[j].name == "null")break;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].name = unknownRobot.who[i].object[j].name;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].x = unknownRobot.who[i].object[j].x;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].y = unknownRobot.who[i].object[j].y;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].existFlag = unknownRobot.who[i].object[j].existFlag;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].theta.local = unknownRobot.who[i].object[j].theta.local;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].theta.global = unknownRobot.who[i].object[j].theta.global;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].dist.local = unknownRobot.who[i].object[j].dist.local;
            robotCupInfo->characterInfo->who[unknownRobot.who[i].whichRobot]->object[unknownRobot.who[i].object[j].name].dist.global = unknownRobot.who[i].object[j].dist.global;
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
