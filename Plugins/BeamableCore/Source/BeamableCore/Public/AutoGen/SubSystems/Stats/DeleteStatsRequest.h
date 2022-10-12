
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/StatRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,Outer"))
	static UDeleteStatsRequest* MakeDeleteStatsRequest(FString _ObjectId, FOptionalString _Stats, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsSuccess, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsError, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteStatsComplete, FBeamRequestContext, Context, UDeleteStatsRequest*, Request);

using FDeleteStatsFullResponse = FBeamFullResponse<UDeleteStatsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteStatsFullResponse, FDeleteStatsFullResponse);
