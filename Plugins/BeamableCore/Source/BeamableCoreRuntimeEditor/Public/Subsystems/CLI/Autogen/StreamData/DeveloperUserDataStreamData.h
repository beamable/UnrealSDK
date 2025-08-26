
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DeveloperUserDataStreamData.generated.h"


UCLASS(BlueprintType)
class UDeveloperUserDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 TemplateGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCorrupted = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DeveloperUserType = {};
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
	FString Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ExpiresIn = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 IssuedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedDate = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplateGamerTag"), TemplateGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsCorrupted"), IsCorrupted, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IssuedAt"), IssuedAt, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplateGamerTag"), TemplateGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsCorrupted"), IsCorrupted, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IssuedAt"), IssuedAt, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GamerTag"), Bag, GamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("TemplateGamerTag"), Bag, TemplateGamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsCorrupted"), Bag, IsCorrupted);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("DeveloperUserType"), Bag, DeveloperUserType);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Alias"), Bag, Alias);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Description"), Bag, Description);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("Tags"), Bag, Tags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("AccessToken"), Bag, AccessToken);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("RefreshToken"), Bag, RefreshToken);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Pid"), Bag, Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Cid"), Bag, Cid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ExpiresIn"), Bag, ExpiresIn);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IssuedAt"), Bag, IssuedAt);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CreatedDate"), Bag, CreatedDate);	
	}
};


