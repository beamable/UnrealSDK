// Fill out your copyright notice in the Description page of Project Settings.


#include "RawAPIs/BeamOptionalTypes.h"



#include "Serialization/BeamJsonUtils.h"




FOptionalInt::FOptionalInt()
{	
	Val = int();
	IsSet = false;
}

FOptionalInt::FOptionalInt(int Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInt::GetAddr() const { return &Val; }

void FOptionalInt::Set(const void* Data)
{
	Val = *static_cast<const int*>(Data);
	IsSet = true;
}



// FOptionalString::FOptionalString()
// {
// 	Val = FString();
// 	IsSet = false;
// }
//
// FOptionalString::FOptionalString(FString Val): Val(Val)
// {
// 	IsSet = true;
// }
//
// const void* FOptionalString::GetAddr() const { return &Val; }
//
// void FOptionalString::Set(const void* Data)
// {
// 	Val = *static_cast<const FString*>(Data);
// 	IsSet = true;
// }

// FArrayOfString::FArrayOfString() = default;
//
// FArrayOfString::FArrayOfString(const TArray<FString>& Values): Values(Values)
// {
// }
//
// void FArrayOfString::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
// {
// 	for (const auto& Value : Values) Serializer->WriteValue(Value);
// }
//
// void FArrayOfString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
// {
// 	for (const auto& Value : Values) Serializer->WriteValue(Value);
// }
//
// void FArrayOfString::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
// {
// 	UBeamJsonUtils::DeserializeArray<FString>(Elements, Values);
// }
//
// FMapOfString::FMapOfString() = default;
//
// FMapOfString::FMapOfString(const TMap<FString, FString>& Val): Values(Val)
// {}
//
// void FMapOfString::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
// }
//
// void FMapOfString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
// }
//
// void FMapOfString::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements)
// {
// 	UBeamJsonUtils::DeserializeMap<FString>(Elements, Values);
// }
//
// FArrayOfTokenResponse::FArrayOfTokenResponse()
// {
// }
//
// FArrayOfTokenResponse::FArrayOfTokenResponse(const TArray<UTokenResponse*>& Val) : Values(Val)
// {
// }
//
// FArrayOfTokenResponse::~FArrayOfTokenResponse()
// {
// 	for (const auto& Value : Values)
// 		Value->MarkAsGarbage();
// }
//
// void FArrayOfTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeArray<UTokenResponse*>(Values, Serializer);	
// }
//
// void FArrayOfTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeArray<UTokenResponse*>(Values, Serializer);
// }
//
// void FArrayOfTokenResponse::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
// {
// 	UBeamJsonUtils::DeserializeArray<UTokenResponse*>(Elements, Values);	
// }
//
// FMapOfTokenResponse::FMapOfTokenResponse()
// {
// }
//
// FMapOfTokenResponse::FMapOfTokenResponse(const TMap<FString, UTokenResponse*>& Val) : Values(Val)
// {
// }
//
// FMapOfTokenResponse::~FMapOfTokenResponse()
// {
// 	for (const auto& Value : Values)
// 		Value.Value->MarkAsGarbage();
// }
//
// void FMapOfTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeMap<UTokenResponse*>(Values, Serializer);
// }
//
// void FMapOfTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
// {
// 	UBeamJsonUtils::SerializeMap<UTokenResponse*>(Values, Serializer);
//
// }
//
// void FMapOfTokenResponse::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements)
// {
// 	UBeamJsonUtils::DeserializeMap<UTokenResponse*>(Elements, Values);	
// }