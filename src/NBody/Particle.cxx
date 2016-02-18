/*! \file Particle.cxx
 *  \brief This file implements functions from \ref NBody::Particle and derived classes

*/

#include <Particle.h>

using namespace std;
using namespace Math;

namespace NBody
{
    int PIDCompare (const void *a, const void *b)
    {
        Int_t aa = ((Particle*)a)->GetPID();
        Int_t bb = ((Particle*)b)->GetPID();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    int IDCompare (const void *a, const void *b)
    {
        Int_t aa = ((Particle*)a)->GetID();
        Int_t bb = ((Particle*)b)->GetID();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    int RadCompare (const void *a, const void *b)
    {
        Double_t aa = ((Particle*)a)->Radius();
        Double_t bb = ((Particle*)b)->Radius();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    int TypeCompare (const void *a, const void *b)
    {
        int aa = ((Particle*)a)->GetType();
        int bb = ((Particle*)b)->GetType();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    int DenCompare (const void *a, const void *b)
    {
        Double_t aa = ((Particle*)a)->GetDensity();
        Double_t bb = ((Particle*)b)->GetDensity();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    int PotCompare (const void *a, const void *b)
    {
        Double_t aa = ((Particle*)a)->GetPotential();
        Double_t bb = ((Particle*)b)->GetPotential();
        if (aa > bb) return 1;
        else if (aa < bb) return -1;
        else return 0;
    }
    /*-----------------------
        Particle functions
      -----------------------*/
    // Constructors
    Particle::Particle(Double_t Mass, Double_t x, Double_t y, Double_t z,
                        Double_t vx, Double_t vy, Double_t vz, Int_t ID, int Type, Double_t Rho, Double_t Phi, Int_t PID)
    {
#ifndef NOMASS
        mass = Mass;
#endif
        position[0] = x;
        position[1] = y;
        position[2] = z;

        velocity[0] = vx;
        velocity[1] = vy;
        velocity[2] = vz;

        id=ID;
        type=Type;
        rho=Rho;
        phi=Phi;
        pid=PID;
#ifdef GASON
        u=0;
        sphden=0;
#endif
#ifdef STARON
        tage=0;
#endif
#if defined (GASON) && (STARON)
        zmet=0;
        sfr=0;
#endif
    }

    Particle::Particle(Double_t Mass, Double_t *NewPos, Double_t *NewVel, Int_t ID, int Type, Double_t Rho, Double_t Phi, Int_t PID)
    {
#ifndef NOMASS
        mass = Mass;
#endif
        position[0] = NewPos[0];
        position[1] = NewPos[1];
        position[2] = NewPos[2];

        velocity[0] = NewVel[0];
        velocity[1] = NewVel[1];
        velocity[2] = NewVel[2];

        id=ID;
        type=Type;
        rho=Rho;
        phi=Phi;
        pid=PID;
#ifdef GASON
        u=0;
        sphden=0;
#endif
#ifdef STARON
        tage=0;
#endif
#if defined (GASON) && (STARON)
        zmet=0;
        sfr=0;
#endif
    }


    // Copy constructor: only copy if not same object
    Particle::Particle(const Particle &p)
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];
            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            pid=p.pid;
#ifdef GASON
            u=p.u;
            sphden=p.sphden;
#endif
#ifdef STARON
            tage=p.tage;
#endif
#if defined (GASON) && (STARON)
            zmet=p.zmet;
            sfr=p.sfr;
#endif
        }
    }

    //    OPERATORS
    //assignment operator only carried out if not same object
    Particle& Particle::operator=(const Particle &p)
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];

            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            pid=p.pid;
#ifdef GASON
            u=p.u;
            sphden=p.sphden;
#endif
#ifdef STARON
            tage=p.tage;
#endif
#if defined (GASON) && (STARON)
            zmet=p.zmet;
            sfr=p.sfr;
#endif
        }
      return *this;
    }

    // Inserter: prints out the particle in ascii format,
    // e.g., cout << part;
    ostream &operator << (ostream &outs, const Particle &p)
    {
        outs.setf(ios::scientific);
        outs.setf(ios::showpos);
        outs.width(18); outs.precision(8);
#ifndef NOMASS
        outs << p.mass<<" ";
#else
		outs << MASSVAL<<" ";
#endif
        outs.width(18);
        outs << p.position[0]<<" ";
        outs.width(18);
        outs << p.position[1]<<" ";
        outs.width(18);
        outs << p.position[2]<<" ";
        outs.width(18);
        outs << p.velocity[0]<<" ";
        outs.width(18);
        outs << p.velocity[1]<<" ";
        outs.width(18);
        outs << p.velocity[2]<<" ";

        outs << p.id<<" ";
        outs << p.type<<" ";
        outs << p.rho<<" ";
        outs << p.phi<<" ";

        outs.unsetf(ios::showpos);
        outs.unsetf(ios::floatfield);
        return outs;
    }

