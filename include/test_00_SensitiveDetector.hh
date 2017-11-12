/// \file test_00_SensitiveDetector.hh
/// \brief Definition of the test_00_SensitiveDetector class
//
//
#ifndef test_00_SensitiveDetector_h
#define test_00_SensitiveDetector_h 1

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4TouchableHistory;

class test_00_SensitiveDetector: public G4VSensitiveDetector
{
private:
    G4String nameOfParticle;
    G4int counter = 0;
public:
    test_00_SensitiveDetector(G4String name);
    ~test_00_SensitiveDetector();
    G4bool ProcessHits(G4Step *step, G4TouchableHistory*);
};

#endif
