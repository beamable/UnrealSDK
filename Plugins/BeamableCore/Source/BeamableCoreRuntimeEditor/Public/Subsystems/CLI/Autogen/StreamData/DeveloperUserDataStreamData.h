
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DeveloperUserDataStreamData.generated.h"


UCLASS(BlueprintType)
class UDeveloperUserDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DeveloperUserType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 TemplatedGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreateByGamerTag = {};
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
	bool CreateCopyOnStart = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplatedGamerTag"), TemplatedGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreateByGamerTag"), CreateByGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreateCopyOnStart"), CreateCopyOnStart, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("DeveloperUserType"), DeveloperUserType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("GamerTag"), GamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TemplatedGamerTag"), TemplatedGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreateByGamerTag"), CreateByGamerTag, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccessToken"), AccessToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RefreshToken"), RefreshToken, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ExpiresIn"), ExpiresIn, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreateCopyOnStart"), CreateCopyOnStart, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Alias"), Alias, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Description"), Description, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("DeveloperUserType")), DeveloperUserType);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("GamerTag")), GamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("TemplatedGamerTag")), TemplatedGamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CreateByGamerTag")), CreateByGamerTag);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("AccessToken")), AccessToken);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("RefreshToken")), RefreshToken);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ExpiresIn")), ExpiresIn);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Pid")), Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Cid")), Cid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CreateCopyOnStart")), CreateCopyOnStart);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Alias")), Alias);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Tags")), Tags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Description")), Description);	
	}
};


