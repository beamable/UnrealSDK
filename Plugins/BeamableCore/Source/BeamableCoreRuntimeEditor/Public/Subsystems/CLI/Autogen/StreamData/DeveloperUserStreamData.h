
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DeveloperUserStreamData.generated.h"


UCLASS(BlueprintType)
class UDeveloperUserStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCorrupted = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DeveloperUserType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 TemplateGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AccessToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ExpiresIn = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedByGamerTag = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsCorrupted"), IsCorrupted, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplateGamerTag"), TemplateGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedByGamerTag"), CreatedByGamerTag, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsCorrupted"), IsCorrupted, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplateGamerTag"), TemplateGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedByGamerTag"), CreatedByGamerTag, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("GamerTag")), GamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("IsCorrupted")), IsCorrupted);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("DeveloperUserType")), DeveloperUserType);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CreatedDate")), CreatedDate);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("TemplateGamerTag")), TemplateGamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Alias")), Alias);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Description")), Description);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Tags")), Tags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("AccessToken")), AccessToken);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("RefreshToken")), RefreshToken);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ExpiresIn")), ExpiresIn);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Pid")), Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Cid")), Cid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CreatedByGamerTag")), CreatedByGamerTag);	
	}
};


