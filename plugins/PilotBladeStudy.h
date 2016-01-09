#ifndef PilotBladeStudy_h
#define PilotBladeStudy_h

/** \class PilotBladeStudy
 * Author: Tamas Almos Vami
 * Year: 2015
 * Desciption header file of the PilotBladeStudy.cc
 ************************************************************/

// ----------------------------------------------------------------------------------------
// CMSSW Version:
#define CMSSW_VER 75

#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
//#include "TrackingTools/PatternTools/interface/TrajectoryFitter.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryFitter.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryStateCombiner.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "Alignment/OfflineValidation/interface/TrackerValidationVariables.h"
#include "TrackingTools/TrackAssociator/interface/TrackAssociatorParameters.h"
#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TObject.h"
#include "TH1D.h"
#include "TFile.h"


#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonTime.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
#include "RecoMuon/GlobalTrackingTools/interface/GlobalMuonTrackMatcher.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/SiPixelRawData/interface/SiPixelRawDataError.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DQM/SiStripCommon/interface/SiStripFolderOrganizer.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "RecoLocalTracker/ClusterParameterEstimator/interface/PixelClusterParameterEstimator.h"


//#include "Geometry/TrackerTopology/interface/RectangularPixelTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"
#include <Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h>
#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "RecoTracker/MeasurementDet/interface/MeasurementTracker.h"
#include "RecoTracker/Record/interface/CkfComponentsRecord.h"
#include "TrackingTools/KalmanUpdators/interface/Chi2MeasurementEstimator.h"
#include "TrackingTools/DetLayers/interface/DetLayer.h"
#include "RecoTracker/TkDetLayers/interface/GeometricSearchTracker.h"
#include "TrackingTools/MeasurementDet/interface/LayerMeasurements.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Common/interface/ConditionsInEdm.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include <DataFormats/Scalers/interface/Level1TriggerScalers.h>
#include <DataFormats/Common/interface/EDCollection.h>
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandPoissonQ.h"
// SimDataFormats
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

// For ROOT
#include <TROOT.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStopwatch.h>

// STD
#include <memory>
#include <string>
#include <iostream>
#include <vector>

// For Resolution
#include "Geometry/CommonTopologies/interface/Topology.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/Records/interface/TransientRecHitRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHitBuilder.h"
#include "RecoTracker/TransientTrackingRecHit/interface/TkTransientTrackingRecHitBuilder.h"


#define NOVAL_I -9999
#define NOVAL_F -9999.0

using namespace reco;
class TTree;
class TFile;
class RectangularPixelTopology;
class TObject;


class PilotBladeStudy : public edm::EDAnalyzer
{
 public:
  
  explicit PilotBladeStudy(const edm::ParameterSet&);
  virtual ~PilotBladeStudy();
  virtual void beginJob();
  virtual void endJob();
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
 private:
  edm::ParameterSet iConfig_;
  edm::ESHandle<TrackerGeometry> tkGeom_;
  edm::ESHandle<MagneticField> magneticField_;
  
  edm::EDGetTokenT<reco::BeamSpot>                  		tok_BS_;
  edm::EDGetTokenT< edm::DetSetVector<SiPixelRawDataError> >	tok_siPixelDigis_;
  edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> >	tok_siPixelClusters_;
  edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> >	tok_PBClusters_;
  edm::EDGetTokenT< edm::AssociationMap<edm::OneToOne<std::vector<Trajectory>,std::vector<reco::Track>,unsigned short> > >	tok_Refitter_;
//   edm::EDGetTokenT< edm::ConditionsInRunBlock>	tok_conditionsInEdm_;


  TTree* eventTree_;
  TTree* trackTree_;
  TTree* clustTree_;
  TTree* trajTree_;
  TFile* outfile_;

  bool usePixelCPE_;
  bool isNewLS_;
    
  unsigned int nHits=0;
  float nPBHits=0.0;

 public:

  // Event info
	class EventData {
	public:
	  int fill;
    int run;
    int ls;
    int evt;

    int nclu[4]; // [0: fpix, i: layer i]
    int npix[4]; // [0: fpix, i: layer i]
    
    float intlumi;
    float instlumi;
    int ntracks;
    int federrs_size;
    // must be the last variable of the object saved to TTree:
    int federrs[16][2]; // [error index] [0:Nerror, 1:errorType]
    
    std::string list;

