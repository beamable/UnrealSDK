#pragma once

#include "CoreMinimal.h"
#include "BeamSemanticType.generated.h"

USTRUCT()
struct BEAMABLECORE_API FBeamSemanticType
{
	GENERATED_BODY()

	FBeamSemanticType() = default;

	FBeamSemanticType(const FBeamSemanticType& Other)
	{
	}

	virtual ~FBeamSemanticType() = default;

	virtual const void* GetAddr(int Representation) const { return nullptr; }

	virtual void Set(const void* Data, FString RepresentationTypeName)
	{
	}

	virtual int GetSerializationRepresentation(FString RepresentationTypeName) const { return 0; }

	template <typename T>
	static void Set(FBeamSemanticType* SemType, const T* Data, FString RepresentationTypeName) { SemType->Set(static_cast<const void*>(Data), RepresentationTypeName); }

	template <typename T>
	static const T& GetValue(const FBeamSemanticType* SemType)
	{
		return *static_cast<const T*>(SemType->GetAddr(SemType->GetSerializationRepresentation(TNameOf<T>::GetName())));
	}
};
