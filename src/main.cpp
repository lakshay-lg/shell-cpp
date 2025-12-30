#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <cstdlib>

#include <filesystem>
#include <unistd.h>
#include <limits.h>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string curPath = std::filesystem::current_path().string();
  while (1)
  {
    // Initial Prompt
    std::cout << "$ ";

    std::string command = "";
    std::getline(std::cin, command);

    // No Commands
    if (command == "")
      continue;

    // Checking the operation in the command
    std::vector<std::string> args;
    std::stringstream ss(command);
    std::string temp;

    // Tracking available builtins
    std::unordered_set<std::string> availableCommands;
    availableCommands.insert("echo");
    availableCommands.insert("exit");
    availableCommands.insert("type");
    availableCommands.insert("pwd");
    availableCommands.insert("cd");

    while (getline(ss, temp, ' '))
    {
      args.push_back(temp);
    }

    // EXIT
    if (args[0] == "exit")
      break;

    // ECHO
    if (args[0] == "echo")
    {
      for (int i = 1; i < args.size(); i++)
      {
        std::cout << args[i] << " ";
      }
      std::cout << std::endl;
    }

    // PWD
    if (args[0] == "pwd")
    {
      std::cout << std::filesystem::current_path().string() << std::endl;
    }

    // CD
    if (args[0] == "cd")
    {
      if (args.size() < 2)
        continue;
      else
      {
        std::error_code ec;
        std::filesystem::current_path(args[1], ec);

        if (ec)
        {
          std::cout << "cd: " << args[1] << ": No such file or directory" << std::endl;
        }
      }
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
    if (args[0] == "type")
    {
      for (int i = 1; i < args.size(); i++)
      {
        bool foundInPath = true;
        if (availableCommands.count(args[i]))
        {
          std::cout << args[i] << " is a shell builtin" << std::endl;
        }
        else
        {
          foundInPath = false;
          for (std::string &st : directories)
          {
            std::string path = st + '/' + args[i];

            // check if file exist in this directory, ensuring it's a file and its executable
            if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && (access(path.c_str(), X_OK) == 0))
            {
              std::cout << args[i] << " is " << path << std::endl;
              foundInPath = true;
              break;
            }
          }
        }

        if (!foundInPath)
        {
          std::cout << args[i] << ": not found" << std::endl;
        }
      }
    }

    // Running exec from Path if command not found
    bool foundInPath = false;
    if (!availableCommands.count(args[0]))
    {
      for (std::string &st : directories)
      {
        std::string path = st + '/' + args[0];

        // check if file exist in this directory, ensuring it's a file and its executable
        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && (access(path.c_str(), X_OK) == 0))
        {
          // TESTING EXTERNAL SCRIPTS
          // std::cout << "Found it: " << path << std::endl;

          std::string argString = "";
          for (int i = 0; i < args.size(); i++)
          {
            argString += (args[i] + ' ');
          }
          std::system(argString.c_str());
          foundInPath = true;
          break;
        }
      }
    }

    // notFound in Commands or $PATH
    if (!(foundInPath || availableCommands.count(args[0])))
      std::cout << args[0] << ": command not found" << std::endl;
  }
}
