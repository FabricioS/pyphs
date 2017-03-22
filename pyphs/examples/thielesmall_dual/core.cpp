/*
    Copyright or (c) or Copr. Project-Team S3 (Sound Signals and Systems) and
    Analysis/Synthesis team, Laboratory of Sciences and Technologies of Music and
    Sound (UMR 9912), IRCAM-CNRS-UPMC, 1 place Igor Stravinsky, F-75004 Paris
    * contributors : Antoine Falaize, Thomas Helie,
    * corresponding contributor: antoine.falaize@ircam.fr
    * date: 2016/12/31 12:47:34

    This has been geerated by PyPHS which purpose is to generate C++
    code for the simulation of multiphysics system described by graph structures.

    This software is governed by the CeCILL-B license under French law and
    abiding by the rules of distribution of free software.  You can  use,
    modify and/ or redistribute the software under the terms of the CeCILL-B
    license as circulated by CEA, CNRS and INRIA at the following URL
    "http://www.cecill.info".

    As a counterpart to the access to the source code and  rights to copy,
    modify and redistribute granted by the license, users are provided only
    with a limited warranty  and the software's author,  the holder of the
    economic rights, and the successive licensors  have only  limited liability.

    In this respect, the user's attention is drawn to the risks associated
    with loading,  using,  modifying and/or developing or reproducing the
    software by the user in light of its specific status of free software,
    that may mean  that it is complicated to manipulate,  and  that  also
    therefore means  that it is reserved for developers  and  experienced
    professionals having in-depth computer knowledge. Users are therefore
    encouraged to load and test the software's suitability as regards their
    requirements in conditions enabling the security of their systems and/or
    data to be ensured and,  more generally, to use and operate it in the
    same conditions as regards security.

    The fact that you are presently reading this means that you have had
    knowledge of the CeCILL-B license and that you accept its terms.

    Created on 2016/12/31 12:47:34

    author: Antoine Falaize


===========================================================================

    This file was automatically generated by PyPHS, date 2017/03/11 22:54:49.

    It contains the code for the simulation of system 'PHSCORE'.

===========================================================================
*/

#include "core.h"

