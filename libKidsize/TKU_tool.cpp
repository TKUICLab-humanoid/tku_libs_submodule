#include "tku_libs/TKU_tool.h"
// Tool* tool = new Tool;
ToolInstance* ToolInstance::m_pInstance;

Tool::Tool()
{

}

Tool::~Tool()
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
        m_pInstance = NULL;
    }
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
                        std::printf("\033[0;31mreadvalue() error\033[0m\n");
                    }
                }
                else
                {
                    std::printf("\033[0;31mplease check '=' after and befor must need space\033[0m\n");
                    std::printf("\033[0;33m%s\033[0m\n", sline.c_str());
                    std::printf("\033[0;31mplease ctrl c\033[0m\n");
                }
            }
            else
            {
                std::printf("\033[0;31mplease check your cpp and ini\033[0m\n");
                std::printf("\033[0;33mcpp str name is %s\033[0m\n", title.c_str());
                std::printf("\033[0;33mini str name is %s\033[0m\n", sline.c_str());
                std::printf("\033[0;31mplease ctrl c\033[0m\n");                
            }
            ros::WallDuration(1).sleep();
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
                        std::printf("\033[0;31mreadvalue() error\033[0m\n");
                    }
                }
                else
                {
                    std::printf("\033[0;31mplease check '=' after and befor must need space\033[0m\n");
                    std::printf("\033[0;33m%s\033[0m\n", sline.c_str());
                    std::printf("\033[0;31mplease ctrl c\033[0m\n");
                }
            }
            else
            {
                std::printf("\033[0;31mplease check your cpp and ini\033[0m\n");
                std::printf("\033[0;33mcpp str name is %s\033[0m\n", title.c_str());
                std::printf("\033[0;33mini str name is %s\033[0m\n", sline.c_str());
                std::printf("\033[0;31mplease ctrl c\033[0m\n");                
            }
            ros::WallDuration(1).sleep();
            break;
        case 2:
            while(1)
            {
                fin.getline(line,sizeof(line),' ');
                if((string)line == title)
                {
                    fin.get(equal);
                    if(equal == '=')
                    {
                        fin.getline(line,sizeof(line),'|');
                        break;
                    }
                }
            }
            return atoi(line);
            break;
        case 3:
            while(1)
            {
                fin.getline(line,sizeof(line),' ');
                if((string)line == title)
                {
                    fin.getline(line,sizeof(line),'|');
                    break;
                }
            }
            return atoi(line);
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

TimeClass::TimeClass(double check_time_ms)
{
	this->check_time_ms = check_time_ms;
}

TimeClass::TimeClass()
{
	// initialize();
}

TimeClass::~TimeClass()
{

}

void TimeClass::updateTime()
{
	end = ros::WallTime::now().toSec();
	time_ms = 1000.0*(end - start);
}

void TimeClass::initialize()
{
	start = ros::WallTime::now().toSec();
	end = start;
	time_ms = 0;
}

void TimeClass::setTimerPass(double check_time_ms, bool init_flag)
{
	this->check_time_ms = check_time_ms;
	if (init_flag)initialize();
}

double TimeClass::getTimeMs()
{
	updateTime();
	return time_ms;
}

bool TimeClass::checkTimePass()
{
	if (getTimeMs() > check_time_ms)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double TimeClass::getPeriodTimeMs()
{
	return check_time_ms;
}

