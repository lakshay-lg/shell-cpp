#include <iostream>
#include <sstream>
#include <vector>
#include <string>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (1)
  {
    // TODO: Uncomment the code below to pass the first stage
    std::cout << "$ ";
    bool found = false;

    std::string command = "";
    std::getline(std::cin, command);

    std::vector<std::string> commands;
    std::stringstream ss(command);
    std::string temp;

    while (getline(ss, temp, ' '))
    {
      commands.push_back(temp);
    }

    if (commands[0] == "exit")
      break;
    if (commands[0] == "echo")
    {
      found = true;
      for (int i = 1; i < commands.size(); i++)
      {
        std::cout << commands[i] << " ";
      }
      std::cout << std::endl;
    }

    if (!found)
      std::cout << command << ": command not found" << std::endl;
  }
}
