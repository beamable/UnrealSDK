// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JsonDomBuilder.h"
#include "UObject/Interface.h"

#include "BeamContentObject.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BEAMABLECORE_API UBeamContentObject : public UObject
{
	GENERATED_BODY()

public:
	FString Id;
	FString Version;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Beam")
	void ToJson(FString& Serialized);
	virtual void ToJson_Implementation(FString& Serialized);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Beam")
	void FromJson(const FString& Json);

	virtual void FromJson_Implementation(const FString& Json);


	virtual void BuildJsonObject(FJsonDomBuilder::FObject& Output);

	virtual void BuildPropertiesJsonObject(FJsonDomBuilder::FObject& Properties);

	virtual void ParseJsonObject(const TSharedPtr<FJsonObject>& Object);

	virtual void ParsePropertiesJsonObject(const TSharedPtr<FJsonObject>& JsonProperties);


	static void SerializeArrayProperty(FString CurrPropName, FJsonDomBuilder::FArray& PropArray, const FArrayProperty* const ArrayProperty, const void* ArrayOwner);
	static void ParseArrayProperty(const FString& PropName, const TArray<TSharedPtr<FJsonValue>>& JsonArray, const FArrayProperty* ArrayProperty, const void* ArrayOwner);

	static void SerializeMapProperty(FString CurrPropName, FJsonDomBuilder::FObject& JsonMap, const FMapProperty* const MapProperty, const void* MapOwner);
	static void ParseMapProperty(const FString& PropName, const TSharedPtr<FJsonObject>& JsonMap, const FMapProperty* MapProperty, void* MapOwner);	

	template <typename TInner>
	static void BuildArray(FJsonDomBuilder::FArray& ArrayToFill, const FArrayProperty* const ArrayProperty, const void* ArrayOwner)
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));

		const auto ArrayNum = Val->Num();
		for (auto i = 0; i < ArrayNum; i++)
		{
			const TInner* Data = static_cast<const TInner*>(Val->GetData());
			ArrayToFill.Add(*(Data + i));
		}
	}

	template <typename TInner>
	static void BuildMap(FStrProperty* const StrKeyProperty, FJsonDomBuilder::FObject JsonMap, FScriptMapHelper MapHelper)
	{
		const auto MapNum = MapHelper.Num();
		for (auto i = 0; i < MapNum; i++)
		{
			if (MapHelper.IsValidIndex(i))
			{
				const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
				const TInner* Data = reinterpret_cast<const TInner*>(MapHelper.GetValuePtr(i));

				JsonMap.Set(Key, *Data);
			}
		}
	}
};
