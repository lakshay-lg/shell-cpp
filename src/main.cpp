#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (1)
  {
    // TODO: Uncomment the code below to pass the first stage
    std::cout << "$ ";

    std::string command = "";
    std::getline(std::cin, command);

    // checking the operation in the command
    std::vector<std::string> commands;
    std::stringstream ss(command);
    std::string temp;

    // tracking available commands
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

    // TYPE
    if (commands[0] == "type")
    {
      for (int i = 1; i < commands.size(); i++)
      {
        if (availableCommands.count(commands[i]))
        {
          std::cout << commands[i] << " is a shell builtin" << std::endl;
        }
        else
        {
          std::cout << commands[i] << ": not found" << std::endl;
        }
      }
    }

    if (!availableCommands.count(commands[0]))
      std::cout << commands[0] << ": command not found" << std::endl;
  }
}
