#include "PathCommand.h"

// Constructor implementation
PathCommand::PathCommand(char cmd, const std::vector<float>& params)
    : command(cmd), parameters(params) {}

// Getter for command
char PathCommand::getCommand() const
{
    return command;
}

// Convert the command to a string representation
std::string PathCommand::tostring() const
{
    std::ostringstream oss;
    oss << command << " ";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        oss << parameters[i];
        if (i < parameters.size() - 1)
            oss << " ";
    }
    return oss.str();
}

// Getter for parameters
const std::vector<float>& PathCommand::getParameters() const
{
    return parameters;
}

