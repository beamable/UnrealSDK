#include "Serialization/BeamOptional.h"

FBeamOptional::~FBeamOptional() = default;

const void* FBeamOptional::GetAddr() const
{
	ensure(false);
	return nullptr;
}

bool FBeamOptional::TryGet(void* OutData, size_t& OutSize) const
{
	ensure(false);
	return false;
}

void FBeamOptional::Set(const void* Data)
{
	ensure(false);
}
