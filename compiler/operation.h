/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#pragma once

#include <stdio.h>
#include <stdint.h>

#include <vector>
#include <sstream>

#include "arg.h"
#include "interface.h"
#include "operation.h"
#include "fasthash.h"

namespace xaio {
namespace compiler {
  struct xaio_arg;
  struct xaio_interface;
  struct xaio_operation {
    ::std::string return_type;
    ::std::string name;
    ::std::vector<xaio_arg *> args;
    xaio_interface *interface;
    xaio_operation(xaio_interface *interface) 
      : interface(interface) {
    }
    ::std::string to_str() const {
      ::std::stringstream ss;
      ss << name_ <<  "(";
      ::std::string del = "";
      for (auto arg : args) {
        ss << del << arg->to_str();
        del = ",";
      }
      ss << "): " << return_type << " => '" << 
        get_fq_name() << "', hash: '" << get_hash() << "'";
      return ss.str();
    }
    ::std::string get_fq_name() const {
      ::std::stringstream ss;
      ss << interface->get_fq_name() << "." << name_;
      ss << "(";
      ::std::string del = "";
      for (auto arg : args) {
        ss << del << ":" << arg->type;
        del = ",";
      }
      ss << "):";
      ss << return_type;
      return ss.str();
    }
    uint32_t get_hash() const {
      ::std::string fq_name = get_fq_name();
      return fasthash32(fq_name.c_str(), fq_name.size(), 0);
    }
  };
}
}