    EventData() { init(); };
    void init() {
      fill=NOVAL_I;
      run=NOVAL_I;
      ls=NOVAL_I;
      evt=NOVAL_I;
      
      for (size_t i=0; i<4; i++) nclu[i]=npix[i]=NOVAL_I;
      
      intlumi=NOVAL_F;
      instlumi=NOVAL_F;
      ntracks=NOVAL_I;
      federrs_size=0;
      for (size_t i=0; i<16; i++) federrs[i][0]=federrs[i][1]=NOVAL_I;

      
      list="fill/I:run/I:ls/I:evt/I:nclu[4]/I:npix[4]/I:intlumi/F:instlumi/F:ntracks/I:federrs_size/I:"
      "federrs[federrs_size][2]";
    }
  } evt_;

  // Track info
  class TrackData {
   public:
    float pt;
    float ndof;
    float chi2;
    float eta;
    float phi;

    std::string list;
   
    TrackData() { init(); }
    void init() {

      pt=NOVAL_F;
      ndof=NOVAL_F;
			chi2=NOVAL_F;
      eta=NOVAL_F;
      phi=NOVAL_F;

      list=	"pt/F:ndof/F:chi2/F:eta/F:phi/F";
    }
  };

  std::vector<TrackData> tracks_;

// Cluster info
  class ClustData {
   public:
    // Paired branches (SPLIT mode)
    float x;
    float y;
    float glx;
    float gly;
    float glz;
    int sizeX;
    int sizeY;

    int i; // serial num of cluster in the given module
    int edge;     // set if there is a valid hit
    int size;
    float charge;

    float adc[1000];
    float pixX[1000];
    float pixY[1000];

    std::string list;

    ClustData() { init(); }
    void init() {
      x=NOVAL_F;
      y=NOVAL_F;
      glx=NOVAL_F;
      gly=NOVAL_F;
      glz=NOVAL_F;
      sizeX=NOVAL_I;
      sizeY=NOVAL_I;
      i=NOVAL_I;
      edge=NOVAL_I;
      size=0;
      charge=NOVAL_F;
      for (size_t i=0; i<1000; i++) { adc[i]=pixX[i]=pixY[i]=NOVAL_F; }


      list="x/F:y/F:glx/F:gly/F:glz/F:sizeX/I:sizeY/I:i/I:edge/I:size/I:charge/F:adc[size]/F";
    }
    
    
  
  };
  // Module info
  class ModuleData {
   public:
    int det;
    int layer;
    int ladder;
    int half;
    int module;
    int disk;
    int blade;
    int panel;
    
    int federr;

    int side;
    int shl;

    int outer;

    unsigned int rawid;
    
    std::map<int, std::string> federrortypes;

    std::string list;

    ModuleData() { init(); }
    void init() {
      det=NOVAL_I;
      layer=NOVAL_I;
      ladder=NOVAL_I;
      half=NOVAL_I;
      module=NOVAL_I;
      disk=NOVAL_I;
      blade=NOVAL_I;
      panel=NOVAL_I;
      federr = NOVAL_I;
      side=NOVAL_I;
      shl=NOVAL_I;
      outer=NOVAL_I;
      rawid=abs(NOVAL_I);

      federrortypes.insert(std::pair<int, std::string>(25, "invalidROC"));
      federrortypes.insert(std::pair<int, std::string>(26, "gap word"));
      federrortypes.insert(std::pair<int, std::string>(27, "dummy word"));
      federrortypes.insert(std::pair<int, std::string>(28, "FIFO full error"));
      federrortypes.insert(std::pair<int, std::string>(29, "timeout error"));
      federrortypes.insert(std::pair<int, std::string>(30, "TBM error trailer"));
      federrortypes.insert(std::pair<int, std::string>(31, "event number error (TBM and FED event number mismatch)"));
      federrortypes.insert(std::pair<int, std::string>(32, "incorrectly formatted Slink Header"));
      federrortypes.insert(std::pair<int, std::string>(33, "incorrectly formatted Slink Trailer"));
      federrortypes.insert(std::pair<int, std::string>(34, "the event size encoded in the Slink Trailer is different than the size found at raw to digi conversion "));
      federrortypes.insert(std::pair<int, std::string>(35, "invalid FED channel number"));
      federrortypes.insert(std::pair<int, std::string>(36, "invalid ROC value "));
      federrortypes.insert(std::pair<int, std::string>(37, "invalid dcol or pixel value "));
      federrortypes.insert(std::pair<int, std::string>(38, "the pixels on a ROC weren't read out from lowest to highest row and dcol value"));
      federrortypes.insert(std::pair<int, std::string>(39, "CRC error"));
      
      list="det/I:layer/I:ladder/I:half/I:module/I:disk/I:blade/I:panel/I:"
      "federr/I:side/I:shl/I:outer/I:rawid/i";
    }

