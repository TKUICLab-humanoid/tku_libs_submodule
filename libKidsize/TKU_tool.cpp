#include "tku_libs/TKU_tool.h"

ToolInstance *ToolInstance::m_pInstance;

Tool::Tool()
{

}

Tool::~Tool()
{

}

string Tool::getPackagePath(string package_name)
{
	package_path = ros::package::getPath(package_name);
	printf("package_path is %s\n", package_path.c_str());
	if(package_path.empty())
	{
		printf("Tool getPath is empty\n");
		return "N";
	} 
	return package_path + "/Parameter";
}

float Tool::readvalue(fstream &fin, string title, int mode)
{
    char line[100];
    char equal;
    string sline, sbuffer;
    switch(mode)
    {
        case 0:
            do
            {
                fin.getline(line,sizeof(line));
                sline = line;
            }
            while(sline == "---" || sline == "");
            if(sline.size() > title.size() && sline.find(title) != -1)
            {
                sbuffer = sline.substr(sline.find(title), title.size());
                if(sline.find(" = ") != -1)
                {
                    if(sline.size() > title.size()+3)
                    {
                        sline.erase(0, title.size()+3);
                        return atoi(sline.c_str());
                    }
                    else
                    {
                        std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                        std::printf("\033[0;31mPlease check your read file!!\033[0m\n");
                    }
                }
                else
                {
                    std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                    std::printf("\033[0;31mPlease check '=' after and befor must need space!!\033[0m\n");
                    std::printf("\033[0;33m%s\033[0m\n", sline.c_str());
                }
            }
            else
            {
                std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                std::printf("\033[0;31mPlease check your cpp and ini!!\033[0m\n");
                std::printf("\033[0;33mcpp str name is %s\033[0m\n", title.c_str());
                std::printf("\033[0;33mini str name is %s\033[0m\n", sline.c_str());             
            }
            exit(1);
            break;
        case 1:
            do
            {
                fin.getline(line,sizeof(line));
                sline = line;
            }
            while(sline == "---" || sline == "");
            if(sline.size() > title.size() && sline.find(title) != -1)
            {
                sbuffer = sline.substr(sline.find(title), title.size());
                if(sline.find(" = ") != -1)
                {
                    if(sline.size() > title.size()+3)
                    {
                        sline.erase(0, title.size()+3);
                        return atof(sline.c_str());
                    }
                    else
                    {
                        std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                        std::printf("\033[0;31mPlease check your read file!!\033[0m\n");
                    }
                }
                else
                {
                    std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                    std::printf("\033[0;31mPlease check '=' after and befor must need space!!\033[0m\n");
                    std::printf("\033[0;33m%s\033[0m\n", sline.c_str());
                }
            }
            else
            {
                std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
                std::printf("\033[0;31mPlease check your cpp and ini!!\033[0m\n");
                std::printf("\033[0;33mcpp str name is %s\033[0m\n", title.c_str());
                std::printf("\033[0;33mini str name is %s\033[0m\n", sline.c_str());            
            }
            exit(1);
            break;
        case 2:
        case 4:
            fin.getline(line,sizeof(line),' ');
            if((string)line == title)
            {
                fin.get(equal);
                if(equal == '=')
                {
                    fin.getline(line,sizeof(line),'|');
                    return atoi(line);
                }
            }
            std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
            std::printf("\033[0;31mPlease check your read file!!\033[0m\n");
            if(mode == 2)
            {
                exit(1);
            }
            else
            {
                return -1;
            }
            break;
        case 3:
        case 5:
            fin.getline(line,sizeof(line),' ');
            if((string)line == title)
            {
                fin.getline(line,sizeof(line),'|');
                return atoi(line);
            }
            std::printf("\033[0;31mreadvalue() Error!!\033[0m\n");
            std::printf("\033[0;31mPlease check your read file!!\033[0m\n");
            if(mode == 3)
            {
                exit(1);
            }
            else
            {
                return -1;
            }
            break;
        default:
            break;
    }
}

void Tool::Delay(int timedelay)
{
    double timeuse;
    struct timeval tstart, tend;
    gettimeofday(&tstart, NULL);
    gettimeofday(&tend, NULL);
    timeuse = (1000000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_usec - tstart.tv_usec))/1000;
    while (timeuse <= timedelay) {
        gettimeofday(&tend, NULL);
        timeuse = (1000000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_usec - tstart.tv_usec))/1000;
    }
}

ToolInstance::ToolInstance() : Tool()
{
    m_pInstance = nullptr;
}

ToolInstance::~ToolInstance()
{

}

ToolInstance* ToolInstance::getInstance()
{
    if(!m_pInstance)m_pInstance = new ToolInstance();
    return m_pInstance;
}

void ToolInstance::deleteInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

TimeClass::TimeClass()
{
    start = 0;
    end = 0;
    timeMs = 0;
    checkTimeMs = 1000;
}

TimeClass::TimeClass(double checkTimeMs)
{
    start = 0;
    end = 0;
    timeMs = 0;
	this->checkTimeMs = checkTimeMs;
}

TimeClass::~TimeClass()
{

}

void TimeClass::initialize()
{
    start = ros::WallTime::now().toSec();
    end = start;
    timeMs = 0;
}

void TimeClass::setTimerPass(double checkTimeMs, bool initFlag)
{
    if(initFlag)initialize();
    this->checkTimeMs = checkTimeMs;
}

void TimeClass::updateTime()
{
    end = ros::WallTime::now().toSec();
    timeMs = 1000.0 * (end - start);
}

double TimeClass::getPeriodTimeMs()
{
	return checkTimeMs;
}

double TimeClass::getTimeMs()
{
    updateTime();
    return timeMs;
}

bool TimeClass::checkTimePass()
{
    if(getTimeMs() > checkTimeMs)
    {
        return true;
    }
    else
    {
        return false;
    }
}
