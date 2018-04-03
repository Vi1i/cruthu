#pragma once

namespace cruthu::voxel {
	class Voxel {
		bool m_head;
		std::shared_ptr<Voxel> nx;
		std::shared_ptr<Voxel> px;

		std::shared_ptr<Voxel> ny;
		std::shared_ptr<Voxel> py;

		std::shared_ptr<Voxel> nz;
		std::shared_ptr<Voxel> pz;

	public:
		Voxel(bool head = false) : m_head(head);
	};
}