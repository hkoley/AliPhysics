/// ////////////////////////////////////////////////////////////////////////////
//
// CEP V0 buffer
//
// structure to hold information on cell level for V0
//
// ____________________________________________________________________________
#include "CEPTrackBuffer.h"
#include "CEPRawV0Buffer.h"

ClassImp(CEPRawV0Buffer)

// ____________________________________________________________________________
CEPRawV0Buffer::CEPRawV0Buffer()
  : TObject()
  , fNCells(64)
  , fNPMV0A (CEPTrackBuffer::kdumval)
  , fNPMV0C (CEPTrackBuffer::kdumval)
{

  this->Reset();

}

// ____________________________________________________________________________
CEPRawV0Buffer::~CEPRawV0Buffer()
{
  
}

// ____________________________________________________________________________
void CEPRawV0Buffer::Reset()
{
    fNCells   = 64;
    fNPMV0A   = CEPTrackBuffer::kdumval;
    fNPMV0C   = CEPTrackBuffer::kdumval;
    for (UInt_t i(0); i<fNCells; i++){
        fMult[i]     = 0.0; 
        fAdc[i]      = 0.0; 
        fTime[i]     = 0.0; 
        fSigWidth[i] = 0.0; 
    }
}

// ____________________________________________________________________________
Float_t CEPRawV0Buffer::GetV0Multiplicity(Int_t i) const
{
    return std::abs(i)<fNCells ? fMult[std::abs(i)] : CEPTrackBuffer::kdumval;
}

// ____________________________________________________________________________
Float_t CEPRawV0Buffer::GetV0Charge(Int_t i) const
{
    return std::abs(i)<fNCells ? fAdc[std::abs(i)] : CEPTrackBuffer::kdumval;
}

// ____________________________________________________________________________
Float_t CEPRawV0Buffer::GetV0Time(Int_t i) const
{
    return std::abs(i)<fNCells ? fTime[std::abs(i)] : CEPTrackBuffer::kdumval;
}

// ____________________________________________________________________________
void CEPRawV0Buffer::SetV0Variables(AliESDVZERO* V0obj)
{
    // Global member variable setter
    this->SetV0NPMV0A(V0obj->GetNbPMV0A());
    this->SetV0NPMV0C(V0obj->GetNbPMV0C());
    for (UInt_t i(0); i<fNCells; i++) 
    {  
        this->SetV0Multiplicity(V0obj->GetMultiplicity(i), i);
        this->SetV0Charge(V0obj->GetAdc(i), i);
        this->SetV0Time(V0obj->GetTime(i), i);
        this->SetV0Width(V0obj->GetWidth(i), i);
    } 
}

// ____________________________________________________________________________
