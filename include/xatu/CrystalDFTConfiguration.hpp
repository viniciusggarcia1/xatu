#pragma once
#include <armadillo>
#include "xatu/SystemConfiguration.hpp"


typedef std::vector<std::vector<std::vector<double>>> cube_vector;

namespace xatu {

class CrystalDFTConfiguration : public SystemConfiguration {

    public:
        int ndim, natoms, norbitals, nshells, nspecies;
        int totalElectrons, coreElectrons;
        bool SOC_FLAG = false;
        
        arma::mat motif, bravaisLattice;
        
        std::vector<int> shellsPerSpecies;
        std::vector<int> orbitalsPerSpecies;
        std::map<int, std::vector<std::string>> shellTypesPerSpecies;
        std::map<int, cube_vector> gaussianCoefficients;

        arma::mat bravaisVectors;
        arma::cx_cube overlapMatrices, fockMatrices;

    public:
        CrystalDFTConfiguration(std::string, int ncells = 20);
        virtual ~CrystalDFTConfiguration(){std::cout << "Calling CrystalDFTConfig destructor..." << std::endl;};


        void parseContent(int, double threshold = 100.);

    private:
        void parseBravaisLattice(double);
        void parseAtoms();
        void parseAtomicBasis();
        arma::cx_mat parseMatrix();
        void extractDimension(double);

        void mapContent();
};

}

size_t split(const std::string&, std::vector<double>&);