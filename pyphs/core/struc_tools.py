# -*- coding: utf-8 -*-
"""
Created on Thu Jun  9 11:46:11 2016

@author: Falaize
"""
from __future__ import absolute_import, division, print_function
import sympy
from .calculus import hessian, jacobian
from .symbs_tools import simplify
from .misc_tools import myrange, geteval


def moveJcolnrow(core, indi, indf):
    new_indices = myrange(core.dims.tot(), indi, indf)
    core.M = core.M[new_indices, new_indices]


def move_stor(core, indi, indf):
    new_indices = myrange(core.dims.x(), indi, indf)
    core.x = [core.x[el] for el in new_indices]
    moveJcolnrow(core, indi, indf)


def move_diss(core, indi, indf):
    new_indices = myrange(core.dims.w(), indi, indf)
    core.w = [core.w[el] for el in new_indices]
    core.z = [core.z[el] for el in new_indices]
    moveJcolnrow(core, core.dims.x()+indi, core.dims.x()+indf)


def move_port(core, indi, indf):
    new_indices = myrange(core.dims.y(), indi, indf)
    core.u = [core.u[el] for el in new_indices]
    core.y = [core.y[el] for el in new_indices]
    moveJcolnrow(core, core.dims.x()+core.dims.w()+indi,
                 core.dims.x()+core.dims.w()+indf)


def split_monovariate(core):
    """
    """

    from utils.structure import move_stor, move_diss
    # split storage part
    i = 0
    for _ in range(core.dims.x()):
        hess = hessian(core.H, core.x)
        hess_line = list(hess[i, :].T)
        # remove i-th element
        hess_line.pop(i)
        # if other elements are all 0
        if all(el is sympy.sympify(0) for el in hess_line):
            # do nothing and increment counter
            i += 1
        else:
            # move the element at the end of states vector
            move_stor(core, i, core.dims.x())
    # number of separate components
    core.dims.xs = i
    # number of non-separate components
    core.dims.xns = core.dims.x()-i
    # split dissipative part
    i = 0
    for _ in range(core.dims.w()):
        Jacz_line = list(core.Jacz[i, :].T)
        # remove i-th element
        Jacz_line.pop(i)
        # if other elements are all 0
        if all(el is sympy.sympify(0) for el in Jacz_line):
            # do nothing and increment counter
            i += 1
        else:
            # move the element at the end of variables vector
            move_diss(core, i, core.dims.w())
    # number of separate components
    core.dims.ws = i
    # number of non-separate components
    core.dims.wns = core.dims.w()-i


def split_linear(core, force_nolin=False):
    """
    """
    # split storage part
    nxl = 0
    if not force_nolin:
        for _ in range(core.dims.x()):
            hess = hessian(core.H, core.x)
            hess_line = list(hess[nxl, :].T)
            # init line symbols
            line_symbols = set()
            # collect line symbols
            for el in hess_line:
                line_symbols = line_symbols.union(el.free_symbols)
            # if symbols are not states
            if not any(el in line_symbols for el in core.x):
                # do nothing and increment counter
                nxl += 1
            else:
                # move the element at the end of states vector
                print(str(nxl)+" "+str(core.dims.x()-1))
                move_stor(core, nxl, core.dims.x()-1)

    hess = hessian(core.H, core.x)
    core._setexpr('Q', hess[:nxl, :nxl])
    # number of linear components
    setattr(core.dims, '_xl', nxl)

    # split dissipative part
    nwl = 0
    if not force_nolin:
        for _ in range(core.dims.w()):
            jacz = jacobian(core.z, core.w)
            jacz_line = list(jacz[nwl, :].T)
            # init line symbols
            line_symbols = set()
            # collect line symbols
            for el in jacz_line:
                line_symbols = line_symbols.union(el.free_symbols)
            # if symbols are not dissipation variables
            if not any(el in line_symbols for el in core.w):
                # do nothing and increment counter
                nwl += 1
            else:
                # move the element to end of dissipation variables vector
                move_diss(core, nwl, core.dims.w()-1)
    jacz = jacobian(core.z, core.w)
    core._setexpr('Zl', jacz[:nwl, :nwl])

    # number of linear components
    setattr(core.dims, '_wl', nwl)
    core.exprs_build()

    names = ('xl', 'xnl', 'wl', 'wnl', 'y')
    core.inds._set_inds(names, core)

    # get() and set() for structure matrices
    core._struc_getset(dims_names=names)


def reduce_linear_dissipations(core):
    if not hasattr(core, 'nwl'):
        split_linear(core)
    iDwl = sympy.eye(core.dims.wl)-core.struc.Mwlwl()*core.Zl
    Dwl = iDwl.inv()
    Mwlnl = sympy.Matrix.hstack(core.Mwlxl(),
                                core.Mwlxnl(),
                                core.Mwlwnl(),
                                core.Mwly())
    Mnlwl = sympy.Matrix.vstack(core.Mxlwl(),
                                core.Mxnlwl(),
                                core.Mwnlwl(),
                                core.Mywl())

    names = ('xl', 'xnl', 'wnl', 'y')
    mat = []
    for namei in names:
        mati = []
        for namej in names:
            mati.append(geteval(core, 'M'+namei+namej))
        mat.append(sympy.Matrix.hstack(*mati))
    Mnl = sympy.Matrix.vstack(*mat)

    core.w = core.w[core.dims.wl:]
    core.z = core.z[core.dims.wl:]
    core.dims.wl = 0
    core.M = Mnlwl*core.Zl*Dwl*Mwlnl + Mnl
    core.build()


def output_function(core):
    """
    Returns the expression of the continuous output vector function y, and the\
expression of the discrete output vector function yd.

    Input:

        - core: pyphs.PortHamiltonianObject

    Output:

        - y: list of sympy expressions associated with output vector \
components, considering the continuous version of storage function gradient
        - y: list of sympy expressions associated with output vector \
components, considering the discrete version of storage function gradient
    """

    if core.dims.y() > 0:  # Check if system has external ports

        # contribution of inputs to the output
        Vyu = core.Myy()*sympy.Matrix(core.u)

        if core.dims.x() > 0:  # Check if system has storage parts
            Vyx = core.Myx()*sympy.Matrix(core.dxH)
            Vyxd = core.Myx()*sympy.Matrix(core.dxHd)
        else:
            Vyx = Vyxd = sympy.zeros(core.dims.y(), 1)

        if core.dims.w() > 0:  # Check if system has dissipative parts
            Vyw = core.Myw()*sympy.Matrix(core.z)
        else:
            Vyw = sympy.zeros(core.dims.y(), 1)

        out = list(Vyx + Vyw + Vyu)
        out = simplify(out)

        outd = list(Vyxd + Vyw + Vyu)
        outd = simplify(outd)

    else:
        out = sympy.Matrix(list(list()))
        outd = sympy.Matrix(list(list()))

    return list(out), list(outd)
