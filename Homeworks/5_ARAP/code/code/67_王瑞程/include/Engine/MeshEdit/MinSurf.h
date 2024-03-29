#pragma once

#include <Basic/HeapObj.h>
#include <UHEMesh/HEMesh.h>
#include <Eigen/Sparse>
#include <UGM/UGM>

namespace Ubpa {
	class TriMesh;
	class Paramaterize;

	class MinSurf : public HeapObj {
	public:
		MinSurf(Ptr<TriMesh> triMesh);
	public:
		static const Ptr<MinSurf> New(Ptr<TriMesh> triMesh) {
			return Ubpa::New<MinSurf>(triMesh);
		}
	public:
		// clear cache data
		void Clear();

		// init cache data (eg. half-edge structure) for Run()
		bool Init(Ptr<TriMesh> triMesh);

		// call it after Init()
		bool Run();

	private:
		// kernel part of the algorithm. 计算将最小化结果保存到heMesh中
		void Minimize();

	private:
		class V;
		class E;
		class P;
		class V : public TVertex<V, E, P> {
		public:
			vecf3 pos;
		};
		class E : public TEdge<V, E, P> { };
		class P :public TPolygon<V, E, P> { };
	private:
		friend class Paramaterize;

		void GenWeight();
		void GenVecb();
		//生成约束 atype = 0 : 全部边界; 1 ： 最大边界
		void GenConstraint(const int atype);
		std::vector<THalfEdge<MinSurf::V, MinSurf::E, MinSurf::P>*> GetLargestBoundary();

		Ptr<TriMesh> triMesh;
		const Ptr<HEMesh<V>> heMesh; // vertice order is same with triMesh
		bool* is_boundary;

		Eigen::SparseMatrix<float> weight_mat;
		Eigen::MatrixXf vec_b;


	};
}
