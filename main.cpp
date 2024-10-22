// Copyright 2024 Medtronic LP
// All Rights Reserved. The information contained herein is confidential
// property of Medtronic. The use, copying, transfer or disclosure of such
// information is prohibited except by express written agreement with Medtronic.
 
/// \file library/ups/diagnostics/jsonSR/main.cpp
/// \ingroup EIN-SWI-XXX

#include<iostream>
#include<sstream>

#include "token.h"
//#include<fstream>
//#include<sstream>

using namespace JsonSR;

int main()
{

  // This file explains how could customer can call jsonSR library to achive or parse the json file, string and object.
   //calling parse using input string  
 /* std::string json_str = "{\"key\": \"value\"}";
    JsonSR::Reader reader;
    bool parseSuccess = reader.parse(json_str);
    std::cout << reader["key"] << std::endl; */
  
  
  //calling parse using a document.
  /*
  std::ifstream file("ani.json");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string json_str = buffer.str(); 
  
  JsonSR::Reader reader;
  bool parseSuccess = reader.parse(json_str); */
  
  
  
  // calling parse using string stream
  
 /* std::string input = "{\"key\": \"value\"}";
  std::istringstream json_str(input);
  
  JsonSR::Reader reader;
  bool parseSuccess = reader.parse(json_str);
  
  std::cout << reader["key"] << std::endl; */
  
  
  
     // Calling reader class using a file.
        JsonSR::Reader reader("ani.json");
        std::string strData = reader.readFile();
        reader.parse(strData);  
  
  
  std::cout << reader["uuid"] << std::endl;
  std::cout << reader["Name"] << std::endl;
  std::cout << reader["Version"] << std::endl;
  std::cout << reader["Value"] << std::endl;
  std::cout << reader["Power"] << std::endl;
  std::cout << reader["Config"] << std::endl;
  
  
  return 0;
}
