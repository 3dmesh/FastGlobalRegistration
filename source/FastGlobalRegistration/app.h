// ----------------------------------------------------------------------------
// -                       Fast Global Registration                           -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016
// Qianyi Zhou <Qianyi.Zhou@gmail.com>
// Jaesik Park <syncle@gmail.com>
// Vladlen Koltun <vkoltun@gmail.com>
// Intel Labs
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------
#include <vector>
#include <flann/flann.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#define DIM_FPFH			33	// FPFH feature dimension
#define DIV_FACTOR			1.4 // 2.0 originally
#define MAX_CORR_DIST		0.025 // todo: should check
#define ITERATION_NUMBER	64
#define TUPLE_SCALE			0.95
#define TUPLE_MAX_CNT		300


using namespace Eigen;
using namespace std;

typedef vector<Vector3f> Points;
typedef vector<VectorXf> Feature;

class CApp{
public:
	void ReadFeature(const char* filepath);
	void NormalizePoints();
	void AdvancedMatching();
	void WriteTrans(const char* filepath);
	double OptimizePairwise(double mu_, bool decrease_mu_, int numIter_);

private:
	// containers
	vector<Points> pointcloud_;
	vector<Feature> features_;
	Matrix4f TransOutput_;
	vector<pair<int, int>> corres_;

	// for normalization
	Points Means;
	float GlobalScale;

	// some internal functions
	void ReadFeature(const char* filepath, Points& pts, Feature& feat);

	//flann::Index<flann::L2<float>>* BuildFLANNTree(Feature& input);
	//void GetFLANNMatrix(Feature);
	void SearchFLANNTree(flann::Index<flann::L2<float>>* index,
		VectorXf& input,
		std::vector<int>& indices,
		std::vector<float>& dists,
		int nn);
};