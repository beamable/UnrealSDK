#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/Optionalint64.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Content/BeamContentObject.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamListingContent.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOfferConstraint : public FBeamJsonSerializableUStruct
{

	GENERATED_BODY()

	FBeamOfferConstraint(const FString& Constraint, int64 Value)
		: Constraint(Constraint),
		  Value(Value){}	
	FBeamOfferConstraint() = default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Constraint = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	int64 Value = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("constraint"), Constraint);
		Serializer->WriteValue(TEXT("value"), Value);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("constraint"), Constraint);
		Serializer->WriteValue(TEXT("value"), Value);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Constraint = Bag->GetStringField(TEXT("constraint"));
		Value = Bag->GetIntegerField(TEXT("value"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOfferRequirement : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString OfferSymbol = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOfferConstraint Purchases = {};

	FBeamOfferRequirement(const FString& OfferSymbol, const FBeamOfferConstraint& Purchases)
		: OfferSymbol(OfferSymbol),
		  Purchases(Purchases)
	{}
	FBeamOfferRequirement() = default;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
		UBeamJsonUtils::SerializeUStruct(TEXT("purchases"),Purchases, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		OfferSymbol = Bag->GetStringField(TEXT("offerSymbol"));
		UBeamJsonUtils::DeserializeUStruct(TEXT("purchases"),Bag,Purchases);
	}
};


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamStatRequirement : public FBeamJsonSerializableUStruct
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalString Domain = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalString Access = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Stat = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Constraint = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	int64 Value = {};

	FBeamStatRequirement(const FOptionalString& Domain, const FOptionalString& Access, const FString& Stat,
		const FString& Constraint, int64 Value)
		: Domain(Domain),
		  Access(Access),
		  Stat(Stat),
		  Constraint(Constraint),
		  Value(Value)
	{}
	FBeamStatRequirement() = default;
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeOptional<FString>(TEXT("domain"), &Domain, Serializer);
		UBeamJsonUtils::SerializeOptional<FString>(TEXT("access"), &Access, Serializer);
		Serializer->WriteValue(TEXT("stat"), Stat);
		Serializer->WriteValue(TEXT("constraint"), Constraint);
		Serializer->WriteValue(TEXT("value"), Value);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeOptional<FString>(TEXT("domain"),Bag, Domain);
		UBeamJsonUtils::DeserializeOptional<FString>(TEXT("access"),Bag, Access);
		Stat = Bag->GetStringField(TEXT("stat"));
		Constraint = Bag->GetStringField(TEXT("constraint"));
		Value = Bag->GetIntegerField(TEXT("value"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamCohortRequirement : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Trial = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Cohort = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Constraint = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("trial"), Trial);
		Serializer->WriteValue(TEXT("cohort"), Cohort);
		Serializer->WriteValue(TEXT("constraint"), Constraint);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Trial = Bag->GetStringField(TEXT("trial"));
		Cohort = Bag->GetStringField(TEXT("cohort"));
		Constraint = Bag->GetStringField(TEXT("constraint"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamActivePeriod : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Start = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalString End = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("start"), Start);
		UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Start = Bag->GetStringField(TEXT("start"));
		UBeamJsonUtils::DeserializeOptional<FString>(TEXT("end"),Bag, End);
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptionalActivePeriod : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FBeamActivePeriod Val = {};

	explicit FBeamOptionalActivePeriod(const FBeamActivePeriod& Val): Val(Val)
	{
		IsSet = true;
	}

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((FBeamActivePeriod*)Data);
		IsSet = true;
	}
	FBeamOptionalActivePeriod()
	{
		IsSet = false;
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOfferObtainItemProperty : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Name = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FString Value = {};
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("value"), Value);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		Value = Bag->GetStringField(TEXT("value"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOfferObtainItem : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BeamContentTypeFilter="item",BeamContentTypeFilterMode="tree"),Category="Beam")
	FBeamContentId ContentId = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamOfferObtainItemProperty> Properties = {};
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("contentId"), ContentId.AsString);
		UBeamJsonUtils::SerializeArray(TEXT("properties"),Properties, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ContentId = FBeamContentId(Bag->GetStringField(TEXT("contentId")));
		UBeamJsonUtils::DeserializeArray(Bag->GetArrayField(TEXT("properties")),Properties, OuterOwner);
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOfferObtainCurrency : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BeamContentTypeFilter="currency",BeamContentTypeFilterMode="tree"),Category="Beam")
	FBeamContentId Symbol = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	int64 Amount = {};
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("symbol"), Symbol.AsString);
		Serializer->WriteValue(TEXT("amount"), Amount);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Symbol = FBeamContentId(Bag->GetStringField(TEXT("symbol")));
		Amount = Bag->GetIntegerField(TEXT("amount"));
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamListingOffer : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FString> Titles = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FString> Descriptions = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamOfferObtainCurrency> ObtainCurrency = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamOfferObtainItem> ObtainItems = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("titles"), Titles);
		Serializer->WriteValue(TEXT("descriptions"), Descriptions);
		UBeamJsonUtils::SerializeArray(TEXT("obtainCurrency"),ObtainCurrency, Serializer);
		UBeamJsonUtils::SerializeArray(TEXT("obtainItems"),ObtainItems, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Bag->TryGetStringArrayField(TEXT("titles"), Titles);
		Bag->TryGetStringArrayField(TEXT("descriptions"), Descriptions);
    	UBeamJsonUtils::DeserializeArray<FBeamOfferObtainCurrency>(Bag->GetArrayField(TEXT("obtainCurrency")), ObtainCurrency, OuterOwner);
    	UBeamJsonUtils::DeserializeArray<FBeamOfferObtainItem>(Bag->GetArrayField(TEXT("obtainItems")), ObtainItems, OuterOwner);
	}
};

