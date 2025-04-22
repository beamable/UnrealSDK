#pragma once

#include "BeamOptional.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptional
{
	GENERATED_BODY()
	virtual ~FBeamOptional();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsSet = false;

	virtual const void* GetAddr() const;

	virtual bool TryGet(void* OutData, size_t& OutSize) const;;

	virtual void Set(const void* Data);

	template <typename T>
	static void Set(FBeamOptional* Optional, const T* Data) { Optional->Set(static_cast<const void*>(Data)); }

	template <typename T>
	static void Reset(FBeamOptional* Optional)
	{
		T defaultVal = T{};
		Optional->Set(static_cast<void*>(&defaultVal));
		Optional->IsSet = false;
	}

	template <typename T>
	static const T& GetValue(const FBeamOptional* Optional) { return *static_cast<const T*>(Optional->GetAddr()); }
};
