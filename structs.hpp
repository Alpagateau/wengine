#ifndef STRUCTS_HPP 
#define STRUCTS_HPP 
#include <iostream>
#include <string>

struct Settings_t 
{
  std::string font;
  float fontSize = -1;
};

typedef enum CState 
{
  PRINTER=0,
  QUESTION,
  TYPING,
  CSLEN,
}CState;

#endif
