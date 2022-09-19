// Fill out your copyright notice in the Description page of Project Settings.


#include "RawAPIs/BeamOptionalTypes.h"

FOptionalInt::FOptionalInt()
{
	Val = 0;
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



FOptionalString::FOptionalString()
{
	Val = 0;
	IsSet = false;
}

FOptionalString::FOptionalString(FString Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalString::GetAddr() const { return &Val; }

void FOptionalString::Set(const void* Data)
{
	Val = *static_cast<const FString*>(Data);
	IsSet = true;
}
