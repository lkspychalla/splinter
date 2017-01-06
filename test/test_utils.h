/*
 * This file is part of the SPLINTER library.
 * Copyright (C) 2012 Bjarne Grimstad (bjarne.grimstad@gmail.com).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef SPLINTER_TESTINGUTILITIES_H
#define SPLINTER_TESTINGUTILITIES_H

#include <data_table.h>
#include <function.h>
#include "definitions.h"
#include <bspline.h>
#include <op_overloads.h>
#include <test_function.h>


namespace SPLINTER
{

enum class TestType {
    All,
    FunctionValue,
    Jacobian,
    Hessian
};

double getError(double exactVal, double approxVal);

bool equalsWithinRange(double a, double b, double margin = 0.0);

bool compareFunctions(const Function &exact, const Function &approx, const std::vector<std::vector<double>> &points);

bool compareFunctions(const Function &exact, const Function &approx, const std::vector<std::vector<double>> &points, double one_norm_epsilon, double two_norm_epsilon, double inf_norm_epsilon);

bool compareFunctions(const Function &exact, const Function &approx);

/*
 * Compares the function value of the Approximant generated by calling
 * approx_gen_func with all the exact functions in funcs.
 * Prints out the 1, 2 and inf norms for all functions if one of the
 * norms are larger than the corresponding epsilon.
 * Also prints out the point with the largest error.
 */
void compareFunctionValue(std::vector<TestFunction *> funcs,
                          std::function<Function *(const DataTable &table)> approx_gen_func,
                          size_t numSamplePoints, size_t numEvalPoints,
                          double one_eps, double two_eps, double inf_eps);

void compareFunctionValue(TestFunction *exact,
                          std::function<Function *(const DataTable &table)> approx_gen_func,
                          size_t numSamplePoints, size_t numEvalPoints,
                          double one_eps, double two_eps, double inf_eps);

void compareJacobianValue(TestFunction *exact,
                          std::function<Function *(const DataTable &table)> approx_gen_func,
                          size_t numSamplePoints, size_t numEvalPoints,
                          double one_eps, double two_eps, double inf_eps);

void checkHessianSymmetry(TestFunction *exact,
                          std::function<Function *(const DataTable &table)> approx_gen_func,
                          size_t numSamplePoints, size_t numEvalPoints);

bool compareBSplines(const BSpline &left, const BSpline &right);

/*
 * Computes the central difference at x. Returns a 1xN row-vector.
 */
DenseMatrix centralDifference(const Function &approx, const DenseVector &x);

bool isSymmetricHessian(const Function &approx, const DenseVector &x);

DataTable sample(const Function &func, std::vector<std::vector<double>> &points);
DataTable sample(const Function *func, std::vector<std::vector<double>> &points);

// points is a vector where each element is the number of points for that dim
std::vector<std::vector<double>> linspace(std::vector<double> start, std::vector<double> end, std::vector<unsigned int> points);

// points is the total number of points, not per dim
std::vector<std::vector<double>> linspace(int dim, double start, double end, unsigned int points);

// Returns a default linspace of dim dim
std::vector<std::vector<double>> linspace(int dim);

std::vector<std::vector<double>> linspace(int dim, unsigned int pointsPerDim);

double sixHumpCamelBack(std::vector<double> x);

double getOneNorm(const DenseMatrix &m);

double getTwoNorm(const DenseMatrix &m);

double getInfNorm(const DenseMatrix &m);

// returns log(x) in base base
double log(double base, double x);

std::string pretty_print(const DenseVector &denseVec);

TestFunction *getTestFunction(int numVariables, int degree);
std::vector<TestFunction *> getTestFunctionsOfDegree(int degree);
std::vector<TestFunction *> getTestFunctionWithNumVariables(int numVariables);
std::vector<TestFunction *> getPolynomialFunctions();
std::vector<TestFunction *> getNastyTestFunctions();

/*
 * Returns 3x3 matrix,
 * first row: function value error norms
 * second row: jacobian value error norms
 * third row: hessian value error norms
 * first col: 1-norms
 * second col: 2-norms
 * third col: inf-norms
 */
DenseMatrix getErrorNorms(const Function *exact, const Function *approx, const std::vector<std::vector<double>> &points);

void checkNorms(DenseMatrix normValues, size_t numPoints, double one_eps, double two_eps, double inf_eps);
void checkNorm(DenseMatrix normValues, TestType type, size_t numPoints, double one_eps, double two_eps, double inf_eps);
void _checkNorm(DenseMatrix normValues, int row, size_t numPoints, double one_eps, double two_eps, double inf_eps);

void testApproximation(std::vector<TestFunction *> funcs,
                       std::function<Function *(const DataTable &table)> approx_gen_func,
                       TestType type, size_t numSamplePoints, size_t numEvalPoints,
                       double one_eps, double two_eps, double inf_eps);

} // namespace SPLINTER

#endif // SPLINTER_TESTINGUTILITIES_H
