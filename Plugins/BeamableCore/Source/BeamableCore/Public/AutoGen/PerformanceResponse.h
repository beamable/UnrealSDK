
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/PANamespace.h"
#include "AutoGen/PASuggestedIndex.h"
#include "AutoGen/PASlowQuery.h"
#include "AutoGen/DatabaseMeasurements.h"

#include "PerformanceResponse.generated.h"

UCLASS(BlueprintType)
class UPerformanceResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespaces")
	TArray<UPANamespace*> Namespaces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Indexes")
	TArray<UPASuggestedIndex*> Indexes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Queries")
	TArray<UPASlowQuery*> Queries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Database Measurements")
	UDatabaseMeasurements* DatabaseMeasurements;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};