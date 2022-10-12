
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/StatsResponse.h"

#include "GetStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalString Stats;

	// Body Params
	

	// Beam Base Request Declaration
	UGetStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,Outer"))
	static UGetStatsRequest* MakeGetStatsRequest(FString _ObjectId, FOptionalString _Stats, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatsSuccess, FBeamRequestContext, Context, UGetStatsRequest*, Request, UStatsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatsError, FBeamRequestContext, Context, UGetStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStatsComplete, FBeamRequestContext, Context, UGetStatsRequest*, Request);

using FGetStatsFullResponse = FBeamFullResponse<UGetStatsRequest*, UStatsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStatsFullResponse, FGetStatsFullResponse);
