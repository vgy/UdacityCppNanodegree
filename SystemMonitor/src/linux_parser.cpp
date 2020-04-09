#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

static const long Hertz = sysconf(_SC_CLK_TCK);

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

std::string GetValue(std::ifstream& stream){
  string key, value, line;
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> key >> value;
  return value;
}

std::string GetToken(std::string & line, int id){
  string token;
  std::istringstream ss(line);
  for (int i = 1; i <= id; i++)
  {
    ss >> token;
  }
  return token;
}

std::string GetToken(std::string & line, char& delimiter, int id){
  string token;
  std::istringstream ss(line);
  for (int i = 1; i <= id; i++)
  {
    std::getline(ss, token, delimiter);
  }
  return token;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {  
  string line;
  float totalMemory {0.0f}, freeMemory {0.0f};
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    totalMemory = std::stof(GetToken(line, 2));
    std::getline(stream, line);
    freeMemory = std::stof(GetToken(line, 2));
  }
  return (totalMemory - freeMemory) / totalMemory;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long upTime {0};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    upTime = std::stol(GetToken(line, 1));
  }
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  vector<string> cpuInfo(10, "0");
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    string token;
    std::istringstream linestream(line);
    linestream >> token;
    for (int i = 0; i < 10; i++)
    {
      linestream >> cpuInfo[i];
    }
  }
  return cpuInfo;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  int totalProcessesCount {0};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    string totalProcesses{""};
    while(totalProcesses != "processes")
    {
      std::getline(stream, line);
      totalProcesses = GetToken(line, 1);
    }
    totalProcessesCount = std::stol(GetToken(line, 2));
  }
  return totalProcessesCount;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  int runningProcessesCount {0};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    string runningProcesses{""};
    while(runningProcesses != "procs_running")
    {
      std::getline(stream, line);
      runningProcesses = GetToken(line, 1);
    }
    runningProcessesCount = std::stol(GetToken(line, 2));
  }
  return runningProcessesCount;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string cmdline;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, cmdline);
  }
  return cmdline;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  long ramMb {0};
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    string key{""};
    while(key != "VmSize:")
    {
      std::getline(stream, line);
      key = GetToken(line, 1);
    }
    auto ramKb = std::stol(GetToken(line, 2));
    ramMb = ramKb/1000;
  }
  return to_string(ramMb);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string uid{"0"};
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    string key{""};
    while(key != "Uid:")
    {
      std::getline(stream, line);
      key = GetToken(line, 1);
    }
    uid = GetToken(line, 2);
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  auto uid = Uid(pid);
  string line;
  char delimiter{':'};
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while(std::getline(stream, line))
    {
      auto id = GetToken(line, delimiter, 3);
      if (id == uid)
      {
        return GetToken(line, delimiter, 1);
      }
    }
  }
  return uid;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long upTime{0};
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    string line;
    std::getline(stream, line);
    auto clockTicks = stol(GetToken(line, 22));
    upTime = clockTicks/Hertz;
  }
  return upTime;
}

// TODO: Read and return Sytem up time
float LinuxParser::SystemUpTime() {
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (!stream.is_open()) {
    return 0;
  }
  string line;
  std::getline(stream, line);
  std::istringstream linestream(line);
  string uptime{"0"};
  linestream >> uptime;
  return stol(uptime);
}

// TODO: Read and return CPU utilization
float LinuxParser::CpuUtilization(int pid) { 
  long utime, stime, cutime, cstime, starttime;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    string line;
    std::getline(stream, line);
    utime = stol(GetToken(line, 14));
    stime = stol(GetToken(line, 15));
    cutime = stol(GetToken(line, 16));
    cstime = stol(GetToken(line, 17));
    starttime = stol(GetToken(line, 22));
  }
  
  auto uptime = SystemUpTime();
  auto totalTime = utime + stime + cutime + cstime;
  auto seconds = uptime - (static_cast<float>(starttime) / Hertz);
  auto cpuUsage = 100 * ((static_cast<float>(totalTime) / Hertz) / seconds);
  return cpuUsage;
}