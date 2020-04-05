//
// Created by Artem Baryshev on 3/25/20.
//

#ifndef RT__READ_PARAMS_HPP_
#define RT__READ_PARAMS_HPP_
#include <unordered_map>
#include "Render.hpp"

int threads = 1;
int sceneId = 1;
std::string outFilePath = "zout.bmp";

void read_params(int argc, const char** argv) {
  std::unordered_map<std::string, std::string> cmdLineParams;

  for(int i = 0; i < argc; i++)
  {
    std::string key(argv[i]);

    if(key.size() > 0 && key[0] == '-')
    {
      if(i != argc - 1) // not last argument
      {
        cmdLineParams[key] = argv[i+1];
        i++;
      }
      else
        cmdLineParams[key] = "";
    }
  }

  if(cmdLineParams.find("-out") != cmdLineParams.end()) {
    outFilePath = cmdLineParams["-out"];
  }

  if(cmdLineParams.find("-scene") != cmdLineParams.end()) {
    sceneId = atoi(cmdLineParams["-scene"].c_str());
  }

  if(cmdLineParams.find("-threads") != cmdLineParams.end()) {
    threads = atoi(cmdLineParams["-threads"].c_str());
  }
}

#endif //RT__READ_PARAMS_HPP_
