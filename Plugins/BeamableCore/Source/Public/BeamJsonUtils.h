#pragma once

#include "BeamTypeTraits.h"
#include "Misc/DefaultValueHelper.h"

#include "BeamJsonUtils.generated.h"


/**
 * @brief Shorter name for the default Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>> TUnrealJsonSerializer;

/**
 * @brief Shorter name for the pretty Unreal Json Writer.
 */
typedef TSharedRef<TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>> TPrettyUnrealJsonSerializer;


USTRUCT(BlueprintType)
struct FBeamJsonSerializable
{
	GENERATED_BODY()
	virtual ~FBeamJsonSerializable() = default;

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const
	{
		Serializer->WriteObjectStart();
		BeamSerializeProperties(Serializer);
		Serializer->WriteObjectEnd();
	}

	virtual void BeamSerialize(TPrettyUnrealJsonSerializer& Serializer) const
	{
		Serializer->WriteObjectStart();
		BeamSerializeProperties(Serializer);
		Serializer->WriteObjectEnd();
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
	{
		ensure(false);
	}

	virtual void BeamSerializeProperties(TPrettyUnrealJsonSerializer& Serializer) const
	{
		ensure(false);
	}

	virtual void BeamDeserialize(const FString& JsonString)
	{
		auto Bag = FJsonDataBag{};
		Bag.FromJson(JsonString);
		BeamDeserializeProperties(Bag.JsonObject);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
	{
		ensure(false);
	}
};


USTRUCT(BlueprintType)
struct FBeamArray : public FBeamJsonSerializable
{
	GENERATED_BODY()

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteArrayStart();
		BeamSerializeProperties(Serializer);
		Serializer->WriteArrayEnd();
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		ensure(false);
	}

	virtual void BeamSerializeProperties(TPrettyUnrealJsonSerializer& Serializer) const override
	{
		ensure(false);
	}

	virtual void BeamDeserialize(const FString& JsonString) override
	{
		TArray<TSharedPtr<FJsonValue>> Elements;
		const auto ArrayReader = TJsonReaderFactory<>::Create(JsonString);
		FJsonSerializer::Deserialize(ArrayReader, Elements);
		BeamDeserializeElements(Elements);
	}

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
	{
		ensure(false);
	}
};

USTRUCT(BlueprintType)
struct FBeamMap : public FBeamJsonSerializable
{
	GENERATED_BODY()

