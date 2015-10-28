// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// M113 idler subsystem.
//
// =============================================================================

#include "chrono/assets/ChTriangleMeshShape.h"
#include "chrono/utils/ChUtilsInputOutput.h"

#include "chrono_vehicle/ChVehicleModelData.h"

#include "m113/M113_Idler.h"

using namespace chrono;
using namespace chrono::vehicle;

namespace m113 {

// -----------------------------------------------------------------------------
// Static variables
// -----------------------------------------------------------------------------
const double M113_Idler::m_wheel_mass = 429.5;
const ChVector<> M113_Idler::m_wheel_inertia(12.55, 14.70, 12.55);
const double M113_Idler::m_wheel_radius = 0.255;
const double M113_Idler::m_wheel_width = 0.181;
const double M113_Idler::m_wheel_gap = 0.051;

const double M113_Idler::m_carrier_mass = 50;
const ChVector<> M113_Idler::m_carrier_inertia(2, 2, 2);
const double M113_Idler::m_carrier_radius = 0.01;

const double M113_Idler::m_tensioner_free_length = 1;

const std::string M113_IdlerLeft::m_meshName = "Idler_L_POV_geom";
const std::string M113_IdlerLeft::m_meshFile = vehicle::GetDataFile("M113/Idler_L.obj");

const std::string M113_IdlerRight::m_meshName = "Idler_R_POV_geom";
const std::string M113_IdlerRight::m_meshFile = vehicle::GetDataFile("M113/Idler_R.obj");

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class M113_TensionerForce : public ChSpringForceCallback {
  public:
    M113_TensionerForce() {
        //// TODO
    }

    virtual double operator()(double time, double rest_length, double length, double vel) override {
        //// TODO
        return 0;
    }
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
M113_Idler::M113_Idler(const std::string& name, VisualizationType vis_type)
    : ChDoubleIdler(name), m_vis_type(vis_type) {
    //// TODO
    m_tensionerForceCB = new M113_TensionerForce();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void M113_Idler::Initialize(ChSharedPtr<ChBodyAuxRef> chassis, const ChVector<>& location) {
    // Invoke the base class method to perform the actual initialization
    ChDoubleIdler::Initialize(chassis, location);

    // Attach visualization
    switch (m_vis_type) {
        case PRIMITIVES:
            AddWheelVisualization();

            break;
        case MESH: {
            geometry::ChTriangleMeshConnected trimesh;
            trimesh.LoadWavefrontMesh(GetMeshFile(), false, false);

            ChSharedPtr<ChTriangleMeshShape> trimesh_shape(new ChTriangleMeshShape);
            trimesh_shape->SetMesh(trimesh);
            trimesh_shape->SetName(GetMeshName());
            m_wheel->AddAsset(trimesh_shape);

            break;
        }
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
const ChVector<> M113_Idler::GetLocation(PointId which) {
    //// TODO
    switch (which) {
        case WHEEL:
            return ChVector<>(0, 0, 0);
        case CARRIER:
            return ChVector<>(0, -0.1, 0);
        case CARRIER_CHASSIS:
            return ChVector<>(0, -0.2, 0);
        case TSDA_CARRIER:
            return ChVector<>(0, -0.2, 0);
        case TSDA_CHASSIS:
            return ChVector<>(0.5, -0.2, 0);
        default:
            return ChVector<>(0, 0, 0);
    }
}

}  // end namespace m113