// PUBLIC    
    
    void PHSCORE::update(vector<double> & u_vec, vector<double> & p_vec){
    
        set_u(u_vec);
        set_p(p_vec);
        
        ud_x_update();
        set_x(_ud_x);
        jacFll_update();
        jacFnll_update();
        ijacFll_update();
        Gl_update();
        Gnl_update();
        ud_Fnl_update();
        set_Fnl(_ud_Fnl);
        res_Fnl_update();
        
        unsigned int iter_res_Fnl = 0;
        _step_Fnl = 1;
        while ((iter_res_Fnl<100) & (res_Fnl()>2.22044604925e-16) & (step_Fnl()>2.22044604925e-16)){    
            save_Fnl_update();
            jacGlnl_update();
            jacGnlnl_update();
            jacFnl_update();
            ijacFnl_update();
            ud_vnl_update();
            set_vnl(_ud_vnl);
            Gl_update();
            Gnl_update();
            ud_Fnl_update();
            set_Fnl(_ud_Fnl);
            res_Fnl_update();
            step_Fnl_update();iter_res_Fnl += 1;
        }
        
        ud_vl_update();
        set_vl(_ud_vl);
        dxH_update();
        z_update();
        y_update();
    }
    
    // Acessors to Arguments, return vector<double>
    
    
    vector<double> PHSCORE::x_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = *xM;    
        v[1] = *xL;    
        v[2] = *xK;    
        return v;
    }
    
    vector<double> PHSCORE::xl_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    
    vector<double> PHSCORE::xnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = *xM;    
        v[1] = *xL;    
        v[2] = *xK;    
        return v;
    }
    
    vector<double> PHSCORE::dx_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = *dxM;    
        v[1] = *dxL;    
        v[2] = *dxK;    
        return v;
    }
    
    vector<double> PHSCORE::dxl_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    
    vector<double> PHSCORE::dxnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = *dxM;    
        v[1] = *dxL;    
        v[2] = *dxK;    
        return v;
    }
    
    vector<double> PHSCORE::w_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = *wR;    
        v[1] = *wA;    
        return v;
    }
    
    vector<double> PHSCORE::wl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = *wR;    
        v[1] = *wA;    
        return v;
    }
    
    vector<double> PHSCORE::wnl_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    
    vector<double> PHSCORE::u_vector() const {    
        vector<double> v = vector<double>(1);    
        v[0] = *uIN;    
        return v;
    }
    
    vector<double> PHSCORE::p_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    
    vector<double> PHSCORE::v_vector() const {    
        vector<double> v = vector<double>(5);    
        v[0] = *dxM;    
        v[1] = *dxL;    
        v[2] = *dxK;    
        v[3] = *wR;    
        v[4] = *wA;    
        return v;
    }
    
    vector<double> PHSCORE::vl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = *wR;    
        v[1] = *wA;    
        return v;
    }
    
    vector<double> PHSCORE::vnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = *dxM;    
        v[1] = *dxL;    
        v[2] = *dxK;    
        return v;
    }
    
    // Acessors to Arguments, return Matrix<double, n, m>
    
    Matrix<double, 3, 1> PHSCORE::x() const {    
        Matrix<double, 3, 1> m;    
        m(0, 0) = *xM;    
        m(1, 0) = *xL;    
        m(2, 0) = *xK;    
        return m;
    }
    Matrix<double, 0, 1> PHSCORE::xl() const {    
        Matrix<double, 0, 1> m;    
        return m;
    }
    Matrix<double, 3, 1> PHSCORE::xnl() const {    
        Matrix<double, 3, 1> m;    
        m(0, 0) = *xM;    
        m(1, 0) = *xL;    
        m(2, 0) = *xK;    
        return m;
    }
    Matrix<double, 3, 1> PHSCORE::dx() const {    
        Matrix<double, 3, 1> m;    
        m(0, 0) = *dxM;    
        m(1, 0) = *dxL;    
        m(2, 0) = *dxK;    
        return m;
    }
    Matrix<double, 0, 1> PHSCORE::dxl() const {    
        Matrix<double, 0, 1> m;    
        return m;
    }
    Matrix<double, 3, 1> PHSCORE::dxnl() const {    
        Matrix<double, 3, 1> m;    
        m(0, 0) = *dxM;    
        m(1, 0) = *dxL;    
        m(2, 0) = *dxK;    
        return m;
    }
    Matrix<double, 2, 1> PHSCORE::w() const {    
        Matrix<double, 2, 1> m;    
        m(0, 0) = *wR;    
        m(1, 0) = *wA;    
        return m;
    }
    Matrix<double, 2, 1> PHSCORE::wl() const {    
        Matrix<double, 2, 1> m;    
        m(0, 0) = *wR;    
        m(1, 0) = *wA;    
        return m;
    }
    Matrix<double, 0, 1> PHSCORE::wnl() const {    
        Matrix<double, 0, 1> m;    
        return m;
    }
    Matrix<double, 1, 1> PHSCORE::u() const {    
        Matrix<double, 1, 1> m;    
        m(0, 0) = *uIN;    
        return m;
    }
    Matrix<double, 0, 1> PHSCORE::p() const {    
        Matrix<double, 0, 1> m;    
        return m;
    }
    Matrix<double, 5, 1> PHSCORE::v() const {    
        Matrix<double, 5, 1> m;    
        m(0, 0) = *dxM;    
        m(1, 0) = *dxL;    
        m(2, 0) = *dxK;    
        m(3, 0) = *wR;    
        m(4, 0) = *wA;    
        return m;
    }
    Matrix<double, 2, 1> PHSCORE::vl() const {    
        Matrix<double, 2, 1> m;    
        m(0, 0) = *wR;    
        m(1, 0) = *wA;    
        return m;
    }
    Matrix<double, 3, 1> PHSCORE::vnl() const {    
        Matrix<double, 3, 1> m;    
        m(0, 0) = *dxM;    
        m(1, 0) = *dxL;    
        m(2, 0) = *dxK;    
        return m;
    }
    
    // Mutators for Arguments, type = vector<double>
    
    void PHSCORE::set_x(vector<double> & v) {
        *xM = v[0];
        *xL = v[1];
        *xK = v[2];
    }
    void PHSCORE::set_xl(vector<double> & v) {
    }
    void PHSCORE::set_xnl(vector<double> & v) {
        *xM = v[0];
        *xL = v[1];
        *xK = v[2];
    }
    void PHSCORE::set_dx(vector<double> & v) {
        *dxM = v[0];
        *dxL = v[1];
        *dxK = v[2];
    }
    void PHSCORE::set_dxl(vector<double> & v) {
    }
    void PHSCORE::set_dxnl(vector<double> & v) {
        *dxM = v[0];
        *dxL = v[1];
        *dxK = v[2];
    }
    void PHSCORE::set_w(vector<double> & v) {
        *wR = v[0];
        *wA = v[1];
    }
    void PHSCORE::set_wl(vector<double> & v) {
        *wR = v[0];
        *wA = v[1];
    }
    void PHSCORE::set_wnl(vector<double> & v) {
    }
    void PHSCORE::set_u(vector<double> & v) {
        *uIN = v[0];
    }
    void PHSCORE::set_p(vector<double> & v) {
    }
    void PHSCORE::set_v(vector<double> & v) {
        *dxM = v[0];
        *dxL = v[1];
        *dxK = v[2];
        *wR = v[3];
        *wA = v[4];
    }
    void PHSCORE::set_vl(vector<double> & v) {
        *wR = v[0];
        *wA = v[1];
    }
    void PHSCORE::set_vnl(vector<double> & v) {
        *dxM = v[0];
        *dxL = v[1];
        *dxK = v[2];
    }
    
    // Mutators for Arguments, type = Matrix<double, n, m>
    
    void PHSCORE::set_x(Matrix<double, 3, 1> & m) {
        *xM = m(0, 0);
        *xL = m(1, 0);
        *xK = m(2, 0);
    }
    void PHSCORE::set_xl(Matrix<double, 0, 1> & m) {
    }
    void PHSCORE::set_xnl(Matrix<double, 3, 1> & m) {
        *xM = m(0, 0);
        *xL = m(1, 0);
        *xK = m(2, 0);
    }
    void PHSCORE::set_dx(Matrix<double, 3, 1> & m) {
        *dxM = m(0, 0);
        *dxL = m(1, 0);
        *dxK = m(2, 0);
    }
    void PHSCORE::set_dxl(Matrix<double, 0, 1> & m) {
    }
    void PHSCORE::set_dxnl(Matrix<double, 3, 1> & m) {
        *dxM = m(0, 0);
        *dxL = m(1, 0);
        *dxK = m(2, 0);
    }
    void PHSCORE::set_w(Matrix<double, 2, 1> & m) {
        *wR = m(0, 0);
        *wA = m(1, 0);
    }
    void PHSCORE::set_wl(Matrix<double, 2, 1> & m) {
        *wR = m(0, 0);
        *wA = m(1, 0);
    }
    void PHSCORE::set_wnl(Matrix<double, 0, 1> & m) {
    }
    void PHSCORE::set_u(Matrix<double, 1, 1> & m) {
        *uIN = m(0, 0);
    }
    void PHSCORE::set_p(Matrix<double, 0, 1> & m) {
    }
    void PHSCORE::set_v(Matrix<double, 5, 1> & m) {
        *dxM = m(0, 0);
        *dxL = m(1, 0);
        *dxK = m(2, 0);
        *wR = m(3, 0);
        *wA = m(4, 0);
    }
    void PHSCORE::set_vl(Matrix<double, 2, 1> & m) {
        *wR = m(0, 0);
        *wA = m(1, 0);
    }
    void PHSCORE::set_vnl(Matrix<double, 3, 1> & m) {
        *dxM = m(0, 0);
        *dxL = m(1, 0);
        *dxK = m(2, 0);
    }
    
    // Functions Results Accessors
    
    Matrix<double, 3, 1> PHSCORE::Mvnly() const {
        return _Mvnly;
    }
    Matrix<double, 2, 3> PHSCORE::jacGlnl() const {
        return _jacGlnl;
    }
    Matrix<double, 3, 1> PHSCORE::fnl() const {
        return _fnl;
    }
    Matrix<double, 2, 3> PHSCORE::jacFlnl() const {
        return _jacFlnl;
    }
    Matrix<double, 5, 1> PHSCORE::Mvy() const {
        return _Mvy;
    }
    Matrix<double, 3, 3> PHSCORE::Mvnlvnl() const {
        return _Mvnlvnl;
    }
    Matrix<double, 2, 1> PHSCORE::Mvly() const {
        return _Mvly;
    }
    Matrix<double, 2, 2> PHSCORE::jacFll() const {
        return _jacFll;
    }
    Matrix<double, 5, 5> PHSCORE::Mvv() const {
        return _Mvv;
    }
    Matrix<double, 2, 3> PHSCORE::Mvlvnl() const {
        return _Mvlvnl;
    }
    Matrix<double, 2, 2> PHSCORE::Mvlvl() const {
        return _Mvlvl;
    }
    Matrix<double, 3, 2> PHSCORE::jacGnll() const {
        return _jacGnll;
    }
    Matrix<double, 3, 1> PHSCORE::dxH() const {
        return _dxH;
    }
    Matrix<double, 2, 2> PHSCORE::jacGll() const {
        return _jacGll;
    }
    Matrix<double, 2, 1> PHSCORE::Fl() const {
        return _Fl;
    }
    Matrix<double, 3, 2> PHSCORE::Mvnlvl() const {
        return _Mvnlvl;
    }
    Matrix<double, 5, 1> PHSCORE::G() const {
        return _G;
    }
    Matrix<double, 5, 1> PHSCORE::F() const {
        return _F;
    }
    double PHSCORE::H() const {
        return _H;
    }
    Matrix<double, 3, 3> PHSCORE::jacGnlnl() const {
        return _jacGnlnl;
    }
    Matrix<double, 3, 2> PHSCORE::jacFnll() const {
        return _jacFnll;
    }
    Matrix<double, 0, 0> PHSCORE::Q() const {
        return _Q;
    }
    Matrix<double, 3, 1> PHSCORE::Fnl() const {
        return _Fnl;
    }
    Matrix<double, 2, 1> PHSCORE::fl() const {
        return _fl;
    }
    Matrix<double, 3, 1> PHSCORE::Gnl() const {
        return _Gnl;
    }
    Matrix<double, 2, 2> PHSCORE::Zl() const {
        return _Zl;
    }
    Matrix<double, 2, 1> PHSCORE::z() const {
        return _z;
    }
    Matrix<double, 0, 0> PHSCORE::g() const {
        return _g;
    }
    Matrix<double, 5, 1> PHSCORE::f() const {
        return _f;
    }
    Matrix<double, 5, 5> PHSCORE::jacF() const {
        return _jacF;
    }
    Matrix<double, 2, 1> PHSCORE::Gl() const {
        return _Gl;
    }
    Matrix<double, 3, 3> PHSCORE::jacFnlnl() const {
        return _jacFnlnl;
    }
    Matrix<double, 1, 1> PHSCORE::y() const {
        return _y;
    }
    double PHSCORE::fs() const {
        return _fs;
    }
    
    // Functions Results Accessors
    
    vector<double> PHSCORE::fnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _fnl(0, 0);    
        v[1] = _fnl(1, 0);    
        v[2] = _fnl(2, 0);    
        return v;
    }
    vector<double> PHSCORE::dxH_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _dxH(0, 0);    
        v[1] = _dxH(1, 0);    
        v[2] = _dxH(2, 0);    
        return v;
    }
    vector<double> PHSCORE::Fl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = _Fl(0, 0);    
        v[1] = _Fl(1, 0);    
        return v;
    }
    vector<double> PHSCORE::G_vector() const {    
        vector<double> v = vector<double>(5);    
        v[0] = _G(0, 0);    
        v[1] = _G(1, 0);    
        v[2] = _G(2, 0);    
        v[3] = _G(3, 0);    
        v[4] = _G(4, 0);    
        return v;
    }
    vector<double> PHSCORE::F_vector() const {    
        vector<double> v = vector<double>(5);    
        v[0] = _F(0, 0);    
        v[1] = _F(1, 0);    
        v[2] = _F(2, 0);    
        v[3] = _F(3, 0);    
        v[4] = _F(4, 0);    
        return v;
    }
    vector<double> PHSCORE::Q_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    vector<double> PHSCORE::Fnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _Fnl(0, 0);    
        v[1] = _Fnl(1, 0);    
        v[2] = _Fnl(2, 0);    
        return v;
    }
    vector<double> PHSCORE::fl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = _fl(0, 0);    
        v[1] = _fl(1, 0);    
        return v;
    }
    vector<double> PHSCORE::Gnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _Gnl(0, 0);    
        v[1] = _Gnl(1, 0);    
        v[2] = _Gnl(2, 0);    
        return v;
    }
    vector<double> PHSCORE::z_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = _z(0, 0);    
        v[1] = _z(1, 0);    
        return v;
    }
    vector<double> PHSCORE::g_vector() const {    
        vector<double> v = vector<double>(0);    
        return v;
    }
    vector<double> PHSCORE::f_vector() const {    
        vector<double> v = vector<double>(5);    
        v[0] = _f(0, 0);    
        v[1] = _f(1, 0);    
        v[2] = _f(2, 0);    
        v[3] = _f(3, 0);    
        v[4] = _f(4, 0);    
        return v;
    }
    vector<double> PHSCORE::Gl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = _Gl(0, 0);    
        v[1] = _Gl(1, 0);    
        return v;
    }
    vector<double> PHSCORE::y_vector() const {    
        vector<double> v = vector<double>(1);    
        v[0] = _y(0, 0);    
        return v;
    }
    
    // Oprations Results Accessors
    
    Matrix<double, 3, 1> PHSCORE::ud_x() const {
        return _ud_x;
    }
    Matrix<double, 2, 2> PHSCORE::ijacFll() const {
        return _ijacFll;
    }
    Matrix<double, 2, 1> PHSCORE::ud_vl() const {
        return _ud_vl;
    }
    Matrix<double, 3, 1> PHSCORE::save_Fnl() const {
        return _save_Fnl;
    }
    Matrix<double, 3, 1> PHSCORE::ud_Fnl() const {
        return _ud_Fnl;
    }
    Matrix<double, 3, 3> PHSCORE::jacFnl() const {
        return _jacFnl;
    }
    Matrix<double, 3, 3> PHSCORE::ijacFnl() const {
        return _ijacFnl;
    }
    double PHSCORE::res_Fnl() const {
        return _res_Fnl;
    }
    double PHSCORE::step_Fnl() const {
        return _step_Fnl;
    }
    Matrix<double, 3, 1> PHSCORE::ud_vnl() const {
        return _ud_vnl;
    }
    
    // Oprations Results Accessors
    
    vector<double> PHSCORE::ud_x_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _ud_x(0, 0);    
        v[1] = _ud_x(1, 0);    
        v[2] = _ud_x(2, 0);    
        return v;
    }
    vector<double> PHSCORE::ud_vl_vector() const {    
        vector<double> v = vector<double>(2);    
        v[0] = _ud_vl(0, 0);    
        v[1] = _ud_vl(1, 0);    
        return v;
    }
    vector<double> PHSCORE::save_Fnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _save_Fnl(0, 0);    
        v[1] = _save_Fnl(1, 0);    
        v[2] = _save_Fnl(2, 0);    
        return v;
    }
    vector<double> PHSCORE::ud_Fnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _ud_Fnl(0, 0);    
        v[1] = _ud_Fnl(1, 0);    
        v[2] = _ud_Fnl(2, 0);    
        return v;
    }
    vector<double> PHSCORE::ud_vnl_vector() const {    
        vector<double> v = vector<double>(3);    
        v[0] = _ud_vnl(0, 0);    
        v[1] = _ud_vnl(1, 0);    
        v[2] = _ud_vnl(2, 0);    
        return v;
    }
    
    // Default Constructor
    
    PHSCORE::PHSCORE(){
        init();
    };
    
    // Constructor with vector state initalization
    
    PHSCORE::PHSCORE(vector<double> & x0){
    
        if (x().size() == x0.size()) {
            set_x(x0);
        }
        else {
            cerr << "Size of x0 does not match size of x" << endl;
            exit(1);
        }
        init();
    };
    
    // Constructor with matrix state initalization
    
    PHSCORE::PHSCORE(Matrix<double, 3, 1> & x0){
    set_x(x0);
        init();
    };
    
    // Default Destructor
    
    PHSCORE::~PHSCORE(){
    };


