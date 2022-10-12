
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/StatUpdateRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Body_ObjectId,_Set,_Add,_bEmitAnalytics,Outer"))
	static UPostStatsRequest* MakePostStatsRequest(FString _ObjectId, FOptionalString Body_ObjectId, FOptionalMapOfString _Set, FOptionalMapOfString _Add, FOptionalBool _bEmitAnalytics, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsSuccess, FBeamRequestContext, Context, UPostStatsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsError, FBeamRequestContext, Context, UPostStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostStatsComplete, FBeamRequestContext, Context, UPostStatsRequest*, Request);

using FPostStatsFullResponse = FBeamFullResponse<UPostStatsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostStatsFullResponse, FPostStatsFullResponse);
