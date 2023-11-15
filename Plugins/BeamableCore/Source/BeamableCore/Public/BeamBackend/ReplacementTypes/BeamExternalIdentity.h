#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamOptional.h"
#include "Json/Public/Dom/JsonObject.h"

#include "BeamExternalIdentity.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamExternalIdentity : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Id", Category="Beam")
	FString UserId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespace", Category="Beam")
	FString ProviderNamespace = {};	
	
	FBeamExternalIdentity() = default;

	friend bool operator==(const FBeamExternalIdentity& Lhs, const FBeamExternalIdentity& RHS)
	{
		return Lhs.ProviderNamespace.Equals(RHS.ProviderNamespace) && Lhs.ProviderService.Equals(RHS.ProviderService) && Lhs.UserId.Equals(RHS.UserId);
	}

	friend bool operator!=(const FBeamExternalIdentity& Lhs, const FBeamExternalIdentity& RHS)
	{
		return !(Lhs == RHS);
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("providerService"), ProviderService);
		Serializer->WriteValue(TEXT("userId"), UserId);
		Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ProviderService   = Bag->GetStringField(TEXT("providerService"));
		UserId            = Bag->GetStringField(TEXT("userId"));
		ProviderNamespace = Bag->GetStringField(TEXT("providerNamespace"));
	}
};

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamExternalIdentityLibrary.MakeOptional", BeamOptionalType="FBeamExternalIdentity"))
struct BEAMABLECORE_API FOptionalBeamExternalIdentity : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FBeamExternalIdentity Val;

	FOptionalBeamExternalIdentity();

	explicit FOptionalBeamExternalIdentity(FBeamExternalIdentity Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};

inline FOptionalBeamExternalIdentity::FOptionalBeamExternalIdentity()
{
	Val   = FBeamExternalIdentity();
	IsSet = false;
}

inline FOptionalBeamExternalIdentity::FOptionalBeamExternalIdentity(FBeamExternalIdentity Val): Val(Val)
{
	IsSet = true;
}

inline const void* FOptionalBeamExternalIdentity::GetAddr() const { return &Val; }

inline void FOptionalBeamExternalIdentity::Set(const void* Data)
{
	Val   = *((FBeamExternalIdentity*)Data);
	IsSet = true;
}

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamExternalIdentityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* @brief Constructs an FOptionalBeamExternalIdentity struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional BeamExternalIdentity", NativeMakeFunc))
	static FOptionalBeamExternalIdentity MakeOptional(FBeamExternalIdentity Value);

	/**
	 * @brief Converts an FBeamExternalIdentity into an FOptionalBeamExternalIdentity automatically.
	 * @param Value The FBeamExternalIdentity to convert.
	 * @return An optional with the BeamExternalIdentity set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - BeamExternalIdentity To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamExternalIdentity Conv_OptionalFromValue(FBeamExternalIdentity Value);

	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's BeamExternalIdentity Value"))
	static FBeamExternalIdentity GetOptionalValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity DefaultValue, bool& WasSet);
};

inline FOptionalBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::MakeOptional(FBeamExternalIdentity Value)
{
	FOptionalBeamExternalIdentity Optional;
	Optional.Val   = Value;
	Optional.IsSet = true;
	return Optional;
}

inline FOptionalBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::Conv_OptionalFromValue(FBeamExternalIdentity Value)
{
	FOptionalBeamExternalIdentity Optional;
	Optional.Val   = Value;
	Optional.IsSet = true;
	return Optional;
}

inline bool UOptionalBeamExternalIdentityLibrary::HasValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

inline FBeamExternalIdentity UOptionalBeamExternalIdentityLibrary::GetOptionalValue(const FOptionalBeamExternalIdentity& Optional, FBeamExternalIdentity DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}
