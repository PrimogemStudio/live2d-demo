module;
#include <Framework/CubismFramework.hpp>
#include <Framework/ICubismAllocator.hpp>
export module Allocator;

using namespace Csm;

export class CustomAllocator final : public ICubismAllocator
{
	void* Allocate(const csmSizeType size) override { return malloc(size); }

	void Deallocate(void* memory) override { free(memory); }

	void* AllocateAligned(const csmSizeType size, const csmUint32 alignment) override
	{
		auto offset = alignment - 1 + sizeof(void*);
		auto allocation = Allocate(size + static_cast<csmUint32>(offset));
		auto alignedAddress = reinterpret_cast<size_t>(allocation) + sizeof(void*);
		if (auto shift = alignedAddress % alignment)
		{
			alignedAddress += (alignment - shift);
		}
		((void**)alignedAddress)[-1] = allocation;
		return (void*)alignedAddress;
	}

	void DeallocateAligned(void* alignedMemory) override { Deallocate(((void**)alignedMemory)[-1]); }
};
