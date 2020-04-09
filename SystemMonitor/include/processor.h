#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::map<std::string, int> cpuInfo;
    std::vector<std::string> cpuInfoLabels{"user", "nice", "system", "idle", "iowait", "irq", "softirq", "steal", "guest", "guest_nice" };
    std::vector<std::string> cpuInfoValues;
    long idle{0};
    long nonIdle{0};
    long total{0};
    float cpuUtilization{0.0f};
};

#endif