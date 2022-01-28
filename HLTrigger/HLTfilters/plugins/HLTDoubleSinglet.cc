/** \class HLTDoubleSinglet
 *
 * See header file for documentation
 *
 *
 *  \author Jaime Leon Holgado
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "HLTDoubleSinglet.h"

#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"

#include "DataFormats/Candidate/interface/Particle.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "HLTrigger/HLTcore/interface/defaultModuleLabel.h"
#include <cmath>

//
// constructors and destructor
//
template <typename T1, typename T2, typename T3>
HLTDoubleSinglet<T1, T2, T3>::HLTDoubleSinglet(const edm::ParameterSet& iConfig)
    : HLTFilter(iConfig),
      originTag1_(iConfig.template getParameter<std::vector<edm::InputTag>>("originTag1")),
      originTag2_(iConfig.template getParameter<std::vector<edm::InputTag>>("originTag2")),
      originTag3_(iConfig.template getParameter<std::vector<edm::InputTag>>("originTag3")),
      inputTag1_(iConfig.template getParameter<edm::InputTag>("inputTag1")),
      inputTag2_(iConfig.template getParameter<edm::InputTag>("inputTag2")),
      inputTag3_(iConfig.template getParameter<edm::InputTag>("inputTag3")),
      inputToken1_(consumes<trigger::TriggerFilterObjectWithRefs>(inputTag1_)),
      inputToken2_(consumes<trigger::TriggerFilterObjectWithRefs>(inputTag2_)),
      inputToken3_(consumes<trigger::TriggerFilterObjectWithRefs>(inputTag3_)),
      triggerType1_(iConfig.template getParameter<int>("triggerType1")),
      triggerType2_(iConfig.template getParameter<int>("triggerType2")),
      triggerType3_(iConfig.template getParameter<int>("triggerType3")),
      min_Dphi_(iConfig.template getParameter<double>("MinDphi")),
      max_Dphi_(iConfig.template getParameter<double>("MaxDphi")),
      min_Deta_(iConfig.template getParameter<double>("MinDeta")),
      max_Deta_(iConfig.template getParameter<double>("MaxDeta")),
      min_Minv_(iConfig.template getParameter<double>("MinMinv")),
      max_Minv_(iConfig.template getParameter<double>("MaxMinv")),
      min_DelR_(iConfig.template getParameter<double>("MinDelR")),
      max_DelR_(iConfig.template getParameter<double>("MaxDelR")),
      min_Pt_(iConfig.template getParameter<double>("MinPt")),
      max_Pt_(iConfig.template getParameter<double>("MaxPt")),
      min_N_(iConfig.template getParameter<int>("MinN")),
      same12_(inputTag1_.encode() == inputTag2_.encode()),  // same collections to be compared?
      same13_(inputTag1_.encode() == inputTag3_.encode()),  // same collections to be compared?
      same23_(inputTag2_.encode() == inputTag3_.encode()),  // same collections to be compared?
      cutdphi_(min_Dphi_ <= max_Dphi_),                   // cut active?
      cutdeta_(min_Deta_ <= max_Deta_),                   // cut active?
      cutminv_(min_Minv_ <= max_Minv_),                   // cut active?
      cutdelr_(min_DelR_ <= max_DelR_),                   // cut active?
      cutpt_(min_Pt_ <= max_Pt_)                          // cut active?
{
  LogDebug("") << "InputTags and cuts : " << inputTag1_.encode() << " " << inputTag2_.encode() << " " << inputTag3_.encode()
               << triggerType1_ << " " << triggerType2_ << " " << triggerType3_ 
               << " Dphi [" << min_Dphi_ << " " << max_Dphi_ << "]"
               << " Deta [" << min_Deta_ << " " << max_Deta_ << "]"
               << " Minv [" << min_Minv_ << " " << max_Minv_ << "]"
               << " DelR [" << min_DelR_ << " " << max_DelR_ << "]"
               << " Pt   [" << min_Pt_ << " " << max_Pt_ << "]"
               << " MinN =" << min_N_ << " same12/same13/same23/dphi/deta/minv/delr/pt " 
               << same12_ << same13_ << same23_ << cutdphi_ << cutdeta_ << cutminv_
               << cutdelr_ << cutpt_;
}

template <typename T1, typename T2, typename T3>
HLTDoubleSinglet<T1, T2, T3>::~HLTDoubleSinglet() = default;
template <typename T1, typename T2, typename T3>
void HLTDoubleSinglet<T1, T2, T3>::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  makeHLTFilterDescription(desc);
  std::vector<edm::InputTag> originTag1(1, edm::InputTag("hltOriginal1"));
  std::vector<edm::InputTag> originTag2(1, edm::InputTag("hltOriginal2"));
  std::vector<edm::InputTag> originTag3(1, edm::InputTag("hltOriginal3"));
  desc.add<std::vector<edm::InputTag>>("originTag1", originTag1);
  desc.add<std::vector<edm::InputTag>>("originTag2", originTag2);
  desc.add<std::vector<edm::InputTag>>("originTag3", originTag3);
  desc.add<edm::InputTag>("inputTag1", edm::InputTag("hltFiltered1"));
  desc.add<edm::InputTag>("inputTag2", edm::InputTag("hltFiltered2"));
  desc.add<edm::InputTag>("inputTag3", edm::InputTag("hltFiltered3"));
  desc.add<int>("triggerType1", 0);
  desc.add<int>("triggerType2", 0);
  desc.add<int>("triggerType3", 0);
  desc.add<double>("MinDphi", +1.0);
  desc.add<double>("MaxDphi", -1.0);
  desc.add<double>("MinDeta", +1.0);
  desc.add<double>("MaxDeta", -1.0);
  desc.add<double>("MinMinv", +1.0);
  desc.add<double>("MaxMinv", -1.0);
  desc.add<double>("MinDelR", +1.0);
  desc.add<double>("MaxDelR", -1.0);
  desc.add<double>("MinPt", +1.0);
  desc.add<double>("MaxPt", -1.0);
  desc.add<int>("MinN", 1);
  descriptions.add(defaultModuleLabel<HLTDoubleSinglet<T1, T2, T3>>(), desc);
}

//
// member functions
//

// ------------ method called to produce the data  ------------
template <typename T1, typename T2, typename T3>
bool HLTDoubleSinglet<T1, T2, T3>::hltFilter(edm::Event& iEvent,
                                   const edm::EventSetup& iSetup,
                                   trigger::TriggerFilterObjectWithRefs& filterproduct) const {
  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace trigger;

  // All HLT filters must create and fill an HLT filter object,
  // recording any reconstructed physics objects satisfying (or not)
  // this HLT filter, and place it in the Event.

  bool accept(false);

  LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 0 " << std::endl;

  std::vector<T1Ref> coll1;
  std::vector<T2Ref> coll2;
  std::vector<T3Ref> coll3;

  // get hold of pre-filtered object collections
  Handle<TriggerFilterObjectWithRefs> handle1, handle2, handle3;
  if (iEvent.getByToken(inputToken1_, handle1) && iEvent.getByToken(inputToken2_, handle2) 
      && iEvent.getByToken(inputToken3_, handle3)) {
    handle1->getObjects(triggerType1_, coll1);
    handle2->getObjects(triggerType2_, coll2);
    handle3->getObjects(triggerType3_, coll3);
    const size_type n1(coll1.size());
    const size_type n2(coll2.size());
    const size_type n3(coll3.size());

    if (saveTags()) {
      InputTag tagOld;
      for (unsigned int i = 0; i < originTag1_.size(); ++i) {
        filterproduct.addCollectionTag(originTag1_[i]);
        LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 1a/" << i << " " << originTag1_[i].encode()
                                  << std::endl;
      }
      tagOld = InputTag();
      for (size_type i1 = 0; i1 != n1; ++i1) {
        const ProductID pid(coll1[i1].id());
        const auto& prov = iEvent.getStableProvenance(pid);
        const string& label(prov.moduleLabel());
        const string& instance(prov.productInstanceName());
        const string& process(prov.processName());
        InputTag tagNew(InputTag(label, instance, process));
        if (tagOld.encode() != tagNew.encode()) {
          filterproduct.addCollectionTag(tagNew);
          tagOld = tagNew;
          LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 1b " << tagNew.encode() << std::endl;
        }
      }
      for (unsigned int i = 0; i < originTag2_.size(); ++i) {
        filterproduct.addCollectionTag(originTag2_[i]);
        LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 2a/" << i << " " << originTag2_[i].encode()
                                  << std::endl;
      }
      tagOld = InputTag();
      for (size_type i2 = 0; i2 != n2; ++i2) {
        const ProductID pid(coll2[i2].id());
        const auto& prov = iEvent.getStableProvenance(pid);
        const string& label(prov.moduleLabel());
        const string& instance(prov.productInstanceName());
        const string& process(prov.processName());
        InputTag tagNew(InputTag(label, instance, process));
        if (tagOld.encode() != tagNew.encode()) {
          filterproduct.addCollectionTag(tagNew);
          tagOld = tagNew;
          LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 2b " << tagNew.encode() << std::endl;
        }
      }
      for (unsigned int i = 0; i < originTag3_.size(); ++i) {
        filterproduct.addCollectionTag(originTag3_[i]);
        LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 3a/" << i << " " << originTag3_[i].encode()
                                  << std::endl;
      }
      tagOld = InputTag();
      for (size_type i3 = 0; i3 != n3; ++i3) {
        const ProductID pid(coll3[i3].id());
        const auto& prov = iEvent.getStableProvenance(pid);
        const string& label(prov.moduleLabel());
        const string& instance(prov.productInstanceName());
        const string& process(prov.processName());
        InputTag tagNew(InputTag(label, instance, process));
        if (tagOld.encode() != tagNew.encode()) {
          filterproduct.addCollectionTag(tagNew);
          tagOld = tagNew;
          LogVerbatim("HLTDoubleSinglet") << " XXX " << moduleLabel() << " 3b " << tagNew.encode() << std::endl;
        }
      }
    }

    int n(0);
    T1Ref r1;
    T2Ref r2;
    T3Ref r3;
    Particle::LorentzVector p1, p2, p3, p13, p23;
    for (unsigned int i1 = 0; i1 != n1; i1++) {
      r1 = coll1[i1];
      p1 = r1->p4();
      unsigned int I(0);
      if (same12_) {
        I = i1 + 1;
      }
      for (unsigned int i2 = I; i2 != n2; i2++) {
        r2 = coll2[i2];
        p2 = r2->p4();
        
        unsigned int Ip(0);
        if (same23_) {
          Ip = I + 1;
        } else if (same13_) {
          Ip = i1 + 1;
        }

        for (unsigned int i3 = Ip; i3 != n3; i3++) {
          r3 = coll3[i3];
          p3 = r3->p4();
          
          double Dphi13(std::abs(p1.phi() - p3.phi()));
          double Dphi23(std::abs(p2.phi() - p3.phi()));
          if (Dphi13 > M_PI)
            Dphi13 = 2.0 * M_PI - Dphi13;
          if (Dphi23 > M_PI)
            Dphi23 = 2.0 * M_PI - Dphi23;

          double Deta13(std::abs(p1.eta() - p3.eta()));
          double Deta23(std::abs(p2.eta() - p3.eta()));

          p13 = p1 + p3;
          p23 = p2 + p3;
          double Minv13(std::abs(p13.mass()));
          double Minv23(std::abs(p23.mass()));
          double Pt13(p13.pt());
          double Pt23(p23.pt());

          double DelR13(sqrt(Dphi13 * Dphi13 + Deta13 * Deta13));
          double DelR23(sqrt(Dphi23 * Dphi23 + Deta23 * Deta23));

          if (((!cutdphi_) || ((min_Dphi_ <= Dphi13) && (Dphi13 <= max_Dphi_))) &&
              ((!cutdphi_) || ((min_Dphi_ <= Dphi23) && (Dphi23 <= max_Dphi_))) &&
              ((!cutdeta_) || ((min_Deta_ <= Deta13) && (Deta13 <= max_Deta_))) &&
              ((!cutdeta_) || ((min_Deta_ <= Deta23) && (Deta23 <= max_Deta_))) &&
              ((!cutminv_) || ((min_Minv_ <= Minv13) && (Minv13 <= max_Minv_))) &&
              ((!cutminv_) || ((min_Minv_ <= Minv23) && (Minv23 <= max_Minv_))) &&
              ((!cutdelr_) || ((min_DelR_ <= DelR13) && (DelR13 <= max_DelR_))) &&
              ((!cutdelr_) || ((min_DelR_ <= DelR23) && (DelR23 <= max_DelR_))) &&
              ((!cutpt_) || ((min_Pt_ <= Pt13) && (Pt13 <= max_Pt_))) &&
              ((!cutpt_) || ((min_Pt_ <= Pt23) && (Pt23 <= max_Pt_)))) {
            n++;
            filterproduct.addObject(triggerType1_, r1);
            filterproduct.addObject(triggerType2_, r2);
            filterproduct.addObject(triggerType3_, r3);
          }
        }
      }
    }
    // filter decision
    accept = (n >= min_N_);
  }

  return accept;
}
