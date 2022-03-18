#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#
#include <iostream>
#include <string>
using namespace std;

class BaseException {
  public:
    virtual void printMessage() = 0;
};

class FileNotFoundException : public BaseException {
  public:
    FileNotFoundException() {}
    void printMessage() {
      cout << "File input tidak tersedia." << endl;
    }
};

#endif