#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <cstdlib>

#include <filesystem>
#include <unistd.h>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (1)
  {
    // Initial Prompt
    std::cout << "$ ";

    std::string command = "";
    std::getline(std::cin, command);

    // checking the operation in the command
    std::vector<std::string> commands;
    std::stringstream ss(command);
    std::string temp;

    // Tracking available commands
    std::unordered_set<std::string> availableCommands;
    availableCommands.insert("echo");
    availableCommands.insert("exit");
    availableCommands.insert("type");

    while (getline(ss, temp, ' '))
    {
      commands.push_back(temp);
    }

    // EXIT
    if (commands[0] == "exit")
      break;

    // ECHO
    if (commands[0] == "echo")
    {
      for (int i = 1; i < commands.size(); i++)
      {
        std::cout << commands[i] << " ";
      }
      std::cout << std::endl;
    }

    // Getting the $PATH variable
    const std::string path_value = getenv("PATH");
    std::vector<std::string> directories;

    std::stringstream dir(path_value);
    std::string tempDir;

    while (getline(dir, tempDir, ':'))
    {
      directories.push_back(tempDir);
    }

    // TYPE
    if (commands[0] == "type")
    {
      for (int i = 1; i < commands.size(); i++)
      {
        bool foundInPath = true;
        if (availableCommands.count(commands[i]))
        {
          std::cout << commands[i] << " is a shell builtin" << std::endl;
        }
        else
        {
          foundInPath = false;
          for (std::string &st : directories)
          {
            std::string path = st + '/' + commands[i];

            // check if file exist in this directory, ensuring it's a file and its executable
            if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && (access(path.c_str(), X_OK) == 0))
            {
              std::cout << commands[i] << " is " << path << std::endl;
              foundInPath = true;
              break;
            }
          }
        }

        if (!foundInPath)
        {
          std::cout << commands[i] << ": not found" << std::endl;
        }
      }
    }

    bool foundInPath = true;
    if (!availableCommands.count(commands[0]))
    {
      for (std::string &st : directories)
      {
        std::string path = st + '/' + commands[0];

        // check if file exist in this directory, ensuring it's a file and its executable
        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && (access(path.c_str(), X_OK) == 0))
        {
          std::string args = "";
          for (int i = 1; i < commands.size(); i++)
          {
            args += (commands[i] + ' ');
          }
          std::system((commands[0] + " " + args).c_str());
          foundInPath = true;
          break;
        }
      }
    }

    if (!(foundInPath || availableCommands.count(commands[0])))
      std::cout << commands[0] << ": command not found" << std::endl;
  }
}
