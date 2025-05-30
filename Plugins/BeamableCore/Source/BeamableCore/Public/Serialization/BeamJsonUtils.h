#pragma once

#include <type_traits>

#include "BeamSemanticType.h"
#include "BeamTypeTraits.h"
#include "Misc/DefaultValueHelper.h"
#include "Serialization/BeamArray.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamMap.h"
#include "Serialization/BeamOptional.h"

#include "BeamJsonUtils.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamJsonUtils final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	template <typename TDataType, typename TSerializer>
	static void _SerializeUObject(const TDataType ToSerialize, TSerializer Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);

		ToSerialize->BeamSerializeProperties(Serializer);
	}

	template <typename TDataType, typename TSerializer>
	static void _SerializeUStruct(const TDataType ToSerialize, TSerializer Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");
		static_assert(TIsDerivedFrom<TDataType, FBeamJsonSerializableUStruct>::Value);
		ToSerialize.BeamSerializeProperties(Serializer);
	}

	template <typename TOptionalType, typename TDataType, typename TSemanticTypeRepresentation, typename TSerializer>
	static void _SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TSerializer Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

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
				UBeamJsonUtils::SerializeArray<TDataType, TSemanticTypeRepresentation>(Identifier, Array, Serializer);
			}
			else if constexpr (TIsTMap<TOptionalType>::Value)
			{
				static_assert(TIsFirstTemplateParam<FString, TOptionalType>::value, "When TOptionalType is a map, the first template argument must be an FString.");
				static_assert(TIsSecondTemplateParam<TDataType, TOptionalType>::value, "When TOptionalType is a map, the second template argument must be TDataType.");

				const auto Map = FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				UBeamJsonUtils::SerializeMap<TDataType, TSemanticTypeRepresentation>(Identifier, Map, Serializer);
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
			else if constexpr (TIsDerivedFrom<TOptionalType, FBeamJsonSerializableUStruct>::Value)
			{
				const FBeamJsonSerializableUStruct* JsonSerializable = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				Serializer->WriteObjectStart(Identifier);
				JsonSerializable->BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
			else if constexpr (TIsDerivedFrom<TOptionalType, FBeamSemanticType>::Value)
			{
				const FBeamSemanticType* JsonSerializable = &FBeamOptional::GetValue<TOptionalType>(ToSerialize);
				UBeamJsonUtils::_SerializeSemanticType<TSemanticTypeRepresentation, TSerializer>(Identifier, JsonSerializable, Serializer);
			}
			else
			{
				const TDataType* val = &FBeamOptional::GetValue<TDataType>(ToSerialize);
				if constexpr (TIsUEnumClass<TDataType>::Value)
				{
					FString ValStr = EnumToSerializationName<TDataType>(*val);
					Serializer->WriteValue(Identifier, ValStr);
				}
				else if constexpr (std::is_same_v<TDataType, FDateTime>)
				{
					Serializer->WriteValue(Identifier, val->ToIso8601());
				}
				else
				{
					Serializer->WriteValue(Identifier, *val);
				}
			}
		}
	}

	template <typename TDataType, typename TSemanticTypeRepresentation, typename TSerializer>
	static void _SerializeArrayElements(const TArray<TDataType>& Array, TSerializer& Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

		if constexpr (TIsPointer<TDataType>::Value)
		{
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
			for (auto i = 0; i < Array.Num(); i++)
			{
				auto Value = Array[i];
				if (Value)
				{
					Serializer->WriteObjectStart();
					Value->BeamSerializeProperties(Serializer);
					Serializer->WriteObjectEnd();
				}
			}
		}
		else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
		{
			for (const auto& Value : Array)
			{
				const auto SoftObjPath = Value.ToSoftObjectPath().ToString();
				Serializer->WriteValue(SoftObjPath);
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamMap>::Value)
		{
			for (const auto& Value : Array)
			{
				Value.BeamSerializeProperties(Serializer);
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamArray>::Value)
		{
			for (const auto& Value : Array)
			{
				Value.BeamSerializeProperties(Serializer);
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializableUStruct>::Value)
		{
			for (const auto& Value : Array)
			{
				Serializer->WriteObjectStart();
				Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else if constexpr (TIsDerivedFrom<TDataType, FBeamSemanticType>::Value)
		{
			for (const auto& Value : Array)
			{
				UBeamJsonUtils::_SerializeSemanticType<TSemanticTypeRepresentation>(&Value, Serializer);
			}
		}
		else if constexpr (std::is_same_v<TDataType, TSharedPtr<FJsonObject>>)
		{
			for (const auto& Value : Array)
			{
				UBeamJsonUtils::SerializeJsonObject(&Value, Serializer);
			}
		}
		else if constexpr (TIsPointer<TDataType>::Value)
		{
			for (auto i = 0; i < Array.Num(); i++)
			{
				auto Value = Array[i];
				if (Value)
				{
					Serializer->WriteObjectStart();
					Value->BeamSerializeProperties(Serializer);
					Serializer->WriteObjectEnd();
				}
			}
		}
		else
		{
			for (const auto& Value : Array)
			{
				if constexpr (TIsUEnumClass<TDataType>::Value)
				{
					FString ValStr = EnumToSerializationName<TDataType>(Value);
					Serializer->WriteValue(ValStr);
				}
				if constexpr (std::is_same_v<TDataType, FDateTime>)
				{
					Serializer->WriteValue(Value.ToIso8601());
				}
				else
				{
					Serializer->WriteValue(Value);
				}
			}
		}
	}

	template <typename TMapType, typename TDataType, typename TSemanticTypeRepresentation, typename TSerializer>
	static void _SerializeMapElements(const TMap<FString, TMapType>& Map, TSerializer& Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

		// Compile-time branch for array case
		if constexpr (TIsTArray<TMapType>::Value)
		{
			static_assert(!TIsTemplateParam<TDataType, TMapType>::value, "TMapType can NOT be an array! It must be wrapped in a FBeamArrayOf____ Type instead.");
		}
		// Compile-time branch for pointer case
		else if constexpr (TIsPointer<TMapType>::Value)
		{
			static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
			for (const auto& Kvp : Map)
			{
				if (Kvp.Value)
				{
					Serializer->WriteObjectStart(Kvp.Key);
					Kvp.Value->BeamSerializeProperties(Serializer);
					Serializer->WriteObjectEnd();
				}
			}
		}
		// Compile-time branch for Map of Maps
		else if constexpr (TIsDerivedFrom<TMapType, FBeamMap>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteIdentifierPrefix(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
			}
		}
		// Compile-time branch for Map of Arrays
		else if constexpr (TIsDerivedFrom<TMapType, FBeamArray>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteIdentifierPrefix(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
			}
		}
		// Compile-time branch for Map of non-Primitives
		else if constexpr (TIsDerivedFrom<TMapType, FBeamJsonSerializableUStruct>::Value)
		{
			for (const auto& Kvp : Map)
			{
				Serializer->WriteObjectStart(Kvp.Key);
				Kvp.Value.BeamSerializeProperties(Serializer);
				Serializer->WriteObjectEnd();
			}
		}
		else if constexpr (TIsDerivedFrom<TMapType, FBeamSemanticType>::Value)
		{
			for (const auto& Kvp : Map)
			{
				UBeamJsonUtils::_SerializeSemanticType<TSemanticTypeRepresentation, TSerializer>(Kvp.Key, &Kvp.Value, Serializer);
			}
		}
		else if constexpr (std::is_same_v<TMapType, TSharedPtr<FJsonObject>>)
		{
			for (const auto& Kvp : Map)
			{
				UBeamJsonUtils::SerializeJsonObject(Kvp.Key, &Kvp.Value, Serializer);
			}
		}
		else if constexpr (TIsPointer<TMapType>::Value)
		{
			for (const auto& Kvp : Map)
			{
				if (Kvp.Value)
				{
					Serializer->WriteObjectStart(Kvp.Key);
					Kvp.Value->BeamSerializeProperties(Serializer);
					Serializer->WriteObjectEnd();
				}
			}
		}
		else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
		{
			for (const auto& Kvp : Map)
			{
				const auto SoftObjPath = Kvp.Value.ToSoftObjectPath().ToString();
				Serializer->WriteValue(Kvp.Key, SoftObjPath);
			}
		}
		// If it's not any of the types we care about, let's assume it's a FString or supported primitive	
		else
		{
			for (const auto& Kvp : Map)
			{
				if constexpr (TIsUEnumClass<TDataType>::Value)
				{
					FString ValStr = EnumToSerializationName<TDataType>(Kvp.Value);
					Serializer->WriteValue(Kvp.Key, ValStr);
				}
				else if constexpr (std::is_same_v<TMapType, FDateTime>)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value.ToIso8601());
				}
				else
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
			}
		}
	}

	template <typename TSemanticTypeRepresentation, typename TSerializer>
	static void _SerializeSemanticType(const FString& Identifier, const FBeamSemanticType* ToSerialize, TSerializer Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

		const auto& Value = FBeamSemanticType::GetValue<TSemanticTypeRepresentation>(ToSerialize);
		Serializer->WriteValue(Identifier, Value);
	}

	template <typename TSemanticTypeRepresentation, typename TSerializer>
	static void _SerializeSemanticType(const FBeamSemanticType* ToSerialize, TSerializer Serializer)
	{
		static_assert(std::is_same_v<TSerializer, TUnrealPrettyJsonSerializer> || std::is_same_v<TSerializer, TUnrealJsonSerializer>, "Serializer must be one of these!");

		const auto& Value = FBeamSemanticType::GetValue<TSemanticTypeRepresentation>(ToSerialize);
		Serializer->WriteValue(Value);
	}

public:
	template <typename TSemanticTypeRepresentation>
	static void SerializeSemanticType(const FString& Identifier, const FBeamSemanticType* ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		_SerializeSemanticType<TSemanticTypeRepresentation, TUnrealJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TSemanticTypeRepresentation>
	static void SerializeSemanticType(const FString& Identifier, const FBeamSemanticType* ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		_SerializeSemanticType<TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TOptionalType, typename TDataType = TOptionalType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TSemanticTypeRepresentation, TUnrealJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TOptionalType, typename TDataType = TOptionalType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealPrettyJsonSerializer Serializer)
	{
		_SerializeOptional<TOptionalType, TDataType, TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Identifier, ToSerialize, Serializer);
	}

	template <typename TDataType>
	static void SerializeUObject(const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);

		if (ToSerialize)
		{
			Serializer->WriteObjectStart();
			_SerializeUObject<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
			Serializer->WriteObjectEnd();
		}
		else
		{
			Serializer->WriteNull();
		}
	}

	template <typename TDataType>
	static void SerializeUObject(const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);

		if (ToSerialize)
		{
			Serializer->WriteObjectStart();
			_SerializeUObject<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
			Serializer->WriteObjectEnd();
		}
		else
		{
			Serializer->WriteNull();
		}
	}

	template <typename TPrimitiveType, typename TJsonType>
	static void SerializeRawPrimitive(const FString& JsonField, TPrimitiveType& ToSerialize, TSharedRef<TJsonType>& Serializer)
	{
		if (TIsDerivedFrom<TPrimitiveType, FBeamSemanticType>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamSemanticType type. We don't support it for now."))
		}
		else if constexpr (TIsPointer<TPrimitiveType>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a UObject type. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamMap>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamMap. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamArray>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamArray. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamJsonSerializableUStruct>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamJsonSerializable. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FGuid>::Value)
		{
			Serializer->WriteValue(JsonField, ToSerialize.ToString(EGuidFormats::DigitsWithHyphensLower));
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FDateTime>::Value)
		{
			Serializer->WriteValue(JsonField, ToSerialize.ToIso8601());
		}
		else
		{
			Serializer->WriteValue(JsonField, ToSerialize);
		}
	}


	template <typename TDataType>
	static void SerializeUObject(const FString& Identifier, const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);

		if (ToSerialize)
		{
			Serializer->WriteObjectStart(Identifier);
			_SerializeUObject<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
			Serializer->WriteObjectEnd();
		}
		else
		{
			Serializer->WriteNull(Identifier);
		}
	}

	template <typename TDataType>
	static void SerializeUObject(const FString& Identifier, const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);

		if (ToSerialize)
		{
			Serializer->WriteObjectStart(Identifier);
			_SerializeUObject<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
			Serializer->WriteObjectEnd();
		}
		else
		{
			Serializer->WriteNull(Identifier);
		}
	}


	template <typename TDataType>
	static void SerializeUStruct(const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value);

		Serializer->WriteObjectStart();
		_SerializeUStruct<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType>
	static void SerializeUStruct(const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value);

		Serializer->WriteObjectStart();
		_SerializeUStruct<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType>
	static void SerializeUStruct(const FString& Identifier, const TDataType& ToSerialize, TUnrealJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value);

		Serializer->WriteObjectStart(Identifier);
		_SerializeUStruct<TDataType, TUnrealJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType>
	static void SerializeUStruct(const FString& Identifier, const TDataType& ToSerialize, TUnrealPrettyJsonSerializer& Serializer)
	{
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value);

		Serializer->WriteObjectStart(Identifier);
		_SerializeUStruct<TDataType, TUnrealPrettyJsonSerializer>(ToSerialize, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TSemanticTypeRepresentation, TUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}

	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeArray(const TArray<TDataType>& Array, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart();
		_SerializeArrayElements<TDataType, TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}


	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart(Identifier);
		_SerializeArrayElements<TDataType, TSemanticTypeRepresentation, TUnrealJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}

	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteArrayStart(Identifier);
		_SerializeArrayElements<TDataType, TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Array, Serializer);
		Serializer->WriteArrayEnd();
	}


	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeMap(const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart();
		_SerializeMapElements<TMapType, TDataType, TSemanticTypeRepresentation, TUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeMap(const TMap<FString, TMapType>& Map, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart();
		_SerializeMapElements<TMapType, TDataType, TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart(Identifier);
		_SerializeMapElements<TMapType, TDataType, TSemanticTypeRepresentation, TUnrealJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealPrettyJsonSerializer& Serializer)
	{
		Serializer->WriteObjectStart(Identifier);
		_SerializeMapElements<TMapType, TDataType, TSemanticTypeRepresentation, TUnrealPrettyJsonSerializer>(Map, Serializer);
		Serializer->WriteObjectEnd();
	}

	static void SerializeJsonObject(const TSharedPtr<FJsonObject>& Json, TUnrealJsonSerializer Serializer)
	{
		FJsonDataBag Bag;
		Bag.FromJson(Json);
		Serializer->WriteRawJSONValue(Bag.ToJson(false));
	}

	static void SerializeJsonObject(const TSharedPtr<FJsonObject>& Json, TUnrealPrettyJsonSerializer Serializer)
	{
		FJsonDataBag Bag;
		Bag.FromJson(Json);
		Serializer->WriteRawJSONValue(Bag.ToJson(true));
	}

	static void SerializeJsonObject(const FString Identifier, const TSharedPtr<FJsonObject>& Json, TUnrealJsonSerializer Serializer)
	{
		FJsonDataBag Bag;
		Bag.FromJson(Json);
		Serializer->WriteRawJSONValue(Identifier, Bag.ToJson(false));
	}

	static void SerializeJsonObject(const FString Identifier, const TSharedPtr<FJsonObject>& Json, TUnrealPrettyJsonSerializer Serializer)
	{
		FJsonDataBag Bag;
		Bag.FromJson(Json);
		Serializer->WriteRawJSONValue(Identifier, Bag.ToJson(true));
	}

	template <typename TEnum>
	static FString EnumToSerializationName(TEnum Value)
	{
		static_assert(TIsUEnumClass<TEnum>::Value);

		const UEnum* Enum = StaticEnum<TEnum>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetNameStringByIndex(NameIndex);

		// We chop off the first five "BEAM_" characters. 		
		return SerializationName.RightChop(5);
	}

	template <typename TEnum>
	static TEnum SerializationNameToEnum(FString Value)
	{
		static_assert(TIsUEnumClass<TEnum>::Value);

		const UEnum* Enum = StaticEnum<TEnum>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			// We chop off the first five "BEAM_" characters.
			const FString& SerializationName = Enum->GetNameStringByIndex(NameIndex).RightChop(5);
			if (Value == SerializationName)
				return static_cast<TEnum>(Enum->GetValueByIndex(NameIndex));
		}

		ensureAlways(false); //  This should be impossible!
		return TEnum();
	}

	template <typename TEnum>
	static TEnum SerializationIndexToEnum(int Value)
	{
		static_assert(TIsUEnumClass<TEnum>::Value);

		const UEnum* Enum = StaticEnum<TEnum>();

		return static_cast<TEnum>(Enum->GetValueByIndex(Value));
	}

	template <typename TSerializationType>
	static void DeserializeSemanticType(const TSharedPtr<FJsonValue>& JsonField, FBeamSemanticType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		const auto SemanticTypeName = FString(TNameOf<TSerializationType>::GetName());
		if constexpr (TIsPointer<TSerializationType>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a UObject type. We don't support it for now."))
		}
		else if constexpr (std::is_same_v<TSerializationType, FString>)
		{
			const FString Val = JsonField->AsString();
			FBeamSemanticType::Set(&ToDeserialize, &Val, SemanticTypeName);
		}
		else if constexpr (TIsDerivedFrom<TSerializationType, FBeamMap>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamMap. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TSerializationType, FBeamArray>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamArray. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TSerializationType, FBeamJsonSerializableUStruct>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamJsonSerializable. We don't support it for now."))
		}
		else if constexpr (std::is_same_v<TSerializationType, int8>)
		{
			const FString Val = JsonField->AsString();
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int8 Cast = static_cast<int8>(Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Cast, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int16>)
		{
			const FString Val = JsonField->AsString();
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int16 Cast = static_cast<int16>(Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Cast, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int32>)
		{
			const FString Val = JsonField->AsString();
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int64>)
		{
			const FString Val = JsonField->AsString();
			int64 Parsed;
			FDefaultValueHelper::ParseInt64(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, float>)
		{
			const FString Val = JsonField->AsString();
			float Parsed;
			FDefaultValueHelper::ParseFloat(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, double>)
		{
			const FString Val = JsonField->AsString();
			double Parsed;
			FDefaultValueHelper::ParseDouble(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, bool>)
		{
			const FString Val = JsonField->AsString();
			const bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
	}

	template <typename TDataType>
	static void DeserializeUObject(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TDataType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		static_assert(TIsPointer<TDataType>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
		static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead		

		// Instantiates a new UObject
		ToDeserialize = NewObject<typename TRemovePointer<TDataType>::Type>(OuterOwner.GetEvenIfUnreachable());
		// Propagates the same owner object that controls the memory for these --- typically the request object.
		// The request object gets released after the complete callback finishes running.
		ToDeserialize->OuterOwner = OuterOwner;
		if (Identifier.IsEmpty())
			ToDeserialize->BeamDeserializeProperties(OwnerBag);
			// If the OwnerBag has the field, we deserialize it into the object.
			// Most of the time, this affects polymorphic response types as means we won't deserialize it 
		else if (OwnerBag->HasField(Identifier))
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (OwnerBag->TryGetObjectField(Identifier, JsonObject))
				ToDeserialize->BeamDeserializeProperties(*JsonObject);
			else
				ToDeserialize = nullptr;
		}
	}

	template <typename TDataType>
	static void DeserializeUStruct(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TDataType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
		static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value); // Non-UObjects must implement FBeamJsonSerializableUStruct instead
		static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value);

		ToDeserialize = TDataType{};
		ToDeserialize.OuterOwner = OuterOwner;

		if (Identifier.IsEmpty())
			ToDeserialize.BeamDeserializeProperties(OwnerBag);
			// If the OwnerBag has the field, we deserialize it into the object.
			// Most of the time, this affects polymorphic response types as we won't deserialize all of the subtypes, just the specific one
		else if (OwnerBag->HasField(Identifier))
			ToDeserialize.BeamDeserializeProperties(OwnerBag->GetObjectField(Identifier));
	}

	template <typename TDataType>
	static void GetEnumFromJsonField(const TSharedPtr<FJsonValue> JsonField, TDataType& ParsedEnum)
	{
		if (JsonField->Type == EJson::String)
		{
			FString Parsed = JsonField->AsString();
			ParsedEnum = SerializationNameToEnum<TDataType>(Parsed);
		}
		else if (JsonField->Type == EJson::Number)
		{
			int Parsed = JsonField->AsNumber();
			ParsedEnum = SerializationIndexToEnum<TDataType>(Parsed);
		}
		else
		{
			// This is impossible, the enum should be only a number or string
			ensureAlways(false);
		}
	}

	template <typename TOptionalType, typename TDataType = TOptionalType, typename TSemanticTypeRepresentation = TDataType>
	static void DeserializeOptional(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamOptional& ToDeserialize,
	                                TWeakObjectPtr<UObject> OwnerOuter = (UObject*)GetTransientPackage())
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
				for (const auto& KvP : JsonField->AsObject()->Values)
				{
					const auto Key = KvP.Key;
					const auto Item = KvP.Value;
					if constexpr (TIsPointer<TDataType>::Value)
					{
						// Ensure this is a UObject that implements IBeamJsonSerializableUObject
						static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
						static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
						static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead

						TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter.GetEvenIfUnreachable());
						Parsed->OuterOwner = OwnerOuter;
						Parsed->BeamDeserializeProperties(Item->AsObject());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, FString>)
					{
						const FString Val = Item->AsString();
						ParsedMap.Add(Key, Val);
					}
					else if constexpr (std::is_same_v<TDataType, FDateTime>)
					{
						const FString Val = Item->AsString();
						FDateTime Parsed;
						FDateTime::ParseIso8601(*Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamSemanticType>::Value)
					{
						TDataType Parsed;
						DeserializeSemanticType<TSemanticTypeRepresentation>(Item, Parsed);
						ParsedMap.Add(Key, Parsed);
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
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializableUStruct>::Value)
					{
						// Ensure this is not a UObject that implements IBeamJsonSerializableUObject
						static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);

						TDataType Parsed;
						Parsed.BeamDeserializeProperties(Item->AsObject());
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (TIsUEnumClass<TDataType>::Value)
					{
						TDataType ParsedEnum;
						GetEnumFromJsonField<TDataType>(JsonField, ParsedEnum);
						ParsedMap.Add(Key, ParsedEnum);
					}
					else if constexpr (std::is_same_v<TDataType, int8>)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int8>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int16>)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int16>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int32>)
					{
						const FString Val = Item->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, int64>)
					{
						const FString Val = Item->AsString();
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, float>)
					{
						const FString Val = Item->AsString();
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, double>)
					{
						const FString Val = Item->AsString();
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, bool>)
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
				for (const auto& ArrayJsonItem : JsonField->AsArray())
				{
					if constexpr (TIsPointer<TDataType>::Value)
					{
						// Ensure this is a UObject that implements IBeamJsonSerializableUObject
						static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
						static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
						static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead

						TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter.GetEvenIfUnreachable());
						Parsed->OuterOwner = OwnerOuter;
						Parsed->BeamDeserializeProperties(ArrayJsonItem->AsObject());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, FString>)
					{
						const FString Val = ArrayJsonItem->AsString();
						ParsedArray.Add(Val);
					}
					else if constexpr (TIsDerivedFrom<TDataType, FBeamSemanticType>::Value)
					{
						TDataType Parsed;
						DeserializeSemanticType<TSemanticTypeRepresentation>(ArrayJsonItem, Parsed);
						ParsedArray.Add(Parsed);
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
					else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializableUStruct>::Value)
					{
						// Ensure this is not a UObject as UStructs
						static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);

						TDataType Parsed;
						Parsed.BeamDeserializeProperties(ArrayJsonItem->AsObject());
						ParsedArray.Add(Parsed);
					}
					else if constexpr (TIsUEnumClass<TDataType>::Value)
					{
						TDataType ParsedEnum;
						GetEnumFromJsonField<TDataType>(JsonField, ParsedEnum);
						ParsedArray.Add(ParsedEnum);
					}
					else if constexpr (std::is_same_v<TDataType, int8>)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int8>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int16>)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int16>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int32>)
					{
						const FString Val = ArrayJsonItem->AsString();
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, int64>)
					{
						const FString Val = ArrayJsonItem->AsString();
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, float>)
					{
						const FString Val = ArrayJsonItem->AsString();
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, double>)
					{
						const FString Val = ArrayJsonItem->AsString();
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, bool>)
					{
						const FString Val = ArrayJsonItem->AsString();
						bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, FDateTime>)
					{
						const FString Val = ArrayJsonItem->AsString();
						FDateTime Parsed;
						FDateTime::ParseIso8601(*Val, Parsed);
						ParsedArray.Add(Parsed);
					}
				}
				FBeamOptional::Set(&ToDeserialize, &ParsedArray);
			}
			else
			{
				if constexpr (TIsPointer<TOptionalType>::Value)
				{
					// Ensure this is a UObject that implements IBeamJsonSerializableUObject
					static_assert(TIsDerivedFrom<typename TRemovePointer<TOptionalType>::Type, UObject>::Value);
					static_assert(TIsDerivedFrom<typename TRemovePointer<TOptionalType>::Type, IBeamJsonSerializableUObject>::Value);
					static_assert(!TIsDerivedFrom<typename TRemovePointer<TOptionalType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead

					TOptionalType Parsed = NewObject<typename TRemovePointer<TOptionalType>::Type>(OwnerOuter.GetEvenIfUnreachable());
					Parsed->OuterOwner = OwnerOuter;
					Parsed->BeamDeserializeProperties(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, FDateTime>)
				{
					FDateTime dateTime;
					FDateTime::ParseIso8601(*JsonField->AsString(), dateTime);
					FBeamOptional::Set(&ToDeserialize, &dateTime);
				}
				else if constexpr (std::is_same_v<TOptionalType, FString>)
				{
					const FString val = JsonField->AsString();
					FBeamOptional::Set(&ToDeserialize, &val);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamSemanticType>::Value)
				{
					TOptionalType val;
					DeserializeSemanticType<TDataType>(JsonField, val);
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
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamJsonSerializableUStruct>::Value)
				{
					TOptionalType Parsed;
					Parsed.BeamDeserializeProperties(JsonField->AsObject());
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (TIsUEnumClass<TDataType>::Value)
				{
					TDataType ParsedEnum;
					GetEnumFromJsonField<TDataType>(JsonField, ParsedEnum);
					FBeamOptional::Set(&ToDeserialize, &ParsedEnum);
				}
				else if constexpr (std::is_same_v<TDataType, int8>)
				{
					const FString Val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int8 cast = static_cast<int8>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (std::is_same_v<TDataType, int16>)
				{
					const FString Val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int16 cast = static_cast<int16>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (std::is_same_v<TOptionalType, int32>)
				{
					const FString val = JsonField->AsString();
					int32 Parsed;
					FDefaultValueHelper::ParseInt(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, int64>)
				{
					const FString val = JsonField->AsString();
					int64 Parsed;
					FDefaultValueHelper::ParseInt64(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, float>)
				{
					const FString val = JsonField->AsString();
					float Parsed;
					FDefaultValueHelper::ParseFloat(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, double>)
				{
					const FString val = JsonField->AsString();
					double Parsed;
					FDefaultValueHelper::ParseDouble(val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, bool>)
				{
					const FString val = JsonField->AsString();
					bool Parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
			}
		}
	}

	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void DeserializeArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<TDataType>& Array, TWeakObjectPtr<UObject> OwnerOuter = (UObject*)GetTransientPackage())
	{
		for (const TSharedPtr<FJsonValue>& JsonValue : JsonArray)
		{
			if constexpr (std::is_same_v<TDataType, FString>)
			{
				const FString val = JsonValue->AsString();
				Array.Add(val);
			}
			else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
			{
				const FString val = JsonValue->AsString();
				const FSoftObjectPath SoftObjectPath = FSoftObjectPath(val);
				TSoftObjectPtr<TSemanticTypeRepresentation> Parsed(SoftObjectPath);
				Array.Add(Parsed);
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamSemanticType>::Value)
			{
				TDataType val;
				DeserializeSemanticType<TSemanticTypeRepresentation>(JsonValue, val);
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
			else if constexpr (TIsPointer<TDataType>::Value)
			{
				// Ensure this is a UObject that implements IBeamJsonSerializableUObject
				static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, UObject>::Value);
				static_assert(TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, IBeamJsonSerializableUObject>::Value);
				static_assert(!TIsDerivedFrom<typename TRemovePointer<TDataType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead

				if (!JsonValue->IsNull())
				{
					TDataType Parsed = NewObject<typename TRemovePointer<TDataType>::Type>(OwnerOuter.GetEvenIfUnreachable());
					Parsed->OuterOwner = OwnerOuter;
					Parsed->BeamDeserializeProperties(JsonValue->AsObject());
					Array.Add(Parsed);
				}
			}
			else if constexpr (TIsDerivedFrom<TDataType, FBeamJsonSerializableUStruct>::Value)
			{
				TDataType Parsed;
				Parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Array.Add(Parsed);
			}
			else if constexpr (TIsUEnumClass<TDataType>::Value)
			{
				TDataType ParsedEnum;
				GetEnumFromJsonField<TDataType>(JsonValue, ParsedEnum);
				Array.Add(ParsedEnum);
			}
			else if constexpr (std::is_same_v<TDataType, FDateTime>)
			{
				const FString val = JsonValue->AsString();
				FDateTime Parsed;
				FDateTime::ParseIso8601(*val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, int>)
			{
				const FString val = JsonValue->AsString();
				int Parsed;
				FDefaultValueHelper::ParseInt(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, int64>)
			{
				const FString val = JsonValue->AsString();
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, float>)
			{
				const FString val = JsonValue->AsString();
				float Parsed;
				FDefaultValueHelper::ParseFloat(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, double>)
			{
				const FString val = JsonValue->AsString();
				double Parsed;
				FDefaultValueHelper::ParseDouble(val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, bool>)
			{
				const FString val = JsonValue->AsString();
				bool Parsed = val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Array.Add(Parsed);
			}
			else
			{
				// static_assert(false);
			}
		}
	}

	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void DeserializeMap(const TSharedPtr<FJsonObject>& JsonMap, TMap<FString, TMapType>& Map, TWeakObjectPtr<UObject> OwnerOuter = (UObject*)GetTransientPackage())
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

			if constexpr (std::is_same_v<TMapType, FString>)
			{
				const auto Val = Value.Value->AsString();
				Map.Add(Key, Val);
			}
			else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
			{
				const auto ValStr = Value.Value->AsString();
				const auto ValSoftObjPath = FSoftObjectPath(ValStr);
				const auto Val = TSoftObjectPtr<TSemanticTypeRepresentation>(ValSoftObjPath);
				Map.Add(Key, Val);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamSemanticType>::Value)
			{
				TMapType Parsed;
				DeserializeSemanticType<TSemanticTypeRepresentation>(JsonValue, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamMap>::Value)
			{
				TMapType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsObject());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamArray>::Value)
			{
				TMapType Parsed;
				Parsed.BeamDeserializeElements(JsonValue->AsArray());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsPointer<TMapType>::Value)
			{
				// Ensure this is a UObject that implements IBeamJsonSerializableUObject
				static_assert(TIsDerivedFrom<typename TRemovePointer<TMapType>::Type, UObject>::Value);
				static_assert(TIsDerivedFrom<typename TRemovePointer<TMapType>::Type, IBeamJsonSerializableUObject>::Value);
				static_assert(!TIsDerivedFrom<typename TRemovePointer<TMapType>::Type, FBeamJsonSerializableUStruct>::Value); // UObjects must implement IBeamJsonSerializableUObject instead

				if (!JsonValue->IsNull())
				{
					TMapType Parsed = NewObject<typename TRemovePointer<TMapType>::Type>(OwnerOuter.GetEvenIfUnreachable());
					Parsed->OuterOwner = OwnerOuter;
					Parsed->BeamDeserializeProperties(JsonValue->AsObject());
					Map.Add(Key, Parsed);
				}
			}
			else if constexpr (TIsDerivedFrom<TMapType, FBeamJsonSerializableUStruct>::Value)
			{
				TMapType Parsed;
				Parsed.BeamDeserializeProperties(JsonValue->AsObject());
				Map.Add(Key, Parsed);
			}
			else if constexpr (TIsUEnumClass<TMapType>::Value)
			{
				TDataType ParsedEnum;
				GetEnumFromJsonField<TDataType>(JsonValue, ParsedEnum);

				Map.Add(Key, ParsedEnum);
			}
			else if constexpr (std::is_same_v<TMapType, FDateTime>)
			{
				const FString Val = Value.Value->AsString();
				FDateTime Parsed;
				FDateTime::ParseIso8601(*Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, int>)
			{
				const auto Val = Value.Value->AsString();
				int Parsed;
				FDefaultValueHelper::ParseInt(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, int64>)
			{
				const auto Val = Value.Value->AsString();
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, float>)
			{
				const auto Val = Value.Value->AsString();
				float Parsed;
				FDefaultValueHelper::ParseFloat(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, double>)
			{
				const auto Val = Value.Value->AsString();
				double Parsed;
				FDefaultValueHelper::ParseDouble(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, bool>)
			{
				const auto Val = Value.Value->AsString();
				bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Map.Add(Key, Parsed);
			}

			// This is here to help us catch missing compilation cases
			else
			{
				// static_assert(false);
			}
		}
	}

	template <typename TPrimitiveType>
	static void DeserializeRawPrimitive(const FString& JsonField, TPrimitiveType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		if (TIsDerivedFrom<TPrimitiveType, FBeamSemanticType>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamSemanticType type. We don't support it for now."))
		}
		else if constexpr (TIsPointer<TPrimitiveType>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a UObject type. We don't support it for now."))
		}
		else if constexpr (std::is_same_v<TPrimitiveType, FString>)
		{
			if (JsonField.StartsWith("\""))
			{
				// We do this as the primitive content that is returned is a string enclosed with quotes.
				ToDeserialize = JsonField.RightChop(1).LeftChop(1);
			}
			else
			{
				ToDeserialize = JsonField;
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamMap>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamMap. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamArray>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamArray. We don't support it for now."))
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FBeamJsonSerializableUStruct>::Value)
		{
			checkf(false, TEXT("TSerializationType cannot be a FBeamJsonSerializable. We don't support it for now."))
		}
		else if constexpr (TIsUEnumClass<TPrimitiveType>::Value)
		{
			int EnumIndex = 0;
			// Try to get the index if we can't then parse as a string
			if (FDefaultValueHelper::ParseInt(JsonField, EnumIndex))
			{
				ToDeserialize = SerializationIndexToEnum<TPrimitiveType>(EnumIndex);
			}
			else
			{
				ToDeserialize = SerializationNameToEnum<TPrimitiveType>(JsonField);
			}
		}
		else if constexpr (std::is_same_v<TPrimitiveType, FGuid>)
		{
			FGuid::Parse(JsonField, ToDeserialize);
		}
		else if constexpr (std::is_same_v<TPrimitiveType, int8>)
		{
			const FString Val = JsonField;
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int8 Cast = static_cast<int8>(Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, int16>)
		{
			const FString Val = JsonField;
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int16 Cast = static_cast<int16>(Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, int32>)
		{
			const FString Val = JsonField;
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, int64>)
		{
			const FString Val = JsonField;
			int64 Parsed;
			FDefaultValueHelper::ParseInt64(Val, Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, float>)
		{
			const FString Val = JsonField;
			float Parsed;
			FDefaultValueHelper::ParseFloat(Val, Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, double>)
		{
			const FString Val = JsonField;
			double Parsed;
			FDefaultValueHelper::ParseDouble(Val, Parsed);
			ToDeserialize = Parsed;
		}
		else if constexpr (std::is_same_v<TPrimitiveType, bool>)
		{
			const FString Val = JsonField;
			const bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
			ToDeserialize = Parsed;
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FDateTime>::Value)
		{
			FString Val = JsonField;
			if (JsonField.StartsWith("\""))
			{
				// We do this as the primitive content could come enclosed with quotes.
				Val = JsonField.RightChop(1).LeftChop(1);
			}
			FDateTime::ParseIso8601(*Val, ToDeserialize);
		}
	}

	static void DeserializeJsonObject(const FString Identifier, const TSharedPtr<FJsonObject>& Bag, TSharedPtr<FJsonObject>& Settings, TWeakObjectPtr<UObject> OuterOwner)
	{
		Settings = Bag->GetObjectField(Identifier);
	}
};
