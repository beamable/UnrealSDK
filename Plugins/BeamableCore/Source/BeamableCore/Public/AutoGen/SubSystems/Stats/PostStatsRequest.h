
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/StatUpdateRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPostStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make PostStats",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bEmitAnalytics,Body_ObjectId,_Set,_Add,RequestOwner"))
	static UPostStatsRequest* Make(FString _ObjectId, FOptionalBool _bEmitAnalytics, FOptionalString Body_ObjectId, FOptionalMapOfString _Set, FOptionalMapOfString _Add, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsSuccess, FBeamRequestContext, Context, UPostStatsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsError, FBeamRequestContext, Context, UPostStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostStatsComplete, FBeamRequestContext, Context, UPostStatsRequest*, Request);

using FPostStatsFullResponse = FBeamFullResponse<UPostStatsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostStatsFullResponse, FPostStatsFullResponse);
