#pragma once
#include "BeamCoreTypes.h"



struct FBeamJsonUtils
{
	template<typename TOptionalType, typename TDataType = TOptionalType>
	constexpr static void SerializeOptional(const FString& Identifier, const FBeamOptional* ToSerialize, TUnrealJsonSerializer Serializer);
	
	template <typename TDataType>
	constexpr static void SerializeArray(const FString& Identifier, const TArray<TDataType>& Array, TUnrealJsonSerializer& Serializer);

	template <typename TMapType, typename TDataType = TMapType>
	constexpr static void SerializeMap(const FString& Identifier, const TMap<FString, TMapType>& Map, TUnrealJsonSerializer& Serializer);

	template<typename TOptionalType, typename TData = TOptionalType>
	constexpr static void DeserializeOptional(const FString& Identifier, const TSharedPtr<FJsonObject>& OwnerBag, FBeamOptional& ToDeserialize);
	
	template <typename TDataType>
	constexpr static void DeserializeArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<TDataType>& Array);

	template <typename TMapType, typename TDataType = TMapType>
	constexpr static void DeserializeMap(const TSharedPtr<FJsonObject>& JsonMap, TMap<FString, TMapType>& Map);
};