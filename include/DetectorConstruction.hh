#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "DetectorMessenger.hh"

//---------------------------------------------------------------------------

class G4VPhysicalVolume;
class VirtualDetectorSD;
class RealDetectorSD;

//---------------------------------------------------------------------------

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  DetectorConstruction();
  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();
  
  inline G4VPhysicalVolume* GetExpHall()           { return fExpHall;           };
  inline G4VPhysicalVolume* GetDetVol(G4int i)     { return fDetVol[i];         };
  inline VirtualDetectorSD* GetVirtualDetectorSD() { return fVirtualDetectorSD; };
  inline G4int              GetNoSD()              { return fNSD;               };

  private:

  G4NistManager*     fNistManager;
  DetectorMessenger* fDetMessenger;

  static const G4int fNSD = 91;

  G4VPhysicalVolume* fExpHall;
  G4VPhysicalVolume* fDetVol[fNSD];
  G4LogicalVolume*   fexpHall_log;

  VirtualDetectorSD* fVirtualDetectorSD;
  RealDetectorSD*    fRealDetectorSD;

};
#endif

//---------------------------------------------------------------------------

