#ifndef TOOL_H
#define TOOL_H

#include <ros/ros.h>
#include <ros/package.h>
#include <sys/time.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#define STANDPATH "/home/iclab/Desktop/Standmotion"

using namespace std;

class Tool
{
    public:
        Tool();
        ~Tool();

        string getPackagePath(string package_name);
        float readvalue(fstream &fin, string title,int mode);
        void Delay(int timedelay);
	private:
		string package_path;
        // string PATH;
};

class ToolInstance : public Tool
{
	public:
		ToolInstance() : Tool(){}
		~ToolInstance(){}
		static ToolInstance* getInstance();
		static void deleteInstance();

	private:
		static ToolInstance *m_pInstance;
};

class TimeClass
{
    public:
        TimeClass(double check_time_ms);
        TimeClass();
        ~TimeClass();
        void updateTime();
        void initialize();
        void setTimerPass(double check_time_ms, bool init_flag = true);
        double getTimeMs();
		double getPeriodTimeMs();
        bool checkTimePass();

    private:
        double start = 0;
        double end = 0;
        double time_ms = 0;
        double check_time_ms = 1000;
};
// extern Tool* tool;

#endif // TOOL_H
