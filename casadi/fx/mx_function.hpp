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

#ifndef MX_FUNCTION_HPP
#define MX_FUNCTION_HPP

#include <set>
#include <iostream>

#include "../mx/mx.hpp"
#include "sx_function.hpp"

namespace CasADi{

/** \brief  An elemenent of the algorithm, namely an MX node */
struct MXAlgEl{
  // Function to be evaluated
  MX op;
  
  // Indices of the children nodes
  std::vector<int> arg;

  // Indices of the children nodes
  std::vector<int> res;
};

} // namespace CasADi

#ifdef SWIG
// Template instantiation
%template(MXAlgElVector) std::vector<CasADi::MXAlgEl>;
#endif // SWIG

// Lifting function to be passed to the evalutator in order to lift the evaluations
typedef void (*LiftingFunction)(double *v, int n, void *user_data);

namespace CasADi{

/** \brief  Forward declaration of internal class */
class MXFunctionInternal;

  /** \brief  General function mapping from/to MX
  \author Joel Andersson 
  \date 2010
*/
class MXFunction : public FX{
public:

  /** \brief  Ddefault constructor */
  MXFunction();

#ifndef SWIG  
  /** \brief  Single input, single output */
  MXFunction(const MX& input, const MX& output);

  /** \brief  Single input, multiple output */
  MXFunction(const MX& input, const std::vector<MX>& output);

  /** \brief  Multiple input, single output */
  MXFunction(const std::vector<MX>& input, const MX& output);
#endif // SWIG  

  /** \brief  Multiple input, multiple output*/
  MXFunction(const std::vector<MX>& input, const std::vector<MX>& output);

  /** \brief  Access functions of the node */
  MXFunctionInternal* operator->();

  /** \brief  Const access functions of the node */
  const MXFunctionInternal* operator->() const;

  /// get function input argument (to be deprecated)
  const MX inputMX(int iind=0) const;
  
  /// get function output argument (to be deprecated)
  const MX outputMX(int oind=0) const;
  
  /// get function inputs argument (to be deprecated)
  const std::vector<MX> & inputsMX() const;
  
  /// get function outputs argument (to be deprecated)
  const std::vector<MX> & outputsMX() const;
  
  /** \brief get function input */
  const MX& inputExpr(int ind) const;
  
  /** \brief get function output */
  const MX& outputExpr(int ind) const;
  
  /** \brief get function inputs */
  const std::vector<MX>& inputExpr() const;
  
  /** \brief get function outputs */
  const std::vector<MX> & outputExpr() const;
  
  /** \brief Access the algorithm */
  const std::vector<MXAlgEl>& algorithm() const;
  
  /** \brief Number of nodes in the algorithm */
  int countNodes() const;
  
  /** \brief Set the lifting function */
  void setLiftingFunction(LiftingFunction liftfun, void* user_data=0);
  
  /// Check if the node is pointing to the right type of object
  virtual bool checkNode() const;
  
  /** \brief Jacobian via source code transformation */
  MX jac(int iind=0, int oind=0, bool compact=false, bool symmetric=false);

  /** \brief Gradient via source code transformation */
  MX grad(int iind=0, int oind=0);
  
  /** \brief Expand the matrix valued graph into a scalar valued graph */
  SXFunction expand(const std::vector<SXMatrix>& inputv = std::vector<SXMatrix>());
  
  /** \brief Get all the free variables of the function */
  std::vector<MX> getFree() const;
};

} // namespace CasADi


#endif // MX_FUNCTION_HPP

