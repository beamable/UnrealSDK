#pragma once

#include "RequestType.generated.h"
/**
* @brief Semantic separation for strings representing each Beamable Request Type (each endpoint). 
 */
USTRUCT(BlueprintType)
struct FRequestType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	explicit FRequestType()
	{
	}

	FRequestType(const FString& x) { Name = x; }

	FRequestType& operator=(const FString& x)
	{
		this->Name = x;
		return *this;
	}

	bool operator==(const FRequestType& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FRequestType& Other) const
	{
		return Name.Equals(Other.Name);
	}

	operator FString() { return Name; }
};

FORCEINLINE uint32 GetTypeHash(const FRequestType& RequestType) { return GetTypeHash(RequestType.Name); }