	virtual void BeamSerialize(TUnrealJsonSerializer& Serializer) const override
	{
		// For the map case, we simply serialize the map as the entire object --- if we try to wrap it around, we'd get
		// {
		//    { ... Map contents ... }
		// }
		// which is invalid JSON.
		BeamSerializeProperties(Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		ensure(false); // "This should be overriden!"
	}

	virtual void BeamSerializeProperties(TPrettyUnrealJsonSerializer& Serializer) const override
	{
		ensure(false); // "This should be overriden!"
	}

	virtual void BeamDeserialize(const FString& JsonString) override
	{
		auto Bag = FJsonDataBag{};
		Bag.FromJson(JsonString);
		BeamDeserializeElements(Bag.JsonObject);
	}

	virtual void BeamDeserializeElements(const TSharedPtr<FJsonObject>& Bag)
	{
		ensure(false); // "This should be overriden!"
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override final
	{
		ensure(false); // "This should never be called!"
	}
};

USTRUCT(BlueprintType)
struct FBeamOptional
{
	GENERATED_BODY()
	virtual ~FBeamOptional() = default;

	UPROPERTY(BlueprintReadOnly)
	bool IsSet = false;

	virtual const void* GetAddr() const
	{
		ensure(false);
		return nullptr;
	}

	virtual bool TryGet(void* OutData, size_t& OutSize) const
	{
		ensure(false);
		return false;
	};

	virtual void Set(const void* Data)
	{
		ensure(false);
	}

	template <typename T>
	static void Set(FBeamOptional* Optional, const T* Data) { Optional->Set(static_cast<const void*>(Data)); }

	template <typename T>
	static void Reset(FBeamOptional* Optional)
	{
		T defaultVal = T{};
		Optional->Set(static_cast<void*>(&defaultVal));
		Optional->IsSet = false;
	}

	template <typename T>
	static const T& GetValue(const FBeamOptional* Optional) { return *static_cast<const T*>(Optional->GetAddr()); }
};


UCLASS(BlueprintType)
class UBeamJsonUtils final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	template <typename TOptionalType, typename TDataType, typename TSerializer>
	static void _SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TSerializer Serializer)
	{
		static_assert(TIsSame<TSerializer, TPrettyUnrealJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		if (ToSerialize->IsSet)
		{
			if constexpr (TIsTArray<TOptionalType>::Value)
			{
				static_assert(TIsTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is an array, TDataType must be the type for that array.");

				const auto Array = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				UBeamJsonUtils::SerializeArray<TDataType>(Identifier, Array, Serializer);
			}
			else if constexpr (TIsDerivedFrom<TOptionalType, FBeamMap>::Value)
			{
				const FBeamMap* JsonSerializable = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteObjectStart(Identifier);
				JsonSerializable->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
			else if constexpr (TIsDerivedFrom<TOptionalType, FBeamArray>::Value)
			{
				const FBeamArray* JsonSerializable = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteArrayStart(Identifier);
				JsonSerializable->BeamSerializeProperties(Serializer);
				Serializer->WriteArrayEnd();
			}
			else if constexpr (TIsDerivedFrom<TOptionalType, FBeamJsonSerializable>::Value)
			{
				const FBeamJsonSerializable* JsonSerializable = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteObjectStart(Identifier);
				JsonSerializable->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
			else
			{
				const TOptionalType* val = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteValue(Identifier, *val);
			}
		}
	}

	template <typename TDataType, typename TSerializer>
	static void _SerializeArrayElements(const TArray<TDataType>& Array, TSerializer& Serializer)
	{
		static_assert(TIsSame<TSerializer, TPrettyUnrealJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteObjectStart();
				Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteArrayStart();
				Value.BeamSerializeProperties(Serializer);
				Serializer->WriteArrayEnd();
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteObjectStart();
				Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteValue(Value);
			}
		}
	}

	template <typename TMapType, typename TDataType, typename TSerializer>
	static void _SerializeMapElements(const TMap<FString, TMapType>& Map, TSerializer& Serializer)
	{
		static_assert(TIsSame<TSerializer, TPrettyUnrealJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		// Compile-time branch for array case
		if constexpr (TIsTArray<TMapType>::Value)
		{
			static_assert(!TIsTemplateParam<TDataType, TMapType>::value, "TMapType can NOT be an array! It must be wrapped in a FBeamArrayOf____ Type instead.");
		}
		// Compile-time branch for Map of Maps
		else if constexpr (TIsDerivedFrom<TMapType, FBeamMap>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		// Compile-time branch for Map of Arrays
		else if constexpr (TIsDerivedFrom<TMapType, FBeamArray>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteArrayStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteArrayEnd();
			}
		}
		// Compile-time branch for Map of non-Primitives
		else if constexpr (TIsDerivedFrom<TMapType, FBeamJsonSerializable>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		// If it's not any of the types we care about, let's assume it's a FString or supported primitive	
		else
		{
			for (const auto& Kvp : Map)
				Serializer->WriteValue(Kvp.Key, Kvp.Value);
		}
	}

public:
	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TUnrealJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TPrettyUnrealJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TPrettyUnrealJsonSerializer>(Identifier, ToSerialize, Serializer);
	}


	template <typename TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}

	template <typename TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TPrettyUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TPrettyUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}


	template <typename TDataType>
	static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart(Identifier);
		_SerializeArrayElements<TDataType, TUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}

	template <typename TDataType>
	static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TPrettyUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart(Identifier);
		_SerializeArrayElements<TDataType, TPrettyUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}


