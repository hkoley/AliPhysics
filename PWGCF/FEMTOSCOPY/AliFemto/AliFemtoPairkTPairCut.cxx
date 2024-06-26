///
/// \file AliFemtoPairkTPairCut.cxx
///

#include "AliFemtoPairkTPairCut.h"
#include <string>
#include <cstdio>
#include <TMath.h>

#ifdef __ROOT__
  /// \cond CLASSIMP
  ClassImp(AliFemtoPairkTPairCut);
  /// \endcond
#endif

//__________________
AliFemtoPairkTPairCut::AliFemtoPairkTPairCut():
  AliFemtoPairCut(),
  fBetaTMin(0.0),
  fBetaTMax(1.0e6),
  fMassPart1(0.13957018),
  fMassPart2(0.13957018)
{ /* no-op */
}

//__________________
AliFemtoPairkTPairCut::AliFemtoPairkTPairCut(double minbetat, double maxbetat, double masspart1, double masspart2):
  AliFemtoPairCut(),
  fBetaTMin(minbetat),
  fBetaTMax(maxbetat),
  fMassPart1(masspart1),
  fMassPart2(masspart2)
{ /* no-op */
}

//__________________
AliFemtoPairkTPairCut::AliFemtoPairkTPairCut(const AliFemtoPairkTPairCut& c):
  AliFemtoPairCut(c),
  fBetaTMin(c.fBetaTMin),
  fBetaTMax(c.fBetaTMax),
  fMassPart1(c.fMassPart1),
  fMassPart2(c.fMassPart2)
{ /* no-op */
}

//__________________
AliFemtoPairkTPairCut::~AliFemtoPairkTPairCut()
{ /* no-op */
}

//__________________
AliFemtoPairkTPairCut& AliFemtoPairkTPairCut::operator=(const AliFemtoPairkTPairCut& c)
{
  if (this != &c) {
    AliFemtoPairCut::operator=(c);
    fBetaTMin = c.fBetaTMin;
    fBetaTMax = c.fBetaTMax;
    fMassPart1 = c.fMassPart1;
    fMassPart2 = c.fMassPart2;
  }
  return *this;
}

//__________________
AliFemtoString AliFemtoPairkTPairCut::Report()
{
  // Prepare a report from the execution
  TString report("AliFemtoBetaT Pair Cut \n");

  report += TString::Format("Accept pair with betaT in range %f , %f", fBetaTMin, fBetaTMax);

  return AliFemtoString((const char *)report);
}

//__________________
TList *AliFemtoPairkTPairCut::ListSettings() {
  // return a list of settings in a writable form
  TList *tListSetttings =  new TList();

  tListSetttings->Add(new TObjString(
    TString::Format("AliFemtoPairkTPairCut.betatmax=%f", fBetaTMax)));

  tListSetttings->Add(new TObjString(
    TString::Format("AliFemtoPairkTPairCut.betatmin=%f", fBetaTMin)));

  return tListSetttings;
}

//__________________
void AliFemtoPairkTPairCut::SetBetaTRange(double minbetat, double maxbetat)
{
  fBetaTMin = minbetat;
  fBetaTMax = maxbetat;
}

//__________________
void AliFemtoPairkTPairCut::SetParticleMasses(double masspart1, double masspart2)
{
  fMassPart1 = masspart1;
  fMassPart2 = masspart2;
}

//______________________________________________________
bool AliFemtoPairkTPairCut::Pass(const AliFemtoPair* pair)
{

  bool pairpass = true;

  // Calculate transverse momentum of the pair:
  double px1 = pair->Track1()->Track()->P().x();
  double px2 = pair->Track2()->Track()->P().x();
  double py1 = pair->Track1()->Track()->P().y();
  double py2 = pair->Track2()->Track()->P().y();
  double pxpair = px1 + px2;
  double pypair = py1 + py2;
  double pTpair = TMath::Sqrt(pxpair*pxpair + pypair*pypair);
  // Calculate energies of particles:
  double pz1 = pair->Track1()->Track()->P().z();
  double pz2 = pair->Track2()->Track()->P().z();
  double pzpair = pz1 + pz2;
  double p1 = TMath::Sqrt(px1*px1 + py1*py1 + pz1*pz1);
  double p2 = TMath::Sqrt(px2*px2 + py2*py2 + pz2*pz2);
  double m1 = fMassPart1;
  double m2 = fMassPart2;
  double e1 = TMath::Sqrt(p1*p1 + m1*m1);
  double e2 = TMath::Sqrt(p2*p2 + m2*m2);
  // Calculate transverse mass of the pair:
  double mInvpair_2 = m1*m1 + m2*m2 + 2*(e1*e2 - px1*px2 - py1*py2 - pz1*pz2);
  double mTpair = TMath::Sqrt(mInvpair_2 + pTpair*pTpair);
  // Calculate betaT:
  double betaT = pTpair / mTpair;

  double kT = TMath::Sqrt(pTpair)/2.0;


  // Check if betaT is in range:
  if(kT < fBetaTMin)
    pairpass = false;
  if(kT > fBetaTMax)
    pairpass = false;

  return pairpass;
}
