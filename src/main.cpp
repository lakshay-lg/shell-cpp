#include <iostream>
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

    std::string command = "";
    std::getline(std::cin, command);

    bool found = false;

    if (!found)
      std::cout << command << ": command not found" << std::endl;
  }
}
