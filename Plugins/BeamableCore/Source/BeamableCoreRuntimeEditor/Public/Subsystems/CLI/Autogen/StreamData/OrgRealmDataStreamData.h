
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "OrgRealmDataStreamData.generated.h"


UCLASS(BlueprintType)
class UOrgRealmDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ParentPid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjectName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RealmName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RealmSecret = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDev = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStaging = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsProduction = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ParentPid"), ParentPid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ProjectName"), ProjectName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmName"), RealmName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmSecret"), RealmSecret, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsDev"), IsDev, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsStaging"), IsStaging, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsProduction"), IsProduction, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ParentPid"), ParentPid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ProjectName"), ProjectName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmName"), RealmName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmSecret"), RealmSecret, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsDev"), IsDev, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsStaging"), IsStaging, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsProduction"), IsProduction, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Cid"), Bag, Cid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Pid"), Bag, Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ParentPid"), Bag, ParentPid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ProjectName"), Bag, ProjectName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("RealmName"), Bag, RealmName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("RealmSecret"), Bag, RealmSecret);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsDev"), Bag, IsDev);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsStaging"), Bag, IsStaging);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsProduction"), Bag, IsProduction);	
	}
};


