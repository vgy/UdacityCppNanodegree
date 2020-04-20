#include <map>
#include <string>
#include <iostream>
#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    cpuInfoValues =  LinuxParser::CpuUtilization();
    for (int i = 0; i < 10; i++)
    {
        cpuInfo.insert(std::pair<std::string, int>(cpuInfoLabels[i], stoi(cpuInfoValues[i])));
    }
    cpuInfo["user"] = cpuInfo["user"] - cpuInfo["guest"];
    cpuInfo["nice"] = cpuInfo["nice"] - cpuInfo["guest_nice"];
    idle = (cpuInfo["idle"] + cpuInfo["ioWait"]);
    nonIdle = (cpuInfo["user"] + cpuInfo["nice"] + cpuInfo["system"] + cpuInfo["irq"] + cpuInfo["softirq"] + cpuInfo["steal"]);
    total = idle + nonIdle;
    cpuUtilization= (float)nonIdle/(float)total;  
    return cpuUtilization;   
  
  /*
  	Another very simple way to calculate as per reviewer:
    #include<thread>
    auto number_of_machine_cores = std::thread::hardware_concurrency();
    auto uptime = LinuxParser::UpTime();
    auto idle = LinuxParser::IdleJiffies();
    return static_cast<float>(number_of_machine_cores x uptime -idle)/(number_of_machine_cores x uptime)
  */
}