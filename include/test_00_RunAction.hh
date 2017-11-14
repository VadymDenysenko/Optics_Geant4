/// \file test_00_RunAction.hh
/// \brief Definition of the test_00_RunAction class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef test_00_RunAction_h
#define test_00_RunAction_h 1

#include "globals.hh"

#include "G4UserRunAction.hh"

class G4Run;

class test_00_RunAction : public G4UserRunAction
{
  public:

    test_00_RunAction();
    virtual ~test_00_RunAction();

  public:

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void  SetRndmFreq(G4int val)
    {
      fSaveRndm = val;
    }
    G4int GetRndmFreq()
    {
      return fSaveRndm;
    }
    
    inline void SetAutoSeed (const G4bool val)
    {
      fAutoSeed = val;
    }

  private:

    G4int fSaveRndm;
    G4bool fAutoSeed;

};

#endif