	template <typename TMapType, typename TDataType = TMapType>
	static void SerializeMap(const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart();
		_SerializeMapElements<TMapType, TDataType, TUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType>
	static void SerializeMap(const TMap<FString, TMapType>& Map, TPrettyUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart();
		_SerializeMapElements<TMapType, TDataType, TPrettyUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType>
	static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart(Identifier);
		_SerializeMapElements<TMapType, TDataType, TUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType>
	static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TPrettyUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart(Identifier);
		_SerializeMapElements<TMapType, TDataType, TPrettyUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}


	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void DeserializeOptional(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamOptional& ToDeserialize)
	{
		// If we didn't receive this field...
		if (!OwnerBag->HasField(Identifier))
		{
			// let's initialize default values based on the type.
			TOptionalType defaultValue{};
			FBeamOptional::Set(&ToDeserialize, &defaultValue);

			// Let's force IsSet back to false.
			ToDeserialize.IsSet = false;
		}
		// If we did receive the field, let's set the optional value based on the types that we get.
		else
		{
			const auto JsonField = OwnerBag->TryGetField(Identifier);
			if constexpr (TIsTMap<TOptionalType>::Value)
			{
				static_assert(TIsSecondTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is a map, TDataType must be the type for that map.");
				TMap<FString, TDataType> ParsedMap;
				for (const auto KvP : JsonField->AsObject()->Values)
				{
					const auto Key = KvP.Key;
					const auto Item = KvP.Value;
					if constexpr (TIsSame<TDataType, FString>::Value)
					{
						const FString Val = Item->AsString();
						ParsedMap.Add(Key, Val);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeElements(Item->AsObject());
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeElements(Item->AsArray());
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeProperties(Item->AsObject());
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsSame<TDataType, int>::Value)
					{
						const FString Val = Item->AsString();
						int parsed;
						FDefaultValueHelper::ParseInt(Val, parsed);
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsSame<TDataType, int64>::Value)
					{
						const FString Val = Item->AsString();
						int64 parsed;
						FDefaultValueHelper::ParseInt64(Val, parsed);
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsSame<TDataType, float>::Value)
					{
						const FString Val = Item->AsString();
						float parsed;
						FDefaultValueHelper::ParseFloat(Val, parsed);
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsSame<TDataType, double>::Value)
					{
						const FString Val = Item->AsString();
						double parsed;
						FDefaultValueHelper::ParseDouble(Val, parsed);
						ParsedMap.Add(Key, parsed);
					}
					else if constexpr (TIsSame<TDataType, bool>::Value)
					{
						const FString Val = Item->AsString();
						bool parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedMap.Add(Key, parsed);
					}
				}
				FBeamOptional::Set(&ToDeserialize, &ParsedMap);
			}
			if constexpr (TIsTArray<TOptionalType>::Value)
			{
				static_assert(TIsTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is an array, TDataType must be the type for that array.");

				TArray<TDataType> ParsedArray;
				for (const auto ArrayJsonItem : JsonField->AsArray())
				{
					if constexpr (TIsSame<TDataType, FString>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						ParsedArray.Add(Val);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeElements(ArrayJsonItem->AsObject());
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeElements(ArrayJsonItem->AsArray());
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
					{
						TDataType parsed;
						parsed.BeamDeserializeProperties(ArrayJsonItem->AsObject());
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsSame<TDataType, int>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int parsed;
						FDefaultValueHelper::ParseInt(Val, parsed);
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsSame<TDataType, int64>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int64 parsed;
						FDefaultValueHelper::ParseInt64(Val, parsed);
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsSame<TDataType, float>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						float parsed;
						FDefaultValueHelper::ParseFloat(Val, parsed);
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsSame<TDataType, double>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						double parsed;
						FDefaultValueHelper::ParseDouble(Val, parsed);
						ParsedArray.Add(parsed);
					}
					else if constexpr (TIsSame<TDataType, bool>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						bool parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedArray.Add(parsed);
					}
				}
				FBeamOptional::Set(&ToDeserialize, &ParsedArray);
			}
			else
			{
				if constexpr (TIsSame<TOptionalType, FString>::Value)
				{
					const FString val = JsonField->AsString();
					FBeamOptional::Set(&ToDeserialize, &val);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamMap>::Value)
				{
					TOptionalType parsed;
					parsed.BeamDeserializeElements(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamArray>::Value)
				{
					TOptionalType parsed;
					parsed.BeamDeserializeElements(JsonField->AsArray());
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamJsonSerializable>::Value)
				{
					TOptionalType parsed;
					parsed.BeamDeserializeProperties(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsSame<TOptionalType, int>::Value)
				{
					const FString val = JsonField->AsString();
					int parsed;
					FDefaultValueHelper::ParseInt(val, parsed);
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsSame<TOptionalType, int64>::Value)
				{
					const FString val = JsonField->AsString();
					int64 parsed;
					FDefaultValueHelper::ParseInt64(val, parsed);
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsSame<TOptionalType, float>::Value)
				{
					const FString val = JsonField->AsString();
					float parsed;
					FDefaultValueHelper::ParseFloat(val, parsed);
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsSame<TOptionalType, double>::Value)
				{
					const FString val = JsonField->AsString();
					double parsed;
					FDefaultValueHelper::ParseDouble(val, parsed);
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
				else if constexpr (TIsSame<TOptionalType, bool>::Value)
				{
					const FString val = JsonField->AsString();
					bool parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
					FBeamOptional::Set(&ToDeserialize, &parsed);
				}
			}
		}
	}

	template <typename TDataType>
	static void DeserializeArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<TDataType>& Array)
	{
		for (const TSharedPtr<FJsonValue>& JsonValue : JsonArray)
		{
			if constexpr (TIsSame<TDataType, FString>::Value)
			{
				const FString val = JsonValue->AsString();
				Array.Add(val);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeElements(JsonValue->AsObject());
				Array.Add(parsed);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeElements(JsonValue->AsArray());
				Array.Add(parsed);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Array.Add(parsed);
			}
			else if constexpr (TIsSame<TDataType, int>::Value)
			{
				const FString val = JsonValue->AsString();
				int parsed;
				FDefaultValueHelper::ParseInt(val, parsed);
				Array.Add(parsed);
			}
			else if constexpr (TIsSame<TDataType, int64>::Value)
			{
				const FString val = JsonValue->AsString();
				int64 parsed;
				FDefaultValueHelper::ParseInt64(val, parsed);
				Array.Add(parsed);
			}
			else if constexpr (TIsSame<TDataType, float>::Value)
			{
				const FString val = JsonValue->AsString();
				float parsed;
				FDefaultValueHelper::ParseFloat(val, parsed);
				Array.Add(parsed);
			}
			else if constexpr (TIsSame<TDataType, double>::Value)
			{
				const FString val = JsonValue->AsString();
				double parsed;
				FDefaultValueHelper::ParseDouble(val, parsed);
				Array.Add(parsed);
			}
			else if constexpr (TIsSame<TDataType, bool>::Value)
			{
				const FString val = JsonValue->AsString();
				bool parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Array.Add(parsed);
			}
		}
	}

	template <typename TMapType, typename TDataType = TMapType>
	static void DeserializeMap(const TSharedPtr<FJsonObject>& JsonMap, TMap<FString, TMapType>& Map)
	{
		if constexpr (TIsTArray<TMapType>::Value)
			static_assert(TIsTemplateParam<TDataType, TMapType>::value, "When TMapType is an array, TDataType must be the type for that array.");

		if constexpr (TIsTMap<TMapType>::Value)
		{
			static_assert(TIsFirstTemplateParam<TDataType, FString>::value, "When TMapType is a map, the map key type must be FString.");
			static_assert(TIsSecondTemplateParam<TDataType, TMapType>::value, "When TMapType is a map,  TDataType must be the value type for that map.");
		}

		for (const auto& Value : JsonMap->Values)
		{
			const auto Key = Value.Key;
			const auto JsonValue = Value.Value;

			if constexpr (TIsSame<TMapType, FString>::Value)
			{
				const auto Val = Value.Value->AsString();
				Map.Add(Key, Val);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamMap>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeElements(JsonValue->AsObject());
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamArray>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeElements(JsonValue->AsArray());
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamJsonSerializable>::Value)
			{
				TDataType parsed;
				parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsTArray<TMapType>::Value)
			{
				TArray<TSharedPtr<FJsonValue>> JsonArray = JsonValue->AsArray();
				TArray<TDataType> ParsedArray;
				UBeamJsonUtils::DeserializeArray<TDataType>(JsonArray, ParsedArray);
				Map.Add(Key, ParsedArray);
			}
			else if constexpr (TIsSame<TMapType, int>::Value)
			{
				const auto Val = Value.Value->AsString();
				int parsed;
				FDefaultValueHelper::ParseInt(Val, parsed);
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsSame<TMapType, int64>::Value)
			{
				const auto Val = Value.Value->AsString();
				int64 parsed;
				FDefaultValueHelper::ParseInt64(Val, parsed);
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsSame<TMapType, float>::Value)
			{
				const auto Val = Value.Value->AsString();
				float parsed;
				FDefaultValueHelper::ParseFloat(Val, parsed);
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsSame<TMapType, double>::Value)
			{
				const auto Val = Value.Value->AsString();
				double parsed;
				FDefaultValueHelper::ParseDouble(Val, parsed);
				Map.Add(Key, parsed);
			}
			else if constexpr (TIsSame<TMapType, bool>::Value)
			{
				const auto Val = Value.Value->AsString();
				bool parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Map.Add(Key, parsed);
			}
		}
	}
};
