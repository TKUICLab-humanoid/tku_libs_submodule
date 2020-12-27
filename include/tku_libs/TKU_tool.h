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
};

class ToolInstance : public Tool
{
	public:
		ToolInstance();
		~ToolInstance();
		static ToolInstance* getInstance();
		static void deleteInstance();

	private:
		static ToolInstance *m_pInstance;
};

class TimeClass
{
    public:
        TimeClass();
		TimeClass(double checkTimeMs);
        ~TimeClass();

        void initialize();
        void setTimerPass(double checkTimeMs, bool initFlag = true);
        void updateTime();
		double getPeriodTimeMs();
        double getTimeMs();
        bool checkTimePass();

    private:
        double start;
        double end;
        double timeMs;
        double checkTimeMs;
};

#endif // TOOL_H
