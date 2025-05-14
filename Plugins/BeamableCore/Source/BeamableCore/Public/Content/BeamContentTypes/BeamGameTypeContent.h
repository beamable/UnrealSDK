// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "Content/BeamContentObject.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamGameTypeContent.generated.h"

UENUM(BlueprintType, Category="Beam|Enums")
enum class EBeamStatCompareOperation : uint8
{
	And,
	Or,
	Equals,
	NotEquals,
	In,
	NotIn,
	LessThan,
	GreaterThan,
	ContainsString
};

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamStatComparisonRule : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	EBeamStatCompareOperation Constraint;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FOptionalString Stat;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FString> Values;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<UBeamStatComparisonRule*> Rules;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		const UEnum* Enum = StaticEnum<EBeamStatCompareOperation>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Constraint));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);
		Serializer->WriteValue("Constraint", SerializationName);

		UBeamJsonUtils::SerializeOptional<FString>("Stat", &Stat, Serializer);
		UBeamJsonUtils::SerializeArray("Values", Values, Serializer);
		UBeamJsonUtils::SerializeArray<UBeamStatComparisonRule*>("Rules", Rules, Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		const UEnum* Enum = StaticEnum<EBeamStatCompareOperation>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Constraint));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);
		Serializer->WriteValue("Constraint", SerializationName);

		UBeamJsonUtils::SerializeOptional<FString>("Stat", &Stat, Serializer);
		UBeamJsonUtils::SerializeArray("Values", Values, Serializer);
		UBeamJsonUtils::SerializeArray<UBeamStatComparisonRule*>("Rules", Rules, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		const auto ConstraintStr = Bag->GetStringField(TEXT("Constraint"));
		const UEnum* Enum = StaticEnum<EBeamStatCompareOperation>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex);
			if (ConstraintStr == SerializationName)
				Constraint = static_cast<EBeamStatCompareOperation>(Enum->GetValueByIndex(NameIndex));
		}

		UBeamJsonUtils::DeserializeOptional<FString>(TEXT("Stat"), Bag, Stat, this);
		UBeamJsonUtils::DeserializeArray(Bag->GetArrayField(TEXT("Values")), Values, this);
		UBeamJsonUtils::DeserializeArray<UBeamStatComparisonRule*>(Bag->GetArrayField(TEXT("Rules")), Rules, this);
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamMatchmakingTeamsRule : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinPlayers = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPlayers = 0;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Name"), Name);
		Serializer->WriteValue(TEXT("MinPlayers"), MinPlayers);
		Serializer->WriteValue(TEXT("MaxPlayers"), MaxPlayers);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Name"), Name);
		Serializer->WriteValue(TEXT("MinPlayers"), MinPlayers);
		Serializer->WriteValue(TEXT("MaxPlayers"), MaxPlayers);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("Name"));
		MinPlayers = Bag->GetNumberField(TEXT("MinPlayers"));
		MaxPlayers = Bag->GetNumberField(TEXT("MaxPlayers"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamMatchmakingNumericRule : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MaxDelta = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Default = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Property;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("MaxDelta"), MaxDelta);
		Serializer->WriteValue(TEXT("Default"), Default);
		Serializer->WriteValue(TEXT("Property"), Property);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("MaxDelta"), MaxDelta);
		Serializer->WriteValue(TEXT("Default"), Default);
		Serializer->WriteValue(TEXT("Property"), Property);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		MaxDelta = Bag->GetNumberField(TEXT("MaxDelta"));
		Default = Bag->GetNumberField(TEXT("Default"));
		Property = Bag->GetStringField(TEXT("Property"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamMatchmakingStringRule : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Property;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Value"), Value);
		Serializer->WriteValue(TEXT("Property"), Property);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Value"), Value);
		Serializer->WriteValue(TEXT("Property"), Property);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Value = Bag->GetStringField(TEXT("Value"));
		Property = Bag->GetStringField(TEXT("Property"));
	}
};


// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(BeamOptionalType="UBeamStatComparisonRule*"))
struct BEAMABLECORE_API FOptionalBeamStatComparisonRule : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	UBeamStatComparisonRule* Val;

	FOptionalBeamStatComparisonRule();

	explicit FOptionalBeamStatComparisonRule(UBeamStatComparisonRule* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};

inline FOptionalBeamStatComparisonRule::FOptionalBeamStatComparisonRule()
{
	Val = nullptr;
	IsSet = false;
}

inline FOptionalBeamStatComparisonRule::FOptionalBeamStatComparisonRule(UBeamStatComparisonRule* Val): Val(Val)
{
	IsSet = true;
}

inline const void* FOptionalBeamStatComparisonRule::GetAddr() const { return &Val; }

inline void FOptionalBeamStatComparisonRule::Set(const void* Data)
{
	Val = *((UBeamStatComparisonRule**)Data);
	IsSet = true;
}

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamGameTypeContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	static inline const FString ContentId = TEXT("game_types");

	UFUNCTION()
	void GetContentType_UBeamGameTypeContent(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamMatchmakingTeamsRule> Teams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalBeamStatComparisonRule EntryRules;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamMatchmakingNumericRule> NumericRules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamMatchmakingStringRule> StringRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalInt32 MaxWaitDurationSecs;

	/**
	 * The length of time to wait for players to enqueue before matching.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalInt32 MatchingIntervalSecs;

	/**
	 * If you have a C#MS implementing IFederatedGameServer, use the UniqueName of its associated IThirdPartyCloudIdentity here so that Beamable knows which microservice to call to provision a GameServer for this type.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federated Game Server",
		meta=(ToolTip=
			"If you have a C#MS implementing IFederatedGameServer, use the UniqueName of its associated IThirdPartyCloudIdentity so that Beamable knows which microservice to call to provision a GameServer for this type."
		))
	FOptionalString FederatedGameServerNamespace;
};

DEFINE_CONTENT_TYPE_NAME(UBeamGameTypeContent, "game_types")
