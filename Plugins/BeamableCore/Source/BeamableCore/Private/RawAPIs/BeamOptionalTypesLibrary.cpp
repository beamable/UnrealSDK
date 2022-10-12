// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "RawAPIs/BeamOptionalTypesLibrary.h"
//
// #include "Serialization/BeamJsonUtils.h"
//
// FOptionalInt UBeamOptionalTypesLibrary::MakeOptionalInt(const int& Value)
// {
// 	FOptionalInt OptionalInt;
// 	OptionalInt.Val = Value;
// 	OptionalInt.IsSet = true;
// 	return OptionalInt;
// }
//
// FOptionalString UBeamOptionalTypesLibrary::MakeOptionalString(const FString& Value)
// {
// 	FOptionalString Optional;
// 	Optional.Val = Value;
// 	Optional.IsSet = true;
// 	return Optional;
// }
//
// FString UBeamOptionalTypesLibrary::Conv_OptionalToString(const FOptionalString& Optional)
// {
// 	return Optional.Val;
// }
//
// FOptionalString UBeamOptionalTypesLibrary::Conv_StringToOptional(const FString& Value)
// {
// 	FOptionalString Optional;
// 	Optional.Val = Value;
// 	Optional.IsSet = true;
// 	return Optional;
// }
