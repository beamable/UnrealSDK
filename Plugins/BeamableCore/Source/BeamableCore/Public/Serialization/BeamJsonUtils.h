#pragma once

#include "BeamTypeTraits.h"
#include "Misc/DefaultValueHelper.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamMap.h"
#include "Serialization/BeamOptional.h"

#include "BeamJsonUtils.generated.h"

UCLASS(BlueprintType)
class UBeamJsonUtils final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	template <typename TDataType, typename TSerializer>
	static void _SerializeUObject(const TDataType ToSerialize, TSerializer Serializer)
	{
		static_assert(TIsSame<TSerializer, TUnrealPrettyJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		if constexpr (TIsPointer<TDataType>::Value)
		{			
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
			
			ToSerialize->BeamSerializeProperties(Serializer);			
		}
		else
		{
			static_assert(false);
		}
	}

	template <typename TOptionalType, typename TDataType, typename TSerializer>
	static void _SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TSerializer Serializer)
	{
		static_assert(TIsSame<TSerializer, TUnrealPrettyJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		if (ToSerialize->IsSet)
		{
			if constexpr (TIsPointer<TOptionalType>::Value)
			{
				auto Value = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteObjectStart(Identifier);
				Value->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
			else if constexpr (TIsTArray<TOptionalType>::Value)
			{
				static_assert(TIsTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is an array, TDataType must be the type for that array.");

				const auto Array = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				UBeamJsonUtils::SerializeArray<TDataType>(Identifier, Array, Serializer);
			}
			else if constexpr (TIsTMap<TOptionalType>::Value)
			{
				static_assert(TIsFirstTemplateParam<FString, TOptionalType>::value, "When TOptionalType is a map, the first template argument must be an FString.");
				static_assert(TIsSecondTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is a map, the second template argument must be TDataType.");

				const auto Map = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				UBeamJsonUtils::SerializeMap<TDataType>(Identifier, Map, Serializer);
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
		static_assert(TIsSame<TSerializer, TUnrealPrettyJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		if constexpr (TIsPointer<TDataType>::Value)
		{
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
			for (const auto& Value : Array)
			{
				Serializer->WriteObjectStart();
				Value->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
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
		else if constexpr (TIsPointer<TDataType>::Value)
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteObjectStart();
				Value->BeamSerializeProperties(Serializer);
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
		static_assert(TIsSame<TSerializer, TUnrealPrettyJsonSerializer>::Value || TIsSame<TSerializer, TUnrealJsonSerializer>::Value, "Serializer must be one of these!");

		// Compile-time branch for array case
		if constexpr (TIsTArray<TMapType>::Value)
		{
			static_assert(!TIsTemplateParam<TDataType, TMapType>::value, "TMapType can NOT be an array! It must be wrapped in a FBeamArrayOf____ Type instead.");
		}
		// Compile-time branch for pointer case
		else if constexpr (TIsPointer<TDataType>::Value)
		{
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		// Compile-time branch for Map of Maps
		else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		// Compile-time branch for Map of Arrays
		else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteArrayStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteArrayEnd();
			}
		}
		// Compile-time branch for Map of non-Primitives
		else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else if constexpr (TIsPointer<TDataType>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value->BeamSerializeProperties(Serializer);
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

public
:
	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TUnrealJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealPrettyJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TUnrealPrettyJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TDataType>
	static void SerializeUObject(const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		
		Serializer->WriteObjectStart();
		_SerializeUObject<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType>
	static void SerializeUObject(const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		
		Serializer->WriteObjectStart();
		_SerializeUObject<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}


	template <typename TDataType>
	static void SerializeUObject(const FString& Identifier, const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		
		Serializer->WriteObjectStart(Identifier);
		_SerializeUObject<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType>
	static void SerializeUObject(const FString& Identifier, const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		
		Serializer->WriteObjectStart(Identifier);
		_SerializeUObject<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}
	

	template <typename TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}

	template <typename TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TUnrealPrettyJsonSerializer>(Array, Serializer);
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
	static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart(Identifier);
		_SerializeArrayElements<TDataType, TUnrealPrettyJsonSerializer>(Array, Serializer);
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
	static void SerializeMap(const TMap<FString, TMapType>& Map, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart();
		_SerializeMapElements<TMapType, TDataType, TUnrealPrettyJsonSerializer>(Map, Serializer);
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
	static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart(Identifier);
		_SerializeMapElements<TMapType, TDataType, TUnrealPrettyJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}


	template <typename TDataType>
	static void DeserializeUObject(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TDataType& ToDeserialize, UObject* OuterOwner = (UObject*)GetTransientPackage())
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializable>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);

		// Instantiates a new UObject
		ToDeserialize = NewObject<typename TRemovePointer<TDataType>::Type>(OuterOwner);
		// Propagates the same owner object that controls the memory for these --- typically the request object.
		// The request object gets released after the complete callback finishes running.
		ToDeserialize->OuterOwner = OuterOwner;
		if (Identifier.IsEmpty())
			ToDeserialize->BeamDeserializeProperties(OwnerBag);
		else
			ToDeserialize->BeamDeserializeProperties(OwnerBag->GetObjectField(Identifier));
	}

	template <typename TOptionalType, typename TDataType = TOptionalType>
	static void DeserializeOptional(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamOptional& ToDeserialize, UObject* OwnerOuter = (UObject*)GetTransientPackage())
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
					if constexpr (TIsPointer<TDataType>::Value)
					{
						TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter);
						Parsed->OuterOwner = OwnerOuter;
						Parsed->BeamDeserializeProperties(Item->AsObject());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, FString>::Value)
					{
						const FString Val = Item->AsString();
						ParsedMap.Add(Key, Val);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeElements(Item->AsObject());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeElements(Item->AsArray());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeProperties(Item->AsObject());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, int8>::Value)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int8>(Parsed));
					}
					else if constexpr (TIsSame<TDataType, int16>::Value)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int16>(Parsed));
					}
					else if constexpr (TIsSame<TDataType, int32>::Value)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, int64>::Value)
					{
						const FString Val = Item->AsString();
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, float>::Value)
					{
						const FString Val = Item->AsString();
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, double>::Value)
					{
						const FString Val = Item->AsString();
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsSame<TDataType, bool>::Value)
					{
						const FString Val = Item->AsString();
						bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedMap.Add(Key, Parsed);
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
					if constexpr (TIsPointer<TDataType>::Value)
					{
						TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter);
						Parsed->OuterOwner = OwnerOuter;
						Parsed->BeamDeserializeProperties(ArrayJsonItem->AsObject());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, FString>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						ParsedArray.Add(Val);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeElements(ArrayJsonItem->AsObject());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeElements(ArrayJsonItem->AsArray());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
					{
						TDataType Parsed;
						Parsed.BeamDeserializeProperties(ArrayJsonItem->AsObject());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, int8>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int8>(Parsed));
					}
					else if constexpr (TIsSame<TDataType, int16>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int16>(Parsed));
					}
					else if constexpr (TIsSame<TDataType, int32>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, int64>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, float>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, double>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsSame<TDataType, bool>::Value)
					{
						const FString Val = ArrayJsonItem->AsString();
						bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedArray.Add(Parsed);
					}
				}
				FBeamOptional::Set(&ToDeserialize, &ParsedArray);
			}
			else
			{
				if constexpr (TIsPointer<TDataType>::Value)
				{
					TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter);
					Parsed->OuterOwner = OwnerOuter;
					Parsed->BeamDeserializeProperties(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TOptionalType, FString>::Value)
				{
					const FString val = JsonField->AsString();
					FBeamOptional::Set(&ToDeserialize, &val);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamMap>::Value)
				{
					TOptionalType Parsed;
					Parsed.BeamDeserializeElements(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamArray>::Value)
				{
					TOptionalType Parsed;
					Parsed.BeamDeserializeElements(JsonField->AsArray());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamJsonSerializable>::Value)
				{
					TOptionalType Parsed;
					Parsed.BeamDeserializeProperties(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TDataType, int8>::Value)
				{
					const FString Val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int8 cast = static_cast<int8>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (TIsSame<TDataType, int16>::Value)
				{
					const FString Val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int16 cast = static_cast<int16>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (TIsSame<TOptionalType, int32>::Value)
				{
					const FString val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TOptionalType, int64>::Value)
				{
					const FString val = JsonField->AsString();
					int64 Parsed;
					FDefaultValueHelper::ParseInt64(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TOptionalType, float>::Value)
				{
					const FString val = JsonField->AsString();
					float Parsed;
					FDefaultValueHelper::ParseFloat(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TOptionalType, double>::Value)
				{
					const FString val = JsonField->AsString();
					double Parsed;
					FDefaultValueHelper::ParseDouble(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsSame<TOptionalType, bool>::Value)
				{
					const FString val = JsonField->AsString();
					bool Parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
			}
		}
	}

	template <typename TDataType>
	static void DeserializeArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<TDataType>& Array, UObject* OwnerOuter = (UObject*)GetTransientPackage())
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
				TDataType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsObject());
				Array.Add(Parsed);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
			{
				TDataType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsArray());
				Array.Add(Parsed);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializable>::Value)
			{
				TDataType Parsed;
				Parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Array.Add(Parsed);
			}
			else if constexpr (TIsSame<TDataType, int>::Value)
			{
				const FString val = JsonValue->AsString();
				int Parsed;
				FDefaultValueHelper::ParseInt(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (TIsSame<TDataType, int64>::Value)
			{
				const FString val = JsonValue->AsString();
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (TIsSame<TDataType, float>::Value)
			{
				const FString val = JsonValue->AsString();
				float Parsed;
				FDefaultValueHelper::ParseFloat(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (TIsSame<TDataType, double>::Value)
			{
				const FString val = JsonValue->AsString();
				double Parsed;
				FDefaultValueHelper::ParseDouble(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (TIsSame<TDataType, bool>::Value)
			{
				const FString val = JsonValue->AsString();
				bool Parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Array.Add(Parsed);
			}
			else if constexpr (TIsPointer<TDataType>::Value)
			{
				TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter);
				Parsed->OuterOwner = OwnerOuter;
				Parsed->BeamDeserializeProperties(JsonValue->AsObject());
				Array.Add(Parsed);
			}
			else
			{
				static_assert(false);
			}
		}
	}

	template <typename TMapType, typename TDataType = TMapType>
	static void DeserializeMap(const TSharedPtr<FJsonObject>& JsonMap, TMap<FString, TMapType>& Map, UObject* OwnerOuter = (UObject*)GetTransientPackage())
	{
		if constexpr (TIsTArray<TMapType>::Value)
			static_assert(TIsTemplateParam<TDataType, TMapType>::value, "When TMapType is an array, TDataType must be the type for that array.");

		if constexpr (TIsTMap<TMapType>::Value)
		{
			static_assert(TIsFirstTemplateParam<FString, TMapType>::value, "When TMapType is a map, the map key type must be FString.");
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
				TDataType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsObject());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamArray>::Value)
			{
				TDataType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsArray());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamJsonSerializable>::Value)
			{
				TDataType Parsed;
				Parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsSame<TMapType, int>::Value)
			{
				const auto Val = Value.Value->AsString();
				int Parsed;
				FDefaultValueHelper::ParseInt(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsSame<TMapType, int64>::Value)
			{
				const auto Val = Value.Value->AsString();
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsSame<TMapType, float>::Value)
			{
				const auto Val = Value.Value->AsString();
				float Parsed;
				FDefaultValueHelper::ParseFloat(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsSame<TMapType, double>::Value)
			{
				const auto Val = Value.Value->AsString();
				double Parsed;
				FDefaultValueHelper::ParseDouble(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsSame<TMapType, bool>::Value)
			{
				const auto Val = Value.Value->AsString();
				bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Map.Add(Key, Parsed);
			}

			else if constexpr (TIsPointer<TMapType>::Value)
			{
				TMapType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter);
				Parsed->OuterOwner = OwnerOuter;
				Parsed->BeamDeserializeProperties(JsonValue->AsObject());
				Map.Add(Key, Parsed);
			}

			// This is here to help us catch missing compilation cases
			else
			{
				static_assert(false);
			}
		}
	}
};
