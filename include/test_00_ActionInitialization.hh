/// \file test_00_ActionInitialization.hh
/// \brief Definition of the test_00_ActionInitialization class
//
//
#ifndef test_00_ActionInitialization_h
#define test_00_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class test_00_DetectorConstruction;

class G4GeneralParticleSource;
/// Action initialization class.
///

class test_00_ActionInitialization : public G4VUserActionInitialization
{
  public:
    test_00_ActionInitialization(test_00_DetectorConstruction*);
    virtual ~test_00_ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    test_00_DetectorConstruction* fDetector;
};

#endif
