#include <iostream>
#include <string>
#include <filesystem>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage

  while(true){
    std::string PATH = std::getenv("PATH");
    bool found = false;
    std::string command;
    std::string input;
    std::cout << "$ ";
    std::cin >> command;
    std::getline(std::cin, input);
    if (!input.empty()) {
      input = input.substr(1);
    }
    if (command == "exit") {
      break;
    }
    if (command == "echo") {
      std::cout << input << std::endl;
      continue;
    }
    if (command == "type") {
      std::string supported[3] = {"echo", "exit", "type"};
      for (int i=0; i<3;i++){
        if (supported[i] == input){
          std::cout << input << " is a shell builtin" << std::endl;
          found = true;
          continue;
        }
      }
      if(!found){
        bool keepGoing = true;
        int len=PATH.length();
        int casebefore=0;
        std::string path;
        for(int i=0;i<len;i++){
          if(PATH[i] == ';' || PATH[i] == ':'){
            path=PATH.substr(casebefore, i-casebefore);
            casebefore=i+1;
            bool dirpathExists = std::filesystem::is_directory(dirpath);
            std::cout << path<<i;
            if(dirpathExists){
              std::filesystem::path exepath = std::string(path + "/" + input);
              bool exepathExists = std::filesystem::exists(exepath);
              if(exepathExists){
                std::cout << input << " is " << exepath.c_str() << std::endl;
                found=true;
                break;
              }
            }
          }
        }
      }
      if(!found){
        std::cout << input <<": not found" << std::endl;
      }
      continue;
    }
    std::cout << command <<": command not found" << std::endl;


  }
}
