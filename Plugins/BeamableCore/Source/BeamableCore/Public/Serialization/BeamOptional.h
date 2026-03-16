#pragma once

#include "BeamOptional.generated.h"

/**
 * Base struct for optional types in the Beam system.
 * 
 * When creating a subclass of FBeamOptional:
 * 1. Must be a USTRUCT(BlueprintType) with meta=(BeamOptionalType="YourType") - the BeamOptionalType must match the type of the Val property.
 * 2. Must have a UPROPERTY "Val" field of the wrapped type (e.g., FBeamFederation Val or UBeamStatComparisonRule* Val).
 * 3. Must override GetAddr() to return the address of the Val field.
 * 4. Must override Set(const void* Data) to assign the dereferenced Data to Val and set IsSet to true.
 * 5. Should provide a default constructor that initializes Val to a default value and sets IsSet to false (default value for UObject properties should be a NewObject).
 * 6. Should provide an explicit constructor that takes the wrapped type and sets IsSet to true.
 * 7. For pointer types, use double pointer dereferencing in Set() (e.g., *((UBeamStatComparisonRule**)Data)).
 * 8. For value types, use single pointer dereferencing in Set() (e.g., *((FBeamFederation*)Data)).
 * 
 * See FOptionalBeamFederation and FOptionalBeamStatComparisonRule for examples.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptional
{
	GENERATED_BODY()
	virtual ~FBeamOptional();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsSet = false;

	virtual const void* GetAddr() const;

	virtual bool TryGet(void* OutData, size_t& OutSize) const;

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

	template<typename T>
	const T& GetValueOrDefault(const T& Default)
	{
		if (!IsSet) return Default;
		return *static_cast<const T*>(GetAddr());
	}
};
