
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/StatRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "DeleteStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make DeleteStats",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,Outer"))
	static UDeleteStatsRequest* Make(FString _ObjectId, FOptionalString _Stats, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsSuccess, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsError, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteStatsComplete, FBeamRequestContext, Context, UDeleteStatsRequest*, Request);

using FDeleteStatsFullResponse = FBeamFullResponse<UDeleteStatsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteStatsFullResponse, FDeleteStatsFullResponse);
