// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AutoGen/Arrays/ArrayOfString.h"
#include "AutoGen/Maps/MapOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamPid.h"
#include "AutoGen/Optionals/OptionalArrayOfInt32.h"
#include "AutoGen/Optionals/OptionalBeamCid.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Content/BeamContentObject.h"
#include "Serialization/BeamJsonUtils.h"

#include "MockBeamContentObject.generated.h"

USTRUCT()
struct FContentLinkWrapperTestStruct : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Beam")
	int32 SomeOtherProperty = 0;

	UPROPERTY(EditAnywhere, Category="Beam")
	FBeamContentLink LinkTest;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("SomeOtherProperty", SomeOtherProperty);
		UBeamJsonUtils::SerializeSemanticType<FString>("LinkTest", &LinkTest, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		SomeOtherProperty = Bag->GetIntegerField(TEXT("SomeOtherProperty"));
		UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("LinkTest")), LinkTest, OuterOwner);
	}
};

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class UContentLinkWrapperTestClass : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Beam")
	int32 SomeOtherProperty;

	UPROPERTY(EditAnywhere, Category="Beam")
	FBeamContentLink LinkTest;

	UPROPERTY(EditAnywhere, Category="Beam")
	UContentLinkWrapperTestClass* RecursiveLinkTest;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("SomeOtherProperty", SomeOtherProperty);
		UBeamJsonUtils::SerializeSemanticType<FString>("LinkTest", &LinkTest, Serializer);
		UBeamJsonUtils::SerializeUObject("RecursiveLinkTest", RecursiveLinkTest, Serializer);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		SomeOtherProperty = Bag->GetIntegerField(TEXT("SomeOtherProperty"));
		UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("LinkTest")), LinkTest, OuterOwner);
		UBeamJsonUtils::DeserializeUObject("RecursiveLinkTest", Bag, RecursiveLinkTest, OuterOwner);
	}
};


UCLASS(BlueprintType)
class BEAMABLECORE_API UMockBeamContentObject : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UMockBeamContentObject(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FBeamCid BeamCid;

	/**
	 * @brief Gameplay Tags are serialized as a regular string in content objects.  
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FGameplayTag UnrealGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FGameplayTag> GameplayTagsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FGameplayTag> GameplayTagsMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FBeamCid> ArrayOfBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FBeamCid> MapOfBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FString> ArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<uint8> ArrayOfU8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FString> MapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, uint8> MapOfU8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FArrayOfString BeamArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FMapOfString BeamMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FArrayOfString> ArrayOfArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<FMapOfString> ArrayOfMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FArrayOfString> MapOfArrayOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, FMapOfString> MapOfMapOfString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FOptionalBool BeamOptionalBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FOptionalArrayOfInt32 BeamOptionalArrayOfInt32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FOptionalMapOfInt64 BeamOptionalMapOfInt64;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FOptionalBeamCid BeamOptionalBeamCid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FOptionalArrayOfBeamPid BeamOptionalArrayOfBeamPid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TSoftObjectPtr<UTexture2D> UnrealSoftObjRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	UClass* UnrealClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<UClass*> UnrealClassArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TMap<FString, UClass*> UnrealClassMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FBeamContentLink TestLink;

	UPROPERTY(EditAnywhere, Category="Beam")
	FContentLinkWrapperTestStruct TestLinkStructWrapper;

	UPROPERTY(EditAnywhere, Category="Beam")
	UContentLinkWrapperTestClass* TestLinkClassWrapper;

	UPROPERTY(EditAnywhere, Category="Beam")
	TArray<FBeamContentLink> TestArrayLink;

	UPROPERTY(EditAnywhere, Category="Beam")
	TArray<FContentLinkWrapperTestStruct> TestArrayLinkStructWrapper;

	UPROPERTY(EditAnywhere, Category="Beam")
	TArray<UContentLinkWrapperTestClass*> TestArrayLinkClassWrapper;

	UPROPERTY(EditAnywhere, Category="Beam")
	TMap<FString, FBeamContentLink> TestMapLink;

	UPROPERTY(EditAnywhere, Category="Beam")
	TMap<FString, FContentLinkWrapperTestStruct> TestMapLinkStructWrapper;

	UPROPERTY(EditAnywhere, Category="Beam")
	TMap<FString, UContentLinkWrapperTestClass*> TestMapLinkClassWrapper;
};

DEFINE_CONTENT_TYPE_NAME(UMockBeamContentObject, "mock")
