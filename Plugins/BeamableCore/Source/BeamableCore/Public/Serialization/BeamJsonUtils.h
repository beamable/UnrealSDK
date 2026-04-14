#pragma once

#include <type_traits>

#include "BeamCoreSettings.h"
#include "BeamLogging.h"
#include "BeamSemanticType.h"
#include "BeamTypeTraits.h"
#include "GameplayTagContainer.h"
#include "JsonDomBuilder.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
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
				else if constexpr (std::is_same_v<TDataType, FVector>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("X"), val->X);
					Serializer->WriteValue(TEXT("Y"), val->Y);
					Serializer->WriteValue(TEXT("Z"), val->Z);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FIntVector>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("X"), val->X);
					Serializer->WriteValue(TEXT("Y"), val->Y);
					Serializer->WriteValue(TEXT("Z"), val->Z);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FColor>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("R"), val->R);
					Serializer->WriteValue(TEXT("G"), val->G);
					Serializer->WriteValue(TEXT("B"), val->B);
					Serializer->WriteValue(TEXT("A"), val->A);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FLinearColor>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("R"), val->R);
					Serializer->WriteValue(TEXT("G"), val->G);
					Serializer->WriteValue(TEXT("B"), val->B);
					Serializer->WriteValue(TEXT("A"), val->A);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FGameplayTag>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("TagName"), val->GetTagName().ToString());
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FGameplayTagContainer>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteArrayStart(TEXT("GameplayTags"));
					TArray<FGameplayTag> Tags;
					val->GetGameplayTagArray(Tags);
					for (const FGameplayTag& Tag : Tags)
					{
						Serializer->WriteObjectStart();
						Serializer->WriteValue(TEXT("TagName"), Tag.GetTagName().ToString());
						Serializer->WriteObjectEnd();
					}
					Serializer->WriteArrayEnd();
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FSoftObjectPath>)
				{
					Serializer->WriteObjectStart(Identifier);
					Serializer->WriteValue(TEXT("AssetPathName"), val->GetAssetPathString());
					Serializer->WriteValue(TEXT("SubPathString"), val->GetSubPathString());
					Serializer->WriteObjectEnd();
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
				else if constexpr (std::is_same_v<TDataType, FDateTime>)
				{
					Serializer->WriteValue(Value.ToIso8601());
				}
				else if constexpr (std::is_same_v<TDataType, FVector>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("X"), Value.X);
					Serializer->WriteValue(TEXT("Y"), Value.Y);
					Serializer->WriteValue(TEXT("Z"), Value.Z);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FIntVector>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("X"), Value.X);
					Serializer->WriteValue(TEXT("Y"), Value.Y);
					Serializer->WriteValue(TEXT("Z"), Value.Z);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FColor>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("R"), Value.R);
					Serializer->WriteValue(TEXT("G"), Value.G);
					Serializer->WriteValue(TEXT("B"), Value.B);
					Serializer->WriteValue(TEXT("A"), Value.A);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FLinearColor>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("R"), Value.R);
					Serializer->WriteValue(TEXT("G"), Value.G);
					Serializer->WriteValue(TEXT("B"), Value.B);
					Serializer->WriteValue(TEXT("A"), Value.A);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FGameplayTag>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("TagName"), Value.GetTagName().ToString());
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FGameplayTagContainer>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteArrayStart(TEXT("GameplayTags"));
					TArray<FGameplayTag> Tags;
					Value.GetGameplayTagArray(Tags);
					for (const FGameplayTag& Tag : Tags)
					{
						Serializer->WriteObjectStart();
						Serializer->WriteValue(TEXT("TagName"), Tag.GetTagName().ToString());
						Serializer->WriteObjectEnd();
					}
					Serializer->WriteArrayEnd();
					Serializer->WriteObjectEnd();
				}
				else if constexpr (std::is_same_v<TDataType, FSoftObjectPath>)
				{
					Serializer->WriteObjectStart();
					Serializer->WriteValue(TEXT("AssetPathName"), Value.GetAssetPathString());
					Serializer->WriteValue(TEXT("SubPathString"), Value.GetSubPathString());
					Serializer->WriteObjectEnd();
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
				else if constexpr (TIsDerivedFrom<TMapType, FVector>::Value)
				{
					Serializer->WriteObjectStart(Kvp.Key);
					Serializer->WriteValue(TEXT("X"), Kvp.Value.X);
					Serializer->WriteValue(TEXT("Y"), Kvp.Value.Y);
					Serializer->WriteValue(TEXT("Z"), Kvp.Value.Z);
					Serializer->WriteObjectEnd();
				}
				else if constexpr (TIsDerivedFrom<TMapType, FIntVector>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
				else if constexpr (TIsDerivedFrom<TMapType, FColor>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
				else if constexpr (TIsDerivedFrom<TMapType, FLinearColor>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
				else if constexpr (TIsDerivedFrom<TMapType, FGameplayTag>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
				else if constexpr (TIsDerivedFrom<TMapType, FGameplayTagContainer>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value);
				}
				else if constexpr (TIsDerivedFrom<TMapType, FSoftObjectPath>::Value)
				{
					Serializer->WriteValue(Kvp.Key, Kvp.Value.GetAssetPathString());
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
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FVector>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("X"), ToSerialize.X);
			Serializer->WriteValue(TEXT("Y"), ToSerialize.Y);
			Serializer->WriteValue(TEXT("Z"), ToSerialize.Z);
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FIntVector>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("X"), ToSerialize.X);
			Serializer->WriteValue(TEXT("Y"), ToSerialize.Y);
			Serializer->WriteValue(TEXT("Z"), ToSerialize.Z);
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FColor>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("R"), ToSerialize.R);
			Serializer->WriteValue(TEXT("G"), ToSerialize.G);
			Serializer->WriteValue(TEXT("B"), ToSerialize.B);
			Serializer->WriteValue(TEXT("A"), ToSerialize.A);
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FLinearColor>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("R"), ToSerialize.R);
			Serializer->WriteValue(TEXT("G"), ToSerialize.G);
			Serializer->WriteValue(TEXT("B"), ToSerialize.B);
			Serializer->WriteValue(TEXT("A"), ToSerialize.A);
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FGameplayTag>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("TagName"), ToSerialize.GetTagName().ToString());
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FGameplayTagContainer>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteArrayStart(TEXT("GameplayTags"));
			TArray<FGameplayTag> Tags;
			ToSerialize.GetGameplayTagArray(Tags);
			for (const FGameplayTag& Tag : Tags)
			{
				Serializer->WriteObjectStart();
				Serializer->WriteValue(TEXT("TagName"), Tag.GetTagName().ToString());
				Serializer->WriteObjectEnd();
			}
			Serializer->WriteArrayEnd();
			Serializer->WriteObjectEnd();
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FSoftObjectPath>::Value)
		{
			Serializer->WriteObjectStart(JsonField);
			Serializer->WriteValue(TEXT("SubPathString"), ToSerialize.GetSubPathString());
			Serializer->WriteValue(TEXT("AssetPathName"), ToSerialize.GetAssetPathString());
			Serializer->WriteObjectEnd();
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
			FString Val;
			JsonField->TryGetString(Val);
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
			FString Val;
			JsonField->TryGetString(Val);
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int8 Cast = static_cast<int8>(Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Cast, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int16>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			const int16 Cast = static_cast<int16>(Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Cast, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int32>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			int32 Parsed;
			FDefaultValueHelper::ParseInt(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, int64>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			int64 Parsed;
			FDefaultValueHelper::ParseInt64(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, float>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			float Parsed;
			FDefaultValueHelper::ParseFloat(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, double>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			double Parsed;
			FDefaultValueHelper::ParseDouble(Val, Parsed);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
		else if constexpr (std::is_same_v<TSerializationType, bool>)
		{
			FString Val;
			JsonField->TryGetString(Val);
			const bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
			FBeamSemanticType::Set(&ToDeserialize, &Parsed, SemanticTypeName);
		}
	}

	template <typename TSerializationType>
	static void DeserializeSemanticType(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamSemanticType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		if (OwnerBag->HasField(Identifier))
		{
			const TSharedPtr<FJsonValue>& JsonField = OwnerBag->TryGetField(Identifier);

			DeserializeSemanticType<TSerializationType>(JsonField, ToDeserialize, OuterOwner);
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
			FString Val;
			JsonField->TryGetString(Val);
			ParsedEnum = SerializationNameToEnum<TDataType>(Val);
		}
		else if (JsonField->Type == EJson::Number)
		{
			int Parsed;
			JsonField->TryGetNumber(Parsed);
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
						FString Val;
						Item->TryGetString(Val);
						ParsedMap.Add(Key, Val);
					}
					else if constexpr (std::is_same_v<TDataType, FDateTime>)
					{
						FString Val;
						Item->TryGetString(Val);
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
						FString Val;
						Item->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int8>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int16>)
					{
						FString Val;
						Item->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, static_cast<int16>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int32>)
					{
						FString Val;
						Item->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, int64>)
					{
						FString Val;
						Item->TryGetString(Val);
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, float>)
					{
						FString Val;
						Item->TryGetString(Val);
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, double>)
					{
						FString Val;
						Item->TryGetString(Val);
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedMap.Add(Key, Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, bool>)
					{
						FString Val;
						Item->TryGetString(Val);
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
						FString Val;
						ArrayJsonItem->TryGetString(Val);
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
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int8>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int16>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(static_cast<int16>(Parsed));
					}
					else if constexpr (std::is_same_v<TDataType, int32>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						int32 Parsed;
						FDefaultValueHelper::ParseInt(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, int64>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						int64 Parsed;
						FDefaultValueHelper::ParseInt64(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, float>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						float Parsed;
						FDefaultValueHelper::ParseFloat(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, double>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						double Parsed;
						FDefaultValueHelper::ParseDouble(Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, bool>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TDataType, FDateTime>)
					{
						FString Val;
						ArrayJsonItem->TryGetString(Val);
						FDateTime Parsed;
						FDateTime::ParseIso8601(*Val, Parsed);
						ParsedArray.Add(Parsed);
					}
					else if constexpr (std::is_same_v<TOptionalType, FVector>)
					{
						FVector Vector;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
							(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
							(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
						}

						ParsedArray.Add(Vector);
					}
					else if constexpr (std::is_same_v<TDataType, FIntVector>)
					{
						FIntVector Vector;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
							(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
							(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
						}

						ParsedArray.Add(Vector);
					}
					else if constexpr (std::is_same_v<TDataType, FColor>)
					{
						FColor Color;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
							(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
							(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
							(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
						}

						ParsedArray.Add(Color);
					}
					else if constexpr (std::is_same_v<TDataType, FLinearColor>)
					{
						FLinearColor Color;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
							(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
							(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
							(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
						}

						ParsedArray.Add(Color);
					}
					else if constexpr (std::is_same_v<TDataType, FGameplayTag>)
					{
						FGameplayTag Tag;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							FString TagName;
							(*JsonObject)->TryGetStringField(TEXT("TagName"), TagName);
							Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
						}

						ParsedArray.Add(Tag);
					}
					else if constexpr (std::is_same_v<TDataType, FGameplayTagContainer>)
					{
						FGameplayTagContainer Container;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							const TArray<TSharedPtr<FJsonValue>>* TagsArray;
							if ((*JsonObject)->TryGetArrayField(TEXT("GameplayTags"), TagsArray))
							{
								for (const auto& TagValue : *TagsArray)
								{
									const TSharedPtr<FJsonObject>* TagObject;
									if (TagValue->TryGetObject(TagObject))
									{
										FString TagName;
										(*TagObject)->TryGetStringField(TEXT("TagName"), TagName);
										Container.AddTag(FGameplayTag::RequestGameplayTag(FName(*TagName)));
									}
								}
							}
						}

						ParsedArray.Add(Container);
					}
					else if constexpr (std::is_same_v<TDataType, FSoftObjectPath>)
					{
						FSoftObjectPath SoftPath;

						const TSharedPtr<FJsonObject>* JsonObject;
						if (ArrayJsonItem->TryGetObject(JsonObject) && JsonObject->IsValid())
						{
							FString AssetPath, SubPath;
							(*JsonObject)->TryGetStringField(TEXT("AssetPathName"), AssetPath);
							(*JsonObject)->TryGetStringField(TEXT("SubPathString"), SubPath);
							SoftPath.SetPath(AssetPath);
							if (!SubPath.IsEmpty())
							{
								SoftPath = FSoftObjectPath(AssetPath + TEXT(":") + SubPath);
							}
						}

						ParsedArray.Add(SoftPath);
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
					FString Val;
					JsonField->TryGetString(Val);
					FDateTime::ParseIso8601(*Val, dateTime);
					FBeamOptional::Set(&ToDeserialize, &dateTime);
				}
				else if constexpr (std::is_same_v<TOptionalType, FVector>)
				{
					FVector Vector;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
						(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
						(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
					}

					FBeamOptional::Set(&ToDeserialize, &Vector);
				}
				else if constexpr (std::is_same_v<TOptionalType, FIntVector>)
				{
					FIntVector Vector;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
						(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
						(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
					}

					FBeamOptional::Set(&ToDeserialize, &Vector);
				}
				else if constexpr (std::is_same_v<TOptionalType, FColor>)
				{
					FColor Color;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
						(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
						(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
						(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
					}

					FBeamOptional::Set(&ToDeserialize, &Color);
				}
				else if constexpr (std::is_same_v<TOptionalType, FLinearColor>)
				{
					FLinearColor Color;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
						(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
						(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
						(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
					}

					FBeamOptional::Set(&ToDeserialize, &Color);
				}
				else if constexpr (std::is_same_v<TOptionalType, FGameplayTag>)
				{
					FGameplayTag Tag;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						FString TagName;
						(*JsonObject)->TryGetStringField(TEXT("TagName"), TagName);
						Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
					}

					FBeamOptional::Set(&ToDeserialize, &Tag);
				}
				else if constexpr (std::is_same_v<TOptionalType, FGameplayTagContainer>)
				{
					FGameplayTagContainer Container;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						const TArray<TSharedPtr<FJsonValue>>* TagsArray;
						if ((*JsonObject)->TryGetArrayField(TEXT("GameplayTags"), TagsArray))
						{
							for (const auto& TagValue : *TagsArray)
							{
								const TSharedPtr<FJsonObject>* TagObject;
								if (TagValue->TryGetObject(TagObject))
								{
									FString TagName;
									(*TagObject)->TryGetStringField(TEXT("TagName"), TagName);
									Container.AddTag(FGameplayTag::RequestGameplayTag(FName(*TagName)));
								}
							}
						}
					}

					FBeamOptional::Set(&ToDeserialize, &Container);
				}
				else if constexpr (std::is_same_v<TOptionalType, FSoftObjectPath>)
				{
					FSoftObjectPath SoftPath;

					const TSharedPtr<FJsonObject>* JsonObject;
					if (JsonField->TryGetObject(JsonObject) && JsonObject->IsValid())
					{
						FString AssetPath, SubPath;
						(*JsonObject)->TryGetStringField(TEXT("AssetPathName"), AssetPath);
						(*JsonObject)->TryGetStringField(TEXT("SubPathString"), SubPath);
						SoftPath.SetPath(AssetPath);
						if (!SubPath.IsEmpty())
						{
							SoftPath = FSoftObjectPath(AssetPath + TEXT(":") + SubPath);
						}
					}

					FBeamOptional::Set(&ToDeserialize, &SoftPath);
				}
				else if constexpr (std::is_same_v<TOptionalType, FString>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					FBeamOptional::Set(&ToDeserialize, &Val);
				}
				else if constexpr (TIsDerivedFrom<TOptionalType, FBeamSemanticType>::Value)
				{
					TOptionalType val;
					DeserializeSemanticType<TDataType>(Identifier, OwnerBag, val);
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
					FString Val;
					JsonField->TryGetString(Val);
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int8 cast = static_cast<int8>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (std::is_same_v<TDataType, int16>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					int16 cast = static_cast<int16>(Parsed);
					FBeamOptional::Set(&ToDeserialize, &cast);
				}
				else if constexpr (std::is_same_v<TOptionalType, int32>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					int32 Parsed;
					FDefaultValueHelper::ParseInt(Val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, int64>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					int64 Parsed;
					FDefaultValueHelper::ParseInt64(Val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, float>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					float Parsed;
					FDefaultValueHelper::ParseFloat(Val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, double>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					double Parsed;
					FDefaultValueHelper::ParseDouble(Val, Parsed);
					FBeamOptional::Set(&ToDeserialize, &Parsed);
				}
				else if constexpr (std::is_same_v<TOptionalType, bool>)
				{
					FString Val;
					JsonField->TryGetString(Val);
					bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
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
				FString Val;
				JsonValue->TryGetString(Val);
				Array.Add(Val);
			}
			else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				const FSoftObjectPath SoftObjectPath = FSoftObjectPath(Val);
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
				FString Val;
				JsonValue->TryGetString(Val);
				FDateTime Parsed;
				FDateTime::ParseIso8601(*Val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, FVector>)
			{
				FVector Vector;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
					(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
					(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
				}
				Array.Add(Vector);
			}
			else if constexpr (std::is_same_v<TDataType, FIntVector>)
			{
				FIntVector Vector;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
					(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
					(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
				}
				Array.Add(Vector);
			}
			else if constexpr (std::is_same_v<TDataType, FColor>)
			{
				FColor Color;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
					(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
					(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
					(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
				}
				Array.Add(Color);
			}
			else if constexpr (std::is_same_v<TDataType, FLinearColor>)
			{
				FLinearColor Color;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
					(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
					(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
					(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
				}
				Array.Add(Color);
			}
			else if constexpr (std::is_same_v<TDataType, FGameplayTag>)
			{
				FGameplayTag Tag;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					FString TagName;
					(*JsonObject)->TryGetStringField(TEXT("TagName"), TagName);
					Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
				}
				Array.Add(Tag);
			}
			else if constexpr (std::is_same_v<TDataType, FGameplayTagContainer>)
			{
				FGameplayTagContainer Container;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					const TArray<TSharedPtr<FJsonValue>>* TagsArray;
					if ((*JsonObject)->TryGetArrayField(TEXT("GameplayTags"), TagsArray))
					{
						for (const auto& TagValue : *TagsArray)
						{
							const TSharedPtr<FJsonObject>* TagObject;
							if (TagValue->TryGetObject(TagObject))
							{
								FString TagName;
								(*TagObject)->TryGetStringField(TEXT("TagName"), TagName);
								Container.AddTag(FGameplayTag::RequestGameplayTag(FName(*TagName)));
							}
						}
					}
				}
				Array.Add(Container);
			}
			else if constexpr (std::is_same_v<TDataType, FSoftObjectPath>)
			{
				FSoftObjectPath SoftPath;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					FString AssetPath, SubPath;
					(*JsonObject)->TryGetStringField(TEXT("AssetPathName"), AssetPath);
					(*JsonObject)->TryGetStringField(TEXT("SubPathString"), SubPath);
					SoftPath.SetPath(AssetPath);
					if (!SubPath.IsEmpty())
					{
						SoftPath = FSoftObjectPath(AssetPath + TEXT(":") + SubPath);
					}
				}
				Array.Add(SoftPath);
			}
			else if constexpr (std::is_same_v<TDataType, int>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				int Parsed;
				FDefaultValueHelper::ParseInt(Val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, int64>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(Val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, float>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				float Parsed;
				FDefaultValueHelper::ParseFloat(Val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, double>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				double Parsed;
				FDefaultValueHelper::ParseDouble(Val, Parsed);
				Array.Add(Parsed);
			}
			else if constexpr (std::is_same_v<TDataType, bool>)
			{
				FString Val;
				JsonValue->TryGetString(Val);
				bool Parsed = Val.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				Array.Add(Parsed);
			}
			else
			{
				// static_assert(false);
			}
		}
	}

	template <typename TDataType, typename TSemanticTypeRepresentation = TDataType>
	static void DeserializeArray(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TArray<TDataType>& Array, TWeakObjectPtr<UObject> OwnerOuter = (UObject*)GetTransientPackage())
	{
		if (OwnerBag->HasField(Identifier))
		{
			const TArray<TSharedPtr<FJsonValue>>& JsonArray = OwnerBag->GetArrayField(Identifier);

			DeserializeArray(JsonArray, Array, OwnerOuter);
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
				FString Val;
				Value.Value->TryGetString(Val);
				Map.Add(Key, Val);
			}
			else if constexpr (std::is_same_v<TDataType, TSoftObjectPtr<TSemanticTypeRepresentation>>)
			{
				FString ValStr;
				Value.Value->TryGetString(ValStr);
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
				FString Val;
				Value.Value->TryGetString(Val);
				FDateTime Parsed;
				FDateTime::ParseIso8601(*Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, FVector>)
			{
				FVector Vector;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
					(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
					(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
				}

				Map.Add(Key, Vector);
			}
			else if constexpr (std::is_same_v<TMapType, FIntVector>)
			{
				FIntVector Vector;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("X"), Vector.X);
					(*JsonObject)->TryGetNumberField(TEXT("Y"), Vector.Y);
					(*JsonObject)->TryGetNumberField(TEXT("Z"), Vector.Z);
				}

				Map.Add(Key, Vector);
			}
			else if constexpr (std::is_same_v<TMapType, FColor>)
			{
				FColor Color;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					int32 R, G, B, A;
					(*JsonObject)->TryGetNumberField(TEXT("R"), R);
					(*JsonObject)->TryGetNumberField(TEXT("G"), G);
					(*JsonObject)->TryGetNumberField(TEXT("B"), B);
					(*JsonObject)->TryGetNumberField(TEXT("A"), A);
					Color = FColor(R, G, B, A);
				}

				Map.Add(Key, Color);
			}
			else if constexpr (std::is_same_v<TMapType, FLinearColor>)
			{
				FLinearColor Color;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					(*JsonObject)->TryGetNumberField(TEXT("R"), Color.R);
					(*JsonObject)->TryGetNumberField(TEXT("G"), Color.G);
					(*JsonObject)->TryGetNumberField(TEXT("B"), Color.B);
					(*JsonObject)->TryGetNumberField(TEXT("A"), Color.A);
				}

				Map.Add(Key, Color);
			}
			else if constexpr (std::is_same_v<TMapType, FGameplayTag>)
			{
				FGameplayTag Tag;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					FString TagName;
					(*JsonObject)->TryGetStringField(TEXT("TagName"), TagName);
					Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
				}

				Map.Add(Key, Tag);
			}
			else if constexpr (std::is_same_v<TMapType, FGameplayTagContainer>)
			{
				FGameplayTagContainer Container;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					const TArray<TSharedPtr<FJsonValue>>* TagsArray;
					if ((*JsonObject)->TryGetArrayField(TEXT("GameplayTags"), TagsArray))
					{
						for (const auto& TagValue : *TagsArray)
						{
							const TSharedPtr<FJsonObject>* TagObject;
							if (TagValue->TryGetObject(TagObject))
							{
								FString TagName;
								(*TagObject)->TryGetStringField(TEXT("TagName"), TagName);
								Container.AddTag(FGameplayTag::RequestGameplayTag(FName(*TagName)));
							}
						}
					}
				}

				Map.Add(Key, Container);
			}
			else if constexpr (std::is_same_v<TMapType, FSoftObjectPath>)
			{
				FSoftObjectPath SoftPath;

				const TSharedPtr<FJsonObject>* JsonObject;
				if (JsonValue->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					FString AssetPath, SubPath;
					(*JsonObject)->TryGetStringField(TEXT("AssetPathName"), AssetPath);
					(*JsonObject)->TryGetStringField(TEXT("SubPathString"), SubPath);
					SoftPath.SetPath(AssetPath);
					if (!SubPath.IsEmpty())
					{
						SoftPath = FSoftObjectPath(AssetPath + TEXT(":") + SubPath);
					}
				}

				Map.Add(Key, SoftPath);
			}
			else if constexpr (std::is_same_v<TMapType, int>)
			{
				FString Val;
				Value.Value->TryGetString(Val);
				int Parsed;
				FDefaultValueHelper::ParseInt(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, int64>)
			{
				FString Val;
				Value.Value->TryGetString(Val);
				int64 Parsed;
				FDefaultValueHelper::ParseInt64(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, float>)
			{
				FString Val;
				Value.Value->TryGetString(Val);
				float Parsed;
				FDefaultValueHelper::ParseFloat(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, double>)
			{
				FString Val;
				Value.Value->TryGetString(Val);
				double Parsed;
				FDefaultValueHelper::ParseDouble(Val, Parsed);
				Map.Add(Key, Parsed);
			}
			else if constexpr (std::is_same_v<TMapType, bool>)
			{
				FString Val;
				Value.Value->TryGetString(Val);
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

	template <typename TMapType, typename TDataType = TMapType, typename TSemanticTypeRepresentation = TDataType>
	static void DeserializeMap(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TMap<FString, TMapType>& Map, TWeakObjectPtr<UObject> OwnerOuter = (UObject*)GetTransientPackage())
	{
		if (OwnerBag->HasField(Identifier))
		{
			const TSharedPtr<FJsonObject>& JsonMap = OwnerBag->GetObjectField(Identifier);

			DeserializeMap(JsonMap, Map, OwnerOuter);
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
		else if constexpr (TIsTArray<TPrimitiveType>::Value)
		{
			TArray<TSharedPtr<FJsonValue>> JsonArray;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonArray))
			{
				using TElementType = typename TRemoveReference<decltype(DeclVal<TPrimitiveType>()[0])>::Type;
				DeserializeArray<TElementType>(JsonArray, ToDeserialize, OuterOwner);
			}
		}
		else if constexpr (TIsTMap<TPrimitiveType>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				using TValueType = typename TPrimitiveType::ValueType;
				DeserializeMap<TValueType>(JsonObject, ToDeserialize, OuterOwner);
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
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FVector>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				JsonObject->TryGetNumberField(TEXT("X"), ToDeserialize.X);
				JsonObject->TryGetNumberField(TEXT("Y"), ToDeserialize.Y);
				JsonObject->TryGetNumberField(TEXT("Z"), ToDeserialize.Z);
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FIntVector>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				JsonObject->TryGetNumberField(TEXT("X"), ToDeserialize.X);
				JsonObject->TryGetNumberField(TEXT("Y"), ToDeserialize.Y);
				JsonObject->TryGetNumberField(TEXT("Z"), ToDeserialize.Z);
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FColor>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				JsonObject->TryGetNumberField(TEXT("R"), ToDeserialize.R);
				JsonObject->TryGetNumberField(TEXT("G"), ToDeserialize.G);
				JsonObject->TryGetNumberField(TEXT("B"), ToDeserialize.B);
				JsonObject->TryGetNumberField(TEXT("A"), ToDeserialize.A);
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FLinearColor>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				JsonObject->TryGetNumberField(TEXT("R"), ToDeserialize.R);
				JsonObject->TryGetNumberField(TEXT("G"), ToDeserialize.G);
				JsonObject->TryGetNumberField(TEXT("B"), ToDeserialize.B);
				JsonObject->TryGetNumberField(TEXT("A"), ToDeserialize.A);
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FGameplayTag>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			FString TagName;
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				JsonObject->TryGetStringField(TEXT("TagName"), TagName);
				ToDeserialize = FGameplayTag::RequestGameplayTag(*TagName);
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FGameplayTagContainer>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				const TArray<TSharedPtr<FJsonValue>>& TagArray = JsonObject->GetArrayField(TEXT("GameplayTags"));
				ToDeserialize = FGameplayTagContainer();

				for (const TSharedPtr<FJsonValue>& TagValue : TagArray)
				{
					if (TagValue->Type == EJson::Object)
					{
						FString TagName;
						TagValue->AsObject()->TryGetStringField(TEXT("TagName"), TagName);
						FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
						ToDeserialize.AddTag(Tag);
					}
				}
			}
		}
		else if constexpr (TIsDerivedFrom<TPrimitiveType, FSoftObjectPath>::Value)
		{
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonField);
			if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
			{
				FString AssetPath;
				JsonObject->TryGetStringField(TEXT("AssetPathName"), AssetPath);

				ToDeserialize = FSoftObjectPath(AssetPath);
			}
		}
	}

	template <typename TPrimitiveType>
	static void DeserializeRawPrimitive(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, TPrimitiveType& ToDeserialize, TWeakObjectPtr<UObject> OuterOwner = (UObject*)GetTransientPackage())
	{
		if (OwnerBag->HasField(Identifier))
		{
			const FString& JsonField = OwnerBag->GetStringField(Identifier);

			DeserializeRawPrimitive<TPrimitiveType>(JsonField, ToDeserialize, OuterOwner);
		}
	}

	static void DeserializeJsonObject(const FString Identifier, const TSharedPtr<FJsonObject>& Bag, TSharedPtr<FJsonObject>& Settings, TWeakObjectPtr<UObject> OuterOwner)
	{
		if (Bag->HasField(Identifier))
		{
			Settings = Bag->GetObjectField(Identifier);
		}
	}

	static bool FromJsonToBag(const FString& JsonString, FJsonDataBag& OutBag)
	{
		OutBag = FJsonDataBag();

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
		bool Success = false;
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject, FJsonSerializer::EFlags::StoreNumbersAsStrings) &&
			JsonObject.IsValid())
		{
			FJsonSerializerReader Serializer(JsonObject);
			OutBag.Serialize(Serializer, false);
			Success = true;
		}

		return Success;
	}

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
		for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
		{
			const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
			const TInner* Data = reinterpret_cast<const TInner*>(MapHelper.GetValuePtr(i));

			JsonMap.Set(Key, *Data);
		}
	}

	static void ParseMapProperty(const FString& PropName, const TSharedPtr<FJsonObject>& JsonMap, const FMapProperty* MapProperty, void* MapOwner, UObject* CallingContext)
	{
		if (const auto StrKeyProperty = CastField<FStrProperty>(MapProperty->KeyProp))
		{
			const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(MapOwner));
			FScriptMapHelper MapHelper(MapProperty, Val);
			MapHelper.EmptyValues();

			if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto Key = Value.Key;

					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Key;

					FSoftObjectPtr* ValData = reinterpret_cast<FSoftObjectPtr*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					*ValData = FSoftObjectPtr(FSoftObjectPath(JsonStr));
				}
			}
			else if (const auto InnerStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
			{
				const auto InnerMapStruct = InnerStructProperty->Struct;
				if (InnerMapStruct->IsChildOf(FBeamMap::StaticStruct()))
				{
					const FMapProperty* InnerMapProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
					{
						InnerMapProperty = CastField<FMapProperty>(*OptIt);
						if (InnerMapProperty) break;
					}

					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto SubMap = Value.Value->AsObject();
						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						ParseMapProperty(Key, SubMap, InnerMapProperty, MapHelper.GetValuePtr(LastEntryIdx), CallingContext);
					}
				}
				else if (InnerMapStruct->IsChildOf(FBeamArray::StaticStruct()))
				{
					const FArrayProperty* InnerArrayProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
					{
						InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
						if (InnerArrayProperty) break;
					}

					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto SubMap = Value.Value->AsArray();
						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						ParseArrayProperty(Key, SubMap, InnerArrayProperty, MapHelper.GetValuePtr(LastEntryIdx), CallingContext);
					}
				}
				else if (InnerMapStruct && InnerMapStruct == TBaseStructure<FVector>::Get())
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FVector* ValData = reinterpret_cast<FVector*>(MapHelper.GetValuePtr(LastEntryIdx));
						const auto JsonStr = Value.Value->AsObject();
						ValData->X = JsonStr->GetNumberField(TEXT("x"));
						ValData->Y = JsonStr->GetNumberField(TEXT("y"));
						ValData->Z = JsonStr->GetNumberField(TEXT("z"));
					}
				}
				else if (InnerMapStruct && InnerMapStruct == TBaseStructure<FIntVector>::Get())
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FIntVector* ValData = reinterpret_cast<FIntVector*>(MapHelper.GetValuePtr(LastEntryIdx));
						const auto JsonStr = Value.Value->AsObject();
						ValData->X = JsonStr->GetNumberField(TEXT("x"));
						ValData->Y = JsonStr->GetNumberField(TEXT("y"));
						ValData->Z = JsonStr->GetNumberField(TEXT("z"));
					}
				}
				else if (InnerMapStruct && InnerMapStruct == TBaseStructure<FColor>::Get())
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FColor* ValData = reinterpret_cast<FColor*>(MapHelper.GetValuePtr(LastEntryIdx));
						const auto JsonStr = Value.Value->AsObject();
						ValData->A = JsonStr->GetNumberField(TEXT("a"));
						ValData->B = JsonStr->GetNumberField(TEXT("b"));
						ValData->G = JsonStr->GetNumberField(TEXT("g"));
						ValData->R = JsonStr->GetNumberField(TEXT("r"));
					}
				}
				else if (InnerMapStruct && InnerMapStruct == TBaseStructure<FColor>::Get())
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FColor* ValData = reinterpret_cast<FColor*>(MapHelper.GetValuePtr(LastEntryIdx));
						const auto JsonStr = Value.Value->AsObject();
						ValData->A = JsonStr->GetNumberField(TEXT("a"));
						ValData->B = JsonStr->GetNumberField(TEXT("b"));
						ValData->G = JsonStr->GetNumberField(TEXT("g"));
						ValData->R = JsonStr->GetNumberField(TEXT("r"));
					}
				}
				else if (InnerMapStruct && InnerMapStruct == TBaseStructure<FLinearColor>::Get())
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FLinearColor* ValData = reinterpret_cast<FLinearColor*>(MapHelper.GetValuePtr(LastEntryIdx));
						const auto JsonStr = Value.Value->AsObject();
						ValData->A = JsonStr->GetNumberField(TEXT("a"));
						ValData->B = JsonStr->GetNumberField(TEXT("b"));
						ValData->G = JsonStr->GetNumberField(TEXT("g"));
						ValData->R = JsonStr->GetNumberField(TEXT("r"));
					}
				}
				else if (InnerMapStruct->IsChildOf(FGameplayTag::StaticStruct()))
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FGameplayTag* ValData = reinterpret_cast<FGameplayTag*>(MapHelper.GetValuePtr(LastEntryIdx));
						FString JsonStr;
						Value.Value->TryGetString(JsonStr);
						const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
						*ValData = FGameplayTag::RequestGameplayTag(FName(JsonStr), !JsonStr.Equals(TEXT("None")) && bShouldError);
					}
				}
				else if (InnerMapStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FGameplayTagContainer* ValData = reinterpret_cast<FGameplayTagContainer*>(MapHelper.GetValuePtr(LastEntryIdx));
						FString JsonStr;
						Value.Value->TryGetString(JsonStr);

						ValData->FromExportString(JsonStr);
					}
				}
				else if (InnerMapStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = Value.Key;

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FBeamSemanticType* ValData = reinterpret_cast<FBeamSemanticType*>(MapHelper.GetValuePtr(LastEntryIdx));
						FString JsonStr;
						Value.Value->TryGetString(JsonStr);
						ValData->Set(&JsonStr, ValData->GetSerializationRepresentationName(0));
					}
				}
				else if (InnerMapStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto Key = FString(Value.Key);

						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Key;

						FBeamJsonSerializableUStruct* ValData = reinterpret_cast<FBeamJsonSerializableUStruct*>(MapHelper.GetValuePtr(LastEntryIdx));
						ValData->OuterOwner = CallingContext;
						ValData->BeamDeserializeProperties(Value.Value->AsObject());
					}
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
				}
			}
			else if (CastField<FClassProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<UClass**>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					*ValData = FSoftClassPath{JsonStr}.ResolveClass();
				}
			}
			else if (const auto InnerObjectProp = CastField<FObjectProperty>(MapProperty->ValueProp))
			{
				if (InnerObjectProp->PropertyClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
				{
					for (const auto& Value : JsonMap->Values)
					{
						const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

						auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
						*KeyData = Value.Key;

						UObject*& ValData = *reinterpret_cast<UObject**>(MapHelper.GetValuePtr(LastEntryIdx));
						ValData = NewObject<UObject>(CallingContext, InnerObjectProp->PropertyClass);
						if (IBeamJsonSerializableUObject* Data = Cast<IBeamJsonSerializableUObject>(ValData))
						{
							Data->OuterOwner = CallingContext;
							Data->BeamDeserializeProperties(Value.Value->AsObject());
						}
					}
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
					       *InnerObjectProp->PropertyClass->GetName())
				}
			}
			else if (CastField<FTextProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<FText*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					auto SerializedVal = JsonStr;
					if (SerializedVal.StartsWith(TEXT("BEAM_ST₢")))
					{
						SerializedVal.RightChopInline(SerializedVal.Find(TEXT("₢")) + 1);

						const auto SeparatorIdx = SerializedVal.Find(TEXT("₢"));
						FString TableId = SerializedVal.Left(SeparatorIdx);
						FString Key = SerializedVal.RightChop(SeparatorIdx + 1);
						FString KeyStr(Key);
						FName TableIdStr(TableId);
						*ValData = FText::FromStringTable(TableIdStr, KeyStr);
					}
					else
					{
						*ValData = FText::FromString(JsonStr);
					}
				}
			}
			else if (CastField<FNameProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<FName*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					*ValData = FName(JsonStr);
				}
			}
			else if (CastField<FStrProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<FString*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					*ValData = JsonStr;
				}
			}
			else if (CastField<FBoolProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<bool*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					*ValData = JsonStr.Equals(TEXT("true"), ESearchCase::IgnoreCase);
				}
			}
			else if (CastField<FFloatProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<float*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					FDefaultValueHelper::ParseFloat(JsonStr, *ValData);
				}
			}
			else if (CastField<FDoubleProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<double*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					FDefaultValueHelper::ParseDouble(JsonStr, *ValData);
				}
			}
			else if (CastField<FIntProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<int32*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					FDefaultValueHelper::ParseInt(JsonStr, *ValData);
				}
			}
			else if (CastField<FInt64Property>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<int64*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					FDefaultValueHelper::ParseInt64(JsonStr, *ValData);
				}
			}
			else if (CastField<FByteProperty>(MapProperty->ValueProp))
			{
				for (const auto& Value : JsonMap->Values)
				{
					const auto LastEntryIdx = MapHelper.AddDefaultValue_Invalid_NeedsRehash();

					auto KeyData = reinterpret_cast<FString*>(MapHelper.GetKeyPtr(LastEntryIdx));
					*KeyData = Value.Key;

					auto ValData = reinterpret_cast<uint8*>(MapHelper.GetValuePtr(LastEntryIdx));
					FString JsonStr;
					Value.Value->TryGetString(JsonStr);
					int32 Parsed;
					FDefaultValueHelper::ParseInt(JsonStr, Parsed);
					*ValData = static_cast<int8>(Parsed);
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *MapProperty->ValueProp->GetName())
			}

			// Must be called to have a valid map according to UE doc.
			MapHelper.Rehash();
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Content Serialization does not support maps with non-FString keys.\n"))
		}
	}

	static void ParseArrayProperty(const FString& PropName, const TArray<TSharedPtr<FJsonValue>>& JsonArray, const FArrayProperty* ArrayProperty, const void* ArrayOwner, UObject* CallingContext)
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));

		// Make a helper and resize the array to the proper size.
		FScriptArrayHelper ArrayHelper(ArrayProperty, Val);
		ArrayHelper.Resize(JsonArray.Num());

		if ([[maybe_unused]] const auto SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<FSoftObjectPtr*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				*ValData = FSoftObjectPath(JsonStr);
			}
		}
		else if (const auto InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			const auto InnerArrayStruct = InnerStructProperty->Struct;
			if (InnerArrayStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const FMapProperty* InnerMapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
				{
					InnerMapProperty = CastField<FMapProperty>(*OptIt);
					if (InnerMapProperty) break;
				}

				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					const auto SubMap = JsonArray[i]->AsObject();
					ParseMapProperty(PropName, SubMap, InnerMapProperty, ArrayHelper.GetRawPtr(i), CallingContext);
				}
			}
			else if (InnerArrayStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const FArrayProperty* InnerArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
				{
					InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (InnerArrayProperty) break;
				}

				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					const auto SubArray = JsonArray[i]->AsArray();
					ParseArrayProperty(PropName, SubArray, InnerArrayProperty, ArrayHelper.GetRawPtr(i), CallingContext);
				}
			}
			else if (InnerArrayStruct && InnerArrayStruct == TBaseStructure<FVector>::Get())
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FVector* ValData = reinterpret_cast<FVector*>(ArrayHelper.GetRawPtr(i));
					const auto JsonStr = JsonArray[i]->AsObject();
					ValData->X = JsonStr->GetNumberField(TEXT("x"));
					ValData->Y = JsonStr->GetNumberField(TEXT("y"));
					ValData->Z = JsonStr->GetNumberField(TEXT("z"));
				}
			}
			else if (InnerArrayStruct && InnerArrayStruct == TBaseStructure<FIntVector>::Get())
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FIntVector* ValData = reinterpret_cast<FIntVector*>(ArrayHelper.GetRawPtr(i));
					const auto JsonStr = JsonArray[i]->AsObject();
					ValData->X = JsonStr->GetNumberField(TEXT("x"));
					ValData->Y = JsonStr->GetNumberField(TEXT("y"));
					ValData->Z = JsonStr->GetNumberField(TEXT("z"));
				}
			}
			else if (InnerArrayStruct && InnerArrayStruct == TBaseStructure<FColor>::Get())
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FColor* ValData = reinterpret_cast<FColor*>(ArrayHelper.GetRawPtr(i));
					const auto JsonStr = JsonArray[i]->AsObject();
					ValData->A = JsonStr->GetNumberField(TEXT("a"));
					ValData->B = JsonStr->GetNumberField(TEXT("b"));
					ValData->G = JsonStr->GetNumberField(TEXT("g"));
					ValData->R = JsonStr->GetNumberField(TEXT("r"));
				}
			}
			else if (InnerArrayStruct && InnerArrayStruct == TBaseStructure<FLinearColor>::Get())
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FLinearColor* ValData = reinterpret_cast<FLinearColor*>(ArrayHelper.GetRawPtr(i));
					const auto JsonStr = JsonArray[i]->AsObject();
					ValData->A = JsonStr->GetNumberField(TEXT("a"));
					ValData->B = JsonStr->GetNumberField(TEXT("b"));
					ValData->G = JsonStr->GetNumberField(TEXT("g"));
					ValData->R = JsonStr->GetNumberField(TEXT("r"));
				}
			}
			else if (InnerArrayStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FGameplayTag* ValData = reinterpret_cast<FGameplayTag*>(ArrayHelper.GetRawPtr(i));
					FString JsonStr;
					JsonArray[i]->TryGetString(JsonStr);
					const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
					*ValData = FGameplayTag::RequestGameplayTag(FName(JsonStr), !JsonStr.Equals(TEXT("None")) && bShouldError);
				}
			}
			else if (InnerArrayStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FGameplayTagContainer* ValData = reinterpret_cast<FGameplayTagContainer*>(ArrayHelper.GetRawPtr(i));
					FString JsonStr;
					JsonArray[i]->TryGetString(JsonStr);
					ValData->FromExportString(JsonStr);
				}
			}
			else if (InnerArrayStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FBeamSemanticType* ValData = reinterpret_cast<FBeamSemanticType*>(ArrayHelper.GetRawPtr(i));
					FString JsonStr;
					JsonArray[i]->TryGetString(JsonStr);

					ValData->Set(&JsonStr, ValData->GetSerializationRepresentationName(0));
				}
			}
			else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					FBeamJsonSerializableUStruct* ValData = reinterpret_cast<FBeamJsonSerializableUStruct*>(ArrayHelper.GetRawPtr(i));
					ValData->OuterOwner = CallingContext;
					ValData->BeamDeserializeProperties(JsonArray[i]->AsObject());
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
			}
		}
		else if (CastField<FClassProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<UClass**>(ArrayHelper.GetRawPtr(i));
				FString SerializedVal;
				JsonArray[i]->TryGetString(SerializedVal);
				*ValData = FSoftClassPath{SerializedVal}.ResolveClass();
			}
		}

		else if (const auto InnerObjectProp = CastField<FObjectProperty>(ArrayProperty->Inner))
		{
			if (InnerObjectProp->PropertyClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
			{
				for (int i = 0; i < JsonArray.Num(); ++i)
				{
					UObject*& ValData = *reinterpret_cast<UObject**>(ArrayHelper.GetRawPtr(i));
					ValData = NewObject<UObject>(CallingContext, InnerObjectProp->PropertyClass);
					if (IBeamJsonSerializableUObject* Data = Cast<IBeamJsonSerializableUObject>(ValData))
					{
						Data->OuterOwner = CallingContext;
						Data->BeamDeserializeProperties(JsonArray[i]->AsObject());
					}
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
				       *InnerObjectProp->PropertyClass->GetName())
			}
		}
		else if (CastField<FTextProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<FText*>(ArrayHelper.GetRawPtr(i));

				FString SerializedVal;
				JsonArray[i]->TryGetString(SerializedVal);

				if (SerializedVal.StartsWith(TEXT("BEAM_ST₢")))
				{
					SerializedVal.RightChopInline(SerializedVal.Find(TEXT("₢")) + 1);

					const auto SeparatorIdx = SerializedVal.Find(TEXT("₢"));
					FString TableId = SerializedVal.Left(SeparatorIdx);
					FString Key = SerializedVal.RightChop(SeparatorIdx + 1);
					FString KeyStr(Key);
					FName TableIdStr(TableId);
					*ValData = FText::FromStringTable(TableIdStr, KeyStr);
				}
				else
				{
					*ValData = FText::FromString(SerializedVal);
				}
			}
		}
		else if (CastField<FNameProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<FName*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				*ValData = FName(JsonStr);
			}
		}
		else if (CastField<FStrProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<FString*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				*ValData = JsonStr;
			}
		}
		else if (CastField<FBoolProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<bool*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				*ValData = JsonStr.Equals(TEXT("true"), ESearchCase::IgnoreCase);
			}
		}
		else if (CastField<FFloatProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<float*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				FDefaultValueHelper::ParseFloat(JsonStr, *ValData);
			}
		}
		else if (CastField<FDoubleProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<double*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				FDefaultValueHelper::ParseDouble(JsonStr, *ValData);
			}
		}
		else if (CastField<FIntProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<int32*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				FDefaultValueHelper::ParseInt(JsonStr, *ValData);
			}
		}
		else if (CastField<FInt64Property>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<int64*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);
				FDefaultValueHelper::ParseInt64(JsonStr, *ValData);
			}
		}
		else if (CastField<FByteProperty>(ArrayProperty->Inner))
		{
			for (int i = 0; i < JsonArray.Num(); ++i)
			{
				const auto ValData = reinterpret_cast<uint8*>(ArrayHelper.GetRawPtr(i));
				FString JsonStr;
				JsonArray[i]->TryGetString(JsonStr);

				int32 Parsed;
				FDefaultValueHelper::ParseInt(JsonStr, Parsed);
				*ValData = static_cast<int8>(Parsed);
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *ArrayProperty->Inner->GetName())
		}
	}

	static void SerializeArrayProperty(FString PropName, FJsonDomBuilder::FArray& JsonArray, const FArrayProperty* const ArrayProperty, const void* ArrayOwner, UObject* CallingContext)
	{
		if (CastField<FSoftObjectProperty>(ArrayProperty->Inner))
		{
			const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
			FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

			const auto ArrayNum = ArrayHelper.Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				if (ArrayHelper.IsValidIndex(i))
				{
					const FSoftObjectPtr* Data = reinterpret_cast<const FSoftObjectPtr*>(ArrayHelper.GetRawPtr(i));
					JsonArray.Add(Data->ToSoftObjectPath().ToString());
				}
			}
		}
		else if (const auto InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			const auto InnerArrayStruct = InnerStructProperty->Struct;

			const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
			FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

			if (InnerArrayStruct->IsChildOf(FBeamMap::StaticStruct()))
			{
				const FMapProperty* InnerMapProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
				{
					InnerMapProperty = CastField<FMapProperty>(*OptIt);
					if (InnerMapProperty) break;
				}

				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FBeamMap* Data = reinterpret_cast<const FBeamMap*>(ArrayHelper.GetRawPtr(i));

						FJsonDomBuilder::FObject SubMap = FJsonDomBuilder::FObject{};
						SerializeMapProperty(PropName, SubMap, InnerMapProperty, Data, CallingContext);
						JsonArray.Add(SubMap);
					}
				}
			}
			else if (InnerArrayStruct->IsChildOf(FBeamArray::StaticStruct()))
			{
				const FArrayProperty* InnerArrayProperty = nullptr;
				for (TFieldIterator<FProperty> OptIt(InnerArrayStruct); OptIt; ++OptIt)
				{
					InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
					if (InnerArrayProperty) break;
				}

				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FBeamArray* Data = reinterpret_cast<const FBeamArray*>(ArrayHelper.GetRawPtr(i));

						FJsonDomBuilder::FArray SubArray;
						SerializeArrayProperty(PropName, SubArray, InnerArrayProperty, Data, CallingContext);
						JsonArray.Add(SubArray);
					}
				}
			}
			else if (InnerArrayStruct == TBaseStructure<FVector>::Get())
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FVector* Data = reinterpret_cast<const FVector*>(ArrayHelper.GetRawPtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("x"), Data->X);
						Bag.Set(TEXT("y"), Data->Y);
						Bag.Set(TEXT("z"), Data->Z);

						JsonArray.Add(Bag.AsJsonObject());
					}
				}
			}
			else if (InnerArrayStruct == TBaseStructure<FIntVector>::Get())
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FIntVector* Data = reinterpret_cast<const FIntVector*>(ArrayHelper.GetRawPtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("x"), Data->X);
						Bag.Set(TEXT("y"), Data->Y);
						Bag.Set(TEXT("z"), Data->Z);

						JsonArray.Add(Bag.AsJsonObject());
					}
				}
			}
			else if (InnerArrayStruct == TBaseStructure<FColor>::Get())
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FColor* Data = reinterpret_cast<const FColor*>(ArrayHelper.GetRawPtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("a"), Data->A);
						Bag.Set(TEXT("b"), Data->B);
						Bag.Set(TEXT("g"), Data->G);
						Bag.Set(TEXT("r"), Data->R);

						JsonArray.Add(Bag.AsJsonObject());
					}
				}
			}
			else if (InnerArrayStruct == TBaseStructure<FLinearColor>::Get())
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FLinearColor* Data = reinterpret_cast<const FLinearColor*>(ArrayHelper.GetRawPtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("a"), Data->A);
						Bag.Set(TEXT("b"), Data->B);
						Bag.Set(TEXT("g"), Data->G);
						Bag.Set(TEXT("r"), Data->R);

						JsonArray.Add(Bag.AsJsonObject());
					}
				}
			}
			else if (InnerArrayStruct->IsChildOf(FGameplayTag::StaticStruct()))
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FGameplayTag* Data = reinterpret_cast<const FGameplayTag*>(ArrayHelper.GetRawPtr(i));
						const FString UnderlyingString = Data->ToString();
						JsonArray.Add(UnderlyingString);
					}
				}
			}
			else if (InnerArrayStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FGameplayTagContainer* Data = reinterpret_cast<const FGameplayTagContainer*>(ArrayHelper.GetRawPtr(i));
						const FString UnderlyingString = Data->ToString();
						JsonArray.Add(UnderlyingString);
					}
				}
			}
			// else if (InnerArrayStruct->IsChildOf(FBeamContentLink::StaticStruct()))
			// {
			// 	const auto ArrayNum = ArrayHelper.Num();
			// 	for (auto i = 0; i < ArrayNum; i++)
			// 	{
			// 		if (ArrayHelper.IsValidIndex(i))
			// 		{
			// 			const FBeamContentLink* Data = reinterpret_cast<const FBeamContentLink*>(ArrayHelper.GetRawPtr(i));
			// 			const FString* UnderlyingString = static_cast<const FString*>(Data->GetAddr(0));
			// 			JsonArray.Add(*UnderlyingString);
			// 		}
			// 	}
			// }
			else if (InnerArrayStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FBeamSemanticType* Data = reinterpret_cast<const FBeamSemanticType*>(ArrayHelper.GetRawPtr(i));
						const FString* UnderlyingString = static_cast<const FString*>(Data->GetAddr(0));
						JsonArray.Add(*UnderlyingString);
					}
				}
			}
			else if (InnerArrayStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
			{
				const auto ArrayNum = ArrayHelper.Num();
				for (auto i = 0; i < ArrayNum; i++)
				{
					if (ArrayHelper.IsValidIndex(i))
					{
						const FBeamJsonSerializableUStruct* Data = reinterpret_cast<const FBeamJsonSerializableUStruct*>(ArrayHelper.GetRawPtr(i));

						FString JsonBody;
						TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
						Data->BeamSerialize(Serializer);
						Serializer->Close();

						FJsonDataBag Bag;
						UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

						FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
						JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

						JsonArray.Add(JsonObject);
					}
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
			}
		}
		else if (CastField<FClassProperty>(ArrayProperty->Inner))
		{
			const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
			const auto ArrayNum = Val->Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				UClass** Data = (UClass**)(Val->GetData());
				JsonArray.Add(FSoftClassPath{*(Data + i)}.ToString());
			}
		}
		else if (const auto InnerObjectProp = CastField<FObjectProperty>(ArrayProperty->Inner))
		{
			if (InnerObjectProp->PropertyClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
			{
				const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
				FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

				const int32 ArraySize = ArrayHelper.Num();
				for (int32 Index = 0; Index < ArraySize; ++Index)
				{
					if (UObject* InstancedObject = *reinterpret_cast<UObject**>(ArrayHelper.GetRawPtr(Index)))
					{
						if (IBeamJsonSerializableUObject* Data = Cast<IBeamJsonSerializableUObject>(InstancedObject))
						{
							FString JsonBody;
							TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
							Data->BeamSerialize(Serializer);
							Serializer->Close();

							FJsonDataBag Bag;
							UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

							FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
							JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

							JsonArray.Add(JsonObject);
						}
					}
				}
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
				       *InnerObjectProp->PropertyClass->GetName())
			}
		}
		else if (CastField<FTextProperty>(ArrayProperty->Inner))
		{
			const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
			const auto ArrayNum = Val->Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				const FText* Data = static_cast<const FText*>(Val->GetData());
				FString ToSerialize;
				if (Data->IsFromStringTable())
				{
					FName TableId;
					FString Key;
					FTextInspector::GetTableIdAndKey(*(Data + i), TableId, Key);
					ToSerialize = TEXT("BEAM_ST₢") + TableId.ToString() + TEXT("₢") + Key;
				}
				else
				{
					ToSerialize = (Data + i)->ToString();
				}
				JsonArray.Add(ToSerialize);
			}
		}
		else if (CastField<FNameProperty>(ArrayProperty->Inner))
		{
			const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(ArrayOwner));
			const auto ArrayNum = Val->Num();
			for (auto i = 0; i < ArrayNum; i++)
			{
				const FName* Data = static_cast<const FName*>(Val->GetData());
				const FString DataStr = (Data + i)->ToString();
				JsonArray.Add(DataStr);
			}
		}
		else if (CastField<FStrProperty>(ArrayProperty->Inner))
		{
			BuildArray<FString>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FBoolProperty>(ArrayProperty->Inner))
		{
			BuildArray<bool>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FFloatProperty>(ArrayProperty->Inner))
		{
			BuildArray<float>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FDoubleProperty>(ArrayProperty->Inner))
		{
			BuildArray<double>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FIntProperty>(ArrayProperty->Inner))
		{
			BuildArray<int32>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FInt64Property>(ArrayProperty->Inner))
		{
			BuildArray<int64>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FByteProperty>(ArrayProperty->Inner))
		{
			BuildArray<uint8>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else if (CastField<FEnumProperty>(ArrayProperty->Inner))
		{
			BuildArray<FString>(JsonArray, ArrayProperty, ArrayOwner);
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *ArrayProperty->Inner->GetName())
		}
	}

	static void SerializeMapProperty(FString PropName, FJsonDomBuilder::FObject& JsonMap, const FMapProperty* const MapProperty, const void* MapOwner, UObject* CallingContext)
	{
		if (const auto StrKeyProperty = CastField<FStrProperty>(MapProperty->KeyProp))
		{
			const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(MapOwner));
			FScriptMapHelper MapHelper(MapProperty, Val);

			if (CastField<FSoftObjectProperty>(MapProperty->ValueProp))
			{
				for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const FSoftObjectPtr* SoftObjectPtr = reinterpret_cast<const FSoftObjectPtr*>(MapHelper.GetValuePtr(i));
					JsonMap.Set(Key, SoftObjectPtr->ToSoftObjectPath().ToString());
				}
			}
			else if (const auto InnerStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
			{
				const auto InnerMapStruct = InnerStructProperty->Struct;
				if (InnerMapStruct->IsChildOf(FBeamMap::StaticStruct()))
				{
					const FMapProperty* InnerMapProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
					{
						InnerMapProperty = CastField<FMapProperty>(*OptIt);
						if (InnerMapProperty) break;
					}

					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamMap* Data = reinterpret_cast<const FBeamMap*>(MapHelper.GetValuePtr(i));

						FJsonDomBuilder::FObject SubMap = FJsonDomBuilder::FObject{};
						SerializeMapProperty(PropName, SubMap, InnerMapProperty, Data, CallingContext);
						JsonMap.Set(Key, SubMap);
					}
				}
				else if (InnerMapStruct->IsChildOf(FBeamArray::StaticStruct()))
				{
					const FArrayProperty* InnerArrayProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(InnerMapStruct); OptIt; ++OptIt)
					{
						InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
						if (InnerArrayProperty) break;
					}

					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamArray* Data = reinterpret_cast<const FBeamArray*>(MapHelper.GetValuePtr(i));

						FJsonDomBuilder::FArray SubArray;

						SerializeArrayProperty(PropName, SubArray, InnerArrayProperty, Data, CallingContext);
						JsonMap.Set(Key, SubArray);
					}
				}
				else if (InnerMapStruct == TBaseStructure<FVector>::Get())
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FVector* Data = reinterpret_cast<const FVector*>(MapHelper.GetValuePtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("x"), Data->X);
						Bag.Set(TEXT("y"), Data->Y);
						Bag.Set(TEXT("z"), Data->Z);

						JsonMap.Set(Key, Bag.AsJsonObject());
					}
				}
				else if (InnerMapStruct == TBaseStructure<FIntVector>::Get())
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FIntVector* Data = reinterpret_cast<const FIntVector*>(MapHelper.GetValuePtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("x"), Data->X);
						Bag.Set(TEXT("y"), Data->Y);
						Bag.Set(TEXT("z"), Data->Z);

						JsonMap.Set(Key, Bag.AsJsonObject());
					}
				}
				else if (InnerMapStruct == TBaseStructure<FColor>::Get())
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FColor* Data = reinterpret_cast<const FColor*>(MapHelper.GetValuePtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("a"), Data->A);
						Bag.Set(TEXT("b"), Data->B);
						Bag.Set(TEXT("g"), Data->G);
						Bag.Set(TEXT("r"), Data->R);

						JsonMap.Set(Key, Bag.AsJsonObject());
					}
				}
				else if (InnerMapStruct == TBaseStructure<FLinearColor>::Get())
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FLinearColor* Data = reinterpret_cast<const FLinearColor*>(MapHelper.GetValuePtr(i));
						auto Bag = FJsonDomBuilder::FObject();
						Bag.Set(TEXT("a"), Data->A);
						Bag.Set(TEXT("b"), Data->B);
						Bag.Set(TEXT("g"), Data->G);
						Bag.Set(TEXT("r"), Data->R);

						JsonMap.Set(Key, Bag.AsJsonObject());
					}
				}
				else if (InnerMapStruct->IsChildOf(FGameplayTag::StaticStruct()))
				{
					const auto MapNum = MapHelper.Num();
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FGameplayTag* UnrealGameplayTag = reinterpret_cast<const FGameplayTag*>(MapHelper.GetValuePtr(i));
						const FString UnderlyingString = UnrealGameplayTag->ToString();
						JsonMap.Set(Key, UnderlyingString);
					}
				}
				else if (InnerMapStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
				{
					const auto MapNum = MapHelper.Num();
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FGameplayTagContainer* UnrealGameplayTag = reinterpret_cast<const FGameplayTagContainer*>(MapHelper.GetValuePtr(i));
						const FString UnderlyingString = UnrealGameplayTag->ToString();
						JsonMap.Set(Key, UnderlyingString);
					}
				}
				// else if (InnerMapStruct->IsChildOf(FBeamContentLink::StaticStruct()))
				// {
				// 	const auto ArrayNum = MapHelper.Num();
				// 	for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
				// 	{
				// 		const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
				// 		const FBeamContentLink* BeamSemantic = reinterpret_cast<const FBeamContentLink*>(MapHelper.GetValuePtr(i));
				// 		const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
				// 		JsonMap.Set(Key, *UnderlyingString);
				// 	}
				// }
				else if (InnerMapStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamSemanticType* BeamSemantic = reinterpret_cast<const FBeamSemanticType*>(MapHelper.GetValuePtr(i));
						const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
						JsonMap.Set(Key, *UnderlyingString);
					}
				}
				else if (InnerMapStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
						const FBeamJsonSerializableUStruct* Data = reinterpret_cast<const FBeamJsonSerializableUStruct*>(MapHelper.GetValuePtr(i));

						FString JsonBody;
						TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
						Data->BeamSerialize(Serializer);
						Serializer->Close();

						FJsonDataBag Bag;
						UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

						FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
						JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

						JsonMap.Set(Key, JsonObject);
					}
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"), *PropName)
				}
			}

			else if (CastField<FClassProperty>(MapProperty->ValueProp))
			{
				for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const UClass** Data = reinterpret_cast<const UClass**>(MapHelper.GetValuePtr(i));

					JsonMap.Set(Key, FSoftClassPath(*Data).ToString());
				}
			}
			else if (const auto InnerObjectProp = CastField<FObjectProperty>(MapProperty->ValueProp))
			{
				if (InnerObjectProp->PropertyClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
				{
					for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
					{
						if (UObject* InstancedObject = *reinterpret_cast<UObject**>(MapHelper.GetValuePtr(i)))
						{
							if (IBeamJsonSerializableUObject* Data = Cast<IBeamJsonSerializableUObject>(InstancedObject))
							{
								FString JsonBody;
								TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
								Data->BeamSerialize(Serializer);
								Serializer->Close();

								FJsonDataBag Bag;
								UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

								FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
								JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

								const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
								JsonMap.Set(Key, JsonObject);
							}
						}
					}
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
					       *InnerObjectProp->PropertyClass->GetName())
				}
			}
			else if (CastField<FTextProperty>(MapProperty->ValueProp))
			{
				for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const auto Data = reinterpret_cast<const FText*>(MapHelper.GetValuePtr(i));
					FString ToSerialize;
					if (Data->IsFromStringTable())
					{
						FName TableId;
						FString TableKey;
						FTextInspector::GetTableIdAndKey(*Data, TableId, TableKey);
						ToSerialize = TEXT("BEAM_ST₢") + TableId.ToString() + TEXT("₢") + TableKey;
					}
					else
					{
						ToSerialize = Data->ToString();
					}
					JsonMap.Set(Key, ToSerialize);
				}
			}
			else if (CastField<FNameProperty>(MapProperty->ValueProp))
			{
				for (FScriptMapHelper::FIterator i = MapHelper.CreateIterator(); i; ++i)
				{
					const FString Key = StrKeyProperty->GetPropertyValue(MapHelper.GetKeyPtr(i));
					const FName* Data = reinterpret_cast<const FName*>(MapHelper.GetValuePtr(i));

					JsonMap.Set(Key, (*Data).ToString());
				}
			}
			else if (CastField<FStrProperty>(MapProperty->ValueProp))
			{
				BuildMap<FString>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FBoolProperty>(MapProperty->ValueProp))
			{
				BuildMap<bool>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FFloatProperty>(MapProperty->ValueProp))
			{
				BuildMap<float>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FDoubleProperty>(MapProperty->ValueProp))
			{
				BuildMap<double>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FIntProperty>(MapProperty->ValueProp))
			{
				BuildMap<int32>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FInt64Property>(MapProperty->ValueProp))
			{
				BuildMap<int64>(StrKeyProperty, JsonMap, MapHelper);
			}
			else if (CastField<FByteProperty>(MapProperty->ValueProp))
			{
				BuildMap<uint8>(StrKeyProperty, JsonMap, MapHelper);
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *PropName, *MapProperty->ValueProp->GetName())
			}
		}
		else
		{
			UE_LOG(LogBeamContent, Error, TEXT("Content Serialization does not support maps with non-FString keys.\n"))
		}
	}

	static void BuildPropertiesJsonObject(FJsonDomBuilder::FObject& Properties, UObject* CallingContext, TArray<FString> ExcludeFields = TArray<FString>(), bool bIsContent = false)
	{
		const auto SelfClass = CallingContext->GetClass();

		UE_LOG(LogBeamRuntime, Verbose, TEXT("BuildPropertiesJsonObject - Parsing Class: %s"), *SelfClass->GetName());

		// First, we sort the fields by name
		TArray<FProperty*> SortedProps;
		for (TFieldIterator<FProperty> It(SelfClass); It; ++It)
		{
			SortedProps.Add(*It);
		}
		SortedProps.StableSort([](FProperty& A, FProperty& B) { return A.GetName() < B.GetName(); });

		// Then we go through the sorted properties to build the JSON.
		for (FProperty* It : SortedProps)
		{
			FJsonDomBuilder::FObject CurrProp = FJsonDomBuilder::FObject{};
			FString CurrPropName = It->GetName();
			UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Parsing Prop: %s"), *CurrPropName);
			if (ExcludeFields.Contains(CurrPropName))
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Skipping Excluded Prop: %s"), *CurrPropName);
				continue;
			}


			auto ShouldAddToJson = true;
			if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(It))
			{
				const auto Val = SoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(CallingContext);
				if (Val->IsNull()) CurrProp.Set("data", "");
				else CurrProp.Set("data", Val->ToSoftObjectPath().ToString());
			}
			else if (const auto StructProperty = CastField<FStructProperty>(It))
			{
				const auto ScriptStruct = StructProperty->Struct;
				if (ScriptStruct && ScriptStruct->IsChildOf(FBeamOptional::StaticStruct()))
				{
					UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Prop %s is FBeamOptional"), *CurrPropName);

					const FBeamOptional* Data = StructProperty->ContainerPtrToValuePtr<FBeamOptional>(CallingContext);
					ShouldAddToJson = Data->IsSet;

					if (ShouldAddToJson)
					{
						FProperty* ValueProp = nullptr;
						for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
						{
							const auto Name = OptIt->NamePrivate;
							ValueProp = !Name.IsEqual(TEXT("IsSet")) ? *OptIt : ValueProp;
						}

						if (const auto InnerOptionalSoftObjectProperty = CastField<FSoftObjectProperty>(ValueProp))
						{
							const auto Val = InnerOptionalSoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(Data);
							if (Val->IsNull()) CurrProp.Set("data", nullptr);
							else CurrProp.Set("data", Val->ToSoftObjectPath().ToString());
						}
						else if (const auto InnerOptionalStructProperty = CastField<FStructProperty>(ValueProp))
						{
							const auto InnerOptionalStruct = InnerOptionalStructProperty->Struct;

							if (InnerOptionalStruct->IsChildOf(FBeamMap::StaticStruct()))
							{
								const FBeamMap* BeamMap = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamMap>(Data);
								FJsonDomBuilder::FObject SubMap = FJsonDomBuilder::FObject{};
								const FMapProperty* InnerMapProperty = nullptr;
								for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
								{
									InnerMapProperty = CastField<FMapProperty>(*OptIt);
									if (InnerMapProperty) break;
								}

								SerializeMapProperty(CurrPropName, SubMap, InnerMapProperty, BeamMap, CallingContext);
								CurrProp.Set("data", SubMap);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamArray::StaticStruct()))
							{
								const FBeamArray* BeamArray = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamArray>(Data);
								FJsonDomBuilder::FArray SubArray;
								const FArrayProperty* InnerArrayProperty = nullptr;
								for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
								{
									InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
									if (InnerArrayProperty) break;
								}

								SerializeArrayProperty(CurrPropName, SubArray, InnerArrayProperty, BeamArray, CallingContext);
								CurrProp.Set("data", SubArray);
							}
							else if (InnerOptionalStruct == TBaseStructure<FVector>::Get())
							{
								const FVector* ValueData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FVector>(Data);
								auto Bag = FJsonDomBuilder::FObject{};
								Bag.Set(TEXT("x"), ValueData->X);
								Bag.Set(TEXT("y"), ValueData->Y);
								Bag.Set(TEXT("z"), ValueData->Z);

								CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
							}
							else if (InnerOptionalStruct == TBaseStructure<FIntVector>::Get())
							{
								const FVector* ValueData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FVector>(Data);
								auto Bag = FJsonDomBuilder::FObject{};
								Bag.Set(TEXT("x"), ValueData->X);
								Bag.Set(TEXT("y"), ValueData->Y);
								Bag.Set(TEXT("z"), ValueData->Z);

								CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
							}
							else if (InnerOptionalStruct == TBaseStructure<FColor>::Get())
							{
								const FColor* ValueData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FColor>(Data);
								auto Bag = FJsonDomBuilder::FObject{};
								Bag.Set(TEXT("a"), ValueData->A);
								Bag.Set(TEXT("b"), ValueData->B);
								Bag.Set(TEXT("g"), ValueData->G);
								Bag.Set(TEXT("r"), ValueData->R);

								CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
							}
							else if (InnerOptionalStruct == TBaseStructure<FLinearColor>::Get())
							{
								const FLinearColor* ValueData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FLinearColor>(Data);
								auto Bag = FJsonDomBuilder::FObject{};
								Bag.Set(TEXT("a"), ValueData->A);
								Bag.Set(TEXT("b"), ValueData->B);
								Bag.Set(TEXT("g"), ValueData->G);
								Bag.Set(TEXT("r"), ValueData->R);

								CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamContentLink::StaticStruct()))
							{
								const FBeamContentLink* ContentLink = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamContentLink>(Data);
								const FString* UnderlyingString = static_cast<const FString*>(ContentLink->GetAddr(0));
								CurrProp.Set(TEXT("$link"), *UnderlyingString);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
							{
								const FBeamSemanticType* BeamSemantic = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(Data);
								const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
								CurrProp.Set("data", *UnderlyingString);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
							{
								const FBeamJsonSerializableUStruct* BeamJsonSerializable = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(Data);
								FString JsonBody;
								TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
								BeamJsonSerializable->BeamSerialize(Serializer);
								Serializer->Close();

								FJsonDataBag Bag;
								UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

								FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
								JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

								UE_LOG(LogBeamContent, Display, TEXT("FBeamOptional wrapping type %s Field %s=%s is a \n"), *InnerOptionalStruct->GetName(), *It->GetName(), *JsonBody);
								CurrProp.Set("data", JsonObject);
							}
							else
							{
								UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
								       *It->GetName())
							}
						}
						else if (const auto InnerOptionalUObjectProperty = CastField<FObjectProperty>(ValueProp))
						{
							const auto InnerOptionalClass = InnerOptionalUObjectProperty->PropertyClass;

							if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
							{
								if (const IBeamJsonSerializableUObject* BeamJsonSerializable = Cast<IBeamJsonSerializableUObject>(
									InnerOptionalUObjectProperty->GetObjectPropertyValue(InnerOptionalUObjectProperty->ContainerPtrToValuePtr<void>(Data))))
								{
									FString JsonBody;
									TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
									BeamJsonSerializable->BeamSerialize(Serializer);
									Serializer->Close();

									FJsonDataBag Bag;
									UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

									FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
									JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

									UE_LOG(LogBeamContent, Display, TEXT("FBeamOptional wrapping type %s Field %s=%s is a \n"), *InnerOptionalClass->GetName(), *It->GetName(), *JsonBody);
									CurrProp.Set("data", JsonObject);
								}
								else
								{
									CurrProp.Set("data", nullptr);
								}
							}
							else
							{
								UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
								       *It->GetName())
							}
						}
						else if (const auto MapProperty = CastField<FMapProperty>(ValueProp))
						{
							FJsonDomBuilder::FObject MapJson = FJsonDomBuilder::FObject{};
							SerializeMapProperty(CurrPropName, MapJson, MapProperty, Data, CallingContext);
							CurrProp.Set("data", MapJson);
						}
						else if (const auto ArrayProperty = CastField<FArrayProperty>(ValueProp))
						{
							FJsonDomBuilder::FArray ArrayJson;
							SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, Data, CallingContext);
							const auto StructProp = CastField<FStructProperty>(ArrayProperty->Inner);
							if (StructProp && StructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
								CurrProp.Set("$links", ArrayJson);
							else
								CurrProp.Set("data", ArrayJson);
						}
						else if (const auto ClassProperty = CastField<FClassProperty>(ValueProp))
						{
							const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(Data);
							CurrProp.Set("data", FSoftClassPath(static_cast<UClass*>(ClassProperty->GetPropertyValue(Val))).ToString());
						}
						else if (const auto TextProperty = CastField<FTextProperty>(ValueProp))
						{
							const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(Data);
							FString ToSerialize;
							if (Val->IsFromStringTable())
							{
								FName TableId;
								FString Key;
								FTextInspector::GetTableIdAndKey(*Val, TableId, Key);
								ToSerialize = TEXT("BEAM_ST₢") + TableId.ToString() + TEXT("₢") + Key;
							}
							else
							{
								ToSerialize = Val->ToString();
							}

							CurrProp.Set("data", ToSerialize);
						}
						else if (const auto NameProperty = CastField<FNameProperty>(ValueProp))
						{
							const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(Data);
							CurrProp.Set("data", NameProperty->GetPropertyValue(Val).ToString());
						}
						else if (const auto StrProperty = CastField<FStrProperty>(ValueProp))
						{
							const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(Data);
							CurrProp.Set("data", StrProperty->GetPropertyValue(Val));
						}
						else if (const auto BoolProperty = CastField<FBoolProperty>(ValueProp))
						{
							const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(Data);
							CurrProp.Set("data", BoolProperty->GetPropertyValue(Val));
						}
						else if (const auto FloatProperty = CastField<FFloatProperty>(ValueProp))
						{
							const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(Data);
							CurrProp.Set("data", FloatProperty->GetFloatingPointPropertyValue(Val));
						}
						else if (const auto DoubleProperty = CastField<FDoubleProperty>(ValueProp))
						{
							const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(Data);
							CurrProp.Set("data", DoubleProperty->GetFloatingPointPropertyValue(Val));
						}
						else if (const auto Int32Property = CastField<FIntProperty>(ValueProp))
						{
							const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(Data);
							CurrProp.Set("data", Int32Property->GetSignedIntPropertyValue(Val));
						}
						else if (const auto Int64Property = CastField<FInt64Property>(ValueProp))
						{
							const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(Data);
							CurrProp.Set("data", Int64Property->GetSignedIntPropertyValue(Val));
						}
						else if (const auto ByteProperty = CastField<FByteProperty>(ValueProp))
						{
							const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(Data);
							CurrProp.Set("data", ByteProperty->GetUnsignedIntPropertyValue(Val));
						}
						else if (const auto EnumProperty = CastField<FEnumProperty>(ValueProp))
						{
							UEnum* Enum = EnumProperty->GetEnum();
							void const* EnumValueAddress = EnumProperty->ContainerPtrToValuePtr<void>(Data);
							int64 EnumValue = EnumProperty->GetUnderlyingProperty()->GetUnsignedIntPropertyValue(EnumValueAddress);
							CurrProp.Set("data", Enum->GetNameStringByValue(EnumValue));
						}
						else
						{
							UE_LOG(LogBeamContent, Error, TEXT("Optional Field %s's underlying Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(),
							       *ValueProp->GetCPPType())
						}
					}
					else
					{
						UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Skipping unset optional prop: %s"), *CurrPropName);
					}
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamMap::StaticStruct()))
				{
					const FBeamMap* Data = StructProperty->ContainerPtrToValuePtr<FBeamMap>(CallingContext);

					FMapProperty* MapProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
					{
						MapProperty = CastField<FMapProperty>(*OptIt);
						if (MapProperty) break;
					}

					FJsonDomBuilder::FObject MapJson = FJsonDomBuilder::FObject{};
					SerializeMapProperty(CurrPropName, MapJson, MapProperty, Data, CallingContext);
					CurrProp.Set("data", MapJson);
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamArray::StaticStruct()))
				{
					const FBeamArray* Data = StructProperty->ContainerPtrToValuePtr<FBeamArray>(CallingContext);

					FArrayProperty* ArrayProperty = nullptr;
					for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
					{
						ArrayProperty = CastField<FArrayProperty>(*OptIt);
						if (ArrayProperty) break;
					}

					FJsonDomBuilder::FArray ArrayJson;
					SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, Data, CallingContext);
					CurrProp.Set("data", ArrayJson);
				}
				else if (ScriptStruct && ScriptStruct == TBaseStructure<FVector>::Get())
				{
					const FVector* Data = StructProperty->ContainerPtrToValuePtr<FVector>(CallingContext);
					auto Bag = FJsonDomBuilder::FObject{};
					Bag.Set(TEXT("x"), Data->X);
					Bag.Set(TEXT("y"), Data->Y);
					Bag.Set(TEXT("z"), Data->Z);

					CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
				}
				else if (ScriptStruct && ScriptStruct == TBaseStructure<FIntVector>::Get())
				{
					const FIntVector* Data = StructProperty->ContainerPtrToValuePtr<FIntVector>(CallingContext);
					auto Bag = FJsonDomBuilder::FObject{};
					Bag.Set(TEXT("x"), Data->X);
					Bag.Set(TEXT("y"), Data->Y);
					Bag.Set(TEXT("z"), Data->Z);

					CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
				}
				else if (ScriptStruct && ScriptStruct == TBaseStructure<FColor>::Get())
				{
					const FColor* Data = StructProperty->ContainerPtrToValuePtr<FColor>(CallingContext);
					auto Bag = FJsonDomBuilder::FObject{};
					Bag.Set(TEXT("a"), Data->A);
					Bag.Set(TEXT("b"), Data->B);
					Bag.Set(TEXT("g"), Data->G);
					Bag.Set(TEXT("r"), Data->R);

					CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
				}
				else if (ScriptStruct && ScriptStruct == TBaseStructure<FLinearColor>::Get())
				{
					const FLinearColor* Data = StructProperty->ContainerPtrToValuePtr<FLinearColor>(CallingContext);
					auto Bag = FJsonDomBuilder::FObject{};
					Bag.Set(TEXT("a"), Data->A);
					Bag.Set(TEXT("b"), Data->B);
					Bag.Set(TEXT("g"), Data->G);
					Bag.Set(TEXT("r"), Data->R);

					CurrProp.Set(TEXT("data"), Bag.AsJsonObject());
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTag::StaticStruct()))
				{
					const FGameplayTag* UnrealGameplayTag = StructProperty->ContainerPtrToValuePtr<FGameplayTag>(CallingContext);
					const FString UnderlyingString = UnrealGameplayTag->ToString();
					CurrProp.Set("data", UnderlyingString);
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
				{
					const FGameplayTagContainer* UnrealGameplayTag = StructProperty->ContainerPtrToValuePtr<FGameplayTagContainer>(CallingContext);
					const FString UnderlyingString = UnrealGameplayTag->ToString();
					CurrProp.Set("data", UnderlyingString);
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamContentLink::StaticStruct()))
				{
					const FBeamContentLink* ContentLink = StructProperty->ContainerPtrToValuePtr<FBeamContentLink>(CallingContext);
					const FString* UnderlyingString = static_cast<const FString*>(ContentLink->GetAddr(0));
					CurrProp.Set(TEXT("$link"), *UnderlyingString);
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
				{
					const FBeamSemanticType* BeamSemantic = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(CallingContext);
					const FString* UnderlyingString = static_cast<const FString*>(BeamSemantic->GetAddr(0));
					CurrProp.Set("data", *UnderlyingString);
				}
				else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
				{
					const FBeamJsonSerializableUStruct* BeamJsonSerializable = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(CallingContext);

					FString JsonBody;
					TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
					BeamJsonSerializable->BeamSerialize(Serializer);
					Serializer->Close();

					FJsonDataBag Bag;
					UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

					FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
					JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });

					CurrProp.Set("data", JsonObject);
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is not supported by the Content serialization system.\n"), *It->GetName())
				}
			}
			else if (const auto MapProperty = CastField<FMapProperty>(It))
			{
				FJsonDomBuilder::FObject MapJson = FJsonDomBuilder::FObject{};
				SerializeMapProperty(CurrPropName, MapJson, MapProperty, CallingContext, CallingContext);
				CurrProp.Set("data", MapJson);
			}
			else if (const auto ArrayProperty = CastField<FArrayProperty>(It))
			{
				FJsonDomBuilder::FArray ArrayJson;
				SerializeArrayProperty(CurrPropName, ArrayJson, ArrayProperty, CallingContext, CallingContext);
				const auto StructProp = CastField<FStructProperty>(ArrayProperty->Inner);
				if (StructProp && StructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
					CurrProp.Set("$links", ArrayJson);
				else
					CurrProp.Set("data", ArrayJson);
			}
			else if (const auto ClassProperty = CastField<FClassProperty>(It))
			{
				const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(CallingContext);
				CurrProp.Set("data", FSoftClassPath(static_cast<UClass*>(ClassProperty->GetPropertyValue(Val))).ToString());
			}

			else if (const auto UObjectProperty = CastField<FObjectProperty>(It))
			{
				const auto InnerOptionalClass = UObjectProperty->PropertyClass;
				if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
				{
					if (const IBeamJsonSerializableUObject* BeamJsonSerializable = Cast<IBeamJsonSerializableUObject>(
						UObjectProperty->GetObjectPropertyValue(UObjectProperty->ContainerPtrToValuePtr<void>(CallingContext))))
					{
						FString JsonBody;
						TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonBody);
						BeamJsonSerializable->BeamSerialize(Serializer);
						Serializer->Close();

						FJsonDataBag Bag;
						UBeamJsonUtils::FromJsonToBag(JsonBody, Bag);

						FJsonDomBuilder::FObject JsonObject = FJsonDomBuilder::FObject{};
						JsonObject.CopyIf(*Bag.JsonObject, [](const FString&, const FJsonValue&) { return true; });
						CurrProp.Set("data", JsonObject);
					}
					else
					{
						CurrProp.Set("data", nullptr);
					}
				}
				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement IBeamJsonSerializableUObject. It cannot be in a content object unless it does.\n"),
					       *It->GetName())
				}
			}
			else if (const auto TextProperty = CastField<FTextProperty>(It))
			{
				const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(CallingContext);
				FString ToSerialize;
				if (Val->IsFromStringTable())
				{
					FName TableId;
					FString Key;
					FTextInspector::GetTableIdAndKey(*Val, TableId, Key);
					ToSerialize = TEXT("BEAM_ST₢") + TableId.ToString() + TEXT("₢") + Key;
				}
				else
				{
					ToSerialize = Val->ToString();
				}

				CurrProp.Set("data", ToSerialize);
			}
			else if (const auto NameProperty = CastField<FNameProperty>(It))
			{
				const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(CallingContext);
				CurrProp.Set("data", NameProperty->GetPropertyValue(Val).ToString());
			}
			else if (const auto StrProperty = CastField<FStrProperty>(It))
			{
				const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(CallingContext);
				CurrProp.Set("data", StrProperty->GetPropertyValue(Val));
			}
			else if (const auto BoolProperty = CastField<FBoolProperty>(It))
			{
				const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(CallingContext);
				CurrProp.Set("data", BoolProperty->GetPropertyValue(Val));
			}
			else if (const auto FloatProperty = CastField<FFloatProperty>(It))
			{
				const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(CallingContext);
				CurrProp.Set("data", FloatProperty->GetFloatingPointPropertyValue(Val));
			}
			else if (const auto DoubleProperty = CastField<FDoubleProperty>(It))
			{
				const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(CallingContext);
				CurrProp.Set("data", DoubleProperty->GetFloatingPointPropertyValue(Val));
			}
			else if (const auto Int32Property = CastField<FIntProperty>(It))
			{
				const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(CallingContext);
				CurrProp.Set("data", Int32Property->GetSignedIntPropertyValue(Val));
			}
			else if (const auto Int64Property = CastField<FInt64Property>(It))
			{
				const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(CallingContext);
				CurrProp.Set("data", Int64Property->GetSignedIntPropertyValue(Val));
			}
			else if (const auto ByteProperty = CastField<FByteProperty>(It))
			{
				const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(CallingContext);
				CurrProp.Set("data", ByteProperty->GetUnsignedIntPropertyValue(Val));
			}
			else if (const auto EnumProperty = CastField<FEnumProperty>(It))
			{
				UEnum* Enum = EnumProperty->GetEnum();
				void const* EnumValueAddress = EnumProperty->ContainerPtrToValuePtr<void>(CallingContext);
				int64 EnumValue = EnumProperty->GetUnderlyingProperty()->GetUnsignedIntPropertyValue(EnumValueAddress);
				CurrProp.Set("data", Enum->GetNameStringByValue(EnumValue));
			}
			else
			{
				UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(), *ArrayProperty->Inner->GetName())
			}

			// If we should not even add the property to the serialized content object (mostly for optional fields)
			if (ShouldAddToJson)
			{
				if (bIsContent)
				{
					Properties.Set(It->GetName(), CurrProp);
				}
				else
				{
					Properties.Set(It->GetName(), CurrProp.AsJsonObject()->GetField<EJson::None>(TEXT("data")));
				}
			}
		}
	}


	static void ParsePropertiesJsonObject(const TSharedPtr<FJsonObject>& JsonProperties, UObject* CallingContext, TArray<FString> ExcludeFields = TArray<FString>(), bool bIsContent = false)
	{
		const auto SelfClass = CallingContext->GetClass();
		UE_LOG(LogBeamContent, Verbose, TEXT("ParsePropertiesJsonObject - Entry: %s"), *SelfClass->GetName());

		for (TFieldIterator<FProperty> It(SelfClass); It; ++It)
		{
			const FString PropName = It->GetName();
			UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Parsing Prop: %s"), *PropName);
			if (ExcludeFields.Contains(PropName))
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("BuildPropertiesJsonObject - Skipping Excluded Prop: %s"), *PropName);
				continue;
			}

			if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(*It))
			{
				FString JsonVal;
				if (bIsContent)
				{
					if (!JsonProperties->GetObjectField(PropName)->TryGetStringField(TEXT("data"), JsonVal))
						JsonVal = TEXT("None");
				}
				else
				{
					if (!JsonProperties->TryGetStringField(PropName, JsonVal))
						JsonVal = TEXT("None");
				}

				const auto Val = SoftObjectProperty->ContainerPtrToValuePtr<FSoftObjectPtr>(CallingContext);
				SoftObjectProperty->SetPropertyValue(Val, FSoftObjectPtr(FSoftObjectPath(JsonVal)));
			}
			else
			{
				TSharedPtr<FJsonObject> ObjectField = !bIsContent ? JsonProperties->GetObjectField(PropName) : JsonProperties->GetObjectField(PropName)->GetObjectField(TEXT("data"));

				TArray<TSharedPtr<FJsonValue>> ObjectArray = !bIsContent ? JsonProperties->GetArrayField(PropName) : JsonProperties->GetObjectField(PropName)->GetArrayField(TEXT("data"));

				FString ObjectString = !bIsContent ? JsonProperties->GetStringField(PropName) : JsonProperties->GetObjectField(PropName)->GetStringField(TEXT("data"));

				int32 ObjectInteger = !bIsContent ? JsonProperties->GetIntegerField(PropName) : JsonProperties->GetObjectField(PropName)->GetIntegerField(TEXT("data"));

				bool ObjectBool = !bIsContent ? JsonProperties->GetBoolField(PropName) : JsonProperties->GetObjectField(PropName)->GetBoolField(TEXT("data"));

				double ObjectNumber = !bIsContent ? JsonProperties->GetNumberField(PropName) : JsonProperties->GetObjectField(PropName)->GetNumberField(TEXT("data"));

				if (const auto StructProperty = CastField<FStructProperty>(*It))
				{
					const auto ScriptStruct = StructProperty->Struct;
					if (ScriptStruct && ScriptStruct->IsChildOf(FBeamOptional::StaticStruct()))
					{
						const auto ExistsInJson = JsonProperties->HasField(PropName);
						if (!ExistsInJson)
						{
							StructProperty->InitializeValueInternal(StructProperty->ContainerPtrToValuePtr<void>(CallingContext));
							FBeamOptional* OptionalVal = StructProperty->ContainerPtrToValuePtr<FBeamOptional>(CallingContext);
							OptionalVal->IsSet = false;
							continue;
						}

						FProperty* OptionalValueProp = nullptr;
						for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
						{
							const auto Name = OptIt->NamePrivate;
							OptionalValueProp = !Name.IsEqual(TEXT("IsSet")) ? *OptIt : OptionalValueProp;
						}


						FBeamOptional* OptionalVal = StructProperty->ContainerPtrToValuePtr<FBeamOptional>(CallingContext);

						if (const auto InnerOptionalSoftObject = CastField<FSoftObjectProperty>(OptionalValueProp))
						{
							const auto Val = InnerOptionalSoftObject->ContainerPtrToValuePtr<FSoftObjectPtr>(OptionalVal);
							InnerOptionalSoftObject->SetPropertyValue(Val, FSoftObjectPtr(FSoftObjectPath(ObjectString)));
						}
						else if (const auto InnerOptionalStructProperty = CastField<FStructProperty>(OptionalValueProp))
						{
							const auto InnerOptionalStruct = InnerOptionalStructProperty->Struct;

							if (InnerOptionalStruct->IsChildOf(FBeamMap::StaticStruct()))
							{
								const auto BeamMapJson = ObjectField;
								FBeamMap* BeamMap = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamMap>(OptionalVal);
								BeamMap->OuterOwner = CallingContext;
								const FMapProperty* InnerMapProperty = nullptr;
								for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
								{
									InnerMapProperty = CastField<FMapProperty>(*OptIt);
									if (InnerMapProperty) break;
								}
								ParseMapProperty(PropName, BeamMapJson, InnerMapProperty, BeamMap, CallingContext);
								OptionalVal->Set(BeamMap);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamArray::StaticStruct()))
							{
								const auto BeamArrayJson = ObjectArray;
								FBeamArray* BeamArray = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamArray>(OptionalVal);
								BeamArray->OuterOwner = CallingContext;
								const FArrayProperty* InnerArrayProperty = nullptr;
								for (TFieldIterator<FProperty> OptIt(InnerOptionalStruct); OptIt; ++OptIt)
								{
									InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
									if (InnerArrayProperty) break;
								}
								ParseArrayProperty(PropName, BeamArrayJson, InnerArrayProperty, BeamArray, CallingContext);
								OptionalVal->Set(BeamArray);
							}
							else if (InnerOptionalStruct == TBaseStructure<FVector>::Get())
							{
								const auto SubJsonSemantic = ObjectField;
								FVector* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FVector>(OptionalVal);
								ValData->X = SubJsonSemantic->GetNumberField(TEXT("x"));
								ValData->Y = SubJsonSemantic->GetNumberField(TEXT("y"));
								ValData->Z = SubJsonSemantic->GetNumberField(TEXT("z"));
								OptionalVal->Set(ValData);
							}
							else if (InnerOptionalStruct == TBaseStructure<FIntVector>::Get())
							{
								const auto SubJsonSemantic = ObjectField;
								FIntVector* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FIntVector>(OptionalVal);
								ValData->X = SubJsonSemantic->GetNumberField(TEXT("x"));
								ValData->Y = SubJsonSemantic->GetNumberField(TEXT("y"));
								ValData->Z = SubJsonSemantic->GetNumberField(TEXT("z"));
								OptionalVal->Set(ValData);
							}
							else if (InnerOptionalStruct == TBaseStructure<FColor>::Get())
							{
								const auto SubJsonSemantic = ObjectField;
								FColor* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FColor>(OptionalVal);
								ValData->A = SubJsonSemantic->GetNumberField(TEXT("a"));
								ValData->B = SubJsonSemantic->GetNumberField(TEXT("b"));
								ValData->G = SubJsonSemantic->GetNumberField(TEXT("g"));
								ValData->R = SubJsonSemantic->GetNumberField(TEXT("r"));
								OptionalVal->Set(ValData);
							}
							else if (InnerOptionalStruct == TBaseStructure<FLinearColor>::Get())
							{
								const auto SubJsonSemantic = ObjectField;
								FLinearColor* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FLinearColor>(OptionalVal);
								ValData->A = SubJsonSemantic->GetNumberField(TEXT("a"));
								ValData->B = SubJsonSemantic->GetNumberField(TEXT("b"));
								ValData->G = SubJsonSemantic->GetNumberField(TEXT("g"));
								ValData->R = SubJsonSemantic->GetNumberField(TEXT("r"));
								OptionalVal->Set(ValData);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamContentLink::StaticStruct()))
							{
								FString SubJsonSemantic;
								if (!JsonProperties->GetObjectField(PropName)->TryGetStringField(TEXT("$link"), SubJsonSemantic))
									SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField(TEXT("link"));

								FBeamContentLink* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamContentLink>(OptionalVal);
								ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
							{
								const auto SubJsonSemantic = ObjectString;
								FBeamSemanticType* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(OptionalVal);
								ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
								OptionalVal->Set(ValData);
							}
							else if (InnerOptionalStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
							{
								const auto SubJsonSerializable = ObjectField;
								FBeamJsonSerializableUStruct* ValData = InnerOptionalStructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(OptionalVal);
								ValData->OuterOwner = CallingContext;
								ValData->BeamDeserializeProperties(SubJsonSerializable);
								OptionalVal->Set(ValData);
							}
							else
							{
								UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a struct and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
								       *It->GetName())
							}
						}
						else if (const auto MapProperty = CastField<FMapProperty>(OptionalValueProp))
						{
							const auto MapJson = ObjectField;
							ParseMapProperty(PropName, MapJson, MapProperty, OptionalVal, CallingContext);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto ArrayProperty = CastField<FArrayProperty>(OptionalValueProp))
						{
							TArray<TSharedPtr<FJsonValue>> ArrayJson;
							const auto StructProp = CastField<FStructProperty>(ArrayProperty->Inner);
							if (StructProp && StructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
							{
								if (JsonProperties->GetObjectField(PropName)->HasField(TEXT("$links")))
									ArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField(TEXT("$links"));
								else if (JsonProperties->GetObjectField(PropName)->HasField(TEXT("links")))
									ArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField(TEXT("links"));
							}
							else
							{
								ArrayJson = ObjectArray;
							}

							ParseArrayProperty(PropName, ArrayJson, ArrayProperty, OptionalVal, CallingContext);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto ClassProperty = CastField<FClassProperty>(OptionalValueProp))
						{
							const auto StrVal = ObjectString;
							const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(OptionalVal);
							ClassProperty->SetPropertyValue(Val, FSoftClassPath{StrVal}.ResolveClass());
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto InnerOptionalUObjectProperty = CastField<FObjectProperty>(OptionalValueProp))
						{
							const auto InnerOptionalClass = InnerOptionalUObjectProperty->PropertyClass;

							if (InnerOptionalClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
							{
								const auto SubJsonSerializable = ObjectField;
								const auto Val = InnerOptionalUObjectProperty->ContainerPtrToValuePtr<UObject*>(OptionalVal);
								*Val = NewObject<UObject>(CallingContext, InnerOptionalClass);
								IBeamJsonSerializableUObject* ValData = Cast<IBeamJsonSerializableUObject>(*Val);
								ValData->OuterOwner = CallingContext;
								ValData->BeamDeserializeProperties(SubJsonSerializable);
								OptionalVal->Set(Val);
							}
							else
							{
								UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
								       *It->GetName())
							}
						}
						else if (const auto TextProperty = CastField<FTextProperty>(OptionalValueProp))
						{
							const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(OptionalVal);
							auto SerializedVal = ObjectString;
							if (SerializedVal.StartsWith(TEXT("BEAM_ST₢")))
							{
								SerializedVal.RightChopInline(SerializedVal.Find(TEXT("₢")) + 1);

								const auto SeparatorIdx = SerializedVal.Find(TEXT("₢"));
								FString TableId = SerializedVal.Left(SeparatorIdx);
								FString Key = SerializedVal.RightChop(SeparatorIdx + 1);
								FString KeyStr(Key);
								FName TableIdStr(TableId);
								TextProperty->SetPropertyValue(Val, FText::FromStringTable(TableIdStr, KeyStr));
							}
							else
							{
								TextProperty->SetPropertyValue(Val, FText::FromString(FString(SerializedVal)));
							}
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto NameProperty = CastField<FNameProperty>(OptionalValueProp))
						{
							const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(OptionalVal);
							NameProperty->SetPropertyValue(Val, FName(ObjectString));
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto StrProperty = CastField<FStrProperty>(OptionalValueProp))
						{
							const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(OptionalVal);
							StrProperty->SetPropertyValue(Val, ObjectString);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto BoolProperty = CastField<FBoolProperty>(OptionalValueProp))
						{
							const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(OptionalVal);
							BoolProperty->SetPropertyValue(Val, ObjectBool);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto FloatProperty = CastField<FFloatProperty>(OptionalValueProp))
						{
							const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(OptionalVal);
							FloatProperty->SetPropertyValue(Val, ObjectNumber);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto DoubleProperty = CastField<FDoubleProperty>(OptionalValueProp))
						{
							const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(OptionalVal);
							DoubleProperty->SetPropertyValue(Val, ObjectNumber);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto Int32Property = CastField<FIntProperty>(OptionalValueProp))
						{
							const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(OptionalVal);
							Int32Property->SetPropertyValue(Val, ObjectInteger);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto Int64Property = CastField<FInt64Property>(OptionalValueProp))
						{
							const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(OptionalVal);
							Int64Property->SetPropertyValue(Val, ObjectInteger);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto ByteProperty = CastField<FByteProperty>(OptionalValueProp))
						{
							const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(OptionalVal);
							ByteProperty->SetPropertyValue(Val, ObjectInteger);
							OptionalVal->Set(OptionalVal->GetAddr());
						}
						else if (const auto EnumProperty = CastField<FEnumProperty>(OptionalValueProp))
						{
							const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(OptionalVal);
							UEnum* Enum = EnumProperty->GetEnum();
							int64 EnumValue = Enum->GetValueByNameString(*Val);

							if (EnumValue != INDEX_NONE)
							{
								void* EnumValueAddress = EnumProperty->ContainerPtrToValuePtr<void>(OptionalVal);
								EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(EnumValueAddress, EnumValue);
								OptionalVal->Set(OptionalVal->GetAddr());
							}
						}
						else
						{
							UE_LOG(LogBeamContent, Error, TEXT("Optional Field %s's underlying Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(),
							       *OptionalValueProp->GetCPPType())
						}
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamMap::StaticStruct()))
					{
						const auto BeamMapJson = ObjectField;
						FBeamMap* BeamMap = StructProperty->ContainerPtrToValuePtr<FBeamMap>(CallingContext);
						BeamMap->OuterOwner = CallingContext;
						const FMapProperty* InnerMapProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
						{
							InnerMapProperty = CastField<FMapProperty>(*OptIt);
							if (InnerMapProperty) break;
						}
						ParseMapProperty(PropName, BeamMapJson, InnerMapProperty, BeamMap, CallingContext);
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamArray::StaticStruct()))
					{
						const auto BeamArrayJson = ObjectArray;
						FBeamArray* BeamArray = StructProperty->ContainerPtrToValuePtr<FBeamArray>(CallingContext);
						BeamArray->OuterOwner = CallingContext;
						const FArrayProperty* InnerArrayProperty = nullptr;
						for (TFieldIterator<FProperty> OptIt(ScriptStruct); OptIt; ++OptIt)
						{
							InnerArrayProperty = CastField<FArrayProperty>(*OptIt);
							if (InnerArrayProperty) break;
						}
						ParseArrayProperty(PropName, BeamArrayJson, InnerArrayProperty, BeamArray, CallingContext);
					}
					else if (ScriptStruct && ScriptStruct == TBaseStructure<FVector>::Get())
					{
						const auto SubJsonSemantic = ObjectField;
						FVector* ValData = StructProperty->ContainerPtrToValuePtr<FVector>(CallingContext);
						ValData->X = SubJsonSemantic->GetNumberField(TEXT("x"));
						ValData->Y = SubJsonSemantic->GetNumberField(TEXT("y"));
						ValData->Z = SubJsonSemantic->GetNumberField(TEXT("z"));
					}
					else if (ScriptStruct && ScriptStruct == TBaseStructure<FIntVector>::Get())
					{
						const auto SubJsonSemantic = ObjectField;
						FIntVector* ValData = StructProperty->ContainerPtrToValuePtr<FIntVector>(CallingContext);
						ValData->X = SubJsonSemantic->GetNumberField(TEXT("x"));
						ValData->Y = SubJsonSemantic->GetNumberField(TEXT("y"));
						ValData->Z = SubJsonSemantic->GetNumberField(TEXT("z"));
					}
					else if (ScriptStruct && ScriptStruct == TBaseStructure<FColor>::Get())
					{
						const auto SubJsonSemantic = ObjectField;
						FColor* ValData = StructProperty->ContainerPtrToValuePtr<FColor>(CallingContext);
						ValData->A = SubJsonSemantic->GetNumberField(TEXT("a"));
						ValData->B = SubJsonSemantic->GetNumberField(TEXT("b"));
						ValData->G = SubJsonSemantic->GetNumberField(TEXT("g"));
						ValData->R = SubJsonSemantic->GetNumberField(TEXT("r"));
					}
					else if (ScriptStruct && ScriptStruct == TBaseStructure<FLinearColor>::Get())
					{
						const auto SubJsonSemantic = ObjectField;
						FLinearColor* ValData = StructProperty->ContainerPtrToValuePtr<FLinearColor>(CallingContext);
						ValData->A = SubJsonSemantic->GetNumberField(TEXT("a"));
						ValData->B = SubJsonSemantic->GetNumberField(TEXT("b"));
						ValData->G = SubJsonSemantic->GetNumberField(TEXT("g"));
						ValData->R = SubJsonSemantic->GetNumberField(TEXT("r"));
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTag::StaticStruct()))
					{
						const auto SubJsonSemantic = ObjectString;
						FGameplayTag* ValData = StructProperty->ContainerPtrToValuePtr<FGameplayTag>(CallingContext);
						const auto bShouldError = GetDefault<UBeamCoreSettings>()->bErrorIfGameplayTagNotFound;
						*ValData = FGameplayTag::RequestGameplayTag(FName(SubJsonSemantic), !SubJsonSemantic.Equals(TEXT("None")) && bShouldError);
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FGameplayTagContainer::StaticStruct()))
					{
						const auto SubJsonSemantic = ObjectString;
						FGameplayTagContainer* ValData = StructProperty->ContainerPtrToValuePtr<FGameplayTagContainer>(CallingContext);
						ValData->FromExportString(SubJsonSemantic);
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamContentLink::StaticStruct()))
					{
						FString SubJsonSemantic;
						if (!JsonProperties->GetObjectField(PropName)->TryGetStringField(TEXT("$link"), SubJsonSemantic))
							SubJsonSemantic = JsonProperties->GetObjectField(PropName)->GetStringField(TEXT("link"));

						FBeamContentLink* ValData = StructProperty->ContainerPtrToValuePtr<FBeamContentLink>(CallingContext);
						ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamSemanticType::StaticStruct()))
					{
						const auto SubJsonSemantic = ObjectString;
						FBeamSemanticType* ValData = StructProperty->ContainerPtrToValuePtr<FBeamSemanticType>(CallingContext);
						ValData->Set(&SubJsonSemantic, ValData->GetSerializationRepresentationName(0));
					}
					else if (ScriptStruct && ScriptStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
					{
						const auto SubJsonSerializable = ObjectField;
						FBeamJsonSerializableUStruct* ValData = StructProperty->ContainerPtrToValuePtr<FBeamJsonSerializableUStruct>(CallingContext);
						ValData->OuterOwner = CallingContext;
						ValData->BeamDeserializeProperties(SubJsonSerializable);
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is not supported by the Content serialization system.\n"), *It->GetName())
					}
				}
				else if (const auto MapProperty = CastField<FMapProperty>(*It))
				{
					const auto Map = ObjectField;
					ParseMapProperty(PropName, Map, MapProperty, CallingContext, CallingContext);
				}
				else if (const auto ArrayProperty = CastField<FArrayProperty>(*It))
				{
					TArray<TSharedPtr<FJsonValue>> ArrayJson;
					const auto StructProp = CastField<FStructProperty>(ArrayProperty->Inner);
					if (StructProp && StructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
					{
						if (JsonProperties->GetObjectField(PropName)->HasField(TEXT("$links")))
							ArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField(TEXT("$links"));
						else if (JsonProperties->GetObjectField(PropName)->HasField(TEXT("links")))
							ArrayJson = JsonProperties->GetObjectField(PropName)->GetArrayField(TEXT("links"));
					}
					else
					{
						ArrayJson = ObjectArray;
					}

					ParseArrayProperty(PropName, ArrayJson, ArrayProperty, CallingContext, CallingContext);
				}
				else if (const auto ClassProperty = CastField<FClassProperty>(*It))
				{
					const auto Val = ClassProperty->ContainerPtrToValuePtr<UClass>(CallingContext);
					const auto StrVal = ObjectString;
					ClassProperty->SetPropertyValue(Val, FSoftClassPath{StrVal}.ResolveClass());
				}
				else if (const auto UObjectProperty = CastField<FObjectProperty>(*It))
				{
					const auto ObjectClass = UObjectProperty->PropertyClass;
					if (ObjectClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
					{
						const TSharedPtr<FJsonObject>* JsonObject;
						if (bIsContent)
						{
							if (JsonProperties->GetObjectField(PropName)->TryGetObjectField(TEXT("data"), JsonObject))
							{
								UObject* Val = NewObject<UObject>(CallingContext, ObjectClass);
								IBeamJsonSerializableUObject* ValData = Cast<IBeamJsonSerializableUObject>(Val);
								ValData->OuterOwner = CallingContext;
								ValData->BeamDeserializeProperties(*JsonObject);
								UObjectProperty->SetObjectPropertyValue(UObjectProperty->ContainerPtrToValuePtr<void>(CallingContext), Val);
							}
						}
						else
						{
							if (JsonProperties->TryGetObjectField(PropName, JsonObject))
							{
								UObject* Val = NewObject<UObject>(CallingContext, ObjectClass);
								IBeamJsonSerializableUObject* ValData = Cast<IBeamJsonSerializableUObject>(Val);
								ValData->OuterOwner = CallingContext;
								ValData->BeamDeserializeProperties(*JsonObject);
								UObjectProperty->SetObjectPropertyValue(UObjectProperty->ContainerPtrToValuePtr<void>(CallingContext), Val);
							}
						}
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type is a class and does not implement FBeamJsonSerializable. It cannot be in a content object unless it does.\n"),
						       *It->GetName())
					}
				}
				else if (const auto TextProperty = CastField<FTextProperty>(*It))
				{
					const auto Val = TextProperty->ContainerPtrToValuePtr<FText>(CallingContext);
					auto SerializedVal = ObjectString;
					if (SerializedVal.StartsWith(TEXT("BEAM_ST₢")))
					{
						SerializedVal.RightChopInline(SerializedVal.Find(TEXT("₢")) + 1);

						const auto SeparatorIdx = SerializedVal.Find(TEXT("₢"));
						FString TableId = SerializedVal.Left(SeparatorIdx);
						FString Key = SerializedVal.RightChop(SeparatorIdx + 1);
						FString KeyStr(Key);
						FName TableIdStr(TableId);
						TextProperty->SetPropertyValue(Val, FText::FromStringTable(TableIdStr, KeyStr));
					}
					else
					{
						TextProperty->SetPropertyValue(Val, FText::FromString(FString(SerializedVal)));
					}
				}
				else if (const auto NameProperty = CastField<FNameProperty>(*It))
				{
					const auto Val = NameProperty->ContainerPtrToValuePtr<FName>(CallingContext);
					NameProperty->SetPropertyValue(Val, FName(ObjectString));
				}
				else if (const auto StrProperty = CastField<FStrProperty>(*It))
				{
					const auto Val = StrProperty->ContainerPtrToValuePtr<FString>(CallingContext);
					StrProperty->SetPropertyValue(Val, ObjectString);
				}
				else if (const auto BoolProperty = CastField<FBoolProperty>(*It))
				{
					const auto Val = BoolProperty->ContainerPtrToValuePtr<bool>(CallingContext);
					BoolProperty->SetPropertyValue(Val, ObjectBool);
				}
				else if (const auto FloatProperty = CastField<FFloatProperty>(*It))
				{
					const auto Val = FloatProperty->ContainerPtrToValuePtr<float>(CallingContext);
					FloatProperty->SetPropertyValue(Val, ObjectNumber);
				}
				else if (const auto DoubleProperty = CastField<FDoubleProperty>(*It))
				{
					const auto Val = DoubleProperty->ContainerPtrToValuePtr<double>(CallingContext);
					DoubleProperty->SetPropertyValue(Val, ObjectNumber);
				}
				else if (const auto Int32Property = CastField<FIntProperty>(*It))
				{
					const auto Val = Int32Property->ContainerPtrToValuePtr<int32>(CallingContext);
					Int32Property->SetPropertyValue(Val, ObjectInteger);
				}
				else if (const auto Int64Property = CastField<FInt64Property>(*It))
				{
					const auto Val = Int64Property->ContainerPtrToValuePtr<int64>(CallingContext);
					Int64Property->SetPropertyValue(Val, ObjectInteger);
				}
				else if (const auto ByteProperty = CastField<FByteProperty>(*It))
				{
					const auto Val = ByteProperty->ContainerPtrToValuePtr<uint8>(CallingContext);
					ByteProperty->SetPropertyValue(Val, ObjectInteger);
				}
				else if (const auto EnumProperty = CastField<FEnumProperty>(*It))
				{
					UEnum* Enum = EnumProperty->GetEnum();
					const auto StrVal = ObjectString;
					int64 EnumValue = Enum->GetValueByNameString(StrVal);

					if (EnumValue != INDEX_NONE)
					{
						// Set the property value
						void* EnumValueAddress = EnumProperty->ContainerPtrToValuePtr<void>(CallingContext);
						EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(EnumValueAddress, EnumValue);
					}
				}

				else
				{
					UE_LOG(LogBeamContent, Error, TEXT("Field %s's Type (%s) is not supported by the Content serialization system.\n"), *It->GetName(), *It->GetCPPType())
				}
			}
		}
	}
};
