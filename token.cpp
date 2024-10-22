// Copyright 2024 Medtronic LP
// All Rights Reserved. The information contained herein is confidential
// property of Medtronic. The use, copying, transfer or disclosure of such
// information is prohibited except by express written agreement with Medtronic.
 
/// \file library/ups/diagnostics/jsonSR/token.cpp
/// \ingroup EIN-SWI-XXX

#include"token.h"
#include<cstring>

namespace JsonSR{

Reader::Reader(const std::string& filename): sfile(filename){}

std::string Reader::readFile() {
         std::ifstream file(sfile);
         if(!file.is_open()) {
           std::cout << "File open Error" << std::endl;  
           return "";     
         }
         
         std::string line="";
         while(std::getline(file,line)) {
             sdata += line;
         }
       return sdata;
}
  
bool Reader::parse(std::string& document) {
         std::cout << "Document called" << std::endl;
         document_.assign(document.begin(), document.end());
         const char* begin = document_.c_str();
         const char* end = begin + document_.length();
         return parse(begin, end);
}
      
bool Reader::parse(std::istream& is) {
       std::cout << "Istream called" << std::endl;
       
       std::string line;
       while(std::getline(is,line)) {
         //std::cout << line << std::endl;
       }
       
      const char* start = line.c_str();
      const char* end = line.c_str()+line.size();
      return parse(start,end);
}  
    
    
bool Reader::parse(const char* beginDoc, const char* endDoc) {
       begin_ = beginDoc;
       end_ = endDoc;
       current_ = begin_;
       
       bool successful = readValue();
       Token token;
       
       return true;
}
    
char Reader::getNextChar() {
      char c = ' ';
      while(c == ' ' || c == '\n')
      {
        c = *current_++;
        if(c == ' ' || c == '\n')
        {
         continue;
        }
      }
     return c;
}
     
void Reader::skipSpaces() {
       while (current_ != end_) {
        char c = *current_;
         if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
           ++current_;
         else
           break;
       }
}
    
auto Reader::readToken() {
     Token token;
     skipSpaces();
     token.start_ = current_;
     char c = getNextChar();
     bool ok = true;
    
    switch (c) {
     case '{':
      token.type_ = tokenObjectBegin;
      break;
     case '}':
      token.type_ = tokenObjectEnd;
      break;
     case '"':
      token.type_ = tokenString;
      token.Value_ = "";
      c = getNextChar();
      while(c != '"') {
      token.Value_ += c;
      c = getNextChar();
      }
      break;
    case ':':
     token.type_ = tokenMemberSeparator;
     break;
    case 0:
     token.type_ = tokenEndOfStream;
     break;
    default:
     break;
   }
   token.end_ = current_;
   return token;
}
      
bool Reader::readValue() {
   Token token;
   bool successful = true;
   token = readToken();

   switch (token.type_) {
    case tokenObjectBegin:
     parseObject();
     break;
    case tokenObjectEnd:
     break;
    case tokenString:
     break;
 
    default:
     std::cout << "default: " << std::endl;
     return false;
    } 
    return true; 
 }
 
void Reader::parseObject() { 
     bool hasCompleted = false;
         
       while(!hasCompleted) {
          if(hasMoreToken()) {
            
            Token nextToken = readToken();
            std::string key = nextToken.Value_;
               
            readToken();
            nextToken = readToken();
            const std::string val = nextToken.Value_;         
               json_map[key] = val;
            }  
             
            Token nextToken1 = readToken();
            if(nextToken1.type_ == TokenType::tokenObjectEnd) {
                hasCompleted = true;
            }
          }
}

void Reader::getMemberNames() {
      
}
    
bool Reader::hasMoreToken() {
          if(current_ == end_) return false;
          return true;
}
      
std::string& Reader::operator[](const std::string& key) {
    return json_map[key];
}
      
      
 
}
