// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamSharedTypes.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamOptional.h"

#include "BeamOptionalTypes.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.BeamOptionalTypesLibrary.MakeOptionalInt"))
struct FOptionalInt : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int Val;

	FOptionalInt();

	explicit FOptionalInt(int Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};

// // Has Native Make/Break require static blueprint pure functions to present as nodes that
// // don't require an execution pin connection. This is super relevant for Blueprint UX. 
// USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.BeamOptionalTypesLibrary.MakeOptionalString"))
// struct FOptionalString : public FBeamOptional
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(BlueprintReadOnly)
// 	FString Val;
//
// 	FOptionalString();
//
// 	explicit FOptionalString(FString Val);
//
// 	virtual const void* GetAddr() const override;
//
// 	virtual void Set(const void* Data) override;
// };

// USTRUCT(BlueprintType)
// struct FArrayOfString : public FBeamArray
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TArray<FString> Values;
//
// 	FArrayOfString();
//
// 	FArrayOfString(const TArray<FString>& Values);
//
// 	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
//
// 	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
//
// 	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
// };
//
// USTRUCT(BlueprintType)
// struct FMapOfString : public FBeamMap
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TMap<FString, FString> Values;
//
// 	FMapOfString();
//
// 	FMapOfString(const TMap<FString, FString>& Val);
//
// 	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
//
// 	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
//
// 	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override;
// };
//
//
// USTRUCT(BlueprintType)
// struct FArrayOfTokenResponse : public FBeamArray
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TArray<UTokenResponse*> Values;
//
// 	FArrayOfTokenResponse();
//
// 	FArrayOfTokenResponse(const TArray<UTokenResponse*>& Val);
//
// 	virtual ~FArrayOfTokenResponse() override;
//
// 	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
//
// 	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
//
// 	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
// };
//
// USTRUCT(BlueprintType)
// struct FMapOfTokenResponse : public FBeamMap
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TMap<FString, UTokenResponse*> Values;
//
// 	FMapOfTokenResponse();
//
// 	FMapOfTokenResponse(const TMap<FString, UTokenResponse*>& Val);
//
// 	virtual ~FMapOfTokenResponse() override;
//
// 	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
//
// 	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
//
// 	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements) override;
// };