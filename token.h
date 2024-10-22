// Copyright 2024 Medtronic LP
// All Rights Reserved. The information contained herein is confidential
// property of Medtronic. The use, copying, transfer or disclosure of such
// information is prohibited except by express written agreement with Medtronic.
 
/// \file library/ups/diagnostics/jsonSR/token.h
/// \ingroup EIN-SWI-XXX

#ifndef JSON_TOKEN_H
#define JSON_TOKEN_H

#include<iostream>
#include<vector>
#include<map>
#include<fstream>


namespace JsonSR {

class Reader {
  public:
  std::map<std::string,std::string> json_map; //To store the json key and value pair. 
  using Location = const char*; // To findout location in current string.
  std::string sdata; //To store the data after reading from a file
  std::string sfile; // file handler.
  std::string document_{}; 
  const char* begin_{}; // begining of a strin which need to be parsed
  const char* end_{};  // end of the string which need to be parsed
  const char* current_{}; // current pointer in the string while parsing. 
  
  bool parse(std::string& document); // read from a document
  bool parse(std::istream& is); // read from a stream 
  bool parse(const char* beginDoc, const char* endDoc); // to read the character string after reading from file or input stream
  Reader()= default;  // constructor
  Reader(const std::string& filename); // constructor to read from a json file
   private:  
   enum TokenType {  // enum to store list of different character types while reading json data
    tokenEndOfStream = 0,
    tokenObjectBegin,
    tokenObjectEnd,
    tokenString,
    tokenMemberSeparator,
    tokenError
  };

  class Token {  // token class which contains type os data and data itself
  public:
    TokenType type_;
    Location start_;
    Location end_;
    std::string Value_;
  };
public:
  bool readValue();   // read the data from a json string
  auto readToken();   // find out token from current data
  void skipSpaces();  // skip spaces inbetween characters in a json data  
  bool readString();  // To read the string once encounter " in the readvalue. 
  bool readObject(Token& token);  // to read object 
  void skipUntilSpace();  // 
  char getNextChar();   // get current character in the stream
  bool hasMoreToken();  // to understand if we can create more tokens 
  void parseObject();   // to parse json object 
  std::string readFile();  // read json file to parse 
  void getMemberNames();   // to iterate though map and display key and value list 
  std::string& operator[](const std::string&); // overloading to return value wrt key in the map.

};

}
#endif
