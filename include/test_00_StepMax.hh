/// \file StepMax.hh
/// \brief Definition of the test_00_StepMax class
//
//
#ifndef test_00_StepMax_h
#define test_00_StepMax_h 1

#include "globals.hh"

#include "G4Step.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"

class test_00_StepMax : public G4VDiscreteProcess
{
  public:

    test_00_StepMax(const G4String& processName = "UserStepMax");
    test_00_StepMax(test_00_StepMax &);

    virtual ~test_00_StepMax();

    virtual G4bool IsApplicable(const G4ParticleDefinition&);

    void SetStepMax(G4double);

    G4double GetStepMax() {return fMaxChargedStep;};

    virtual G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                                  G4double previousStepSize,
                                                  G4ForceCondition* condition);

    virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

  protected:

    G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*);

  private:

    // hide assignment operator as private
    test_00_StepMax & operator=(const test_00_StepMax &right);
    test_00_StepMax(const test_00_StepMax&);

  private:

    G4double fMaxChargedStep;

};

#endif