    std::string shell() {
      std::ostringstream ss;
      if (det==0) {
	ss << "B" << ((module>0) ? "p" : "m") << ((ladder>0) ? "I" : "O");
      } else if (det==1) {
	ss << "B" << ((disk>0) ? "p" : "m") << ((blade>0) ? "I" : "O");
      }
      return ss.str();
    }

    int shell_num() {
      if (det==0)      return ((module>0) ? 0 : 2) + ((ladder>0) ? 0 : 1);
      else if (det==1) return ((disk>0) ? 0 : 2) + ((blade>0) ? 0 : 1);
      return -1;
    }
    
    std::string federr_name() {
      std::map<int, std::string>::const_iterator it=federrortypes.find(federr);
      return (it!=federrortypes.end()) ? it->second : "FED error not interpreted";
    }
    
  };

  // Trajectory info
  class TrajMeasData {
   public:

    float lx;
    float ly;
    float glx;
    float gly;
    float glz;
    float res_dx;
    float res_dz;
    int hit_near;
    
    int nclu_mod;
    int nclu_roc;
    int npix_mod;
    int npix_roc;

    float dx_cl[2];
    float dx_cl_corr[2];
    float dy_cl[2];
    float dy_cl_corr[2];
    float dx_hit;
    float dy_hit;

    int i; // serial num of trajectory measurement on the (single) track of the event
    int onEdge;
    int type;

    float lx_err;
    float ly_err;
    float d_cl[2];

    float alpha;
    float beta;
    float norm_charge;

    std::string list;

    TrajMeasData() { init(); }
    void init() {
      lx=NOVAL_F;
      ly=NOVAL_F;

      glx=NOVAL_F;
      
      gly=NOVAL_F;
      glz=NOVAL_F;
            
      res_dx=NOVAL_F;
      res_dz=NOVAL_F;
      hit_near=NOVAL_I;
      
      dx_cl[0]=dx_cl[1]=NOVAL_F;
      dx_cl_corr[0]=dx_cl_corr[1]=NOVAL_F;
      dy_cl[0]=dy_cl[1]=NOVAL_F;
      dx_cl_corr[0]=dy_cl_corr[1]=NOVAL_F;
      dx_hit=NOVAL_F;
      dy_hit=NOVAL_F;
      

      i=NOVAL_I;
      onEdge=NOVAL_I;
      type=NOVAL_I;
      
      lx_err=NOVAL_F;
      ly_err=NOVAL_F;
      d_cl[0]=d_cl[1]=NOVAL_F;

      alpha=NOVAL_F;
      beta=NOVAL_F;
      norm_charge=NOVAL_F;

      list="lx/F:ly/F:glx/F:gly/F:glz/F:res_dx/F:res_dz/F:hit_near/I:nclu_mod/I:nclu_roc/I:npix_mod/I:npix_roc/I:"
	    "dx_cl[2]/F:dx_cl_corr[2]/F:dy_cl[2]/F:dy_cl_corr[2]/F:dx_hit/F:dy_hit/F:i/I:onEdge/I:type/I:lx_err/F:ly_err/F:d_cl[2]/F:alpha/F:beta/F:norm_charge/F";
    }

  };
  class Cluster : public ClustData {
   public:

    ModuleData mod; // offline module number
    ModuleData mod_on; // online module number

    Cluster() { mod.init(); mod_on.init();}
    void init() {
      ClustData::init();
      mod.init();
      mod_on.init();
    }
    
  };

  std::vector<Cluster> clust_;


  class TrajMeasurement : public TrajMeasData {
   public:
    ModuleData mod; // offline module number
    ModuleData mod_on; // online module number
    ClustData clu;
    TrackData trk;

    TrajMeasurement() { mod.init(); mod_on.init(); trk.init(); }
    void init() {
      TrajMeasData::init();
      mod.init();
      mod_on.init();
      trk.init();
    }
  };

  std::vector<std::vector<TrajMeasurement> > trajmeas_;
  
  void init_all() {
    evt_.init();
    tracks_.clear();
    trajmeas_.clear();
    clust_.clear();
  }

  ModuleData getModuleData(uint32_t rawId, const std::map<uint32_t, int>& federrors, std::string scheme="offline");

//   void analyzeClusters(const edm::Event&, const edm::EventSetup&, std::string, std::map<uint32_t, int> federrors);
  void analyzeClusters(const edm::Event&, const edm::EventSetup&, edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> >, std::map<uint32_t, int> federrors);
  
  int get_RocID_from_cluster_coords(const float&, const float&, const ModuleData&);
  int get_RocID_from_local_coords(const float&, const float&, const ModuleData&);
				
  void findClosestClusters(const edm::Event&, const edm::EventSetup&, uint32_t, 
			   float, float, float*, float*, edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> >, ClustData&);
			    

};

#endif
