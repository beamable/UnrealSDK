#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"

#include "Serialization/BeamOptional.h"
#include "BeamFederation.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamFederation : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Service;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Namespace;


	FBeamFederation() = default;

	friend bool operator==(const FBeamFederation& Lhs, const FBeamFederation& RHS)
	{
		return Lhs.Service.Equals(RHS.Service) && Lhs.Namespace.Equals(RHS.Namespace);
	}

	friend bool operator!=(const FBeamFederation& Lhs, const FBeamFederation& RHS)
	{
		return !(Lhs == RHS);
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
	{
		Serializer->WriteValue("service", Service);
		Serializer->WriteValue("namespace", Namespace);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
	{
		Serializer->WriteValue("service", Service);
		Serializer->WriteValue("namespace", Namespace);
	}


	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
	{
		Service = Bag->GetStringField(TEXT("service"));
		Namespace = Bag->GetStringField(TEXT("namespace"));
	}
};

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamFederationLibrary.MakeOptional", BeamOptionalType="FBeamFederation"))
struct BEAMABLECORE_API FOptionalBeamFederation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FBeamFederation Val;

	FOptionalBeamFederation();

	explicit FOptionalBeamFederation(FBeamFederation Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};

inline FOptionalBeamFederation::FOptionalBeamFederation()
{
	Val = FBeamFederation();
	IsSet = false;
}

inline FOptionalBeamFederation::FOptionalBeamFederation(FBeamFederation Val): Val(Val)
{
	IsSet = true;
}

inline const void* FOptionalBeamFederation::GetAddr() const { return &Val; }

inline void FOptionalBeamFederation::Set(const void* Data)
{
	Val = *((FBeamFederation*)Data);
	IsSet = true;
}

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamFederationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* @brief Constructs an FOptionalBeamFederation struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Make Optional BeamFederation", NativeMakeFunc))
	static FOptionalBeamFederation MakeOptional(FBeamFederation Value);

	/**
	 * @brief Converts an FBeamFederation into an FOptionalBeamFederation automatically.
	 * @param Value The FBeamFederation to convert.
	 * @return An optional with the BeamFederation set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName="BeamFederation To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamFederation Conv_OptionalFromValue(FBeamFederation Value);

	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamFederation& Optional, FBeamFederation& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Get Optional's BeamFederation Value"))
	static FBeamFederation GetOptionalValue(const FOptionalBeamFederation& Optional, FBeamFederation DefaultValue, bool& WasSet);
};

inline FOptionalBeamFederation UOptionalBeamFederationLibrary::MakeOptional(FBeamFederation Value)
{
	FOptionalBeamFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

inline FOptionalBeamFederation UOptionalBeamFederationLibrary::Conv_OptionalFromValue(FBeamFederation Value)
{
	FOptionalBeamFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

inline bool UOptionalBeamFederationLibrary::HasValue(const FOptionalBeamFederation& Optional, FBeamFederation& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

inline FBeamFederation UOptionalBeamFederationLibrary::GetOptionalValue(const FOptionalBeamFederation& Optional, FBeamFederation DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}
