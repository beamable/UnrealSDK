#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "Serialization/BeamJsonSerializable.h"

#include "BeamAnalyticsCallsite.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamAnalyticsCallsite : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString File;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Line = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Function;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double TimestampUtcSeconds = 0.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString UserSlot;

	FBeamAnalyticsCallsite() = default;
	FBeamAnalyticsCallsite(const FString& InFile, int32 InLine, const FString& InFunction,
		double InTimestampUtcSeconds, const FString& InUserSlot)
		: File(InFile)
		, Line(InLine)
		, Function(InFunction)
		, TimestampUtcSeconds(InTimestampUtcSeconds)
		, UserSlot(InUserSlot)
	{
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("File"), File);
		Serializer->WriteValue(TEXT("Line"), Line);
		Serializer->WriteValue(TEXT("Function"), Function);
		Serializer->WriteValue(TEXT("TimestampUtcSeconds"), TimestampUtcSeconds);
		Serializer->WriteValue(TEXT("UserSlot"), UserSlot);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("File"), File);
		Serializer->WriteValue(TEXT("Line"), Line);
		Serializer->WriteValue(TEXT("Function"), Function);
		Serializer->WriteValue(TEXT("TimestampUtcSeconds"), TimestampUtcSeconds);
		Serializer->WriteValue(TEXT("UserSlot"), UserSlot);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		if (Bag->HasField(TEXT("File")))
			File = Bag->GetStringField(TEXT("File"));
		if (Bag->HasField(TEXT("Line")))
			Line = Bag->GetIntegerField(TEXT("Line"));
		if (Bag->HasField(TEXT("Function")))
			Function = Bag->GetStringField(TEXT("Function"));
		if (Bag->HasField(TEXT("TimestampUtcSeconds")))
			TimestampUtcSeconds = Bag->GetNumberField(TEXT("TimestampUtcSeconds"));
		if (Bag->HasField(TEXT("UserSlot")))
			UserSlot = Bag->GetStringField(TEXT("UserSlot"));
	}
};

#define BEAM_ANALYTICS_CALLSITE() \
	FBeamAnalyticsCallsite( \
		FString(ANSI_TO_TCHAR(__FILE__)), \
		static_cast<int32>(__LINE__), \
		FString(ANSI_TO_TCHAR(__FUNCTION__)), \
		FDateTime::UtcNow().ToUnixTimestampDecimal(), \
		FString())