// PRIVATE    
    
    // Functions Results Updates
    
    void PHSCORE::Mvnly_update(){
    };
    void PHSCORE::jacGlnl_update(){
    _jacGlnl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacGlnl(0, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*L)
    )));
    };
    void PHSCORE::fnl_update(){
    _fnl(0, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       5.0*(*dxM) + 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       10.0*(*xM)
    )
    : (
       5.0*(*dxM) + 10.0*(*xM)
    )));
    _fnl(1, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _fnl(2, 0) = (((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )));
    };
    void PHSCORE::jacFlnl_update(){
    _jacFlnl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacFlnl(0, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*L)
    )));
    };
    void PHSCORE::Mvy_update(){
    };
    void PHSCORE::Mvnlvnl_update(){
    };
    void PHSCORE::Mvly_update(){
    };
    void PHSCORE::jacFll_update(){
    };
    void PHSCORE::Mvv_update(){
    };
    void PHSCORE::Mvlvnl_update(){
    };
    void PHSCORE::Mvlvl_update(){
    };
    void PHSCORE::jacGnll_update(){
    };
    void PHSCORE::dxH_update(){
    _dxH(0, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       5.0*(*dxM) + 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       10.0*(*xM)
    )
    : (
       5.0*(*dxM) + 10.0*(*xM)
    )));
    _dxH(1, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _dxH(2, 0) = (((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )));
    };
    void PHSCORE::jacGll_update(){
    };
    void PHSCORE::Fl_update(){
    _Fl(0, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       -10.0*(*dxL) + (*wR) - 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       (*wR) - 20.0*(*xL)
    )
    : (
       -10.0*(*dxL) + (*wR) - 20.0*(*xL)
    )));
    _Fl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -5.0*(*dxM) + (*wA) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       (*wA) - 10.0*(*xM)
    )
    : (
       -5.0*(*dxM) + (*wA) - 10.0*(*xM)
    )));
    };
    void PHSCORE::Mvnlvl_update(){
    };
    void PHSCORE::G_update(){
    _G(0, 0) = 48000.0*(*dxM) + 1.0*(((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    ))) - 50.0*(((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _G(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxL) + 250.0*(*dxM) - 1.0*(*uIN) + 500.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxL) - 1.0*(*uIN) + 500.0*(*xM)
    )
    : (
       48000.0*(*dxL) + 250.0*(*dxM) - 1.0*(*uIN) + 500.0*(*xM)
    )));
    _G(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxK) - 10.0*(*xM)
    )
    : (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )));
    _G(3, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       -10.0*(*dxL) - 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       -20.0*(*xL)
    )
    : (
       -10.0*(*dxL) - 20.0*(*xL)
    )));
    _G(4, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       -10.0*(*xM)
    )
    : (
       -5.0*(*dxM) - 10.0*(*xM)
    )));
    };
    void PHSCORE::F_update(){
    _F(0, 0) = 48000.0*(*dxM) + 0.1*(*wA) + 1.0*(((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    ))) - 50.0*(((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _F(1, 0) = 48000.0*(*dxL) - 1.0*(*uIN) + 1000.0*(*wR) + 50.0*(((*dxM) < -2.22044604925031e-16) ? (
       5.0*(*dxM) + 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       10.0*(*xM)
    )
    : (
       5.0*(*dxM) + 10.0*(*xM)
    )));
    _F(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxK) - 10.0*(*xM)
    )
    : (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )));
    _F(3, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       -10.0*(*dxL) + (*wR) - 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       (*wR) - 20.0*(*xL)
    )
    : (
       -10.0*(*dxL) + (*wR) - 20.0*(*xL)
    )));
    _F(4, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -5.0*(*dxM) + (*wA) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       (*wA) - 10.0*(*xM)
    )
    : (
       -5.0*(*dxM) + (*wA) - 10.0*(*xM)
    )));
    };
    void PHSCORE::H_update(){
    _H = 0.5*(*K)*pow((*xK), 2) + 0.5*pow((*xM), 2)/(*M) + 0.5*pow((*xL), 2)/(*L);
    };
    void PHSCORE::jacGnlnl_update(){
    _jacGnlnl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       0.5*(*Bl)/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*Bl)/(*M)
    )));
    _jacGnlnl(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacGnlnl(0, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5*(*Bl)/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5*(*Bl)/(*L)
    )));
    _jacGnlnl(0, 2) = (((*dxK) < -2.22044604925031e-16) ? (
       0.5*(*K)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*K)
    )));
    };
    void PHSCORE::jacFnll_update(){
    };
    void PHSCORE::Q_update(){
    };
    void PHSCORE::Fnl_update(){
    _Fnl(0, 0) = 48000.0*(*dxM) + 0.1*(*wA) + 1.0*(((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    ))) - 50.0*(((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _Fnl(1, 0) = 48000.0*(*dxL) - 1.0*(*uIN) + 1000.0*(*wR) + 50.0*(((*dxM) < -2.22044604925031e-16) ? (
       5.0*(*dxM) + 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       10.0*(*xM)
    )
    : (
       5.0*(*dxM) + 10.0*(*xM)
    )));
    _Fnl(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxK) - 10.0*(*xM)
    )
    : (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )));
    };
    void PHSCORE::fl_update(){
    _fl(0, 0) = 1000.0*(*wR);
    _fl(1, 0) = (1.0L/10.0L)*(*wA);
    };
    void PHSCORE::Gnl_update(){
    _Gnl(0, 0) = 48000.0*(*dxM) + 1.0*(((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    ))) - 50.0*(((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _Gnl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxL) + 250.0*(*dxM) - 1.0*(*uIN) + 500.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxL) - 1.0*(*uIN) + 500.0*(*xM)
    )
    : (
       48000.0*(*dxL) + 250.0*(*dxM) - 1.0*(*uIN) + 500.0*(*xM)
    )));
    _Gnl(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       48000.0*(*dxK) - 10.0*(*xM)
    )
    : (
       48000.0*(*dxK) - 5.0*(*dxM) - 10.0*(*xM)
    )));
    };
    void PHSCORE::Zl_update(){
    };
    void PHSCORE::z_update(){
    _z(0, 0) = 1000.0*(*wR);
    _z(1, 0) = (1.0L/10.0L)*(*wA);
    };
    void PHSCORE::g_update(){
    };
    void PHSCORE::f_update(){
    _f(0, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       5.0*(*dxM) + 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       10.0*(*xM)
    )
    : (
       5.0*(*dxM) + 10.0*(*xM)
    )));
    _f(1, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       10.0*(*dxL) + 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       20.0*(*xL)
    )
    : (
       10.0*(*dxL) + 20.0*(*xL)
    )));
    _f(2, 0) = (((*dxK) < -2.22044604925031e-16) ? (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       1000000.0*(*xK)
    )
    : (
       500000.0*(*dxK) + 1000000.0*(*xK)
    )));
    _f(3, 0) = 1000.0*(*wR);
    _f(4, 0) = (1.0L/10.0L)*(*wA);
    };
    void PHSCORE::jacF_update(){
    _jacF(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       0.5*(*Bl)/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*Bl)/(*M)
    )));
    _jacF(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacF(4, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacF(0, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5*(*Bl)/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5*(*Bl)/(*L)
    )));
    _jacF(3, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*L)
    )));
    _jacF(0, 2) = (((*dxK) < -2.22044604925031e-16) ? (
       0.5*(*K)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*K)
    )));
    };
    void PHSCORE::Gl_update(){
    _Gl(0, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       -10.0*(*dxL) - 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       -20.0*(*xL)
    )
    : (
       -10.0*(*dxL) - 20.0*(*xL)
    )));
    _Gl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -5.0*(*dxM) - 10.0*(*xM)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       -10.0*(*xM)
    )
    : (
       -5.0*(*dxM) - 10.0*(*xM)
    )));
    };
    void PHSCORE::jacFnlnl_update(){
    _jacFnlnl(1, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       0.5*(*Bl)/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*Bl)/(*M)
    )));
    _jacFnlnl(2, 0) = (((*dxM) < -2.22044604925031e-16) ? (
       -0.5/(*M)
    )
    : (((*dxM) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5/(*M)
    )));
    _jacFnlnl(0, 1) = (((*dxL) < -2.22044604925031e-16) ? (
       -0.5*(*Bl)/(*L)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       0
    )
    : (
       -0.5*(*Bl)/(*L)
    )));
    _jacFnlnl(0, 2) = (((*dxK) < -2.22044604925031e-16) ? (
       0.5*(*K)
    )
    : (((*dxK) < 2.22044604925031e-16) ? (
       0
    )
    : (
       0.5*(*K)
    )));
    };
    void PHSCORE::y_update(){
    _y(0, 0) = (((*dxL) < -2.22044604925031e-16) ? (
       -10.0*(*dxL) - 20.0*(*xL)
    )
    : (((*dxL) < 2.22044604925031e-16) ? (
       -20.0*(*xL)
    )
    : (
       -10.0*(*dxL) - 20.0*(*xL)
    )));
    };
    void PHSCORE::fs_update(){
    };
    
    // Oprations Results Updates
    
    void PHSCORE::ud_x_update(){
        _ud_x = (x()) + (dx());
    };
    void PHSCORE::ijacFll_update(){
        _ijacFll = (jacFll()).inverse();
    };
    void PHSCORE::ud_vl_update(){
        _ud_vl = (ijacFll())*((-1.0)*(Gl()));
    };
    void PHSCORE::save_Fnl_update(){
        _save_Fnl = Fnl();
    };
    void PHSCORE::ud_Fnl_update(){
        _ud_Fnl = (Gnl()) + ((jacFnll())*((ijacFll())*((-1)*(Gl()))));
    };
    void PHSCORE::jacFnl_update(){
        _jacFnl = (jacGnlnl()) + ((jacFnll())*((ijacFll())*((-1)*(jacGlnl()))));
    };
    void PHSCORE::ijacFnl_update(){
        _ijacFnl = (jacFnl()).inverse();
    };
    void PHSCORE::res_Fnl_update(){
        _res_Fnl = sqrt((Fnl()).dot(Fnl()));
    };
    void PHSCORE::step_Fnl_update(){
        _step_Fnl = sqrt(((Fnl()) + ((-1.0)*(save_Fnl()))).dot((Fnl()) + ((-1.0)*(save_Fnl()))));
    };
    void PHSCORE::ud_vnl_update(){
        _ud_vnl = (vnl()) + ((-1.0)*((ijacFnl())*(Fnl())));
    };
    
    // Initialization
    
    void PHSCORE::init(){
        
        
        // Functions Results Initialisation Data
        double Mvnly_data[] = {0, 1.00000000000000, 0};
        double jacGlnl_data[] = {0, 0, 0, 0, 0, 0};
        double fnl_data[] = {0, 0, 0};
        double jacFlnl_data[] = {0, 0, 0, 0, 0, 0};
        double Mvy_data[] = {0, 1.00000000000000, 0, 0, 0};
        double Mvnlvnl_data[] = {0, -1.0*(*Bl), 1.00000000000000, 1.0*(*Bl), 0, 0, -1.00000000000000, 0, 0};
        double Mvly_data[] = {0, 0};
        double jacFll_data[] = {1, 0, 0, 1};
        double Mvv_data[] = {0, -1.0*(*Bl), 1.00000000000000, 0, 1.00000000000000, 1.0*(*Bl), 0, 0, 1.00000000000000, 0, -1.00000000000000, 0, 0, 0, 0, 0, -1.00000000000000, 0, 0, 0, -1.00000000000000, 0, 0, 0, 0};
        double Mvlvnl_data[] = {0, 1.00000000000000, 1.00000000000000, 0, 0, 0};
        double Mvlvl_data[] = {0, 0, 0, 0};
        double jacGnll_data[] = {0, 0, 0, 0, 0, 0};
        double dxH_data[] = {0, 0, 0};
        double jacGll_data[] = {0, 0, 0, 0};
        double Fl_data[] = {0, 0};
        double Mvnlvl_data[] = {0, -1.00000000000000, 0, -1.00000000000000, 0, 0};
        double G_data[] = {0, 0, 0, 0, 0};
        double F_data[] = {0, 0, 0, 0, 0};
        double H_data = 0.;
        double jacGnlnl_data[] = {48000.0000000000, 0, 0, 0, 48000.0000000000, 0, 0, 0, 48000.0000000000};
        double jacFnll_data[] = {0, 1.0*(*R), 0, 1.0/(*A), 0, 0};
        double Q_data[] = {};
        double Fnl_data[] = {0, 0, 0};
        double fl_data[] = {0, 0};
        double Gnl_data[] = {0, 0, 0};
        double Zl_data[] = {(*R), 0, 0, 1.0/(*A)};
        double z_data[] = {0, 0};
        double g_data[] = {};
        double f_data[] = {0, 0, 0, 0, 0};
        double jacF_data[] = {48000.0000000000, 0, 0, 0, 0, 0, 48000.0000000000, 0, 0, 0, 0, 0, 48000.0000000000, 0, 0, 0, 1.0*(*R), 0, 1, 0, 1.0/(*A), 0, 0, 0, 1};
        double Gl_data[] = {0, 0};
        double jacFnlnl_data[] = {48000.0000000000, 0, 0, 0, 48000.0000000000, 0, 0, 0, 48000.0000000000};
        double y_data[] = {0};
        double fs_data = (*_fs);
        
        // Oprations Results Initialisation Data
        double ud_x_data[] = {0.0, 0.0, 0.0};
        double ijacFll_data[] = {1.0, 0.0, 0.0, 1.0};
        double ud_vl_data[] = {0.0, 0.0};
        double save_Fnl_data[] = {-0.00460216033026, -0.012031037854, 6.66619876851e-06};
        double ud_Fnl_data[] = {0.0, 0.0, 0.0};
        double jacFnl_data[] = {48000.5, 250.0, -5.0, -500.0, 58000.0, 0.0, 500000.0, 0.0, 48000.0};
        double ijacFnl_data[] = {2.08096023638e-05, -8.96965619128e-08, 2.16766691289e-09, 1.79393123826e-07, 1.72406060641e-05, 1.86867837318e-11, -0.000216766691289, 9.34339186592e-07, 2.08107534697e-05};
        double res_Fnl_data = 0.;
        double step_Fnl_data = 0.;
        double ud_vnl_data[] = {0.0, 0.0, 0.0};    
        
        // Functions Results Initialisation
        
        _Mvnly = Map<Matrix<double, 3, 1>> (Mvnly_data);
        _jacGlnl = Map<Matrix<double, 2, 3>> (jacGlnl_data);
        _fnl = Map<Matrix<double, 3, 1>> (fnl_data);
        _jacFlnl = Map<Matrix<double, 2, 3>> (jacFlnl_data);
        _Mvy = Map<Matrix<double, 5, 1>> (Mvy_data);
        _Mvnlvnl = Map<Matrix<double, 3, 3>> (Mvnlvnl_data);
        _Mvly = Map<Matrix<double, 2, 1>> (Mvly_data);
        _jacFll = Map<Matrix<double, 2, 2>> (jacFll_data);
        _Mvv = Map<Matrix<double, 5, 5>> (Mvv_data);
        _Mvlvnl = Map<Matrix<double, 2, 3>> (Mvlvnl_data);
        _Mvlvl = Map<Matrix<double, 2, 2>> (Mvlvl_data);
        _jacGnll = Map<Matrix<double, 3, 2>> (jacGnll_data);
        _dxH = Map<Matrix<double, 3, 1>> (dxH_data);
        _jacGll = Map<Matrix<double, 2, 2>> (jacGll_data);
        _Fl = Map<Matrix<double, 2, 1>> (Fl_data);
        _Mvnlvl = Map<Matrix<double, 3, 2>> (Mvnlvl_data);
        _G = Map<Matrix<double, 5, 1>> (G_data);
        _F = Map<Matrix<double, 5, 1>> (F_data);
        _H = H_data;
        _jacGnlnl = Map<Matrix<double, 3, 3>> (jacGnlnl_data);
        _jacFnll = Map<Matrix<double, 3, 2>> (jacFnll_data);
        _Q = Map<Matrix<double, 0, 0>> (Q_data);
        _Fnl = Map<Matrix<double, 3, 1>> (Fnl_data);
        _fl = Map<Matrix<double, 2, 1>> (fl_data);
        _Gnl = Map<Matrix<double, 3, 1>> (Gnl_data);
        _Zl = Map<Matrix<double, 2, 2>> (Zl_data);
        _z = Map<Matrix<double, 2, 1>> (z_data);
        _g = Map<Matrix<double, 0, 0>> (g_data);
        _f = Map<Matrix<double, 5, 1>> (f_data);
        _jacF = Map<Matrix<double, 5, 5>> (jacF_data);
        _Gl = Map<Matrix<double, 2, 1>> (Gl_data);
        _jacFnlnl = Map<Matrix<double, 3, 3>> (jacFnlnl_data);
        _y = Map<Matrix<double, 1, 1>> (y_data);
        _fs = fs_data;
        
        // Operations Results Initialisation
        
        _ud_x = Map<Matrix<double, 3, 1>> (ud_x_data);
        _ijacFll = Map<Matrix<double, 2, 2>> (ijacFll_data);
        _ud_vl = Map<Matrix<double, 2, 1>> (ud_vl_data);
        _save_Fnl = Map<Matrix<double, 3, 1>> (save_Fnl_data);
        _ud_Fnl = Map<Matrix<double, 3, 1>> (ud_Fnl_data);
        _jacFnl = Map<Matrix<double, 3, 3>> (jacFnl_data);
        _ijacFnl = Map<Matrix<double, 3, 3>> (ijacFnl_data);
        _res_Fnl = res_Fnl_data;
        _step_Fnl = step_Fnl_data;
        _ud_vnl = Map<Matrix<double, 3, 1>> (ud_vnl_data);
    };