/*
    // Extractor: sets particle attributes from a stream,
    // e.g., cin >> part;
    istream &operator >> (istream &ins, Particle &p)
    {
        cout << "Please enter the values: Mass, Position[3], Velocity[3], ID, Rho:"
          << endl;
        ins >> p.mass >> p.position[0] >> p.position[1] >> p.position[2]
            >> p.velocity[0] >> p.velocity[1] >> p.velocity[2]
            >>p.id>>p.rho>>p.phi;
#ifdef EXTENDEDPARTICLE
        cout<<"Enter Phi, Temp:"<<endl;
        ins>>p.phi>>p.temp ;
#endif
        return ins;
    }
*/
/*
    // Read a particle from an stream in binary format
    void Particle::Read(std::istream &F)
    {
        F.read((char*)&mass, sizeof(Double_t));
        F.read((char*)position, 3 * sizeof(Double_t));
        F.read((char*)velocity, 3 * sizeof(Double_t));
        F.read((char*)&id, sizeof(int));
        F.read((char*)&rho, sizeof(Double_t));
        F.read((char*)&phi, sizeof(Double_t));
#ifdef TEMP
        F.read((char*)&temp,sizeof(Double_t));
#endif
    }
*/
    // Write a particle to a stream in binary format
    void Particle::Write(std::ostream &F) const
    {
#ifndef NOMASS
        F.write((char*)&mass, sizeof(Double_t));
#endif
        F.write((char*)position, 3 * sizeof(Double_t));
        F.write((char*)velocity, 3 * sizeof(Double_t));
        F.write((char*)&id, sizeof(Int_t));
        F.write((char*)&type, sizeof(int));
        F.write((char*)&rho, sizeof(Double_t));
    }

    /* End of Particle */


    /*
        Sub Particle Classes: Gas and Star particles
    */
    GasParticle::GasParticle(Double_t Mass, Double_t x, Double_t y, Double_t z,
                        Double_t vx, Double_t vy, Double_t vz, Int_t ID, int Type, Double_t Rho, Double_t Phi, Double_t Temp, Double_t Ui, Double_t Pi, Double_t NE,Double_t NH0,Double_t Zi, Double_t SFR,Double_t LGS): Particle::Particle(Mass,x,y,z,vx,vy,vz,ID,Type,Rho,Phi)
    {
        temp = Temp;
        U = Ui;
        P = Pi;
        Ne = NE;
        Nh0 = NH0;
        metal = Zi;
        sfr = SFR;
        lgS=LGS;
    }

    GasParticle::GasParticle(Double_t Mass, Double_t *NewPos, Double_t *NewVel, Int_t ID, int Type, Double_t Rho, Double_t Phi, Double_t Temp, Double_t Ui, Double_t Pi, Double_t NE,Double_t NH0,Double_t Zi, Double_t SFR,Double_t LGS): Particle::Particle(Mass,NewPos,NewVel,ID,Type,Rho,Phi)
    {
        temp = Temp;
        U = Ui;
        P = Pi;
        Ne = NE;
        Nh0 = NH0;
        metal = Zi;
        sfr = SFR;
        lgS=LGS;
    }


    // Copy constructor
    GasParticle::GasParticle(const GasParticle &p) : Particle::Particle((Particle)p) 
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];
            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            temp = p.temp;
            U = p.U;
            P = p.P;
            Ne = p.Ne;
            Nh0 = p.Nh0;
            metal = p.metal;
            sfr = p.sfr;
            lgS=p.lgS;
        }
    }

    //    OPERATORS
    GasParticle& GasParticle::operator=(const GasParticle &p)
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];
            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            temp = p.temp;
            U = p.U;
            P = p.P;
            Ne = p.Ne;
            Nh0 = p.Nh0;
            metal = p.metal;
            sfr = p.sfr;
            lgS=p.lgS;
        }
        return *this;
    }

    
    StarParticle::StarParticle(Double_t Mass, Double_t x, Double_t y, Double_t z,
                        Double_t vx, Double_t vy, Double_t vz, Int_t ID, int Type, Double_t Rho, Double_t Phi, Double_t TF, Double_t Zi): Particle::Particle(Mass,x,y,z,vx,vy,vz,ID,Type,Rho,Phi)
    {
        tform=TF;
        metal=Zi;
    }

    StarParticle::StarParticle(Double_t Mass, Double_t *NewPos, Double_t *NewVel, Int_t ID, int Type, Double_t Rho, Double_t Phi, Double_t TF, Double_t Zi): Particle::Particle(Mass,NewPos,NewVel,ID,Type,Rho,Phi)
    {
        tform=TF;
        metal=Zi;
    }


    // Copy constructor
    StarParticle::StarParticle(const StarParticle &p) 
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];
            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            tform=p.tform;
            metal=p.metal;
        }
    }

    //    OPERATORS
    StarParticle& StarParticle::operator=(const StarParticle &p)
    {
        if (this!=&p) {
#ifndef NOMASS
            mass = p.mass;
#endif
            position[0] = p.position[0];
            position[1] = p.position[1];
            position[2] = p.position[2];
            velocity[0] = p.velocity[0];
            velocity[1] = p.velocity[1];
            velocity[2] = p.velocity[2];
            id=p.id;
            type=p.type;
            rho=p.rho;
            phi=p.phi;
            tform=p.tform;
            metal=p.metal;
        }
        return *this;
    }
}