UENUM(BlueprintType, Category="Beam|Enums")
enum class EBeamListingPriceType : uint8
{
	Skus,
	Currency
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamListingPrice : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	EBeamListingPriceType Type = {};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam", meta=(BeamContentTypeFilter="currency",BeamContentTypeFilterMode="tree"))
	FBeamContentId Symbol = {};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	int64 Amount = {};
	
	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		const UEnum*  Enum              = StaticEnum<EBeamListingPriceType>();
		const int64   NameIndex         = Enum->GetIndexByValue(static_cast<int64>(Type));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex).ToLower();
		Serializer->WriteValue("type", SerializationName);
		Serializer->WriteValue(TEXT("symbol"), Symbol.AsString);
		Serializer->WriteValue(TEXT("amount"), Amount);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		const auto   ConstraintStr = Bag->GetStringField(TEXT("type"));
		const UEnum* Enum          = StaticEnum<EBeamListingPriceType>();
		for (int64 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex);
			if (ConstraintStr == SerializationName)
				Type = static_cast<EBeamListingPriceType>(Enum->GetValueByIndex(NameIndex));
		}
		Symbol = Bag->GetStringField(TEXT("symbol"));
		Amount = Bag->GetIntegerField(TEXT("amount"));
	}
};
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamScheduleDefinition : public FBeamJsonSerializableUStruct
{
    GENERATED_BODY()

    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    // int64 Index = -1;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    // FString CronRawFormat;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    // FString CronHumanFormat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> Second = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> Minute = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> Hour = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> DayOfMonth = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> Month = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> Year = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Beam")
    TArray<FString> DayOfWeek = {};
	
    virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
    {
        // Serializer->WriteValue(TEXT("index"), Index);
        // Serializer->WriteValue(TEXT("cronRawFormat"), CronRawFormat);
        // Serializer->WriteValue(TEXT("cronHumanFormat"), CronHumanFormat);
		Serializer->WriteValue(TEXT("second"), Second);
        Serializer->WriteValue(TEXT("minute"), Minute);
        Serializer->WriteValue(TEXT("hour"), Hour);
        Serializer->WriteValue(TEXT("dayOfMonth"), DayOfMonth);
        Serializer->WriteValue(TEXT("month"), Month);
        Serializer->WriteValue(TEXT("year"), Year);
        Serializer->WriteValue(TEXT("dayOfWeek"), DayOfWeek);
    }

    virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
    {
        // Index = Bag->GetIntegerField(TEXT("index"));
        // CronRawFormat = Bag->GetStringField(TEXT("cronRawFormat"));
        // CronHumanFormat = Bag->GetStringField(TEXT("cronHumanFormat"));

        Bag->TryGetStringArrayField(TEXT("second"), Second);
        Bag->TryGetStringArrayField(TEXT("minute"), Minute);
        Bag->TryGetStringArrayField(TEXT("hour"), Hour);
        Bag->TryGetStringArrayField(TEXT("dayOfMonth"), DayOfMonth);
        Bag->TryGetStringArrayField(TEXT("month"), Month);
        Bag->TryGetStringArrayField(TEXT("year"), Year);
        Bag->TryGetStringArrayField(TEXT("dayOfWeek"), DayOfWeek);
    }
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamSchedule : public FBeamJsonSerializableUStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    FString Description = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    FString ActiveFrom = FDateTime::UtcNow().ToIso8601();

    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    FOptionalString ActiveTo = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
    TArray<FBeamScheduleDefinition> Definitions = {};

    // UPROPERTY(BlueprintCallable)
    bool IsPeriod() const
    {
        for (const FBeamScheduleDefinition& Def : Definitions)
        {
            bool HourContainsWildcard = Def.Hour.Contains(TEXT("*"));
            bool MinuteContainsWildcard = Def.Minute.Contains(TEXT("*"));

            if ((HourContainsWildcard && !MinuteContainsWildcard) ||
                (!HourContainsWildcard && MinuteContainsWildcard) ||
                (!HourContainsWildcard && !MinuteContainsWildcard))
            {
                return true;
            }
        }
        return false;
    }

    virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
    {
        Serializer->WriteValue(TEXT("description"), Description);
        Serializer->WriteValue(TEXT("activeFrom"), ActiveFrom);
		UBeamJsonUtils::SerializeOptional<FString>(TEXT("activeTo"), &ActiveTo, Serializer);
		UBeamJsonUtils::SerializeArray(TEXT("definitions"),Definitions, Serializer);
    }

    virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
    {
        Description = Bag->GetStringField(TEXT("description"));
        ActiveFrom = Bag->GetStringField(TEXT("activeFrom"));
    	UBeamJsonUtils::DeserializeOptional<FString>(TEXT("activeTo"),Bag, ActiveTo);
    	UBeamJsonUtils::DeserializeArray<FBeamScheduleDefinition>(Bag->GetArrayField(TEXT("definitions")), Definitions, OuterOwner);
    }
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptionalCohortRequirements : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamCohortRequirement> Val = {};


	explicit FBeamOptionalCohortRequirements(const TArray<FBeamCohortRequirement>& Val): Val(Val)
	{
		IsSet = true;
	}
	FBeamOptionalCohortRequirements()
	{
		IsSet = false;
	}

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((TArray<FBeamCohortRequirement>*)Data);
		IsSet = true;
	}
};
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptionalStatRequirements : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamStatRequirement> Val = {};


	explicit FBeamOptionalStatRequirements(const TArray<FBeamStatRequirement>& Val): Val(Val)
	{
		IsSet = true;
	}
	FBeamOptionalStatRequirements()
	{
		IsSet = false;
	}

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((TArray<FBeamStatRequirement>*)Data);
		IsSet = true;
	}
};
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptionalOfferRequirements : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TArray<FBeamOfferRequirement> Val = {};

	explicit FBeamOptionalOfferRequirements(const TArray<FBeamOfferRequirement>& Val): Val(Val)
	{
		IsSet = true;
	}
	FBeamOptionalOfferRequirements()
	{
		IsSet = false;
	}

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((TArray<FBeamOfferRequirement>*)Data);
		IsSet = true;
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOptionalSchedule : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamSchedule Val = {};


	explicit FBeamOptionalSchedule(const FBeamSchedule& Val): Val(Val)
	{
		IsSet = true;
	}
	FBeamOptionalSchedule()
	{
		IsSet = false;
	}

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((FBeamSchedule*)Data);
		IsSet = true;
	}
};

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamListingContent : public UBeamContentObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void GetContentType_UBeamListingContent(FString& Result);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamListingPrice price = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamListingOffer offer = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOptionalActivePeriod activePeriod = {};
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalInt64 purchaseLimit = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOptionalCohortRequirements cohortRequirements = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOptionalStatRequirements playerStatRequirements = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOptionalOfferRequirements offerRequirements = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TMap<FString,FString> clientData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalInt64 activeDurationSeconds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalInt64 activeDurationCoolDownSeconds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalInt64 activeDurationPurchaseLimit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalString buttonText = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FBeamOptionalSchedule schedule = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	FOptionalString scheduleInstancePurchaseLimit = {};
};

DEFINE_CONTENT_TYPE_NAME(UBeamListingContent, "listings")