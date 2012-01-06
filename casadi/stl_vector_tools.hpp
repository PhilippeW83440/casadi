/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef STL_VECTOR_TOOLS_HPP
#define STL_VECTOR_TOOLS_HPP


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <limits>
#include "casadi_exception.hpp"
#include "casadi_types.hpp"

/** \brief Convenience tools for STL vectors
    \author Joel Andersson 
    \date 2010-2011
*/

namespace std{

  /// Enables flushing an STL vector to a stream (prints representation)
  template<typename T>
  ostream& operator<<(ostream &stream, const vector<T> &v);
  
  /// Enables flushing an STL pair to a stream (prints representation)
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const pair<T1,T2> &p);
  
} // namespace std

namespace CasADi{

  #ifndef SWIG
  /** Range function
  * \param start
  * \param stop
  * \param step
  * \param len
  *
  * Consider a infinitely long list [start, start+step, start+2*step, ...]
  * Elements larger than or equal to stop are chopped off.
  *
  */
  std::vector<int> range(int start, int stop, int step=1, int len=std::numeric_limits<int>::max());

  /** Range function
  * \param stop
  *
  * \return list [0,1,2...stop-1]
  */
  std::vector<int> range(int stop);
  #endif // SWIG
  
  /// Print representation
  template<typename T>
  void repr(const std::vector<T> &v, std::ostream &stream=std::cout);
  
  /// Print description
  template<typename T>
  void print(const std::vector<T> &v, std::ostream &stream=std::cout);

  /// Print representation to string
  template<typename T>
  std::string getRepresentation(const std::vector<T> &v);
  
  /// Print description to string
  template<typename T>
  std::string getDescription(const std::vector<T> &v);

  /// Print vector, matlab style
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<T> &v);
  
  /// Print matrix, matlab style
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<std::vector<T> > &v);

  /// Read vector, matlab style
  template<typename T>
  void read_matlab(std::istream &stream, std::vector<T> &v);

  /// Read matrix, matlab style
  template<typename T>
  void read_matlab(std::ifstream &file, std::vector<std::vector<T> > &v);

  /// Matlab's linspace
  template<typename T, typename F, typename L>
  void linspace(std::vector<T> &v, const F& first, const L& last);

  /// Get an pointer of sets of booleans from a double vector
  bvec_t* get_bvec_t(std::vector<double>& v);

  /// Get an pointer of sets of booleans from a double vector
  const bvec_t* get_bvec_t(const std::vector<double>& v);
  
  /// Get an pointer of sets of booleans from a double vector
  template<typename T>
  bvec_t* get_bvec_t(std::vector<T>& v){
    casadi_assert_message(0,"get_bvec_t only supported for double");
  }

  /// Get an pointer of sets of booleans from a double vector
  template<typename T>
  const bvec_t* get_bvec_t(const std::vector<T>& v){
    casadi_assert_message(0,"get_bvec_t only supported for double");
  }
  
  /// Get a pointer to the data contained in the vector
  template<typename T>
  T* getPtr(std::vector<T> &v);
  
  /// Get a pointer to the data contained in the vector
  template<typename T>
  const T* getPtr(const std::vector<T> &v);
  
} // namespace CasADi
  
// Implementations  
  



namespace std{

  /// Enables flushing an STL vector to a stream (prints representation)
  template<typename T>
  ostream& operator<<(ostream &stream, const vector<T> &v){
    CasADi::repr(v,stream);
    return stream;
  }
  
  template<typename T1, typename T2>
  ostream& operator<<(ostream &stream, const pair<T1,T2> &p){
    stream << "(" << p.first << "," << p.second << ")";
    return stream;
  }

  
} // namespace std

namespace CasADi{
  
  template<typename T>
  void repr(const std::vector<T> &v, std::ostream &stream){
    if(v.empty()){
      stream << "[]";
    } else {
      // Print elements, python style
      stream << "[";
      stream << v.front();
      for(unsigned int i=1; i<v.size(); ++i)
        stream << "," << v[i];
      stream << "]";
    }
  }
  
  template<typename T>
  void print(const std::vector<T> &v, std::ostream &stream){
    // print vector style
    stream << "[" << v.size() << "]"; // Print dimension

    if(v.empty()){
      stream << "()";
    } else {
      // Print elements, ublas stype
      stream << "(";
      for(unsigned int i=0; i<v.size()-1; ++i)
        stream << v[i] << ",";
      if(!v.empty()) stream << v.back();
      stream << ")";
    }
  }

  template<typename T>
  std::string getRepresentation(const std::vector<T> &v){
    std::stringstream ss;
    repr(v,ss);
    return ss.str();
  }
  
  template<typename T>
  std::string getDescription(const std::vector<T> &v){
    std::stringstream ss;
    print(v,ss);
    return ss.str();
  }

  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<T> &v){
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(stream, " "));
  }
  
  template<typename T>
  void write_matlab(std::ostream &stream, const std::vector<std::vector<T> > &v){
    for(unsigned int i=0; i<v.size(); ++i){    
      std::copy(v[i].begin(), v[i].end(), std::ostream_iterator<T>(stream, " "));
      stream << std::endl;
    }
  }
  
  template<typename T>
  void read_matlab(std::istream &stream, std::vector<T> &v){
    v.clear();
  
    while(!stream.eof()) {
      T val;
      stream >> val;
      if(stream.fail()){
        stream.clear();
        std::string s;
        stream >> s;
        if(s.compare("inf") == 0)
          val = std::numeric_limits<T>::infinity();
        else
          break;
      }
      v.push_back(val);
    }
  }
  
  template<typename T>
  void read_matlab(std::ifstream &file, std::vector<std::vector<T> > &v){
    v.clear();
    std::string line;
    while(!getline(file, line, '\n').eof()) {
      std::istringstream reader(line);
      std::vector<T> lineData;
      std::string::const_iterator i = line.begin();
      
      while(!reader.eof()) {
        T val;
        reader >> val;
        if(reader.fail()){
          reader.clear();
          std::string s;
          reader >> s;
          if(s.compare("inf") == 0)
            val = std::numeric_limits<T>::infinity();
          else
            break;
        }
        lineData.push_back(val);
      }
      v.push_back(lineData);
    }
  }

  template<typename T, typename F, typename L>
  void linspace(std::vector<T> &v, const F& first, const L& last){
    if(v.size()<2) throw CasadiException("std::linspace: vector must contain at least two elements");
    
    // Increment
    T increment = (last-first)/T(v.size()-1);
    
    v[0] = first;
    for(unsigned i=1; i<v.size()-1; ++i)
      v[i] = v[i-1] + increment;
    v[v.size()-1] = last;
  }

  template<typename T>
  T* getPtr(std::vector<T> &v){
    if(v.empty())
      return 0;
    else
      return &v.front();
  }
  
  template<typename T>
  const T* getPtr(const std::vector<T> &v){
    if(v.empty())
      return 0;
    else
      return &v.front();
  }

} // namespace CasADi



#endif // STL_VECTOR_TOOLS_HPP
