#pragma once
#include <vector>
#include "matrix.h"

typedef std::vector<Vec>	PointArray;

class Hermite
{
public:
	Hermite();
	virtual ~Hermite();

	void	SetPathDuration(float t)	{ m_TotalTime = t; }
	void	SetStiffness(float s)		{ m_stiffness = s; }

	// initialize and precompute samples
	// samples are equidistant, thus speed is constant over the curve
	void	init(float duration, int numSamples, int numpoints, float* xyz);
	float	CalculateTotalLength(float step);
	void	initSamplesFromControlPoints(float duration, int numSamples);

	// get point from samples calculated at initialization
	Vec		GetPoint(float t);
	Vec		GetTangent(float t);

	// calculate point, t = 0.0 to 1.0
	Vec		CalcPoint(float w);
	// calculate point, t = 0.0 to numpoints-1
	Vec		Interpolate(float t);
	static Vec RawCurveCalc(Vec &point1, Vec &point2, Vec &tangentP1, Vec &tangentP2, float weight);

	float	m_TotalTime;
	float	m_TotalCurveLength;

	PointArray	ControlPoints; // control points
	PointArray	SamplePoints;
	PointArray	SampleTangents;

	float	m_stiffness;

private:
	void	ComputeTangents(PointArray points, PointArray& tangents);
	void	ComputeSamples(int numSamples);

	PointArray	Tangents;
};


