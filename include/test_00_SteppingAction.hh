/// \file test_00_SteppingAction.hh
/// \brief Definition of the test_00_SteppingAction class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef test_00_SteppingAction_h
#define test_00_SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include <fstream>
#include <sstream>

class test_00_DetectorConstruction;

class G4Track;
class G4StepPoint;

class G4OpBoundaryProcess;

class test_00_SteppingAction : public G4UserSteppingAction
{
  public:

    test_00_SteppingAction(test_00_DetectorConstruction*);
    virtual ~test_00_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

    G4int GetCounts();

  private:
    // number of photons that reach the end
    G4int fCounter;
    G4int fAbsorbed;
    G4int testCounter;

    // maximum number of save states
    static G4int fMaxRndmSave;

    test_00_DetectorConstruction* fDetector;

    inline void ResetCounters()
    {
      fCounter = 0;
      fAbsorbed = 0;
      testCounter = 0;
    }

    std::ofstream saveFile;
    inline void SaveParticles(G4int id, G4double x, G4double y, G4double z)
    {
      if (saveFile.is_open())
      {
        saveFile << id << ":: " << x << " : " << y << " : " << z << "\n";
      }
      else
        G4cout << "Unable to open file";
    }
    inline void SaveParticles(G4double x1, G4double y1, G4double z1, G4String a1,
                              G4double x2, G4double y2, G4double z2, G4String a2,
                              G4int id)
    {
      if (saveFile.is_open())
      {
        saveFile << "        " << x1 << " : " << y1 << " : " << z1 << "_"
                               << a1 << " -> "
                               << x2 << " : " << y2 << " : " << z2 << "_"
                               << a2 << " -| "
                               << id << ";\n";
      }
      else
        G4cout << "Unable to open file";
    }

    // save the random status into a sub-directory
    // Pre: subDir must be empty or ended with "/"
    inline void saveRandomStatus(G4String subDir);

};

#endif
