#include <iostream>

#include "launcher/Launcher.hpp"
#include "launcher/ParsedArgs.hpp"

using namespace TaskReader;

int main(int argc, char **argv)
{
    ParsedArgs args;
    try {
        args.parse_args(argc, argv);
    }
    catch (std::exception &exc) {
        std::cerr << "Error during parsing command line: " << std::endl
                  << exc.what() << std::endl;
        return 1;
    }

    Launcher launcher;
    launcher.run(args.get_task_file(), args.get_output_dir());

    return 0;
}
