//  PhysObjectProcessor.hpp
//
//  Created by Jeremi Niedziela on 29/07/2019.

#ifndef PhysObjectProcessor_hpp
#define PhysObjectProcessor_hpp

#include "Helpers.hpp"
#include "PhysObject.hpp"

class PhysObjectProcessor;
extern PhysObjectProcessor physObjectProcessor;

class PhysObjectProcessor {
public:
  /// Default constructor
  PhysObjectProcessor();
  
  // Default destructor
  ~PhysObjectProcessor();
  
  // Returns ΔR=sqrt(Δη^2 + Δφ^2) between two PhysObjects
  double GetDeltaR(const PhysObject &a, const PhysObject &b);
  
  // Returns a lorentz vector which is a sum of provided objects
  TLorentzVector GetObjectsSum(const PhysObject &a, const PhysObject &b);
  
private:
  
  
};

#endif /* PhysObjectProcessor_hpp */
