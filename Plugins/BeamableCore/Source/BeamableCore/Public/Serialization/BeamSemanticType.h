#pragma once

#include "CoreMinimal.h"
#include "BeamSemanticType.generated.h"


/// This exists for legacy reasons around our API. It allows for choosing a specific underlying blueprint compatible primitive when making requests.
/// It also makes it easier to make requests in blueprints by self-documenting a specific semantic around a FString, int32/64, etc...  
/// The first representation MUST BE A FString --- this ensures compatibility with both our content serialization and Request/Response serialization (this is also imposed due to legacy reasons).
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
	virtual FString GetSerializationRepresentationName(int Representation) const { return TNameOf<FString>::GetName(); }

	template <typename T>
	static void Set(FBeamSemanticType* SemType, const T* Data, FString RepresentationTypeName) { SemType->Set(static_cast<const void*>(Data), RepresentationTypeName); }

	template <typename T>
	static const T& GetValue(const FBeamSemanticType* SemType)
	{
		return *static_cast<const T*>(SemType->GetAddr(SemType->GetSerializationRepresentation(TNameOf<T>::GetName())));
	}
};
