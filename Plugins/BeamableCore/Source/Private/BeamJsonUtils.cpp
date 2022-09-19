#include "BeamJsonUtils.h"

#include "BeamTypeTraits.h"
#include "Misc/DefaultValueHelper.h"

template <typename TOptionalType, typename TDataType>
constexpr void FBeamJsonUtils::SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealJsonSerializer Serializer)
{
	if (ToSerialize->IsSet)
	{
		if constexpr (TIsTArray<TOptionalType>::Value)
		{
			static_assert(TIsTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is an array, TDataType must be the type for that array.");

			const auto Array = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
			FBeamJsonUtils::SerializeArray<TDataType>(Identifier, Array, Serializer);
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

template <typename TDataType>
constexpr void FBeamJsonUtils::SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
{
	Serializer->WriteArrayStart(Identifier);
	if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
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
	Serializer->WriteArrayEnd();
}

template <typename TMapType, typename TDataType>
constexpr void FBeamJsonUtils::SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer)
{
	Serializer->WriteObjectStart(Identifier);

	// Compile-time branch for array case
	if constexpr (TIsTArray<TMapType>::Value)
	{
		static_assert(TIsTemplateParam<TDataType, TMapType>::value, "When TMapType is an array, TDataType must be the type for that array.");

		for (const auto& Kvp : Map)
		{
			const auto& array = StaticCast<TArray<TDataType>>(Kvp.Value);
			FBeamJsonUtils::SerializeArray<TDataType>(Kvp.Key, array, Serializer);
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

	Serializer->WriteObjectEnd();
}


template <typename TOptionalType, typename TDataType>
constexpr void FBeamJsonUtils::DeserializeOptional(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamOptional& ToDeserialize)
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
constexpr void FBeamJsonUtils::DeserializeArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<TDataType>& Array)
{
	for (const TSharedPtr<FJsonValue>& JsonValue : JsonArray)
	{
		if constexpr (TIsSame<TDataType, FString>::Value)
		{
			const FString val = JsonValue->AsString();
			Array.Add(val);
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

template <typename TMapType, typename TDataType>
constexpr void FBeamJsonUtils::DeserializeMap(const TSharedPtr<FJsonObject>& JsonMap, TMap<FString, TMapType>& Map)
{
	if constexpr (TIsTArray<TMapType>::Value)
		static_assert(TIsTemplateParam<TDataType, TMapType>::value, "When TMapType is an array, TDataType must be the type for that array.");

	for (const auto& Value : JsonMap->Values)
	{
		const auto Key = Value.Key;
		const auto JsonValue = Value.Value;

		if constexpr (TIsSame<TMapType, FString>::Value)
		{
			const auto Val = Value.Value->AsString();
			Map.Add(Key, Val);
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
			FBeamJsonUtils::DeserializeArray<TDataType>(JsonArray, ParsedArray);
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
