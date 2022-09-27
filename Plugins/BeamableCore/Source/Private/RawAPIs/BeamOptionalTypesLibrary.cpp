// Fill out your copyright notice in the Description page of Project Settings.


#include "RawAPIs/BeamOptionalTypesLibrary.h"

#include "BeamJsonUtils.h"

FOptionalInt UBeamOptionalTypesLibrary::MakeOptionalInt(const int& Value)
{
	FOptionalInt OptionalInt;
	OptionalInt.Val = Value;
	OptionalInt.IsSet = true;
	return OptionalInt;
}

FOptionalString UBeamOptionalTypesLibrary::MakeOptionalString(const FString& Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}
