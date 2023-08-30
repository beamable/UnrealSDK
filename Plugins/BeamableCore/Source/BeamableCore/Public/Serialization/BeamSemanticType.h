#pragma once

#include "CoreMinimal.h"
#include "BeamSemanticType.generated.h"


/// This exists for legacy reasons around our API. It allows for choosing a specific underlying blueprint compatible primitive when making requests.
/// It also makes it easier to make requests in blueprints by self-documenting a specific semantic around a FString, int32/64, etc...  
/// The first representation MUST BE A FString --- this ensures compatibility with both our content serialization and Request/Response serialization (this is also imposed due to legacy reasons).
///
/// There's one exception to this --- semantic types that are not defined in the OAPI spec (such as FBeamClientPermission)
/// are expected to inherit from FBeamJsonSerializable first (FBeamSemanticType as a second inheritance).
/// This makes it so that it is (de)serialized using the FBeamJsonSerializable interfaces instead of the default SemType (de)serialization which
/// allows for custom implementations of (de)serialization. This also allows us to replace auto-gen'ed types at will by making them into this type of SemType.
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
