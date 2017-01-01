#ifndef SHELL_PROBLEM_LAUNCHER_HPP
#define SHELL_PROBLEM_LAUNCHER_HPP

#include <string>

class Launcher
{
public:
    Launcher();
    void run(const std::string &task_file, const std::string &output_dir);
    void setup_logger(const std::string &output_dir) const;
};

#endif //SHELL_PROBLEM_LAUNCHER_HPP
